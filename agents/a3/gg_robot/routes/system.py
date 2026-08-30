"""GET /api/system（Action+告警）+ GET /api/status（BMS/关节/急停缓存）"""

from fastapi import APIRouter

router = APIRouter()


@router.get("/api/system")
async def system():
    from .. import rpc
    out: dict = {"action": None, "alerts_count": 0, "alerts": []}
    try:
        info = rpc.action_get().get("info", {})
        out["action"] = str(info.get("current_action", "")).replace("MotionControlAction_", "")
        out["action_status"] = str(info.get("status", "")).replace("MotionControlActionStatus_", "")
    except Exception as e:  # noqa: BLE001
        out["action_error"] = str(e)
    try:
        alerts = rpc.alerts().get("data", {}).get("alerts", [])
        active = [a for a in alerts if "ACTIVE" in str(a.get("state", ""))]
        out["alerts_count"] = len(active)
        out["alerts"] = [
            {"code": a.get("alert_code"), "level": str(a.get("level", "")).replace("AlertLevel_", ""),
             "text": (a.get("alert_text") or {}).get("zh_CN", a.get("description", ""))}
            for a in active[:10]
        ]
    except Exception as e:  # noqa: BLE001
        out["alerts_error"] = str(e)
    return out


@router.get("/api/status")
async def status():
    from .. import node as node_mod
    n = node_mod._node
    if n is None:
        return {"battery": None, "arms": [], "imu": None, "emergency": None}
    return {"battery": n.battery, "arms": n.arm_joints, "imu": n.imu, "emergency": n.emergency}
