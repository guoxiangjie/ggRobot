"""ggplatform 入口 — python -m ggplatform（Electron sidecar 或开发直跑）

端口：--port 参数 > GG_PLATFORM_PORT 环境变量 > 默认 8310；只绑 127.0.0.1。
"""

import argparse
import os
import sys

import uvicorn

from .app import create_app


def main() -> None:
    # Windows 管道 stdout 默认 ANSI(GBK)，print emoji 直接 UnicodeEncodeError 崩进程
    # （Electron spawn 走管道必炸；控制台手动跑不炸——差异即坑）。强制 UTF-8 + 容错。
    for stream in (sys.stdout, sys.stderr):
        if stream is not None:
            try:
                stream.reconfigure(encoding="utf-8", errors="replace")
            except (AttributeError, OSError):
                pass

    parser = argparse.ArgumentParser(prog="ggplatform")
    parser.add_argument("--port", type=int, default=None, help="监听端口（默认 8310）")
    args = parser.parse_args()

    port = args.port or int(os.environ.get("GG_PLATFORM_PORT", "8310"))
    app = create_app()
    print(f"🛰 ggplatform: http://127.0.0.1:{port}")
    uvicorn.run(app, host="127.0.0.1", port=port, log_level="info")


if __name__ == "__main__":
    main()
