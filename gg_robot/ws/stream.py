"""WebSocket — 传感器数据推送 + 相机帧 + 键盘遥控"""

import asyncio
import json
import logging
import struct
import time
from fastapi import APIRouter, WebSocket, WebSocketDisconnect

logger = logging.getLogger(__name__)

router = APIRouter()

# 已连接的 WebSocket 客户端
_clients: set[WebSocket] = set()


async def broadcast_json(data: dict):
    """向所有客户端推送 JSON"""
    dead: list[WebSocket] = []
    text = json.dumps(data, ensure_ascii=False)
    for ws in _clients:
        try:
            await ws.send_text(text)
        except Exception:
            dead.append(ws)
    for ws in dead:
        _clients.discard(ws)


async def broadcast_bytes(data: bytes):
    """向所有客户端推送二进制数据（相机帧）"""
    dead: list[WebSocket] = []
    for ws in _clients:
        try:
            await ws.send_bytes(data)
        except Exception:
            dead.append(ws)
    for ws in dead:
        _clients.discard(ws)


@router.websocket("/ws")
async def ws_endpoint(ws: WebSocket):
    await ws.accept()
    _clients.add(ws)
    logger.info(f"🔗 WebSocket 客户端连接 (共 {len(_clients)} 个)")

    try:
        while True:
            raw = await ws.receive_text()

            try:
                msg = json.loads(raw)
            except json.JSONDecodeError:
                continue

            msg_type = msg.get("type")

            if msg_type == "ping":
                await ws.send_text(json.dumps({"type": "pong"}))

            elif msg_type == "velocity":
                from .. import node as node_mod
                if node_mod._cmd_queue:
                    node_mod._cmd_queue.put("velocity",
                                            forward=float(msg.get("forward", 0)),
                                            lateral=float(msg.get("lateral", 0)),
                                            angular=float(msg.get("angular", 0)))

    except WebSocketDisconnect:
        pass
    finally:
        _clients.discard(ws)
        logger.info(f"🔌 WebSocket 客户端断开 (共 {len(_clients)} 个)")


# ── 后台定时推送 ──

async def sensor_pusher(interval: float = 0.2):
    """每 200ms 推送电池/IMU/关节数据"""
    while True:
        await asyncio.sleep(interval)
        if not _clients:
            continue

        from .. import node as node_mod
        _node = node_mod._node
        if _node is None:
            continue

        try:
            payload = {
                "type": "sensor",
                "ts": time.time(),
                "battery": _node.battery if _node.battery else None,
                "imu": _node.imu if _node.imu else None,
                "arms": _node.arm_joints[:14],
            }
            await broadcast_json(payload)
        except Exception as e:
            logger.error(f"传感器推送异常: {e}")


async def camera_pusher(interval: float = 0.1):
    """每 100ms 推送相机 JPEG 帧（二进制）"""
    while True:
        await asyncio.sleep(interval)
        if not _clients:
            continue

        from .. import node as node_mod
        _node = node_mod._node
        if _node is None:
            continue

        frame = _node.get_camera_frame()
        if frame is None:
            continue

        # 4 字节时间戳(ms) + JPEG 数据
        ts_bytes = struct.pack(">I", int(time.time() * 1000) & 0xFFFFFFFF)
        try:
            await broadcast_bytes(ts_bytes + frame)
        except Exception:
            pass
