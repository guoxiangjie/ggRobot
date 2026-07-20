"""POST /api/tts — 语音播报"""

from fastapi import APIRouter
from ..schemas import TtsRequest, TtsResponse

router = APIRouter()


@router.post("/api/tts", response_model=TtsResponse)
async def tts(req: TtsRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return TtsResponse(ok=False)

    future = node_mod._cmd_queue.put("tts", text=req.text)
    ok = future.result(timeout=10.0)
    return TtsResponse(ok=ok)
