#!/usr/bin/env python3
"""契约代码生成器 — catalog.json 唯一真源，生成 TS/Python 两份产物。

用法: cd contracts && python3 gen.py
产物: ts/catalog.ts（renderer 用） / py/catalog.py（platform + agent 用，Pydantic）
"""

import json
from pathlib import Path

HERE = Path(__file__).resolve().parent


def main() -> None:
    catalog = json.loads((HERE / "catalog.json").read_text(encoding="utf-8"))

    # ── TypeScript ──
    ts = TS_TEMPLATE.format(
        version=catalog["catalog_version"],
        data=json.dumps(catalog, ensure_ascii=False, indent=2),
    )
    (HERE / "ts").mkdir(exist_ok=True)
    (HERE / "ts" / "catalog.ts").write_text(ts, encoding="utf-8")

    # ── Python (Pydantic) ──
    py = PY_TEMPLATE.format(
        version=catalog["catalog_version"],
        data=json.dumps(catalog, ensure_ascii=False, indent=4),
    )
    (HERE / "py").mkdir(exist_ok=True)
    (HERE / "py" / "catalog.py").write_text(py, encoding="utf-8")

    n = len(catalog["capabilities"])
    print(f"✅ 生成完成: ts/catalog.ts + py/catalog.py（catalog v{catalog['catalog_version']}，{n} 个能力类型）")


TS_TEMPLATE = """\
// ⚠️ 自动生成（contracts/gen.py），勿手改 — 真源: contracts/catalog.json
export const CATALOG_VERSION = {version};

export interface CapabilityCallParam {{ [field: string]: string }}   // 字段名 → "类型 默认值 说明"
export interface CapabilityReportParam {{ [field: string]: string }}

export interface CapabilityType {{
  type: string
  category: 'motion' | 'expression' | 'perception' | 'status'
  desc: string
  call: CapabilityCallParam
  report: CapabilityReportParam
}}

export interface Catalog {{
  catalog_version: number
  desc: string
  capabilities: CapabilityType[]
}}

export const CATALOG: Catalog = {data};

export const CAPABILITY_TYPES: string[] = CATALOG.capabilities.map((c) => c.type);
"""


PY_TEMPLATE = '''\
"""⚠️ 自动生成（contracts/gen.py），勿手改 — 真源: contracts/catalog.json"""
from typing import Any

CATALOG_VERSION = {version}

CATALOG: dict[str, Any] = {data}


def capability_types() -> list[str]:
    """目录内全部能力类型名"""
    return [c["type"] for c in CATALOG["capabilities"]]


def get_type(type_name: str) -> dict[str, Any] | None:
    for c in CATALOG["capabilities"]:
        if c["type"] == type_name:
            return c
    return None
'''


if __name__ == "__main__":
    main()
