"""配对 — 平台生成 token，装机向导 SSH 推 deb + /tmp/gg-token，postinst 吸收后自动激活"""

import secrets

from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from sqlmodel import Session, select

from ..db import engine
from ..models import Robot
from ..agent_client import fetch_health

router = APIRouter(prefix="/api/pair")


class PairPrepare(BaseModel):
    ip: str
    name: str = ""


@router.post("/prepare")
async def pair_prepare(req: PairPrepare):
    """装机向导第一步：探 IP 的 /api/health 拿 SN → upsert Robot(pending) → 返回 token

    流程：renderer 拿 token → desktop IPC installAgent（sftp 推 deb + /tmp/gg-token，
    apt install 后 postinst 吸收 token 并启动）→ hub 轮询 health+token 通过 → 自动 active。
    """
    health = await fetch_health(req.ip)
    if health is None:
        raise HTTPException(502, f"{req.ip}:8300 无 agent 响应（需先安装 deb）")

    sn = health.get("sn") or "unpaired"
    if sn == "unpaired" or not health.get("ok"):
        raise HTTPException(409, "agent 未上报 SN（异常状态）")

    token = secrets.token_urlsafe(24)
    with Session(engine) as s:
        rb = s.exec(select(Robot).where(Robot.sn == sn)).first()
        if rb:
            # 已登记（重装场景）：更新 token 为新值，保持身份/别名
            rb.token = token
            rb.last_ip = req.ip
            rb.status = "pending"
        else:
            rb = Robot(sn=sn, name=req.name or f"{health.get('model', 'robot')}-{sn[-4:]}",
                       model=health.get("model", "x2"), token=token,
                       status="pending", last_ip=req.ip)
        s.add(rb)
        s.commit()
        s.refresh(rb)
        return {
            "robot": {"id": rb.id, "sn": rb.sn, "name": rb.name, "model": rb.model},
            "token": token,
            "ip": req.ip,
        }
