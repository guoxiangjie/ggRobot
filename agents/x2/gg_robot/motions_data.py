"""X2 静态能力数据 — 权威清单（从 1.0 web/src/config/motions.ts 与 TaskEditor.vue 移植）

这是 agent 能力上报（capabilities.py）的数据源，前端不再硬编码动作/模式/表情表。
来源：AimSDK 文档 tbl-preset-motion（v0.8.0+）与实机验证结论。
"""

# ── 预设动作 ─────────────────────────────
# ⚠️ 所有预设动作必须在 STAND_DEFAULT（稳定站立）模式下执行，否则不动。
# area 编码：1=左臂 2=右臂 3=双臂 11=全身；4=头部(4001/4002 待实机验证)
MOTION_LIST = [
    # 手臂动作（area 1/2/3）
    {"motion": 1002, "area": 2, "name": "右手挥手"},
    {"motion": 1002, "area": 1, "name": "左手挥手"},
    {"motion": 1001, "area": 2, "name": "右手举手"},
    {"motion": 1001, "area": 1, "name": "左手举手"},
    {"motion": 1003, "area": 2, "name": "右手握手"},
    {"motion": 1003, "area": 1, "name": "左手握手"},
    {"motion": 1004, "area": 2, "name": "右手飞吻"},
    {"motion": 1004, "area": 1, "name": "左手飞吻"},
    {"motion": 1007, "area": 3, "name": "双手比心"},
    {"motion": 1007, "area": 2, "name": "右手比心"},
    {"motion": 1007, "area": 1, "name": "左手比心"},
    {"motion": 1008, "area": 2, "name": "右手击掌"},
    {"motion": 1008, "area": 1, "name": "左手击掌"},
    {"motion": 1010, "area": 3, "name": "双手平举"},
    {"motion": 1010, "area": 2, "name": "右手平举"},
    {"motion": 1010, "area": 1, "name": "左手平举"},
    {"motion": 1011, "area": 2, "name": "胸前右手挥手"},
    {"motion": 1011, "area": 1, "name": "胸前左手挥手"},
    {"motion": 1013, "area": 2, "name": "右手敬礼"},
    {"motion": 1013, "area": 1, "name": "左手敬礼"},
    # 全身动作（area 11）
    {"motion": 3017, "area": 11, "name": "鼓掌"},
    {"motion": 3031, "area": 11, "name": "拜拜"},
    {"motion": 3001, "area": 11, "name": "鞠躬"},
    {"motion": 3007, "area": 11, "name": "动感光波"},
    {"motion": 3008, "area": 11, "name": "拥抱"},
    {"motion": 3009, "area": 11, "name": "双手打叉"},
    {"motion": 3011, "area": 11, "name": "加油"},
    {"motion": 3024, "area": 11, "name": "挠头"},
    {"motion": 3025, "area": 11, "name": "抓屁股"},
    # 头部动作（area 4；SDK 枚举有 4001/4002 但文档 tbl 未列，待实机验证）
    {"motion": 4001, "area": 4, "name": "点头"},
    {"motion": 4002, "area": 4, "name": "摇头"},
]

AREA_LABEL = {1: "左臂", 2: "右臂", 3: "双臂", 11: "全身", 4: "头部"}

# ── 运动模式 ─────────────────────────────
# SIT_DOWN / ZERO_TORQUE 后端只认数字 action_value，调用必须携带 numeric_value
MODE_LIST = [
    {"id": "STAND_DEFAULT", "name": "稳定站立"},
    {"id": "LOCOMOTION_DEFAULT", "name": "走跑"},
    {"id": "DAMPING_DEFAULT", "name": "阻尼"},
    {"id": "JOINT_DEFAULT", "name": "位控站立"},
    {"id": "PASSIVE_DEFAULT", "name": "零力矩/急停"},
    {"id": "SIT_DOWN", "name": "坐下", "numeric_value": 2000},
    {"id": "ZERO_TORQUE", "name": "零力矩", "numeric_value": 4},
]

# ── 面部表情 ─────────────────────────────
EMOJI_LIST = [
    {"id": 1, "name": "眨眼"}, {"id": 10, "name": "平静"}, {"id": 20, "name": "游戏"},
    {"id": 30, "name": "卖萌"}, {"id": 40, "name": "闭眼"}, {"id": 50, "name": "睁眼"},
    {"id": 60, "name": "无聊"}, {"id": 80, "name": "睡着"}, {"id": 90, "name": "快乐"},
    {"id": 100, "name": "加倍开心"}, {"id": 110, "name": "悲伤"}, {"id": 120, "name": "同情"},
    {"id": 130, "name": "疑惑"}, {"id": 140, "name": "震惊"}, {"id": 150, "name": "撒娇"},
    {"id": 160, "name": "严肃"}, {"id": 170, "name": "思考"}, {"id": 180, "name": "愤怒"},
    {"id": 190, "name": "加倍愤怒"}, {"id": 200, "name": "崇拜"}, {"id": 220, "name": "充电"},
]

# ── 速度档位（SDK 轴范围：forward/lateral ±0.2~1.0 m/s，angular ±0.1~1.0 rad/s）──
GEAR_PRESETS = [
    {"id": "slow", "name": "慢速", "forward": 0.3, "lateral": 0.4, "angular": 0.3},
    {"id": "mid", "name": "中速", "forward": 0.5, "lateral": 0.6, "angular": 0.5},
    {"id": "fast", "name": "快速", "forward": 0.8, "lateral": 0.8, "angular": 0.8},
]

# ── 开发者模式迁移白名单（文档 5.6；勿使用未提及的系统模式）──
MIGRATE_STATES = ["Ready", "Develop_Audio_Linux", "Develop_Audio_ROS", "Develop_Nav", "Develop_MC"]


def motion_key(motion: int, area: int) -> str:
    """契约 action_id 复合键 motion:area"""
    return f"{motion}:{area}"
