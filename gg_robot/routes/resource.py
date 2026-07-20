"""GET /api/resources — 查询机器人灵创动作资源列表"""

from fastapi import APIRouter

router = APIRouter()


@router.get("/api/resources")
async def list_resources():
    """列出机器人所有灵创动作资源（来自 GetRobotResources）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化", "resources": []}
    future = node_mod._cmd_queue.put("resources")
    return future.result(timeout=10.0)
