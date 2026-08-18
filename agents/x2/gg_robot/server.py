"""X2 agent — FastAPI 应用工厂（纯 API：token 鉴权 + 控制会话锁，无前端资产）"""

import asyncio
import logging
from contextlib import asynccontextmanager

from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse

logger = logging.getLogger(__name__)


@asynccontextmanager
async def lifespan(app: FastAPI):
    """管理 WebSocket 推送任务的生命周期"""
    from .ws.stream import sensor_pusher, camera_pusher, sys_pusher
    tasks = [
        asyncio.create_task(sensor_pusher()),
        asyncio.create_task(camera_pusher()),
        asyncio.create_task(sys_pusher()),
    ]
    logger.info("📡 推送任务已启动（sensor 200ms / camera 100ms / sys 10s）")

    yield

    for t in tasks:
        t.cancel()
    logger.info("📡 推送任务已停止")


# 免 token 端点（发现探测 + 调试文档）
_OPEN_PATHS = ("/api/health",)
_OPEN_PREFIXES = ("/docs", "/redoc", "/openapi.json")


def create_app() -> FastAPI:
    from . import __version__
    from .security import verify_bearer, is_paired, controller, client_id_from

    app = FastAPI(title="ggrobot-agent", version=__version__, lifespan=lifespan)

    # CORS 放开（安全由 token 承担，内网定位）：允许平台 renderer 直连
    app.add_middleware(
        CORSMiddleware,
        allow_origins=["*"],
        allow_methods=["*"],
        allow_headers=["Authorization", "X-Client-Id", "X-Client-Name", "Content-Type"],
        expose_headers=["X-Locked-By"],
    )

    # ── token 鉴权 + 控制会话锁（契约 §2）──
    @app.middleware("http")
    async def auth_and_lock(request: Request, call_next):
        path = request.url.path
        method = request.method

        if method == "OPTIONS":  # CORS preflight
            return await call_next(request)
        if path in _OPEN_PATHS or path.startswith(_OPEN_PREFIXES):
            return await call_next(request)

        if path.startswith("/api/"):
            auth = request.headers.get("authorization")
            if not verify_bearer(auth):
                # 未配对 503（装机后 conf 就位才有 token）；token 错 401
                status = 401 if is_paired() else 503
                return JSONResponse({"detail": "unauthorized", "paired": is_paired()}, status_code=status)

            # 控制类（POST，会话锁范围；takeover 豁免——它本身就是夺锁动作）
            if method == "POST" and not path.startswith("/api/session/"):
                client_id = client_id_from(auth, request.headers.get("x-client-id"))
                client_name = request.headers.get("x-client-name", "")
                ok, locked_by = controller.check_or_acquire(client_id, client_name)
                if not ok:
                    return JSONResponse({"detail": "locked", "locked_by": locked_by}, status_code=409)

        return await call_next(request)

    # ── API 路由 ──
    from .routes import register_routes
    register_routes(app)

    # ── WebSocket 路由（自带握手鉴权）──
    from .ws.stream import router as ws_router
    app.include_router(ws_router)

    @app.get("/api")
    async def api_root():
        return {"service": "ggrobot-agent", "version": __version__}

    return app
