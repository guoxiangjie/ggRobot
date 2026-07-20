#!/bin/bash
# Orin 上一键安装依赖
set -e

echo "📦 安装 Python 依赖..."
pip install fastapi uvicorn websockets python-multipart

echo "✅ 安装完成"
echo ""
echo "启动方式:"
echo "  cd ~/ggRobot && python -m gg_robot"
