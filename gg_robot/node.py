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
from aimdk_msgs.msg import McLocomotionVelocity, PmuState, MessageHeader, PlayStateChange, JointStateArray
from sensor_msgs.msg import Imu, CompressedImage

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
        self._sensor_recv = {"battery": 0, "arm": 0, "imu": 0}  # 收消息计数（诊断）

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
        self._camera_frame_count: int = 0          # 收帧计数（用于诊断）
        self._camera_first_ts: float = 0.0         # 首帧时间
        self._camera_last_ts: float = 0.0          # 末帧时间（供 camera_pusher 诊断无帧）

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
        self.create_subscription(JointStateArray, "/aima/hal/joint/arm/state", self._on_arm, qos_profile_sensor_data)
        self.create_subscription(Imu, "/aima/hal/imu/torso/state", self._on_imu, qos_profile_sensor_data)

        # ── 订阅音频播放状态（TTS 完成事件）──
        self.create_subscription(PlayStateChange, "/aima/hal/audio/play_state", self._on_play_state, qos_profile_sensor_data)

        # ── 自动选择第一个有数据的相机 ──
        self._auto_select_camera()

        # ── 速度控制状态 ──
        self._input_registered = False
        self._vel_target = (0.0, 0.0, 0.0)
        # 常驻 50Hz 速度发布定时器：在 __init__（rclpy 线程）创建一次，永不 create/destroy。
        # 否则 cmd 线程在 _do_velocity 里频繁 create/destroy timer 会与 executor 竞态，
        # 导致 executor.spin() 卡死、传感器回调停（ros2 topic hz 显示 publisher 正常，
        # 但 gg_robot 收不到更新，前端表现为数据冻结）。timer 由 executor 调度，
        # _do_velocity 只读写 _vel_target（tuple 整体替换，GIL 原子）。
        self._vel_timer = self.create_timer(0.02, self._publish_velocity)

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
        self._sensor_recv["battery"] += 1
        if self._sensor_recv["battery"] == 1:
            logger.info("🔋 首条 PmuState 收到，电池订阅正常")
        self.battery = {
            "percentage": round(msg.battery_remaining_capacity_percentage, 1),
            "voltage": round(msg.battery_pack_voltage, 2),
            "current": round(msg.battery_current, 2),
            "temperature": round(msg.battery_temperature, 1),
            "power": round(msg.battery_output_power, 1),
        }

    def _on_arm(self, msg):
        self._sensor_recv["arm"] += 1
        if self._sensor_recv["arm"] == 1:
            logger.info("🦾 首条 JointStateArray 收到，手臂订阅正常")
        # aimdk_msgs/JointStateArray：msg.joints 是对象数组，每个含 name/position/velocity/effort
        self.arm_joints = [
            {"name": j.name, "position": round(j.position, 3), "velocity": round(j.velocity, 3)}
            for j in msg.joints
        ]

    def _on_imu(self, msg):
        self._sensor_recv["imu"] += 1
        if self._sensor_recv["imu"] == 1:
            logger.info("📐 首条 Imu 收到，IMU 订阅正常")
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
            self._camera_last_ts = self._camera_timestamp
            self._camera_frame_count += 1

            # 首帧日志 + 每300帧(约10秒@30Hz)统计一次
            if self._camera_frame_count == 1:
                self._camera_first_ts = self._camera_timestamp
                logger.info(f"📷 收到首帧！相机={self._active_camera}, 大小={len(self._camera_frame)}B")
            elif self._camera_frame_count % 300 == 0:
                elapsed = self._camera_timestamp - self._camera_first_ts
                avg_fps = self._camera_frame_count / max(elapsed, 0.001)
                logger.info(f"📷 相机帧 #{self._camera_frame_count}, 大小={len(self._camera_frame)}B, 平均fps≈{avg_fps:.0f}")

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
        start = time.time()
        est_ms = getattr(self, "_last_tts_duration_ms", 0) or 0
        # 估时(秒) + 0.3s 余量；无估值时退化为纯等事件
        target = start + (est_ms / 1000.0 + 0.3) if est_ms > 0 else None
        deadline = start + timeout
        while time.time() < deadline:
            # play_state 收到 STOPED（且本次期间）→ 提前返回
            # executor 在独立线程 spin，回调正常触发，无需在此手动 spin
            if self._play_state == 2 and self._play_state_ts > start:
                return True
            # 已等够 estimated_duration → 视为播完
            if target is not None and time.time() >= target:
                return True
            time.sleep(0.05)
        logger.warning(f"⏱️ TTS 等待超时({timeout}s)，est={est_ms}ms")
        return False

    def _get_action_status(self) -> int | None:
        """查询当前运动状态（GetMcAction.info.status.value：0=IDLE 100=RUNNING 200=TRANSITION）"""
        req = GetMcAction.Request()
        req.request.header.stamp = self.get_clock().now().to_msg()
        future = self.action_client.call_async(req)
        t0 = time.monotonic()
        while time.monotonic() - t0 < 0.5:
            if future.done():
                r = future.result()
                return r.info.status.value if r else None
            time.sleep(0.02)
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
        """返回所有相机及当前选中状态"""
        result = []
        for cam_id, cfg in self._camera_topics.items():
            result.append({
                "id": cam_id,
                "label": cfg["label"],
                "topic": cfg["topic"],
                "active": True,
                "selected": cam_id == self._active_camera,
            })
        return result

    def switch_camera(self, camera_id: str) -> dict:
        """切换到指定相机"""
        if camera_id not in self._camera_topics:
            return {"ok": False, "error": f"未知相机: {camera_id}"}

        cfg = self._camera_topics[camera_id]
        cfg["active"] = True
        # 不预检 topic 是否已被 DDS 发现：create_subscription 直接订阅，
        # DDS 会自动匹配 publisher（跨板 discovery 延迟也能后续收到）

        # 销毁旧订阅
        if self._cam_sub is not None:
            self.destroy_subscription(self._cam_sub)
            self._cam_sub = None

        # 清空帧缓存 + 重置诊断计数器
        with self._camera_lock:
            self._camera_frame = None
            self._camera_timestamp = 0.0
            self._camera_frame_count = 0
            self._camera_first_ts = 0.0
            self._camera_last_ts = 0.0

        # 用内置 qos_profile_sensor_data（完整 DDS profile）。ros2 topic echo 即用此类 QoS，
        # 实测能匹配 RELIABLE+VOLATILE publisher 稳定收到 30Hz JPEG（publisher 在线、echo 可收、
        # 仅 gg_robot 收不到 → 排除驱动/网络/QoS 兼容性）。
        # ⚠️ 之前手搓 QoSProfile(reliability=RELIABLE, durability=VOLATILE, history=KEEP_LAST, depth=1)
        # 字段不全（lifespan/deadline/liveliness 未设），DDS 协商失败、Subscription count=0、收不到帧。
        # 更早用 qos_profile_sensor_data "收不到" 的真正原因是 executor 卡死（_on_camera 不调度），
        # 非 QoS —— 现已修（常驻 timer 消除 cmd 线程 timer 竞态）。
        qos = qos_profile_sensor_data
        self._cam_sub = self.create_subscription(
            CompressedImage,
            cfg["topic"],
            self._on_camera,
            qos,
        )
        self._active_camera = camera_id
        logger.info(f"📷 切换相机: {cfg['label']} ({cfg['topic']}) qos=qos_profile_sensor_data")
        return {"ok": True, "camera": cfg["label"], "topic": cfg["topic"]}

    def get_active_camera(self) -> str:
        """返回当前活跃相机 ID"""
        return self._active_camera

    def _auto_select_camera(self):
        """直接订阅第一个相机（推荐 RGBD 前视）。
        create_subscription 不依赖 topic 已被 DDS 发现，订阅创建后 publisher 出现即匹配。"""
        for cam_id in self._camera_topics:
            self.switch_camera(cam_id)
            break
        if self._active_camera:
            cfg = self._camera_topics[self._active_camera]
            logger.info(f"📷 自动选择相机: {cfg['label']}")

    def _try_select_camera_once(self) -> bool:
        """单次尝试选相机（非阻塞）：DDS 发现 topic 就订阅第一个可用相机"""
        if self._active_camera:
            return True
        topic_names = {t for t, _ in self.get_topic_names_and_types()}
        for cam_id, cfg in self._camera_topics.items():
            if cfg["topic"] in topic_names:
                self.switch_camera(cam_id)
                logger.info(f"📷 后台自动订阅相机: {cfg['label']}")
                return True
        return False

    # ── 命令处理 ──
    def process_commands(self):
        """处理命令队列中的待执行命令（由 rclpy 线程调用）"""
        # 相机兜底：DDS 跨 SoC 发现需时（10-30s+），不主动销毁订阅切换，
        # 否则每次切换都会重置 DDS 发现过程。订阅创建后等待 publisher 自然匹配即可。
        # 仅打印诊断日志，切换由用户通过 API 手动触发。
        if self._active_camera and self._camera_last_ts == 0.0:
            now = time.time()
            cam_wait_start = getattr(self, '_cam_wait_start', 0.0)
            if cam_wait_start == 0.0:
                self._cam_wait_start = now
            elif now - cam_wait_start > 60.0:
                # 60s 还没帧，打印提示但不切换（DDS 没发现 publisher 的话切换也没用）
                logger.warning(
                    f"📷 {self._active_camera} 已等待 {now - cam_wait_start:.0f}s 仍未收到帧，"
                    f"继续等待 DDS 发现...（可用 ros2 topic info 确认 publisher 是否在线）"
                )
                self._cam_wait_start = now  # 重置，下次60s后再提醒
        elif self._active_camera and self._camera_last_ts > 0.0:
            self._cam_wait_start = 0.0  # 有帧则重置

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

    def _publish_velocity(self):
        # 未注册输入源前不发布（避免无意义流量）；注册后持续 50Hz 发，全零=停车。
        if not self._input_registered:
            return
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
        # 只更新目标速度（tuple 原子替换）。timer 常驻，不在此 create/destroy，
        # 避免 cmd 线程操作 rclpy 实体触发 executor 竞态卡死 spin。
        # 全零时常驻 timer 持续发全零 = 停车，满足「持续 50Hz、松开发全零」要求。
        self._vel_target = (forward, lateral, angular)

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
        from aimdk_msgs.msg import AudioFile

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
            import os
            def build():
                req = PlayAudioFile.Request()
                req.request.header.stamp = self.get_clock().now().to_msg()
                req.file = AudioFile()
                req.file.pkg_name = "web_ui"
                req.file.file_name = file_name                          # 仅文件名
                req.file.file_path = os.path.dirname(file_path) + '/'   # 目录(带斜杠)
                req.file.priority = 6
                req.file.priority_weight = 0
                return req
            resp = call_with_retry(self, self.audio_client, build, "PlayAudioFile", timeout=5.0, retries=1)
            # 注意：PlayAudioFile.Response 的字段官方就叫 reponse（少个s，aimdk 笔误），
            # 详见 docs/aimdk install/aimdk_msgs/share/aimdk_msgs/srv/PlayAudioFile.srv。勿"修正"为 response。
            ok = resp is not None and resp.reponse.status.value == 1
            return {"ok": ok}

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
        """命令线程安全的 sleep（executor 在独立线程 spin，不会饿死回调）"""
        end = time.monotonic() + sec
        while time.monotonic() < end:
            time.sleep(min(0.05, max(0.0, end - time.monotonic())))

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
