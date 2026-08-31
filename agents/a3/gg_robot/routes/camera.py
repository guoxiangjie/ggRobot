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


@router.get("/api/camera/shot")
async def camera_shot():
    """单张截图（PNG→JPEG base64；调试/缩略图用，正式流走 WS cam.*）"""
    import base64
    n = _node()
    if n is None:
        return {"ok": False, "error": "后端未初始化"}
    import asyncio
    frame = await asyncio.to_thread(n.shot_jpeg)
    if frame is None:
        return {"ok": False, "error": "截图失败"}
    return {"ok": True, "jpeg_b64": base64.b64encode(frame).decode(), "size": len(frame)}
