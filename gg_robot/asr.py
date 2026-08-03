"""语音识别引擎 — 可插拔：none / funasr（本地 FunASR）

VAD 采集到的是 16kHz / 16bit / 单声道 PCM，直接喂给识别后端。
新增后端只需实现 recognize(pcm_bytes) -> str。

默认 none（只采集不识别，平台其他功能不受影响）；
配置 robot.yaml mic.asr_provider=funasr 后启用本地 FunASR。
Orin 上安装：pip install funasr modelscope（torch 按 Jetson 官方 wheel 装）。
"""

import logging
import threading

from .config import MIC_ASR_PROVIDER, MIC_ASR_MODEL

logger = logging.getLogger(__name__)


class NullAsr:
    """未配置识别后端：只采集展示，不识别"""
    name = "none"

    def recognize(self, pcm: bytes) -> str:
        return ""


class FunasrAsr:
    """本地 FunASR（默认 paraformer-zh）。

    依赖较重（torch + funasr），加载/识别失败时降级为空识别，绝不拖垮主服务。
    """
    name = "funasr"

    def __init__(self, model_name: str = "paraformer-zh"):
        self._model_name = model_name
        self._model = None       # None=未加载 True=就绪 False=加载失败
        self._lock = threading.Lock()

    def _ensure_model(self):
        if self._model is not None:
            return self._model is True
        try:
            from funasr import AutoModel
            self._model = AutoModel(
                model=self._model_name,
                model_revision="v2.0.4",
                disable_update=True,
            )
            logger.info(f"🎙️ FunASR 模型就绪: {self._model_name}")
            return True
        except Exception as e:
            logger.error(f"🎙️ FunASR 加载失败（本次会话不识别，可装依赖后重启）: {e}")
            self._model = False
            return False

    def recognize(self, pcm: bytes) -> str:
        if not pcm:
            return ""
        with self._lock:
            if not self._ensure_model():
                return ""
            try:
                import numpy as np
                audio = np.frombuffer(pcm, dtype=np.int16).astype(np.float32) / 32768.0
                res = self._model.generate(input=audio, batch_size_s=300, is_final=True)
                if res and isinstance(res, list) and res[0].get("text"):
                    return str(res[0]["text"]).strip()
            except Exception as e:
                logger.warning(f"🎙️ FunASR 识别失败: {e}")
        return ""


_ENGINE = None
_ENGINE_LOCK = threading.Lock()


def get_asr_engine():
    """单例：按 robot.yaml mic.asr_provider 选择后端"""
    global _ENGINE
    with _ENGINE_LOCK:
        if _ENGINE is None:
            provider = (MIC_ASR_PROVIDER or "none").strip().lower()
            if provider == "funasr":
                _ENGINE = FunasrAsr(MIC_ASR_MODEL)
            else:
                _ENGINE = NullAsr()
            logger.info(f"🎙️ ASR 引擎: {_ENGINE.name}")
        return _ENGINE
