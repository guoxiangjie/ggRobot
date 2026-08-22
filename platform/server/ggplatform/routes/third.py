"""三方能力 CRUD + 测试执行（platform 侧，由桌面端代发 —— 桌面机有外网/内网均可达）

    GET    /api/third            能力列表
    POST   /api/third            新建
    PATCH  /api/third/{id}       更新
    DELETE /api/third/{id}       删除
    POST   /api/third/test       测试执行（不落库的临时定义 或 已存能力 + 入参）

编排接入：routes/choreo.py 的 /api/choreo/types 会把能力库注入为步骤类型（third:<id>）；
编排执行：choreo/runner.py 按 start_ts 时间轴代发 third:* 步骤（不经过机器人）。
"""

import json
import logging
from datetime import datetime, timezone

import httpx
from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from sqlmodel import Session, select

from ..db import engine
from ..models import ThirdApi

logger = logging.getLogger(__name__)
router = APIRouter(prefix="/api")


class ThirdSaveRequest(BaseModel):
    name: str = ""
    desc: str = ""
    method: str = "GET"
    url: str = ""
    headers: list[dict] = []        # [{key, value}]（value 可含 {{param}})
    body: str = ""
    params: list[dict] = []         # [{key, label, default}]
    timeout: int = 10


class ThirdTestRequest(ThirdSaveRequest):
    api_id: str = ""                # 已存能力测试（用库内定义+传入 args）；空 = 用请求体内联定义
    args: dict = {}                 # 入参实值


def _api_dict(a: ThirdApi) -> dict:
    try:
        headers = json.loads(a.headers_json or "[]")
    except json.JSONDecodeError:
        headers = []
    try:
        params = json.loads(a.params_json or "[]")
    except json.JSONDecodeError:
        params = []
    return {
        "id": a.id, "name": a.name, "desc": a.desc,
        "method": a.method, "url": a.url, "headers": headers,
        "body": a.body, "params": params, "timeout": a.timeout,
    }


def render(tpl: str, args: dict) -> str:
    """{{key}} 占位替换（未提供的占位符保留原样）"""
    out = tpl
    for k, v in args.items():
        out = out.replace("{{" + k + "}}", str(v))
    return out


async def invoke_third(method: str, url: str, headers: list[dict], body: str,
                       args: dict, timeout: int) -> dict:
    """执行一次三方调用。返回 {ok, status, text}（异常/非2xx → ok False）"""
    try:
        url2 = render(url, args)
        hdrs = {}
        for h in headers:
            k = str(h.get("key", "")).strip()
            if k:
                hdrs[k] = render(str(h.get("value", "")), args)
        kwargs: dict = {"headers": hdrs, "timeout": min(max(timeout, 1), 30)}
        if method.upper() == "POST" and body:
            try:
                kwargs["json"] = json.loads(render(body, args))
            except json.JSONDecodeError:
                kwargs["content"] = render(body, args)
                hdrs.setdefault("Content-Type", "text/plain")
        async with httpx.AsyncClient() as c:
            r = await c.request(method.upper(), url2, **kwargs)
        text = r.text[:2000]
        return {"ok": 200 <= r.status_code < 300, "status": r.status_code, "text": text}
    except Exception as e:
        return {"ok": False, "status": 0, "text": f"{type(e).__name__}: {e}"}


# ── CRUD ──

@router.get("/third")
async def list_third():
    with Session(engine) as s:
        rows = s.exec(select(ThirdApi).order_by(ThirdApi.created_at)).all()
        return {"apis": [_api_dict(r) for r in rows]}


@router.post("/third")
async def create_third(req: ThirdSaveRequest):
    if not req.name.strip() or not req.url.strip():
        raise HTTPException(400, "名称和 URL 必填")
    with Session(engine) as s:
        a = ThirdApi(
            name=req.name.strip(), desc=req.desc,
            method=req.method.upper() if req.method.upper() in ("GET", "POST") else "GET",
            url=req.url.strip(),
            headers_json=json.dumps(req.headers, ensure_ascii=False),
            body=req.body,
            params_json=json.dumps(req.params, ensure_ascii=False),
            timeout=req.timeout,
        )
        s.add(a); s.commit(); s.refresh(a)
        return _api_dict(a)


@router.patch("/third/{api_id}")
async def patch_third(api_id: str, req: ThirdSaveRequest):
    with Session(engine) as s:
        a = s.get(ThirdApi, api_id)
        if a is None:
            raise HTTPException(404, "能力不存在")
        a.name = req.name.strip() or a.name
        a.desc = req.desc
        a.method = req.method.upper() if req.method.upper() in ("GET", "POST") else a.method
        a.url = req.url.strip() or a.url
        a.headers_json = json.dumps(req.headers, ensure_ascii=False)
        a.body = req.body
        a.params_json = json.dumps(req.params, ensure_ascii=False)
        a.timeout = req.timeout
        a.updated_at = datetime.now(timezone.utc)
        s.add(a); s.commit(); s.refresh(a)
        return _api_dict(a)


@router.delete("/third/{api_id}")
async def delete_third(api_id: str):
    with Session(engine) as s:
        a = s.get(ThirdApi, api_id)
        if a is None:
            raise HTTPException(404, "能力不存在")
        s.delete(a); s.commit()
    return {"ok": True}


# ── 测试执行 ──

@router.post("/third/test")
async def test_third(req: ThirdTestRequest):
    """内联定义或已存能力 + 入参 → 实调一次返回响应（配置台即时验证）"""
    if req.api_id:
        with Session(engine) as s:
            a = s.get(ThirdApi, req.api_id)
            if a is None:
                raise HTTPException(404, "能力不存在")
            d = _api_dict(a)
        method, url = d["method"], d["url"]
        headers, body, timeout = d["headers"], d["body"], d["timeout"]
    else:
        method, url = req.method, req.url
        headers, body, timeout = req.headers, req.body, req.timeout
    if not url:
        raise HTTPException(400, "URL 必填")
    result = await invoke_third(method, url, headers, body, req.args, timeout)
    return result
