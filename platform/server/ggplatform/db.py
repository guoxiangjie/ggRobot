"""SQLite（SQLModel）— 库文件路径由 Electron 侧通过 GG_PLATFORM_DB 注入 userData"""

import os
from datetime import datetime, timezone
from pathlib import Path

from sqlalchemy import inspect, text
from sqlmodel import SQLModel, Session, create_engine

DB_PATH = Path(os.environ.get("GG_PLATFORM_DB") or Path(__file__).resolve().parent.parent / "data.db")

engine = create_engine(f"sqlite:///{DB_PATH}", echo=False)


def init_db() -> None:
    DB_PATH.parent.mkdir(parents=True, exist_ok=True)
    SQLModel.metadata.create_all(engine)
    # 轻量迁移：create_all 不改旧表 —— 缺列的表补 ALTER TABLE（加列场景，SQLite 支持）
    insp = inspect(engine)
    with engine.begin() as conn:
        for table in SQLModel.metadata.sorted_tables:
            if not insp.has_table(table.name):
                continue
            existing = {c['name'] for c in insp.get_columns(table.name)}
            for col in table.columns:
                if col.name not in existing:
                    ddl = f'ALTER TABLE {table.name} ADD COLUMN {col.name} {col.type}'
                    if col.server_default is not None:
                        ddl += f' DEFAULT {col.server_default.arg}'
                    elif not col.nullable:
                        ddl += " DEFAULT ''"
                    conn.execute(text(ddl))


def get_session():
    with Session(engine) as session:
        yield session


def utcnow() -> datetime:
    return datetime.now(timezone.utc)
