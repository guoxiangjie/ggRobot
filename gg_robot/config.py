"""ggRobot 配置 — 环境变量优先，robot.yaml 兜底

优先级：环境变量 > robot.yaml > 硬编码默认值
"""

import os
import logging
import shutil
from pathlib import Path

logger = logging.getLogger(__name__)

# ── 尝试加载 robot.yaml ──────────────────────
_yaml_config: dict = {}

def _load_yaml(path: Path) -> dict:
    """简易 YAML 解析器，只支持嵌套 key: value（无需 pyyaml）"""
    if not path.exists():
        return {}
    result = {}
    stack = [(result, -1)]  # (dict, indent_level)
    with open(path) as f:
        for line in f:
            stripped = line.rstrip()
            if not stripped or stripped.startswith("#") or stripped.startswith("---"):
                continue
            # 计算缩进层级
            indent = len(line) - len(line.lstrip())
            key, _, val = stripped.partition(":")
            key = key.strip()
            val = val.strip().strip('"').strip("'")
            if val == "":
                # 父节点，创建子 dict
                child = {}
                result[key] = child
                stack = [(r, i) for r, i in stack if i < indent]
                stack.append((child, indent))
            else:
                # 叶子节点
                while stack and stack[-1][1] >= indent:
                    stack.pop()
                target = stack[-1][0] if stack else result
                # 类型转换
                if val.lower() in ("true", "false"):
                    val = val.lower() == "true"
                elif val.count(".") == 1 and all(p.isdigit() or (p.startswith("-") and p[1:].isdigit()) for p in val.split(".")):
                    val = float(val)
                elif val.lstrip("-").isdigit():
                    val = int(val)
                target[key] = val
    return result


_yaml_path = Path(__file__).resolve().parent.parent / "config" / "robot.yaml"
try:
    _yaml_config = _load_yaml(_yaml_path)
    logger.info(f"📋 已加载配置: {_yaml_path}")
except Exception as e:
    logger.warning(f"⚠️ 配置加载失败: {e}")


def _get(key: str, default=None):
    """读取配置：env > yaml > default"""
    env_key = f"GGROBOT_{key.upper()}"
    if env_key in os.environ:
        return os.environ[env_key]
    # 支持嵌套 key，如 "robot.pc3_host"
    parts = key.split(".")
    val = _yaml_config
    for p in parts:
        if isinstance(val, dict):
            val = val.get(p)
        else:
            val = None
            break
    return val if val is not None else default


# ── 公开配置项 ──

# 机器人连接
PC2_HOST = _get("robot.pc2_host", "10.0.1.41")
PC3_HOST = _get("robot.pc3_host", "10.0.1.42")
PC3_MEDIA_PATH = _get("robot.pc3_media_path", "/agibot/data/home/agi/media")  # face_ui 在 PC3 读这里
PC3_PASSWORD = os.environ.get("GGROBOT_PC3_PASSWORD", "")  # 配了则用 sshpass 自动 scp 到 PC3

# 速度控制
VEL_SOURCE_NAME = _get("velocity.source_name", "web_ui")
VEL_PUBLISH_RATE = _get("velocity.publish_rate", 50)

# 注：导航参数未走本配置 —— navigation/avoidance.py 独立运行，
# 参数硬编码在其 CFG 字典中（robot.yaml 的 navigation 段暂未接线，见该文件注释）。

# ── 用户数据目录 ──
# 任务/项目/手机按键/媒体等用户数据独立于部署目录 ~/ggRobot，
# make clean/ship 全量部署 rm -rf ~/ggRobot 不会清掉这里。
# 优先级：env GGROBOT_DATA_DIR > robot.yaml server.data_dir > ~/ggRobot-data
DATA_DIR = Path(os.environ.get("GGROBOT_DATA_DIR") or _get("server.data_dir", "~/ggRobot-data")).expanduser()

# 旧版用户数据位置（部署目录内，全量部署会被清掉）
_LEGACY_DATA_ROOT = Path.home() / "ggRobot"
_LEGACY_ITEMS = ("tasks", "projects", "phone_keys.json", "media")


def migrate_legacy_data():
    """首次启动时把旧版存放在 ~/ggRobot 内的用户数据迁移到 DATA_DIR（幂等，目标已存在则跳过）。"""
    if DATA_DIR == _LEGACY_DATA_ROOT:
        return
    DATA_DIR.mkdir(parents=True, exist_ok=True)
    moved = []
    for name in _LEGACY_ITEMS:
        src = _LEGACY_DATA_ROOT / name
        dst = DATA_DIR / name
        if src.exists() and not dst.exists():
            try:
                shutil.move(str(src), str(dst))
                moved.append(name)
            except Exception as e:
                logger.warning(f"⚠️ 用户数据迁移 {name} 失败: {e}")
    if moved:
        logger.info(f"📦 旧版用户数据已迁移到 {DATA_DIR}: {', '.join(moved)}")
