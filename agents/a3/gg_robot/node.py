"""A3 ROS2 节点 — 传感器订阅（BEST_EFFORT）+ 50Hz 速度发布 + 命令队列

与 X2 的本质差异（docs/a3-ultra-dev-notes.md）：
- 控制类不走 ROS Service，走 HTTP RPC（rpc.py）——本节点只剩"订阅"与"速度发布"
- 多数业务话题封装为 ros2_plugin_proto/RosMsgWrapper（serialization_type: pb|json），
  pb 需 prebuilt a3_aimdk whl（未装则对应传感器优雅降级为 None，不崩）
- 速度是比例制 -1.0~1.0（平台 API 统一 m/s，_publish_velocity 内换算）
- 无需注册输入源（X2 的 SetMcInputSource 在 A3 不存在）

rclpy 必须独立线程 spin（命令队列模式，架构同 X2——见 CLAUDE.md）。
"""

import base64
import json
import logging
import threading
import time
from concurrent.futures import Future
from typing import Any

logger = logging.getLogger(__name__)

# pb 协议（未部署 a3_aimdk whl 时降级）
_pb2 = None
try:
    # whl 真实结构 aimdk/protocol/<模块>/*_pb2（文档示例的 aimdk.protocol_pb2 是错的，
    # 以官方 examples/other/bms.py 等为准；2026-08-31 实机核对）
    from aimdk.protocol.hal.bms.hal_bms_channel_pb2 import BmsStateChannel  # type: ignore
    from aimdk.protocol.hal.state.hal_state_channel_pb2 import EmergencyStateChannel  # type: ignore
    _pb2 = True
except Exception:  # noqa: BLE001 —— whl 未装/不在机上是部署态常态
    logger.warning("⚠️ a3_aimdk pb 导入失败：BMS/急停/VAD 音频降级 None")


class Command:
    __slots__ = ("action", "kwargs", "future", "created")

    def __init__(self, action: str, **kwargs):
        self.action = action
        self.kwargs = kwargs
        self.future = Future()
        self.created = time.time()


class CommandQueue:
    """线程安全命令队列（API 线程 put → rclpy 线程消费），同 X2"""

    def __init__(self):
        import queue
        self._q: "queue.Queue[Command]" = queue.Queue()

    def put(self, action: str, **kwargs) -> Future:
        cmd = Command(action, **kwargs)
        self._q.put(cmd)
        return cmd.future

    def get_nowait(self) -> Command | None:
        try:
            return self._q.get_nowait()
        except Exception:
            return None

    def pending_count(self) -> int:
        return self._q.qsize()


# 模块级引用（routes 经此访问；X2 同款模式）
_node: "A3Node | None" = None
_cmd_queue: CommandQueue | None = None


def _unwrap(msg) -> bytes:
    """RosMsgWrapper.data（byte[]）拼回 bytes"""
    return bytes(bytearray(getattr(msg, "data", b"")))


class A3Node:
    """A3-Ultra 传感器/速度节点（rclpy 线程内构造）"""

    def __init__(self):
        import rclpy
        from rclpy.node import Node
        from rclpy.qos import QoSHistoryPolicy, QoSProfile, QoSReliabilityPolicy

        # 用组合而非继承（rclpy Node 基类在无 ROS 环境下 import 即失败，保持延迟）
        self.node = Node("ggrobot_a3_agent")
        self._rclpy = rclpy

        qos = QoSProfile(
            history=QoSHistoryPolicy.KEEP_LAST, depth=10,
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
        )

        # ── 传感器状态（ws/stream.sensor.all 消费的形态，对齐 X2）──
        self.battery: dict | None = None
        self.imu: dict | None = None          # A3 IMU 为 foxglove 封装，M1 暂不订阅
        self.arm_joints: list = []
        self.emergency: dict | None = None
        self.tts_state: dict | None = None
        self._sensor_recv = {"battery": 0, "arm": 0, "tts": 0, "emergency": 0}

        self._qos_sensor = qos
        self._create_sensor_subs(qos)
        self._create_velocity_publisher(qos)

        # ── 相机（TakeShot 按需模式：raw 话题订阅已禁——265MB/s 触发 A3531001，实机教训）──
        self._active_camera: str | None = None
        self._camera_frame_count = 0
        self._auto_select_camera()
        self.slam_mapping = False

        # ── 麦克风 VAD 段采集（/agent/process_audio_output，only_voice 模式）──
        self.mic_enabled = False
        self._mic_lock = threading.Lock()
        self._mic_recv = 0
        self._vad_state = 0
        self._mic_segment = b""
        self._mic_segment_ts = 0.0
        self._mic_last_segment = b""
        self._mic_last_segment_ts = 0.0
        self._mic_last_segment_size = 0
        self._mic_source = 0

        # ── 速度状态（按需发布：静止即停发，PASSIVE 态灌速度会触发 H3 告警 A3531001，
        #    2026-08-31 实机教训；官方 walk.py 语义也是"发一段时间后停发"）──
        self._vel = {"forward": 0.0, "lateral": 0.0, "angular": 0.0}
        self._vel_lock = threading.Lock()
        self._vel_last_cmd = 0.0
        self._vel_publishing = False   # 仅运动期间发布；全零 2s 后停发
        self._vel_zero_since: float | None = None
        self._mode_checked_at = 0.0    # MOTION 前置检查缓存（10s）

        logger.info("🤖 A3Node 就绪（传感器订阅 + 速度发布）")

    # ── 订阅 ─────────────────────────────

    def _create_sensor_subs(self, qos) -> None:
        """按 subs.* 开关订阅（A3531001 二分排查：全关=最小模式）"""
        from ros2_plugin_proto.msg import RosMsgWrapper
        from . import config as cfg

        def sub_r(topic: str, cb):
            self.node.create_subscription(RosMsgWrapper, topic, cb, qos)

        def sub_j(topic: str, cb):
            from sensor_msgs.msg import JointState
            self.node.create_subscription(JointState, topic, cb, qos)

        if cfg.SUBS_ARM:
            sub_j("/motion/control/arm_joint_state", self._on_arm)
        if cfg.SUBS_BMS:
            sub_r("/aima/bms/data/pb_3Aaimdk_2Eprotocol_2EBmsStateChannel", self._on_bms)
        if cfg.SUBS_EMERGENCY:
            sub_r("/hal_state/emergency/pb_3Aaimdk_2Eprotocol_2EEmergencyStateChannel", self._on_emergency)
        if cfg.SUBS_TTS_STATUS:
            # TTS 状态推送（normal 模式才发；wait_tts_done 的 topic 通道）
            sub_r("/interaction/tts_status/pb_3Aaimdk_2Eprotocol_2ETTSStatus", self._on_tts_status)
        if cfg.SUBS_AUDIO:
            # VAD 降噪音频（only_voice 模式持续输出；normal 模式唤醒词激活）
            sub_r("/agent/process_audio_output/pb_3Aaimdk_2Eprotocol_2EProcessedAudioOutput", self._on_mic)
        on = [k for k, v in dict(arm=cfg.SUBS_ARM, bms=cfg.SUBS_BMS, emergency=cfg.SUBS_EMERGENCY,
                                 tts=cfg.SUBS_TTS_STATUS, audio=cfg.SUBS_AUDIO).items() if v]
        logger.info(f"🔌 订阅开关: {on or ['（全关·最小模式）']}")

    def _on_arm(self, msg) -> None:
        try:
            names = list(getattr(msg, "name", []) or [])
            if not names:  # RosMsgWrapper 包装（非标准 JointState 直发）
                return
            pos = list(getattr(msg, "position", []) or [])
            self.arm_joints = [
                {"name": n, "position": p, "velocity": v, "effort": e}
                for n, p, v, e in zip(names, pos,
                                      getattr(msg, "velocity", []) or [],
                                      getattr(msg, "effort", []) or [])
            ]
            self._sensor_recv["arm"] += 1
        except Exception:  # noqa: BLE001
            pass

    def _on_bms(self, msg) -> None:
        if _pb2 is None:
            return
        try:
            m = BmsStateChannel()
            m.ParseFromString(_unwrap(msg))
            # channel 消息：bms_datas 是 repeated BmsState（双电池）；取"在用"包
            packs = list(m.bms_datas) or ([m.data] if m.HasField("data") else [])
            cur = next((b for b in reversed(packs) if int(b.bms_state) == 1),  # 1=Connected
                       packs[-1] if packs else None)
            if cur is None:
                return
            charging = int(getattr(cur, "power_supply_status", 0)) == 1  # 1=CHARGING
            self.battery = {
                "charge": cur.charge,
                "voltage": round(cur.voltage / 1000, 2),      # mV → V
                "current": round(cur.current / 1000, 3),      # mA → A
                "temperature": round(cur.temperature / 10, 1),  # 0.1℃ → ℃
                "capacity": cur.capacity,
                "charging": charging,
                "dual": len(packs),
            }
            self._sensor_recv["battery"] += 1
        except Exception:  # noqa: BLE001
            pass

    def _on_emergency(self, msg) -> None:
        if _pb2 is None:
            return
        try:
            m = EmergencyStateChannel()
            m.ParseFromString(_unwrap(msg))
            d = m.data if m.HasField("data") else m
            self.emergency = {
                "active": bool(getattr(d, "active", False)
                               or getattr(d, "wired_emergency_stop", False)
                               or getattr(d, "wireless_emergency_stop", False)
                               or getattr(d, "software_emergency_stop", False)),
                "wired": bool(getattr(d, "wired_emergency_stop", False)),
                "wireless": bool(getattr(d, "wireless_emergency_stop", False)),
                "software": bool(getattr(d, "software_emergency_stop", False)),
                "reason": str(getattr(d, "reason", "")),
            }
            self._sensor_recv["emergency"] += 1
        except Exception:  # noqa: BLE001
            pass

    def _on_tts_status(self, msg) -> None:
        try:
            raw = _unwrap(msg)
            try:
                self.tts_state = json.loads(raw) if raw.startswith(b"{") else None
            except json.JSONDecodeError:
                self.tts_state = None
            if self.tts_state:
                self._sensor_recv["tts"] += 1
        except Exception:  # noqa: BLE001
            pass

    # ── 速度发布（50Hz，m/s → 比例）──────────────

    def _create_velocity_publisher(self, qos) -> None:
        from ros2_plugin_proto.msg import RosMsgWrapper
        self._vel_pub = self.node.create_publisher(
            RosMsgWrapper,
            "/motion/control/locomotion_velocity/pb_3Aaimdk_2Eprotocol_2EMotionControlLocomotionVelocityChannel",
            qos)
        self._vel_timer = self.node.create_timer(1.0 / 50.0, self._publish_velocity)

    def _ensure_motion_mode(self) -> None:
        """开始运动前确保 MC 在 MOTION 态（10s 缓存；非 MOTION 自动切，对齐文档 7.1.4）"""
        if time.time() - self._mode_checked_at < 10.0:
            return
        from . import rpc
        try:
            info = rpc.action_get().get("info", {})
            cur = str(info.get("current_action", "")).replace("MotionControlAction_", "")
            if cur and cur != "MOTION":
                logger.info(f"🏃 速度前置：{cur} → MOTION")
                rpc.action_set("MOTION")
                time.sleep(0.5)
            self._mode_checked_at = time.time()
        except Exception as e:  # noqa: BLE001 —— 查询失败不阻塞遥控（mc 会自行拒绝非法输入）
            logger.warning(f"模式前置检查失败: {e}")
            self._mode_checked_at = time.time()

    def set_velocity(self, forward: float, lateral: float, angular: float) -> None:
        """目标速度（m/s / rad/s；API 线程调用）。非零 → 激活发布；零 → 计时停发"""
        moving = bool(forward or lateral or angular)
        with self._vel_lock:
            self._vel = {"forward": forward, "lateral": lateral, "angular": angular}
            self._vel_last_cmd = time.time()
            if moving:
                self._vel_publishing = True
                self._vel_zero_since = None
            elif self._vel_zero_since is None:
                self._vel_zero_since = time.time()

    def _publish_velocity(self) -> None:
        """50Hz 发布（rclpy timer 回调）。静止（全零 2s）后停止发布——
        PASSIVE 态持续灌速度话题会触发 mc 异常（实机 A3531001）"""
        from . import config as cfg
        with self._vel_lock:
            if not self._vel_publishing:
                return   # 静止期：零发布（这是修复 H3 告警的关键）
            v = dict(self._vel)
            if time.time() - self._vel_last_cmd > 1.0:
                v = {"forward": 0.0, "lateral": 0.0, "angular": 0.0}
                self._vel = dict(v)
            if v["forward"] == 0 and v["lateral"] == 0 and v["angular"] == 0:
                if self._vel_zero_since is not None and time.time() - self._vel_zero_since > 2.0:
                    self._vel_publishing = False   # 停发（下次非零 set_velocity 再激活）
                    return
        try:
            payload = json.dumps({"data": {
                "mode": 0,
                "forward_velocity": _clamp(v["forward"] / cfg.VEL_MAX_FORWARD),
                "lateral_velocity": _clamp(v["lateral"] / cfg.VEL_MAX_LATERAL),
                "angular_velocity": _clamp(v["angular"] / cfg.VEL_MAX_ANGULAR),
            }}).encode()
            msg = self._vel_pub.msg_type()
            msg.serialization_type = "json"
            msg.data = [payload[i:i + 1] for i in range(len(payload))]
            self._vel_pub.publish(msg)
        except Exception as e:  # noqa: BLE001
            logger.error(f"速度发布失败: {e}")

    def stop_velocity(self) -> None:
        self.set_velocity(0.0, 0.0, 0.0)

    # ── TTS 等待（trace_id 轮询，≤1Hz 遵守限频约束）──────────

    def wait_tts_done(self, trace_id: str, timeout: float = 30.0) -> bool:
        from . import rpc
        deadline = time.time() + timeout
        while time.time() < deadline:
            time.sleep(1.0)
            try:
                st = rpc.tts_status(trace_id).get("tts_status", {})
                s = str(st.get("tts_status", ""))
                if "NOTInQue" in s:
                    return True     # 播放队列无此文本 = 已播完
                if "Error" in s:
                    return False
            except Exception:  # noqa: BLE001 —— RPC 不可达继续等（超时兜底）
                continue
        return False

    # ── 相机：按需订阅 /rgb（sensor_msgs/Image）→ 降采样 JPEG ──

    def _auto_select_camera(self) -> None:
        from . import config as cfg
        self._active_camera = cfg.CAMERA_LIST[0][1] if cfg.CAMERA_LIST else None

    def get_camera_frame(self) -> bytes | None:
        """保留接口（shot 模式下相机帧由 stream.camera_pusher 直接管理，不走 node）"""
        return None

    def list_cameras(self) -> list[dict]:
        from . import config as cfg
        return [{"id": cid, "name": name, "shot_name": shot, "active": shot == self._active_camera}
                for cid, shot, name in cfg.CAMERA_LIST]

    def switch_camera(self, camera_id: str) -> dict:
        from . import config as cfg
        valid = {c[0]: c[1] for c in cfg.CAMERA_LIST}
        if camera_id not in valid:
            return {"ok": False, "error": f"unknown camera {camera_id}"}
        self._active_camera = valid[camera_id]
        return {"ok": True, "active": self._active_camera}

    def shot_jpeg(self) -> bytes | None:
        """TakeShot → PNG → 缩放 JPEG（stream.camera_pusher 经 to_thread 调用）"""
        from . import rpc
        from . import config as cfg
        try:
            import io
            from PIL import Image
            png = rpc.take_shot(self._active_camera or "right_fisheye_camera")
            img = Image.open(io.BytesIO(png))
            if img.width > cfg.CAMERA_MAX_WIDTH:
                img = img.resize((cfg.CAMERA_MAX_WIDTH, int(img.height * cfg.CAMERA_MAX_WIDTH / img.width)),
                                 Image.BILINEAR)
            buf = io.BytesIO()
            img.save(buf, format="JPEG", quality=cfg.CAMERA_JPEG_QUALITY)
            self._camera_frame_count += 1
            return buf.getvalue()
        except Exception as e:  # noqa: BLE001
            logger.debug(f"截图失败: {e}")
            return None

    def _on_mic(self, msg) -> None:
        """VAD 段采集（ProcessedAudioOutput：stream_id/vad_state/audio_data）
        对齐 X2 /api/mic 语义；识别由平台 sidecar 做。外置麦 VAD 有官方 bug，只取内置。"""
        if _pb2 is None:
            return
        try:
            from aimdk.protocol.agent.agent_data_pb2 import ProcessedAudioOutput
            m = ProcessedAudioOutput()
            m.ParseFromString(_unwrap(msg))
            self._mic_recv += 1
            vad = int(m.vad_state)
            data = bytes(m.audio_data) if m.audio_data else b""
            with self._mic_lock:
                self._vad_state = vad
                if m.stream_id != 1:
                    return
                if vad == 3:   # 语音结束 → 封包（前端拉段 + 平台侧 ASR）
                    if data:
                        self._mic_segment += data
                    self._mic_last_segment = self._mic_segment
                    self._mic_last_segment_ts = time.time()
                    self._mic_last_segment_size = len(self._mic_segment)
                    self._mic_segment = b""
                    self._mic_segment_ts = 0.0
                elif vad in (1, 2):
                    if not self._mic_segment_ts:
                        self._mic_segment_ts = time.time()
                    self._mic_segment += data
                    if len(self._mic_segment) > 2 * 1024 * 1024:   # END 漏收保护
                        self._mic_segment = self._mic_segment[-2 * 1024 * 1024:]
                else:
                    self._mic_segment = b""
                    self._mic_segment_ts = 0.0
        except Exception:  # noqa: BLE001
            pass

    def get_mic_audio_b64(self) -> str:
        with self._mic_lock:
            return base64.b64encode(self._mic_last_segment).decode()

    def get_mic_status(self) -> dict:
        with self._mic_lock:
            return {
                "enabled": self.mic_enabled,
                "vad_state": self._vad_state,
                "segment_bytes": len(self._mic_segment),
                "last_segment_bytes": self._mic_last_segment_size,
                "last_segment_ts": self._mic_last_segment_ts,
                "mic_source": self._mic_source,
                "text": "",   # A3：识别统一在平台 sidecar（本地转写），agent 只采集
                "recv_count": self._mic_recv,
            }

    # ── 命令队列消费（rclpy 线程驱动；命令本体走 HTTP RPC）──────

    def process_commands(self) -> None:
        # _cmd_queue 是本模块级全局（__main__.ros_spin 里注入），直接引用
        if _cmd_queue is None:
            return
        for _ in range(20):  # 每轮最多消费 20 条，防单轮霸占
            cmd = _cmd_queue.get_nowait()
            if cmd is None:
                return
            try:
                result = self._dispatch(cmd)
                if not cmd.future.done():
                    cmd.future.set_result(result)
            except Exception as e:  # noqa: BLE001
                if not cmd.future.done():
                    cmd.future.set_exception(e)

    def _dispatch(self, cmd: Command) -> Any:
        from . import rpc
        act = cmd.action

        if act == "velocity":
            f, l, a = (float(cmd.kwargs.get("forward", 0)),
                       float(cmd.kwargs.get("lateral", 0)),
                       float(cmd.kwargs.get("angular", 0)))
            if (f or l or a) and not self._vel_publishing:
                self._ensure_motion_mode()   # 速度话题仅 MOTION 可调（文档 7.1.4）
            self.set_velocity(f, l, a)
            return {"ok": True}

        if act == "stop":
            self.stop_velocity()
            return {"ok": True}

        if act == "tts":
            text = str(cmd.kwargs.get("text", ""))
            r = rpc.tts_play(text, bool(cmd.kwargs.get("interrupt", True)))
            trace = r.get("trace_id", "")
            if cmd.kwargs.get("wait"):
                self.wait_tts_done(trace, timeout=max(3.0, len(text) / 3.0))
            return {"ok": True, "trace_id": trace}

        if act == "motion":
            r = rpc.motion_command(
                motion_id=str(cmd.kwargs.get("motion_id", "")),
                duration_ms=int(cmd.kwargs.get("duration_ms", 10000)),
                cmd_pause=bool(cmd.kwargs.get("pause", False)),
                cmd_reset=bool(cmd.kwargs.get("reset", False)),
                cmd_repeat=bool(cmd.kwargs.get("repeat", False)),
            )
            state = str(r.get("state", ""))
            if "SUCCESS" not in state:
                raise RuntimeError(f"motion failed: {state}")
            return {"ok": True}

        if act == "mode":
            return rpc.action_set(str(cmd.kwargs.get("action_name", "MOTION")))

        raise ValueError(f"unknown command: {act}")

    # ── 生命周期 ──

    def destroy(self) -> None:
        self._vel_alive = False
        try:
            self.stop_velocity()
            time.sleep(0.05)  # 让最后一帧零速发出
            self.node.destroy_node()
        except Exception:  # noqa: BLE001
            pass


def _clamp(x: float, lo: float = -1.0, hi: float = 1.0) -> float:
    return max(lo, min(hi, float(x)))
