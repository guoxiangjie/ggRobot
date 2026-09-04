"""A3 Pydantic 请求/响应模型（公共部分与 X2 同名同形，前端零改动）"""

from pydantic import BaseModel, Field


class TtsRequest(BaseModel):
    text: str = Field(..., min_length=1, max_length=400)   # A3 硬限 1024 字节(~200 中文)
    domain: str = Field(default="web_ui")
    is_interrupted: bool = Field(default=True)
    priority_level: int = Field(default=6, ge=0, le=10)
    wait: bool = Field(default=False, description="阻塞到播完（trace_id 轮询）")


class TtsResponse(BaseModel):
    ok: bool
    trace_id: str | None = None


class MotionRequest(BaseModel):
    """A3 动作：motion_id = 资源文件绝对路径（capabilities 上报的 id）"""
    motion_id: str = Field(..., description="动作资源路径，如 /agibot/data/resources/default/motion/握手/握手.mcap")
    duration_ms: int = Field(default=10000, ge=100, le=600000)
    interrupt: bool = Field(default=False)
    pause: bool = Field(default=False)
    reset: bool = Field(default=False)
    repeat: bool = Field(default=False)
    cmd_end: bool = Field(default=False, description="播完自动复位初始姿态（默认不复位）")


class MotionResponse(BaseModel):
    ok: bool
    error: str | None = None


class VelocityRequest(BaseModel):
    forward: float = Field(default=0.0, ge=-1.5, le=1.5)   # m/s（agent 内换算比例）
    lateral: float = Field(default=0.0, ge=-1.5, le=1.5)
    angular: float = Field(default=0.0, ge=-2.0, le=2.0)   # rad/s


class VelocityResponse(BaseModel):
    ok: bool


class NavRequest(BaseModel):
    kind: str = Field(default="goal", description="goal/pose2d/linear_goal/linear_pose2d/precise_goal")
    map_id: str | int
    target_id: int | None = None
    x: float | None = None
    y: float | None = None
    angle: float | None = None


class DanceRequest(BaseModel):
    command: str = Field(default="Start", description="Start/Pause/Stop")
    path: str | None = None
    session_id: str = Field(default="")
