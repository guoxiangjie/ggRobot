"""MIC 采集 + VAD + ASR

数据来自机器人侧 agent 发布的 /agent/process_audio_output
（PCM 16kHz/16bit/单声道，VAD 状态 0=无语音 1=开始 2=处理中 3=结束）。
⚠️ VAD 需要先唤醒词激活（v0.9+），见 CLAUDE.md。
"""

import base64
import logging
import threading

from fastapi import APIRouter
from pydantic import BaseModel, Field

logger = logging.getLogger(__name__)
router = APIRouter()

VAD_LABELS = {0: "无语音", 1: "开始说话", 2: "说话中", 3: "语音结束"}


class MicToggleRequest(BaseModel):
    enable: bool


class MicSourceRequest(BaseModel):
    mic_source: int = Field(..., ge=0, le=1, description="0=内置麦 1=外置麦")


def _node():
    from .. import node as node_mod
    return node_mod._node


@router.get("/api/mic")
async def mic_status():
    """采集/识别状态（VAD 四态、缓冲大小、最近识别文本、麦克风源）"""
    n = _node()
    if n is None:
        return {"ok": False, "enabled": False, "vad_state": 0, "segment_bytes": 0,
                "last_segment_bytes": 0, "mic_source": 0, "text": "", "recv_count": 0}
    st = n.get_mic_status()
    return {"ok": True, **st, "vad_label": VAD_LABELS.get(st["vad_state"], "未知")}


@router.post("/api/mic")
async def mic_toggle(req: MicToggleRequest):
    """开启/关闭识别（采集状态始终跟踪；关闭后不再触发 ASR）"""
    n = _node()
    if n is None:
        return {"ok": False, "enabled": False, "error": "后端未初始化"}
    n.mic_enabled = req.enable
    if not req.enable:
        n._mic_text = ""
    logger.info(f"🎙️ MIC 识别 {'开启' if req.enable else '关闭'}")
    return {"ok": True, "enabled": n.mic_enabled, "vad_state": n._vad_state}


@router.get("/api/mic/audio")
async def mic_audio():
    """最近一个完整语音段（PCM 16k/16bit/mono，base64）+ 识别文本"""
    n = _node()
    if n is None:
        return {"ok": False, "data": "", "size": 0, "text": ""}
    with n._mic_lock:
        data = n._mic_last_segment
        text = n._mic_text
    return {"ok": True, "data": base64.b64encode(data).decode(), "size": len(data), "text": text}


@router.get("/api/mic/source")
async def mic_source_get():
    """查询当前 MIC 设备（0=内置 1=外置）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "mic_source": 0, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put("mic_source_get")
    return future.result(timeout=5.0)


@router.post("/api/mic/source")
async def mic_source_set(req: MicSourceRequest):
    """切换 MIC 设备（0=内置 1=外置）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "mic_source": 0, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put("mic_source_set", mic_source=req.mic_source)
    return future.result(timeout=5.0)


@router.post("/api/mic/asr")
async def mic_asr():
    """强制对最近一个语音段重新识别（异步，结果轮询 /api/mic）"""
    n = _node()
    if n is None:
        return {"ok": False, "error": "后端未初始化"}
    with n._mic_lock:
        segment = n._mic_last_segment
    if not segment:
        return {"ok": False, "error": "暂无语音段"}
    if n._asr_busy:
        return {"ok": True, "started": False, "error": "已有识别在进行"}
    n._asr_busy = True
    threading.Thread(target=n._asr_worker, args=(segment,), daemon=True).start()
    return {"ok": True, "started": True}
