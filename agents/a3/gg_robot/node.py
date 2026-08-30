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
    from aimdk.protocol_pb2 import (  # type: ignore
        BmsStateChannel, EmergencyStateChannel, ProcessedAudioOutput)
    _pb2 = True
except Exception:  # noqa: BLE001 —— whl 未装/不在机上是部署态常态
    logger.warning("⚠️ a3_aimdk whl 未安装：BMS/急停/VAD 音频无法反序列化（降级 None）")


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
        # 相机订阅保活（0.5s 检查；切换相机后由 _ensure_camera_sub 重建）
        self.node.create_timer(0.5, self._ensure_camera_sub)

        # ── 相机（按需订阅活跃路 /rgb → JPEG，Phase C）──
        self._camera_frames: dict[str, tuple[bytes, float]] = {}
        self._active_camera: str | None = None
        self._camera_frame_count = 0
        self._camera_last_ts = 0.0
        self._camera_sub = None
        self._camera_sub_topic = ""
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

        # ── 速度状态（50Hz 发布循环用）──
        self._vel = {"forward": 0.0, "lateral": 0.0, "angular": 0.0}
        self._vel_lock = threading.Lock()
        self._vel_last_cmd = 0.0
        self._vel_alive = True

        logger.info("🤖 A3Node 就绪（传感器订阅 + 速度发布）")

    # ── 订阅 ─────────────────────────────

    def _create_sensor_subs(self, qos) -> None:
        from ros2_plugin_proto.msg import RosMsgWrapper

        def sub(topic: str, cb):
            self.node.create_subscription(RosMsgWrapper, topic, cb, qos)

        sub("/motion/control/arm_joint_state", self._on_arm)
        sub("/aima/bms/data/pb_3Aaimdk_2Eprotocol_2EBmsStateChannel", self._on_bms)
        sub("/hal_state/emergency/pb_3Aaimdk_2Eprotocol_2EEmergencyStateChannel", self._on_emergency)
        # TTS 状态推送（normal 模式才发；wait_tts_done 的 topic 通道）
        sub("/interaction/tts_status/pb_3Aaimdk_2Eprotocol_2ETTSStatusChannel", self._on_tts_status)
        # VAD 降噪音频（only_voice 模式持续输出；normal 模式唤醒词激活）
        sub("/agent/process_audio_output/pb_3Aaimdk_2Eprotocol_2EProcessedAudioOutput", self._on_mic)

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
            # 双电池数组：取"在用"包（bms_state=Connected 优先，否则最后一个）
            packs = list(m.bms_datas)
            cur = next((b for b in reversed(packs)
                        if b.bms_state == 2 or "Connected" in str(b.bms_state)), packs[-1] if packs else None)
            if cur is None:
                return
            charging = "CHARGING" in str(getattr(cur, "power_supply_status", ""))
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
            d = getattr(m, "data", m)
            self.emergency = {
                "active": bool(getattr(d, "wired_emergency_stop", False)
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

    def set_velocity(self, forward: float, lateral: float, angular: float) -> None:
        """目标速度（m/s / rad/s；API 线程调用）"""
        with self._vel_lock:
            self._vel = {"forward": forward, "lateral": lateral, "angular": angular}
            self._vel_last_cmd = time.time()

    def _publish_velocity(self) -> None:
        """50Hz 发布（rclpy timer 回调）。>1s 无新指令自动归零（松手保护）"""
        from . import config as cfg
        with self._vel_lock:
            v = dict(self._vel)
            if time.time() - self._vel_last_cmd > 1.0:
                v = {"forward": 0.0, "lateral": 0.0, "angular": 0.0}
                self._vel = dict(v)
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
        self._active_camera = cfg.CAMERA_LIST[0][0] if cfg.CAMERA_LIST else None

    def _camera_topic(self, cid: str) -> str:
        from . import config as cfg
        for c, topic, _name in cfg.CAMERA_LIST:
            if c == cid:
                return topic
        return ""

    def _ensure_camera_sub(self) -> None:
        """按需订阅当前活跃相机（切换时重建；rclpy 线程调用安全）"""
        if not self._active_camera:
            return
        topic = self._camera_topic(self._active_camera)
        if not topic or topic == self._camera_sub_topic:
            return
        if self._camera_sub is not None:
            try:
                self.node.destroy_subscription(self._camera_sub)
            except Exception:  # noqa: BLE001
                pass
        from sensor_msgs.msg import Image
        self._camera_sub = self.node.create_subscription(
            Image, topic, self._on_camera, self._qos_sensor)
        self._camera_sub_topic = topic
        logger.info(f"📷 相机订阅: {topic}")

    def _on_camera(self, msg) -> None:
        """Image → JPEG（限频 + 降采样；PIL/numpy 缺失时降级跳过）"""
        from . import config as cfg
        now = time.time()
        if now - self._camera_last_ts < 1.0 / max(1, cfg.CAMERA_FPS):
            return
        try:
            import numpy as np
            from PIL import Image as PILImage
            w, h = int(msg.width), int(msg.height)
            enc = str(msg.encoding or "rgb8")
            if w == 0 or h == 0 or len(msg.data) < w * h * 3:
                return
            arr = np.frombuffer(bytes(msg.data), dtype=np.uint8)
            if enc in ("rgb8", "bgr8"):
                arr = arr[: w * h * 3].reshape(h, w, 3)
                if enc == "bgr8":
                    arr = arr[:, :, ::-1]
            elif enc.startswith("rgba") or enc.startswith("bgra"):
                arr = arr[: w * h * 4].reshape(h, w, 4)[:, :, :3]
                if enc.startswith("bgra"):
                    arr = arr[:, :, ::-1]
            else:
                return   # yuv422/mono 等暂不支持（RGB 流已覆盖主要相机）
            img = PILImage.fromarray(arr)
            if img.width > 800:
                img = img.resize((800, int(img.height * 800 / img.width)), PILImage.BILINEAR)
            import io
            buf = io.BytesIO()
            img.save(buf, format="JPEG", quality=cfg.CAMERA_JPEG_QUALITY)
            self._camera_frames[self._active_camera] = (buf.getvalue(), now)
            self._camera_frame_count += 1
            self._camera_last_ts = now
        except ImportError:
            pass   # pillow/numpy 未装：相机降级（不崩）
        except Exception as e:  # noqa: BLE001
            logger.debug(f"相机帧处理失败: {e}")

    # ── 麦克风 VAD 段（对齐 X2 /api/mic 语义；ASR 由平台 sidecar 做）──

    def _on_mic(self, msg) -> None:
        if _pb2 is None:
            return
        try:
            m = ProcessedAudioOutput()
            m.ParseFromString(_unwrap(msg))
            self._mic_recv += 1
            vad = int(m.vad_state)
            data = bytes(m.audio_data) if m.audio_data else b""
            with self._mic_lock:
                self._vad_state = vad
                if m.stream_id != 1:   # 统一走内置麦（外置麦 VAD 状态有 bug，官方未修）
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

    def get_mic_audio_b64(self) -> str:
        with self._mic_lock:
            return base64.b64encode(self._mic_last_segment).decode()

    # ── 相机（供 camera_pusher 复用的 X2 同形接口）──

    def get_camera_frame(self) -> bytes | None:
        """当前活跃相机 JPEG（对齐 X2 接口，camera_pusher 复用）；无帧 None"""
        if not self._active_camera:
            return None
        got = self._camera_frames.get(self._active_camera)
        return got[0] if got else None

    def list_cameras(self) -> list[dict]:
        from . import config as cfg
        return [{"id": cid, "name": name, "topic": topic}
                for cid, topic, name in cfg.CAMERA_LIST]

    def switch_camera(self, camera_id: str) -> dict:
        valid = [c["id"] for c in self.list_cameras()]
        if camera_id not in valid:
            return {"ok": False, "error": f"unknown camera {camera_id}"}
        self._active_camera = camera_id
        self._camera_sub_topic = ""   # 让 _ensure_camera_sub 重建订阅
        return {"ok": True, "active": camera_id}

    # ── 命令队列消费（rclpy 线程驱动；命令本体走 HTTP RPC）──────

    def process_commands(self) -> None:
        from . import _cmd_queue as q  # noqa: PLC0415
        assert q is not None
        for _ in range(20):  # 每轮最多消费 20 条，防单轮霸占
            cmd = q.get_nowait()
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
            self.set_velocity(float(cmd.kwargs.get("forward", 0)),
                              float(cmd.kwargs.get("lateral", 0)),
                              float(cmd.kwargs.get("angular", 0)))
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
            return rpc.action_set(str(cmd.kwargs.get("action", "MOTION")))

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
