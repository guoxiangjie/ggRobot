"""多机编排 REST API（agent 侧）— 预分发 / 广播开始 / 停止 / 状态

协议（docs/choreo-design.md §3）：
    POST /api/choreo/load     {run_id, steps}  预分发本机轨道
    POST /api/choreo/start    {run_id, start_ts}  广播开始（绝对墙钟时刻）
    POST /api/choreo/stop     {run_id}         停止
    GET  /api/choreo/status?run_id=…           状态查询
POST 控制类走中间件会话锁（与其它控制操作一致）；WS 事件见 choreo.py。
"""

import asyncio
import logging

from fastapi import APIRouter
from pydantic import BaseModel

logger = logging.getLogger(__name__)
router = APIRouter()


class ChoreoLoadRequest(BaseModel):
    run_id: str
    steps: list[dict] = []


class ChoreoStartRequest(BaseModel):
    run_id: str
    start_ts: float


class ChoreoStopRequest(BaseModel):
    run_id: str


@router.post("/api/choreo/load")
async def choreo_load(req: ChoreoLoadRequest):
    from ..choreo import runner
    return runner.load(req.run_id, req.steps)


@router.post("/api/choreo/start")
async def choreo_start(req: ChoreoStartRequest):
    from ..choreo import runner
    return runner.start(req.run_id, req.start_ts, asyncio.get_running_loop())


@router.post("/api/choreo/stop")
async def choreo_stop(req: ChoreoStopRequest):
    from ..choreo import runner
    return runner.stop(req.run_id)


@router.get("/api/choreo/status")
async def choreo_status(run_id: str):
    from ..choreo import runner
    return runner.status(run_id)
