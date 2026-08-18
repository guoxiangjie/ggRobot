"""任务数据 v2 迁移 — 老任务（tts 挂载动作/表情）→ 并行块

只在内存中转换（engine.run 时调用），不改写用户文件——
编辑器 UI 升级（P2）之后再落盘 version:2。
转换幂等：已转换的并行块不再重复处理。
"""

import logging

logger = logging.getLogger(__name__)


def ensure_task_v2(task: dict) -> dict:
    """把老式 tts 挂载转成并行组块；已是 v2 或无可转内容则原样返回。"""
    if task.get("version") == 2:
        return task

    steps = task.get("steps") or []
    new_steps = []
    converted = False
    for i, step in enumerate(steps):
        if step.get("type") == "tts" and (step.get("motions") or step.get("emojis")):
            mounts = []
            for m in step.get("motions") or []:
                if m.get("kind") == "linkcraft":
                    mounts.append({
                        "type": "linkcraft",
                        "resource_key": m.get("resource_key", ""),
                        "version": m.get("version", ""),
                        "resource_type": m.get("resource_type", ""),
                        "name": m.get("name", ""),
                    })
                else:
                    mounts.append({
                        "type": "motion",
                        "motion_id": m.get("motion_id", 0),
                        "area": m.get("area", 0),
                    })
            for e in step.get("emojis") or []:
                mounts.append({"type": "emoji", "emotion_id": e, "mode": 1})

            tts_step = {k: v for k, v in step.items() if k not in ("motions", "emojis")}
            branches = [{"id": "p1", "steps": [tts_step]}] + [
                {"id": f"p{k + 2}", "steps": [s]} for k, s in enumerate(mounts)
            ]
            new_steps.append({
                "id": step.get("id") or f"g{i}",
                "type": "parallel",
                "name": "并行执行",
                "branches": branches,
            })
            converted = True
        else:
            new_steps.append(step)

    if converted:
        task["steps"] = new_steps
        task["version"] = 2
        logger.info(f"🔄 任务 {task.get('id') or task.get('name', '?')} 已迁移为 v2 并行块")
    else:
        task["version"] = 2  # 标记 v2 但保持原结构（无挂载也要标记，避免重复检查）
    return task
