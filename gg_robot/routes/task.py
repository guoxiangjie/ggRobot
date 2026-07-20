"""任务编排 REST API

GET    /api/tasks          列出所有任务
GET    /api/tasks/{id}     获取任务详情
POST   /api/tasks          新建/更新任务
DELETE /api/tasks/{id}     删除任务
POST   /api/tasks/{id}/run 执行任务
POST   /api/tasks/{id}/stop 停止执行
GET    /api/tasks/status   当前执行状态
GET    /api/capabilities   能力列表
"""

from fastapi import APIRouter
from fastapi.responses import JSONResponse
from pydantic import BaseModel

router = APIRouter()


class TaskSaveRequest(BaseModel):
    id: str | None = None
    name: str = "未命名任务"
    desc: str = ""
    steps: list[dict] = []


# ── 任务 CRUD ──

@router.get("/api/tasks")
async def list_tasks():
    from ..task.store import list_tasks
    return {"tasks": list_tasks()}


@router.get("/api/tasks/{task_id}")
async def get_task(task_id: str):
    from ..task.store import get_task
    task = get_task(task_id)
    if task is None:
        return JSONResponse({"error": "任务不存在"}, status_code=404)
    return task


@router.post("/api/tasks")
async def save_task(req: TaskSaveRequest):
    from ..task.store import save_task
    data = req.model_dump()
    return save_task(data)


@router.delete("/api/tasks/{task_id}")
async def delete_task(task_id: str):
    from ..task.store import delete_task
    ok = delete_task(task_id)
    return {"ok": ok}


# ── 任务执行 ──

@router.post("/api/tasks/{task_id}/run")
async def run_task(task_id: str):
    from ..task.store import get_task
    from ..task.engine import get_engine
    from .. import node as node_mod

    task = get_task(task_id)
    if task is None:
        return JSONResponse({"ok": False, "error": "任务不存在"}, status_code=404)
    if node_mod._node is None:
        return {"ok": False, "error": "后端未初始化"}
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "命令队列未就绪"}

    engine = get_engine()
    if engine.state.running:
        return {"ok": False, "error": "已有任务在运行，请先停止"}

    # 通过命令队列触发（确保在 rclpy 线程执行）
    future = node_mod._cmd_queue.put("run_task", task=task, engine=engine)
    return future.result(timeout=3.0)


@router.post("/api/tasks/stop")
async def stop_task():
    from ..task.engine import get_engine
    engine = get_engine()
    engine.stop()
    return {"ok": True}


@router.get("/api/tasks/status")
async def task_status():
    from ..task.engine import get_engine
    engine = get_engine()
    return engine.get_status()


# ── 能力列表 ──

@router.get("/api/capabilities")
async def capabilities():
    from ..task.steps import CAPABILITIES
    return {"capabilities": CAPABILITIES}
