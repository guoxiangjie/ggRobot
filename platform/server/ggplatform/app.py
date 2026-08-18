"""平台应用工厂（只绑 127.0.0.1，供 Electron renderer 本机访问）"""

import logging
from contextlib import asynccontextmanager

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(name)s: %(message)s")
logger = logging.getLogger("ggplatform")


@asynccontextmanager
async def lifespan(app: FastAPI):
    from .db import init_db, DB_PATH
    init_db()
    logger.info(f"🗄 SQLite: {DB_PATH}")
    yield


def create_app() -> FastAPI:
    app = FastAPI(title="ggplatform", version="2.0.0", lifespan=lifespan)

    # renderer 来源：dev http://localhost:5173 / prod file://（Origin null）→ 放开即可（本机绑定）
    app.add_middleware(
        CORSMiddleware,
        allow_origins=["*"],
        allow_methods=["*"],
        allow_headers=["*"],
    )

    from .routes.robots import router as robots_router
    from .routes.pair import router as pair_router
    from .routes.hub import router as hub_router
    app.include_router(robots_router)
    app.include_router(pair_router)
    app.include_router(hub_router)

    @app.get("/healthz")
    async def healthz():
        return {"ok": True, "service": "ggplatform"}

    return app
