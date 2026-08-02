"""灵创动作资源 — 查询列表 + 播放"""

from fastapi import APIRouter
from pydantic import BaseModel

router = APIRouter()


class PlayResourceRequest(BaseModel):
    resource_key: str
    version: str = ""
    resource_type: str = ""   # 可空：后端按 resource_key 含 onnx 自动判断 BODY/ARM


@router.get("/api/resources")
async def list_resources():
    """列出机器人所有灵创动作资源（来自 GetRobotResources）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化", "resources": []}
    future = node_mod._cmd_queue.put("resources")
    return future.result(timeout=10.0)


@router.post("/api/resources/play")
async def play_resource(req: PlayResourceRequest):
    """播放指定灵创动作资源（ExecuteActionResource）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put(
        "play_resource",
        resource_key=req.resource_key,
        version=req.version,
        resource_type=req.resource_type,
    )
    return future.result(timeout=15.0)
