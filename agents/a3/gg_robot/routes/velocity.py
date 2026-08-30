"""POST /api/velocity — 速度控制（m/s 入参，node 内换算 A3 比例制）"""

from fastapi import APIRouter

from ..schemas import VelocityRequest, VelocityResponse

router = APIRouter()


@router.post("/api/velocity", response_model=VelocityResponse)
async def velocity(req: VelocityRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return VelocityResponse(ok=False)
    fut = node_mod._cmd_queue.put("velocity",
                                  forward=req.forward, lateral=req.lateral, angular=req.angular)
    fut.result(timeout=2.0)
    return VelocityResponse(ok=True)
