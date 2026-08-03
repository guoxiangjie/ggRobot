"""AI 生成编排任务 — 可插拔：none（本地规则）/ openai（OpenAI 兼容接口）

本地规则覆盖常用指令（打招呼/跳舞/巡逻/比心/挥手/鞠躬等），离线可用；
配置 robot.yaml ai.provider=openai 后走 LLM 生成，并在服务端做步骤校验
（动作组合归一化、未知类型过滤），避免生成无效动作。
"""

import json
import logging
import re
import urllib.request

from ..config import AI_PROVIDER, AI_BASE_URL, AI_API_KEY, AI_MODEL
from .motions import MOTION_COMBOS, is_valid, normalize_step_motions

logger = logging.getLogger(__name__)

_STEP_TYPES = {"tts", "motion", "emoji", "velocity", "wait", "mode", "volume", "media", "linkcraft", "http"}


# ═══════════════════════════════════════════
# 本地规则生成（离线兜底）
# ═══════════════════════════════════════════

_RULES: list[tuple[list[str], str, callable]] = [
    (["跳舞", "舞蹈", "跳支舞", "跳个舞"], "跳舞", lambda: [
        {"type": "tts", "text": "让我为你跳支舞吧", "delay": 0},
        {"type": "emoji", "emotion_id": 100, "mode": 2, "delay": 0},
        {"type": "wait", "duration": 1.0},
        {"type": "motion", "area": 3, "motion_id": 1007, "delay": 2.5},   # 双手比心
        {"type": "motion", "area": 2, "motion_id": 1004, "delay": 2.0},   # 右手飞吻
        {"type": "motion", "area": 11, "motion_id": 3007, "delay": 2.0},  # 动感光波
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
        {"type": "motion", "area": 11, "motion_id": 3001, "delay": 2.0},   # 鞠躬
        {"type": "tts", "text": "很高兴认识你", "delay": 0},
        {"type": "motion", "area": 2, "motion_id": 1002, "delay": 1.5},    # 右手挥手
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

_SYSTEM_PROMPT = f"""你是机器人任务编排助手。用户会用自然语言描述想让机器人执行的动作，
请只输出一个 JSON 对象（不要 Markdown 代码块、不要任何多余文字），格式：
{{"name": "简短任务名", "desc": "一句话描述", "steps": [步骤...]}}
步骤 type 只能是：{sorted(_STEP_TYPES)}
预设动作必须使用下方合法组合（motion_id+area 绑定）：{[(m, a) for m, a, _ in MOTION_COMBOS]}
常用字段：tts(text,delay)、motion(motion_id,area,delay)、emoji(emotion_id,mode,delay)、
velocity(forward,lateral,angular,duration)、mode(action_desc)、volume(volume)、
wait(duration)、media(file_name)、linkcraft(resource_key)、http(method,url)。
步骤不超过 10 个。"""


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
        "max_tokens": 1500,
    }).encode()
    req = urllib.request.Request(url, data=body, headers={
        "Authorization": f"Bearer {AI_API_KEY}",
        "Content-Type": "application/json",
    }, method="POST")
    with urllib.request.urlopen(req, timeout=45) as resp:
        data = json.loads(resp.read().decode())
    content = data["choices"][0]["message"]["content"]
    content = re.sub(r"^```(?:json)?\s*|```\s*$", "", content.strip(), flags=re.M)
    m = re.search(r"\{.*\}", content, re.S)
    if not m:
        raise ValueError("AI 返回内容无法解析为 JSON")
    return json.loads(m.group(0))


# ═══════════════════════════════════════════
# 步骤校验 / 入口
# ═══════════════════════════════════════════

def _sanitize_task(raw: dict) -> dict:
    steps: list[dict] = []
    for s in (raw.get("steps") or [])[:20]:
        if not isinstance(s, dict) or s.get("type") not in _STEP_TYPES:
            continue
        step = dict(s)
        normalize_step_motions(step)
        if step.get("type") == "motion" and not is_valid(step.get("motion_id", 0), step.get("area", 0)):
            logger.warning(f"  ⚠️ AI 生成了无效动作组合，已剔除: {step}")
            continue
        if step.get("type") == "tts":
            step["text"] = str(step.get("text", ""))[:200]
        steps.append(step)
    return {
        "name": str(raw.get("name", "") or "")[:30] or "AI任务",
        "desc": str(raw.get("desc", "") or "")[:100],
        "steps": steps,
    }


def generate_task(prompt: str) -> dict:
    """生成编排任务（LLM 优先，失败/未配置回退本地规则）"""
    provider = (AI_PROVIDER or "none").strip().lower()
    if provider == "openai":
        try:
            task = _sanitize_task(_llm_generate(prompt))
            if task["steps"]:
                logger.info(f"🤖 AI 生成任务: {task['name']}（{len(task['steps'])} 步）")
                return task
            logger.warning("AI 返回空步骤，回退本地规则")
        except Exception as e:
            logger.warning(f"AI 生成失败，回退本地规则: {e}")
    return _rule_generate(prompt)
