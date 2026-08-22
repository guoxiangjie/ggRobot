"""本地语音转写（sherpa-onnx）— 双档模型懒加载

模型：
  builtin    paraformer-zh-small int8（~82MB，随 dmg 内置 resources/asr/paraformer）
  sensevoice SenseVoice int8（~230MB，设置页经 main 下载器落到数据目录）
目录来源（main spawn sidecar 时注入）：
  GG_ASR_BUILTIN_DIR  内置模型目录（dmg: resources/asr；dev: platform/desktop/resources/asr）
  GG_ASR_DATA_DIR     用户数据目录（userData/asr-models，SenseVoice 下载处）

    GET  /api/asr/status      {builtin: bool, sensevoice: bool, active: str}
    POST /api/asr/transcribe  {audio_b64(PCM 16k/16bit/mono), model: auto|paraformer|sensevoice} → {ok, text, model}
"""

import base64
import logging
import os
from pathlib import Path

from fastapi import APIRouter
from pydantic import BaseModel

logger = logging.getLogger(__name__)
router = APIRouter(prefix="/api")

_builtin_dir = Path(os.environ.get("GG_ASR_BUILTIN_DIR") or "")
_data_dir = Path(os.environ.get("GG_ASR_DATA_DIR") or "")

# 懒加载缓存（首次转写才初始化，~1s；常驻复用）
_recs: dict[str, object] = {}


def _has_builtin() -> bool:
    return (_builtin_dir / "paraformer" / "model.int8.onnx").exists()


def _has_sensevoice() -> bool:
    return (_data_dir / "sensevoice" / "model.int8.onnx").exists()


def _load(model: str):
    import sherpa_onnx
    if model == "paraformer":
        d = _builtin_dir / "paraformer"
        return sherpa_onnx.OfflineRecognizer.from_paraformer(
            paraformer=str(d / "model.int8.onnx"), tokens=str(d / "tokens.txt"),
            num_threads=2, debug=False,
        )
    d = _data_dir / "sensevoice"
    return sherpa_onnx.OfflineRecognizer.from_sense_voice(
        model=str(d / "model.int8.onnx"), tokens=str(d / "tokens.txt"),
        use_itn=True, num_threads=2, debug=False,
    )


def _pick(model: str) -> str:
    """auto：有 SenseVoice 用 SenseVoice，否则 paraformer；指定模型不存在时回落另一档"""
    if model in ("paraformer", "sensevoice"):
        ok = _has_sensevoice() if model == "sensevoice" else _has_builtin()
        if ok:
            return model
    if _has_sensevoice():
        return "sensevoice"
    return "paraformer"


@router.get("/asr/status")
async def asr_status():
    return {"builtin": _has_builtin(), "sensevoice": _has_sensevoice(),
            "active": _pick("auto") if (_has_builtin() or _has_sensevoice()) else ""}


class TranscribeRequest(BaseModel):
    audio_b64: str = ""
    model: str = "auto"     # auto | paraformer | sensevoice
    sample_rate: int = 16000


@router.post("/asr/transcribe")
async def asr_transcribe(req: TranscribeRequest):
    if not req.audio_b64:
        return {"ok": False, "error": "缺音频数据"}
    model = _pick(req.model)
    try:
        import numpy as np
        if model not in _recs:
            _recs[model] = _load(model)
            logger.info(f"🎧 ASR 模型加载: {model}")
        pcm = base64.b64decode(req.audio_b64)
        samples = np.frombuffer(pcm, dtype=np.int16).astype(np.float32) / 32768.0
        rec = _recs[model]
        s = rec.create_stream()
        s.accept_waveform(req.sample_rate, samples)
        rec.decode_stream(s)
        return {"ok": True, "text": s.result.text.strip(), "model": model}
    except Exception as e:
        logger.warning(f"🎧 转写失败: {e}")
        return {"ok": False, "error": str(e)[:200]}
