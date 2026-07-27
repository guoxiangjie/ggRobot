#!/bin/bash
# Mac → Orin 一键部署
set -e

ORIN_HOST="${ORIN_HOST:-agi@10.0.1.41}"
ORIN_DIR="${ORIN_DIR:-~/ggRobot}"

echo "📦 部署到 ${ORIN_HOST}:${ORIN_DIR}..."

rsync -avz \
  --exclude '.git' \
  --exclude 'docs' \
  --exclude '__pycache__' \
  --exclude '*.pyc' \
  --exclude 'web/node_modules' \
  --exclude '.DS_Store' \
  "$(dirname "$0")/../" "${ORIN_HOST}:${ORIN_DIR}"

echo "✅ 部署完成"
echo ""
echo "启动: ssh ${ORIN_HOST} 'cd ${ORIN_DIR} && python -m gg_robot'"
