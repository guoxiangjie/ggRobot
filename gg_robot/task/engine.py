"""任务执行引擎 — 顺序执行步骤，支持中断

引擎在 rclpy 线程中运行，通过命令队列触发。
"""

import logging
import threading
from dataclasses import dataclass, field
from datetime import datetime

from .steps import execute_step, StepAbort

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

        for i, step in enumerate(steps):
            if self._stop_flag.is_set():
                logger.info("⏹ 任务被中断")
                break

            self.state.current = i + 1
            self.state.current_step = step
            step_type = step.get("type", "?")
            delay = step.get("delay", 0)
            logger.info(f"  [{i+1}/{self.state.total}] {step_type}")

            try:
                execute_step(node, step, self._ctx)
            except StepAbort as e:
                logger.error(f"🛑 步骤 [{i+1}] 中止任务: {e}")
                break
            except Exception as e:
                logger.error(f"❌ 步骤 [{i+1}] 异常: {e}")

            # 步骤间延时
            if delay > 0 and not self._stop_flag.is_set():
                node._sleep(delay)

        # 清理：确保速度停止
        try:
            node._do_velocity(0.0, 0.0, 0.0)
        except Exception:
            pass

        self.state.running = False
        logger.info(f"✅ 任务结束: {self.state.task_name}")

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
