"""GET /api/cameras + POST /api/camera/switch — 相机切换"""

from fastapi import APIRouter
from pydantic import BaseModel

router = APIRouter()


class CameraSwitchRequest(BaseModel):
    camera_id: str


@router.get("/api/cameras")
async def list_cameras():
    """列出所有可用相机及其状态"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"cameras": []}
    future = node_mod._cmd_queue.put("camera_list")
    return {"cameras": future.result(timeout=3.0)}


@router.post("/api/camera/switch")
async def switch_camera(req: CameraSwitchRequest):
    """切换到指定相机"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put("camera_switch", camera_id=req.camera_id)
    return future.result(timeout=5.0)


@router.get("/api/camera/active")
async def active_camera():
    """获取当前活跃相机"""
    from .. import node as node_mod
    if node_mod._node is None:
        return {"camera_id": ""}
    return {"camera_id": node_mod._node.get_active_camera()}
