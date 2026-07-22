"""X2 ROS2 节点 — Service 客户端 + 传感器订阅 + 相机帧缓存

改造要点（相比旧版）：
1. 添加 RGBD 相机订阅 + 帧缓存（供 WebSocket 推送）
2. 去掉 MIC VAD 采集（简化，后续再加）
3. 输入源注册统一处理
4. 所有跨板调用统一走 retry.call_with_retry
"""

import logging
import threading
import math
import time
from concurrent.futures import Future
from dataclasses import dataclass
from typing import Any

from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data, QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from aimdk_msgs.srv import (
    PlayTts, SetMcPresetMotion, GetMcAction, SetMcAction,
    GetSystemState, PlayEmoji, PlayAudioFile, PlayVideo,
    SetVolume, GetVolume, SetMute, GetMute, SetMcInputSource,
    GetRobotResources, ExecuteActionResource,
)
from aimdk_msgs.msg import McLocomotionVelocity, PmuState, MessageHeader, PlayStateChange
from sensor_msgs.msg import JointState, Imu, CompressedImage

logger = logging.getLogger(__name__)

# 全局引用，由 __main__.py 初始化
_node: "X2Node | None" = None


# ═══════════════════════════════════════════════
# 命令类型
# ═══════════════════════════════════════════════

@dataclass
class Command:
    action: str
    kwargs: dict = None
    future: "Future[Any] | None" = None

    def __post_init__(self):
        if self.kwargs is None:
            self.kwargs = {}


# ═══════════════════════════════════════════════
# 命令队列（线程安全）
# ═══════════════════════════════════════════════

import queue


class CommandQueue:
    def __init__(self):
        self._q: queue.Queue[Command] = queue.Queue()

    def put(self, action: str, **kwargs) -> Future:
        f: Future = Future()
        self._q.put(Command(action=action, kwargs=kwargs, future=f))
        return f

    def get_nowait(self) -> Command | None:
        try:
            return self._q.get_nowait()
        except queue.Empty:
            return None

    def pending_count(self) -> int:
        return self._q.qsize()


# ═══════════════════════════════════════════════
# ROS2 节点
# ═══════════════════════════════════════════════

class X2Node(Node):
    def __init__(self):
        super().__init__("gg_robot")

        # ── Service 客户端 ──
        self.tts_client = self.create_client(PlayTts, "/aimdk_5Fmsgs/srv/PlayTts")
        self.motion_client = self.create_client(SetMcPresetMotion, "/aimdk_5Fmsgs/srv/SetMcPresetMotion")
        self.action_client = self.create_client(GetMcAction, "/aimdk_5Fmsgs/srv/GetMcAction")
        self.mode_client = self.create_client(SetMcAction, "/aimdk_5Fmsgs/srv/SetMcAction")
        self.sys_client = self.create_client(GetSystemState, "/aimdk_5Fmsgs/srv/GetSystemState")
        self.emoji_client = self.create_client(PlayEmoji, "/aimdk_5Fmsgs/srv/PlayEmoji")
        self.audio_client = self.create_client(PlayAudioFile, "/aimdk_5Fmsgs/srv/PlayAudioFile")
        self.video_client = self.create_client(PlayVideo, "/face_ui_proxy/play_video")
        self.input_source_client = self.create_client(SetMcInputSource, "/aimdk_5Fmsgs/srv/SetMcInputSource")
        self.vol_get = self.create_client(GetVolume, "/aimdk_5Fmsgs/srv/GetVolume")
        self.vol_set = self.create_client(SetVolume, "/aimdk_5Fmsgs/srv/SetVolume")
        self.mute_get = self.create_client(GetMute, "/aimdk_5Fmsgs/srv/GetMute")
        self.mute_set = self.create_client(SetMute, "/aimdk_5Fmsgs/srv/SetMute")
        self.get_resources_client = self.create_client(GetRobotResources, "/aimdk_5Fmsgs/srv/GetRobotResources")
        self.play_resource_client = self.create_client(ExecuteActionResource, "/aimdk_5Fmsgs/srv/ExecuteActionResource")

        # ── 速度发布 ──
        self.vel_publisher = self.create_publisher(McLocomotionVelocity, "/aima/mc/locomotion/velocity", 10)

        # ── 传感器缓存 ──
        self.battery: dict = {}
        self.arm_joints: list[dict] = []
        self.imu: dict = {}

        # ── 音频播放状态缓存（用于精确等待 TTS 播完）──
        # 注：v0.9.0 文档无 /aima/hal/audio/play_state 话题，主用 estimated_duration 估时
        self._play_state: int = 0      # PlayStateType: 0=CLOSED 1=PLAYING 2=STOPED
        self._play_pkg: str = ""
        self._play_state_ts: float = 0.0
        self._last_tts_duration_ms: int = 0   # 最近一次 TTS 的预计耗时(毫秒)

        # ── 相机帧缓存 ──
        self._camera_frame: bytes | None = None
        self._camera_timestamp: float = 0.0
        self._camera_lock = threading.Lock()

        # ── 相机 Topic 配置 ──
        # v0.8.1 已下线交互相机 rgb_head_front_center，不再列入
        # QoS 按 v0.9.0 文档：RGBD 用 RELIABLE，双目/后视用 TRANSIENT_LOCAL
        self._camera_topics = {
            "rgbd_front": {
                "label": "RGBD 前视（推荐）",
                "topic": "/aima/hal/sensor/rgbd_head_front/rgb_image/compressed",
                "qos": "reliable",
                "active": False,
            },
            "rgb_rear": {
                "label": "RGB 后视",
                "topic": "/aima/hal/sensor/rgb_head_rear/rgb_image/compressed",
                "qos": "transient_local",
                "active": False,
            },
            "stereo_left": {
                "label": "双目 左",
                "topic": "/aima/hal/sensor/stereo_head_front_left/rgb_image/compressed",
                "qos": "transient_local",
                "active": False,
            },
            "stereo_right": {
                "label": "双目 右",
                "topic": "/aima/hal/sensor/stereo_head_front_right/rgb_image/compressed",
                "qos": "transient_local",
                "active": False,
            },
        }
        self._active_camera: str = ""
        self._cam_sub = None
        self._cam_qos_map = {
            "reliable": QoSProfile(
                reliability=ReliabilityPolicy.RELIABLE,
                durability=DurabilityPolicy.VOLATILE,
                history=HistoryPolicy.KEEP_LAST,
                depth=1,
            ),
            "transient_local": QoSProfile(
                reliability=ReliabilityPolicy.RELIABLE,
                durability=DurabilityPolicy.TRANSIENT_LOCAL,
                history=HistoryPolicy.KEEP_LAST,
                depth=1,
            ),
        }

        # ── 订阅传感器 ──
        self.create_subscription(PmuState, "/aima/hal/pmu/state", self._on_battery, qos_profile_sensor_data)
        self.create_subscription(JointState, "/aima/hal/joint/arm/state", self._on_arm, qos_profile_sensor_data)
        self.create_subscription(Imu, "/aima/hal/imu/torso/state", self._on_imu, qos_profile_sensor_data)

        # ── 订阅音频播放状态（TTS 完成事件）──
        self.create_subscription(PlayStateChange, "/aima/hal/audio/play_state", self._on_play_state, qos_profile_sensor_data)

        # ── 自动选择第一个有数据的相机 ──
        self._auto_select_camera()

        # ── 速度控制状态 ──
        self._input_registered = False
        self._vel_timer = None
        self._vel_target = (0.0, 0.0, 0.0)

        self._wait_services()
        logger.info("✅ X2Node 就绪")

    def _wait_services(self, timeout: float = 30.0):
        """等待所有 Service 就绪，超时则抛出 RuntimeError"""
        clients = [
            ("PlayTts", self.tts_client), ("SetMcPresetMotion", self.motion_client),
            ("GetMcAction", self.action_client), ("SetMcAction", self.mode_client),
            ("GetSystemState", self.sys_client), ("PlayEmoji", self.emoji_client),
            ("PlayAudioFile", self.audio_client), ("PlayVideo", self.video_client),
            ("GetVolume", self.vol_get), ("SetVolume", self.vol_set),
            ("GetMute", self.mute_get), ("SetMute", self.mute_set),
            ("SetMcInputSource", self.input_source_client),
        ]
        t0 = time.time()
        for name, client in clients:
            logger.info(f"⏳ 等待 {name} 服务...")
            while not client.wait_for_service(timeout_sec=2.0):
                if time.time() - t0 > timeout:
                    missing = [n for n, c in clients if not c.wait_for_service(timeout_sec=0.1)]
                    raise RuntimeError(f"Service 等待超时，未就绪: {missing}")
                pass

    # ── 传感器回调 ──
    def _on_battery(self, msg):
        self.battery = {
            "percentage": round(msg.battery_remaining_capacity_percentage, 1),
            "voltage": round(msg.battery_pack_voltage, 2),
            "current": round(msg.battery_current, 2),
            "temperature": round(msg.battery_temperature, 1),
            "power": round(msg.battery_output_power, 1),
        }

    def _on_arm(self, msg):
        self.arm_joints = [
            {"name": n, "position": round(p, 3), "velocity": round(v, 3)}
            for n, p, v in zip(msg.name, msg.position, msg.velocity)
        ]

    def _on_imu(self, msg):
        self.imu = {
            "accel_x": round(msg.linear_acceleration.x, 2),
            "accel_y": round(msg.linear_acceleration.y, 2),
            "accel_z": round(msg.linear_acceleration.z, 2),
        }

    def _on_camera(self, msg: CompressedImage):
        """缓存相机帧，供 WebSocket 推送"""
        with self._camera_lock:
            self._camera_frame = bytes(msg.data)
            self._camera_timestamp = time.time()

    def _on_play_state(self, msg: PlayStateChange):
        """音频播放状态变化（TTS 完成事件）"""
        self._play_state = msg.state.value
        self._play_pkg = msg.pkg_name
        self._play_state_ts = time.time()

    def wait_tts_done(self, timeout: float = 20.0) -> bool:
        """等待 TTS 播报完成。

        v0.9.0 文档无 TTS 完成回调话题，以 PlayTtsResponse.estimated_duration 估时为主；
        若实机仍存在 /aima/hal/audio/play_state 话题，期间收到 STOPED 则提前返回。
        """
        from rclpy import spin_once as _spin_once
        start = time.time()
        est_ms = getattr(self, "_last_tts_duration_ms", 0) or 0
        # 估时(秒) + 0.3s 余量；无估值时退化为纯等事件
        target = start + (est_ms / 1000.0 + 0.3) if est_ms > 0 else None
        deadline = start + timeout
        while time.time() < deadline:
            _spin_once(self, timeout_sec=0.05)
            # play_state 收到 STOPED（且本次期间）→ 提前返回
            if self._play_state == 2 and self._play_state_ts > start:
                return True
            # 已等够 estimated_duration → 视为播完
            if target is not None and time.time() >= target:
                return True
        logger.warning(f"⏱️ TTS 等待超时({timeout}s)，est={est_ms}ms")
        return False

    def _get_action_status(self) -> int | None:
        """查询当前运动状态（GetMcAction.info.status.value：0=IDLE 100=RUNNING 200=TRANSITION）"""
        req = GetMcAction.Request()
        req.request.header.stamp = self.get_clock().now().to_msg()
        future = self.action_client.call_async(req)
        t0 = time.time()
        while time.time() - t0 < 0.5:
            from rclpy import spin_once as _spin_once
            _spin_once(self, timeout_sec=0.05)
            if future.done():
                r = future.result()
                return r.info.status.value if r else None
        return None

    def wait_motion_done(self, timeout: float = 30.0) -> bool:
        """轮询 GetMcAction.status，等动作做完（status 从 RUNNING 回到非 RUNNING）

        ⚠️ McActionStatus 是否反映「预设动作」执行状态需实测。
        """
        start = time.time()
        deadline = start + timeout
        entered_running = False
        while time.time() < deadline:
            s = self._get_action_status()
            if s is not None:
                if s == 100:  # RUNNING
                    entered_running = True
                elif entered_running:  # 之前在 RUNNING，现在不是 → 完成
                    return True
            self._sleep(0.15)
        logger.warning(f"⏱️ 动作等待超时({timeout}s)，status={self._get_action_status()}")
        return False

    def stop_motion(self):
        """停止当前预设动作 — 切回稳定站立(STAND_DEFAULT)打断当前动作

        ⚠️ 通过切换运动模式实现，会让机器人回到站立姿态。
        """
        logger.info("  ⏹ 停止动作（切回站立）")
        self._do_mode("STAND_DEFAULT")

    def get_camera_frame(self) -> bytes | None:
        with self._camera_lock:
            return self._camera_frame

    # ── 相机管理 ──
    def list_cameras(self) -> list[dict]:
        """返回所有相机 topic 及其状态"""
        result = []
        for cam_id, cfg in self._camera_topics.items():
            result.append({
                "id": cam_id,
                "label": cfg["label"],
                "topic": cfg["topic"],
                "active": cfg["active"],
                "selected": cam_id == self._active_camera,
            })
        return result

    def switch_camera(self, camera_id: str) -> dict:
        """切换到指定相机"""
        if camera_id not in self._camera_topics:
            return {"ok": False, "error": f"未知相机: {camera_id}"}

        cfg = self._camera_topics[camera_id]
        if not cfg["active"]:
            return {"ok": False, "error": f"相机 {cfg['label']} 无数据"}

        # 销毁旧订阅
        if self._cam_sub is not None:
            self.destroy_subscription(self._cam_sub)
            self._cam_sub = None

        # 清空帧缓存
        with self._camera_lock:
            self._camera_frame = None
            self._camera_timestamp = 0.0

        # 创建新订阅
        self._cam_sub = self.create_subscription(
            CompressedImage,
            cfg["topic"],
            self._on_camera,
            self._cam_qos_map.get(cfg.get("qos", "reliable"), self._cam_qos_map["reliable"]),
        )
        self._active_camera = camera_id
        logger.info(f"📷 切换相机: {cfg['label']} ({cfg['topic']})")
        return {"ok": True, "camera": cfg["label"], "topic": cfg["topic"]}

    def get_active_camera(self) -> str:
        """返回当前活跃相机 ID"""
        return self._active_camera

    def _auto_select_camera(self):
        """扫描所有相机 topic，自动选择第一个有数据的"""
        # 先快速检测哪些 topic 有发布者
        from rclpy import spin_once as _spin_once
        import time as _time
        deadline = _time.time() + 3.0
        checked: set[str] = set()
        while _time.time() < deadline:
            for cam_id, cfg in self._camera_topics.items():
                if cam_id in checked:
                    continue
                # 尝试通过 topic name 匹配来判断是否有发布者
                topic_names = self.get_topic_names_and_types()
                for tname, _ in topic_names:
                    if tname == cfg["topic"]:
                        cfg["active"] = True
                        checked.add(cam_id)
                        if not self._active_camera:
                            self.switch_camera(cam_id)
                        break
            if self._active_camera:
                break
            _spin_once(self, timeout_sec=0.1)
        else:
            # 3秒后还没找到，选第一个 active 的
            for cam_id, cfg in self._camera_topics.items():
                if cfg["active"] and not self._active_camera:
                    self.switch_camera(cam_id)
                    break

        if not self._active_camera:
            logger.warning("📷 未检测到任何相机 topic，相机功能不可用")
        else:
            cfg = self._camera_topics[self._active_camera]
            logger.info(f"📷 自动选择相机: {cfg['label']}")

    # ── 命令处理 ──
    def process_commands(self):
        """处理命令队列中的待执行命令（由 rclpy 线程调用）"""
        while True:
            cmd = _cmd_queue.get_nowait()
            if cmd is None:
                break
            try:
                result = self._dispatch(cmd)
                if cmd.future and not cmd.future.done():
                    cmd.future.set_result(result)
            except Exception as e:
                if cmd.future and not cmd.future.done():
                    cmd.future.set_exception(e)

    def _dispatch(self, cmd: Command) -> Any:
        action_map = {
            "tts": self._do_tts,
            "motion": self._do_motion,
            "velocity": self._do_velocity,
            "status": self._get_status,
            "system": self._do_system,
            "mode": self._do_mode,
            "emoji": self._do_emoji,
            "media_play": self._do_media_play,
            "logo_show": self._do_logo_show,
            "logo_hide": self._do_logo_hide,
            "get_volume": self._do_get_volume,
            "set_volume": self._do_set_volume,
            "get_mute": self._do_get_mute,
            "set_mute": self._do_set_mute,
            "action_sequence": self._do_action_sequence,
            "camera_list": self.list_cameras,
            "camera_switch": self.switch_camera,
            "resources": self._get_resources,
            "play_resource": self._play_resource,
            "run_task": self._do_run_task,
        }
        handler = action_map.get(cmd.action)
        if handler is None:
            raise ValueError(f"未知命令: {cmd.action}")
        return handler(**cmd.kwargs)

    # ── TTS ──
    def _do_tts(self, text: str) -> bool:
        from .retry import call_with_retry

        def build():
            req = PlayTts.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()
            req.tts_req.text = text
            req.tts_req.domain = "web_ui"
            req.tts_req.is_interrupted = True
            req.tts_req.priority_level.value = 6
            req.tts_req.priority_weight = 0
            req.tts_req.trace_id = f"web_{self.get_clock().now().nanoseconds}"
            return req
        resp = call_with_retry(self, self.tts_client, build, "PlayTts")
        if resp is not None and resp.tts_resp.is_success:
            # 记录预计耗时(毫秒)，供 wait_tts_done 估时
            self._last_tts_duration_ms = int(resp.tts_resp.estimated_duration or 0)
            return True
        self._last_tts_duration_ms = 0
        return False

    # ── 预设动作 ──
    def _do_motion(self, area: int, motion_id: int) -> dict:
        from .retry import call_with_retry
        from aimdk_msgs.msg import McPresetMotion, McControlArea

        def build():
            req = SetMcPresetMotion.Request()
            req.header.stamp = self.get_clock().now().to_msg()
            req.motion = McPresetMotion(); req.motion.value = motion_id
            req.area = McControlArea(); req.area.value = area
            req.interrupt = False
            return req
        resp = call_with_retry(self, self.motion_client, build, "SetMcPresetMotion")
        if resp is None:
            return {"ok": False, "task_id": None, "error": "timeout"}
        return {
            "ok": resp.response.header.code == 0,
            "task_id": resp.response.task_id,
            "error": None if resp.response.header.code == 0 else "failed",
        }

    # ── 速度控制 ──
    def _register_input_source(self):
        if self._input_registered:
            return
        from .retry import call_with_retry
        from aimdk_msgs.msg import McInputSource, McInputAction

        def build():
            req = SetMcInputSource.Request()
            req.request.header.stamp = self.get_clock().now().to_msg()
            req.action = McInputAction(); req.action.value = 1001
            req.input_source = McInputSource()
            req.input_source.name = "web_ui"
            req.input_source.priority = 40
            req.input_source.timeout = 1000
            return req
        resp = call_with_retry(self, self.input_source_client, build, "SetMcInputSource")
        if resp and resp.response.header.code == 0:
            self._input_registered = True
            logger.info("🕹️ web_ui 已注册运动控制输入源")

    def _ensure_vel_timer(self):
        if self._vel_timer is None:
            self._vel_timer = self.create_timer(0.02, self._publish_velocity)

    def _publish_velocity(self):
        fwd, lat, ang = self._vel_target
        msg = McLocomotionVelocity()
        msg.header = MessageHeader()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.source = "web_ui"
        msg.forward_velocity = float(fwd)
        msg.lateral_velocity = float(lat)
        msg.angular_velocity = float(ang)
        self.vel_publisher.publish(msg)

    def _do_velocity(self, forward: float, lateral: float, angular: float):
        self._register_input_source()
        self._vel_target = (forward, lateral, angular)
        if forward == 0.0 and lateral == 0.0 and angular == 0.0:
            if self._vel_timer:
                self.destroy_timer(self._vel_timer)
                self._vel_timer = None
        else:
            self._ensure_vel_timer()

    # ── 系统状态 ──
    def _do_system(self) -> dict:
        from .retry import call_with_retry

        def build_action():
            req = GetMcAction.Request()
            req.request.header.stamp = self.get_clock().now().to_msg()
            return req
        action_resp = call_with_retry(self, self.action_client, build_action, "GetMcAction")

        def build_sys():
            req = GetSystemState.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()
            return req
        sys_resp = call_with_retry(self, self.sys_client, build_sys, "GetSystemState")

        return {
            "action": {
                "desc": action_resp.info.action_desc if action_resp else "未知",
                "status": action_resp.info.status.value if action_resp else -1,
            } if action_resp else None,
            "system": {
                "state": sys_resp.cur_state if sys_resp else "未知",
                "status": sys_resp.curr_status.value if sys_resp else -1,
            } if sys_resp else None,
        }

    # ── 表情 ──
    def _do_emoji(self, emotion_id: int, mode: int = 1) -> dict:
        from .retry import call_with_retry

        def build():
            req = PlayEmoji.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()
            req.emotion_id = emotion_id
            req.mode = mode
            req.priority = 5
            return req
        resp = call_with_retry(self, self.emoji_client, build, "PlayEmoji")
        ok = resp is not None and resp.success
        return {"ok": ok, "message": resp.message if resp else "timeout"}

    # ── 音量 ──
    def _do_get_volume(self) -> dict:
        from .retry import call_with_retry
        def build(): req = GetVolume.Request(); req.request.header.stamp = self.get_clock().now().to_msg(); return req
        resp = call_with_retry(self, self.vol_get, build, "GetVolume")
        return {"volume": resp.audio_volume if resp else 0}

    def _do_set_volume(self, volume: int) -> dict:
        from .retry import call_with_retry
        def build(): req = SetVolume.Request(); req.request.header.stamp = self.get_clock().now().to_msg(); req.audio_volume = volume; return req
        resp = call_with_retry(self, self.vol_set, build, "SetVolume")
        return {"volume": resp.audio_volume if resp else volume}

    # ── 静音 ──
    def _do_get_mute(self) -> dict:
        from .retry import call_with_retry
        def build(): req = GetMute.Request(); req.request.header.stamp = self.get_clock().now().to_msg(); return req
        resp = call_with_retry(self, self.mute_get, build, "GetMute")
        return {"is_mute": resp.is_mute if resp else False}

    def _do_set_mute(self, is_mute: bool) -> dict:
        from .retry import call_with_retry
        def build(): req = SetMute.Request(); req.request.header.stamp = self.get_clock().now().to_msg(); req.is_mute = is_mute; return req
        resp = call_with_retry(self, self.mute_set, build, "SetMute")
        return {"is_mute": resp.is_mute if resp else is_mute}

    # ── 模式切换 ──
    def _do_mode(self, action_desc: str) -> dict:
        """切换运动模式（v0.8.2+ 用 action_desc 字符串，非数字ID）

        合法值：PASSIVE_DEFAULT(零力矩/急停) / DAMPING_DEFAULT(阻尼) /
        JOINT_DEFAULT(位控站立) / STAND_DEFAULT(稳定站立) / LOCOMOTION_DEFAULT(走跑)
        """
        from .retry import call_with_retry
        from aimdk_msgs.msg import McActionCommand

        def build():
            req = SetMcAction.Request()
            req.header.stamp = self.get_clock().now().to_msg()
            req.source = "web_ui"
            req.command = McActionCommand()
            req.command.action_desc = action_desc
            return req
        resp = call_with_retry(self, self.mode_client, build, "SetMcAction")
        ok = resp is not None and resp.response.header.code == 0
        return {"ok": ok}

    # ── 音视频播放 ──
    def _do_media_play(self, file_path: str, file_name: str) -> dict:
        from .retry import call_with_retry
        from aimdk_msgs.msg import AudioFile, AudioInfo

        ext = file_name.rsplit(".", 1)[-1].lower() if "." in file_name else ""
        is_video = ext in ("mp4", "avi", "mov", "mkv")

        if is_video:
            def build():
                req = PlayVideo.Request()
                req.header.header.stamp = self.get_clock().now().to_msg()
                req.video_path = file_path
                req.mode = 1; req.priority = 5
                return req
            resp = call_with_retry(self, self.video_client, build, "PlayVideo")
            return {"ok": resp is not None and resp.success}
        else:
            def build():
                req = PlayAudioFile.Request()
                req.request.header.stamp = self.get_clock().now().to_msg()
                req.file = AudioFile()
                req.file.pkg_name = "web_ui"; req.file.file_name = file_name; req.file.file_path = file_path
                info = AudioInfo(); info.channels = 1; info.sample_rate = 16000
                req.file.info = info; req.file.priority = 6
                return req
            resp = call_with_retry(self, self.audio_client, build, "PlayAudioFile")
            return {"ok": resp is not None and resp.reponse.header.code == 0}

    # ── Logo 脸屏显示 ──
    def _do_logo_show(self, file_path: str) -> dict:
        """循环播放 logo 视频到脸部屏（PlayVideo mode=2）"""
        from .retry import call_with_retry

        def build():
            req = PlayVideo.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()
            req.video_path = file_path
            req.mode = 2  # 循环播放
            req.priority = 5
            return req
        resp = call_with_retry(self, self.video_client, build, "PlayVideo(logo)")
        ok = resp is not None and resp.success
        return {"ok": ok}

    def _do_logo_hide(self) -> dict:
        """关闭 logo —— PlayVideo 无 stop 字段，切回待机表情覆盖"""
        return self._do_emoji(10, 1)  # EMOTION_IDLE_CALM_1

    # ── 状态查询 ──
    def _get_status(self) -> dict:
        return {
            "battery": self.battery if self.battery else None,
            "arms": self.arm_joints,
            "imu": self.imu if self.imu else None,
        }

    # ── 灵创动作资源 ──
    def _get_resources(self) -> dict:
        """查询机器人所有动作资源（灵创动作包）"""
        from .retry import call_with_retry

        if not self.get_resources_client.wait_for_service(timeout_sec=1.0):
            return {"ok": False, "error": "GetRobotResources 服务不可用", "resources": []}

        def build():
            return GetRobotResources.Request()
        resp = call_with_retry(self, self.get_resources_client, build, "GetRobotResources")
        if resp is None:
            return {"ok": False, "error": "查询超时", "resources": []}

        resources = []
        for r in resp.robot_resources:
            ver = r.current_version
            key = r.resource_key
            # 含 onnx 为全身动作，否则手臂动作
            rtype = "BODY_MOTION" if "onnx" in key else "ARM_MOTION"
            resources.append({
                "resource_key": key,
                "name": ver.name or key,
                "version": ver.version,
                "type": rtype,
            })
        logger.info(f"📦 查询到 {len(resources)} 个灵创动作资源")
        return {"ok": True, "resources": resources}

    def _play_resource(self, resource_key: str, version: str = "", resource_type: str = "") -> dict:
        """执行灵创动作资源"""
        from .retry import call_with_retry

        if not self.play_resource_client.wait_for_service(timeout_sec=1.0):
            return {"ok": False, "error": "ExecuteActionResource 服务不可用"}

        rtype = resource_type or ("BODY_MOTION" if "onnx" in resource_key else "ARM_MOTION")

        def build():
            req = ExecuteActionResource.Request()
            req.resource_key = resource_key
            req.resource_version = version
            req.meta = f'{{"resource_type": "{rtype}"}}'
            return req
        resp = call_with_retry(self, self.play_resource_client, build, "ExecuteActionResource")
        if resp is None:
            return {"ok": False, "error": "执行超时"}
        code = resp.header.header.code
        return {"ok": code == 0, "code": code, "message": resp.header.message}

    # ── 工具方法 ──
    def _sleep(self, sec: float):
        """rclpy 安全的 sleep（用 spin_once 循环替代 time.sleep）"""
        t0 = time.time()
        while time.time() - t0 < sec:
            from rclpy import spin_once as _spin_once
            _spin_once(self, timeout_sec=0.01)

    # ── 动作序列 ──
    def _do_action_sequence(self) -> dict:
        logger.info("🎬 动作序列开始")
        self._register_input_source()
        self._sleep(0.5)
        self._do_velocity(0.3, 0.0, 0.0); self._sleep(3.0)
        self._do_velocity(0.0, 0.0, 0.0); self._sleep(0.5)
        logger.info("🎬 双手比心")
        self._do_motion(2, 1007); self._sleep(2.5)   # 右手比心
        self._do_motion(1, 1007); self._sleep(2.5)   # 左手比心
        logger.info("🎬 转身180°")
        self._do_velocity(0.0, 0.0, 0.5); self._sleep(math.pi / 0.5)
        self._do_velocity(0.0, 0.0, 0.0); self._sleep(0.5)
        self._do_velocity(0.3, 0.0, 0.0); self._sleep(3.0)
        self._do_velocity(0.0, 0.0, 0.0)
        logger.info("🎬 动作序列完成")
        return {"ok": True}

    def _do_run_task(self, task: dict, engine) -> dict:
        """在 rclpy 线程中执行编排任务"""
        engine.run(self, task)
        return engine.get_status()


# ── 模块级引用（供 routes 直接使用）──
_cmd_queue: CommandQueue | None = None
