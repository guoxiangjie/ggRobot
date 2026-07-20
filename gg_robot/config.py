"""ggRobot 配置 — 环境变量优先，robot.yaml 兜底

优先级：环境变量 > robot.yaml > 硬编码默认值
"""

import os
import logging
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
PC3_MEDIA_PATH = _get("robot.pc3_media_path", "/var/tmp/x2_media")

# 速度控制
VEL_SOURCE_NAME = _get("velocity.source_name", "web_ui")
VEL_PUBLISH_RATE = _get("velocity.publish_rate", 50)

# 激光避障
NAV_STOP_DISTANCE = _get("navigation.stop_distance", 0.5)
NAV_AVOID_DISTANCE = _get("navigation.avoid_distance", 0.8)
NAV_SLOW_DISTANCE = _get("navigation.slow_distance", 1.5)
NAV_MAX_FORWARD_SPEED = _get("navigation.max_forward_speed", 0.4)
NAV_MAX_ANGULAR_SPEED = _get("navigation.max_angular_speed", 0.8)
