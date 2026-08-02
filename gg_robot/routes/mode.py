"""POST /api/mode — 运动模式切换（action_desc 字符串 或 action_value 数字 ID）

⚠️ 字符串 action_desc 后端只认 PASSIVE/DAMPING/JOINT/STAND/LOCOMOTION 系列；
SIT_DOWN_DEFAULT(2000)/ZERO_TORQUE_DEFAULT(4)/STAND_BODY_CONTROL(201) 等
必须传 value 数字 ID（见 docs/api_reference.md McAction.value 表）。
"""

from fastapi import APIRouter, Query

router = APIRouter()


@router.post("/api/mode")
async def set_mode(
    mode: str = Query(..., description="action_desc: STAND_DEFAULT/LOCOMOTION_DEFAULT/DAMPING_DEFAULT/JOINT_DEFAULT/PASSIVE_DEFAULT"),
    value: int | None = Query(None, description="运动模式数字 ID（可选，优先）：4=ZERO_TORQUE 2000=SIT_DOWN 201=STAND_BODY_CONTROL 等"),
):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False}
    future = node_mod._cmd_queue.put("mode", action_desc=mode, action_value=value or 0)
    return future.result(timeout=5.0)
