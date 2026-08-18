"""ggplatform 入口 — python -m ggplatform（Electron sidecar 或开发直跑）

端口：--port 参数 > GG_PLATFORM_PORT 环境变量 > 默认 8310；只绑 127.0.0.1。
"""

import argparse
import os

import uvicorn

from .app import create_app


def main() -> None:
    parser = argparse.ArgumentParser(prog="ggplatform")
    parser.add_argument("--port", type=int, default=None, help="监听端口（默认 8310）")
    args = parser.parse_args()

    port = args.port or int(os.environ.get("GG_PLATFORM_PORT", "8310"))
    app = create_app()
    print(f"🛰 ggplatform: http://127.0.0.1:{port}")
    uvicorn.run(app, host="127.0.0.1", port=port, log_level="info")


if __name__ == "__main__":
    main()
