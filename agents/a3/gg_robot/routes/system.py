"""GET /api/system（Action+告警）+ GET /api/status（BMS/关节/急停缓存）

system 有 5s 结果缓存：sidecar hub 每 5s 轮询此端点，直通 RPC 会以 0.2Hz 持续
打 MDU（文档限频红线）——缓存后多客户端并发轮询也只有单次穿透。"""

import time

from fastapi import APIRouter

router = APIRouter()

_cache: dict = {"ts": 0.0, "data": None}


@router.get("/api/system")
async def system():
    from .. import rpc
    if _cache["data"] is not None and time.time() - _cache["ts"] < 5.0:
        return _cache["data"]
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
    _cache["ts"], _cache["data"] = time.time(), out
    return out


@router.get("/api/status")
async def status():
    from .. import node as node_mod
    n = node_mod._node
    if n is None:
        return {"battery": None, "arms": [], "imu": None, "emergency": None}
    return {"battery": n.battery, "arms": n.arm_joints, "imu": n.imu, "emergency": n.emergency}
