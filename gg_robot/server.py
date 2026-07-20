"""X2 Web Backend — FastAPI 应用 + 静态文件服务"""

import asyncio
import logging
from pathlib import Path
from contextlib import asynccontextmanager
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse, Response

logger = logging.getLogger(__name__)

STATIC_DIR = Path(__file__).resolve().parent.parent / "static"


@asynccontextmanager
async def lifespan(app: FastAPI):
    """管理 rclpy 线程 + WebSocket 推送任务的生命周期"""
    # 启动传感器推送后台任务
    from .ws.stream import sensor_pusher, camera_pusher
    sensor_task = asyncio.create_task(sensor_pusher())
    camera_task = asyncio.create_task(camera_pusher())
    logger.info("📡 传感器推送任务已启动")

    yield  # FastAPI 运行中...

    # 清理
    sensor_task.cancel()
    camera_task.cancel()
    logger.info("📡 传感器推送任务已停止")


def create_app() -> FastAPI:
    app = FastAPI(title="ggRobot", version="2.0.0", lifespan=lifespan)

    app.add_middleware(
        CORSMiddleware,
        allow_origins=["*"],
        allow_methods=["*"],
        allow_headers=["*"],
    )

    # ── API 路由 ──
    from .routes import register_routes
    register_routes(app)

    # ── WebSocket 路由 ──
    from .ws.stream import router as ws_router
    app.include_router(ws_router)

    # ── 根路径 ──
    @app.get("/api")
    async def api_root():
        return {"service": "ggRobot", "version": "2.0.0"}

    # ── SPA 静态文件 + 回退路由 ──
    # 必须放在所有 API 路由之后，否则会拦截 API 请求
    if STATIC_DIR.exists() and any(STATIC_DIR.iterdir()):
        async def _serve_static(full_path: str) -> Response:
            """统一静态文件服务 + SPA fallback"""
            file_path = STATIC_DIR / full_path
            # 文件存在 → 直接返回
            if file_path.is_file():
                return FileResponse(file_path)
            # 否则返回 index.html（SPA fallback）
            index = STATIC_DIR / "index.html"
            if index.exists():
                return FileResponse(index)
            return Response("{}", status_code=404, media_type="application/json")

        @app.get("/{full_path:path}")
        async def catch_all(full_path: str):
            return await _serve_static(full_path)

        @app.head("/{full_path:path}")
        async def catch_all_head(full_path: str):
            return await _serve_static(full_path)

        logger.info(f"🌐 静态文件服务: {STATIC_DIR}")
    else:
        @app.get("/")
        async def no_frontend():
            return {"error": "前端未构建，请先运行 make web"}

    return app
