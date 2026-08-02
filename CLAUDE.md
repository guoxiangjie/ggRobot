# ggRobot — 灵犀 X2 机器人 Web 控制台 v2.0

## 项目定位

在智元 X2 人形机器人的 Orin 计算单元（PC2, 10.0.1.41）上运行的 Web 控制台。用户通过浏览器即可操控机器人的所有交互功能：TTS语音、预设动作、速度遥控、表情、音量、媒体播放，并实时查看传感器状态和 3D 孪生模型。

开发机是 Mac M2，网线直连 X2 二次开发网口（Mac IP 10.0.1.2）。

## 硬件三计算单元（铁律）

| 设备 | IP | 角色 |
|------|----|------|
| **PC1 运控单元** | 10.0.1.40 | ⛔ **绝对禁止 SSH/改配置**（站立行走的大脑） |
| **PC2 Orin NX** | 10.0.1.41 | ✅ 本项目运行位置，SSH 账号 agi |
| **PC3 交互单元** | 10.0.1.42 | ⚠️ 仅放音视频文件，不改系统（屏幕/扬声器） |

## 目录结构

```
ggRobot/
├── gg_robot/           ← Python 后端 (FastAPI + rclpy/ROS2)
│   ├── __main__.py     ← 入口：启动rclpy守护线程 → 等待就绪 → 启动FastAPI
│   ├── server.py       ← FastAPI 应用工厂（路由+CORS+静态文件+lifespan）
│   ├── node.py         ← 核心ROS2节点：16个Service客户端+传感器订阅+命令队列
│   ├── schemas.py      ← Pydantic 请求/响应模型
│   ├── retry.py        ← 跨板Service调用重试封装（3次×3.0s，可按接口调）
│   ├── routes/         ← REST API 路由（tts/motion/velocity/system/emoji/media/volume/mic/sequence）
│   └── ws/stream.py    ← WebSocket端点 + 传感器推送 + 相机帧推送 + 键盘遥控
├── web/                ← Vue3 PWA 前端源码
│   └── src/
│       ├── api/        ← HTTP+WebSocket客户端封装
│       ├── stores/     ← Pinia状态（connection + robot）
│       ├── views/      ← 12个页面（Dashboard/Control/Task/Project/Camera/Model3D/Media/Emoji/Linkcraft/System/Phone）
│       ├── components/ ← UI组件（BatteryCard/ImuCard/JointCard/MotionPanel/TtsPanel/VolumePanel/x2model）
│       └── types/      ← AimDK消息类型定义
├── static/             ← 前端构建产物（FastAPI直接托管）
├── navigation/         ← 激光避障独立ROS2节点（点云→地面去除→扇区→决策→安全速度）
├── config/robot.yaml   ← 参数配置
├── docs/               ← 知识库文档
│   ├── api_reference.md ← AimDK v1.0 完整API参考（62个接口）
│   └── dev_guide.md    ← 开发指南
├── scripts/            ← 运维脚本
├── Makefile            ← 一键构建/部署/启动
└── requirements.txt    ← fastapi/uvicorn/websockets/python-multipart
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
| PlayMediaFile(原PlayAudioFile)/PlayVideo | `POST /api/media/play` | 音视频播放（v0.8.0改名，结构扁平化） |
| SetMcAction | `POST /api/mode` | 运动模式切换（⚠️v0.8.2+ 用 action_desc 字符串: PASSIVE/DAMPING/JOINT/STAND/LOCOMOTION_DEFAULT，非数字ID） |

### 消息 Header 类型差异（必坑）

不同 Service 的 header 结构不同：
- `CommonRequest header` → `req.header.header.stamp`（PlayTts, GetSystemState）
- `RequestHeader header` → `req.header.stamp`（SetMcPresetMotion, SetMcAction）
- `CommonRequest request` → `req.request.header.stamp`（PlayAudioFile, GetMcAction, SetMcInputSource）

## 激光避障模块 (navigation/avoidance.py)

独立 ROS2 节点，实现了安全过滤器模式的激光避障：

**处理链**：PointCloud2解析 → ROI裁剪 → 体素降采样 → RANSAC地面去除+高度过滤（取并集） → 9扇区分区 → EMA平滑 → 状态机决策

**状态机**：IDLE → GO → SLOW → AVOID → TURN → STOP → TRAPPED

**输入**：目标速度（filter模式从 `/cmd_vel` 订阅，auto模式自动生成）
**输出**：安全速度发布到 `/aima/mc/locomotion/velocity`

支持三种模式：`filter`（过滤器）、`auto`（独立自动前进）、`dry_run`（空跑测试）

## 开发命令

```bash
make web      # 构建前端（pnpm build→static/）
make deploy   # rsync部署到Orin（ORIN_HOST从ip.txt读取）
make start    # SSH到Orin启动服务（自动source ROS2环境）
make stop     # 停止Orin上的服务
make install  # 安装Orin上的Python依赖
make all      # web + deploy一键
```

## 关键注意事项

1. **PC1永远不碰** — 10.0.1.40是运控大脑
2. **速度控制前必须注册输入源** — 名称"web_ui"，优先级40，超时1000ms
3. **速度必须持续50Hz发送** — 单条指令无效，松开需发全零
4. **TTS/Service跨板调用不稳定** — 统一 `retry.call_with_retry()`（3次×3.0s）
5. **QoS不匹配是传感器无数据的第一大原因** — 实机统一用 `qos_profile_sensor_data`（BEST_EFFORT+VOLATILE）订阅传感器/相机（可匹配 RELIABLE publisher）；控制指令用 RELIABLE
6. **音视频文件必须传到 PC3 的 `/agibot/data/home/agi/media/`** — face_ui 服务在 PC3 读 agi home 此目录，`/var/tmp` 它读不到（报文件不存在）；PC2→PC3 免密要配 PC2 的 `~/.ssh/config`（系统默认 webssh key 无效），见记忆 face-ui-pc3-media
7. **time.sleep 卡死rclpy spin** — 用 spin_once 循环替代
8. **Mac Python版本** — 用 Homebrew python@3.12，不要用 3.14（llvmlite不兼容）
9. **SDK 版本说明** — 文档站 latest 指向 v0.9.0（部分页面已到 v1.0.0）。项目接口现状：McAction 支持 action_desc 字符串 + action_value 数字 ID（SIT_DOWN=2000/ZERO_TORQUE=4 必须用数字）、area 用 1/2/3/11、相机用 rgbd_head_front、TTS 以 estimated_duration 估时、关节状态是 JointStateArray 非 sensor_msgs。**速查见 docs/api_reference.md 与 docs/dev_guide.md**
