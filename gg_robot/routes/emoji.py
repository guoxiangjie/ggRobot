"""POST /api/emoji — 表情控制"""

from fastapi import APIRouter
from pydantic import BaseModel, Field

router = APIRouter()


class EmojiRequest(BaseModel):
    emotion_id: int = Field(..., ge=1, le=255)
    mode: int = Field(default=1, ge=1, le=2)


@router.post("/api/emoji")
async def emoji(req: EmojiRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "message": "后端未初始化"}

    future = node_mod._cmd_queue.put("emoji", emotion_id=req.emotion_id, mode=req.mode)
    return future.result(timeout=5.0)
