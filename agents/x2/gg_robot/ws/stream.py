"""WebSocket v2 — wildcard 订阅 + 二进制相机帧 + 键盘遥控（会话锁保护）

协议（契约 §3）：
  客户端→agent: {"v":1,"type":"sub","topics":["sensor.*","cam.*"]}   # wildcard 仅支持尾 *
                {"v":1,"type":"unsub","topics":["cam.*"]}
                {"v":1,"type":"ping"}
                {"v":1,"type":"velocity","forward":0,"lateral":0,"angular":0}
  agent→客户端: {"v":1,"type":"event","topic":"sensor.all","data":{...},"ts":...}
                {"v":1,"type":"pong"} / {"v":1,"type":"session",...} / {"v":1,"type":"error",...}
  二进制（仅订阅 cam.* 的连接）: 4字节大端ms时间戳 + JPEG
握手: /ws?token=<设备token>&client_id=<平台实例ID>&name=<名称>（token 必须匹配）
默认订阅: sys.*
"""

import asyncio
import fnmatch
import json
import logging
import struct
import time

from fastapi import APIRouter, WebSocket, WebSocketDisconnect

logger = logging.getLogger(__name__)

router = APIRouter()


class Client:
    """一个 WS 连接 = 一个订阅者"""

    __slots__ = ("ws", "client_id", "name", "topics")

    def __init__(self, ws: WebSocket, client_id: str, name: str):
        self.ws = ws
        self.client_id = client_id
        self.name = name
        self.topics: set[str] = {"sys.*"}

    def subscribed(self, topic: str) -> bool:
        return any(fnmatch.fnmatch(topic, pat) for pat in self.topics)


_clients: set[Client] = set()


async def publish(topic: str, data: dict):
    """按订阅推送 JSON 事件"""
    dead: list[Client] = []
    payload = json.dumps({"v": 1, "type": "event", "topic": topic, "data": data, "ts": time.time()},
                         ensure_ascii=False)
    for c in list(_clients):
        if not c.subscribed(topic):
            continue
        try:
            await c.ws.send_text(payload)
        except Exception:
            dead.append(c)
    for c in dead:
        _clients.discard(c)


async def publish_frame(topic: str, frame: bytes):
    """按订阅推送二进制帧（4B大端ms时间戳 + JPEG）"""
    dead: list[Client] = []
    payload = struct.pack(">I", int(time.time() * 1000) & 0xFFFFFFFF) + frame
    for c in list(_clients):
        if not c.subscribed(topic):
            continue
        try:
            await c.ws.send_bytes(payload)
        except Exception:
            dead.append(c)
    for c in dead:
        _clients.discard(c)


@router.websocket("/ws")
async def ws_endpoint(ws: WebSocket, token: str = "", client_id: str = "anon", name: str = ""):
    from ..security import verify_bearer, controller

    # 握手鉴权：token 必须匹配（未配对/错 token 一律拒绝）
    if not verify_bearer(f"Bearer {token}"):
        await ws.close(code=4001, reason="invalid token")
        return

    await ws.accept()
    client = Client(ws, client_id, name)
    _clients.add(client)
    controller.bind_ws(client_id, ws, asyncio.get_running_loop())
    logger.info(f"🔗 WS 连接 client_id={client_id} (共 {len(_clients)} 个)")

    try:
        while True:
            raw = await ws.receive_text()
            try:
                msg = json.loads(raw)
            except json.JSONDecodeError:
                continue

            msg_type = msg.get("type")

            if msg_type == "ping":
                await ws.send_text(json.dumps({"v": 1, "type": "pong"}))

            elif msg_type == "sub":
                topics = msg.get("topics") or []
                if isinstance(topics, list):
                    client.topics.update(str(t) for t in topics)
                await ws.send_text(json.dumps({"v": 1, "type": "suback", "topics": sorted(client.topics)}))

            elif msg_type == "unsub":
                topics = msg.get("topics") or []
                if isinstance(topics, list):
                    client.topics.difference_update(str(t) for t in topics)

            elif msg_type == "velocity":
                # 控制类：会话锁校验
                ok, locked_by = controller.check_or_acquire(client_id, name)
                if not ok:
                    await ws.send_text(json.dumps(
                        {"v": 1, "type": "error", "code": 409, "reason": "locked", "locked_by": locked_by}))
                    continue
                from .. import node as node_mod
                if node_mod._cmd_queue:
                    node_mod._cmd_queue.put("velocity",
                                            forward=float(msg.get("forward", 0)),
                                            lateral=float(msg.get("lateral", 0)),
                                            angular=float(msg.get("angular", 0)))

    except WebSocketDisconnect:
        pass
    finally:
        _clients.discard(client)
        controller.release(client_id)
        logger.info(f"🔌 WS 断开 client_id={client_id} (共 {len(_clients)} 个)")


# ── 后台定时推送 ──

async def sensor_pusher(interval: float = 0.2):
    """每 200ms 推送电池/IMU/关节复合数据（topic: sensor.all，订阅 sensor.* 命中）"""
    _diag_counter = 0
    while True:
        await asyncio.sleep(interval)
        if not _clients:
            continue

        from .. import node as node_mod
        _node = node_mod._node
        if _node is None:
            continue

        try:
            await publish("sensor.all", {
                "battery": _node.battery if _node.battery else None,
                "imu": _node.imu if _node.imu else None,
                "arms": _node.arm_joints[:14],
            })
        except Exception as e:
            logger.error(f"传感器推送异常: {e}")

        # 周期诊断：每 ~10s 打印 rclpy 传感器回调计数，确认 executor 是否还在调度回调。
        # 若 b/a/i 计数不再增长 → executor.spin 卡住/退出，而 sensor_pusher 仍在广播旧对象，
        # 前端表现为"值不变"。
        _diag_counter += 1
        if _diag_counter % 50 == 0:
            recv = getattr(_node, "_sensor_recv", {})
            logger.info(
                f"📊 传感器回调计数 b/a/i = "
                f"{recv.get('battery', 0)}/{recv.get('arm', 0)}/{recv.get('imu', 0)} "
                f"| WS 客户端 {len(_clients)}"
            )


async def camera_pusher(interval: float = 0.1):
    """每 100ms 推送活跃相机 JPEG 帧（topic: cam.{camera_id}，订阅 cam.* 命中）"""
    _no_frame_since: float = 0.0  # 首次进入不告警，等首帧出现后再计时
    _warned = False

    while True:
        await asyncio.sleep(interval)
        if not _clients:
            _no_frame_since = 0.0
            _warned = False
            continue

        from .. import node as node_mod
        _node = node_mod._node
        if _node is None:
            continue

        frame = _node.get_camera_frame()
        if frame is None:
            now = time.time()
            if _no_frame_since == 0.0:
                # 检查后端是否已经收到过帧（_camera_last_ts > 0 表示曾经收到过）
                if _node._camera_last_ts > 0:
                    _no_frame_since = now  # 曾经有帧但现在没了，开始计时
            elif now - _no_frame_since > 5.0 and not _warned:
                logger.warning(
                    f"📷 相机帧推送中断 {now - _no_frame_since:.0f}s！"
                    f"活跃相机={_node._active_camera}, "
                    f"总收帧={_node._camera_frame_count}"
                )
                _warned = True
            continue

        _no_frame_since = 0.0
        _warned = False

        try:
            await publish_frame(f"cam.{_node._active_camera or 'default'}", frame)
        except Exception:
            pass


async def cloud_pusher(interval: float = 0.125):
    """建图中推送实时点云帧（topic: slam.cloud；slam_mapping=False 时零开销）
    二进制: 4B大端ms时间戳 + [pose_x,pose_y,yaw(3×f32 LE) + n(u16) + n×(x,y int16 LE cm)]"""
    _last_ts = 0.0
    while True:
        await asyncio.sleep(interval)
        from .. import node as node_mod
        _node = node_mod._node
        if _node is None or not getattr(_node, "slam_mapping", False):
            _last_ts = 0.0
            continue
        got = _node.get_cloud_frame()
        if got is None:
            continue
        frame, ts = got
        if ts == _last_ts:
            continue   # 无新帧不重推
        _last_ts = ts
        await publish_frame("slam.cloud", frame)


async def sys_pusher(interval: float = 10.0):
    """每 10s 推系统心跳（默认订阅，连接活性保底）"""
    import datetime
    while True:
        await asyncio.sleep(interval)
        if not _clients:
            continue
        from ..security import controller
        await publish("sys.heartbeat", {
            "ts": datetime.datetime.now().isoformat(timespec="seconds"),
            "clients": len(_clients),
            "controller": controller.current(),
        })
