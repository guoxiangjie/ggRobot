"""agent HTTP 客户端 — 平台→机器人的唯一通道（httpx，短超时）"""

import httpx

AGENT_PORT = 8300
_HEALTH_TIMEOUT = 2.0   # agent 事件循环偶发繁忙，1s 太紧会闪断（另有消抖兜底）
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


# ── 多机编排（choreo 协议，docs/choreo-design.md §3）──

_CHOREO_TIMEOUT = 5.0


async def choreo_load(ip: str, token: str, run_id: str, steps: list, port: int = AGENT_PORT) -> dict | None:
    """预分发本机轨道。会话被占（423）时返回 {"ok": False, "error": "...被占用"} 供前端提示接管"""
    try:
        async with httpx.AsyncClient(timeout=_CHOREO_TIMEOUT) as c:
            r = await c.post(f"http://{ip}:{port}/api/choreo/load",
                             json={"run_id": run_id, "steps": steps},
                             headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
            if r.status_code == 423:   # locked —— 区别于无响应，前端给出明确指引
                who = (r.json().get("locked_by") or {}).get("name") or "其他客户端"
                return {"ok": False, "error": f"控制权被「{who}」占用（可能是快捷遥控/控制页在连），关闭它或稍后再试"}
    except Exception:
        pass
    return None


async def choreo_start(ip: str, token: str, run_id: str, start_ts: float, port: int = AGENT_PORT) -> dict | None:
    """广播开始（绝对墙钟时刻）"""
    try:
        async with httpx.AsyncClient(timeout=_CHOREO_TIMEOUT) as c:
            r = await c.post(f"http://{ip}:{port}/api/choreo/start",
                             json={"run_id": run_id, "start_ts": start_ts},
                             headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None


async def choreo_stop(ip: str, token: str, run_id: str, port: int = AGENT_PORT) -> dict | None:
    """停止单机编排"""
    try:
        async with httpx.AsyncClient(timeout=_CHOREO_TIMEOUT) as c:
            r = await c.post(f"http://{ip}:{port}/api/choreo/stop",
                             json={"run_id": run_id},
                             headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None


async def choreo_status(ip: str, token: str, run_id: str, port: int = AGENT_PORT) -> dict | None:
    """查询单机编排状态"""
    try:
        async with httpx.AsyncClient(timeout=_CHOREO_TIMEOUT) as c:
            r = await c.get(f"http://{ip}:{port}/api/choreo/status",
                            params={"run_id": run_id},
                            headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None


async def fetch_choreo_types(ip: str, token: str, port: int = AGENT_PORT) -> dict | None:
    """拉取 agent 编排步骤类型清单（前端表单动态组装）"""
    try:
        async with httpx.AsyncClient(timeout=_CHOREO_TIMEOUT) as c:
            r = await c.get(f"http://{ip}:{port}/api/choreo/types",
                            headers={"Authorization": f"Bearer {token}"})
            if r.status_code == 200:
                return r.json()
    except Exception:
        pass
    return None
