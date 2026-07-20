# ggRobot — 灵犀 X2 Web 控制台

> 在 X2 机器人上运行，浏览器直接访问控制台。

## 快速开始

```bash
# Mac 上
make all          # 构建前端 + 部署到 Orin
make start        # SSH 到 Orin 启动服务

# 浏览器打开输出的 IP 地址即可
```

## 目录结构

```
ggRobot/
├── gg_robot/        ← Python 后端 (FastAPI + rclpy)
│   ├── routes/      ← REST API
│   └── ws/          ← WebSocket 数据推送
├── web/             ← Vue3 PWA 前端源码
├── static/          ← 前端构建产物
├── navigation/      ← 激光避障
├── config/          ← 参数配置
├── scripts/         ← 运维脚本
├── docs/            ← 知识库文档
└── Makefile         ← 一键构建/部署/启动
```

## 可用命令

| 命令 | 说明 |
|------|------|
| `make web` | 构建前端 |
| `make deploy` | 部署到 Orin |
| `make start` | 启动服务 |
| `make stop` | 停止服务 |
| `make all` | 构建 + 部署 |
| `make install` | 安装 Python 依赖 |
| `make ip` | 查看 Orin IP |
