"""POST /api/tts — 语音播报（trace_id 可查状态；wait=true 阻塞到播完）"""

from fastapi import APIRouter

from ..schemas import TtsRequest, TtsResponse

router = APIRouter()


@router.post("/api/tts", response_model=TtsResponse)
async def tts(req: TtsRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return TtsResponse(ok=False)
    fut = node_mod._cmd_queue.put("tts", text=req.text, interrupt=req.is_interrupted, wait=req.wait)
    r = fut.result(timeout=60.0)
    return TtsResponse(ok=bool(r.get("ok")), trace_id=r.get("trace_id"))
