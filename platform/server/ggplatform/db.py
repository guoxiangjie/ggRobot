"""SQLite（SQLModel）— 库文件路径由 Electron 侧通过 GG_PLATFORM_DB 注入 userData"""

import os
from datetime import datetime, timezone
from pathlib import Path

from sqlmodel import SQLModel, Session, create_engine

DB_PATH = Path(os.environ.get("GG_PLATFORM_DB") or Path(__file__).resolve().parent.parent / "data.db")

engine = create_engine(f"sqlite:///{DB_PATH}", echo=False)


def init_db() -> None:
    DB_PATH.parent.mkdir(parents=True, exist_ok=True)
    SQLModel.metadata.create_all(engine)


def get_session():
    with Session(engine) as session:
        yield session


def utcnow() -> datetime:
    return datetime.now(timezone.utc)
