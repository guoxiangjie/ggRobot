"""统一注册所有路由（A3）"""

from fastapi import FastAPI


def register_routes(app: FastAPI):
    from .meta import router as meta_router
    from .tts import router as tts_router
    from .motion import router as motion_router
    from .velocity import router as velocity_router
    from .system import router as system_router
    from .volume import router as volume_router
    from .mode import router as mode_router
    from .nav import router as nav_router
    from .dance import router as dance_router
    from .maps import router as maps_router
    from .choreo import router as choreo_router
    from .camera import router as camera_router
    from .mic import router as mic_router

    app.include_router(meta_router)
    app.include_router(tts_router)
    app.include_router(motion_router)
    app.include_router(velocity_router)
    app.include_router(system_router)
    app.include_router(volume_router)
    app.include_router(mode_router)
    app.include_router(nav_router)
    app.include_router(dance_router)
    app.include_router(maps_router)
    app.include_router(choreo_router)
    app.include_router(camera_router)
    app.include_router(mic_router)
