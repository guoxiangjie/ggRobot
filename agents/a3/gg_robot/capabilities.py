"""A3 能力契约上报 — catalog v1 格式 + A3 扩展类型（nav/dance/motion.advance）

公共类型与 X2 同名同参（前端零改动）；扩展类型按上报与否条件渲染（Phase B 落 catalog/前端）。
"""

from . import __version__
from . import motions_data

CATALOG_VERSION = 1
MODEL = "a3-ultra"


def _motion_actions() -> list[dict]:
    out = []
    for m in motions_data.get_motions():
        a = {
            "id": m["id"],           # A3: 动作 id = 资源文件绝对路径
            "name": m["name"],
            "requires_stand": False,  # A3 动作经 motion_player，无 STAND 前置约束
        }
        if m.get("duration"):
            a["duration"] = float(m["duration"])   # 真实时长（秒）
        out.append(a)
    return out


def _cameras() -> list[dict]:
    try:
        from . import node as node_mod
        if node_mod._node is not None:
            return [{"id": c["id"], "label": c["name"], "topic": c["topic"],
                     "active": c["id"] == node_mod._node._active_camera}
                    for c in node_mod._node.list_cameras()]
    except Exception:
        pass
    from . import config as cfg
    return [{"id": cid, "label": name, "topic": topic, "active": False}
            for cid, topic, name in cfg.CAMERA_LIST]


def build_capabilities() -> dict:
    from .security import agent_sn
    return {
        "catalog_version": CATALOG_VERSION,
        "sn": agent_sn() or "unknown",
        "model": MODEL,
        "version": __version__,
        "capabilities": [
            # ── 公共类型（X2/A3 同构，前端即用）──
            {"type": "speech.tts", "params": {}},
            {"type": "motion.preset", "params": {"actions": _motion_actions()}},
            {"type": "locomotion.velocity", "params": {
                "axes": ["forward", "lateral", "angular"],
                "send_interval_ms": 50,
                "gears": motions_data.GEAR_PRESETS,
            }},
            {"type": "mode.switch", "params": {"modes": motions_data.MODE_LIST}},
            {"type": "status.battery", "params": {"topic": "sensor.battery", "dual": True}},
            {"type": "status.joints", "params": {"topic": "sensor.joints"}},
            {"type": "status.emergency", "params": {"topic": "sensor.emergency"}},
            {"type": "perception.camera", "params": {
                "cameras": _cameras(),
                "frame_interval_ms": 200,
            }},
            # ── A3 扩展类型（Phase B：contracts/catalog.json + 前端步骤类型）──
            {"type": "nav.goto", "params": {
                "kinds": ["goal", "pose2d", "linear_goal", "linear_pose2d", "precise_goal"],
            }},
            {"type": "nav.control", "params": {"ops": ["pause", "resume", "cancel"]}},
            {"type": "dance.play", "params": {"skills": motions_data.get_skills()}},
            {"type": "motion.advance", "params": {"ops": ["pause", "resume", "stop", "repeat"]}},
            {"type": "map.manage", "params": {"supported": True}},   # 地图列表/2D/拓扑点
            {"type": "slam.mapping", "params": {"supported": True, "realtime_rpc": True}},
        ],
    }
