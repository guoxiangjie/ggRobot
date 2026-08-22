"""POST /api/motion — 预设动作；POST /api/motion/timed — 发+等完成+返回真实耗时（动作时长实测用）"""

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


@router.post("/api/motion/timed")
async def motion_timed(req: MotionRequest):
    """发动作 → 轮询 GetMcAction 到完成 → 返回真实耗时（时长实测工具用）
    ok=动作受理；tracked=状态轮询是否精确跟踪到；seconds=实测时长（未跟踪到为 null）"""
    import time as _t
    from .. import node as node_mod
    n = node_mod._node
    if n is None or node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put("motion", area=req.area, motion_id=req.motion_id)
    result = future.result(timeout=10.0)
    if not result.get("ok"):
        return {"ok": False, "error": result.get("error", "动作下发失败")}
    t0 = _t.time()
    tracked = n.wait_motion_done(timeout=45.0, grace=1.5)
    return {"ok": True, "tracked": tracked,
            "seconds": round(_t.time() - t0, 2) if tracked else None}
