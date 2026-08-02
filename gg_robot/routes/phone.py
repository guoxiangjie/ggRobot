"""手机端按键绑定 — GET / PUT /api/phone/keys（纯文件 CRUD，不走 cmd_queue）"""

from fastapi import APIRouter
from pydantic import BaseModel

router = APIRouter()


class PhoneKeySlot(BaseModel):
    slot: int
    name: str = ""
    resource_key: str = ""
    version: str = ""
    resource_type: str = ""


class PhoneKeysRequest(BaseModel):
    keys: list[PhoneKeySlot]


@router.get("/api/phone/keys")
async def get_phone_keys():
    from ..task.store import load_phone_keys
    return load_phone_keys()


@router.put("/api/phone/keys")
async def save_phone_keys(req: PhoneKeysRequest):
    from ..task.store import save_phone_keys as _save
    return _save({"keys": [k.model_dump() for k in req.keys]})
