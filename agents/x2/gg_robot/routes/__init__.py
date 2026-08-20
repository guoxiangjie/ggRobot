"""统一注册所有路由"""

from fastapi import FastAPI


def register_routes(app: FastAPI):
    from .meta import router as meta_router
    from .choreo import router as choreo_router
    from .tts import router as tts_router
    from .motion import router as motion_router
    from .velocity import router as velocity_router
    from .system import router as system_router
    from .emoji import router as emoji_router
    from .media import router as media_router
    from .logo import router as logo_router
    from .volume import router as volume_router
    from .mic import router as mic_router
    from .mode import router as mode_router
    from .sequence import router as sequence_router
    from .camera import router as camera_router
    from .task import router as task_router
    from .resource import router as resource_router
    from .phone import router as phone_router
    from .project import router as project_router
    from .slam import router as slam_router

    app.include_router(meta_router)
    app.include_router(choreo_router)
    app.include_router(tts_router)
    app.include_router(motion_router)
    app.include_router(velocity_router)
    app.include_router(system_router)
    app.include_router(emoji_router)
    app.include_router(media_router)
    app.include_router(logo_router)
    app.include_router(volume_router)
    app.include_router(mic_router)
    app.include_router(mode_router)
    app.include_router(sequence_router)
    app.include_router(camera_router)
    app.include_router(task_router)
    app.include_router(resource_router)
    app.include_router(phone_router)
    app.include_router(project_router)
    app.include_router(slam_router)
