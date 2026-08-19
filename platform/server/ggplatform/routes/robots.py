"""机器人 CRUD + 发现扫描 + 配对"""

import secrets
from typing import Optional

from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from sqlmodel import Session, select

from ..db import engine
from ..models import Robot
from ..discovery import scan_subnet, refresh_all
from ..agent_client import fetch_capabilities

router = APIRouter(prefix="/api")


class RobotCreate(BaseModel):
    sn: str
    name: str = ""
    model: str = "x2"


class RobotPatch(BaseModel):
    name: Optional[str] = None


def _robot_dict(rb: Robot, include_token: bool = True) -> dict:
    d = {
        "id": rb.id, "sn": rb.sn, "name": rb.name, "model": rb.model,
        "status": rb.status, "last_ip": rb.last_ip,
        "last_seen": rb.last_seen.isoformat() if rb.last_seen else None,
        "created_at": rb.created_at.isoformat(),
    }
    if include_token:
        d["token"] = rb.token
    return d


@router.get("/robots")
async def list_robots(refresh: bool = False):
    """机器人列表。?refresh=1 时先探测在线状态（hub 也会周期刷新）"""
    summaries = {}
    if refresh:
        for s in await refresh_all():
            summaries[s["id"]] = s
    with Session(engine) as s:
        robots = s.exec(select(Robot)).all()
        out = []
        for rb in robots:
            d = _robot_dict(rb)
            if rb.id in summaries:
                d["summary"] = summaries[rb.id]
            out.append(d)
        return {"robots": out}


@router.get("/robots/{robot_id}")
async def get_robot(robot_id: str):
    with Session(engine) as s:
        rb = s.get(Robot, robot_id)
        if not rb:
            raise HTTPException(404, "robot not found")
        d = _robot_dict(rb)
    # 顺带拉能力契约（失败静默——机器人可能离线）
    if rb.last_ip:
        caps = await fetch_capabilities(rb.last_ip, rb.token)
        if caps:
            d["capabilities"] = caps
    return d


@router.post("/robots")
async def create_robot(req: RobotCreate):
    with Session(engine) as s:
        exist = s.exec(select(Robot).where(Robot.sn == req.sn)).first()
        if exist:
            raise HTTPException(409, f"SN 已登记: {req.sn}")
        rb = Robot(sn=req.sn, name=req.name or req.sn, model=req.model,
                   token=secrets.token_urlsafe(24))
        s.add(rb)
        s.commit()
        s.refresh(rb)
        return _robot_dict(rb)


@router.patch("/robots/{robot_id}")
async def patch_robot(robot_id: str, req: RobotPatch):
    with Session(engine) as s:
        rb = s.get(Robot, robot_id)
        if not rb:
            raise HTTPException(404, "robot not found")
        if req.name is not None:
            rb.name = req.name
        s.add(rb)
        s.commit()
        return _robot_dict(rb)


@router.delete("/robots/{robot_id}")
async def delete_robot(robot_id: str):
    with Session(engine) as s:
        rb = s.get(Robot, robot_id)
        if not rb:
            raise HTTPException(404, "robot not found")
        s.delete(rb)
        s.commit()
    return {"ok": True}


@router.post("/robots/{robot_id}/token-rotate")
async def rotate_token(robot_id: str):
    """轮换 token：生成新值入库并返回（需重装/SSH 推送到 agent 生效）"""
    with Session(engine) as s:
        rb = s.get(Robot, robot_id)
        if not rb:
            raise HTTPException(404, "robot not found")
        rb.token = secrets.token_urlsafe(24)
        s.add(rb)
        s.commit()
        s.refresh(rb)
        return {"ok": True, "token": rb.token}


@router.post("/discovery/scan")
async def discovery_scan(subnet: str = "10.10.4"):
    """网段扫描：探测 subnet.1-254 的 :8300，按 SN 匹配库"""
    if not subnet.count(".") == 2:
        raise HTTPException(400, "subnet 形如 10.10.4（三段）")
    found = await scan_subnet(subnet)
    return {"subnet": subnet, "found": found}


@router.post("/estop")
async def emergency_stop():
    """全局急停：对所有在线机器人并发发零速度（安全件 — token 不出平台）"""
    import asyncio
    import httpx

    with Session(engine) as s:
        robots = s.exec(select(Robot)).all()

    async def zero(ip: str, token: str) -> tuple[str, bool]:
        try:
            async with httpx.AsyncClient(timeout=2.0) as c:
                r = await c.post(f"http://{ip}:8300/api/velocity",
                                 json={"forward": 0, "lateral": 0, "angular": 0},
                                 headers={"Authorization": f"Bearer {token}"})
                return ip, r.status_code == 200
        except Exception:
            return ip, False

    results = await asyncio.gather(*(zero(r.last_ip, r.token) for r in robots if r.last_ip))
    ok = [ip for ip, success in results if success]
    return {"ok": len(ok) > 0 or len(results) == 0, "stopped": ok, "total": len(results)}
