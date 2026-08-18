"""任务存储 — JSON 文件 CRUD

任务文件存放在用户数据目录 tasks/ 下（默认 ~/ggRobot-data/tasks/，
可用 GGROBOT_DATA_DIR / robot.yaml server.data_dir 覆盖），每个任务一个 .json 文件。
"""

import json
import logging
import uuid
from datetime import datetime
from pathlib import Path

from ..config import DATA_DIR

logger = logging.getLogger(__name__)

TASKS_DIR = DATA_DIR / "tasks"
TASKS_DIR.mkdir(parents=True, exist_ok=True)


def _task_path(task_id: str) -> Path:
    """任务 ID → 文件路径"""
    return TASKS_DIR / f"{task_id}.json"


def _read_json(path: Path) -> dict:
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def _write_json(path: Path, data: dict):
    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)


def list_tasks() -> list[dict]:
    """列出所有任务（返回摘要，不含完整步骤）"""
    tasks = []
    for path in sorted(TASKS_DIR.glob("*.json")):
        try:
            data = _read_json(path)
            tasks.append({
                "id": data.get("id", path.stem),
                "name": data.get("name", path.stem),
                "desc": data.get("desc", ""),
                "step_count": len(data.get("steps", [])),
                "updated_at": data.get("updated_at", ""),
            })
        except Exception as e:
            logger.warning(f"跳过损坏的任务文件 {path.name}: {e}")
    return tasks


def get_task(task_id: str) -> dict | None:
    """获取完整任务"""
    path = _task_path(task_id)
    if not path.exists():
        return None
    return _read_json(path)


def save_task(data: dict) -> dict:
    """保存任务（新建或更新）"""
    task_id = data.get("id") or str(uuid.uuid4())[:8]
    data["id"] = task_id
    data.setdefault("name", "未命名任务")
    data.setdefault("desc", "")
    data.setdefault("steps", [])
    data["updated_at"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    path = _task_path(task_id)
    _write_json(path, data)
    logger.info(f"💾 任务已保存: {data['name']} ({task_id})")
    return data


def delete_task(task_id: str) -> bool:
    """删除任务"""
    path = _task_path(task_id)
    if path.exists():
        path.unlink()
        logger.info(f"🗑️ 任务已删除: {task_id}")
        return True
    return False


def init_builtin_tasks():
    """首次运行时创建内置示例任务"""
    if list(TASKS_DIR.glob("*.json")):
        return  # 已存在则不重复创建

    builtins = [
        {
            "id": "greet",
            "name": "打招呼",
            "desc": "机器人自我介绍：说话→表情→点头→挥手",
            "steps": [
                {"type": "emoji", "emotion_id": 90, "mode": 1},
                {"type": "tts", "text": "你好，我是灵犀X2机器人", "delay": 0.5},
                {"type": "wait", "duration": 0.5},
                {"type": "motion", "area": 11, "motion_id": 3001, "delay": 2.5},  # 鞠躬（v0.8.2头部pitch下线，点头改鞠躬）
                {"type": "tts", "text": "很高兴认识你", "delay": 1.0},
                {"type": "motion", "area": 2, "motion_id": 1002, "delay": 2.0},   # 右手挥手（v0.8.0+ area 无 0，必须 1/2/3/11）
                {"type": "emoji", "emotion_id": 1, "mode": 1},
            ],
        },
        {
            "id": "dance",
            "name": "趣味舞蹈",
            "desc": "播放音乐→比心→飞吻→挥手",
            "steps": [
                {"type": "tts", "text": "让我为你跳支舞吧", "delay": 0.5},
                {"type": "emoji", "emotion_id": 100, "mode": 2},
                {"type": "wait", "duration": 1.0},
                {"type": "motion", "area": 3, "motion_id": 1007, "delay": 2.5},  # 双手比心（v0.8.0 motion 3004→1007）
                {"type": "motion", "area": 2, "motion_id": 1004, "delay": 2.0},   # 右手飞吻
                {"type": "motion", "area": 11, "motion_id": 3007, "delay": 2.0},  # 动感光波（全身 area=11）
                {"type": "emoji", "emotion_id": 90, "mode": 1},
            ],
        },
        {
            "id": "patrol",
            "name": "短距离巡逻",
            "desc": "站立→前进→转身→后退→恢复",
            "steps": [
                {"type": "mode", "action_desc": "STAND_DEFAULT", "delay": 1.0},
                {"type": "tts", "text": "开始巡逻", "delay": 0.5},
                {"type": "velocity", "forward": 0.3, "duration": 3.0},
                {"type": "wait", "duration": 0.5},
                {"type": "velocity", "angular": 0.5, "duration": 3.2},
                {"type": "wait", "duration": 0.5},
                {"type": "velocity", "forward": -0.2, "duration": 2.0},
                {"type": "tts", "text": "巡逻结束", "delay": 0.5},
            ],
        },
    ]
    for t in builtins:
        save_task(t)
    logger.info(f"📦 已创建 {len(builtins)} 个内置任务")


def migrate_legacy_motions():
    """一次性修复已保存任务里的旧动作数据（area=0 / 旧 ID 3004 等）。

    机器人上已存在的任务文件可能存着 v0.8.0 之前的无效组合（被静默忽略=不执行）。
    就地归一化并写回，幂等；执行时 steps 里还会再归一化兜底。
    """
    from .motions import normalize_step_motions
    fixed = 0
    for path in TASKS_DIR.glob("*.json"):
        try:
            data = _read_json(path)
            changed = False
            for step in data.get("steps", []):
                changed = normalize_step_motions(step) or changed
            if changed:
                _write_json(path, data)
                fixed += 1
        except Exception as e:
            logger.warning(f"跳过任务文件 {path.name}: {e}")
    if fixed:
        logger.info(f"🕺 已自动修复 {fixed} 个历史任务中的旧动作组合")


# ═══════════════════════════════════════════════
# 手机端按键绑定（{DATA_DIR}/phone_keys.json，单文件 8 位）
# ═══════════════════════════════════════════════

PHONE_KEYS_PATH = DATA_DIR / "phone_keys.json"


def _default_phone_keys() -> dict:
    """8 个空按键位"""
    return {
        "keys": [
            {"slot": i, "name": "", "resource_key": "", "version": "", "resource_type": ""}
            for i in range(8)
        ],
        "updated_at": "",
    }


def load_phone_keys() -> dict:
    """读取手机端按键绑定；文件不存在或损坏返回默认 8 空位"""
    if not PHONE_KEYS_PATH.exists():
        return _default_phone_keys()
    try:
        return _read_json(PHONE_KEYS_PATH)
    except Exception as e:
        logger.warning(f"phone_keys.json 损坏，返回默认: {e}")
        return _default_phone_keys()


def save_phone_keys(data: dict) -> dict:
    """保存手机端按键绑定（补全 8 位 + 字段 + 时间戳）"""
    raw_keys = data.get("keys", [])
    keys = []
    for i in range(8):
        k = raw_keys[i] if i < len(raw_keys) else {}
        keys.append({
            "slot": i,
            "name": k.get("name", ""),
            "resource_key": k.get("resource_key", ""),
            "version": k.get("version", ""),
            "resource_type": k.get("resource_type", ""),
        })
    out = {"keys": keys, "updated_at": datetime.now().strftime("%Y-%m-%d %H:%M:%S")}
    _write_json(PHONE_KEYS_PATH, out)
    bound = sum(1 for k in keys if k["resource_key"])
    logger.info(f"📱 手机按键已保存 ({bound}/8 已绑定)")
    return out
