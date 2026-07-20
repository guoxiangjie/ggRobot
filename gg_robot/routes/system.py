"""GET /api/system + GET /api/status"""

from fastapi import APIRouter

router = APIRouter()


@router.get("/api/system")
async def system():
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"action": None, "system": None}
    future = node_mod._cmd_queue.put("system")
    return future.result(timeout=5.0)


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
