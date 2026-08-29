# 机器人集群控制系统（ggRobot）

> 一台电脑 · 局域网 · 管理任意数量人形机器人（当前支持智元 X2，A3 接入中）

Electron 桌面客户端（Mac / Windows 双击安装）+ 机器人 Agent（.deb 分发、systemd 常驻）。
能力契约（`contracts/catalog.json`）三端唯一真源 —— 新型号接入，平台与界面零改动。

## 核心能力

| 模块 | 说明 |
|------|------|
| 设备管理 | 网段扫描 → 一键装机（agent + 自启 + 配对，约 1 分钟/台）→ 批量更新（带语音播报提醒） |
| 单机操控 | 仪表盘 / 遥控 / 相机（多路 + 拍照）/ 语音（TTS + VAD 采集 + 本地转写）/ 表情 / 媒体 / 动作 八大面板 |
| 自由控制 | 绑定机器人的即点即执行按钮墙（动作/语音/表情自由组合） |
| 多机编排 | 剪映式时间轨道编辑、时间戳锚定多机同步（<100ms）、语音自动配手势、三方 HTTP 步骤 |
| 地图·建图 | 遥控建图实时点云可视化（墙体轮廓随行走生长）+ 轨迹；地图管理 / 重定位 |
| 三方能力 | 任意 HTTP 接口（门禁/灯光/通知）配置即用，编排联动 |
| 本地语音转写 | 双档离线模型：paraformer（82MB 随包）+ SenseVoice（230MB 可选下载） |
| 3D 展馆 | 模型文件加载预览（数字孪生雏形） |

## 目录结构

```
ggRobot/
├── agents/x2/          ← X2 机器人 Agent（FastAPI + rclpy，:8300，deb 打包）
├── platform/
│   ├── desktop/        ← Electron 桌面客户端（React + Semi Design）
│   └── server/         ← ggplatform：FastAPI sidecar（127.0.0.1:8310）+ SQLite
├── contracts/          ← 能力契约目录（catalog.json 唯一真源）
├── web/                ← 1.0 Vue3 前端（legacy，仅作参考）
├── docs/               ← 知识库（API 参考 / 开发指南 / 架构文档）
└── Makefile            ← 全部构建/部署命令
```

## 快速开始

```bash
# 机器人侧
make agent-deb      # 构建 X2 agent .deb
make agent-deploy   # scp + apt install 到机器人（免密）
make agent-status   # 查看 systemd 状态 + /api/health

# 桌面客户端（开发）
cd platform/desktop && pnpm dev     # 自动拉起 sidecar

# 打包发布
make desktop-package     # Mac dmg（本机出 sidecar + electron-builder）
make desktop-package-win # Windows nsis（GitHub Actions 出 win sidecar + 交叉合包）

# 回归测试
make test            # agent 单测 + platform e2e（假 agent 全链路）
```

## 更多文档

- 架构总览：`docs/architecture.md`（HTML 彩图版 `docs/architecture.html` 可导出 PNG）
- 开发指南 / API 速查：`docs/dev_guide.md` · `docs/api_reference.md`
- X2 实机踩坑结晶：`docs/x2-agent-deploy-pitfalls.md`
