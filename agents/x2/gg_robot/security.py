"""agent 安全层 — /etc/ggrobot-agent.conf 读取 + token 鉴权 + 控制会话锁

conf 由 deb postinst 生成（token 永不覆盖），格式 key=value 行：token/sn/model/port。
"""

import asyncio
import hashlib
import hmac
import logging
import threading
import time

logger = logging.getLogger(__name__)

_conf_cache: dict | None = None


def load_conf() -> dict:
    """读取 agent conf（带缓存）。文件不存在 = 未配对模式。"""
    global _conf_cache
    if _conf_cache is not None:
        return _conf_cache
    from .config import AGENT_CONF_PATH
    conf: dict = {}
    try:
        for line in AGENT_CONF_PATH.read_text().splitlines():
            line = line.strip()
            if not line or line.startswith("#") or "=" not in line:
                continue
            k, _, v = line.partition("=")
            conf[k.strip()] = v.strip()
    except FileNotFoundError:
        pass
    except Exception as e:
        logger.warning(f"⚠️ 读取 {AGENT_CONF_PATH} 失败: {e}")
    _conf_cache = conf
    return conf


def reload_conf() -> dict:
    global _conf_cache
    _conf_cache = None
    return load_conf()


def agent_token() -> str | None:
    return load_conf().get("token") or None


def agent_sn() -> str | None:
    """SN 优先 conf（postinst 烧录），兜底环境变量"""
    return load_conf().get("sn") or None


def is_paired() -> bool:
    return bool(agent_token())


def verify_bearer(header_value: str | None) -> bool:
    """校验 Authorization: Bearer <token>"""
    if not header_value or not header_value.startswith("Bearer "):
        return False
    provided = header_value[7:].strip()
    expect = agent_token()
    if not expect:
        return False  # 未配对：控制面全关
    return hmac.compare_digest(provided.encode(), expect.encode())


# ── 控制会话锁 ─────────────────────────────
# 同一台机器人同一时刻只有一个控制者：第一个带 client_id 的控制请求获得锁，
# 后来者 409；持锁者 30s 无控制请求自动释放；可 takeover 抢占（原持有者 WS 收 session lost）。

LOCK_TIMEOUT = 30.0


class _Holder:
    __slots__ = ("client_id", "name", "since", "last_seen", "ws", "loop")

    def __init__(self, client_id: str, name: str, ws=None, loop=None):
        self.client_id = client_id
        self.name = name
        self.since = time.time()
        self.last_seen = self.since
        self.ws = ws
        self.loop = loop

    def info(self) -> dict:
        return {"client_id": self.client_id, "name": self.name, "since": self.since}


class ControllerLock:
    def __init__(self):
        self._lock = threading.Lock()
        self._holder: _Holder | None = None

    def _expired(self) -> bool:
        return self._holder is not None and (time.time() - self._holder.last_seen) > LOCK_TIMEOUT

    def check_or_acquire(self, client_id: str, name: str = "") -> tuple[bool, dict | None]:
        """控制请求前调用。返回 (允许?, 被谁占用)。同 client_id 刷新 keep-alive。"""
        with self._lock:
            if self._holder is None or self._expired():
                self._holder = _Holder(client_id, name)
                return True, None
            if self._holder.client_id == client_id:
                self._holder.last_seen = time.time()
                return True, None
            return False, self._holder.info()

    def takeover(self, client_id: str, name: str = "") -> dict | None:
        """抢占控制权，返回被踢掉的原持有者信息（如有）。"""
        with self._lock:
            old = self._holder
            self._holder = _Holder(client_id, name)
        if old is not None and old.ws is not None and old.loop is not None:
            self._notify_lost(old)
        return old.info() if old and old.client_id != client_id else None

    def bind_ws(self, client_id: str, ws, loop) -> None:
        """WS 连接绑定到持锁者（若 client_id 一致），用于抢占时推送 session lost"""
        with self._lock:
            if self._holder is not None and self._holder.client_id == client_id:
                self._holder.ws = ws
                self._holder.loop = loop

    def release(self, client_id: str) -> None:
        """WS 断开时：若持锁者是它则释放"""
        with self._lock:
            if self._holder is not None and self._holder.client_id == client_id:
                self._holder = None

    @staticmethod
    def _notify_lost(holder: _Holder) -> None:
        try:
            async def _send():
                await holder.ws.send_json(
                    {"v": 1, "type": "session", "event": "lost",
                     "taken_by": holder.client_id and {"name": ""} or None})
                # 简化：只通知事件，不携带新持有者详情
            holder.loop.call_soon_threadsafe(lambda: asyncio.ensure_future(_send()))
        except Exception:
            pass  # 通知失败无妨，前端靠 409 兜底

    def current(self) -> dict | None:
        with self._lock:
            if self._holder is None or self._expired():
                return None
            return self._holder.info()


# 模块级单例（与 node.py 的模式一致）
controller = ControllerLock()


def client_id_from(auth_header: str | None, x_client_id: str | None) -> str:
    """client_id 解析：优先 X-Client-Id 头；缺省用 token 指纹（同 token 客户端互不冲突的退化行为）"""
    if x_client_id:
        return x_client_id
    if auth_header and auth_header.startswith("Bearer "):
        return "tok-" + hashlib.sha256(auth_header[7:].encode()).hexdigest()[:12]
    return "anonymous"
