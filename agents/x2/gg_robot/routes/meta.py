"""元端点 — /api/health（发现探测，免 token）/api/capabilities /api/session"""

from fastapi import APIRouter

from .. import __version__
from ..capabilities import build_capabilities
from ..security import agent_sn, controller, is_paired

router = APIRouter()


@router.get("/api/health")
async def health():
    """发现协议探测端点：平台扫描网段 :8300 后调它拿 SN/model/version 判身份。免 token。"""
    return {
        "ok": True,
        "service": "ggrobot-agent",
        "sn": agent_sn() or "unpaired",
        "model": "x2",
        "version": __version__,
        "paired": is_paired(),
    }


@router.get("/api/capabilities")
async def capabilities():
    """能力契约上报（contracts v1）——平台/前端按能力类型组装 UI 的数据源"""
    return build_capabilities()


@router.get("/api/session")
async def session_info():
    """当前控制者信息（无控制者返回 free）"""
    cur = controller.current()
    return {"free": cur is None, "controller": cur}


@router.post("/api/session/takeover")
async def session_takeover(client_id: str = "cli", name: str = ""):
    """抢占控制权（原持有者收到 session lost）"""
    kicked = controller.takeover(client_id, name)
    return {"ok": True, "kicked": kicked, "controller": controller.current()}
