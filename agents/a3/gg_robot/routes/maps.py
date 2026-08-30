"""地图管理（A3 版，RPC 数据源）— 对齐 X2 /api/slam/* 路由形态（前端 Maps 页复用）

差异：X2 读 map.db/文件系统；A3 走 MappingService/LocalizationService RPC（ADU）。
"""

from fastapi import APIRouter
from pydantic import BaseModel

from .. import rpc

router = APIRouter()


class StopMappingRequest(BaseModel):
    map_name: str = "ggrobot-地图"


class RelocalizeRequest(BaseModel):
    map_id: str
    x: float = 0.0
    y: float = 0.0


@router.post("/api/slam/mapping/start")
async def start_mapping():
    try:
        rpc.mapping_start()
        from .. import node as node_mod
        if node_mod._node is not None:
            node_mod._node.slam_mapping = True   # 开启建图可视化轮询
        return {"ok": True}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.post("/api/slam/mapping/stop")
async def stop_mapping(req: StopMappingRequest):
    try:
        r = rpc.mapping_stop(save=True, map_name=req.map_name)
        from .. import node as node_mod
        if node_mod._node is not None:
            node_mod._node.slam_mapping = False
        return {"ok": True, "map_id": (r.get("data") or {}).get("map_id", "")}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.get("/api/slam/maps")
async def list_maps():
    try:
        data = rpc.map_list().get("data", {})
        maps = [{"map_id": str(m.get("map_id", "")), "map_name": m.get("map_name", "")}
                for m in data.get("map_lists", [])]
        return {"maps": maps}
    except Exception as e:  # noqa: BLE001
        return {"maps": [], "error": str(e)}


@router.get("/api/slam/map/current")
async def current_map():
    try:
        return {"ok": True, "map_id": str(rpc.map_current().get("data", {}).get("map_id", ""))}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.get("/api/slam/map/{map_id}")
async def get_map(map_id: str):
    """取地图（png base64 + map_info + 拓扑点）"""
    try:
        r = rpc.map_2d(map_id).get("data", {})
        topo = rpc.map_topo(map_id).get("data", {})
        return {
            "ok": True,
            "map": {
                "map_id": r.get("map_id"), "map_name": r.get("map_name"),
                "width": r.get("width"), "height": r.get("height"),
                "resolution": r.get("resolution"),
                "origin_x": r.get("origin_x"), "origin_y": r.get("origin_y"),
                "png_b64": r.get("map_data", ""),
            },
            "topo": topo,
        }
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.post("/api/slam/relocalize")
async def relocalize(req: RelocalizeRequest):
    try:
        r = rpc.relocalize("relocalization", map_id=req.map_id, x=req.x, y=req.y)
        return {"ok": True, "raw": r}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.get("/api/slam/realtime")
async def realtime():
    """实时建图数据（cur_pos + lidar_points + trajectory + png）——建图工作台数据源"""
    try:
        return {"ok": True, "data": rpc.mapping_realtime().get("data", {})}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}
