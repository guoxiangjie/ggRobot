# ggRobot 2.0 — 机器人通用平台（桌面客户端 + 机器人 agent）
#
# 目录结构:
#   agents/x2/     X2 机器人 agent（FastAPI + rclpy，纯 API，.deb 分发）
#   platform/      桌面平台（desktop: Electron-vite + React + Semi / server: FastAPI + SQLite）
#   contracts/     能力类型目录 v1（三端共享，catalog.json 唯一真源）
#   web/           1.0 Vue 前端（legacy，仅作 React 重写参考，不再构建部署）
#
# 用法:
#   make agent-deb      # 构建 X2 agent .deb（M2 提供）
#   make agent-deploy   # 推 deb 到机器人并安装（M2 提供）
#   make agent-stop     # 停机器人上 1.0 旧服务（agent 装机前的清理）
#   make platform-dev   # 本地开发桌面平台（M4 提供）
#   make contracts      # 由 catalog.json 重新生成 TS/Python 契约代码

ORIN_HOST := $(shell grep -v '^\#' ip.txt 2>/dev/null | head -1)
ORIN_DIR  ?= ~/ggRobot

.PHONY: contracts agent-deb agent-deploy agent-stop agent-status deploy start stop sidecar-build desktop-package test test-agent test-e2e

# ── 多机编排回归测试 ──
# test-agent: agent choreo 执行器单测（无 rclpy 依赖，Mac python3.12）
# test-e2e:   platform 编排端到端（假 agent×2，需 platform/server/.venv）
test-agent:
	@echo "🧪 agent choreo 单测..."
	/opt/homebrew/bin/python3.12 agents/x2/tests/test_choreo.py

test-e2e:
	@echo "🧪 platform 编排 e2e（端口 8300/8301/8320 需空闲）..."
	platform/server/.venv/bin/python platform/server/tests/test_choreo_e2e.py

test: test-agent test-e2e

# ── 平台 sidecar 打包（PyInstaller onedir → desktop/resources/sidecar/）──
sidecar-build:
	cd platform/server && .venv/bin/pip install -q pyinstaller
	cd platform/server && .venv/bin/pyinstaller --name ggplatform --onedir --noconfirm \
		--collect-all sqlmodel --collect-all uvicorn --collect-all sherpa_onnx --collect-all numpy --clean \
		run.py
	rm -rf platform/desktop/resources/sidecar
	mkdir -p platform/desktop/resources/sidecar
	cp -R platform/server/dist/ggplatform/ platform/desktop/resources/sidecar/ggplatform
	rm -rf platform/server/dist platform/server/build
	@echo "✅ sidecar → platform/desktop/resources/sidecar/ggplatform"

# ── 桌面 App 出 dmg（sidecar + electron-builder）──
desktop-package: sidecar-build
	cd platform/desktop && ELECTRON_MIRROR="https://npmmirror.com/mirrors/electron/" pnpm package
	@echo "✅ dmg → platform/desktop/release/"

# ── 桌面 App 目录版（免打包调试，快速验证）──
desktop-dir: sidecar-build
	cd platform/desktop && ELECTRON_MIRROR="https://npmmirror.com/mirrors/electron/" pnpm package:dir

# ── 契约生成（contracts/catalog.json → ts/py）──
contracts:
	@echo "🔧 生成契约代码..."
	cd contracts && python3 gen.py
	@echo "✅ 已生成 contracts/ts/catalog.ts + contracts/py/catalog.py"

# ── agent .deb 构建/部署 ──
agent-deb:
	@bash agents/x2/packaging/build.sh

agent-deploy: agent-deb
	@echo "📦 推送并安装 deb 到 $(ORIN_HOST)..."
	scp agents/x2/packaging/build/*.deb $(ORIN_HOST):/tmp/
	ssh $(ORIN_HOST) "sudo -n apt install -y --reinstall /tmp/ggrobot-agent_*.deb"
	@echo "✅ 安装完成: ssh $(ORIN_HOST) 'systemctl status ggrobot-agent'"

agent-status:
	ssh $(ORIN_HOST) "systemctl status ggrobot-agent --no-pager -l | head -20; curl -s http://127.0.0.1:8300/api/health"

# ── 停机器人上的 1.0 旧服务（装机前清理，释放 8000）──
agent-stop:
	@echo "🛑 停止 $(ORIN_HOST) 上的 1.0 服务..."
	-ssh $(ORIN_HOST) "pkill -f gg_robot; sleep 2; pkill -9 -f gg_robot 2>/dev/null; sleep 0.5; ss -tlnp 2>/dev/null | grep ':8000' || echo '✅ 8000 已释放'"

# ── 开发期调试：rsync 源码到机器人（正式分发走 deb，勿用于生产）──
RSYNC_FLAGS = -avz \
	--exclude '.git' \
	--exclude '.claude' \
	--exclude '.idea' \
	--exclude '.DS_Store' \
	--exclude '__pycache__' \
	--exclude '*.pyc' \
	--exclude 'web' \
	--exclude 'docs' \
	--exclude 'platform' \
	--exclude 'contracts' \
	--exclude 'CLAUDE.md' \
	--exclude 'Makefile' \
	--exclude 'README.md' \
	--exclude 'ip.txt' \
	--exclude 'logo.svg' \
	--exclude 'ggRobot-data'

deploy:
	@echo "📦 rsync agents/x2 到 $(ORIN_HOST):$(ORIN_DIR)（开发调试用）..."
	rsync $(RSYNC_FLAGS) ./ $(ORIN_HOST):$(ORIN_DIR)

# ── 开发期调试：SSH 前台跑 agent（未走 systemd，调试用）──
start:
	@echo "🚀 前台启动 agent（调试）..."
	ssh -t $(ORIN_HOST) "\
		source /opt/ros/humble/setup.bash && \
		source ~/aimdk/install/local_setup.bash && \
		cd $(ORIN_DIR)/agents/x2 && \
		python -m gg_robot"

stop: agent-stop
