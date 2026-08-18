"""GET /api/system + GET /api/status + POST /api/system/migrate（开发者模式）"""

from fastapi import APIRouter
from pydantic import BaseModel

router = APIRouter()

# 开发者模式合法目标态白名单（文档 5.6；警告：勿使用未提及的系统模式）
_MIGRATE_STATES = {"Ready", "Develop_Audio_Linux", "Develop_Audio_ROS", "Develop_Nav", "Develop_MC"}


class MigrateRequest(BaseModel):
    state: str


@router.get("/api/system")
async def system():
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"action": None, "system": None}
    future = node_mod._cmd_queue.put("system")
    return future.result(timeout=5.0)


@router.post("/api/system/migrate")
async def migrate_system_state(req: MigrateRequest):
    """切换系统状态/开发者模式（MigrateSystemState），后端阻塞到迁移完成（最多 ~15s）。"""
    if req.state not in _MIGRATE_STATES:
        return {"ok": False, "message": f"非法目标态: {req.state}（仅允许 {sorted(_MIGRATE_STATES)}）"}
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "message": "后端未初始化"}
    future = node_mod._cmd_queue.put("migrate_system_state", state=req.state)
    return future.result(timeout=25.0)


@router.get("/api/status")
async def status():
    from .. import node as node_mod
    if node_mod._node is None:
        return {"battery": None, "arms": [], "imu": None}
    return {
        "battery": node_mod._node.battery if node_mod._node.battery else None,
        "arms": node_mod._node.arm_joints,
        "imu": node_mod._node.imu if node_mod._node.imu else None,
    }
