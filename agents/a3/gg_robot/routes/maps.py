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
    """取地图 — 响应字段对齐 X2（Maps.tsx 零改动）：map_base64/map_info/navi_points(像素 u,v)
    路径参数兼容 map_id 与 map_name（前端 X2 传 name，A3 列表两者都有）"""
    try:
        if not map_id.isdigit():
            resolved = next((m.get("map_id") for m in
                             (rpc.map_list().get("data", {}).get("map_lists") or [])
                             if m.get("map_name") == map_id), map_id)
            map_id = str(resolved)
        r = rpc.map_2d(map_id).get("data", {})
        topo = rpc.map_topo(map_id).get("data", {})
        navi = [{"x": p.get("pixel_pose", {}).get("position", {}).get("u"),
                 "y": p.get("pixel_pose", {}).get("position", {}).get("v")}
                for p in topo.get("points", [])
                if p.get("pixel_pose", {}).get("position")]
        global _last_map_meta
        _last_map_meta = {"resolution": r.get("resolution"),
                          "origin_x": r.get("origin_x"), "origin_y": r.get("origin_y")}
        return {
            "ok": True,
            "map_id": r.get("map_id"),
            "map_base64": r.get("map_data", ""),
            "map_info": {"width": r.get("width"), "height": r.get("height")},
            "navi_points": navi,
            "meta": {   # A3 附加（建图/重定位换算用）
                "resolution": r.get("resolution"),
                "origin_x": r.get("origin_x"), "origin_y": r.get("origin_y"),
                "topo_points": topo.get("points", []),
            },
        }
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.post("/api/slam/relocalize")
async def relocalize(req: RelocalizeRequest):
    """重定位（X2 兼容入口）：切工作地图 → 全局重定位（机器人自主找位）"""
    try:
        rpc.set_working_map(req.map_id)
        r = rpc.relocalize_global(req.map_id)
        return {"ok": True, "raw": r}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.post("/api/slam/map/current")
async def set_current_map(req: RelocalizeRequest):
    """仅切换当前工作地图（不触发重定位）"""
    try:
        rpc.set_working_map(req.map_id)
        return {"ok": True}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}


@router.get("/api/slam/origin/{map_id}")
async def get_origin(map_id: str):
    """重定位默认位姿（X2 兼容：lines[1]='x y'）；A3 默认地图原点 0,0（实机校准后可改）"""
    return {"ok": True, "lines": ["a3", "0 0", ""]}


@router.get("/api/slam/pose")
async def slam_pose():
    """实时位姿（世界坐标 m，X2 兼容）——取自实时建图数据的 cur_pos（像素）+ 2D 图 origin 换算"""
    import time
    try:
        rt = rpc.mapping_realtime().get("data", {})
        cur = rt.get("cur_pos", {}).get("position", {})
        u, v, ang = cur.get("u"), cur.get("v"), rt.get("cur_pos", {}).get("angle", 0)
        if u is None:
            return {"pose": {}}
        # origin 从最近一次 get_map 的 meta 缓存；无缓存时退化返回像素
        m = _last_map_meta
        if m:
            res = float(m.get("resolution") or 20) / 1000.0   # mm/px → m/px
            x = (float(u) - float(m.get("origin_x") or 0)) * res
            y = -(float(v) - float(m.get("origin_y") or 0)) * res
            return {"pose": {"x": round(x, 3), "y": round(y, 3), "angle": ang, "ts": time.time()}}
        return {"pose": {"u": u, "v": v, "angle": ang}}
    except Exception:  # noqa: BLE001
        return {"pose": {}}


_last_map_meta: dict = {}


@router.get("/api/slam/realtime")
async def realtime():
    """实时建图数据（cur_pos + lidar_points + trajectory + png）——建图工作台数据源"""
    try:
        return {"ok": True, "data": rpc.mapping_realtime().get("data", {})}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}
