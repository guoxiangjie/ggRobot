"""Logo 脸屏显示控制 — 在脸部屏循环播放呼吸 logo

face_ui 服务在 PC3（交互单元），读 PC3 上 agi home(/agibot/data/home/agi/)下的文件，
PC2 的 /var/tmp 它读不到。logo.mp4 需在 PC3:/agibot/data/home/agi/logo.mp4。

可选自动同步：设了环境变量 GGROBOT_PC3_PASSWORD 且 PC2 装了 sshpass 时，
show 会自动把 logo.mp4 scp 到 PC3；否则假设文件已手动传到位。
手动传一次（home 持久，长期有效）：
  scp gg_robot/assets/logo.mp4 agi@10.0.1.42:/agibot/data/home/agi/
"""

import logging
import os
import subprocess
from pathlib import Path

from fastapi import APIRouter

from ..config import PC3_HOST

logger = logging.getLogger(__name__)
router = APIRouter()

LOGO_SRC = Path(__file__).resolve().parent / "assets" / "logo.mp4"
LOGO_PLAY_PATH = "/agibot/data/home/agi/logo.mp4"   # face_ui 在 PC3 读这里
PC3_PASSWORD = os.environ.get("GGROBOT_PC3_PASSWORD", "")


def _sync_logo_to_pc3() -> bool:
    """可选：用 sshpass 把 logo scp 到 PC3（配了 GGROBOT_PC3_PASSWORD 才生效）"""
    if not PC3_PASSWORD:
        return True  # 未配密码 → 假设文件已手动传到位，跳过自动同步
    try:
        subprocess.run(
            ["sshpass", "-p", PC3_PASSWORD, "scp", "-o", "StrictHostKeyChecking=no",
             str(LOGO_SRC), f"agi@{PC3_HOST}:{LOGO_PLAY_PATH}"],
            capture_output=True, timeout=15, check=False,
        )
        return True
    except Exception as e:
        logger.warning(f"logo 自动 scp 失败（文件应已手动传到 PC3）: {e}")
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
