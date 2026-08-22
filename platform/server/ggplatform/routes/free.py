"""自由控制项 CRUD（platform 侧）

    GET    /api/free-items        列表（含 config 解析）
    POST   /api/free-items        新增
    PATCH  /api/free-items/{id}   更新
    DELETE /api/free-items/{id}   删除

执行不经平台：前端直连 agent（/api/tts、/api/motion、/api/resources/play 现有端点），
项只做存储与校验（robot 在库、tts/action 至少一项）。
"""

import json
import logging
from typing import Optional

from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from sqlmodel import Session, select

from ..db import engine
from ..models import Robot, FreeItem

logger = logging.getLogger(__name__)
router = APIRouter(prefix="/api")


class FreeItemRequest(BaseModel):
    label: str = ""
    robot_id: str = ""
    tts: str = ""
    action: Optional[dict] = None   # {kind:"motion"|"linkcraft", ...}


def _item_dict(it: FreeItem) -> dict:
    try:
        config = json.loads(it.config_json or "{}")
    except json.JSONDecodeError:
        config = {}
    return {
        "id": it.id,
        "label": it.label,
        "robot_id": it.robot_id,
        "tts": config.get("tts", ""),
        "action": config.get("action"),
        "sort": it.sort,
    }


def _validate(req: FreeItemRequest) -> None:
    if not req.robot_id:
        raise HTTPException(400, "必须绑定机器人")
    with Session(engine) as s:
        if s.get(Robot, req.robot_id) is None:
            raise HTTPException(400, "机器人不存在")
    if not req.tts.strip() and not req.action:
        raise HTTPException(400, "语音和动作至少填一项")
    if req.action:
        kind = req.action.get("kind")
        if kind == "motion" and req.action.get("motion_id") is None:
            raise HTTPException(400, "预设动作缺 motion_id")
        if kind == "linkcraft" and not req.action.get("resource_key"):
            raise HTTPException(400, "灵创动作缺 resource_key")
        if kind not in ("motion", "linkcraft"):
            raise HTTPException(400, f"未知动作类型: {kind}")


@router.get("/free-items")
async def list_free_items():
    with Session(engine) as s:
        rows = s.exec(select(FreeItem).order_by(FreeItem.sort, FreeItem.created_at)).all()
        return {"items": [_item_dict(r) for r in rows]}


@router.post("/free-items")
async def create_free_item(req: FreeItemRequest):
    _validate(req)
    with Session(engine) as s:
        it = FreeItem(
            label=req.label.strip() or "未命名",
            robot_id=req.robot_id,
            config_json=json.dumps({"tts": req.tts, "action": req.action}, ensure_ascii=False),
        )
        s.add(it)
        s.commit()
        s.refresh(it)
        return _item_dict(it)


@router.patch("/free-items/{item_id}")
async def patch_free_item(item_id: str, req: FreeItemRequest):
    _validate(req)
    with Session(engine) as s:
        it = s.get(FreeItem, item_id)
        if it is None:
            raise HTTPException(404, "自由项不存在")
        it.label = req.label.strip() or it.label
        it.config_json = json.dumps({"tts": req.tts, "action": req.action}, ensure_ascii=False)
        s.add(it)
        s.commit()
        s.refresh(it)
        return _item_dict(it)


@router.delete("/free-items/{item_id}")
async def delete_free_item(item_id: str):
    with Session(engine) as s:
        it = s.get(FreeItem, item_id)
        if it is None:
            raise HTTPException(404, "自由项不存在")
        s.delete(it)
        s.commit()
    return {"ok": True}
