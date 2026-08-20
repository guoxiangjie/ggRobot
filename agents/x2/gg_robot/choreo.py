"""多机编排执行器（agent 侧）— 时间戳锚定 + 本地按 at 推进

协议（docs/choreo-design.md §3-4）：
    load(run_id, steps)   —— 平台预分发本机轨道（steps 含 type/at/参数）
    start(run_id, start_ts) —— 以【绝对墙钟时刻】start_ts 为时间轴原点起执行线程
    stop(run_id)          —— 置停止标志（步骤边界生效）+ 发全零速度收尾
    status(run_id)        —— 主动查询

调度语义（简单且鲁棒）：
    - 步骤按 at 升序，每步最早开始时刻 = start_ts + at
    - 步骤间顺序执行：实际开始 = max(due, 上一步完成时刻)
      → 同一轨不会自打架（TTS 未播完不冲突），跨机仍由 at 锚定同一绝对时刻
    - 步骤执行用内置轻量执行器 _exec_step（不复用 task/steps.py 的 handler：
      ① _tts 在子线程调 _do_tts 吞异常，② execute_step 内部 catch 异常不重新抛，
      两者都会让 choreo 收不到失败信号），失败 raise → 记入 failed 跳过继续
    - 等待语义：motion/tts 完成后估时等待（wait_done），velocity 持续 duration

线程模型：执行线程是 daemon 线程，只调线程安全的 node 方法（service 走 future
轮询、velocity 元组原子替换）；WS 上报经 run_coroutine_threadsafe 投递到 FastAPI
事件循环（照 security.py ControllerLock._notify_lost 的模式），绝不阻塞 rclpy 回调。
"""

import asyncio
import logging
import threading
import time
from typing import Any

logger = logging.getLogger(__name__)

# run 状态机：loaded → running → finished / stopped / failed
STATE_LOADED = "loaded"
STATE_RUNNING = "running"
STATE_FINISHED = "finished"
STATE_STOPPED = "stopped"
STATE_FAILED = "failed"


class _Run:
    """单次编排执行（每 run_id 一个实例）"""

    __slots__ = (
        "run_id", "steps", "state", "current", "total",
        "failed", "start_ts", "loop", "thread", "stop_flag",
    )

    def __init__(self, run_id: str, steps: list[dict]):
        self.run_id = run_id
        # 按 at 升序（缺省 0），执行器依赖有序
        self.steps = sorted(steps or [], key=lambda s: float(s.get("at", 0.0)))
        self.state = STATE_LOADED
        self.current = -1
        self.total = len(self.steps)
        self.failed: list[dict] = []
        self.start_ts = 0.0
        self.loop: asyncio.AbstractEventLoop | None = None
        self.thread: threading.Thread | None = None
        self.stop_flag = False

    def to_dict(self) -> dict:
        return {
            "run_id": self.run_id,
            "state": self.state,
            "current": self.current,
            "total": self.total,
            "failed": self.failed,
            "start_ts": self.start_ts,
        }


class ChoreoRunner:
    """多 run 并存（控制会话锁保证实际同一时刻只有一个控制者，互不干扰）"""

    def __init__(self):
        self._lock = threading.Lock()
        self._runs: dict[str, _Run] = {}

    # ── 控制面（路由线程调用，线程安全）──

    def load(self, run_id: str, steps: list[dict]) -> dict:
        with self._lock:
            self._runs[run_id] = _Run(run_id, steps)
        logger.info(f"🎬 choreo load: run={run_id} steps={len(steps)}")
        return {"ok": True, "run_id": run_id, "loaded": len(steps)}

    def start(self, run_id: str, start_ts: float, loop: asyncio.AbstractEventLoop) -> dict:
        with self._lock:
            run = self._runs.get(run_id)
            if run is None:
                return {"ok": False, "error": "run 不存在（先 load）"}
            if run.state == STATE_RUNNING:
                return {"ok": False, "error": "run 已在执行中"}
            run.start_ts = float(start_ts)
            run.loop = loop
            run.stop_flag = False
            run.state = STATE_RUNNING
            run.thread = threading.Thread(
                target=self._execute, args=(run,), daemon=True, name=f"choreo-{run_id}")
            run.thread.start()
        logger.info(f"🎬 choreo start: run={run_id} start_ts={start_ts:.3f} steps={run.total}")
        return {"ok": True, "run_id": run_id, "start_ts": start_ts}

    def stop(self, run_id: str) -> dict:
        with self._lock:
            run = self._runs.get(run_id)
            if run is None:
                return {"ok": False, "error": "run 不存在"}
            run.stop_flag = True
        logger.info(f"⏹ choreo stop: run={run_id}")
        # 同步发全零速度（安全收尾，线程安全）
        try:
            from . import node as node_mod
            if node_mod._node is not None:
                node_mod._node._do_velocity(0.0, 0.0, 0.0)
        except Exception as e:
            logger.warning(f"⏹ choreo stop 发零速失败: {e}")
        return {"ok": True, "run_id": run_id}

    def status(self, run_id: str) -> dict:
        with self._lock:
            run = self._runs.get(run_id)
            if run is None:
                return {"ok": False, "error": "run 不存在"}
            return {"ok": True, **run.to_dict()}

    # ── 执行线程 ──

    def _execute(self, run: _Run) -> None:
        try:
            from . import node as node_mod
            node = node_mod._node
            if node is None:
                run.state = STATE_FAILED
                self._report(run, "choreo.state", {"state": run.state, "error": "node 未就绪"})
                return

            for i, step in enumerate(run.steps):
                if run.stop_flag:
                    break
                run.current = i

                # 1) 等到点（start_ts + at），分片 sleep 检查停止
                due = run.start_ts + float(step.get("at", 0.0))
                while time.time() < due and not run.stop_flag:
                    time.sleep(0.05)

                if run.stop_flag:
                    break

                step_type = step.get("type", "?")
                self._report(run, "choreo.step", {
                    "index": i, "type": step_type, "at": step.get("at", 0.0),
                    "status": "started",
                })
                try:
                    self._run_step(node, step)
                    self._report(run, "choreo.step", {
                        "index": i, "type": step_type, "at": step.get("at", 0.0),
                        "status": "done",
                    })
                except Exception as e:
                    logger.error(f"🎬 步骤失败 [{i}] {step_type}: {e}")
                    run.failed.append({
                        "index": i, "type": step_type, "at": step.get("at", 0.0),
                        "error": str(e)[:200],
                    })
                    self._report(run, "choreo.step", {
                        "index": i, "type": step_type, "at": step.get("at", 0.0),
                        "status": "failed", "error": str(e)[:200],
                    })
                    # 失败跳过继续

            # 2) 收尾：状态判定 + 零速兜底
            try:
                node._do_velocity(0.0, 0.0, 0.0)
            except Exception:
                pass
            run.state = STATE_STOPPED if run.stop_flag else STATE_FINISHED
            logger.info(
                f"🎬 choreo 结束: run={run.run_id} state={run.state} "
                f"failed={len(run.failed)}/{run.total}")
            self._report(run, "choreo.state", {
                "state": run.state, "failed": run.failed, "total": run.total,
            })
        except Exception as e:
            logger.exception("🎬 choreo 执行线程异常")
            run.state = STATE_FAILED
            self._report(run, "choreo.state", {"state": run.state, "error": str(e)[:200]})

    def _run_step(self, node, step: dict) -> None:
        """执行单个步骤：内部轻量执行器，失败 raise（由 _execute 记入 failed）。"""
        _exec_step(node, step)

    def _report(self, run: _Run, topic: str, data: dict) -> None:
        """执行线程 → FastAPI 事件循环投递 WS 上报（run.loop 由 start 注入）"""
        loop = run.loop
        if loop is None:
            return
        try:
            from .ws.stream import publish
            coro = publish(topic, {"run_id": run.run_id, **data})
            asyncio.run_coroutine_threadsafe(coro, loop)
        except Exception as e:
            logger.warning(f"🎬 WS 上报失败: {e}")


# ── 轻量步骤执行器 ─────────────────────────────
# 每类步骤 → node 方法调用 + 等待策略。失败 raise（调用方记 failed 跳过继续）。
# 复用 task/motions.py 的动作归一化/估时，不复用 task/steps.py 的 handler（原因见模块 docstring）。

def _exec_step(node, step: dict) -> None:
    t = step.get("type", "")

    if t == "tts":
        text = str(step.get("text", "") or "")
        if not text:
            raise ValueError("tts 缺 text")
        ok = node._do_tts(text)
        if not ok:
            raise RuntimeError("TTS 下发失败")
        if step.get("wait_done", True):
            node.wait_tts_done(timeout=float(step.get("timeout", 20.0) or 20.0))

    elif t == "motion":
        from .task.motions import normalize_motion, motion_duration
        motion_id, area, valid = normalize_motion(step.get("motion_id", 0), step.get("area", 0))
        if not valid:
            raise ValueError(f"动作组合无效 motion={motion_id} area={area}")
        r = node._do_motion(area, motion_id, step.get("interrupt", True))
        if not r.get("ok"):
            raise RuntimeError("预设动作执行失败")
        if step.get("wait_done", True):
            node._sleep(motion_duration(motion_id, area))

    elif t == "emoji":
        r = node._do_emoji(int(step.get("emotion_id", 0)), int(step.get("mode", 1)))
        if not r.get("ok"):
            raise RuntimeError("表情执行失败")

    elif t == "velocity":
        node._do_velocity(
            float(step.get("forward", 0.0)), float(step.get("lateral", 0.0)),
            float(step.get("angular", 0.0)))
        node._sleep(float(step.get("duration", 1.0) or 1.0))
        node._do_velocity(0.0, 0.0, 0.0)

    elif t == "wait":
        node._sleep(float(step.get("duration", 1.0) or 1.0))

    elif t == "mode":
        r = node._do_mode(str(step.get("action_desc", "STAND_DEFAULT") or "STAND_DEFAULT"),
                          int(step.get("action_value", 0) or 0))
        if not r.get("ok"):
            raise RuntimeError(f"模式切换失败: {r.get('message', '')}")

    elif t == "volume":
        node._do_set_volume(int(step.get("volume", 50)))

    elif t == "media":
        from ..routes.media import PC3_MEDIA
        name = str(step.get("file_name", "") or "")
        if not name:
            raise ValueError("media 缺 file_name")
        r = node._do_media_play(f"{PC3_MEDIA}/{name}", name)
        if not r.get("ok"):
            raise RuntimeError("媒体播放失败")

    elif t == "linkcraft":
        from .task.steps import _linkcraft_est
        rk = str(step.get("resource_key", "") or "")
        if not rk:
            raise ValueError("linkcraft 缺 resource_key")
        rtype = str(step.get("resource_type", "") or "")
        r = node._play_resource(rk, str(step.get("version", "") or ""), rtype)
        if not r.get("ok"):
            raise RuntimeError("灵创动作执行失败")
        if step.get("wait_done", True):
            node._sleep(float(step.get("duration") or _linkcraft_est(rtype)))

    else:
        raise ValueError(f"未知步骤类型: {t}")


# 模块级单例（与 security.controller 模式一致）
runner = ChoreoRunner()
