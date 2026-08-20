"""hub WS — 多机状态聚合推送（5s 轮询各 agent，聚合摘要推给前端）"""

import asyncio
import json
import logging

from fastapi import APIRouter, WebSocket, WebSocketDisconnect

from ..discovery import refresh_all

logger = logging.getLogger(__name__)

router = APIRouter()

POLL_INTERVAL = 5.0

_subscribers: set[WebSocket] = set()
_task: asyncio.Task | None = None


async def _broadcaster():
    """周期聚合 → 推送所有 hub 订阅者"""
    while True:
        await asyncio.sleep(POLL_INTERVAL)
        if not _subscribers:
            continue
        try:
            summaries = await refresh_all()
            from ..choreo.runner import runner as choreo_runner
            payload = json.dumps(
                {"type": "hub", "robots": summaries,
                 "choreo": choreo_runner.active_runs()},
                ensure_ascii=False)
            dead = []
            for ws in list(_subscribers):
                try:
                    await ws.send_text(payload)
                except Exception:
                    dead.append(ws)
            for ws in dead:
                _subscribers.discard(ws)
        except Exception as e:
            logger.error(f"hub 聚合异常: {e}")


@router.websocket("/hub")
async def hub(ws: WebSocket):
    global _task
    await ws.accept()
    _subscribers.add(ws)
    if _task is None or _task.done():
        _task = asyncio.create_task(_broadcaster())
    # 连上立即推一次全量
    try:
        summaries = await refresh_all()
        from ..choreo.runner import runner as choreo_runner
        await ws.send_text(json.dumps(
            {"type": "hub", "robots": summaries,
             "choreo": choreo_runner.active_runs()},
            ensure_ascii=False))
    except Exception:
        pass
    logger.info(f"🛰 hub 订阅者 +1（共 {len(_subscribers)}）")
    try:
        while True:
            # 只收 ping；客户端也可发 {"type":"refresh"} 主动触发
            raw = await ws.receive_text()
            try:
                msg = json.loads(raw)
            except json.JSONDecodeError:
                continue
            if msg.get("type") == "ping":
                await ws.send_text('{"type":"pong"}')
            elif msg.get("type") == "refresh":
                summaries = await refresh_all()
                await ws.send_text(json.dumps({"type": "hub", "robots": summaries}, ensure_ascii=False))
    except WebSocketDisconnect:
        pass
    finally:
        _subscribers.discard(ws)
