"""音量 — GET/POST /api/volume + /api/mute（A3 硬上限 70：超限钳制，保护扬声器）"""

from fastapi import APIRouter, Query

from .. import rpc

router = APIRouter()


@router.post("/api/volume")
async def set_volume(volume: int = Query(..., ge=0, le=100)):
    v = min(volume, 70)   # ⚠️ 官方上限 70，超了烧扬声器
    try:
        rpc.volume_set(v)
        return {"volume": v}
    except Exception as e:  # noqa: BLE001
        return {"volume": v, "error": str(e)}


@router.get("/api/volume")
async def get_volume():
    try:
        r = rpc.volume_get()
        return {"volume": r.get("audio_volume", 0), "is_mute": bool(r.get("is_mute", False)),
                "speaker_type": str(r.get("type", ""))}
    except Exception as e:  # noqa: BLE001
        return {"volume": 0, "error": str(e)}


@router.post("/api/mute")
async def set_mute(mute: bool = Query(...)):
    try:
        r = rpc.volume_get()
        rpc.volume_set(int(r.get("audio_volume", 30)), mute=mute)
        return {"is_mute": mute}
    except Exception as e:  # noqa: BLE001
        return {"is_mute": mute, "error": str(e)}
