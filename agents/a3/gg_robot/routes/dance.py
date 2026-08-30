"""舞蹈播放（A3 独有）— POST /api/dance + GET /api/dances 清单"""

from fastapi import APIRouter

from .. import motions_data, rpc
from ..schemas import DanceRequest

router = APIRouter()


@router.post("/api/dance")
async def dance(req: DanceRequest):
    """播放舞蹈（Start/Pause/Stop）。⚠️ 保持机器人周围两米无障碍。"""
    try:
        r = rpc.dance(req.command, req.path or "", req.session_id)
        return {"ok": True, "session_id": r.get("session_id", "")}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.get("/api/dances")
async def dances(refresh: bool = False):
    return {"dances": motions_data.get_skills(force=refresh)}
