# ggRobot — X2 机器人 Web 控制台
#
# 部署前请先在机器人上手动停服：pkill -f 'python -m gg_robot'
#
# 用法:
#   make build     # 构建前端
#   make deploy    # 增量化部署（不删旧目录）
#   make ship      # 构建前端 + 清旧目录 + 全新部署
#   make stop      # 停远端服务（杀进程 + 释放 8000）
#   make start     # SSH 前台启动服务
#   make restart   # stop + start（干净重启，解决 address already in use）

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

.PHONY: build deploy clean ship start stop restart migrate-data

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

# ── 停止远端服务（杀进程 + 释放 8000）──
stop:
	@echo "🛑 停止 $(ORIN_HOST) 上的 ggRobot..."
	-ssh $(ORIN_HOST) "pkill -f gg_robot; sleep 2; pkill -9 -f gg_robot 2>/dev/null; sleep 0.5; ss -tlnp 2>/dev/null | grep ':8000' || echo '✅ 8000 已释放'"

# ── 一次性迁移：把旧版存放在部署目录内的用户数据搬到 ~/ggRobot-data ──
# 升级到"数据独立目录"版本前先跑一次，否则 make ship 的 clean 会清掉旧数据。
# 之后每次 ship 只清代码目录 ~/ggRobot，不再影响用户数据。
migrate-data:
	@echo "📦 迁移用户数据到 ~/ggRobot-data..."
	ssh $(ORIN_HOST) "mkdir -p ~/ggRobot-data && for d in tasks projects media; do if [ -d ~/ggRobot/$$d ] && [ ! -e ~/ggRobot-data/$$d ]; then mv ~/ggRobot/$$d ~/ggRobot-data/; fi; done; if [ -f ~/ggRobot/phone_keys.json ] && [ ! -e ~/ggRobot-data/phone_keys.json ]; then mv ~/ggRobot/phone_keys.json ~/ggRobot-data/; fi; ls -A ~/ggRobot-data"
	@echo "✅ 迁移完成（首次部署新代码后启动服务也会自动迁移兜底）"

# ── 干净重启（先停后启，避免端口占用）──
restart: stop start

# ── SSH 启动服务 ──
start:
	@echo "🚀 启动 ggRobot..."
	ssh -t $(ORIN_HOST) "\
		source /opt/ros/humble/setup.bash && \
		source ~/aimdk/install/local_setup.bash && \
		cd $(ORIN_DIR) && \
		python -m gg_robot"
