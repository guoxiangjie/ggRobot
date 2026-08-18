"""Logo 脸屏显示控制 — 在脸部屏循环播放呼吸 logo

face_ui 服务在 PC3（交互单元），读 PC3_MEDIA_PATH(/agibot/data/home/agi/media/)下的文件。
配了 GGROBOT_PC3_PASSWORD + sshpass 时 show 自动同步 logo，否则假设已手动传到位。
手动传一次（home 持久，长期有效）：
  scp gg_robot/assets/logo.mp4 agi@10.0.1.42:/agibot/data/home/agi/media/
"""

import logging
import subprocess
from pathlib import Path

from fastapi import APIRouter

from ..config import PC3_HOST, PC3_MEDIA_PATH, PC3_PASSWORD

logger = logging.getLogger(__name__)
router = APIRouter()

LOGO_SRC = Path(__file__).resolve().parent / "assets" / "logo.mp4"
LOGO_PLAY_PATH = f"{PC3_MEDIA_PATH}/logo.mp4"


def _sync_logo_to_pc3() -> bool:
    """可选：用 sshpass 把 logo scp 到 PC3（配了 GGROBOT_PC3_PASSWORD 才生效，并检查返回码）"""
    if not PC3_PASSWORD:
        return True  # 未配密码 → 假设文件已手动传到位，跳过自动同步
    try:
        r = subprocess.run(
            ["sshpass", "-p", PC3_PASSWORD, "scp", "-o", "StrictHostKeyChecking=no",
             str(LOGO_SRC), f"agi@{PC3_HOST}:{LOGO_PLAY_PATH}"],
            capture_output=True, timeout=15,
        )
        if r.returncode != 0:
            logger.warning(f"logo scp 失败: {r.stderr.decode(errors='replace').strip()}")
            return False
        return True
    except Exception as e:
        logger.warning(f"logo scp 失败（文件应已手动传到 PC3）: {e}")
        return False


@router.post("/api/logo/show")
async def show():
    """循环播放 logo 到脸部屏（PlayVideo mode=2）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    _sync_logo_to_pc3()
    future = node_mod._cmd_queue.put("logo_show", file_path=LOGO_PLAY_PATH)
    return future.result(timeout=5.0)


@router.post("/api/logo/hide")
async def hide():
    """关闭 logo（切回待机表情）"""
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}
    future = node_mod._cmd_queue.put("logo_hide")
    return future.result(timeout=5.0)
