"""机器人发现 — 网段扫描 :8300 + /api/health 取 SN 判身份"""

import asyncio

from sqlmodel import Session, select

from .db import engine, utcnow
from .models import Robot
from .agent_client import fetch_health, fetch_status

SCAN_TIMEOUT = 0.3   # 每 IP TCP 探测超时
SCAN_CONCURRENCY = 64


async def _probe(ip: str) -> dict | None:
    """探测单 IP：TCP 8300 通 → GET /api/health"""
    try:
        reader, writer = await asyncio.wait_for(
            asyncio.open_connection(ip, 8300), timeout=SCAN_TIMEOUT)
        writer.close()
        await writer.wait_closed()
    except Exception:
        return None
    health = await fetch_health(ip)
    if health is not None:
        health["ip"] = ip
    return health


async def scan_subnet(subnet: str) -> list[dict]:
    """扫描 subnet（如 '10.10.4'）的 1-254，返回发现的 agent 候选清单

    返回项：{ip, sn, model, version, paired, registered, robot_id?, name?}
    registered=true 表示库里已有该 SN（pending 或 active）。
    """
    sem = asyncio.Semaphore(SCAN_CONCURRENCY)

    async def guarded(ip: str):
        async with sem:
            return await _probe(ip)

    results = await asyncio.gather(*(guarded(f"{subnet}.{i}") for i in range(1, 255)))
    found = [r for r in results if r]

    # 匹配库内已登记
    known: dict[str, Robot] = {}
    with Session(engine) as s:
        for rb in s.exec(select(Robot)).all():
            known[rb.sn] = rb

    out = []
    for h in found:
        sn = h.get("sn") or "unpaired"
        rb = known.get(sn)
        out.append({
            "ip": h.get("ip"),
            "sn": sn,
            "model": h.get("model", ""),
            "version": h.get("version", ""),
            "paired": h.get("paired", False),
            "registered": rb is not None,
            "robot_id": rb.id if rb else None,
            "name": rb.name if rb else "",
            "status": rb.status if rb else "unregistered",
        })
    return out


async def refresh_robot_online_state(robot: Robot) -> dict:
    """刷新单台机器人的在线状态并落库（health + status token 双探测）

    返回聚合摘要 {id, sn, name, online, token_ok, battery_soc, version, last_ip}
    pending 状态的机器人 health 通且 token 校验通过 → 自动激活 active。
    """
    summary = {
        "id": robot.id, "sn": robot.sn, "name": robot.name or robot.sn,
        "model": robot.model, "status": robot.status,
        "online": False, "token_ok": False,
        "battery_soc": None, "version": "", "last_ip": robot.last_ip,
    }
    ip = robot.last_ip
    if not ip:
        return summary

    health = await fetch_health(ip)
    if health is None:
        return summary

    summary["online"] = True
    summary["version"] = health.get("version", "")

    status = None
    if robot.token:
        status = await fetch_status(ip, robot.token)
        summary["token_ok"] = status is not None
        if status and isinstance(status.get("battery"), dict):
            b = status["battery"]
            soc = b.get("percentage") or b.get("soc")
            summary["battery_soc"] = int(soc) if soc is not None else None

    # pending → active（health 通 + token 验证通过 = 装机完成）
    now_active = robot.status == "active" or (robot.status == "pending" and summary["token_ok"])
    summary["status"] = "active" if now_active else robot.status

    with Session(engine) as s:
        db_robot = s.get(Robot, robot.id)
        if db_robot:
            db_robot.last_seen = utcnow()
            db_robot.status = summary["status"]
            s.add(db_robot)
            s.commit()
    return summary


async def refresh_all() -> list[dict]:
    """刷新全部已登记机器人（hub 5s 循环调用）"""
    with Session(engine) as s:
        robots = s.exec(select(Robot)).all()
    return list(await asyncio.gather(*(refresh_robot_online_state(r) for r in robots)))
