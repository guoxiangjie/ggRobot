"""X2 ROS2 节点 — Service 客户端 + 传感器订阅 + 相机帧缓存

改造要点（相比旧版）：
1. 添加 RGBD 相机订阅 + 帧缓存（供 WebSocket 推送）
2. 添加 MIC VAD 采集（/agent/process_audio_output）+ 可插拔 ASR（funasr/none）
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
from rclpy.qos import qos_profile_sensor_data
from rclpy.callback_groups import ReentrantCallbackGroup

from aimdk_msgs.srv import (
    PlayTts, SetMcPresetMotion, GetMcAction, SetMcAction,
    GetSystemState, MigrateSystemState, PlayEmoji, PlayAudioFile, PlayVideo,
    SetVolume, GetVolume, SetMute, GetMute, SetMcInputSource,
    GetRobotResources, ExecuteActionResource,
    GetMicSourceRequest, SetMicSourceRequest,
)
from aimdk_msgs.msg import McLocomotionVelocity, PmuState, MessageHeader, PlayStateChange, JointStateArray, ProcessedAudioOutput
from sensor_msgs.msg import Imu, CompressedImage

from .config import VEL_SOURCE_NAME, VEL_PUBLISH_RATE

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
        # 独立 ReentrantCallbackGroup：service response 回调走单独线程，避免和高频传感器回调
        # (IMU 500Hz / arm 450Hz / vel timer 50Hz，都在 default MutuallyExclusive group 的同一个线程)
        # 抢占导致 response 饿死、call_async 的 future 永不 done、retry 全超时。
        g = ReentrantCallbackGroup()
        self._srv_group = g
        self.tts_client = self.create_client(PlayTts, "/aimdk_5Fmsgs/srv/PlayTts", callback_group=g)
        self.motion_client = self.create_client(SetMcPresetMotion, "/aimdk_5Fmsgs/srv/SetMcPresetMotion", callback_group=g)
        self.action_client = self.create_client(GetMcAction, "/aimdk_5Fmsgs/srv/GetMcAction", callback_group=g)
        self.mode_client = self.create_client(SetMcAction, "/aimdk_5Fmsgs/srv/SetMcAction", callback_group=g)
        self.sys_client = self.create_client(GetSystemState, "/aimdk_5Fmsgs/srv/GetSystemState", callback_group=g)
        self.migrate_client = self.create_client(MigrateSystemState, "/aimdk_5Fmsgs/srv/MigrateSystemState", callback_group=g)
        self.emoji_client = self.create_client(PlayEmoji, "/aimdk_5Fmsgs/srv/PlayEmoji", callback_group=g)
        self.audio_client = self.create_client(PlayAudioFile, "/aimdk_5Fmsgs/srv/PlayAudioFile", callback_group=g)
        self.video_client = self.create_client(PlayVideo, "/face_ui_proxy/play_video", callback_group=g)
        self.input_source_client = self.create_client(SetMcInputSource, "/aimdk_5Fmsgs/srv/SetMcInputSource", callback_group=g)
        self.vol_get = self.create_client(GetVolume, "/aimdk_5Fmsgs/srv/GetVolume", callback_group=g)
        self.vol_set = self.create_client(SetVolume, "/aimdk_5Fmsgs/srv/SetVolume", callback_group=g)
        self.mute_get = self.create_client(GetMute, "/aimdk_5Fmsgs/srv/GetMute", callback_group=g)
        self.mute_set = self.create_client(SetMute, "/aimdk_5Fmsgs/srv/SetMute", callback_group=g)
        self.get_resources_client = self.create_client(GetRobotResources, "/aimdk_5Fmsgs/srv/GetRobotResources", callback_group=g)
        self.play_resource_client = self.create_client(ExecuteActionResource, "/aimdk_5Fmsgs/srv/ExecuteActionResource", callback_group=g)
        self.mic_get_client = self.create_client(GetMicSourceRequest, "/aimdk_5Fmsgs/srv/GetMicSourceRequest", callback_group=g)
        self.mic_set_client = self.create_client(SetMicSourceRequest, "/aimdk_5Fmsgs/srv/SetMicSourceRequest", callback_group=g)

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
        self._pending_camera: str | None = None  # cmd 线程设、rclpy 线程消费（避免 cmd 线程 create_subscription 竞态）

        # ── 订阅传感器 ──
        self.create_subscription(PmuState, "/aima/hal/pmu/state", self._on_battery, qos_profile_sensor_data)
        self.create_subscription(JointStateArray, "/aima/hal/joint/arm/state", self._on_arm, qos_profile_sensor_data)
        self.create_subscription(Imu, "/aima/hal/imu/torso/state", self._on_imu, qos_profile_sensor_data)

        # ── 订阅音频播放状态（TTS 完成事件）──
        self.create_subscription(PlayStateChange, "/aima/hal/audio/play_state", self._on_play_state, qos_profile_sensor_data)

        # ── MIC VAD 采集（/agent/process_audio_output）──
        # 机器人侧 agent 已做降噪 + VAD；需要先唤醒词激活（v0.9+，见 CLAUDE.md）。
        # 无论内置/外置麦，数据都走 stream_id=1；识别到语言后堆积数据先极速发出，后续约 25Hz。
        self.mic_enabled = False          # 前端开关：开启后才做 ASR（采集/状态始终跟踪）
        self._mic_lock = threading.Lock()
        self._vad_state = 0               # 0=无语音 1=开始 2=处理中 3=结束
        self._mic_segment = b""           # 当前正在累积的语音段
        self._mic_segment_ts = 0.0
        self._mic_last_segment = b""      # 最近一个完整语音段（VAD END 触发）
        self._mic_last_segment_ts = 0.0
        self._mic_last_segment_size = 0
        self._mic_text = ""               # 最近识别结果
        self._mic_source = 0              # 0=内置麦 1=外置麦
        self._mic_recv = 0                # 收消息计数（诊断）
        self._asr_busy = False
        self._mic_sub = self.create_subscription(
            ProcessedAudioOutput, "/agent/process_audio_output", self._on_mic, qos_profile_sensor_data)

        # ── 自动选择第一个有数据的相机 ──
        self._auto_select_camera()

        # ── 速度控制状态 ──
        self._input_registered = False
        self._vel_target = (0.0, 0.0, 0.0)

        # ── 自由任务节点执行状态 ──
        self._node_running_id: str = ""   # 当前正在执行的自由节点 id（空=空闲）
        self._node_stop_flag: bool = False
        # 常驻 50Hz 速度发布定时器：在 __init__（rclpy 线程）创建一次，永不 create/destroy。
        # 否则 cmd 线程在 _do_velocity 里频繁 create/destroy timer 会与 executor 竞态，
        # 导致 executor.spin() 卡死、传感器回调停（ros2 topic hz 显示 publisher 正常，
        # 但 gg_robot 收不到更新，前端表现为数据冻结）。timer 由 executor 调度，
        # _do_velocity 只读写 _vel_target（tuple 整体替换，GIL 原子）。
        self._vel_timer = self.create_timer(1.0 / max(VEL_PUBLISH_RATE, 1), self._publish_velocity)
        # 相机切换在 rclpy 线程执行：cmd 线程 destroy/create subscription 会与 executor.spin() 竞态，
        # 导致新订阅未注册进 executor、_on_camera 永不调度（所有相机收不到帧，同 velocity timer 的坑）
        self._cam_switch_timer = self.create_timer(0.1, self._process_camera_switch)

        self._wait_services()
        logger.info("✅ X2Node 就绪")

    def _wait_services(self, timeout: float = 10.0):
        """等待所有 Service 就绪（容错，不阻塞启动）。

        ⚠️ 开发者模式下部分原生服务会被停用、从 DDS 消失：
          Develop_Audio_Linux/ROS 停 hal_audio → PlayAudioFile/PlayTts/音量/静音等消失
          Develop_MC 停运控 → SetMcAction 等消失
        这是预期行为，对缺失的 service 只告警、不抛异常。否则一旦切了开发者模式，
        ggRobot 起不来、Web UI 用不了，会被锁死、无法切回 Ready。
        timeout 控制在 10s 内（< __main__.wait_for_queue 的 15s），正常态下服务几乎立即可用。
        """
        clients = [
            ("PlayTts", self.tts_client), ("SetMcPresetMotion", self.motion_client),
            ("GetMcAction", self.action_client), ("SetMcAction", self.mode_client),
            ("GetSystemState", self.sys_client), ("PlayEmoji", self.emoji_client),
            ("PlayAudioFile", self.audio_client), ("PlayVideo", self.video_client),
            ("GetVolume", self.vol_get), ("SetVolume", self.vol_set),
            ("GetMute", self.mute_get), ("SetMute", self.mute_set),
            ("SetMcInputSource", self.input_source_client),
            ("GetMicSourceRequest", self.mic_get_client), ("SetMicSourceRequest", self.mic_set_client),
        ]
        deadline = time.time() + timeout
        pending = dict(clients)
        while pending and time.time() < deadline:
            for name in list(pending):
                if pending[name].wait_for_service(timeout_sec=0.3):
                    del pending[name]
        ready = len(clients) - len(pending)
        logger.info(f"⏳ 服务就绪 {ready}/{len(clients)}" + ("，其余等待超时放弃" if pending else ""))
        for name in pending:
            logger.warning(f"⚠ 服务未就绪（开发者模式下可能正常）: {name}")
        if pending:
            logger.warning(f"⚠ {len(pending)} 个服务未就绪，对应功能不可用；可在控制页查看/切换系统态")

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

    # ── MIC VAD 采集 ──
    def _on_mic(self, msg: ProcessedAudioOutput):
        """VAD 音频段回调：按 VAD 状态累积/封包，结束后台 ASR（绝不阻塞 rclpy 回调）"""
        self._mic_recv += 1
        vad = msg.audio_vad_state.value if msg.audio_vad_state else 0
        data = bytes(msg.audio_data) if msg.audio_data else b""

        with self._mic_lock:
            self._vad_state = vad
            if msg.stream_id != 1:   # 数据统一走 stream_id=1
                return
            if vad == 3:  # 语音结束 → 封包
                if data:
                    self._mic_segment += data
                self._mic_last_segment = self._mic_segment
                self._mic_last_segment_ts = time.time()
                self._mic_last_segment_size = len(self._mic_segment)
                self._mic_segment = b""
                self._mic_segment_ts = 0.0
                segment = self._mic_last_segment
                if segment and self.mic_enabled and not self._asr_busy:
                    self._asr_busy = True
                    threading.Thread(target=self._asr_worker, args=(segment,), daemon=True).start()
            elif vad in (1, 2):  # 开始/处理中 → 累积
                if not self._mic_segment_ts:
                    self._mic_segment_ts = time.time()
                self._mic_segment += data
                # 防 VAD END 漏收导致无限增长
                if len(self._mic_segment) > 2 * 1024 * 1024:
                    self._mic_segment = self._mic_segment[-2 * 1024 * 1024:]
            else:  # 0=无语音
                self._mic_segment = b""
                self._mic_segment_ts = 0.0

    def _asr_worker(self, segment: bytes):
        """后台识别线程：识别结果写回 _mic_text"""
        try:
            from .asr import get_asr_engine
            text = get_asr_engine().recognize(segment)
            with self._mic_lock:
                if text:
                    self._mic_text = text
                    logger.info(f"🎙️ 识别结果: {text}")
        except Exception as e:
            logger.warning(f"🎙️ ASR 异常: {e}")
        finally:
            self._asr_busy = False

    def get_mic_status(self) -> dict:
        """MIC 采集/识别状态（路由直接读，无需进命令队列）"""
        with self._mic_lock:
            return {
                "enabled": self.mic_enabled,
                "vad_state": self._vad_state,
                "segment_bytes": len(self._mic_segment),
                "last_segment_bytes": self._mic_last_segment_size,
                "last_segment_ts": self._mic_last_segment_ts,
                "mic_source": self._mic_source,
                "text": self._mic_text,
                "recv_count": self._mic_recv,
            }

    # ── 麦克风设备 ──
    def _do_get_mic_source(self) -> dict:
        from .retry import call_with_retry

        def build():
            req = GetMicSourceRequest.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()  # CommonRequest → 两层
            return req
        resp = call_with_retry(self, self.mic_get_client, build, "GetMicSourceRequest")
        if resp is not None:
            self._mic_source = resp.mic_source
            return {"ok": True, "mic_source": resp.mic_source}
        return {"ok": False, "mic_source": self._mic_source, "message": "查询超时"}

    def _do_set_mic_source(self, mic_source: int) -> dict:
        from .retry import call_with_retry

        def build():
            req = SetMicSourceRequest.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()
            req.mic_source = mic_source
            return req
        resp = call_with_retry(self, self.mic_set_client, build, "SetMicSourceRequest")
        if resp is not None:
            self._mic_source = mic_source
            return {"ok": True, "mic_source": mic_source}
        return {"ok": False, "mic_source": self._mic_source, "message": "切换超时"}

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
        """切换到指定相机（cmd 线程入口）：只登记目标，真正的 destroy/create 在 rclpy 线程做。

        ⚠️ destroy_subscription/create_subscription 不能在 cmd 线程做 —— 会与 executor.spin() 竞态，
        导致新订阅没注册进 executor、_on_camera 永不调度（所有相机收不到帧）。
        同 velocity timer 的坑（已改常驻）。这里只设 _pending_camera 标志，
        由 _cam_switch_timer 在 rclpy 线程消费。
        """
        if camera_id not in self._camera_topics:
            return {"ok": False, "error": f"未知相机: {camera_id}"}
        self._camera_topics[camera_id]["active"] = True
        self._pending_camera = camera_id
        cfg = self._camera_topics[camera_id]
        return {"ok": True, "camera": cfg["label"], "topic": cfg["topic"]}

    def _process_camera_switch(self):
        """rclpy 线程（timer 回调）：执行待处理的相机切换。

        create/destroy subscription 在此线程做，与 executor 实体管理一致，避免竞态。
        """
        cam_id = self._pending_camera
        if cam_id is None:
            return
        self._pending_camera = None
        if cam_id not in self._camera_topics:
            return
        cfg = self._camera_topics[cam_id]

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

        # qos_profile_sensor_data（= SensorDataQoS: BEST_EFFORT+VOLATILE），与官方 echo_camera_rgbd 一致，
        # 能匹配 RELIABLE publisher。之前"收不到"的根因是 cmd 线程竞态（见上），非 QoS。
        qos = qos_profile_sensor_data
        self._cam_sub = self.create_subscription(
            CompressedImage, cfg["topic"], self._on_camera, qos,
        )
        self._active_camera = cam_id
        pub_count = self.count_publishers(cfg["topic"])
        logger.info(
            f"📷 切换相机[rclpy线程]: {cfg['label']} ({cfg['topic']}) | "
            f"publisher={pub_count}（0=驱动未发布/discovery 未完成，>0=有发布者）"
        )

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
            elif now - cam_wait_start > 15.0:
                # 15s 还没帧：探测 publisher，区分「驱动没起」vs「有发布者但 DDS/QoS 没匹配」
                topic = self._camera_topics[self._active_camera]["topic"]
                pub_count = self.count_publishers(topic)
                logger.warning(
                    f"📷 {self._active_camera} 已等待 {now - cam_wait_start:.0f}s 仍未收到帧 | "
                    f"topic={topic} publisher={pub_count}"
                    f"（0=驱动未发布该 topic；>0=有发布者但 DDS 未匹配/QoS 不兼容）"
                )
                self._cam_wait_start = now  # 重置，下次再提醒
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
            "migrate_system_state": self._do_migrate_system_state,
            "mode": self._do_mode,
            "emoji": self._do_emoji,
            "media_play": self._do_media_play,
            "logo_show": self._do_logo_show,
            "logo_hide": self._do_logo_hide,
            "get_volume": self._do_get_volume,
            "set_volume": self._do_set_volume,
            "get_mute": self._do_get_mute,
            "set_mute": self._do_set_mute,
            "mic_source_get": self._do_get_mic_source,
            "mic_source_set": self._do_set_mic_source,
            "action_sequence": self._do_action_sequence,
            "camera_list": self.list_cameras,
            "camera_switch": self.switch_camera,
            "resources": self._get_resources,
            "play_resource": self._play_resource,
            "run_task": self._do_run_task,
            "run_node": self._do_run_node,
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
    def _do_motion(self, area: int, motion_id: int, interrupt: bool = True) -> dict:
        """预设动作 SetMcPresetMotion（文档 5.1.4）。

        interrupt=True（默认，文档最佳实践）：打断当前正在执行的动作，新动作立即生效——
        连续触发时后者能执行，避免被前一个未完成的动作拒绝（"概率不执行"问题）。
        ⚠️ 所有预设动作必须在 STAND_DEFAULT（稳定站立）模式下执行；area 无 0，
        只有文档 tbl-preset-motion 列出的 (motion,area) 组合有效（见 web/src/config/motions.ts）。
        """
        from .retry import call_with_retry
        from aimdk_msgs.msg import McPresetMotion, McControlArea

        def build():
            req = SetMcPresetMotion.Request()
            req.header.stamp = self.get_clock().now().to_msg()
            req.motion = McPresetMotion(); req.motion.value = motion_id
            req.area = McControlArea(); req.area.value = area
            req.interrupt = interrupt
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

        # 先注销可能残留的 web_ui（gg_robot 重启后机器人侧可能仍有旧注册，
        # 直接 1001 注册会 code=1 失败）。照 navigation/avoidance.py 先删后注模式。
        def build_unregister():
            req = SetMcInputSource.Request()
            req.request.header.stamp = self.get_clock().now().to_msg()
            req.action = McInputAction(); req.action.value = 1003
            req.input_source = McInputSource(); req.input_source.name = VEL_SOURCE_NAME
            return req
        call_with_retry(self, self.input_source_client, build_unregister, "SetMcInputSource(unregister)")
        self._sleep(0.3)

        def build():
            req = SetMcInputSource.Request()
            req.request.header.stamp = self.get_clock().now().to_msg()
            req.action = McInputAction(); req.action.value = 1001
            req.input_source = McInputSource()
            req.input_source.name = VEL_SOURCE_NAME
            req.input_source.priority = 40
            req.input_source.timeout = 1000
            return req
        resp = call_with_retry(self, self.input_source_client, build, "SetMcInputSource")
        if resp and resp.response.header.code == 0:
            self._input_registered = True
            logger.info(f"🕹️ {VEL_SOURCE_NAME} 已注册运动控制输入源")
        else:
            logger.warning(f"🕹️ {VEL_SOURCE_NAME} 输入源注册失败: resp={resp}")

    def _publish_velocity(self):
        # 未注册输入源前不发布（避免无意义流量）；注册后持续 50Hz 发，全零=停车。
        if not self._input_registered:
            return
        fwd, lat, ang = self._vel_target
        msg = McLocomotionVelocity()
        msg.header = MessageHeader()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.source = VEL_SOURCE_NAME
        msg.forward_velocity = float(fwd)
        msg.lateral_velocity = float(lat)
        msg.angular_velocity = float(ang)
        self.vel_publisher.publish(msg)

    def _do_velocity(self, forward: float, lateral: float, angular: float):
        if not self._input_registered:
            logger.info(f"🕹️ 收到首次 velocity: f={forward} l={lateral} a={angular}")
        self._register_input_source()
        # 只更新目标速度（tuple 原子替换）。timer 常驻，不在此 create/destroy，
        # 避免 cmd 线程操作 rclpy 实体触发 executor 竞态卡死 spin。
        # 全零时常驻 timer 持续发全零 = 停车，满足「持续 50Hz、松开发全零」要求。
        self._vel_target = (forward, lateral, angular)

    # ── 系统状态 ──
    def _do_system(self) -> dict:
        """查询运动模式(GetMcAction) + 系统态(GetSystemState)。

        两路独立 try + 防御性解析：任一路失败/字段缺失不影响另一路，也避免异常上抛
        导致整个 /api/system 500（前端表现为状态"未知"）。
        """
        from .retry import call_with_retry

        # 运动模式（GetMcAction）—— CommonRequest request → req.request.header.stamp
        action_info = None
        try:
            def build_action():
                req = GetMcAction.Request()
                req.request.header.stamp = self.get_clock().now().to_msg()
                return req
            r = call_with_retry(self, self.action_client, build_action, "GetMcAction")
            if r is not None:
                info = getattr(r, "info", None)
                st = getattr(info, "status", None) if info else None
                action_info = {
                    "desc": getattr(info, "action_desc", "未知") if info else "未知",
                    "status": st.value if st is not None else -1,
                }
        except Exception as e:
            logger.warning(f"GetMcAction 查询/解析异常: {e}")

        # 系统态（GetSystemState）—— CommonRequest header → req.header.header.stamp
        system_info = None
        try:
            def build_sys():
                req = GetSystemState.Request()
                req.header.header.stamp = self.get_clock().now().to_msg()
                return req
            r = call_with_retry(self, self.sys_client, build_sys, "GetSystemState")
            if r is not None:
                cs = getattr(r, "curr_status", None)
                system_info = {
                    "state": getattr(r, "cur_state", "") or "",
                    "status": cs.value if cs is not None else -1,
                }
                logger.info(f"📊 系统态: state={system_info['state']} status={system_info['status']}")
            else:
                logger.warning("GetSystemState 无响应（重试失败），系统态未知")
        except Exception as e:
            logger.warning(f"GetSystemState 查询/解析异常: {e}")

        return {"action": action_info, "system": system_info}

    # ── 开发者模式 / 系统状态迁移 ──
    def _do_migrate_system_state(self, state: str) -> dict:
        """切换系统状态/开发者模式（MigrateSystemState），发起后轮询 GetSystemState 阻塞到迁移完成。

        ⚠️ Develop_MC 会停用原生运动控制（直接给 ethercat 发数据做全身控制），
        机器人将失去站立/行走保护，可能摔倒 —— 仅在安全场地、明确知情下使用。
        完成开发后务必切回 Ready 或整机重启（文档 5.6.4 安全注意事项）。
        """
        from .retry import call_with_retry

        if not self.migrate_client.wait_for_service(timeout_sec=1.0):
            return {"ok": False, "message": "MigrateSystemState 服务不可用"}

        def build_migrate():
            req = MigrateSystemState.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()  # CommonRequest header → 两层
            req.state = state
            return req
        resp = call_with_retry(self, self.migrate_client, build_migrate, "MigrateSystemState")
        if resp is None:
            return {"ok": False, "message": "MigrateSystemState 服务超时"}
        code = resp.header.header.code  # CommonResponse header → 两层
        if code != 0:
            return {"ok": False, "code": code, "message": resp.header.message or "迁移请求被拒绝"}

        # 迁移需数秒（状态机 IN_READY→IN_MOVE→IN_READY）。轮询 GetSystemState 确认完成。
        # ⚠️ 不能用 cur_state == 目标值 判定：切回 Ready 时实测 cur_state 变为业务态 "Business"
        # （非 "Ready"），只有 Develop_* 态才与目标同名。故改用「status==IN_READY(1) 且 cur_state
        # 已离开迁移前状态」判定，并返回真实 cur_state。复用 _do_system 的 build_sys。
        def build_sys():
            req = GetSystemState.Request()
            req.header.header.stamp = self.get_clock().now().to_msg()
            return req
        before = call_with_retry(self, self.sys_client, build_sys, "GetSystemState(before)", timeout=1.0, retries=1)
        before_state = before.cur_state if before else ""
        # 停用系统节点（如 hal_audio）的迁移跨板、较慢，给足窗口。
        deadline = time.monotonic() + 20.0
        cur_state, cur_status = before_state, -1
        saw_move = False
        while time.monotonic() < deadline:
            self._sleep(0.5)
            sys_resp = call_with_retry(self, self.sys_client, build_sys, "GetSystemState(poll)", timeout=1.0, retries=1)
            if sys_resp:
                cur_state = sys_resp.cur_state
                cur_status = sys_resp.curr_status.value
                if cur_status == 2:  # IN_MOVE：迁移进行中
                    saw_move = True
                if cur_status == 1 and cur_state.lower() != before_state.lower():  # 离开迁移前态且就绪
                    logger.info(f"🔄 开发者模式迁移完成: {before_state} → {cur_state}")
                    return {"ok": True, "code": code, "state": cur_state, "status": cur_status}
        # 超时：若观察到进入迁移态（status 曾==2 或当前==2），迁移已发起只是没在窗口内完成 —— 不算失败
        if saw_move or cur_status == 2:
            logger.info(f"🔄 迁移仍在进行中(超时窗口内未完成): target={state} {before_state}→{cur_state} status={cur_status}")
            return {"ok": True, "in_progress": True, "code": code, "state": cur_state, "status": cur_status,
                    "message": "迁移已发起，仍在进行中，请稍后刷新查看"}
        logger.warning(f"🔄 迁移未生效: target={state} {before_state}→{cur_state} status={cur_status}")
        return {"ok": False, "code": code, "state": cur_state, "status": cur_status,
                "message": f"迁移未生效（当前 {cur_state}）"}

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
    def _do_mode(self, action_desc: str = "", action_value: int = 0) -> dict:
        """切换运动模式。action_value（数字 ID）优先且最可靠；
        action_desc 字符串只对示例列的 5 种（PASSIVE/DAMPING/JOINT/STAND/LOCOMOTION）有效，
        STAND_BODY_CONTROL/SIT_DOWN/ZERO_TORQUE 等后端不认字符串，必须靠 action_value。
        value 见 api_reference McAction.value 表（201=STAND_BODY_CONTROL）。"""
        from .retry import call_with_retry
        from aimdk_msgs.msg import McActionCommand, McAction

        def build():
            req = SetMcAction.Request()
            req.header.stamp = self.get_clock().now().to_msg()
            req.source = "web_ui"
            req.command = McActionCommand()
            req.command.action_desc = action_desc
            if action_value:
                req.command.action = McAction()
                req.command.action.value = action_value
            return req
        resp = call_with_retry(self, self.mode_client, build, "SetMcAction")
        if resp is None:
            return {"ok": False, "message": "service timeout"}
        code = resp.response.header.code
        return {"ok": code == 0, "code": code, "message": resp.response.message}

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

        # ⚠️ aimdk 官方 resource_type 拼写就是 MONTION（少个字母，SDK 示例与文档 5.1.5 均如此），
        # 非 MOTION —— 用错拼写会导致 ExecuteActionResource 执行失败。
        # 前端可能传 BODY/ARM 简写或 BODY_MONTION/ARM_MONTION，统一规范化；空则按 resource_key 含 onnx 判
        rt = (resource_type or "").upper()
        if "BODY" in rt:
            rtype = "BODY_MONTION"
        elif "ARM" in rt:
            rtype = "ARM_MONTION"
        else:
            rtype = "BODY_MONTION" if "onnx" in resource_key else "ARM_MONTION"
        logger.info(f"▶ 播放灵创: {resource_key} → {rtype}")

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

    def _do_run_node(self, step: dict) -> dict:
        """执行单个自由任务节点（cmd 线程，复用 steps.execute_step）。
        手动单点触发，不走 engine（无状态机/无顺序/无前后依赖）。"""
        from .task.steps import execute_step
        self._node_stop_flag = False
        self._node_running_id = step.get("id", "")
        try:
            execute_step(self, step, {"responses": {}})
            return {"ok": True, "node_id": step.get("id", "")}
        except Exception as e:
            logger.error(f"❌ 自由节点执行失败 [{step.get('type')}]: {e}")
            return {"ok": False, "error": str(e), "node_id": step.get("id", "")}
        finally:
            self._node_running_id = ""


# ── 模块级引用（供 routes 直接使用）──
_cmd_queue: CommandQueue | None = None
