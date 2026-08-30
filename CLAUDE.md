# ggRobot — 机器人通用平台 v2.0

## 项目定位（2.0 架构）

**多机器人通用管理平台**：Electron 桌面客户端（Mac/Win 双击安装，同局域网）+ 机器人 agent（.deb 分发、systemd 常驻、纯 API）。支持多型号接入（X2/A2/A3/机器狗），能力契约（`contracts/catalog.json`）是三端唯一真源。全套架构决策见记忆 `ggrobot-2-0-platform.md` 与 git 分支 `2.0` 的提交历史。

- **平台**（`platform/`）：desktop = Electron-vite + React + Semi Design(暗色) + Lucide + Zustand；server = FastAPI sidecar（127.0.0.1:8310）+ SQLite
- **agent**（`agents/x2/`）：FastAPI + rclpy（:8300），token 鉴权 + SN 上报（AGIBOT_SN）+ 单机会话锁；`sudo apt install` 免密装 deb
- **web/**：1.0 的 Vue3 前端，**legacy 保留仅作 React 重写参考**（WS 时序 5s/15s/3s、20Hz 遥控+全零停止、相机 4B+JPEG 帧、motions 动作表都在里面），迁完即删

开发机 Mac M2；实机 `agi@10.10.4.175`（ip.txt 首行，sudoers 免密仅 `/usr/bin/apt`）。

## 硬件三计算单元（铁律）

| 设备 | IP | 角色 |
|------|----|------|
| **PC1 运控单元** | 10.0.1.40 | ⛔ **绝对禁止 SSH/改配置**（站立行走的大脑） |
| **PC2 Orin NX** | 10.0.1.41 | ✅ 本项目运行位置，SSH 账号 agi |
| **PC3 交互单元** | 10.0.1.42 | ⚠️ 仅放音视频文件，不改系统（屏幕/扬声器） |

## 目录结构（2.0，分支 `2.0`）

```
ggRobot/
├── agents/x2/                  ← X2 机器人 agent
│   （目录细节见下）
├── agents/a3/                  ← A3-Ultra agent（HTTP RPC + Topic 双通道，严禁 apt）
│   ├── gg_robot/               ← FastAPI + rclpy（骨架复用 X2：server/security/ws 协议层）
│   │   ├── rpc.py              ← 核心：三单元 RPC 端口表 + 封装（tts/motion/nav/map/dance）
│   │   ├── node.py             ← 订阅 BMS/急停/TTS/VAD + 50Hz 速度（m/s→比例换算）
│   │   ├── choreo.py           ← 编排执行器（tts 精确等播完/motion 真实时长/nav/dance）
│   │   └── routes/             ← 对齐 X2 API 形态 + nav/dance/maps 扩展
│   ├── deploy/deploy.sh        ← rsync+venv+systemd user 部署（禁 apt，白名单目录）
│   └── config/robot.yaml       ← 三单元 IP + 速度上限 + 相机清单
│   ├── gg_robot/               ← FastAPI + rclpy/ROS2（原 1.0 后端演进，纯 API 化）
│   │   ├── __main__.py         ← 入口：rclpy守护线程 → FastAPI（:8300）
│   │   ├── server.py           ← 应用工厂（token鉴权 + 会话锁 + CORS）
│   │   ├── node.py             ← ROS2节点：19个Service客户端+传感器订阅+命令队列
│   │   ├── capabilities.py     ← 能力契约上报（catalog v1 格式）
│   │   ├── motions_data.py     ← 30项预设动作权威清单（STAND前置约束）
│   │   ├── routes/             ← REST 路由（tts/motion/velocity/.../health/session）
│   │   └── ws/stream.py        ← WS v2 协议（wildcard订阅 + 二进制相机帧）
│   ├── packaging/              ← .deb 打包（control/postinst/prerm/start.sh/build.sh）
│   ├── navigation/             ← 激光避障独立ROS2节点
│   └── config/robot.yaml       ← 参数配置
├── platform/                   ← 桌面平台
│   ├── desktop/                ← Electron-vite + React + Semi Design（GG Robot 客户端）
│   └── server/                 ← ggplatform：FastAPI sidecar（127.0.0.1:8310）+ SQLite
├── contracts/                  ← 能力类型目录 v1（三端共享）
│   ├── catalog.json            ← 唯一真源（13个能力类型）
│   ├── gen.py                  ← 生成器：make contracts
│   ├── ts/catalog.ts           ← 生成物（renderer）
│   └── py/catalog.py           ← 生成物（platform/agent）
├── web/                        ← 1.0 Vue3 前端（legacy 参考，勿新增功能）
├── docs/                       ← 知识库（api_reference.md / dev_guide.md / patents）
├── Makefile                    ← agent-deb/agent-deploy/contracts/...
├── ip.txt                      ← 实机地址（首行 agi@10.10.4.175）
└── agents/x2/requirements.txt  ← agent 侧 Python 依赖（deb 打包用）
```

## 核心架构

### 命令队列模式（线程安全跨线程通信）

```
浏览器 → FastAPI(uvicorn线程) → queue.Queue → rclpy线程(spin_once轮询)
                    ↑ Future.set_result() ← 执行结果 ← X2Node._dispatch()
```

- ROS2 的 rclpy 必须在自己的线程中 spin，不能直接在 uvicorn async 线程中调用 Service
- API 层通过 `_cmd_queue.put("tts", text="你好")` 返回 Future，最多阻塞等待 10s
- rclpy 线程每 10ms 调用 `node.process_commands()` 消费队列
- `X2Node._dispatch()` 根据 action 名称路由到对应的处理方法

### 跨板重试

所有跨计算单元的 Service 调用走 `retry.call_with_retry()`：**默认 3 次重试，每次 timeout 3.0s**（PlayAudioFile 等特殊接口单次 5s/不重试，避免重复播放）。

### 双通道数据推送

| 通道 | 协议 | 频率 | 内容 |
|------|------|------|------|
| REST API | HTTP | 按需 | 指令控制 |
| WebSocket | WS | 200ms/100ms | 传感器推送 + 相机JPEG帧 + 键盘遥控 |

### 前端技术栈

- Vue 3.5 + TypeScript + Vite 8
- Naive UI（组件库）、Pinia（状态管理）
- ECharts 6（图表）、Three.js 0.185（3D机器人模型）
- PWA 可安装为桌面应用

## 已接入的 ROS2 接口一览

| 接口 | HTTP 路由 | 说明 |
|------|-----------|------|
| PlayTts | `POST /api/tts` | 语音播报 |
| SetMcPresetMotion | `POST /api/motion` | 预设动作（⚠️v0.8.0+ area: 1=左臂/2=右臂/3=双臂/11=全身，非旧位掩码1/2/4/8；motion_id也变动） |
| McLocomotionVelocity | `POST /api/velocity` + WS | 速度控制（需先注册输入源"web_ui"） |
| GetSystemState | `GET /api/system` | 系统状态 |
| PmuState/JointState/Imu | `GET /api/status` + WS推送 | 电池/关节/IMU |
| PlayEmoji | `POST /api/emoji` | 面部表情 |
| SetVolume/GetVolume | `GET\|POST /api/volume` | 音量 |
| SetMute/GetMute | `GET\|POST /api/mute` | 静音 |
| GetMicSource/SetMicSource | `GET\|POST /api/mic/source` | 麦克风设备切换（0=内置 1=外置） |
| VAD 音频采集 | 订阅 `/agent/process_audio_output` | 降噪后 VAD 语音段（PCM 16k/16bit/mono），`GET /api/mic` 状态 / `GET /api/mic/audio` 取段 |
| PlayMediaFile(原PlayAudioFile)/PlayVideo | `POST /api/media/play` | 音视频播放（v0.8.0改名，结构扁平化） |
| SetMcAction | `POST /api/mode` | 运动模式切换（⚠️v0.8.2+ 用 action_desc 字符串: PASSIVE/DAMPING/JOINT/STAND/LOCOMOTION_DEFAULT，非数字ID） |

### 消息 Header 类型差异（必坑）

不同 Service 的 header 结构不同：
- `CommonRequest header` → `req.header.header.stamp`（PlayTts, GetSystemState）
- `RequestHeader header` → `req.header.stamp`（SetMcPresetMotion, SetMcAction）
- `CommonRequest request` → `req.request.header.stamp`（PlayAudioFile, GetMcAction, SetMcInputSource）

## 激光避障模块 (agents/x2/navigation/avoidance.py)

独立 ROS2 节点，实现了安全过滤器模式的激光避障：

**处理链**：PointCloud2解析 → ROI裁剪 → 体素降采样 → RANSAC地面去除+高度过滤（取并集） → 9扇区分区 → EMA平滑 → 状态机决策

**状态机**：IDLE → GO → SLOW → AVOID → TURN → STOP → TRAPPED

**输入**：目标速度（filter模式从 `/cmd_vel` 订阅，auto模式自动生成）
**输出**：安全速度发布到 `/aima/mc/locomotion/velocity`

支持三种模式：`filter`（过滤器）、`auto`（独立自动前进）、`dry_run`（空跑测试）

## 多机编排模块（choreo，设计见 docs/choreo-design.md）

**模型**：时间线多轨 —— `编排 = {name, tracks: [{robot_id, steps: [{type, at, ...}]}]}`，每台机器人一条轨道，`at` = 相对执行开始的秒偏移。

**同步**：时间戳锚定 —— 平台并发分发各机轨道（`POST /api/choreo/load`）→ 广播 `start_ts=now+1.5s`（`POST /api/choreo/start`）→ agent 以 `start_ts` 为时间轴原点按 `at` 到点触发。步骤间顺序执行（`max(due, 上一步完成时刻)`），同轨不打架、跨机按 at 对齐（局域网墙钟漂移 <100ms）。

**执行链路**：
- agent：`agents/x2/gg_robot/choreo.py`（ChoreoRunner + 内置执行器 `_exec_step`，**不复用** task/steps.py 的 handler——tts 子线程吞异常 + execute_step 异常不重抛都会丢失败信号）；失败 raise → 记 failed 跳过继续；WS 事件 `choreo.step/choreo.state` 经 `run_coroutine_threadsafe` 上报
- platform：`ggplatform/choreo/runner.py`（分发/广播/聚合轮询 1s；掉线 3 次判 failed 其余继续；全局单 run 锁；stop 并发停止；10min 超时）+ `routes/choreo.py`（CRUD/run/stop/status/types）
- 前端：`platform/desktop/src/renderer/src/pages/Choreo.tsx`（列表/执行监控/时间线多轨编辑器；步骤类型清单从 agent `/api/choreo/types` 动态拉取，本地 STEP_META 兜底）

**回归测试**：`make test`（= `make test-agent` 单测 24 项 + `make test-e2e` 端到端 18 项，假 agent×2 全链路）。agent 单测无 rclpy 依赖，需 `/opt/homebrew/bin/python3.12`（系统 python3 是 3.9，项目用 3.10+ 语法）。

**M4 实机验证**（待机器人上线）：`make agent-deploy` → `cd platform/desktop && pnpm dev` → 编排页选两台 active 机器人排时间线 → 执行 → 观察每机状态条与实际动作时序（TTS 超时会打断下一步，必要时加 wait 缓冲步骤）。

## 开发命令

```bash
make contracts     # catalog.json → 生成 ts/py 契约代码
make agent-deb     # 构建 X2 agent .deb（产物 agents/x2/packaging/build/）
make agent-deploy  # scp deb 到机器人 + sudo apt install（免密）
make agent-stop    # 停机器人上 1.0 旧服务（装机前清理 8000）
make agent-status  # 查看 systemd 状态 + /api/health
make test          # 多机编排回归：agent 单测 + platform e2e（42 项断言）
make deploy/start  # 开发期调试：rsync 源码 + SSH 前台跑（正式分发走 deb）
```

平台桌面端（M4 后）：`cd platform/desktop && pnpm dev`（自动拉起 platform/server sidecar）。

**A3 机型**（v0.1.0，文档研读见 docs/a3-ultra-dev-notes.md，实机清单 docs/a3-agent-checklist.md）：`make a3-deploy A3_IP=<HDU地址>`（rsync+venv+systemd，严禁 apt）；`make a3-status / a3-log`。A3 速度为比例制（agent 内 m/s→比例换算，上限在 agents/a3/config/robot.yaml）；动作清单=资源服务动态拉取；导航/舞蹈为 A3 独有能力（契约新类型 nav.goto/dance.play 等 6 个，前端编排步骤动态出现）。

**Windows 版**（Mac 交叉打包，无需 Win 电脑）：`make desktop-package-win` —— GitHub Actions（win-sidecar workflow）在 Windows runner 上跑 PyInstaller 出 win sidecar → `gh run download` 拉回 `resources/sidecar-win/` → electron-builder `--win` 交叉出 nsis。远端 `github`（guoxiangjie/ggRobot，gh CLI 已 auth）。Mac/win sidecar 目录分离（`resources/sidecar` / `resources/sidecar-win`），互不覆盖。

**sudoers 铁律**：机器人 agi 免密仅 `/usr/bin/apt`——远程命令只用 `sudo -n apt install`，systemctl/写 /etc 全部收在 deb 的 postinst 内。

## X2 沙盒铁律（实机踩坑结晶，详见 docs/x2-agent-deploy-pitfalls.md）

1. **沙盒双视图**：`/home/agi`（沙盒）与 `/agibot/data/home/agi`（真系统）是同一目录——unit 里用真系统路径，脚本里两者皆可
2. **自启唯一正解**：user systemd + `ExecStart=/usr/bin/agirun bash 脚本`（agirun 是 ELF 直接执行，**勿套外层 bash**，SOP 文档写法在本机会报 126）；启动脚本必须 source `/agibot/data/home/agi/.aima/env/bashrc`（补 user systemd 缺失的 DDS 配置）
3. **SN 只能用 `bash -ic 'echo $AGIBOT_SN'` 读**（定义在 .bashrc 交互段）；device-tree 兜底必须 `tr -d '\0'`
4. **conf 在 `~/.config/ggrobot-agent.conf`（agi 域）**：SSH 直写 + `systemctl --user restart` = 快速配对（免 apt）；agent 只在启动时读一次 conf
5. **Python 用系统 python3 不用 venv**（numpy/ROS 在系统层）；启动脚本禁 `set -u`（ROS setup.bash 炸）慎 `set -e`（`[ ] && cmd` 假值中断）
6. **agent 代码改动后三连验证**：pyflakes → curl /api/health → WS 握手（import 名错误 py_compile 抓不到）
7. **平台 sidecar 单例复用**（8310-8330 探测 healthz），DB 在 userData

## 关键注意事项

1. **PC1永远不碰** — 10.0.1.40是运控大脑
2. **用户数据不在部署目录** — 任务/项目/手机按键/媒体存 `~/ggRobot-data/`（可用 GGROBOT_DATA_DIR 或 robot.yaml server.data_dir 改），`make clean/ship` 全量部署只清 `~/ggRobot` 代码目录，不会清数据；旧版 `~/ggRobot` 内的数据首次启动自动迁移
3. **速度控制前必须注册输入源** — 名称"web_ui"，优先级40，超时1000ms
4. **速度必须持续50Hz发送** — 单条指令无效，松开需发全零
5. **TTS/Service跨板调用不稳定** — 统一 `retry.call_with_retry()`（3次×3.0s）
6. **QoS不匹配是传感器无数据的第一大原因** — 实机统一用 `qos_profile_sensor_data`（BEST_EFFORT+VOLATILE）订阅传感器/相机（可匹配 RELIABLE publisher）；控制指令用 RELIABLE
7. **音视频文件必须传到 PC3 的 `/agibot/data/home/agi/media/`** — face_ui 服务在 PC3 读 agi home 此目录，`/var/tmp` 它读不到（报文件不存在）；PC2→PC3 免密要配 PC2 的 `~/.ssh/config`（系统默认 webssh key 无效），见记忆 face-ui-pc3-media
8. **time.sleep 卡死rclpy spin** — 用 spin_once 循环替代
9. **Mac Python版本** — 用 Homebrew python@3.12，不要用 3.14（llvmlite不兼容）
10. **SDK 版本说明** — 文档站 latest 指向 v0.9.0（部分页面已到 v1.0.0）。项目接口现状：McAction 支持 action_desc 字符串 + action_value 数字 ID（SIT_DOWN=2000/ZERO_TORQUE=4 必须用数字）、area 用 1/2/3/11、相机用 rgbd_head_front、TTS 以 estimated_duration 估时、关节状态是 JointStateArray 非 sensor_msgs。**速查见 docs/api_reference.md 与 docs/dev_guide.md**
11. **MIC VAD 需要唤醒词激活（v0.9+）** — `/agent/process_audio_output` 的 VAD 事件：原生智元交互保持开启时唤醒词仅短时激活；切 only_voice 模式后首次唤醒词即长期激活，后续有语音即触发。ASR 可插拔（robot.yaml mic.asr_provider）：默认 none 只采集不识别；funasr 需在 Orin 装 funasr/modelscope/torch（Jetson 用 NVIDIA wheel）。识别在独立线程跑，绝不阻塞 rclpy 回调
