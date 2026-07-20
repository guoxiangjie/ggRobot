# 灵犀 X2 二开知识库

> 本文是全部对话的技术沉淀。新窗口先读本文件，再开干。
> 最后更新：2026-07-08

---

## 一、设备与网络

### 1.1 硬件清单

| 设备 | 配置 | 角色 |
|------|------|------|
| Mac M2 | 24GB，arm64 | 开发机，PyCharm 写代码 |
| Ubuntu 22.04 | @ 10.10.91.170，16核/15GB/900GB，GTX 1650 | 上位机，ROS2 环境 |
| X2 旗舰版 | 展厅，有吊架，Agibot Go APP | 真机 |

### 1.2 X2 三个计算单元（关键认知）

```
PC1 运控单元  10.0.1.40  ⛔ 绝对禁止 SSH/改配置（站立行走的大脑）
PC2 开发单元  10.0.1.41  ✅ SSH 账号 agi，二开程序跑这里（Orin NX 157TOPS）
PC3 交互单元  10.0.1.42  ⚠️ 只放音视频文件，不改系统（屏幕/扬声器）
```

**铁律：PC1 永远不碰。** TTS 不需要文件；PlayVideo/PlayAudio 必须先把文件放 PC3。

### 1.3 连接方式

- **网线直连**（推荐）：Mac 网线 → X2 二次开发网口
- Mac 配静态 IP `10.0.1.2/255.255.255.0`，路由器留空
- **网络服务顺序**：系统设置→网络→设定服务顺序，Wi-Fi 在网线之上（Wi-Fi 上网 + 网线连机器人）
- 也可连 X2 Wi-Fi 热点，但会断网

### 1.4 SSH 连接

```bash
ssh agi@10.0.1.41       # 进 PC2
# scp 拉文件
scp -r agi@10.0.1.41:~/aimdk ~/Documents/code/机器人/aimdk_v1.0
```

Mac clash 代理：`127.0.0.1:7890`，拉 GitHub 时用。

---

## 二、开发环境

### 2.1 Mac 环境

- **Python**：用 Homebrew `python@3.12`（**不要用 3.14**，llvmlite 不兼容）
  - 全局 PATH：`/opt/homebrew/opt/python@3.12/libexec/bin`
- **Poetry**：pipx 装，但 pipx 依赖 3.14 无法卸载。项目用 `poetry env use /opt/homebrew/bin/python3.12` 指定版本
- **核心坑**：Python 3.11+ 有 PEP668，不能直接 `pip install`，要用 `pipx`（命令行工具）或 venv（项目库）

### 2.2 Ubuntu 环境（已装好）

```bash
source /opt/ros/humble/setup.bash
source ~/lx2501_3-v0.9.0.4/install/local_setup.bash
# 已写入 ~/.bashrc 自动加载
```

- ROS2 Humble + SDK v0.9 编译（56 条 aimdk 接口）
- MuJoCo 3.9 + RViz2
- 国内源：阿里云（apt）+ 清华 ROS2 源（`mirrors.tuna.tsinghua.edu.cn/ros2/ubuntu`，注意是 ros2 不是 ros）

### 2.3 Orin 上的 SDK

- 真机自带 SDK v1.0（`~/aimdk`），比 0.9 多了 SLAM/导航/RL部署
- 编译：`cd ~/aimdk && colcon build && source install/local_setup.bash`
- **aimdk_msgs 路径**：`~/aimdk/install/aimdk_msgs/local/lib/python3.10/dist-packages`

### 2.4 PyCharm 远程开发

- 配 SSH 解释器 → 10.0.1.41，解释器 `/usr/bin/python3`（**不要建 venv**，ROS2 在 venv 里跑不了）
- 报红处理：Interpreter Paths 加
  - `/opt/ros/humble/local/lib/python3.10/dist-packages`（rclpy）
  - `/home/agi/aimdk/install/aimdk_msgs/local/lib/python3.10/dist-packages`
- **PyCharm 运行 ROS2 程序易报 `No module rpyutils`**，最稳是用终端 source 后跑；调试要配 PYTHONPATH/LD_LIBRARY_PATH/AMENT_PREFIX_PATH 三大环境变量

---

## 三、ROS2 接口实战

### 3.1 关键只读 Topic（安全，先练这些）

| 功能 | 话题 | 消息类型 |
|------|------|---------|
| 电池/电源 | `/aima/hal/pmu/state` | `aimdk_msgs/msg/PmuState` |
| 手臂关节 | `/aima/hal/joint/arm/state` | `sensor_msgs/msg/JointState` |
| IMU | `/aima/hal/imu/torso/state` | `sensor_msgs/msg/Imu` |
| 头部触摸 | `/aima/hal/sensor/touch_head` | `aimdk_msgs/msg/TouchState` |
| RGBD 前视 | `/aima/hal/sensor/rgbd_head_front/rgb_image` | `sensor_msgs/msg/Image` |
| 后视 RGB | `/aima/hal/sensor/rgb_head_rear/rgb_image` | `sensor_msgs/msg/Image` |

### 3.2 关键 Service

| 功能 | 服务 | 类型 |
|------|------|------|
| 语音播报 | `/aimdk_5Fmsgs/srv/PlayTts` | `aimdk_msgs/srv/PlayTts` |
| 运动模式查询 | `/aimdk_5Fmsgs/srv/GetMcAction` | `aimdk_msgs/srv/GetMcAction` |
| 预设动作 | `/aimdk_5Fmsgs/srv/SetMcPresetMotion` | `aimdk_msgs/srv/SetMcPresetMotion` |

### 3.3 ⭐ QoS 必坑

**订阅传感器收不到数据，99% 是 QoS 不匹配**：

```python
from rclpy.qos import qos_profile_sensor_data  # 最简单，BEST_EFFORT 预设
self.create_subscription(Image, topic, cb, qos_profile_sensor_data)
```

或手动：
```python
QoSProfile(reliability=QoSReliabilityPolicy.BEST_EFFORT,
           durability=QoSDurabilityPolicy.VOLATILE,
           history=QoSHistoryPolicy.KEEP_LAST, depth=1)
```

### 3.4 TTS 调用模板

```python
req = PlayTts.Request()
req.tts_req.text = "你好"
req.tts_req.domain = "demo"          # 必填，调用方标识
req.tts_req.trace_id = "xxx"         # 可选
req.tts_req.is_interrupted = True    # 必填，打断当前播报
req.tts_req.priority_level.value = 6 # INTERACTION_L6
# 跨板通信要重试 8 次（ROS2 已知问题）
for i in range(8):
    req.header.header.stamp = node.get_clock().now().to_msg()
    future = client.call_async(req)
    rclpy.spin_until_future_complete(node, future, timeout_sec=0.25)
    if future.done(): break
```

### 3.5 可用相机

只有 **RGBD 前视**默认有数据。双目（stereo_left/right）可能没启动。拍照用官方 `take_photo` 示例，支持 `--ros-args -p image_topic:=...` 切相机。

---

## 四、Demo 实现（已跑通的）

代码位置：Mac `~/Documents/code/机器人/x2_workspace/demo/` 和 Orin `~/project/tts/`

### 4.1 已实现

1. **battery_monitor.py** — 电池仪表盘（PmuState，电量/电压/温度）
2. **take_photo.py** — 拍照（官方例，qos_profile_sensor_data）
3. **play_tts.py** — TTS 播报（官方例，含重试机制）

### 4.2 Mac 本地验证链路（已跑通）

```
test_mac.py     — 人脸注册 + 摄像头识别（InsightFace）
test_full_chain.py — 语音唤醒(FunASR) + 人脸 + 查日报 + 朗读
```

- **InsightFace**：buffalo_l 模型（5个ONNX），ArcFace 512维向量，余弦相似度>0.45 判定
- **FunASR**：paraformer-zh 本地 ASR，GPU rtf=0.09。坑：numba/llvmlite 版本锁死，要 `numba>=0.60 llvmlite>=0.43 numpy<2.2`

### 4.3 待做

- 人脸识别 + TTS 完整 Demo（在 Orin 跑，调 RGBD 相机）
- play_video（需先传视频到 PC3）

---

## 五、模型与文件位置

| 内容 | 路径 |
|------|------|
| SDK v0.9 | Mac `~/Documents/code/机器人/lx2501_3-v0.9.0.4` |
| SDK v1.0 | Mac `~/Documents/code/机器人/aimdk_v1.0`（含 extra/x2_rl_deploy）|
| URDF | Mac `~/Documents/code/机器人/X2_URDF-v1.3.0` |
| AimRT 源码 | Mac `~/Documents/code/机器人/AimRT-main` |
| Link-U-OS 源码 | Mac `~/Documents/code/机器人/Link-U-OS-main`（子模块未拉）|
| 方案文档 | `二开学习方案.md`、`阶段一-执行计划.md` |
| InsightFace 模型 | `~/.insightface/models/buffalo_l/`（~480MB）|
| FunASR 模型 | `~/.cache/modelscope/hub/models/iic/`（~2GB）|

---

## 六、核心技术架构（智元全家桶）

```
┌─────────────────────────────────────────────┐
│ VLA 模型（GO-1，2025.9 开源）               │ ← 视觉+语言→动作（叠衣服/抓取）
├─────────────────────────────────────────────┤
│ RL 运控策略（Link-U-OS rl_training）         │ ← 站立/行走
│   X2 部署框架：aimdk_v1.0/extra/x2_rl_deploy │
├─────────────────────────────────────────────┤
│ AimRT 通信中间件（16个插件，ros2/grpc/mqtt） │
├─────────────────────────────────────────────┤
│ AimDK / GDK SDK（你用的 aimdk_msgs）         │
├─────────────────────────────────────────────┤
│ 硬件（X2灵犀 / A2远征 / G2精灵）             │
└─────────────────────────────────────────────┘
```

**X2 旗舰版**：30 DOF（腿12+臂14+腰3+头1），Orin NX 157TOPS+16GB，约1.31m/39kg，3个计算单元。

---

## 七、关键卡点与出路

### 7.1 MuJoCo 里 X2 站不稳
- **原因**：URDF 默认增益 kp=1.0 太小；本质是缺 RL 策略
- **出路**：v1.0 的 `x2_rl_deploy` 是官方部署框架，需配策略 .pt

### 7.2 X2 RL 策略 .pt 未开源
- **路线A**：自己训（X2 URDF + Link-U-OS rl_training + 4090，几天）
- **路线B（推荐）**：问智元技术支持要（付费客户，理由充分）
- **路线C**：先训 A2 跑通流程

### 7.3 GO-1 VLA 模型
- 已开源：huggingface `agibot-world/GO-1`、GO-1-Air（轻量）
- 代码：github `OpenDriveLab/AgiBot-World`
- 4090 可推理（~7GB），微调全模型需 A100
- 是**操作模型**（抓取/叠衣），不是 Demo 要的感知模型

---

## 八、常用命令速查

```bash
# Mac 连 X2
ssh agi@10.0.1.41

# Orin 上跑 ROS2 程序
source /opt/ros/humble/setup.bash && source ~/aimdk/install/local_setup.bash
cd ~/project/tts && python3 xxx.py

# 看话题帧率（确认有数据）
ros2 topic hz /aima/hal/sensor/rgbd_head_front/rgb_image

# 查服务类型
ros2 service type /aimdk_5Fmsgs/srv/PlayTts

# 查消息定义
ros2 interface show aimdk_msgs/srv/PlayTts

# 拉照片到 Mac
scp agi@10.0.1.41:~/project/tts/images/*.png ~/Desktop/

# MuJoCo 看模型（Ubuntu 桌面）
cd ~/X2_URDF-v1.3.0 && DISPLAY=:1 python3 ~/x2_workspace/hello_x2.py
```

---

## 九、Web 控制台架构

### 9.1 整体架构

```
前端(PWA Vue3) ──rosbridge :9090──► 实时数据（电池/IMU/关节/相机）
               ──FastAPI :8000──► 指令控制（TTS/动作/速度/音量）
               ──FastAPI WS ────► 键盘遥控
```

- **rosbridge**：ROS2 官方桥，apt 安装，WebSocket 直连，前端 roslib v2 订阅
- **FastAPI**：自研后端，命令队列模式（uvicorn 线程→Queue→rclpy 线程），8次跨板重试

### 9.2 项目位置

| 项目 | Mac 路径 | Orin 路径 |
|------|----------|-----------|
| 前端 | `~/PycharmProjects/tts/console/` | —（pnpm dev 或 build） |
| 后端 | `~/PycharmProjects/tts/backend/` | `~/project/tts/backend/` |
| 转换工具 | `console/tools/` | — |

### 9.3 启动命令（Orin 上）

```bash
# rosbridge
source /opt/ros/humble/setup.bash && source ~/aimdk/install/local_setup.bash
ros2 launch rosbridge_server rosbridge_websocket_launch.xml

# 后端
cd ~/project/tts/backend && source /opt/ros/humble/setup.bash && source ~/aimdk/install/local_setup.bash
python -m x2_backend.main

# 或一键
cd ~/project/tts/backend/scripts && bash start_all.sh
```

### 9.4 连接方式

- **网线直连**：Mac IP `10.0.1.2/24`，Orin `10.0.1.41`
- **WiFi**：Orin 连路由器后 `hostname -I` 查 IP，前端连接面板改 IP
- 每 5 秒心跳检测，刷新页面自动重连（localStorage 持久化）

---

## 十、后端架构详解

### 10.1 命令队列模式

```
FastAPI(uvicorn线程) → queue.Queue → rclpy线程(spin_once轮询)
```

- API 层 `_cmd_queue.put("tts", text="你好")` 返回 `concurrent.futures.Future`
- rclpy 线程 `node.process_commands()` 从队列取命令执行
- 结果通过 `future.set_result()` 返回给 API 线程

### 10.2 跨板重试

```python
for i in range(8):
    req = build_request()
    future = client.call_async(req)
    rclpy.spin_until_future_complete(node, future, timeout_sec=0.25)
    if future.done(): return future.result()
```

### 10.3 已接入的 Service

| Service | 接口 | 说明 |
|---------|------|------|
| PlayTts | POST /api/tts | 语音播报 |
| SetMcPresetMotion | POST /api/motion | 预设动作（挥手/比心等） |
| SetMcInputSource | — | 运动控制输入源注册 |
| SetVolume/GetVolume | GET/POST /api/volume | 音量控制 |
| SetMute/GetMute | GET/POST /api/mute | 静音控制 |
| GetMcAction | — | 查询运动模式 |
| GetSystemState | GET /api/system | 系统状态 |
| PlayEmoji | POST /api/emoji | 表情控制 |

### 10.4 消息类型差异（必坑）

不同 Service 的 header 类型不同：
- `CommonRequest header` → `req.header.header.stamp`（PlayTts, GetSystemState）
- `RequestHeader header` → `req.header.stamp`（SetMcPresetMotion, SetMcAction）
- `CommonRequest request` → `req.request.header.stamp`（PlayAudioFile, GetMcAction, SetMcInputSource）

---

## 十一、3D 模型（X2 孪生）

### 11.1 数据来源

- URDF：`知识库/X2_URDF-v1.3.0/x2_ultra.urdf`（31 DOF）
- STL：`知识库/X2_URDF-v1.3.0/meshes/`（45 个文件，111MB）
- 转换脚本：`console/tools/convert_x2.py`（STL→glb+joint_tree.json）
- 输出：`console/src/assets/models/x2_model.glb`（30.7MB）+ `x2_joints.json`（36KB）

### 11.2 渲染方案

- 前端直接加载 45 个 STL（Three.js STLLoader）
- 按 URDF 关节树逐层摆放（toThree 坐标转换）
- `mergeVertices` + `computeVertexNormals` 平滑表面
- MSAA + 高 pixelRatio 抗锯齿
- `<keep-alive>` 缓存页面不重载

### 11.3 坐标转换

ROS (z-up) → Three.js (y-up)：
```typescript
function toThree(p) { return new Vector3(p[0], p[2], -p[1]) }
```
每个 mesh wrap 做局部旋转 `rotation.set(-PI/2, 0, 0)`

---

## 十二、相机

### 12.1 可用相机

| 相机 | Topic | QoS | 状态 |
|------|-------|-----|------|
| RGBD 前视 | `/.../rgbd_head_front/rgb_image/compressed` | RELIABLE 30Hz | ✅ |
| 后视 RGB | `/.../rgb_head_rear/...` | TRANSIENT_LOCAL 10Hz | ❌ 硬件未推流 |
| 双目 左/右 | `/.../stereo_head_front_*/...` | TRANSIENT_LOCAL 10Hz | ❌ 硬件未推流 |

### 12.2 rosbridge 图片解码

rosbridge 把 `uint8[]` 转成 base64 字符串，前端需解码：
```typescript
const binary = atob(msg.data)
const bytes = new Uint8Array(binary.length)
for (let i=0; i<binary.length; i++) bytes[i] = binary.charCodeAt(i)
```

---

## 十三、麦克风与语音

### 13.1 VAD 话题

`/agent/process_audio_output` — VAD 降噪后语音段：
- state 1：语音开始 → 开始攒 PCM
- state 2：处理中 → 继续攒（约 25Hz）
- state 3：语音结束 → 打包 → 可送 FunASR 转文字

### 13.2 原始麦克风

`/aima/hal/audio/capture` — 33Hz 持续推流，6 声道

---

## 十四、运动控制的坑

### 14.1 必须先注册输入源

```python
req = SetMcInputSource.Request()
req.action.value = 1001  # ADD
req.input_source.name = "web_ui"  # 或自定义名
req.input_source.priority = 40
req.input_source.timeout = 1000
```

不注册的话运动控制器直接忽略速度指令。

### 14.2 速度必须持续发送

机器人需要 50Hz 持续收到速度指令才动。单发一条没用。

### 14.3 数值类型

`McLocomotionVelocity` 的 forward_velocity 等字段断言必须是 `float`：
```python
msg.forward_velocity = float(fwd)  # JSON 里的 0 是 int，必须转
```

### 14.4 脚本等待不要用 time.sleep

`time.sleep()` 卡死整个 rclpy spin，定时器不回调。用 `spin_once` 循环替代。

---

## 十五、部署备忘

### 15.1 Orin 需安装

```bash
sudo apt install ros-humble-rosbridge-server tmux -y
pip install fastapi uvicorn websockets python-multipart
```

### 15.2 常见问题

| 问题 | 原因 | 解决 |
|------|------|------|
| WS 路由 404 | 未装 `websockets` | `pip install websockets` |
| 端口 9090 被占 | 旧 rosbridge 残留 | `kill -9 PID` 或 `pkill -f rosbridge` |
| WiFi 模式连不上 | IP 变了 | `hostname -I` 查新 IP，改连接面板 |
| 输入源注册 code=1 | 已存在同名输入源 | 先 DELETE(1003) 再 ADD(1001) |
| 页面刷新丢失连接 | localStorage 未存 | 自动重连已实现，检查心跳 |

---

## 十六、人脸识别方案（待实施）

- 部署 InsightFace buffalo_l 到 Orin
- 模型路径：`~/.insightface/models/buffalo_l/`（约 480MB）
- API：`GET /api/face/result`、`POST /api/face/register`
- 方案文档：`backend/face/方案.md`

## 十七、下一步计划

1. 人脸识别部署到 Orin + 控制台集成
2. VAD 语音 → FunASR 转文字 → 前端显示
3. 联系智元技术支持：X2 RL 策略、后视相机启停
4. 系统学 SDK：预设动作、键盘遥控、传感器采集
