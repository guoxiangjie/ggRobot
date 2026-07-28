# ggRobot — X2 机器人 Web 控制台
#
# 部署前请先在机器人上手动停服：pkill -f 'python -m gg_robot'
#
# 用法:
#   make build     # 构建前端
#   make deploy    # 增量化部署（不删旧目录）
#   make ship      # 构建前端 + 清旧目录 + 全新部署

ORIN_HOST := $(shell grep -v '^\#' ip.txt 2>/dev/null | head -1)
ORIN_DIR  ?= ~/ggRobot

RSYNC_FLAGS = -avz \
	--exclude '.git' \
	--exclude '.claude' \
	--exclude '.idea' \
	--exclude '.DS_Store' \
	--exclude '.gitignore' \
	--exclude '__pycache__' \
	--exclude '*.pyc' \
	--exclude 'web' \
	--exclude 'docs' \
	--exclude 'scripts' \
	--exclude 'CLAUDE.md' \
	--exclude 'Makefile' \
	--exclude 'README.md' \
	--exclude 'ip.txt' \
	--exclude 'logo.svg'

.PHONY: build deploy clean ship start

# ── 前端构建 ──
build:
	@echo "🔨 构建前端..."
	cd web && pnpm build
	@rm -rf static && mkdir -p static
	@cp -r web/dist/* static/
	@echo "✅ 前端已构建到 static/"

# ── 增量部署（不删旧目录）──
deploy:
	@echo "📦 部署到 $(ORIN_HOST):$(ORIN_DIR)..."
	rsync $(RSYNC_FLAGS) ./ $(ORIN_HOST):$(ORIN_DIR)
	@echo "✅ 部署完成"

# ── 删远端旧目录 ──
clean:
	@echo "🗑 删除 $(ORIN_HOST):$(ORIN_DIR)..."
	ssh $(ORIN_HOST) "rm -rf $(ORIN_DIR)"
	@echo "✅ 已清除"

# ── 一键交付：构建 + 清旧 + 全量部署 ──
ship: build clean deploy
	@echo ""
	@echo "✅ 构建+全量部署完成"
	@echo "   启动: make start"

# ── SSH 启动服务 ──
start:
	@echo "🚀 启动 ggRobot..."
	ssh -t $(ORIN_HOST) "\
		source /opt/ros/humble/setup.bash && \
		source ~/aimdk/install/local_setup.bash && \
		cd $(ORIN_DIR) && \
		python -m gg_robot"
