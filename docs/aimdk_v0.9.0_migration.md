# AimDK_X2 v0.9.0 / v1.0.0 迁移与变更指南

> 基于官方在线文档 https://x2-aimdk.agibot.com/zh-cn/latest/ 系统爬取整理（2026-07）。
> 文档站点 `latest` 当前指向 **v0.9.0**，部分页面已开始显示 **v1.0.0**（过渡期）。本指南以 v0.9.0 为基准，v1.0.0 新增项单独标注。
> 对照项目代码：`gg_robot/node.py`、`gg_robot/task/steps.py`、`web/` 前端。

---

## 一、Changelog 时间线

### v1.0.0（latest 部分页面已显示，未正式发版号）
**新增**：灵创动作（GetRobotResources / ExecuteActionResource）、SLAM（选装）、麦克风切换与原始流式音频、T2.1 灵巧手触觉、进入开发者模式服务。

### v0.9.0（2026-02-03，Beta2.0）
- **【变更】** `SetMcAction` 请求新增 `source` 域标记输入源
- **【变更】** `JointStateArray` 新增 `DomainErrorState state`（关节组异常：1阻尼/2下电/3下使能/4通信断连）
- **【变更】** `TtsPriorityLevel` 新增 `SYSTEM_L7`(=7)
- **【变更】** `PlayVideoGroup` 恢复上线（`PlayEmojiGroup` 仍下线）
- **【变更】** VAD（`/agent/process_audio_output`）需唤醒词激活

### v0.8.2（2025-12-10，Beta1.2）
- **【红线】** PC1(10.0.1.40) 正式禁止作为二开程序运行环境
- **【破坏】** `SetMcAction`/`GetMcAction` **不再用数字 ID**，改用 `action_desc` 字符串传模式名
- **【废弃】** 头部关节 pitch 自由度暂时下线（只剩 yaw）

### v0.8.1（2025-11-11，Beta1.1）
- **【新增】** 在线 SDK 文档；灯带控制 `/aimdk_5Fmsgs/srv/LedStripCommand`
- **【废弃】** **交互相机所有接口**（资源占用过高）：
  - `/aima/hal/sensor/rgb_head_front_center/camera_info`
  - `/aima/hal/sensor/rgb_head_front_center/rgb_image`
  - `/aima/hal/sensor/rgb_head_front_center/rgb_image/compressed`
- **【废弃】** 头部 IMU `/aima/hal/imu/head/state`（用深度相机 IMU 替代）
- **【废弃】** 播放列表 `PlayEmojiGroup`、`PlayVideoGroup`（v0.9.0 中 PlayVideoGroup 已恢复）

### v0.8.0（2025-11-06，Beta1.0）
- **【新增】** 底层关节电机控制（`/aima/hal/joint/{head,arm,waist,leg}/{command,state}`）
- **【新增】** 供电状态监控（PmuState 完整 BMS）、头部触摸（`/aima/hal/sensor/touch_head`）、系统音量、IMU 开放（胸/胯）
- **【破坏】** 预设动作扩充与**编码变动**；表情 `priority` uint8→int32
- **【破坏】** 消息改名：`PlayTts` 字段 `tty_xx→tts_xx`；`PlayAudioFile→PlayMediaFile`（结构扁平化）；`SetMcInputSource`/`GetCurrentInputSource` 加 `McInputSource.msg` 包裹层
- **【废弃】** 体态控制 `McBodyPose`；可用运动模式查询 `GetMcAvailableActions`（→ 必须硬编码 5 个 action_desc）

---

## 二、对项目代码的影响（按严重程度）

### 🔴 P0-1：相机用了已下线的 topic（`node.py:123`）
项目把 `rgb_head_front_center` 列在相机列表**首位**，而该接口 v0.8.1 已下线。`_auto_select_camera` 会优先尝试一个永不存在的 topic，可能导致相机无画面。

**v0.9.0 可用相机 topic（5.4.1）：**

| 相机 | compressed topic | QoS | 帧率 |
|------|------------------|-----|------|
| RGBD 前视（推荐） | `/aima/hal/sensor/rgbd_head_front/rgb_image/compressed` | **RELIABLE** | 10Hz |
| 后视 RGB | `/aima/hal/sensor/rgb_head_rear/rgb_image/compressed` | TRANSIENT_LOCAL | 10Hz |
| 双目左 | `/aima/hal/sensor/stereo_head_front_left/rgb_image/compressed` | TRANSIENT_LOCAL | 10Hz |
| 双目右 | `/aima/hal/sensor/stereo_head_front_right/rgb_image/compressed` | TRANSIENT_LOCAL | 10Hz |

RGBD 还提供 `depth_image`、`depth_pointcloud`、`rgb_camera_info`、`depth_camera_info`、`imu`(200Hz)。

**改法**：删除 `rgb_front_center` 条目；默认改 `rgbd_front`；QoS 按来源分组（RGBD=RELIABLE，其余=TRANSIENT_LOCAL）。

### 🔴 P0-2：SetMcAction 用数字 ID（`node.py:281,286,580`）
- `stop_motion()` 调 `_do_mode(200)`（数字 200）
- `_do_mode` 里 `req.command.action_desc = "web_ui"`（**action_desc 被错填成来源名，应是模式名**）
- v0.8.2 起数字 ID 不再对二开开放

**v0.9.0 合法的 5 个 `action_desc`：**

| action_desc | 中文 | 用途 |
|-------------|------|------|
| `PASSIVE_DEFAULT` | 零力矩 | 启动/维护/软急停 |
| `DAMPING_DEFAULT` | 阻尼 | 安全移动 |
| `JOINT_DEFAULT` | 位控站立 | 精确关节位置 |
| `STAND_DEFAULT` | 稳定站立（力控） | 动作就绪 |
| `LOCOMOTION_DEFAULT` | 走跑 | 日常移动（走/跑自动切换） |

**改法**：`_do_mode(action_desc: str)`，填 `req.command.action_desc = action_desc`，新增 `req.source = "web_ui"`。`stop_motion()` 改 `_do_mode("STAND_DEFAULT")`。

### 🔴 P0-3：预设动作 area 编码过时（CLAUDE.md + `node.py:689`）
CLAUDE.md 写 `area: 1左手/2右手/4头部/8腰部` 是 **v0.7.x 位掩码**，已失效。示例 `_do_motion(2,3004)` 比心用的 `3004` 在新表不存在。

**新 area 语义：1=左臂 / 2=右臂 / 3=双臂 / 11=全身（腰腿）。** 头部/腰部不再是独立 area。

**新预设动作表（部分，motion+area 联合）：**
| 动作 | motion | area |
|------|--------|------|
| 左/右手挥手 | 1002 | 1 或 2 |
| 举手 | 1001 | 1 或 2 |
| 握手 | 1003 | 2 |
| 飞吻 | 1004 | — |
| 比心 | 1007 | 1/2/3 |
| 击掌 | 1008 | — |
| 双手平举 | 1010 | 3 |
| 敬礼 | 1013 | — |
| 鞠躬 | 3001 | 11 |
| 拥抱 | 3008 | 11 |
| 动感光波 | 3007 | 11 |
| 双手打叉 | 3009 | 11 |
| 加油 | 3011 | 11 |
| 挠头 | 3024 | 11 |
| 鼓掌 | 3017 | 11 |
| 拜拜 | 3031 | 11 |

> 所有预设动作执行前机器人必须处于 `STAND_DEFAULT`。

### 🟠 P1-1：TTS 完成检测依赖不存在的话题（`node.py:109,162,242`）
项目订阅 `/aima/hal/audio/play_state`（PlayStateChange）等 `state==STOPED`——**该话题在 v0.9.0 文档 5.2.1 中不存在**，官方 Python TTS 示例也没有任何完成回调。

**可靠替代：`PlayTtsResponse.estimated_duration`（预计耗时，毫秒）**——同步返回，按此值 sleep 即可。

```python
# _do_tts 返回值应带上 estimated_duration
resp = ... # PlayTts.Response
dur_ms = resp.tts_resp.estimated_duration
time.sleep(dur_ms / 1000 + 0.3)  # +300ms 余量
```

> 注：实机上 `/aima/hal/audio/play_state` 可能仍存在（早期版本或未文档化）。建议先用 `ros2 topic list | grep play_state` 实测；若不存在，改用 estimated_duration。

### 🟠 P1-2：表情/视频 service 路径不一致
- 文档 5.2.2 表格写 `/aimdk_5Fmsgs/srv/PlayEmoji`、`/aimdk_5Fmsgs/srv/PlayVideo`
- Python 示例代码用 `/face_ui_proxy/play_emoji`、`/face_ui_proxy/play_video`
- 表情**状态话题**确定是 `/face_ui_proxy/status`（face_ui 命名空间）

**待实机 `ros2 service list` 确认。** 若项目当前用 `/face_ui_proxy/*`（与示例一致），可能反而是对的。

### 🟠 P1-3：关节订阅消息类型（`node.py:158`）
项目订阅 `/aima/hal/joint/arm/state` 用 `sensor_msgs/JointState`，文档定义是 **`aimdk_msgs/msg/JointStateArray`**（v0.9.0 还含 `DomainErrorState`）。类型不匹配会完全无数据。

**待实机 `ros2 topic info /aima/hal/joint/arm/state` 确认真实类型。**

### 🟡 P2：QoS 细化
- CLAUDE.md 笼统说"传感器用 BEST_EFFORT"——v0.9.0 已细化：
  - RGBD 所有话题 → **RELIABLE**
  - 双目/后视/Lidar/IMU → TRANSIENT_LOCAL
  - `camera_info`（latched，只发一帧）必须 RELIABLE + TRANSIENT_LOCAL，否则收不到
- 走跑启动门限：forward≥0.09、lateral≥0.60、angular≥0.03（低于门限不迈步）；示例代码里 forward/lateral 取 0 或 ±(0.2~1.0)、angular 0 或 ±(0.1~1.0)

### 🟡 P2：输入源优先级与系统 pnc 冲突
项目注册 `web_ui` priority=40，与系统内置 `pnc`(40) **同级**。同优先级"先到先得"，可能被抢占。官方建议二开用 20-100 避开系统源（rc=80/vr=70/app=60/interaction=50/pnc=40）。建议改 30 或确认冲突策略。

---

## 三、Service / Topic 真实路径速查（从 Python 示例提取）

| 接口 | 真实 path | 消息类型 |
|------|-----------|----------|
| GetMcAction | `/aimdk_5Fmsgs/srv/GetMcAction` | aimdk_msgs/srv/GetMcAction |
| SetMcAction | `/aimdk_5Fmsgs/srv/SetMcAction` | aimdk_msgs/srv/SetMcAction |
| SetMcPresetMotion | `/aimdk_5Fmsgs/srv/SetMcPresetMotion` | aimdk_msgs/srv/SetMcPresetMotion |
| SetMcInputSource | `/aimdk_5Fmsgs/srv/SetMcInputSource` | aimdk_msgs/srv/SetMcInputSource |
| GetCurrentInputSource | `/aimdk_5Fmsgs/srv/GetCurrentInputSource` | aimdk_msgs/srv/GetCurrentInputSource |
| GetAllJointState | `/aimdk_5Fmsgs/srv/GetAllJointState` | aimdk_msgs/srv/GetAllJointState |
| GetHandType | `/aimdk_5Fmsgs/srv/GetHandType` | aimdk_msgs/srv/GetHandType |
| PlayTts | `/aimdk_5Fmsgs/srv/PlayTts` | aimdk_msgs/srv/PlayTts |
| PlayMediaFile | `/aimdk_5Fmsgs/srv/PlayMediaFile` | aimdk_msgs/srv/PlayMediaFile |
| GetVolume/SetVolume/GetMute/SetMute | `/aimdk_5Fmsgs/srv/*` | aimdk_msgs/srv/* |
| LedStripCommand | `/aimdk_5Fmsgs/srv/LedStripCommand` | aimdk_msgs/srv/LedStripCommand |
| PlayEmoji | `/face_ui_proxy/play_emoji`（示例）/ `/aimdk_5Fmsgs/srv/PlayEmoji`（文档表）⚠️待确认 | aimdk_msgs/srv/PlayEmoji |
| PlayVideo | `/face_ui_proxy/play_video`（示例）/ `/aimdk_5Fmsgs/srv/PlayVideo`（文档表）⚠️待确认 | aimdk_msgs/srv/PlayVideo |
| 走跑速度（topic） | `/aima/mc/locomotion/velocity` | aimdk_msgs/msg/McLocomotionVelocity |
| 关节控制（topic） | `/aima/hal/joint/{head,arm,waist,leg}/command` | aimdk_msgs/msg/JointCommandArray |
| 关节状态（topic） | `/aima/hal/joint/{head,arm,waist,leg}/state` | aimdk_msgs/msg/JointStateArray |
| 手部控制（topic） | `/aima/hal/joint/hand/command` | aimdk_msgs/msg/HandCommandArray |
| 表情状态（topic） | `/face_ui_proxy/status` | face_ui/FaceEmojiStatus |
| MIC/VAD（topic） | `/agent/process_audio_output` | aimdk_msgs/msg/ProcessedAudioOutput |
| 触摸（topic） | `/aima/hal/sensor/touch_head` | aimdk_msgs/msg/TouchState |
| PMU（topic） | `/aima/hal/pmu/state` | hal/PmuState（0.2Hz） |

> **命名规律**：`/aimdk_5Fmsgs/srv/<Name>` 是大多数控制/语音服务的真实路径（恰好等于 service type 标识）；face_ui 模块的表情/视频服务和状态在 `/face_ui_proxy/` 下；HAL 传感器/关节在 `/aima/hal/` 下。

## 四、Header 嵌套层级速查（项目已知坑，v0.9.0 确认未变）

| 服务 | stamp 写法 | 层级 |
|------|-----------|------|
| GetMcAction / GetCurrentInputSource / GetAllJointState | `req.request.header.stamp` | 两层（req.request = CommonRequest） |
| SetMcAction / SetMcPresetMotion | `req.header.stamp` | 单层（header = RequestHeader） |
| SetMcInputSource | `req.request.header.stamp` | 两层（req.request = RequestHeader） |
| PlayTts / PlayMediaFile / PlayVideo / PlayEmoji | `req.header.header.stamp` | 两层（req.header = MessageHeader/CommonRequest） |
| LedStripCommand | `req.request.header.stamp` | 两层 |

> 音量服务响应头字段官方拼写是 `reponse`（少个 s，已知笔误）。

## 五、表情完成检测（新能力，项目可接入）

订阅 `/face_ui_proxy/status`（FaceEmojiStatus, RELIABLE, 1Hz）：
- `status`: 0空闲 / 1开始 / 2运行中 / **3完成** / **4被停止**
- 1/3/4 是 edge 触发（只播报 1 次）
- 可仿照 TTS 的 `wait_tts_done` 实现 `wait_emoji_done`，判 `status==3`

表情 ID 完整表（1~220）：1眨眼/10-11平静眼/20平静游戏/30-33卖萌/40闭眼/50睁眼/60无聊/70异常/80睡着/90快乐/100-101狂喜/110悲伤/120同情/130疑惑/140震惊/150撒娇/160严肃/170思考/180愤怒/190加倍愤怒/200崇拜/210加倍崇拜/220充电。

## 六、TTS 优先级体系（v0.9.0 完整）

| 级别 | 值 | 场景 |
|------|----|------|
| SAFETY_L10 | 10 | 安全警告（不被打断）|
| WARNING_L8 | 8 | 危险提醒 |
| SYSTEM_L7 | 7 | 系统播报（v0.9.0 新增）|
| INTERACTION_L6 | 6 | **用户交互（项目推荐默认）** |
| MISSION_L4 | 4 | 任务执行 |
| SERVICE_L2 | 2 | 主动服务 |
| BACKGROUND_L1 | 1 | 后台 |

高优先级打断低优先级；同优先级看 `priority_weight`(0-99) + `is_interrupted`。

## 七、可接入的新能力

| 能力 | 接口 | 难度 | 备注 |
|------|------|------|------|
| 灯带控制 | `/aimdk_5Fmsgs/srv/LedStripCommand`（mode 0常亮/1呼吸/2闪烁/3流水 + RGB） | 低 | **响应慢~5s，重试特殊：4次×5s**（非8次×0.25s）|
| 表情完成检测 | `/face_ui_proxy/status` | 低 | 见第五节 |
| 触摸交互 | `/aima/hal/sensor/touch_head` | 低 | 100Hz，摸头触发 TTS/表情 |
| 关节精细控制 | `/aima/hal/joint/{head,arm,waist,leg}/command` | 高 | **必须先 `aima em stop-app mc`**，2ms 周期 |
| 末端执行器 | `/aima/hal/joint/hand/command` | 高 | 夹爪(OmniPicker,1维0-1)/灵巧手(OmniHand,10维rad)，**必须先停 mc** |
| PMU 增强 | `/aima/hal/pmu/state` | 低 | 解析 bms_status_bits 显示过流/过温/欠压告警 |
| 多 IMU | chest/torso/lidar/rgbd | 低 | 可融合显示 |

## 八、特殊过渡方案（§8）

### 8.1 关闭内置交互系统（释放音频流给自研 ASR）
```bash
# 切 only_voice 模式（禁用大模型，保留 VAD）
ros2 service call /aimdk_5Fmsgs/srv/SetAgentPropertiesRequest \
  aimdk_msgs/srv/SetAgentPropertiesRequest "{contents:{properties:[{key:{value:2}, value:'only_voice'}]}}"
aima em stop-app agent && aima em start-app agent
# 恢复：value 改 'normal' 再重启
```

### 8.2 McAction 废弃状态码（v0.7.x → v0.8+）
| v0.7.x 废弃码 | 替代 |
|---------------|------|
| ZERO_TORQUE_DEFAULT | PASSIVE_DEFAULT |
| SOFT_EMERGENCY_STOP | PASSIVE_DEFAULT / DAMPING_DEFAULT |
| JOINT_FREEZE | JOINT_DEFAULT / DAMPING_DEFAULT |
| STAND_BODY_CONTROL | STAND_DEFAULT |
| RUN_DEFAULT | LOCOMOTION_DEFAULT（走跑合一）|

> `GetMcAction` 响应里 `current_action`（枚举）已废弃，改读 `info.action_desc`。`McActionStatus.value` 现仅 100=运行中 / 200=切换中（IDLE=0 文档无定义）。

## 九、二次开发边界红线（§9）

1. **禁止改 Orin 系统环境**（OS/驱动/依赖库）
2. **禁止用 PC1(10.0.1.40) 跑二开程序**
3. 不建议改 DDS 配置 / kernel / 算法参数
4. 禁止非授权改硬件接口/供电/总线
5. 集成第三方库前建议咨询官方
6. 自定义功能以插件/独立进程实现，不覆盖官方核心组件
7. 异常先查指南或联系官方

## 十、迁移优先级清单

| 优先级 | 项 | 文件位置 |
|--------|----|---------|
| P0 | 删相机 `rgb_head_front_center`，默认改 `rgbd_front`，QoS 分组 | node.py:120-154 |
| P0 | `_do_mode` 改 action_desc 字符串 + source 字段 | node.py:570-584 |
| P0 | 预设动作 area/motion 编码迁移（1/2/3/11） | node.py:689 + 前端 MotionPanel |
| P1 | TTS 完成检测改用 estimated_duration（play_state 实测后定夺） | node.py:224-245 |
| P1 | 关节订阅消息类型实机确认 | node.py:158 |
| P1 | PlayEmoji/PlayVideo 路径实机确认 | node.py:91 |
| P2 | 输入源 priority 改 30（避开 pnc） | node.py:460-474 |
| P2 | 接入灯带/触摸/表情完成检测 | 新增 route |
