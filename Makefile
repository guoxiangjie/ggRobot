# ggRobot — X2 机器人 Web 控制台
# 用法:
#   ORIN_HOST=agi@192.168.x.x make deploy    # 先设 IP 再部署
#   ORIN_HOST=agi@192.168.x.x make start     # 先设 IP 再启动
#   ORIN_HOST=agi@192.168.x.x make all       # 构建+部署
#
# 默认值 (网线直连):
#   ORIN_HOST=agi@10.0.1.41

ORIN_HOST := $(shell grep -v '^\#' ip.txt 2>/dev/null | head -1)
ORIN_DIR  ?= ~/ggRobot

RSYNC = rsync -avz --exclude '.git' --exclude '__pycache__' --exclude '*.pyc' --exclude 'web/node_modules'

.PHONY: web deploy install start stop ip all

# ── 前端构建 ──
web:
	@echo "🔨 构建前端..."
	cd web && pnpm build
	@rm -rf static && mkdir -p static
	@cp -r web/dist/* static/
	@echo "✅ 前端已构建到 static/"

# ── 部署 ──
deploy:
	@echo "📦 部署到 $(ORIN_HOST):$(ORIN_DIR)..."
	$(RSYNC) ./ $(ORIN_HOST):$(ORIN_DIR)
	@echo "✅ 部署完成"

# ── 安装依赖 ──
install:
	@echo "📦 安装 Orin 依赖..."
	ssh $(ORIN_HOST) "pip install fastapi uvicorn websockets python-multipart"
	@echo "✅ 依赖安装完成"

# ── 启动 ──
start:
	@echo "🚀 启动 ggRobot..."
	ssh -t $(ORIN_HOST) "\
		source /opt/ros/humble/setup.bash && \
		source ~/aimdk/install/local_setup.bash && \
		cd $(ORIN_DIR) && \
		IP=\$$(grep -oE '[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+' $(ORIN_DIR)/ip.txt | head -1) && \
		echo '' && \
		echo '================================' && \
		echo '  访问: http://'\$$IP':8000' && \
		echo '================================' && \
		echo '' && \
		python -m gg_robot"

# ── 停止 ──
stop:
	@echo "⏹ 停止 ggRobot..."
	ssh $(ORIN_HOST) "pkill -f 'python -m gg_robot' || true"
	@echo "✅ 已停止"

# ── 全部 ──
all: web deploy
	@echo ""
	@echo "✅ 构建+部署完成"
	@echo "   运行: ORIN_HOST=$(ORIN_HOST) make start"
