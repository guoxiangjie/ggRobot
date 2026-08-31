"""POST /api/mode — Action 状态机切换（MOTION/PD_STAND/DAMPING…字符串）"""

from fastapi import APIRouter, Query

router = APIRouter()

_ALLOWED = {"PASSIVE", "DAMPING", "PD_STAND", "MOTION", "SIT_DOWN", "STAND_UP",
            "LIE_DOWN", "GET_UP", "PACKAGE_LIE_DOWN", "PACKAGE_GET_UP", "AVARAR"}


@router.post("/api/mode")
async def set_mode(mode: str = Query(..., description="Action 名（GetAvailableActions 的 ext_action）")):
    mode = mode.upper()
    if mode not in _ALLOWED:
        return {"ok": False, "error": f"非法 action: {mode}"}
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False}
    fut = node_mod._cmd_queue.put("mode", action_name=mode)
    return fut.result(timeout=5.0)


@router.get("/api/mode")
async def get_mode():
    from .. import rpc
    try:
        r = rpc.action_get()
        info = r.get("info", {})
        return {"ok": True, "action": str(info.get("current_action", "")),
                "ext_action": str(info.get("ext_action", "")),
                "status": str(info.get("status", ""))}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}
