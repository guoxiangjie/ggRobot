"""动作播放 — POST /api/motion（播放/暂停/复位）+ GET /api/motions 清单"""

from fastapi import APIRouter

from ..schemas import MotionRequest, MotionResponse
from .. import motions_data

router = APIRouter()


@router.post("/api/motion", response_model=MotionResponse)
async def motion(req: MotionRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return MotionResponse(ok=False, error="后端未初始化")
    fut = node_mod._cmd_queue.put("motion", motion_id=req.motion_id,
                                  duration_ms=req.duration_ms,
                                  cmd_end=req.cmd_end,
                                  pause=req.pause, reset=req.reset, repeat=req.repeat)
    r = fut.result(timeout=10.0)
    return MotionResponse(ok=bool(r.get("ok")), error=r.get("error"))


@router.post("/api/motion/stop")
async def motion_stop():
    """停止当前动作（cmd_reset）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False}
    fut = node_mod._cmd_queue.put("motion", motion_id="", reset=True)
    return fut.result(timeout=10.0)


@router.get("/api/motions")
async def list_motions(refresh: bool = False):
    """动作清单（资源服务动态；refresh=true 强制刷新缓存）"""
    return {"motions": motions_data.get_motions(force=refresh)}
