"""多机编排 CRUD + 执行（platform 侧）

    GET    /api/choreos                    列表（摘要）
    GET    /api/choreos/{id}               详情（含 tracks）
    POST   /api/choreos                    新建
    PATCH  /api/choreos/{id}               更新
    DELETE /api/choreos/{id}               删除
    POST   /api/choreos/{id}/run           执行（分发→广播→监控）
    POST   /api/choreo/run/{run_id}/stop   停止
    GET    /api/choreo/run/{run_id}/status 聚合状态
"""

import json
import logging
from datetime import datetime, timezone
from typing import Optional

from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from sqlmodel import Session, select

from ..db import engine
from ..models import Robot, Choreography
from ..choreo.runner import runner

logger = logging.getLogger(__name__)
router = APIRouter(prefix="/api")


class ChoreoSaveRequest(BaseModel):
    name: str = "未命名编排"
    desc: str = ""
    tracks: list[dict] = []   # [{robot_id, robot_name, steps:[{type, at, ...}]}]


def _choreo_dict(ch: Choreography, include_tracks: bool = True) -> dict:
    d = {
        "id": ch.id,
        "name": ch.name,
        "desc": ch.desc,
        "created_at": ch.created_at.isoformat(),
        "updated_at": ch.updated_at.isoformat(),
    }
    if include_tracks:
        try:
            d["tracks"] = json.loads(ch.tracks_json or "[]")
        except json.JSONDecodeError:
            d["tracks"] = []
        d["robot_count"] = len(d["tracks"])
        d["step_count"] = sum(len(t.get("steps") or []) for t in d["tracks"])
    return d


def _validate_tracks(tracks: list[dict]) -> list[str]:
    """基础校验：每轨 robot_id 非空、steps 是数组、at 可转 float。返回错误列表。"""
    errors = []
    for i, tr in enumerate(tracks):
        if not tr.get("robot_id"):
            errors.append(f"轨道 {i + 1} 缺 robot_id")
            continue
        steps = tr.get("steps") or []
        if not isinstance(steps, list):
            errors.append(f"轨道 {i + 1} steps 必须是数组")
            continue
        for j, st in enumerate(steps):
            if not st.get("type"):
                errors.append(f"轨道 {i + 1} 步骤 {j + 1} 缺 type")
            try:
                float(st.get("at", 0.0))
            except (TypeError, ValueError):
                errors.append(f"轨道 {i + 1} 步骤 {j + 1} 的 at 非数字")
    return errors


# ── CRUD ──

@router.get("/choreos")
async def list_choreos():
    with Session(engine) as s:
        rows = s.exec(select(Choreography).order_by(Choreography.created_at)).all()
        return {"choreos": [_choreo_dict(c, include_tracks=False) for c in rows]}


@router.get("/choreos/{choreo_id}")
async def get_choreo(choreo_id: str):
    with Session(engine) as s:
        ch = s.get(Choreography, choreo_id)
        if ch is None:
            raise HTTPException(404, "编排不存在")
        return _choreo_dict(ch)


@router.post("/choreos")
async def create_choreo(req: ChoreoSaveRequest):
    errors = _validate_tracks(req.tracks)
    if errors:
        raise HTTPException(400, "；".join(errors))
    with Session(engine) as s:
        ch = Choreography(name=req.name or "未命名编排", desc=req.desc,
                          tracks_json=json.dumps(req.tracks, ensure_ascii=False))
        s.add(ch)
        s.commit()
        s.refresh(ch)
        return _choreo_dict(ch)


@router.patch("/choreos/{choreo_id}")
async def patch_choreo(choreo_id: str, req: ChoreoSaveRequest):
    errors = _validate_tracks(req.tracks)
    if errors:
        raise HTTPException(400, "；".join(errors))
    with Session(engine) as s:
        ch = s.get(Choreography, choreo_id)
        if ch is None:
            raise HTTPException(404, "编排不存在")
        ch.name = req.name or ch.name
        ch.desc = req.desc
        ch.tracks_json = json.dumps(req.tracks, ensure_ascii=False)
        ch.updated_at = datetime.now(timezone.utc)
        s.add(ch)
        s.commit()
        s.refresh(ch)
        return _choreo_dict(ch)


@router.delete("/choreos/{choreo_id}")
async def delete_choreo(choreo_id: str):
    with Session(engine) as s:
        ch = s.get(Choreography, choreo_id)
        if ch is None:
            raise HTTPException(404, "编排不存在")
        s.delete(ch)
        s.commit()
    return {"ok": True}


# ── 执行 ──

@router.post("/choreos/{choreo_id}/run")
async def run_choreo(choreo_id: str):
    with Session(engine) as s:
        ch = s.get(Choreography, choreo_id)
        if ch is None:
            raise HTTPException(404, "编排不存在")
        tracks = json.loads(ch.tracks_json or "[]")
        name = ch.name

    # 收集涉及的机器人（id → {name, ip, port, token}）
    robot_ids = {tr.get("robot_id") for tr in tracks if tr.get("robot_id")}
    robots: dict[str, dict] = {}
    if robot_ids:
        with Session(engine) as s:
            rows = s.exec(select(Robot).where(Robot.id.in_(robot_ids))).all()
            for rb in rows:
                robots[rb.id] = {"name": rb.name or rb.sn, "ip": rb.last_ip or "",
                                 "port": rb.port or 8300, "token": rb.token or ""}

    return await runner.run({"id": choreo_id, "name": name, "tracks": tracks}, robots)


@router.post("/choreo/run/{run_id}/stop")
async def stop_choreo_run(run_id: str):
    return await runner.stop(run_id)


@router.get("/choreo/run/{run_id}/status")
async def choreo_run_status(run_id: str):
    return runner.status(run_id)
