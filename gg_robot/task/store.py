"""任务存储 — JSON 文件 CRUD

任务文件存放在 ~/ggRobot/tasks/ 目录下，每个任务一个 .json 文件。
"""

import json
import logging
import uuid
from datetime import datetime
from pathlib import Path

logger = logging.getLogger(__name__)

TASKS_DIR = Path.home() / "ggRobot" / "tasks"
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
                {"type": "motion", "area": 0, "motion_id": 1002, "delay": 2.0},
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
                {"type": "motion", "area": 0, "motion_id": 1004, "delay": 2.0},
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
