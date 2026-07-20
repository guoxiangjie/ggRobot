"""POST /api/motion — 预设动作"""

from fastapi import APIRouter
from ..schemas import MotionRequest, MotionResponse

router = APIRouter()


@router.post("/api/motion", response_model=MotionResponse)
async def motion(req: MotionRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return MotionResponse(ok=False, error="后端未初始化")

    future = node_mod._cmd_queue.put("motion", area=req.area, motion_id=req.motion_id)
    result = future.result(timeout=10.0)
    return MotionResponse(**result)
