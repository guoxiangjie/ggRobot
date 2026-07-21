"""Logo 脸屏显示控制 — 在脸部屏循环播放呼吸 logo

logo.mp4 需已 SCP 到 PC3（PC3_MEDIA_PATH/logo.mp4）。
"""

import logging
import subprocess
from pathlib import Path

from fastapi import APIRouter

from ..config import PC3_HOST, PC3_MEDIA_PATH

logger = logging.getLogger(__name__)
router = APIRouter()

LOGO_LOCAL = Path(__file__).resolve().parent / "assets" / "logo.mp4"   # 部署后在 PC2
LOGO_PC3_PATH = f"{PC3_MEDIA_PATH}/logo.mp4"                            # 播放时的 PC3 路径
SSH_KEY = str(Path.home() / ".ssh/id_rsa")


def _ensure_logo_on_pc3() -> bool:
    """覆盖式 scp logo.mp4 到 PC3（文件小，每次确保最新）"""
    try:
        subprocess.run(["ssh", "-i", SSH_KEY, f"agi@{PC3_HOST}",
                        f"mkdir -p {PC3_MEDIA_PATH}"], capture_output=True, timeout=5)
        subprocess.run(["scp", "-i", SSH_KEY, str(LOGO_LOCAL),
                        f"agi@{PC3_HOST}:{LOGO_PC3_PATH}"], capture_output=True, timeout=15)
        return True
    except Exception as e:
        logger.warning(f"logo scp 到 PC3 失败: {e}")
        return False


@router.post("/api/logo/show")
async def show():
    """循环播放 logo 到脸部屏（PlayVideo mode=2）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    synced = _ensure_logo_on_pc3()
    future = node_mod._cmd_queue.put("logo_show", file_path=LOGO_PC3_PATH)
    result = future.result(timeout=5.0)
    result["pc3_synced"] = synced
    return result


@router.post("/api/logo/hide")
async def hide():
    """关闭 logo（切回待机表情）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put("logo_hide")
    return future.result(timeout=5.0)
