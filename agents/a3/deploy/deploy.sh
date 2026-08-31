#!/usr/bin/env bash
# A3-Ultra agent 部署（HDU）— rsync 源码 + venv + SDK 协议包 + systemd user 自启
# ⚠️ A3 严禁 apt（docs 4 约束）：一切依赖走 venv pip；部署目录必须是白名单路径
# 用法: ./deploy.sh <hd_ip> [token] [sn]
#   例: ./deploy.sh 10.42.10.10 mytoken A3-00042
set -euo pipefail

IP="${1:?用法: deploy.sh <hd_ip> [token] [sn]}"
TOKEN="${2:-$(openssl rand -hex 16)}"
SN="${3:-}"
SDK="${SDK:-$(dirname "$0")/../../../agibot_a3_Ultra_aimdk-dev3.2}"
REMOTE_DIR="/agibot/data/home/agi/Desktop/ggrobot-a3"
SSH="ssh agi@$IP"

echo "📦 [1/6] rsync 源码 → $REMOTE_DIR"
ssh agi@$IP "mkdir -p $REMOTE_DIR/config"
rsync -az --delete --exclude '__pycache__' --exclude '.venv' \
  "$(dirname "$0")/../gg_robot" agi@$IP:$REMOTE_DIR/
rsync -az "$(dirname "$0")/../config/" agi@$IP:$REMOTE_DIR/config/
rsync -az "$(dirname "$0")/../requirements.txt" agi@$IP:$REMOTE_DIR/

echo "📦 [2/6] 传 SDK 协议件（whl + ros2_plugin_proto）"
rsync -az "$SDK/prebuilt/a3_aimdk-3.2.0-py3-none-any.whl" agi@$IP:$REMOTE_DIR/
rsync -az "$SDK/prebuilt/ros2_plugin_proto_aarch64/" agi@$IP:$REMOTE_DIR/ros2_plugin_proto/

echo "📦 [3/6] venv + 依赖（python3.11 —— ROS Jazzy 的 rclpy 是 3.11 包，默认 3.12 不兼容）"
$SSH "cd $REMOTE_DIR && \
  if [ ! -x venv/bin/python ] || ! venv/bin/python --version 2>&1 | grep -q 'Python 3.11'; then rm -rf venv; python3.11 -m venv venv; fi && \
  ./venv/bin/pip install -q -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple && \
  ./venv/bin/pip install -q --force-reinstall ./a3_aimdk-3.2.0-py3-none-any.whl"

echo "📦 [4/6] 写配对 conf（token 永不覆盖）"
$SSH "mkdir -p ~/.config && \
  if [ -f ~/.config/ggrobot-agent.conf ]; then \
    echo '  conf 已存在，跳过（如需重配删掉它）'; \
  else \
    printf 'token=%s\nsn=%s\nmodel=a3-ultra\nport=8300\n' '$TOKEN' '$SN' > ~/.config/ggrobot-agent.conf; \
  fi && cat ~/.config/ggrobot-agent.conf | head -2 | sed 's/token=.*/token=***/'"

echo "📦 [5/6] systemd user 自启 + linger（开机不登录也跑）"
$SSH "mkdir -p ~/.config/systemd/user && cat > ~/.config/systemd/user/ggrobot-a3.service <<'UNIT'
[Unit]
Description=ggRobot A3 agent
After=network-online.target

[Service]
Type=simple
WorkingDirectory=$REMOTE_DIR
# ROS2/DDS 环境（env.sh）+ Jazzy + ros2_plugin_proto（SDK prebuilt）
ExecStart=/bin/bash -c 'source /agibot/software/v0/entry/env/env.sh && source /opt/ros/jazzy/setup.bash && source $REMOTE_DIR/ros2_plugin_proto/share/ros2_plugin_proto/local_setup.bash && exec $REMOTE_DIR/venv/bin/python -m gg_robot'
Environment=PYTHONUNBUFFERED=1
Environment=LANG=C.UTF-8
Restart=on-failure
RestartSec=3

[Install]
WantedBy=default.target
UNIT
systemctl --user daemon-reload && systemctl --user enable ggrobot-a3.service && systemctl --user restart ggrobot-a3.service"
$SSH "loginctl enable-linger agi 2>/dev/null || sudo -n loginctl enable-linger agi || echo '  ⚠️ linger 设置失败（需登录后服务才跑，实机排查）'"

echo "📦 [6/6] 健康检查"
sleep 4
$SSH "curl -s -m 5 http://127.0.0.1:8300/api/health" || echo "  ⚠️ health 未就绪：journalctl --user -u ggrobot-a3 -n 50 排查"
echo ""
echo "✅ 部署完成。token: ${TOKEN}（配对用，conf 已写入机器人）"
