"""Pydantic 请求/响应模型"""

from pydantic import BaseModel, Field


class TtsRequest(BaseModel):
    text: str = Field(..., min_length=1, max_length=500)
    domain: str = Field(default="web_ui")
    is_interrupted: bool = Field(default=True)
    priority_level: int = Field(default=6, ge=0, le=10)


class TtsResponse(BaseModel):
    ok: bool


class MotionRequest(BaseModel):
    area: int = Field(..., description="1=左手 2=右手 4=头部 8=腰部")
    motion_id: int = Field(...)
    interrupt: bool = Field(default=False)


class MotionResponse(BaseModel):
    ok: bool
    task_id: int | None = None
    error: str | None = None


class VelocityRequest(BaseModel):
    forward: float = Field(default=0.0, ge=-1.0, le=1.0)
    lateral: float = Field(default=0.0, ge=-1.0, le=1.0)
    angular: float = Field(default=0.0, ge=-1.0, le=1.0)


class VelocityResponse(BaseModel):
    ok: bool
