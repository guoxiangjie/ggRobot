"""POST /api/volume GET /api/volume — 音量控制"""

from fastapi import APIRouter, Query

router = APIRouter()


@router.post("/api/volume")
async def set_volume(volume: int = Query(..., ge=0, le=100)):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"volume": volume}
    future = node_mod._cmd_queue.put("set_volume", volume=volume)
    return future.result(timeout=5.0)


@router.get("/api/volume")
async def get_volume():
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"volume": 0}
    future = node_mod._cmd_queue.put("get_volume")
    return future.result(timeout=5.0)


@router.post("/api/mute")
async def set_mute(mute: bool = Query(...)):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"is_mute": mute}
    future = node_mod._cmd_queue.put("set_mute", is_mute=mute)
    return future.result(timeout=5.0)


@router.get("/api/mute")
async def get_mute():
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"is_mute": False}
    future = node_mod._cmd_queue.put("get_mute")
    return future.result(timeout=5.0)
