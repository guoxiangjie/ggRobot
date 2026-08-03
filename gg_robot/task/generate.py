"""AI 生成编排任务 — 可插拔：none（本地规则）/ openai（OpenAI 兼容接口）

模型"知道"编排方法的方式 = 每次请求注入系统提示词：
- 步骤 schema 从 steps.py CAPABILITIES 动态生成（与编辑器/引擎同源，不漂移）
- 预设动作合法组合从 motions.py MOTION_COMBOS 动态生成
- 内置 few-shot 示例：并行组（边走边说）、分支块（接口判断）
- 支持 v2 块结构：parallel(branches) / branch(cond/then/else)

模型输出不直接信任，过 _sanitize_steps 递归消毒：
- 类型白名单过滤、文本截断、motion 组合归一化/非法剔除
- 并行组冲突（多速度/多TTS/同区域动作/模式+速度）整组剔除
- 分支块 cond 截断、then/else 递归消毒
"""

import json
import logging
import re
import urllib.request

from ..config import AI_PROVIDER, AI_BASE_URL, AI_API_KEY, AI_MODEL
from .motions import MOTION_COMBOS, is_valid, normalize_motion
from .steps import CAPABILITIES

logger = logging.getLogger(__name__)

_STEP_TYPES = {"tts", "motion", "emoji", "velocity", "wait", "mode", "volume", "media", "linkcraft", "http"}


# ═══════════════════════════════════════════
# 动态 schema（与编辑器/引擎同源）
# ═══════════════════════════════════════════

def _build_schema_lines() -> list[str]:
    lines = []
    for cap in CAPABILITIES:
        t = cap["type"]
        params = ", ".join(p["name"] for p in cap.get("params", []))
        lines.append(f"- {t}({params})")
    return lines


_SCHEMA_LINES = _build_schema_lines()
_MOTION_LIST = ", ".join(f"{m}:{a}" for m, a, _ in MOTION_COMBOS)

_SYSTEM_PROMPT = f"""你是机器人任务编排助手。用户会用自然语言描述想让机器人执行的动作，请只输出一个 JSON 对象（不要 Markdown 代码块、不要任何多余文字），格式：
{{"name": "简短任务名", "desc": "一句话描述", "steps": [步骤或块...]}}

steps 里的每一项可以是：
1. 普通步骤，type 只能是：{sorted(_STEP_TYPES)}
   字段说明：
{chr(10).join(_SCHEMA_LINES)}
2. 并行组块（多个分支同时执行，全部完成后进入下一步）：
   {{"type": "parallel", "name": "并行组名", "branches": [{{"steps": [普通步骤...]}}, {{"steps": [普通步骤...]}}]}}
3. 分支块（按条件走"是/否"）：
   {{"type": "branch", "cond": "条件表达式", "then": [步骤或块...], "else": [步骤或块...]}}

预设动作必须使用下方合法组合（motion_id:area 绑定，area 1=左臂 2=右臂 3=双臂 11=全身）：
{_MOTION_LIST}

约束：
- 并行组内不要放两个 velocity（互相覆盖）、不要放两个 tts（互相打断）、
  不要 mode 与 velocity/motion 并行、不要同区域两个 motion
- 条件表达式支持 {{{{var.字段}}}} 与 == != > < >= <= in contains and/or/not，
  变量来自 http 步骤的 save_as 响应
- 不要生成 linkcraft / media 步骤（资源/文件名依赖机器人侧，用户会自己选）
- 步骤（含分支内）总计不超过 12 个

示例1（并行"边走边说"）：
{{"name": "边走边说", "steps": [
  {{"type": "parallel", "name": "边走边说", "branches": [
    {{"steps": [{{"type": "velocity", "forward": 0.3, "lateral": 0, "angular": 0, "duration": 4}}]}},
    {{"steps": [{{"type": "tts", "text": "我们出发吧", "wait_done": true}}]}}
  ]}}
]}}

示例2（接口判断分支）：
{{"name": "接口判断", "steps": [
  {{"type": "http", "method": "GET", "url": "http://example.com/api/status", "save_as": "resp"}},
  {{"type": "branch", "cond": "{{{{resp.code}}}} == 1",
    "then": [{{"type": "motion", "motion_id": 1002, "area": 2}}],
    "else": [{{"type": "emoji", "emotion_id": 130}}]}}
]}}"""


# ═══════════════════════════════════════════
# 本地规则生成（离线兜底）
# ═══════════════════════════════════════════

_RULES: list[tuple[list[str], str, callable]] = [
    (["边走边说", "一边走一边说", "边前进边说话"], "边走边说", lambda: [
        {"type": "parallel", "name": "边走边说", "branches": [
            {"steps": [{"type": "velocity", "forward": 0.3, "lateral": 0, "angular": 0, "duration": 4}]},
            {"steps": [{"type": "tts", "text": "我们出发吧", "wait_done": True}]},
        ]},
    ]),
    (["跳舞", "舞蹈", "跳支舞", "跳个舞"], "跳舞", lambda: [
        {"type": "tts", "text": "让我为你跳支舞吧", "delay": 0},
        {"type": "emoji", "emotion_id": 100, "mode": 2, "delay": 0},
        {"type": "wait", "duration": 1.0},
        {"type": "motion", "area": 3, "motion_id": 1007, "delay": 2.5},
        {"type": "motion", "area": 2, "motion_id": 1004, "delay": 2.0},
        {"type": "motion", "area": 11, "motion_id": 3007, "delay": 2.0},
        {"type": "emoji", "emotion_id": 90, "mode": 1, "delay": 0},
    ]),
    (["巡逻"], "巡逻", lambda: [
        {"type": "mode", "action_desc": "STAND_DEFAULT", "delay": 1.0},
        {"type": "tts", "text": "开始巡逻", "delay": 0},
        {"type": "velocity", "forward": 0.3, "lateral": 0, "angular": 0, "duration": 3.0},
        {"type": "wait", "duration": 0.5},
        {"type": "velocity", "forward": 0, "lateral": 0, "angular": 0.5, "duration": 3.2},
        {"type": "wait", "duration": 0.5},
        {"type": "velocity", "forward": -0.2, "lateral": 0, "angular": 0, "duration": 2.0},
        {"type": "tts", "text": "巡逻结束", "delay": 0},
    ]),
    (["打招呼", "自我介绍", "问候", "你好"], "打招呼", lambda: [
        {"type": "emoji", "emotion_id": 90, "mode": 1, "delay": 0},
        {"type": "tts", "text": "你好，我是灵犀X2机器人", "delay": 0},
        {"type": "motion", "area": 11, "motion_id": 3001, "delay": 2.0},
        {"type": "tts", "text": "很高兴认识你", "delay": 0},
        {"type": "motion", "area": 2, "motion_id": 1002, "delay": 1.5},
        {"type": "emoji", "emotion_id": 1, "mode": 1, "delay": 0},
    ]),
    (["比心", "爱心"], "比心", lambda: [
        {"type": "tts", "text": "给你比个心", "delay": 0},
        {"type": "motion", "area": 3, "motion_id": 1007, "delay": 2.0},
    ]),
    (["挥手"], "挥手", lambda: [
        {"type": "tts", "text": "你好呀", "delay": 0},
        {"type": "motion", "area": 2, "motion_id": 1002, "delay": 1.5},
    ]),
    (["鞠躬", "感谢"], "鞠躬", lambda: [
        {"type": "tts", "text": "谢谢大家", "delay": 0},
        {"type": "motion", "area": 11, "motion_id": 3001, "delay": 2.0},
    ]),
    (["飞吻"], "飞吻", lambda: [
        {"type": "tts", "text": "飞吻一个", "delay": 0},
        {"type": "motion", "area": 2, "motion_id": 1004, "delay": 1.5},
    ]),
    (["鼓掌"], "鼓掌", lambda: [
        {"type": "tts", "text": "好棒", "delay": 0},
        {"type": "motion", "area": 11, "motion_id": 3017, "delay": 1.5},
    ]),
    (["加油"], "加油", lambda: [
        {"type": "tts", "text": "加油", "delay": 0},
        {"type": "motion", "area": 11, "motion_id": 3011, "delay": 1.5},
    ]),
    (["拥抱"], "拥抱", lambda: [
        {"type": "tts", "text": "抱一下", "delay": 0},
        {"type": "motion", "area": 11, "motion_id": 3008, "delay": 1.5},
    ]),
    (["再见", "拜拜"], "再见", lambda: [
        {"type": "tts", "text": "再见", "delay": 0},
        {"type": "motion", "area": 11, "motion_id": 3031, "delay": 1.5},
    ]),
    (["前进"], "前进", lambda: [
        {"type": "tts", "text": "前进", "delay": 0},
        {"type": "velocity", "forward": 0.3, "lateral": 0, "angular": 0, "duration": 2.0},
    ]),
    (["后退"], "后退", lambda: [
        {"type": "tts", "text": "后退", "delay": 0},
        {"type": "velocity", "forward": -0.2, "lateral": 0, "angular": 0, "duration": 2.0},
    ]),
    (["右转"], "右转", lambda: [
        {"type": "velocity", "forward": 0, "lateral": 0, "angular": -0.4, "duration": 2.0},
    ]),
    (["左转", "转身"], "转身", lambda: [
        {"type": "velocity", "forward": 0, "lateral": 0, "angular": 0.4, "duration": 2.0},
    ]),
    (["站立"], "站立", lambda: [
        {"type": "mode", "action_desc": "STAND_DEFAULT", "delay": 0},
    ]),
]


def _rule_generate(prompt: str) -> dict:
    steps: list[dict] = []
    used: list[str] = []
    for keywords, name, factory in _RULES:
        if any(k in prompt for k in keywords):
            steps.extend(factory())
            used.append(name)
    if not steps:
        text = (prompt or "").strip()[:80] or "你好"
        steps = [{"type": "tts", "text": text, "delay": 0}]
        used = ["自定义播报"]
    return {
        "name": "AI任务·" + "/".join(used)[:24],
        "desc": (prompt or "").strip()[:80],
        "steps": steps,
    }


# ═══════════════════════════════════════════
# LLM 生成（OpenAI 兼容 chat/completions）
# ═══════════════════════════════════════════

def _llm_generate(prompt: str) -> dict:
    if not (AI_API_KEY and AI_BASE_URL):
        raise ValueError("未配置 AI 接口（robot.yaml ai.api_key / ai.base_url）")
    url = AI_BASE_URL.rstrip("/") + "/chat/completions"
    body = json.dumps({
        "model": AI_MODEL,
        "messages": [
            {"role": "system", "content": _SYSTEM_PROMPT},
            {"role": "user", "content": prompt},
        ],
        "temperature": 0.4,
        "max_tokens": 2000,
    }).encode()
    req = urllib.request.Request(url, data=body, headers={
        "Authorization": f"Bearer {AI_API_KEY}",
        "Content-Type": "application/json",
    }, method="POST")
    with urllib.request.urlopen(req, timeout=60) as resp:
        data = json.loads(resp.read().decode())
    content = data["choices"][0]["message"]["content"]
    content = re.sub(r"^```(?:json)?\s*|```\s*$", "", content.strip(), flags=re.M)
    m = re.search(r"\{.*\}", content, re.S)
    if not m:
        raise ValueError("AI 返回内容无法解析为 JSON")
    return json.loads(m.group(0))


# ═══════════════════════════════════════════
# 递归消毒（普通步骤 / 并行组 / 分支块）
# ═══════════════════════════════════════════

def _sanitize_step(step: dict):
    """消毒单个普通步骤；无效 motion 返回 None"""
    t = step.get("type")
    if t == "motion":
        mid, area, valid = normalize_motion(step.get("motion_id", 0), step.get("area", 0))
        if not valid:
            logger.warning(f"  ⚠️ AI 生成无效动作组合，已剔除: motion={mid} area={area}")
            return None
        step["motion_id"], step["area"] = mid, area
    elif t == "tts":
        step["text"] = str(step.get("text", ""))[:200]
    elif t == "http":
        step["url"] = str(step.get("url", ""))[:300]
    return step


def _parallel_conflicts(group: dict) -> list[str]:
    """并行组内冲突检查（与 validate.py 规则一致，供生成时剔除）"""
    members = [s for b in group.get("branches") or [] for s in (b.get("steps") or []) if isinstance(s, dict)]
    types = [s.get("type") for s in members]
    errs = []
    if types.count("velocity") > 1:
        errs.append("多个速度控制互相覆盖")
    if types.count("tts") > 1:
        errs.append("多个语音播报互相打断")
    if "mode" in types and any(t in ("velocity", "motion") for t in types):
        errs.append("模式切换与速度/动作并行")
    areas = [s.get("area") for s in members if s.get("type") == "motion" and s.get("area")]
    if len(areas) != len(set(areas)):
        errs.append("同区域动作并行")
    return errs


def _sanitize_blocks(steps: list) -> list:
    """递归消毒步骤数组：普通步骤 / parallel / branch 块"""
    out: list[dict] = []
    for s in (steps or [])[:12]:
        if not isinstance(s, dict):
            continue
        t = s.get("type")
        if t == "parallel":
            branches = []
            for b in (s.get("branches") or [])[:6]:
                if not isinstance(b, dict):
                    continue
                bsteps = _sanitize_blocks(b.get("steps") or [])
                if bsteps:
                    branches.append({"id": b.get("id", f"p{len(branches) + 1}"), "steps": bsteps})
            if not branches:
                continue
            group = {"type": "parallel", "name": str(s.get("name", "并行执行"))[:30], "branches": branches}
            errs = _parallel_conflicts(group)
            if errs:
                logger.warning(f"  ⚠️ AI 生成的并行组冲突，整组剔除: {'；'.join(errs)}")
                continue
            out.append(group)
        elif t == "branch":
            then = _sanitize_blocks(s.get("then") or [])
            els = _sanitize_blocks(s.get("else") or [])
            if not then and not els:
                continue
            out.append({
                "type": "branch",
                "cond": str(s.get("cond", ""))[:200],
                "then": then,
                "else": els,
            })
        elif t in _STEP_TYPES:
            step = _sanitize_step(dict(s))
            if step is not None:
                out.append(step)
    return out


def _sanitize_task(raw: dict) -> dict:
    steps = _sanitize_blocks(raw.get("steps") or [])
    return {
        "name": str(raw.get("name", "") or "")[:30] or "AI任务",
        "desc": str(raw.get("desc", "") or "")[:100],
        "steps": steps,
    }


# ═══════════════════════════════════════════
# 入口
# ═══════════════════════════════════════════

def generate_task(prompt: str) -> dict:
    """生成编排任务（LLM 优先，失败/未配置回退本地规则）"""
    provider = (AI_PROVIDER or "none").strip().lower()
    if provider == "openai":
        try:
            task = _sanitize_task(_llm_generate(prompt))
            if task["steps"]:
                logger.info(f"🤖 AI 生成任务: {task['name']}（{len(task['steps'])} 块）")
                return task
            logger.warning("AI 返回空步骤，回退本地规则")
        except Exception as e:
            logger.warning(f"AI 生成失败，回退本地规则: {e}")
    return _rule_generate(prompt)
