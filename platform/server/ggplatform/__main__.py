"""ggplatform 入口 — python -m ggplatform（Electron sidecar 或开发直跑）

环境变量：GG_PLATFORM_PORT（默认 8310）/ GG_PLATFORM_DB（默认 platform/server/data.db）
只绑 127.0.0.1。
"""

import os

import uvicorn

from .app import create_app


def main() -> None:
    port = int(os.environ.get("GG_PLATFORM_PORT", "8310"))
    app = create_app()
    print(f"🛰 ggplatform: http://127.0.0.1:{port}")
    uvicorn.run(app, host="127.0.0.1", port=port, log_level="info")


if __name__ == "__main__":
    main()
