"""MIC 采集 + VAD 段 — 对齐 X2 /api/mic 语义（ASR 由平台 sidecar 承担）

A3 注意（docs 7.3 / 8.2）：
- 持续音频输出需 agent 交互模式 only_voice（SetAgentPropertiesRequest，重启机器人生效）
- normal 模式下唤醒词短时激活 VAD
"""

import logging

from fastapi import APIRouter, Query
from pydantic import BaseModel

from .. import rpc

logger = logging.getLogger(__name__)
router = APIRouter()

VAD_LABELS = {0: "无语音", 1: "开始说话", 2: "说话中", 3: "语音结束"}


class MicToggleRequest(BaseModel):
    enable: bool


def _node():
    from .. import node as node_mod
    return node_mod._node


@router.get("/api/mic")
async def mic_status():
    n = _node()
    if n is None:
        return {"ok": False, "enabled": False, "vad_state": 0, "segment_bytes": 0,
                "last_segment_bytes": 0, "mic_source": 0, "text": "", "recv_count": 0}
    st = n.get_mic_status()
    return {"ok": True, **st, "vad_label": VAD_LABELS.get(st["vad_state"], "未知")}


@router.post("/api/mic")
async def mic_toggle(req: MicToggleRequest):
    n = _node()
    if n is None:
        return {"ok": False, "enabled": False, "error": "后端未初始化"}
    n.mic_enabled = req.enable
    return {"ok": True, "enabled": n.mic_enabled, "vad_state": n._vad_state}


@router.get("/api/mic/audio")
async def mic_audio():
    """最近一个完整语音段（PCM 16k/16bit/mono，base64）"""
    n = _node()
    if n is None:
        return {"ok": False}
    b64 = n.get_mic_audio_b64()
    return {"ok": bool(b64), "data": b64, "size": len(b64) * 3 // 4,
            "ts": n._mic_last_segment_ts}


@router.get("/api/mic/source")
async def get_source():
    try:
        r = rpc.call("hdu_audio", "aimdk.protocol.HalAudioService", "GetMicSourceRequest",
                     {}, retries=2)
        src = int(r.get("mic_source", 0))
        if _node() is not None:
            _node()._mic_source = src
        return {"mic_source": src}
    except Exception as e:  # noqa: BLE001
        return {"mic_source": _node()._mic_source if _node() else 0, "error": str(e)}


@router.post("/api/mic/source")
async def set_source(mic_source: int = Query(..., ge=0, le=1)):
    try:
        rpc.call("hdu_audio", "aimdk.protocol.HalAudioService", "SetMicSourceRequest",
                 {"mic_source": mic_source})
        return {"mic_source": mic_source}
    except Exception as e:  # noqa: BLE001
        return {"mic_source": mic_source, "error": str(e)}


@router.get("/api/mic/mode")
async def get_mode():
    """交互运行模式（normal / only_voice / voice_face）"""
    try:
        r = rpc.call("hdu", "aimdk.protocol.AgentControlService", "GetAgentPropertiesRequest",
                     {"property_ids": [2]}, retries=2)
        mode = (r.get("contents", {}).get("properties", {}) or {}).get("2", "")
        return {"mode": mode}
    except Exception as e:  # noqa: BLE001
        return {"mode": "", "error": str(e)}


@router.post("/api/mic/mode")
async def set_mode(mode: str = Query(..., description="normal/only_voice/voice_face")):
    """切换交互运行模式（⚠️ 需重启机器人生效；only_voice 后 VAD 音频持续输出）"""
    if mode not in ("normal", "only_voice", "voice_face"):
        return {"ok": False, "error": f"非法模式: {mode}"}
    try:
        rpc.call("hdu", "aimdk.protocol.AgentControlService", "SetAgentPropertiesRequest",
                 {"contents": {"properties": {"2": mode}}})
        return {"ok": True, "mode": mode, "note": "需重启机器人生效"}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "error": str(e)}
