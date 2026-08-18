"""任务数据校验 — 并行组冲突检查（保存/运行前调用）

规则：
- 并行组内多个 velocity → 冲突（互相覆盖目标速度）
- 并行组内多个 tts → 冲突（语音互相打断）
- 并行组内 motion 区域重复 → 冲突（同区域动作抢占）
- 并行组内 mode 与 velocity/motion 并行 → 冲突（切换模式会影响速度/动作执行）
- 递归检查分支块内嵌套的并行组
"""

import logging

logger = logging.getLogger(__name__)


def _iter_parallel_blocks(steps: list):
    """递归收集所有并行组块（含分支块 then/else 内嵌套的）"""
    for block in steps or []:
        btype = block.get("type")
        if btype == "parallel":
            yield block
        elif btype == "branch":
            yield from _iter_parallel_blocks(block.get("then") or [])
            yield from _iter_parallel_blocks(block.get("else") or [])


def validate_task(task: dict) -> list[str]:
    """返回冲突错误列表（空=通过）"""
    errors: list[str] = []
    steps = task.get("steps") or []

    # 普通顺序流中的并行组冲突
    for gi, group in enumerate(_iter_parallel_blocks(steps)):
        branches = group.get("branches") or []
        members = [s for b in branches for s in (b.get("steps") or [])]
        types = [s.get("type") for s in members]
        label = f"并行组[{gi + 1}]"

        if types.count("velocity") > 1:
            errors.append(f"{label} 内多个速度控制会互相覆盖，请拆成顺序步骤")
        if types.count("tts") > 1:
            errors.append(f"{label} 内多个语音播报会互相打断，请拆开或去掉一个")
        if "mode" in types and any(t in ("velocity", "motion") for t in types):
            errors.append(f"{label} 内模式切换不能与速度/动作并行")
        areas = [s.get("area") for s in members if s.get("type") == "motion" and s.get("area")]
        if len(areas) != len(set(areas)):
            errors.append(f"{label} 内多个预设动作区域冲突（同一身体区域同时执行）")

    return errors
