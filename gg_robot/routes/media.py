"""音视频资源管理 — 上传 / 列表 / 删除 / 播放

文件流程:
  上传 → PC2 暂存 → scp 到 PC3(/agibot/data/home/agi/media) → 播放时用 PC3 路径
"""

import logging
import shutil
import subprocess
from pathlib import Path

from fastapi import APIRouter, UploadFile, File, Form
from fastapi.responses import JSONResponse

from ..config import PC3_HOST, PC3_MEDIA_PATH, PC3_PASSWORD

logger = logging.getLogger(__name__)
router = APIRouter()

PC2_MEDIA = Path.home() / "ggRobot/media"
PC2_MEDIA.mkdir(parents=True, exist_ok=True)

PC3_USER = "agi"
PC3_MEDIA = PC3_MEDIA_PATH


def _pc3_prefix() -> list:
    """配了密码用 sshpass，否则普通 ssh/scp（依赖免密）"""
    return ["sshpass", "-p", PC3_PASSWORD] if PC3_PASSWORD else []


def _scp_to_pc3(local_path: Path) -> bool:
    """将文件拷贝到 PC3，检查返回码（不再假阳性）"""
    pre = _pc3_prefix()
    try:
        subprocess.run(
            pre + ["ssh", "-o", "StrictHostKeyChecking=no", f"{PC3_USER}@{PC3_HOST}",
                   f"mkdir -p {PC3_MEDIA} && chmod 755 {PC3_MEDIA}"],
            capture_output=True, timeout=5,
        )
        r = subprocess.run(
            pre + ["scp", "-o", "StrictHostKeyChecking=no", str(local_path),
                   f"{PC3_USER}@{PC3_HOST}:{PC3_MEDIA}/"],
            capture_output=True, timeout=15,
        )
        if r.returncode != 0:
            logger.warning(f"⚠️ SCP 失败: {r.stderr.decode(errors='replace').strip()}")
            return False
        subprocess.run(
            pre + ["ssh", "-o", "StrictHostKeyChecking=no", f"{PC3_USER}@{PC3_HOST}",
                   f"chmod 644 {PC3_MEDIA}/{local_path.name}"],
            capture_output=True, timeout=5,
        )
        logger.info(f"📦 已同步到 PC3: {local_path.name}")
        return True
    except Exception as e:
        logger.warning(f"⚠️ SCP 到 PC3 失败: {e}")
        return False


def _delete_from_pc3(filename: str) -> bool:
    try:
        r = subprocess.run(
            _pc3_prefix() + ["ssh", "-o", "StrictHostKeyChecking=no", f"{PC3_USER}@{PC3_HOST}",
                             f"rm -f {PC3_MEDIA}/{filename}"],
            capture_output=True, timeout=5,
        )
        return r.returncode == 0
    except Exception:
        return False


@router.post("/api/media/upload")
async def upload(file: UploadFile = File(...)):
    if not file.filename:
        return JSONResponse({"ok": False, "error": "文件名为空"}, status_code=400)

    safe_name = Path(file.filename).name
    local_dest = PC2_MEDIA / safe_name

    with open(local_dest, "wb") as f:
        shutil.copyfileobj(file.file, f)

    synced = _scp_to_pc3(local_dest)
    return {"ok": True, "name": safe_name, "size": local_dest.stat().st_size, "pc3_synced": synced}


@router.get("/api/media/list")
async def list_files():
    if not PC2_MEDIA.exists():
        return {"files": []}

    files = []
    for f in sorted(PC2_MEDIA.iterdir(), key=lambda x: x.stat().st_mtime, reverse=True):
        if f.is_file():
            ext = f.suffix.lower()
            kind = "video" if ext in (".mp4", ".avi", ".mov", ".mkv") else "audio"
            files.append({"name": f.name, "size": f.stat().st_size, "kind": kind, "ext": ext})
    return {"files": files}


@router.delete("/api/media/{name}")
async def delete(name: str):
    path = PC2_MEDIA / name
    if not path.exists():
        return JSONResponse({"ok": False, "error": "文件不存在"}, status_code=404)
    path.unlink()
    _delete_from_pc3(name)
    return {"ok": True}


@router.post("/api/media/play")
async def play(name: str = Form(...)):
    from .. import node as node_mod
    if node_mod._cmd_queue is None:
        return {"ok": False, "error": "后端未初始化"}

    pc3_path = f"{PC3_MEDIA}/{name}"
    future = node_mod._cmd_queue.put("media_play", file_path=pc3_path, file_name=name)
    return future.result(timeout=5.0)
