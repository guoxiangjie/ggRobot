"""平台侧多机编排执行器 — 分发 / 广播 / 聚合 / 失败跳过

流程（docs/choreo-design.md §5）：
    1. 校验：track 引用的机器人在库（离线机标记 unavailable，其余照跑）
    2. 分发：并发 POST /api/choreo/load（每台机器人自己的轨道）
    3. 广播：start_ts = now + 1.5s，并发 POST /api/choreo/start
       （agent 以 start_ts 为时间轴原点，各机消息到达先后不影响对齐）
    4. 监控：后台 task 轮询各机 /api/choreo/status（1s）聚合
       → 掉线/无响应 3 次 → 该机 failed，其余机继续（跳过继续+汇报）
    5. 全部终态 → run finished；超时（默认 10min）→ 未完成机标 failed

约束：全局同时只允许一个 active run（agent 控制会话锁也保证单控制者）。
"""

import asyncio
import logging
import time
import uuid
from collections import deque
from datetime import datetime, timezone

from ..agent_client import (
    choreo_load, choreo_start, choreo_stop, choreo_status,
)

logger = logging.getLogger(__name__)

START_DELAY = 1.5          # 广播 start_ts 的余量（秒）
POLL_INTERVAL = 1.0        # 状态轮询间隔
POLL_FAIL_LIMIT = 3        # 连续无响应次数上限 → 判该机失败
RUN_TIMEOUT = 600.0        # run 总超时（秒）

# 机器人状态机（与 agent 对齐 + 平台侧补充）
RB_PENDING = "pending"       # 待分发
RB_LOADING = "loading"       # 分发中
RB_RUNNING = "running"       # 执行中
RB_FINISHED = "finished"
RB_STOPPED = "stopped"
RB_FAILED = "failed"         # 掉线/无响应/load 失败
RB_UNAVAILABLE = "unavailable"  # 启动前校验离线，未参与

_TERMINAL = {RB_FINISHED, RB_STOPPED, RB_FAILED, RB_UNAVAILABLE}


class ChoreoRun:
    """单次多机编排执行"""

    def __init__(self, run_id: str, choreo_id: str, name: str):
        self.run_id = run_id
        self.choreo_id = choreo_id
        self.name = name
        self.state = "pending"          # pending → running → finished/stopped/failed
        self.start_ts = 0.0
        self.robots: list[dict] = []    # 每机 {robot_id, name, ip, token, state, current, total, failed, error, fail_count}
        self.created_at = datetime.now(timezone.utc).isoformat(timespec="seconds")
        self.ended_at = ""
        self._task: asyncio.Task | None = None

    def to_dict(self) -> dict:
        return {
            "run_id": self.run_id,
            "choreo_id": self.choreo_id,
            "name": self.name,
            "state": self.state,
            "start_ts": self.start_ts,
            "robots": [dict(r) for r in self.robots],
            "created_at": self.created_at,
            "ended_at": self.ended_at,
        }


class ChoreoRunner:
    def __init__(self):
        self._lock = asyncio.Lock()
        self._runs: dict[str, ChoreoRun] = {}
        self._active_run_id: str | None = None
        # 最近执行历史（终态 run，内存保留，供"最近执行"回看）
        self._history: deque[dict] = deque(maxlen=20)

    # ── 控制面 ──

    async def run(self, choreo: dict, robots: dict[str, dict]) -> dict:
        """执行编排。choreo: {id, name, tracks:[{robot_id, steps}]}；robots: {robot_id: {name, ip, token}}"""
        async with self._lock:
            if self._active_run_id is not None:
                return {"ok": False, "error": f"已有编排在执行: {self._active_run_id}"}

        tracks = choreo.get("tracks") or []
        if not tracks:
            return {"ok": False, "error": "编排无轨道"}

        run_id = str(uuid.uuid4())[:8]
        run = ChoreoRun(run_id, choreo.get("id", ""), choreo.get("name", "未命名"))
        offline: list[str] = []

        for tr in tracks:
            rid = tr.get("robot_id", "")
            steps = tr.get("steps") or []
            rb = robots.get(rid)
            if rb is None:
                offline.append(f"{tr.get('robot_name', rid)}(未登记)")
                continue
            if not rb.get("ip"):
                offline.append(f"{rb.get('name', rid)}(无 IP)")
                continue
            run.robots.append({
                "robot_id": rid, "name": rb.get("name", rid),
                "ip": rb["ip"], "port": int(rb.get("port", 8300) or 8300),
                "token": rb.get("token", ""),
                "state": RB_LOADING, "current": -1, "total": len(steps),
                "failed": [], "error": "", "fail_count": 0,
                "_steps": steps,
            })
        if not run.robots:
            return {"ok": False, "error": "没有可执行的机器人轨道"}

        run.state = "running"
        self._runs[run_id] = run
        self._active_run_id = run_id
        logger.info(f"🎬 编排启动: {run.name} ({run_id}) 机器 x{len(run.robots)}" +
                    (f"，离线跳过: {offline}" if offline else ""))

        run._task = asyncio.create_task(self._execute(run))
        return {"ok": True, "run_id": run_id, "offline": offline}

    async def stop(self, run_id: str) -> dict:
        run = self._runs.get(run_id)
        if run is None:
            return {"ok": False, "error": "run 不存在"}
        # 并发停止所有还在跑的机器（幂等，agent 侧 stop 重复安全）
        await asyncio.gather(*(
            choreo_stop(rb["ip"], rb["token"], run_id, rb["port"])
            for rb in run.robots if rb["state"] not in _TERMINAL
        ))
        # 等监控 task 收敛（agent 侧 stop 后状态会转 stopped）
        if run._task and not run._task.done():
            try:
                await asyncio.wait_for(run._task, timeout=8.0)
            except asyncio.TimeoutError:
                run.state = "stopped"
                run.ended_at = self._now()
                self._clear_active(run_id)
        return {"ok": True, "run_id": run_id}

    def status(self, run_id: str) -> dict:
        run = self._runs.get(run_id)
        if run is None:
            return {"ok": False, "error": "run 不存在"}
        return {"ok": True, **run.to_dict()}

    def active_runs(self) -> list[dict]:
        """hub 推送用：当前活跃 run（未终态）"""
        return [r.to_dict() for r in self._runs.values()
                if r.state not in ("finished", "stopped", "failed")]

    def history(self) -> list[dict]:
        """最近执行历史（终态，倒序）"""
        return list(self._history)

    def _record_history(self, run: ChoreoRun) -> None:
        """run 终态时记入历史（清理 _steps 内部字段）"""
        d = run.to_dict()
        for rb in d["robots"]:
            rb.pop("_steps", None)
        self._history.appendleft(d)

    # ── 执行流程（后台 task）──

    async def _execute(self, run: ChoreoRun) -> None:
        try:
            # 1. 并发分发轨道
            results = await asyncio.gather(*(
                self._load_one(run, rb) for rb in run.robots
            ))
            alive = [rb for rb, ok in zip(run.robots, results) if ok]
            if not alive:
                run.state = "failed"
                run.ended_at = self._now()
                self._clear_active(run.run_id)
                self._record_history(run)
                return

            # 2. 广播开始（绝对墙钟时刻）
            run.start_ts = time.time() + START_DELAY
            await asyncio.gather(*(
                choreo_start(rb["ip"], rb["token"], run.run_id, run.start_ts, rb["port"])
                for rb in alive
            ))
            logger.info(f"🎬 广播开始 run={run.run_id} start_ts={run.start_ts:.3f}")

            # 3. 监控轮询聚合
            deadline = time.time() + RUN_TIMEOUT
            while time.time() < deadline:
                await asyncio.sleep(POLL_INTERVAL)
                await self._poll(run)
                if all(rb["state"] in _TERMINAL for rb in run.robots):
                    break
            else:
                # 超时：未完成机标 failed
                for rb in run.robots:
                    if rb["state"] not in _TERMINAL:
                        rb["state"] = RB_FAILED
                        rb["error"] = "run 超时"

            run.state = "finished"
            run.ended_at = self._now()
            logger.info(
                f"🎬 编排结束 run={run.run_id} 机器 "
                + ", ".join(f"{rb['name']}:{rb['state']}(fail {len(rb['failed'])})" for rb in run.robots))
            self._clear_active(run.run_id)
            self._record_history(run)
        except Exception as e:
            logger.exception(f"🎬 编排执行异常 run={run.run_id}")
            run.state = "failed"
            run.ended_at = self._now()
            self._clear_active(run.run_id)
            self._record_history(run)

    async def _load_one(self, run: ChoreoRun, rb: dict) -> bool:
        """分发单机轨道；失败 → 标记该机 failed（跳过继续）"""
        resp = await choreo_load(rb["ip"], rb["token"], run.run_id, rb.get("_steps") or [], rb["port"])
        if resp is None or not resp.get("ok"):
            rb["state"] = RB_FAILED
            rb["error"] = "load 失败（agent 无响应/会话被占）"
            logger.warning(f"🎬 分发失败 {rb['name']}: {rb['error']}")
            return False
        rb["state"] = RB_RUNNING
        return True

    async def _poll(self, run: ChoreoRun) -> None:
        """轮询各机状态并聚合（掉线连续 3 次判失败）"""
        for rb in run.robots:
            if rb["state"] in _TERMINAL:
                continue
            st = await choreo_status(rb["ip"], rb["token"], run.run_id, rb["port"])
            if st is None or not st.get("ok"):
                rb["fail_count"] += 1
                if rb["fail_count"] >= POLL_FAIL_LIMIT:
                    rb["state"] = RB_FAILED
                    rb["error"] = "连续无响应（掉线）"
                    logger.warning(f"🎬 {rb['name']} 掉线判失败")
                continue
            rb["fail_count"] = 0
            rb["state"] = st.get("state", RB_RUNNING)
            rb["current"] = st.get("current", rb.get("current", -1))
            rb["total"] = st.get("total", rb.get("total", 0))
            if st.get("failed"):
                rb["failed"] = st["failed"]
            if st.get("state") == RB_FAILED:
                rb["error"] = st.get("error", "")

    def _clear_active(self, run_id: str) -> None:
        if self._active_run_id == run_id:
            self._active_run_id = None

    @staticmethod
    def _now() -> str:
        return datetime.now(timezone.utc).isoformat(timespec="seconds")


# 模块级单例
runner = ChoreoRunner()
