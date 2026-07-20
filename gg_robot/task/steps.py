"""任务步骤定义 — 每种 action type → 执行函数

每个 step_handler 签名：
    (node: X2Node, step: dict) -> None

参数从 step dict 中读取，执行具体的 SDK 调用。
"""

import json
import logging
import re

logger = logging.getLogger(__name__)


class StepAbort(Exception):
    """步骤主动要求中止整个任务（如 HTTP 业务码校验失败）"""
    pass


# 变量引用模板：{{var.path}}
_TEMPLATE_RE = re.compile(r"\{\{\s*([\w.]+)\s*\}\}")


def _resolve_var(ctx: dict, path: str):
    """从 ctx['responses'] 解析点分路径（支持 dict 取键、list 取下标），返回 (found, value)"""
    cur = ctx.get("responses", {})
    for part in path.split("."):
        if isinstance(cur, dict) and part in cur:
            cur = cur[part]
        elif isinstance(cur, list):
            try:
                cur = cur[int(part)]
            except (ValueError, IndexError):
                return False, None
        else:
            return False, None
    return True, cur


def _render_value(value, ctx: dict):
    """递归渲染字符串中的 {{var.path}} 占位符（返回新结构，不修改原值）"""
    if isinstance(value, str):
        def repl(m):
            path = m.group(1)
            found, val = _resolve_var(ctx, path)
            if not found:
                logger.warning(f"  ⚠️ 变量 {{{{{path}}}}} 未找到，替换为空")
                return ""
            if isinstance(val, (dict, list)):
                return json.dumps(val, ensure_ascii=False)
            return str(val)
        return _TEMPLATE_RE.sub(repl, value)
    if isinstance(value, dict):
        return {k: _render_value(v, ctx) for k, v in value.items()}
    if isinstance(value, list):
        return [_render_value(v, ctx) for v in value]
    return value


def _tts(node, step: dict):
    """TTS 语音播报 — 可并行挂载多个动作和多个表情

    step 字段：
        text:      语音文字（必填）
        delay:     整节并行等待时长(秒)，默认 1.0
        motions:   动作数组，每项可为：
                     预设动作 {kind:'preset', motion_id, area}
                     灵创动作 {kind:'linkcraft', resource_key, version, resource_type, name}
                   （kind 缺省视为 preset，向后兼容）
        emojis:    [emotion_id, ...] 可选，依次触发表情
    """
    text = step.get("text", "")
    delay = step.get("delay", 1.0)
    motions = step.get("motions", []) or []
    emojis = step.get("emojis", []) or []

    extras = []
    # 1. 先触发所有表情（立即显示）
    for eid in emojis:
        if eid:
            node._do_emoji(int(eid), 1)
            extras.append(f"表情#{eid}")
    # 2. 触发所有动作（预设/灵创，不同区域可并行）
    for m in motions:
        kind = m.get("kind", "preset")
        if kind == "linkcraft":
            rk = m.get("resource_key", "")
            if rk:
                node._play_resource(rk, m.get("version", ""), m.get("resource_type", ""))
                extras.append(f"灵创:{m.get('name', rk)}")
        else:
            mid = m.get("motion_id", 0)
            if mid:
                node._do_motion(int(m.get("area", 0)), int(mid))
                extras.append(f"动作#{mid}")
    # 3. 触发 TTS（开始说话，与上面并行）
    result = node._do_tts(text)
    extras_str = f" + {' '.join(extras)}" if extras else ""
    logger.info(f"  📢 TTS: {str(text)[:30]}...{extras_str} {'✅' if result else '❌'}")
    # 4. 等待播完
    wait_done = step.get("wait_done", True)
    motion_wait = step.get("motion_wait", True)
    has_motion = bool(motions)
    if wait_done and result:
        node.wait_tts_done(timeout=step.get("timeout", 20.0))
        # 有挂载动作时，按策略处理动作
        if has_motion:
            if motion_wait:
                # 等动作做完（取 max(TTS, 动作)）
                node.wait_motion_done(timeout=step.get("motion_timeout", 30.0))
            else:
                # 以语音为准：播完即停止动作
                node.stop_motion()
    # 5. 额外等待（给表情/动作收尾）
    if delay > 0:
        node._sleep(delay)


def _motion(node, step: dict):
    """预设动作"""
    area = step.get("area", 0)
    motion_id = step["motion_id"]
    result = node._do_motion(area, motion_id)
    ok = result.get("ok", False)
    logger.info(f"  🕺 Motion area={area} id={motion_id} {'✅' if ok else '❌'}")


def _emoji(node, step: dict):
    """表情"""
    emotion_id = step["emotion_id"]
    mode = step.get("mode", 1)
    result = node._do_emoji(emotion_id, mode)
    ok = result.get("ok", False)
    logger.info(f"  😊 Emoji id={emotion_id} {'✅' if ok else '❌'}")


def _velocity(node, step: dict):
    """速度控制 — 持续 duration 秒后自动停"""
    forward = step.get("forward", 0.0)
    lateral = step.get("lateral", 0.0)
    angular = step.get("angular", 0.0)
    duration = step.get("duration", 1.0)

    node._do_velocity(float(forward), float(lateral), float(angular))
    logger.info(f"  🏃 Velocity fwd={forward} lat={lateral} ang={angular} × {duration}s")
    node._sleep(duration)
    node._do_velocity(0.0, 0.0, 0.0)
    logger.info(f"  🛑 停止")


def _wait(node, step: dict):
    """等待"""
    duration = step.get("duration", 1.0)
    logger.info(f"  ⏱️ Wait {duration}s")
    node._sleep(duration)


def _mode(node, step: dict):
    """运动模式切换（v0.8.2+ 用 action_desc 字符串）"""
    action_desc = step.get("action_desc", "STAND_DEFAULT")
    result = node._do_mode(action_desc)
    ok = result.get("ok", False)
    logger.info(f"  ⚙️ Mode {action_desc} {'✅' if ok else '❌'}")


def _volume(node, step: dict):
    """音量设置"""
    vol = step["volume"]
    node._do_set_volume(vol)
    logger.info(f"  🔊 Volume: {vol}%")


def _media(node, step: dict):
    """播放媒体文件"""
    file_name = step["file_name"]
    from ..routes.media import PC3_MEDIA
    file_path = f"{PC3_MEDIA}/{file_name}"
    node._do_media_play(file_path, file_name)
    logger.info(f"  🎬 Media: {file_name}")


def _camera(node, step: dict):
    """切换相机"""
    camera_id = step["camera_id"]
    node.switch_camera(camera_id)
    logger.info(f"  📷 Camera: {camera_id}")


def _linkcraft(node, step: dict):
    """灵创动作 — 播放机器人资源系统的动作包"""
    resource_key = step.get("resource_key", "")
    version = step.get("version", "")
    resource_type = step.get("resource_type", "")
    name = step.get("name", resource_key)
    if not resource_key:
        logger.warning("  ⚠️ 灵创动作未配置 resource_key，跳过")
        return
    result = node._play_resource(resource_key, version, resource_type)
    ok = result.get("ok", False)
    logger.info(f"  🤖 灵创动作: {name} {'✅' if ok else '❌'}")


def _http(node, step: dict, ctx: dict | None = None):
    """HTTP 接口调用 — 支持 {{}} 变量引用、save_as 存响应、expect_code 校验

    step 字段：
        method:      GET/POST/PUT/DELETE/PATCH，默认 GET
        url:         完整 HTTP(S) 地址（必填）
        headers:     请求头，JSON 字符串或 dict，可选
        body:        请求体字符串（POST/PUT/PATCH 时发送）
        save_as:     响应存到 ctx['responses'][save_as]（{code,msg,data} 的 data 字段自动提升）
        expect_code: 期望的业务 code，不符则中止任务（StepAbort）
        timeout:     超时秒数，默认 10
    """
    import urllib.request
    import urllib.error

    method = str(step.get("method", "GET")).upper()
    url = str(step.get("url", "")).strip()
    headers_raw = step.get("headers", "") or ""
    body = str(step.get("body", "") or "")
    timeout = float(step.get("timeout", 10) or 10)
    save_as = str(step.get("save_as", "") or "").strip()
    expect_code = step.get("expect_code", None)

    if not url:
        logger.warning("  ⚠️ HTTP 步骤未配置 url，跳过")
        return

    # headers 支持 dict 或 JSON 字符串
    headers: dict = {}
    if isinstance(headers_raw, dict):
        headers = {str(k): str(v) for k, v in headers_raw.items()}
    elif isinstance(headers_raw, str) and headers_raw.strip():
        try:
            parsed = json.loads(headers_raw)
            if isinstance(parsed, dict):
                headers = {str(k): str(v) for k, v in parsed.items()}
        except Exception as e:
            logger.warning(f"  ⚠️ headers 非合法 JSON，已忽略: {e}")

    # 请求体（仅写方法发送）
    data = None
    if method in ("POST", "PUT", "PATCH") and body:
        data = body.encode("utf-8")
        if not any(k.lower() == "content-type" for k in headers):
            headers["Content-Type"] = "application/json"

    req = urllib.request.Request(url, data=data, headers=headers, method=method)
    status = None
    resp_text = ""
    try:
        with urllib.request.urlopen(req, timeout=timeout) as resp:
            status = resp.status
            resp_text = resp.read().decode("utf-8", errors="replace")
        logger.info(f"  🌐 HTTP {method} {url} → {status} ({len(resp_text)}B)")
    except urllib.error.HTTPError as e:
        status = e.code
        try:
            resp_text = e.read().decode("utf-8", errors="replace")
        except Exception:
            resp_text = ""
        logger.warning(f"  ⚠️ HTTP {method} {url} → {status} {e.reason}")
    except Exception as e:
        logger.error(f"  ❌ HTTP {method} {url} 调用失败: {e}")
        if save_as and ctx is not None:
            ctx.setdefault("responses", {})[save_as] = {
                "status": None, "code": None, "msg": str(e), "_raw": None, "body_text": ""}
        return

    # 解析响应（识别 {code, msg, data} 结构，提升 data 字段到顶层）
    entry: dict = {"status": status, "body_text": resp_text}
    parsed = None
    if resp_text:
        try:
            parsed = json.loads(resp_text)
        except Exception:
            parsed = None
    entry["_raw"] = parsed

    if isinstance(parsed, dict):
        entry["code"] = parsed.get("code")
        entry["msg"] = parsed.get("msg")
        data_obj = parsed.get("data")
        if isinstance(data_obj, dict):
            entry["data"] = data_obj
            reserved = {"code", "msg", "status", "_raw", "body_text", "data"}
            for k, v in data_obj.items():
                if k not in reserved:   # 保留字优先，冲突走 {{var.data.xxx}}
                    entry[k] = v
        elif data_obj is not None:
            entry["data"] = data_obj

    if save_as and ctx is not None:
        ctx.setdefault("responses", {})[save_as] = entry
        logger.info(f"  💾 响应已存为变量: {save_as}")

    # 业务码校验：不符则中止任务（留空不校验）
    if expect_code is not None and str(expect_code).strip() != "":
        biz_code = entry.get("code")
        if str(biz_code) != str(expect_code).strip():
            raise StepAbort(
                f"业务码校验失败: 期望 {expect_code}，实际 {biz_code}（{entry.get('msg', '')}）")


# ── 注册表 ──

STEP_HANDLERS = {
    "tts": _tts,
    "motion": _motion,
    "emoji": _emoji,
    "velocity": _velocity,
    "wait": _wait,
    "mode": _mode,
    "volume": _volume,
    "media": _media,
    "camera": _camera,
    "linkcraft": _linkcraft,
    "http": _http,
}


def execute_step(node, step: dict, ctx: dict | None = None):
    """执行单个步骤（执行前对字符串字段做 {{}} 变量渲染）"""
    if ctx is None:
        ctx = {"responses": {}}
    step_type = step.get("type", "")
    handler = STEP_HANDLERS.get(step_type)
    if handler is None:
        logger.error(f"❌ 未知步骤类型: {step_type}")
        return
    # 渲染变量（深拷贝，不污染任务定义）
    rendered = _render_value(step, ctx)
    try:
        if step_type == "http":
            handler(node, rendered, ctx)
        else:
            handler(node, rendered)
    except StepAbort:
        raise  # 业务中止，传播给引擎
    except Exception as e:
        logger.error(f"❌ 步骤执行失败 [{step_type}]: {e}")


# ── 能力列表（供前端生成配置表单）──

CAPABILITIES = [
    {
        "type": "tts",
        "label": "语音播报",
        "icon": "🗣️",
        "color": "#4CAF50",
        "params": [
            {"name": "text", "label": "播报文字", "type": "string", "required": True},
            {"name": "delay", "label": "完成后等待(s)", "type": "number", "default": 0.5},
        ],
    },
    {
        "type": "motion",
        "label": "预设动作",
        "icon": "🕺",
        "color": "#FF9800",
        "params": [
            {"name": "motion_id", "label": "动作ID", "type": "number", "required": True,
             "hint": "1001=抬手 1002=挥手 3004=比心 4001=点头 4002=摇头"},
            {"name": "area", "label": "身体区域", "type": "select", "default": 0,
             "options": [{"label": "自动", "value": 0}, {"label": "左手", "value": 1},
                         {"label": "右手", "value": 2}, {"label": "头部", "value": 4},
                         {"label": "腰部", "value": 8}]},
            {"name": "delay", "label": "完成后等待(s)", "type": "number", "default": 1.0},
        ],
    },
    {
        "type": "emoji",
        "label": "表情",
        "icon": "😊",
        "color": "#E91E63",
        "params": [
            {"name": "emotion_id", "label": "表情ID", "type": "number", "required": True,
             "hint": "1=眨眼 90=快乐 110=悲伤 130=疑惑 140=震惊"},
            {"name": "mode", "label": "播放模式", "type": "select", "default": 1,
             "options": [{"label": "播放一次", "value": 1}, {"label": "循环", "value": 2}]},
            {"name": "delay", "label": "完成后等待(s)", "type": "number", "default": 0.5},
        ],
    },
    {
        "type": "velocity",
        "label": "速度控制",
        "icon": "🏃",
        "color": "#2196F3",
        "params": [
            {"name": "forward", "label": "前后(m/s) +前-后", "type": "number", "default": 0.3},
            {"name": "lateral", "label": "左右(m/s) +左-右", "type": "number", "default": 0.0},
            {"name": "angular", "label": "旋转(rad/s) +左-右", "type": "number", "default": 0.0},
            {"name": "duration", "label": "持续时间(s)", "type": "number", "default": 2.0},
        ],
    },
    {
        "type": "wait",
        "label": "等待",
        "icon": "⏱️",
        "color": "#9E9E9E",
        "params": [
            {"name": "duration", "label": "等待时间(s)", "type": "number", "default": 2.0},
        ],
    },
    {
        "type": "mode",
        "label": "运动模式",
        "icon": "⚙️",
        "color": "#795548",
        "params": [
            {"name": "action_desc", "label": "模式", "type": "select", "required": True, "default": "STAND_DEFAULT",
             "options": [
                {"label": "稳定站立", "value": "STAND_DEFAULT"},
                {"label": "走跑", "value": "LOCOMOTION_DEFAULT"},
                {"label": "阻尼", "value": "DAMPING_DEFAULT"},
                {"label": "位控站立", "value": "JOINT_DEFAULT"},
                {"label": "零力矩/急停", "value": "PASSIVE_DEFAULT"},
             ]},
            {"name": "delay", "label": "完成后等待(s)", "type": "number", "default": 1.0},
        ],
    },
    {
        "type": "volume",
        "label": "音量",
        "icon": "🔊",
        "color": "#607D8B",
        "params": [
            {"name": "volume", "label": "音量(0-100)", "type": "number", "default": 50},
        ],
    },
    {
        "type": "media",
        "label": "媒体播放",
        "icon": "🎬",
        "color": "#673AB7",
        "params": [
            {"name": "file_name", "label": "文件名", "type": "string", "required": True,
             "hint": "PC3上的音视频文件名"},
            {"name": "delay", "label": "完成后等待(s)", "type": "number", "default": 2.0},
        ],
    },
    {
        "type": "http",
        "label": "接口调用",
        "icon": "🌐",
        "color": "#26A69A",
        "params": [
            {"name": "method", "label": "方法", "type": "select", "required": True, "default": "GET",
             "options": [
                 {"label": "GET", "value": "GET"},
                 {"label": "POST", "value": "POST"},
                 {"label": "PUT", "value": "PUT"},
                 {"label": "DELETE", "value": "DELETE"},
                 {"label": "PATCH", "value": "PATCH"},
             ]},
            {"name": "url", "label": "接口地址", "type": "string", "required": True,
             "hint": "完整 HTTP(S) URL，如 https://example.com/api"},
            {"name": "headers", "label": "请求头(JSON)", "type": "string", "default": "",
             "hint": "可选，如 {\"Authorization\":\"Bearer xxx\"}"},
            {"name": "body", "label": "请求体", "type": "string", "default": "",
             "hint": "POST/PUT/PATCH 发送内容（JSON 字符串），支持 {{var.field}}"},
            {"name": "save_as", "label": "响应存为变量", "type": "string", "default": "",
             "hint": "填变量名，响应 data 字段自动提升，后续用 {{变量名.字段}} 引用"},
            {"name": "expect_code", "label": "期望业务码", "type": "number", "default": None,
             "hint": "填 code 值（如 0），不符则中止任务；不填不校验"},
            {"name": "timeout", "label": "超时(s)", "type": "number", "default": 10},
            {"name": "delay", "label": "完成后等待(s)", "type": "number", "default": 0.5},
        ],
    },
]
