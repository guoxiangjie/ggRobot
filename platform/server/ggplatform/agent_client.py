"""agent HTTP 客户端 — 平台→机器人的唯一通道（httpx，短超时）"""

import httpx

AGENT_PORT = 8300
_HEALTH_TIMEOUT = 1.0
_STATUS_TIMEOUT = 2.5
_CAPS_TIMEOUT = 4.0


async def fetch_health(ip: str, port: int = AGENT_PORT) -> dict | None:
    """/api/health（免 token）。不可达/超时返回 None。"""
    try:
        async with httpx.AsyncClient(timeout=_HEALTH_TIMEOUT) as c:
            r = await c.get(f"http://{ip}:{port}/api/health")
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None


async def fetch_status(ip: str, token: str, port: int = AGENT_PORT) -> dict | None:
    """/api/status（带 token）。token 错/离线返回 None。"""
    try:
        async with httpx.AsyncClient(timeout=_STATUS_TIMEOUT) as c:
            r = await c.get(f"http://{ip}:{port}/api/status",
                            headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None


async def fetch_capabilities(ip: str, token: str, port: int = AGENT_PORT) -> dict | None:
    """/api/capabilities（带 token，契约 v1）"""
    try:
        async with httpx.AsyncClient(timeout=_CAPS_TIMEOUT) as c:
            r = await c.get(f"http://{ip}:{port}/api/capabilities",
                            headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None
