"""A3 agent 配置 — 环境变量优先，robot.yaml 兜底（复用 X2 的简易 YAML 加载约定）"""

import os
import logging
from pathlib import Path

logger = logging.getLogger(__name__)


def _load_yaml(path: Path) -> dict:
    """简易 YAML 解析器，只支持嵌套 key: value（无需 pyyaml；与 X2 config 同款）"""
    if not path.exists():
        return {}
    result = {}
    stack = [(result, -1)]
    with open(path) as f:
        for line in f:
            stripped = line.rstrip()
            if not stripped or stripped.startswith("#") or stripped.startswith("---"):
                continue
            indent = len(line) - len(line.lstrip())
            key, _, val = stripped.partition(":")
            key = key.strip()
            val = val.strip()
            comment_at = val.find(" #")
            if comment_at != -1:
                val = val[:comment_at].rstrip()
            val = val.strip('"').strip("'")
            if val == "":
                child = {}
                result[key] = child
                stack = [(r, i) for r, i in stack if i < indent]
                stack.append((child, indent))
            else:
                while stack and stack[-1][1] >= indent:
                    stack.pop()
                target = stack[-1][0] if stack else result
                if val.lower() in ("true", "false"):
                    val = val.lower() == "true"
                elif val.count(".") == 1 and all(
                    p.isdigit() or (p.startswith("-") and p[1:].isdigit()) for p in val.split(".")
                ):
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
    env_key = f"GGROBOT_{key.upper().replace('.', '_')}"
    if env_key in os.environ:
        return os.environ[env_key]
    parts = key.split(".")
    val = _yaml_config
    for p in parts:
        if isinstance(val, dict):
            val = val.get(p)
        else:
            val = None
            break
    return val if val is not None else default


# ── 三计算单元内网固定 IP（docs/a3-ultra-dev-notes.md）──
HDU_HOST = str(_get("a3.hdu_host", "10.42.10.10"))   # agent 部署地 / 交互 / TTS / 音频 / 资源
MDU_HOST = str(_get("a3.mdu_host", "10.42.10.12"))   # 运控 / 动作命令 / 告警
ADU_HOST = str(_get("a3.adu_host", "10.42.10.11"))   # 地图 / 导航

# ── 速度控制（A3 为比例制 -1.0~1.0；平台 API 统一 m/s，agent 内换算）──
VEL_PUBLISH_RATE = int(_get("velocity.publish_rate", 50))
VEL_MAX_FORWARD = float(_get("velocity.max_forward", 1.0))    # m/s，映射 forward 比例 = v / max
VEL_MAX_LATERAL = float(_get("velocity.max_lateral", 0.6))
VEL_MAX_ANGULAR = float(_get("velocity.max_angular", 1.0))    # rad/s
# A3 日常行走建议 <1.2 m/s（官方规格），默认上限 1.0 保守

# ── RPC 超时/重试 ──
RPC_TIMEOUT = float(_get("rpc.timeout", 3.0))
RPC_QUERY_RETRIES = int(_get("rpc.query_retries", 2))   # 查询类（幂等）可重试
RPC_CTRL_RETRIES = int(_get("rpc.ctrl_retries", 0))     # 控制类（非幂等：TTS/动作）不重试

# ── 相机（Phase C：sensor_msgs/Image → JPEG 推流）──
# ⚠️ raw Image 30FPS≈265MB/s DDS 流量，常订阅疑似触发内部通信告警（实机验证中）；
#    默认关闭，前端打开相机页时再经 API 显式开启（camera.enable=true 供调试）
CAMERA_ENABLED = bool(_get("camera.enable", False))
CAMERA_FPS = int(_get("camera.fps", 5))
CAMERA_JPEG_QUALITY = int(_get("camera.jpeg_quality", 60))
CAMERA_LIST = (
    ("head_stereo_left", "/hal/head_stereo_left_fisheye_camera/rgb", "头部双目·左"),
    ("head_stereo_right", "/hal/head_stereo_right_fisheye_camera/rgb", "头部双目·右"),
    ("chest_front", "/hal/chest_front_d457_camera/rgb", "胸前深度"),
    ("waist_front", "/hal/waist_front_d415_camera/rgb", "腰部前向"),
    ("head_left", "/hal/head_left_fisheye_camera/rgb", "头部左鱼眼"),
    ("head_right", "/hal/head_right_fisheye_camera/rgb", "头部右鱼眼"),
    ("head_rear", "/hal/head_rear_fisheye_camera/rgb", "头部后鱼眼"),
)

# ── 订阅开关矩阵（A3531001 排查二分法：默认全关最小模式，逐项打开定位元凶）──
SUBS_ARM = bool(_get("subs.arm", False))            # 臂关节状态（小消息）
SUBS_BMS = bool(_get("subs.bms", False))            # 电池（小消息）
SUBS_EMERGENCY = bool(_get("subs.emergency", False))  # 急停（小消息）
SUBS_TTS_STATUS = bool(_get("subs.tts_status", False))  # TTS 播报状态
SUBS_AUDIO = bool(_get("subs.audio", False))        # VAD 降噪音频（32KB/s）
# 相机开关已有 CAMERA_ENABLED（raw 265MB/s，最强嫌疑）

# ── 2.0 agent 通用 ──
AGENT_CONF_PATH = Path(os.environ.get(
    "GG_AGENT_CONF", Path.home() / ".config" / "ggrobot-agent.conf"))
AGENT_PORT = int(os.environ.get("GG_AGENT_PORT") or _get("server.port", 8300))

# 动作清单缓存刷新（GetResourceList 限频，长缓存 + 手动刷新端点）
MOTIONS_CACHE_TTL = float(_get("motions.cache_ttl", 300))
