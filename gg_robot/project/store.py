"""自由任务（项目）存储 — JSON 文件 CRUD

项目文件存放在用户数据目录 projects/ 下（默认 ~/ggRobot-data/projects/），每个项目一个 .json 文件。
一个项目 = 一组无序节点（Node），手动单点执行（节点之间没有上下流关系）。
"""

import json
import logging
import uuid
from datetime import datetime
from pathlib import Path

from ..config import DATA_DIR

logger = logging.getLogger(__name__)

PROJECTS_DIR = DATA_DIR / "projects"
PROJECTS_DIR.mkdir(parents=True, exist_ok=True)


def _path(project_id: str) -> Path:
    return PROJECTS_DIR / f"{project_id}.json"


def _read_json(path: Path) -> dict:
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def _write_json(path: Path, data: dict):
    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)


def list_projects() -> list[dict]:
    """列出所有项目（摘要，不含完整节点）"""
    out = []
    for path in sorted(PROJECTS_DIR.glob("*.json")):
        try:
            d = _read_json(path)
            out.append({
                "id": d.get("id", path.stem),
                "name": d.get("name", path.stem),
                "desc": d.get("desc", ""),
                "icon": d.get("icon", "📂"),
                "node_count": len(d.get("nodes", [])),
                "updated_at": d.get("updated_at", ""),
            })
        except Exception as e:
            logger.warning(f"跳过损坏的项目文件 {path.name}: {e}")
    return out


def get_project(project_id: str) -> dict | None:
    p = _path(project_id)
    if not p.exists():
        return None
    return _read_json(p)


def save_project(data: dict) -> dict:
    """新建/更新项目（给节点补 id/默认字段）"""
    pid = data.get("id") or str(uuid.uuid4())[:8]
    data["id"] = pid
    data.setdefault("name", "未命名项目")
    data.setdefault("desc", "")
    data.setdefault("icon", "📂")
    nodes = data.get("nodes") or []
    for i, n in enumerate(nodes):
        if not n.get("id"):
            n["id"] = f"n{i + 1}"
        n.setdefault("name", "")
        n.setdefault("icon", "")
    data["nodes"] = nodes
    data["updated_at"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    _write_json(_path(pid), data)
    logger.info(f"📁 项目已保存: {data['name']} ({pid}, {len(nodes)} 节点)")
    return data


def delete_project(project_id: str) -> bool:
    p = _path(project_id)
    if p.exists():
        p.unlink()
        logger.info(f"🗑️ 项目已删除: {project_id}")
        return True
    return False


def init_builtin_projects():
    """首次运行创建示例项目"""
    if list(PROJECTS_DIR.glob("*.json")):
        return
    builtins = [
        {
            "id": "quick_actions",
            "name": "快捷动作台",
            "desc": "常用动作一键执行",
            "icon": "⚡",
            "nodes": [
                {"name": "你好", "icon": "🗣️", "type": "tts", "text": "你好", "wait_done": True, "motion_wait": True, "delay": 0.5, "motions": [], "emojis": []},
                {"name": "鞠躬", "icon": "🙇", "type": "motion", "area": 11, "motion_id": 3001, "delay": 1},
                {"name": "挥手", "icon": "👋", "type": "motion", "area": 2, "motion_id": 1002, "delay": 1},
                {"name": "比心", "icon": "❤️", "type": "motion", "area": 3, "motion_id": 1007, "delay": 1},
                {"name": "快乐", "icon": "😊", "type": "emoji", "emotion_id": 90, "mode": 1, "delay": 0.5},
                {"name": "站立", "icon": "🧍", "type": "mode", "action_desc": "STAND_DEFAULT", "delay": 1},
                {"name": "前进2秒", "icon": "🚶", "type": "velocity", "forward": 0.3, "lateral": 0, "angular": 0, "duration": 2},
            ],
        },
    ]
    for p in builtins:
        save_project(p)
    logger.info(f"📦 已创建 {len(builtins)} 个内置项目")


def migrate_legacy_motions():
    """一次性修复已保存项目节点里的旧动作数据（area=0 / 旧 ID 3004 等），幂等。"""
    from .motions import normalize_step_motions
    fixed = 0
    for path in PROJECTS_DIR.glob("*.json"):
        try:
            data = _read_json(path)
            changed = False
            for node in data.get("nodes", []):
                changed = normalize_step_motions(node) or changed
            if changed:
                _write_json(path, data)
                fixed += 1
        except Exception as e:
            logger.warning(f"跳过项目文件 {path.name}: {e}")
    if fixed:
        logger.info(f"🕺 已自动修复 {fixed} 个历史项目中的旧动作组合")
