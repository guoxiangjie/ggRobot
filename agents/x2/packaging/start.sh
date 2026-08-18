#!/bin/bash
# /opt/ggrobot-agent/start.sh — systemd ExecStart 包装
# source ROS2 humble + AimDK 环境（与手动启动逐字等价，解决非交互 shell 环境缺失问题）
set -e

source /opt/ros/humble/setup.bash

# AimDK 路径兜底（systemd User=agi 会设 HOME；缺失时跳过让 agent 报具体错误）
AIMDK_SETUP="${HOME:-/home/agi}/aimdk/install/local_setup.bash"
[ -f "$AIMDK_SETUP" ] && source "$AIMDK_SETUP"

exec /opt/ggrobot-agent/venv/bin/python -m gg_robot
