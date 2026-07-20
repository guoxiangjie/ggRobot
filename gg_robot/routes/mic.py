"""POST /api/mode — 运动模式切换"""

from fastapi import APIRouter, Query

router = APIRouter()


@router.post("/api/mode")
async def set_mode(mode: str = Query(..., description="action_desc: STAND_DEFAULT/LOCOMOTION_DEFAULT/DAMPING_DEFAULT/JOINT_DEFAULT/PASSIVE_DEFAULT")):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False}
    future = node_mod._cmd_queue.put("mode", action_desc=mode)
    return future.result(timeout=5.0)
