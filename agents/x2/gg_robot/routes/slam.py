"""SLAM REST API — 建图 / 取图 / 重定位 / 位姿

POST /api/slam/mapping/start        开始建图
POST /api/slam/mapping/stop         停止建图并保存 {map_name}
GET  /api/slam/maps                 已建地图列表（读 map.db）
GET  /api/slam/map/{map_name}       取地图（PNG base64 + 拓扑点）
POST /api/slam/relocalize           重定位 {map_id, x, y}
GET  /api/slam/pose                 实时位姿（lidar_odom）
GET  /api/slam/origin/{map_id}      重定位默认位姿（grid_map_info.txt origin）
"""

import logging
import sqlite3
from pathlib import Path

from fastapi import APIRouter
from pydantic import BaseModel

logger = logging.getLogger(__name__)
router = APIRouter()

MAP_DIR = Path("/agibot/data/var/MapManagerModule")
MAP_DB = MAP_DIR / "map.db"


class StopMappingRequest(BaseModel):
    map_name: str


class RelocalizeRequest(BaseModel):
    map_id: str
    x: float
    y: float


# ── 建图 ──

@router.post("/api/slam/mapping/start")
async def start_mapping():
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "命令队列未就绪"}
    future = node_mod._cmd_queue.put("slam_command", cmd="start_mapping")
    return future.result(timeout=5.0)


@router.post("/api/slam/mapping/stop")
async def stop_mapping(req: StopMappingRequest):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "命令队列未就绪"}
    future = node_mod._cmd_queue.put("slam_command", cmd=f"stop_mapping:{req.map_name}")
    return future.result(timeout=5.0)


# ── 地图 ──

@router.get("/api/slam/maps")
async def list_maps():
    """读 map.db 列出已建地图（map_id, map_name）"""
    if not MAP_DB.exists():
        # map.db 在首次建图保存后才生成；不存在 = 尚未建图，返回空列表（不报错）
        return {"maps": []}
    try:
        # 只读连接（uri mode=ro），不锁库；每次开闭
        con = sqlite3.connect(f"file:{MAP_DB}?mode=ro", uri=True)
        cur = con.execute("SELECT map_id, map_name FROM map")
        maps = [{"map_id": str(row[0]), "map_name": row[1] or ""} for row in cur.fetchall()]
        con.close()
        return {"maps": maps}
    except Exception as e:
        logger.warning(f"读 map.db 失败: {e}")
        return {"maps": [], "error": f"读 map.db 失败: {e}"}


@router.get("/api/slam/map/{map_name}")
async def get_map(map_name: str):
    """取地图（PNG base64 + map_info + 导航点 + 虚拟墙）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "命令队列未就绪"}
    future = node_mod._cmd_queue.put("get_map", map_name=map_name)
    return future.result(timeout=35.0)


# ── 重定位 ──

@router.post("/api/slam/relocalize")
async def relocalize(req: RelocalizeRequest):
    """重定位：发 start_relocalization:<map_id> + 像素位姿，阻塞等 lidar_odom（最多 ~35s）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "命令队列未就绪"}
    future = node_mod._cmd_queue.put("relocalize", map_id=req.map_id, x=req.x, y=req.y)
    return future.result(timeout=35.0)


@router.get("/api/slam/origin/{map_id}")
async def get_origin(map_id: str):
    """读 <map_id>/grid_map_info.txt（3行：分辨率/origin/长宽），返回 origin 供重定位默认位姿"""
    info_path = MAP_DIR / map_id / "grid_map_info.txt"
    if not info_path.exists():
        return {"ok": False, "error": f"grid_map_info.txt 不存在: {info_path}"}
    try:
        lines = info_path.read_text(encoding="utf-8", errors="replace").strip().splitlines()
        return {"ok": True, "lines": lines[:3]}
    except Exception as e:
        return {"ok": False, "error": str(e)}


# ── 实时位姿 ──

@router.get("/api/slam/pose")
async def slam_pose():
    """当前 SLAM 位姿（/slam/lidar_odom 缓存）"""
    from .. import node as node_mod
    n = node_mod._node
    return {"pose": getattr(n, "slam_pose", {})}
