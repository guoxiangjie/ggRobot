"""自由任务（项目）REST API

GET    /api/projects                       列出项目
GET    /api/projects/{pid}                 项目详情
POST   /api/projects                       新建/更新项目
DELETE /api/projects/{pid}                 删除项目
POST   /api/projects/{pid}/nodes/{nid}/run 执行单个节点
POST   /api/projects/stop                  停止当前节点
GET    /api/projects/status                当前节点执行状态
"""

from fastapi import APIRouter
from fastapi.responses import JSONResponse
from pydantic import BaseModel

router = APIRouter()


class ProjectSaveRequest(BaseModel):
    id: str | None = None
    name: str = "未命名项目"
    desc: str = ""
    icon: str = "📂"
    nodes: list[dict] = []


# ── 项目 CRUD ──

@router.get("/api/projects")
async def list_projects():
    from ..project.store import list_projects
    return {"projects": list_projects()}


@router.get("/api/projects/{pid}")
async def get_project(pid: str):
    from ..project.store import get_project
    p = get_project(pid)
    if p is None:
        return JSONResponse({"error": "项目不存在"}, status_code=404)
    return p


@router.post("/api/projects")
async def save_project(req: ProjectSaveRequest):
    from ..project.store import save_project
    return save_project(req.model_dump())


@router.delete("/api/projects/{pid}")
async def delete_project(pid: str):
    from ..project.store import delete_project
    return {"ok": delete_project(pid)}


# ── 节点执行 ──

@router.post("/api/projects/{pid}/nodes/{nid}/run")
async def run_node(pid: str, nid: str):
    """执行项目里的单个节点（走命令队列，复用 steps.execute_step）"""
    from ..project.store import get_project
    from .. import node as node_mod

    p = get_project(pid)
    if p is None:
        return JSONResponse({"ok": False, "error": "项目不存在"}, status_code=404)
    node = next((n for n in p.get("nodes", []) if n.get("id") == nid), None)
    if node is None:
        return JSONResponse({"ok": False, "error": "节点不存在"}, status_code=404)
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "命令队列未就绪"}

    # 防重复：同一节点正在跑则拒绝
    n = node_mod._node
    if n is not None and getattr(n, "_node_running_id", "") == nid:
        return {"ok": False, "error": "该节点正在执行"}

    future = node_mod._cmd_queue.put("run_node", step=node)
    return future.result(timeout=60.0)


@router.post("/api/projects/stop")
async def stop_node():
    """停止当前节点执行（设停止标志 + 停车，针对长动作 velocity）"""
    from .. import node as node_mod
    n = node_mod._node
    if n is not None:
        n._node_stop_flag = True
        try:
            n._do_velocity(0.0, 0.0, 0.0)
        except Exception:
            pass
    return {"ok": True}


@router.get("/api/projects/status")
async def project_status():
    from .. import node as node_mod
    n = node_mod._node
    running_id = getattr(n, "_node_running_id", "") if n else ""
    return {"running": running_id != "", "node_id": running_id}
