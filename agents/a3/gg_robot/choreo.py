"""A3 多机编排执行器 — 时间戳锚定 + 本地按 at 推进（协议与 X2 版一致，docs/choreo-design.md）

A3 差异红利：
- tts 用 trace_id 精确等播完（X2 只能估时）
- motion 用资源真实 duration 等待（X2 需实测回填）
- 新步骤：dance（舞蹈）/ nav（导航到点）
"""

import asyncio
import logging
import threading
import time

from . import motions_data

logger = logging.getLogger(__name__)

STATE_LOADED = "loaded"
STATE_RUNNING = "running"
STATE_FINISHED = "finished"
STATE_STOPPED = "stopped"
STATE_FAILED = "failed"


class _Run:
    __slots__ = ("run_id", "steps", "state", "current", "total",
                 "failed", "start_ts", "loop", "thread", "stop_flag")

    def __init__(self, run_id: str, steps: list[dict]):
        self.run_id = run_id
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
        return {"run_id": self.run_id, "state": self.state, "current": self.current,
                "total": self.total, "failed": self.failed, "start_ts": self.start_ts}


class ChoreoRunner:
    """多 run 并存（会话锁保证单控制者）"""

    def __init__(self):
        self._lock = threading.Lock()
        self._runs: dict[str, _Run] = {}

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
            run.thread = threading.Thread(target=self._execute, args=(run,),
                                          daemon=True, name=f"choreo-{run_id}")
            run.thread.start()
        return {"ok": True, "run_id": run_id, "start_ts": start_ts}

    def stop(self, run_id: str) -> dict:
        with self._lock:
            run = self._runs.get(run_id)
            if run is None:
                return {"ok": False, "error": "run 不存在"}
            run.stop_flag = True
        try:
            from . import node as node_mod
            if node_mod._node is not None:
                node_mod._node.stop_velocity()
        except Exception as e:
            logger.warning(f"⏹ choreo stop 发零速失败: {e}")
        return {"ok": True, "run_id": run_id}

    def status(self, run_id: str) -> dict:
        with self._lock:
            run = self._runs.get(run_id)
            if run is None:
                return {"ok": False, "error": "run 不存在"}
            return {"ok": True, **run.to_dict()}

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
                due = run.start_ts + float(step.get("at", 0.0))
                while time.time() < due and not run.stop_flag:
                    time.sleep(0.05)
                if run.stop_flag:
                    break
                step_type = step.get("type", "?")
                self._report(run, "choreo.step",
                             {"index": i, "type": step_type, "at": step.get("at", 0.0), "status": "started"})
                try:
                    self._run_step(node, step)
                    self._report(run, "choreo.step",
                                 {"index": i, "type": step_type, "at": step.get("at", 0.0), "status": "done"})
                except Exception as e:  # noqa: BLE001
                    logger.error(f"🎬 步骤失败 [{i}] {step_type}: {e}")
                    run.failed.append({"index": i, "type": step_type,
                                       "at": step.get("at", 0.0), "error": str(e)[:200]})
                    self._report(run, "choreo.step",
                                 {"index": i, "type": step_type, "at": step.get("at", 0.0),
                                  "status": "failed", "error": str(e)[:200]})
            try:
                node.stop_velocity()
            except Exception:  # noqa: BLE001
                pass
            run.state = STATE_STOPPED if run.stop_flag else STATE_FINISHED
            self._report(run, "choreo.state", {"state": run.state, "failed": run.failed, "total": run.total})
        except Exception as e:  # noqa: BLE001
            logger.exception("🎬 choreo 执行线程异常")
            run.state = STATE_FAILED
            self._report(run, "choreo.state", {"state": run.state, "error": str(e)[:200]})

    def _run_step(self, node, step: dict) -> None:
        _exec_step(node, step)

    def _report(self, run: _Run, topic: str, data: dict) -> None:
        loop = run.loop
        if loop is None:
            return
        try:
            from .ws.stream import publish
            asyncio.run_coroutine_threadsafe(publish(topic, {"run_id": run.run_id, **data}), loop)
        except Exception as e:  # noqa: BLE001
            logger.warning(f"🎬 WS 上报失败: {e}")


# ── 轻量步骤执行器（失败 raise；控制走 rpc，速度走 node）──

def _exec_step(node, step: dict) -> None:
    import time as _t

    from . import rpc
    t = step.get("type", "")

    if t == "tts":
        text = str(step.get("text", "") or "")
        if not text:
            raise ValueError("tts 缺 text")
        # 配动手势（A3：选一个动作资源，仅上肢不出声的配说话类动作）：先发不等待 → 再播 TTS
        ga = step.get("gesture_motion_id")
        if ga:
            try:
                rpc.motion_command(motion_id=str(ga), duration_ms=int(step.get("gesture_ms", 15000)))
            except Exception as e:  # noqa: BLE001
                logger.warning(f"🎬 配动手势下发失败: {e}")
        r = rpc.tts_play(text)
        trace = r.get("trace_id", "")
        if step.get("wait_done", True):
            node.wait_tts_done(trace, timeout=max(5.0, len(text) / 3.0))

    elif t == "motion":
        mid = str(step.get("motion_id", "") or "")
        if not mid:
            raise ValueError("motion 缺 motion_id（资源路径）")
        # duration 优先取步骤显式值，兜底资源清单 duration，再兜底 8s
        dur_ms = int(float(step.get("duration") or _motion_ms(mid) or 8.0) * 1000)
        rpc.motion_command(motion_id=mid, duration_ms=dur_ms)
        if step.get("wait_done", True):
            _sleep_cancellable(node, dur_ms / 1000.0 + 0.5)

    elif t == "dance":
        path = str(step.get("path", "") or "")
        if not path:
            raise ValueError("dance 缺 path（技能资源路径）")
        rpc.dance("Start", path)
        if step.get("wait_done", True):
            _sleep_cancellable(node, float(step.get("duration") or 30.0))

    elif t == "nav":
        kind = str(step.get("kind", "goal"))
        map_id = step.get("map_id")
        if map_id is None:
            raise ValueError("nav 缺 map_id")
        kw = {}
        if step.get("target_id") is not None:
            kw["target_id"] = int(step["target_id"])
        elif step.get("x") is not None and step.get("y") is not None:
            kw["pose"] = {"position": {"x": float(step["x"]), "y": float(step["y"])},
                          "angle": float(step.get("angle", 0.0))}
        else:
            raise ValueError("nav 需要 target_id 或 x/y")
        r = rpc.navi(kind, map_id, **kw)
        task_id = r.get("task_id")
        if not task_id:
            raise RuntimeError(f"导航下发失败: {r}")
        if step.get("wait_done", True):   # 轮询到完成（≤1Hz 限频）
            deadline = _t.time() + float(step.get("timeout", 180.0))
            while _t.time() < deadline:
                _sleep_cancellable(node, 1.0)
                st = str(rpc.navi_state(int(task_id)).get("state", ""))
                if "SUCCESS" in st:
                    return
                if "FAILED" in st:
                    raise RuntimeError(f"导航失败 task={task_id}")

    elif t == "velocity":
        node.set_velocity(float(step.get("forward", 0.0)),
                          float(step.get("lateral", 0.0)),
                          float(step.get("angular", 0.0)))
        _sleep_cancellable(node, float(step.get("duration", 1.0) or 1.0))
        node.stop_velocity()

    elif t == "wait":
        _sleep_cancellable(node, float(step.get("duration", 1.0) or 1.0))

    elif t == "mode":
        r = rpc.action_set(str(step.get("action", "MOTION")))
        if "SUCCESS" not in str(r.get("state", "")):
            raise RuntimeError(f"模式切换失败: {r.get('state')}")

    elif t == "volume":
        rpc.volume_set(min(int(step.get("volume", 50)), 70))

    else:
        raise ValueError(f"未知步骤类型: {t}")


def _motion_ms(motion_id: str) -> float | None:
    """资源清单里的动作时长（秒）"""
    for m in motions_data.get_motions():
        if m["id"] == motion_id and m.get("duration"):
            return float(m["duration"])
    return None


def _sleep_cancellable(node, seconds: float) -> None:
    """分片 sleep（0.1s），急停触发时提前返回"""
    import time as _t
    deadline = _t.time() + max(0.0, seconds)
    while _t.time() < deadline:
        if node.emergency and node.emergency.get("active"):
            return
        _t.sleep(0.1)


# ── 步骤类型清单（GET /api/choreo/types；前端动态组装表单）──

def _motion_options() -> list[dict]:
    return [{"label": f"{m['name']}（{m.get('duration', '?')}s）", "value": m["id"]}
            for m in motions_data.get_motions()]


def _dance_options() -> list[dict]:
    return [{"label": s["name"], "value": s["path"]} for s in motions_data.get_skills()]


def build_step_types() -> list[dict]:
    return [
        {"type": "tts", "label": "语音", "icon": "🗣️", "color": "#4CAF50", "fields": [
            {"name": "text", "label": "播报文字", "kind": "text", "required": True},
            {"name": "wait_done", "label": "等播完（精确）", "kind": "switch", "default": True},
            {"name": "gesture_motion_id", "label": "配动手势（边说边做）", "kind": "select",
             "default": "", "options": [{"label": "无", "value": ""}] + _motion_options()},
        ]},
        {"type": "motion", "label": "预设动作", "icon": "🕺", "color": "#FF9800", "fields": [
            {"name": "motion_id", "label": "动作", "kind": "select", "required": True,
             "options": _motion_options()},
            {"name": "wait_done", "label": "等完成（真实时长）", "kind": "switch", "default": True},
        ]},
        {"type": "dance", "label": "舞蹈", "icon": "💃", "color": "#AB47BC", "fields": [
            {"name": "path", "label": "舞蹈", "kind": "select", "required": True,
             "options": _dance_options()},
            {"name": "wait_done", "label": "等完成", "kind": "switch", "default": True},
        ]},
        {"type": "nav", "label": "导航到点", "icon": "🧭", "color": "#00ACC1", "fields": [
            {"name": "map_id", "label": "地图 ID", "kind": "text", "required": True},
            {"name": "target_id", "label": "导航点 ID", "kind": "number"},
            {"name": "x", "label": "或目标 X(m)", "kind": "number"},
            {"name": "y", "label": "或目标 Y(m)", "kind": "number"},
            {"name": "angle", "label": "朝向 rad", "kind": "number", "default": 0},
            {"name": "wait_done", "label": "等到点", "kind": "switch", "default": True},
        ]},
        {"type": "velocity", "label": "速度", "icon": "🏃", "color": "#2196F3", "fields": [
            {"name": "forward", "label": "前后 m/s", "kind": "number", "default": 0.3},
            {"name": "lateral", "label": "左右 m/s", "kind": "number", "default": 0},
            {"name": "angular", "label": "旋转 rad/s", "kind": "number", "default": 0},
            {"name": "duration", "label": "持续秒", "kind": "number", "default": 2},
        ]},
        {"type": "wait", "label": "等待", "icon": "⏱️", "color": "#9E9E9E", "fields": [
            {"name": "duration", "label": "等待秒", "kind": "number", "default": 1},
        ]},
        {"type": "mode", "label": "模式", "icon": "⚙️", "color": "#795548", "fields": [
            {"name": "action", "label": "Action", "kind": "select", "default": "MOTION",
             "options": [
                 {"label": "运动模式", "value": "MOTION"},
                 {"label": "位控站立", "value": "PD_STAND"},
                 {"label": "阻尼", "value": "DAMPING"},
             ]},
        ]},
        {"type": "volume", "label": "音量", "icon": "🔊", "color": "#607D8B", "fields": [
            {"name": "volume", "label": "音量 0-70", "kind": "number", "default": 50},
        ]},
    ]


CHOREO_STEP_TYPES: list[dict] = []   # 动态清单经 build_step_types()（资源清单运行时拉取）
runner = ChoreoRunner()
