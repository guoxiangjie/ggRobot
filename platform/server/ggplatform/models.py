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
    agent_version: str = ""                            # agent 版本（health 上报，hub 刷新落库）
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


class FreeItem(SQLModel, table=True):
    """自由控制项 — 即点即执行（绑定机器人；TTS/预设动作/灵创，语音+动作可组合并行）

    config_json: {tts?: str, action?: {kind: "motion"|"linkcraft", motion_id?, area?,
                resource_key?, version?, resource_type?}}
    """

    id: str = Field(default_factory=lambda: str(uuid.uuid4()), primary_key=True)
    label: str = ""
    robot_id: str = Field(index=True)
    config_json: str = "{}"
    sort: int = 0
    created_at: datetime = Field(default_factory=_now)


class ThirdApi(SQLModel, table=True):
    """三方能力 — 可配置的 HTTP 调用定义（编排步骤/事件钩子复用；由本平台代发）

    url/body/headers 中 {{key}} 为占位符，params_json 声明入参（使用方填值）：
        params_json:  [{"key":"city","label":"城市","default":"北京"}]
        headers_json: [{"key":"Authorization","value":"Bearer xxx"}]
    """

    id: str = Field(default_factory=lambda: str(uuid.uuid4()), primary_key=True)
    name: str = ""
    desc: str = ""
    method: str = "GET"                       # GET / POST
    url: str = ""
    headers_json: str = "[]"
    body: str = ""                            # 模板（POST 用，{{key}} 占位）
    params_json: str = "[]"
    timeout: int = 10
    created_at: datetime = Field(default_factory=_now)
    updated_at: datetime = Field(default_factory=_now)
