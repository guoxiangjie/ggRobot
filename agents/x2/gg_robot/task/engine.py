"""任务执行引擎 — 块式执行（顺序 / 并行组 / 分支），支持中断

引擎在 rclpy 线程中运行，通过命令队列触发。

块类型：
- 普通步骤：直接 execute_step（tts/motion/velocity/...）
- parallel：branches 内每个分支一个线程并发执行，全部完成后继续
- branch：eval_cond 为真走 then，否则走 else（then/else 为子步骤数组，可再嵌块）
"""

import logging
import threading
from dataclasses import dataclass, field
from datetime import datetime

from .steps import execute_step, StepAbort
from .cond import eval_cond
from .convert import ensure_task_v2
from .validate import validate_task

logger = logging.getLogger(__name__)


@dataclass
class TaskState:
    """任务执行状态"""
    running: bool = False
    task_id: str = ""
    task_name: str = ""
    total: int = 0
    current: int = 0
    current_step: dict | None = None
    started_at: str = ""


class TaskEngine:
    """任务执行引擎"""

    def __init__(self):
        self.state = TaskState()
        self._stop_flag = threading.Event()

    def run(self, node, task: dict):
        """执行任务（在 rclpy 线程中调用）"""
        if self.state.running:
            logger.warning("⚠️ 已有任务正在执行，请先停止")
            return {"ok": False, "error": "已有任务在运行"}

        steps = task.get("steps", [])
        if not steps:
            return {"ok": False, "error": "任务无步骤"}

        # 老任务（tts 挂载）→ v2 并行块（仅内存，不落盘）
        ensure_task_v2(task)
        errors = validate_task(task)
        if errors:
            logger.error(f"⛔ 任务校验失败: {'；'.join(errors)}")
            return {"ok": False, "error": "；".join(errors)}

        self._stop_flag.clear()
        self.state = TaskState(
            running=True,
            task_id=task.get("id", ""),
            task_name=task.get("name", "未命名"),
            total=len(steps),
            current=0,
            started_at=datetime.now().strftime("%H:%M:%S"),
        )

        logger.info(f"▶️ 开始执行任务: {self.state.task_name} ({self.state.total} 步骤)")

        self._ctx = {"responses": {}}  # 任务级变量上下文（存 HTTP 响应等）
        self._exec_blocks(node, steps, self._ctx)

        # 清理：确保速度停止
        try:
            node._do_velocity(0.0, 0.0, 0.0)
        except Exception:
            pass

        self.state.running = False
        logger.info(f"✅ 任务结束: {self.state.task_name}")

    # ── 块执行 ─────────────────────────────────
    def _exec_blocks(self, node, blocks: list, ctx: dict, update_state: bool = True):
        """顺序执行一组块；块可能是普通步骤 / parallel / branch"""
        for i, block in enumerate(blocks):
            if self._stop_flag.is_set():
                logger.info("⏹ 任务被中断")
                break
            if update_state:
                self.state.current = i + 1
                self.state.current_step = block

            btype = block.get("type", "?")
            logger.info(f"  [{i + 1}/{len(blocks)}] {btype}")
            try:
                if btype == "parallel":
                    self._exec_parallel(node, block, ctx)
                elif btype == "branch":
                    self._exec_branch(node, block, ctx)
                else:
                    execute_step(node, block, ctx)
                    delay = block.get("delay", 0) or 0
                    if delay > 0 and not self._stop_flag.is_set():
                        node._sleep(delay)
            except StepAbort as e:
                logger.error(f"🛑 块 [{i + 1}] 中止任务: {e}")
                break
            except Exception as e:
                logger.error(f"❌ 块 [{i + 1}] 异常: {e}")

    def _exec_parallel(self, node, block: dict, ctx: dict):
        """并行组：每个分支一个线程，全部 join 完成后继续。

        分支线程只调用线程安全的 node 方法（service 走 future 轮询、
        velocity 元组原子替换、等待用 sleep 轮询），executor 在独立线程
        spin，不受影响。停止时共享 stop 标志，分支在当前步骤边界退出。
        """
        branches = block.get("branches") or []
        if not branches:
            return
        logger.info(f"  ⚡ 并行执行 {len(branches)} 个分支: {block.get('name', '')}")
        threads = []
        for b in branches:
            bsteps = b.get("steps") or []
            t = threading.Thread(
                target=self._exec_blocks, args=(node, bsteps, ctx), kwargs={"update_state": False},
                daemon=True,
            )
            threads.append(t)
        for t in threads:
            t.start()
        for t in threads:
            t.join()  # 分支内步骤会自行检查 stop 标志，在步骤边界退出

    def _exec_branch(self, node, block: dict, ctx: dict):
        """分支块：条件为真走 then，否则走 else"""
        cond = str(block.get("cond", "") or "")
        take_then = eval_cond(cond, ctx)
        logger.info(f"  🔀 分支: {cond!r} → {'是' if take_then else '否'}")
        sub = (block.get("then") or []) if take_then else (block.get("else") or [])
        if sub:
            self._exec_blocks(node, sub, ctx, update_state=False)

    def stop(self):
        """停止执行"""
        self._stop_flag.set()
        self.state.running = False
        logger.info("⏹ 收到停止指令")

    def get_status(self) -> dict:
        """获取当前状态"""
        return {
            "running": self.state.running,
            "task_id": self.state.task_id,
            "task_name": self.state.task_name,
            "total": self.state.total,
            "current": self.state.current,
            "current_step": self.state.current_step,
            "started_at": self.state.started_at,
            "progress": round(self.state.current / max(self.state.total, 1) * 100, 1),
        }


# 全局单例
_task_engine: TaskEngine | None = None


def get_engine() -> TaskEngine:
    global _task_engine
    if _task_engine is None:
        _task_engine = TaskEngine()
    return _task_engine
