"""能力契约上报 — contracts/catalog.json v1 格式（真源见 contracts/，此处组装 X2 实例数据）

GET /api/capabilities 返回结构（平台/前端按能力类型动态组装 UI）：
{catalog_version, sn, model, version, capabilities: [{type, params: {...}}]}
"""

from . import __version__
from . import motions_data

CATALOG_VERSION = 1
MODEL = "x2"


def _motion_actions() -> list[dict]:
    return [
        {
            "id": motions_data.motion_key(m["motion"], m["area"]),
            "name": m["name"],
            "area": m["area"],
            "requires_stand": True,  # 所有预设动作都必须 STAND 模式前置
        }
        for m in motions_data.MOTION_LIST
    ]


def _cameras() -> list[dict]:
    """优先从运行中的 node 读（含 active 态），未就绪时静态清单"""
    try:
        from . import node as node_mod
        if node_mod._node is not None:
            return [
                {"id": cid, "label": cfg["label"], "topic": cfg["topic"],
                 "active": cfg.get("active", False)}
                for cid, cfg in node_mod._node._camera_topics.items()
            ]
    except Exception:
        pass
    return [
        {"id": "rgbd_front", "label": "RGBD 前视（推荐）", "topic": "/aima/hal/sensor/rgbd_head_front/rgb_image/compressed", "active": False},
        {"id": "rgb_rear", "label": "RGB 后视", "topic": "/aima/hal/sensor/rgb_head_rear/rgb_image/compressed", "active": False},
        {"id": "stereo_left", "label": "双目 左", "topic": "/aima/hal/sensor/stereo_head_front_left/rgb_image/compressed", "active": False},
        {"id": "stereo_right", "label": "双目 右", "topic": "/aima/hal/sensor/stereo_head_front_right/rgb_image/compressed", "active": False},
    ]


def build_capabilities() -> dict:
    from .security import agent_sn
    return {
        "catalog_version": CATALOG_VERSION,
        "sn": agent_sn() or "unknown",
        "model": MODEL,
        "version": __version__,
        "capabilities": [
            {"type": "speech.tts", "params": {}},
            {"type": "motion.preset", "params": {"actions": _motion_actions()}},
            {"type": "locomotion.velocity", "params": {
                "axes": ["forward", "lateral", "angular"],
                "send_interval_ms": 50,
                "gears": motions_data.GEAR_PRESETS,
            }},
            {"type": "mode.switch", "params": {"modes": motions_data.MODE_LIST}},
            {"type": "expression.face", "params": {"emotions": motions_data.EMOJI_LIST}},
            {"type": "media.play", "params": {"kinds": ["audio", "video"]}},
            {"type": "perception.camera", "params": {
                "cameras": _cameras(),
                "frame_interval_ms": 100,
            }},
            {"type": "slam.mapping", "params": {"supported": True}},
            {"type": "slam.localize", "params": {"supported": True}},
            {"type": "status.battery", "params": {"topic": "sensor.battery"}},
            {"type": "status.imu", "params": {"topic": "sensor.imu"}},
            {"type": "status.joints", "params": {"topic": "sensor.joints"}},
            {"type": "status.system", "params": {"migrate_states": motions_data.MIGRATE_STATES}},
        ],
    }
