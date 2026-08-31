"""A3 HTTP JSON RPC 客户端 — 三单元服务端口表 + 超时重试 + header 构造

A3-Ultra 控制面 = AimRT 暴露的 HTTP JSON RPC（POST /rpc/aimdk.protocol.{Service}/{Method}），
无鉴权。服务分布在三台工控机（端口表来自 docs/a3-ultra-dev-notes.md / 官方 examples）。
agent 跑在 HDU，本机服务走 127.0.0.1，跨单元走内网固定 IP。

重试哲学（对齐 X2 retry.py）：查询类幂等可重试；控制类（TTS/动作播放）不重试——
timeout 后盲重发会造成重复播报。
"""

import time
import logging

import httpx

from . import config

logger = logging.getLogger(__name__)

# 三单元服务端口（unit: (host, port)）
UNITS = {
    "hdu": (config.HDU_HOST, 59301),   # AgentControl / TTS
    "hdu_audio": (config.HDU_HOST, 56666),   # HalAudio（音量/麦克风源/文件播放）
    "hdu_resource": (config.HDU_HOST, 51049),  # Resource（动作/表情/音频资源）
    "hdu_camera": (config.HDU_HOST, 56430),   # HalCameraService（TakeShot 截图；实机扫描发现，文档未载）
    "mdu": (config.MDU_HOST, 56322),   # MotionControlAction（状态机）
    "mdu_motion": (config.MDU_HOST, 56444),  # MotionCommand（动作播放）
    "mdu_hds": (config.MDU_HOST, 50587),   # HDS 告警
    "adu": (config.ADU_HOST, 50807),   # Mapping / Localization
    "adu_pnc": (config.ADU_HOST, 53176),   # 导航
}

_client = httpx.Client(timeout=10.0)


class RpcError(Exception):
    """RPC 调用失败（网络/超时/业务码非 0）"""

    def __init__(self, msg: str, code: str = "", url: str = ""):
        super().__init__(msg)
        self.code = code
        self.url = url


def _header(control_source: str = "ControlSource_MANUAL") -> dict:
    """通用请求头（文档：header 可省略，带上便于机上日志追踪）"""
    now = time.time()
    return {
        "timestamp": {
            "seconds": int(now),
            "nanos": int((now % 1) * 1e9),
            "ms_since_epoch": int(now * 1000),
        },
        "control_source": control_source,
        "uuid": "",
        "trace_id": "ggrobot-agent",
        "domin": "",
    }


def call(unit: str, service: str, method: str, payload: dict | None = None,
         timeout: float | None = None, retries: int | None = None,
         with_header: bool = False) -> dict:
    """调用 RPC。返回出参 JSON（dict）。

    unit: UNITS 键；service: 如 aimdk.protocol.TTSService；method: 如 PlayTTS
    retries 默认按控制类 0（不重试）；查询类显式传 retries=RPC_QUERY_RETRIES
    """
    host, port = UNITS[unit]
    url = f"http://{host}:{port}/rpc/{service}/{method}"
    body: dict = dict(payload or {})
    if with_header and "header" not in body:
        body["header"] = _header()

    timeout = config.RPC_TIMEOUT if timeout is None else timeout
    retries = config.RPC_CTRL_RETRIES if retries is None else retries

    last_err: Exception | None = None
    for attempt in range(retries + 1):
        try:
            r = _client.post(url, json=body, timeout=timeout,
                             headers={"Content-Type": "application/json"})
            r.raise_for_status()
            data = r.json()
            # 多数服务业务码在 header.code（"0"=成功）；部分服务无 header
            hdr = data.get("header") or {}
            code = str(hdr.get("code", "0"))
            if code != "0":
                raise RpcError(hdr.get("msg") or f"rpc code {code}", code=code, url=url)
            return data
        except (httpx.TimeoutException, httpx.ConnectError) as e:
            last_err = e
            if attempt < retries:
                time.sleep(0.5 * (attempt + 1))
                continue
            break
        except RpcError:
            raise
        except httpx.HTTPStatusError as e:
            raise RpcError(f"http {e.response.status_code}", url=url) from e
        except ValueError as e:  # json 解析失败
            raise RpcError(f"bad json: {e}", url=url) from e
    raise RpcError(f"unreachable: {last_err}", url=url)


# ── 相机截图（TakeShot；PNG base64）─────────────────────

# 实机在线相机名（TakeShot 用短名，非话题全名；2026-08-31 验证）
SHOT_CAMERAS = {"right_fisheye": "right_fisheye_camera", "left_fisheye": "left_fisheye_camera"}


def take_shot(camera: str = "right_fisheye_camera") -> bytes:
    """单相机截图 → PNG bytes。⚠️ 单张 ~2.5MB，仅在有人看相机时调用（按需轮询）"""
    import base64
    r = call("hdu_camera", "aimdk.protocol.HalCameraService", "TakeShot",
             {"camera_name": [camera]}, timeout=8.0)
    shots = r.get("camera_shot") or []
    if not shots:
        raise RpcError(f"no shot from {camera}", url="TakeShot")
    return base64.b64decode(shots[0].get("data", ""))


# ── 常用封装（供 routes / node 直接调）─────────────────────

def tts_play(text: str, is_interrupted: bool = True) -> dict:
    """TTS 播报（HDU）。返回含 trace_id（查询播完状态用）。≤1024 字节。"""
    return call("hdu", "aimdk.protocol.TTSService", "PlayTTS", {
        "text": text,
        "priority_level": "INTERACTION_L6",
        "domain": "ggrobot",
        "trace_id": f"gg-{int(time.time()*1000)}",
        "is_interrupted": is_interrupted,
    })


def tts_status(trace_id: str) -> dict:
    return call("hdu", "aimdk.protocol.TTSService", "GetAudioStatus",
                {"trace_id": trace_id}, retries=config.RPC_QUERY_RETRIES)


def tts_stop(trace_id: str) -> dict:
    return call("hdu", "aimdk.protocol.TTSService", "StopTTSTraceId", {"trace_id": trace_id})


def media_play(file_name: str, file_path: str = "") -> dict:
    """播放音频文件（HDU；wav 推荐，pcm 需 channles/samplerate）"""
    return call("hdu", "aimdk.protocol.TTSService", "PlayMediaFile", {
        "file_name": file_name, "file_path": file_path,
        "priority_level": "INTERACTION_L6", "domain": "ggrobot",
        "trace_id": f"gg-{int(time.time()*1000)}", "is_interrupted": True,
    })


def volume_get() -> dict:
    return call("hdu_audio", "aimdk.protocol.HalAudioService", "GetAudioVolume",
                {}, retries=config.RPC_QUERY_RETRIES)


def volume_set(volume: int, mute: bool = False) -> dict:
    """音量 0-100。⚠️ 官方上限 70，超了损坏扬声器——这里硬钳制。"""
    v = max(0, min(70, int(volume)))
    return call("hdu_audio", "aimdk.protocol.HalAudioService", "SetAudioVolume",
                {"audio_volume": v, "is_mute": mute, "type": "SPEAKER_BUILT_IN"})


def action_get() -> dict:
    """查询运动控制状态机（当前 Action）"""
    return call("mdu", "aimdk.protocol.MotionControlActionService", "GetAction",
                {}, retries=config.RPC_QUERY_RETRIES)


def action_set(action: str) -> dict:
    """切换状态机。action 如 MOTION / PD_STAND / DAMPING（GetAvailableActions 的 ext_action）"""
    return call("mdu", "aimdk.protocol.MotionControlActionService", "SetAction", {
        "header": _header("ControlSource_SAFE"),
        "command": {"action": f"MotionControlAction_{action}", "ext_action": action},
    })


def action_available() -> dict:
    return call("mdu", "aimdk.protocol.MotionControlActionService", "GetAvailableActions",
                {}, retries=config.RPC_QUERY_RETRIES)


def motion_command(motion_id: str = "", duration_ms: int = 10000, cmd_end: bool = True,
                   cmd_pause: bool = False, cmd_reset: bool = False,
                   cmd_repeat: bool = False) -> dict:
    """动作播放/暂停/复位/循环（MDU）。motion_id = 资源文件绝对路径；空+cmd_reset=停止"""
    return call("mdu_motion", "aimdk.protocol.MotionCommandService", "SendMotionCommand", {
        "motion_id": motion_id, "duration_ms": int(duration_ms),
        "cmd_end": cmd_end, "cmd_pause": cmd_pause,
        "cmd_reset": cmd_reset, "cmd_repeat": cmd_repeat,
    })


def resource_list(resource_type: str) -> dict:
    """资源列表（动作 RESOURCE_TYPE_MOTION / 表情 / 音频 / 技能 / 地图 / 创作作品）"""
    return call("hdu_resource", "aimdk.protocol.ResourceService", "GetResourceList", {
        "header": _header(),
        "resource_type": resource_type,
    }, retries=config.RPC_QUERY_RETRIES)


def alerts() -> dict:
    """HDS 当前告警列表（MDU）"""
    return call("mdu_hds", "aimdk.protocol.HDSService", "GetAlertList",
                {}, retries=config.RPC_QUERY_RETRIES)


def dance(command: str = "Start", path: str = "", session_id: str = "") -> dict:
    """舞蹈播放（Start/Pause/Stop）。path = 技能资源目录"""
    return call("hdu", "aimdk.protocol.SkillPilotService", "SkillPackage", {
        "source": "custom", "command": command, "path": path, "session_id": session_id,
    })


# ── 导航（ADU）──────────────────────

def navi(kind: str, map_id: str | int, **kw) -> dict:
    """导航任务统一下发。kind: goal/pose2d/linear_goal/linear_pose2d/linear_relative/
    direct_goal/direct_relative/precise_goal/spin_turn/move_forward"""
    svc = "aimdk.protocol.PncService"
    method = {
        "goal": "PlanningNaviToGoal", "pose2d": "PlanningNaviToPose2D",
        "linear_goal": "LinearNaviToGoal", "linear_pose2d": "LinearNaviToPose2D",
        "linear_relative": "LinearNaviToRelative",
        "direct_goal": "DirectNaviToRelativeGoal", "direct_relative": "DirectNaviToRelative",
        "precise_goal": "PreciseNaviToGoal",
        "spin_turn": "SpinTurn", "move_forward": "MoveForward",
    }[kind]
    body: dict = {"task_id": 0, "map_id": int(map_id)}
    if "target_id" in kw:
        body["target_id"] = int(kw["target_id"])
    if "pose" in kw:
        body["pose"] = kw["pose"]
    if "angle" in kw:
        body["angle"] = float(kw["angle"])
    if "distance" in kw:
        body["distance"] = float(kw["distance"])
    if "pose_offset" in kw:
        body["pose_offset"] = kw["pose_offset"]
    body["ackerman_mode"] = False
    return call("adu_pnc", svc, method, body)


def navi_control(method: str, task_id: int) -> dict:
    """ActionCancel / ActionPause / ActionResume"""
    return call("adu_pnc", "aimdk.protocol.PncService", method, {"task_id": int(task_id)})


def navi_state(task_id: int = 0) -> dict:
    """任务状态（task_id=0 → 最近一次任务）"""
    return call("adu_pnc", "aimdk.protocol.PncService", "ActionGetState",
                {"task_id": int(task_id)}, retries=config.RPC_QUERY_RETRIES)


# ── 地图（ADU）──────────────────────

def map_list() -> dict:
    return call("adu", "aimdk.protocol.MappingService", "GetStoredMapNames",
                {"command": "MappingCommand_GET_STORED_MAP_NAME"}, retries=config.RPC_QUERY_RETRIES)


def map_current() -> dict:
    return call("adu", "aimdk.protocol.MappingService", "GetCurrentWorkingMap",
                {"command": "MappingCommand_GET_CURRENT_WORKING_MAP"}, retries=config.RPC_QUERY_RETRIES)


def map_2d(map_id: str) -> dict:
    return call("adu", "aimdk.protocol.MappingService", "Get2DWholeMap",
                {"command": "MappingCommand_GET_2D_WHOLE_MAP", "map_id": map_id})


def map_topo(map_id: str) -> dict:
    return call("adu", "aimdk.protocol.LocalizationService", "GetTopoMsgs",
                {"command": "TopoCommand_GET_TOPO_MSG", "map_id": int(map_id)},
                retries=config.RPC_QUERY_RETRIES)


def mapping_start() -> dict:
    return call("adu", "aimdk.protocol.MappingService", "StartMapping",
                {"header": {}, "command": "MappingCommand_START_MAPPING", "no_realtime_data": True})


def mapping_stop(save: bool = True, map_name: str = "ggrobot-地图") -> dict:
    cmd = "MappingCommand_SAVING_MAP" if save else "MappingCommand_STOP_MAPPING"
    body = {"header": _header(), "command": cmd}
    if save:
        body["map_name"] = map_name
    return call("adu", "aimdk.protocol.MappingService", "StopMapping", body)


def mapping_realtime() -> dict:
    """实时建图数据（cur_pos + lidar_points + trajectory + base64 png）"""
    return call("adu", "aimdk.protocol.MappingService", "GetRealtimeMapData",
                {"header": _header(), "command": "MappingCommand_GET_REALTIME_MAP"},
                retries=config.RPC_QUERY_RETRIES)


def relocalize(mode: str = "relocalization", **kw) -> dict:
    """重定位（examples/mm/relocalization.sh + teleop_relocation.sh 的入参形态，实机校准）"""
    body = {"header": _header(), "command": mode}
    body.update(kw)
    return call("adu", "aimdk.protocol.LocalizationService", "Relocalization", body)
