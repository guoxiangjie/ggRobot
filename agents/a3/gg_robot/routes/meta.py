"""元端点 — /api/health（发现探测，免 token）/api/capabilities /api/session"""

from fastapi import APIRouter

from .. import __version__
from ..capabilities import build_capabilities, MODEL
from ..security import agent_sn, controller, is_paired

router = APIRouter()


@router.get("/api/health")
async def health():
    return {
        "ok": True,
        "service": "ggrobot-agent",
        "sn": agent_sn() or "unpaired",
        "model": MODEL,
        "version": __version__,
        "paired": is_paired(),
    }


@router.get("/api/capabilities")
async def capabilities():
    return build_capabilities()


@router.get("/api/session")
async def session_info():
    cur = controller.current()
    return {"free": cur is None, "controller": cur}


@router.post("/api/session/takeover")
async def session_takeover(client_id: str = "cli", name: str = ""):
    kicked = controller.takeover(client_id, name)
    return {"ok": True, "kicked": kicked, "controller": controller.current()}
