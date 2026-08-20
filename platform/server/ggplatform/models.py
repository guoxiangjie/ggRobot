"""数据模型 — robots 表（SN 唯一索引，robot_id 平台生成）"""

import uuid
from datetime import datetime, timezone

from sqlmodel import SQLModel, Field


def _now() -> datetime:
    return datetime.now(timezone.utc)


class Robot(SQLModel, table=True):
    id: str = Field(default_factory=lambda: str(uuid.uuid4()), primary_key=True)
    sn: str = Field(unique=True, index=True)          # 物理身份（AGIBOT_SN），配对/恢复靠它
    name: str = ""                                     # 用户别名「实验室X2-2号」
    model: str = "x2"
    token: str                                         # 设备令牌（与 SN 分开，可轮换）
    status: str = "pending"                            # pending(装机中) / active(已激活)
    last_ip: str = ""
    port: int = 8300                                   # agent 端口（默认 8300，可覆盖）
    last_seen: datetime | None = None
    capabilities_json: str = "{}"
    created_at: datetime = Field(default_factory=_now)


class Choreography(SQLModel, table=True):
    """多机编排 — 时间线多轨模型（docs/choreo-design.md §2）

    tracks_json: [{robot_id, robot_name, steps:[{type, at, ...}]}]
    """

    id: str = Field(default_factory=lambda: str(uuid.uuid4()), primary_key=True)
    name: str = "未命名编排"
    desc: str = ""
    tracks_json: str = "[]"
    created_at: datetime = Field(default_factory=_now)
    updated_at: datetime = Field(default_factory=_now)
