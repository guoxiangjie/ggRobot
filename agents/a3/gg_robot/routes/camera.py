"""相机 — GET /api/cameras 清单 + POST /api/camera/switch 切换（帧走 WS cam.*）"""

from fastapi import APIRouter
from pydantic import BaseModel

router = APIRouter()


class SwitchRequest(BaseModel):
    camera_id: str


def _node():
    from .. import node as node_mod
    return node_mod._node


@router.get("/api/cameras")
async def cameras():
    n = _node()
    if n is None:
        return {"cameras": []}
    return {"cameras": n.list_cameras(), "active": n._active_camera}


@router.post("/api/camera/switch")
async def switch_camera(req: SwitchRequest):
    n = _node()
    if n is None:
        return {"ok": False, "error": "后端未初始化"}
    return n.switch_camera(req.camera_id)
