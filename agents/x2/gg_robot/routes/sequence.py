"""POST /api/sequence — 执行动作序列"""

from fastapi import APIRouter

router = APIRouter()


@router.post("/api/sequence")
async def run_sequence():
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}

    future = node_mod._cmd_queue.put("action_sequence")
    return future.result(timeout=5.0)
