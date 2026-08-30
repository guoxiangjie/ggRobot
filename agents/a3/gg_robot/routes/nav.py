"""导航（A3 独有）— 到点/坐标导航 + 暂停/恢复/取消 + 状态查询

前置（docs 7.9.1）：重定位成功 + MC 在 MOTION 模式 + map_id 与当前地图一致。
"""

import logging

from fastapi import APIRouter, Query

from .. import rpc
from ..schemas import NavRequest

logger = logging.getLogger(__name__)
router = APIRouter()


@router.post("/api/nav/goto")
async def nav_goto(req: NavRequest):
    """下发导航任务。返回 task_id（后续控制/查询用）。"""
    kw = {}
    if req.target_id is not None:
        kw["target_id"] = req.target_id
    if req.x is not None and req.y is not None:
        kw["pose"] = {"position": {"x": req.x, "y": req.y},
                      "angle": req.angle if req.angle is not None else 0.0}
    try:
        r = rpc.navi(req.kind, req.map_id, **kw)
        return {"ok": "SUCCESS" in str(r.get("state", "")), "task_id": r.get("task_id")}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.post("/api/nav/control")
async def nav_control(op: str = Query(..., description="pause/resume/cancel"), task_id: int = 0):
    method = {"pause": "ActionPause", "resume": "ActionResume", "cancel": "ActionCancel"}.get(op)
    if not method:
        return {"ok": False, "error": f"未知操作: {op}"}
    try:
        r = rpc.navi_control(method, task_id)
        return {"ok": "SUCCESS" in str(r.get("state", "")), "task_id": r.get("task_id")}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.get("/api/nav/state")
async def nav_state(task_id: int = 0):
    """任务状态（task_id=0 → 最近一次任务）"""
    try:
        r = rpc.navi_state(task_id)
        return {"ok": True, "task_id": r.get("task_id"),
                "state": str(r.get("state", "")).replace("PncServiceState_", "")}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}
