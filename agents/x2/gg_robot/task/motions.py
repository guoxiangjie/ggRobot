"""预设动作权威组合表 — 与 web/src/config/motions.ts 保持同步（v0.8.0+）

只有下面这些 (motion, area) 组合在实机上有效，其他会被机器人静默忽略
（这正是"编排动作大多不执行"的根因：历史任务里存着 area=0 / 旧 ID 3004）。
area 编码：1=左臂 2=右臂 3=双臂 11=全身（4=头部 4001/4002 待实机验证）。
⚠️ 所有预设动作必须在 STAND_DEFAULT（稳定站立）模式下执行。
"""

# (motion_id, area, 名称) —— 顺序与前端 motions.ts 保持一致
MOTION_COMBOS: list[tuple[int, int, str]] = [
    (1002, 2, "右手挥手"), (1002, 1, "左手挥手"),
    (1001, 2, "右手举手"), (1001, 1, "左手举手"),
    (1003, 2, "右手握手"), (1003, 1, "左手握手"),
    (1004, 2, "右手飞吻"), (1004, 1, "左手飞吻"),
    (1007, 3, "双手比心"), (1007, 2, "右手比心"), (1007, 1, "左手比心"),
    (1008, 2, "右手击掌"), (1008, 1, "左手击掌"),
    (1010, 3, "双手平举"), (1010, 2, "右手平举"), (1010, 1, "左手平举"),
    (1011, 2, "胸前右手挥手"), (1011, 1, "胸前左手挥手"),
    (1013, 2, "右手敬礼"), (1013, 1, "左手敬礼"),
    (3017, 11, "鼓掌"), (3031, 11, "拜拜"), (3001, 11, "鞠躬"),
    (3007, 11, "动感光波"), (3008, 11, "拥抱"), (3009, 11, "双手打叉"),
    (3011, 11, "加油"), (3024, 11, "挠头"), (3025, 11, "抓屁股"),
    (4001, 4, "点头"), (4002, 4, "摇头"),
]

_COMBOS = {(m, a): name for m, a, name in MOTION_COMBOS}

# motion_id → 默认 area（取表内第一条；area 缺省/为 0 时自动补）
_DEFAULT_AREA: dict[int, int] = {}
for _m, _a, _ in MOTION_COMBOS:
    _DEFAULT_AREA.setdefault(_m, _a)

# 旧 ID 映射（v0.8.0 变更）：3004=比心 → 1007
_OLD_ID_MAP = {3004: 1007}


def is_valid(motion_id: int, area: int) -> bool:
    return (int(motion_id), int(area)) in _COMBOS


def default_area(motion_id: int) -> int:
    return _DEFAULT_AREA.get(int(motion_id), 0)


def motion_name(motion_id: int, area: int) -> str:
    return _COMBOS.get((int(motion_id), int(area)), f"动作#{motion_id}")


def normalize_motion(motion_id, area=0):
    """编排执行前的动作兜底归一化：旧 ID 映射 + area=0 自动补默认 area。

    返回 (motion_id, area, valid)；valid=False 表示组合无效，调用方应跳过并告警。
    这能自动修复机器人上历史任务文件里的旧数据（area=0 / 3004），无需用户重编任务。
    """
    motion_id = int(motion_id)
    area = int(area or 0)
    motion_id = _OLD_ID_MAP.get(motion_id, motion_id)
    if area == 0:
        area = _DEFAULT_AREA.get(motion_id, 0)
    return motion_id, area, is_valid(motion_id, area)


def normalize_step_motions(step: dict) -> bool:
    """就地归一化单个步骤/节点里的动作字段（motion 步骤 + tts 挂载动作），返回是否有修改。"""
    changed = False
    if step.get("type") == "motion":
        mid, area, valid = normalize_motion(step.get("motion_id", 0), step.get("area", 0))
        if valid and (mid != step.get("motion_id") or area != step.get("area")):
            step["motion_id"], step["area"] = mid, area
            changed = True
    elif step.get("type") == "tts":
        for m in step.get("motions") or []:
            if m.get("kind", "preset") != "linkcraft":
                mid, area, valid = normalize_motion(m.get("motion_id", 0), m.get("area", 0))
                if valid and (mid != m.get("motion_id") or area != m.get("area")):
                    m["motion_id"], m["area"] = mid, area
                    changed = True
    return changed


# ── 预设动作经验时长（秒）─────────────────────────
# SDK 无预设动作完成信号（无完成话题/无 task_id 查询；GetMcAction.status 是运动模式
# 状态，是否反映单个预设动作存疑），用作 wait_motion_done 失效时的兜底估时。
# 按 motion_id 段分类，值留余量；宁可偏长半秒，不可短了漏动作。实机校准。
_MOTION_DURATIONS: dict[int, float] = {
    # 头部：点头/摇头（短）
    4001: 1.5, 4002: 1.5,
    # 基础手臂（单臂 1001-1013）：举手/挥手/握手/飞吻/击掌/平举/胸前挥手/敬礼
    1001: 2.0, 1002: 2.0, 1003: 2.5, 1004: 2.0,
    1007: 2.5, 1008: 2.0, 1010: 2.0, 1011: 2.0, 1013: 2.0,
    # 转身挥手
    2001: 3.0,
    # 全身简单：鞠躬/鼓掌/拜拜
    3001: 2.5, 3017: 2.5, 3031: 2.5,
    # 全身交互：动感光波/拥抱/双手打叉/加油/挠头/抓屁股
    3007: 3.5, 3008: 3.5, 3009: 3.5, 3011: 3.5, 3024: 3.5, 3025: 3.5,
    # 跳舞（长）
    3013: 4.0, 3014: 4.0,
}
_DEFAULT_MOTION_DURATION = 2.5


def motion_duration(motion_id: int, area: int = 0) -> float:
    """预设动作经验时长（秒）—— 动作等待的估时兜底。

    wait_motion_done 轮询 GetMcAction.status 若 grace 期内未进入 RUNNING（status
    不反映此动作），则按此时长 sleep 兜底，避免连续动作互相打断而漏执行。
    """
    base = _MOTION_DURATIONS.get(int(motion_id), _DEFAULT_MOTION_DURATION)
    if int(area or 0) == 3:  # 双臂动作略长
        base = max(base, 2.5)
    return base
