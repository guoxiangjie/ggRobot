# 灵犀 X2 AimDK v1.0 API 参考文档

> 来源：`aimdk_v1.0/src/aimdk_msgs/interface/` · 共 62 个接口
> 最后更新：2026-06-26

---

## 通用类型

所有 Service/Topic 都会引用以下基础类型。

### 请求头 `RequestHeader`
```
builtin_interfaces/Time stamp   # 时间戳
```

### 响应头 `ResponseHeader`
```
builtin_interfaces/Time stamp   # 时间戳
int64 code                      # 0=成功，非0=失败
```

### 消息头 `MessageHeader`
```
builtin_interfaces/Time stamp       # 发布时间
string frame_id                     # 坐标系
uint32 sequence                     # 消息序号（递增）
builtin_interfaces/Time meas_stamp  # 测量时间
```

### 通用请求 `CommonRequest`
```
RequestHeader header
```

### 通用响应 `CommonResponse`
```
ResponseHeader header
CommonState status      # 状态码
string message          # 消息
```

### 通用任务响应 `CommonTaskResponse`
```
ResponseHeader header
uint64 task_id          # 任务ID
CommonState state       # 任务状态
```

### 通用状态 `CommonState`
| 值 | 含义 | | 值 | 含义 |
|----|------|---|----|------|
| 0 | UNKNOWN | | 5 | INVALID |
| 1 | SUCCESS | | 6 | IN_MANUAL |
| 2 | FAILURE | | 100 | NOT_READY |
| 3 | ABORTED | | 200 | PENDING |
| 4 | TIMEOUT | | 300 | CREATED |
| | | | 400 | RUNNING |

### 域控制器状态 `DomainErrorState`
| 值 | 含义 |
|----|------|
| 0x00 | 正常 |
| 0x01 | 阻尼模式 |
| 0x02 | 下电模式 |
| 0x03 | 下使能模式 |
| 0x04 | CAN通信断连 |

---

## 一、传感器 Topics（只读，订阅）

### 1.1 电池/电源 `/aima/hal/pmu/state` → `PmuState`

**QoS**: BEST_EFFORT, KEEP_LAST(1)

```
# === 电池 BMS ===
string bms_manufacturer             # 厂家
string bms_serial_number            # 序列号
string bms_hardware_version         # 硬件版本
string bms_software_version         # 软件版本
uint32 bms_status_bits              # 状态位（见下方 bit 定义）
uint16 battery_balance_line_resistance  # 均衡线电阻(mΩ)
float64 battery_pack_voltage        # 电池包电压(V)
float64 battery_current             # 电流(A, 充电正/放电负)
float64 battery_output_power        # 输出功率(W)
float64 battery_temperature         # 温度(℃)
uint32 battery_remaining_capacity   # 剩余容量(mAh)
uint8 battery_remaining_capacity_percentage  # 电量百分比
uint16 battery_cycle_count          # 循环次数
uint32 battery_cycle_total_capacity # 累计充放电(Ah)

# === 电源管理 PMU ===
string pmu_software_version
string pmu_hardware_version
uint32 pmu_bool_status              # 状态位
float64 head_power_current          # 头部电流(A)
float64 output_48v_current          # 48V输出电流(A)
float64 rk3588_current              # RK3588电流(A)
float64 output_12v_current          # 12V输出电流(A)
float64 bus_48v_current             # 48V总线电流(A)
float64 orin_current                # ORIN电流(A)
float64 bus_48v_pmos_voltage        # 48V PMOS电压(V)
float64 battery_voltage             # 电池电压(V)
float64 fan_voltage                 # 风扇电压(V)
float64 output_12v_voltage          # 12V输出电压(V)
float64 output_48v_voltage          # 48V输出电压(V)
float64 bus_48v_voltage             # 48V总线电压(V)
float64 head_power_voltage          # 头部电压(V)
float64 orin_voltage                # ORIN电压(V)
float64 rk3588_voltage              # RK3588电压(V)
float64 fan_speed                   # 风扇转速(RPM)
uint8 fan_pecentage                 # 风扇百分比
float64 pmu_temperature             # PMU温度(℃)
```

**BMS 状态位 (bms_status_bits)**：
| bit | 含义 | bit | 含义 |
|-----|------|-----|------|
| 0 | 充电标志 | 11 | 放电超温 |
| 1 | 充电过流 | 12 | 充电超温 |
| 2 | 放电标志 | 13 | 放电低温 |
| 3 | 放电过流 | 14 | 充电低温 |
| 4 | 短路 | 16 | 电芯压差过大 |
| 6 | 电芯过压 | 17 | MOSFET禁充 |
| 7 | 电芯欠压 | 18 | MOSFET禁放 |
| 8 | 总压过压 | 19 | MOSFET超温 |
| 9 | 总压欠压 | 20 | 均衡线电阻过大 |
| 10 | 电芯开路 | | |

---

### 1.2 关节状态 `/aima/hal/joint/{arm,leg,waist,head}/state` → `JointStateArray`

**QoS**: BEST_EFFORT · 手臂1kHz, 腿部1kHz, 腰部1kHz, 头部1kHz

```
MessageHeader header
DomainErrorState state           # 域控制器状态
JointState[] joints              # 关节数组
```

**JointState**：
```
string name             # 关节名
float64 position        # 位置(rad)
float64 velocity        # 速度(rad/s)
float64 effort          # 力矩(N·m)
uint16 error_code       # 错误码
```

**关节名称列表**（29个关节）：

| 区域 | 关节名 | 区域 | 关节名 |
|------|--------|------|--------|
| 左腿 | left_hip_pitch_joint | 右腿 | right_hip_pitch_joint |
| | left_hip_roll_joint | | right_hip_roll_joint |
| | left_hip_yaw_joint | | right_hip_yaw_joint |
| | left_knee_joint | | right_knee_joint |
| | left_ankle_pitch_joint | | right_ankle_pitch_joint |
| | left_ankle_roll_joint | | right_ankle_roll_joint |
| 腰部 | waist_yaw_joint | 头部 | head_yaw_joint |
| | waist_pitch_joint | | head_pitch_joint |
| | waist_roll_joint | | |
| 左臂 | left_shoulder_pitch_joint | 右臂 | right_shoulder_pitch_joint |
| | left_shoulder_roll_joint | | right_shoulder_roll_joint |
| | left_shoulder_yaw_joint | | right_shoulder_yaw_joint |
| | left_elbow_joint | | right_elbow_joint |
| | left_wrist_yaw_joint | | right_wrist_yaw_joint |
| | left_wrist_pitch_joint | | right_wrist_pitch_joint |
| | left_wrist_roll_joint | | right_wrist_roll_joint |

---

### 1.3 IMU `/aima/hal/imu/{torso,chest}/state` → `sensor_msgs/Imu`

**QoS**: BEST_EFFORT · 躯干500Hz, 胸腔500Hz

标准 ROS2 `sensor_msgs/Imu` 类型：
```
Header header
geometry_msgs/Quaternion orientation
float64[9] orientation_covariance
geometry_msgs/Vector3 angular_velocity
float64[9] angular_velocity_covariance
geometry_msgs/Vector3 linear_acceleration
float64[9] linear_acceleration_covariance
```

---

### 1.4 头部触摸 `/aima/hal/sensor/touch_head` → `TouchState`

**QoS**: BEST_EFFORT

```
MessageHeader header
uint8 event_type            # 触摸事件类型
uint32[8] data              # 8通道原始值
uint32[8] threshold         # 8通道阈值
bool[8] is_touched          # 8通道触摸状态
```

**event_type**：
| 值 | 含义 | 值 | 含义 |
|----|------|----|------|
| 0 | 未知 | 4 | 单击 |
| 1 | 空闲 | 5 | 双击 |
| 2 | 触摸 | 6 | 三击 |
| 3 | 滑动 | | |

---

### 1.5 相机 Topics

| Topic | 类型 | 频率 |
|-------|------|------|
| `/aima/hal/sensor/rgbd_head_front/rgb_image` | `sensor_msgs/Image` | 30Hz |
| `/aima/hal/sensor/rgbd_head_front/depth_image` | `sensor_msgs/Image` | 30Hz |
| `/aima/hal/sensor/rgb_head_rear/rgb_image` | `sensor_msgs/Image` | - |
| `/aima/hal/sensor/stereo_head_front_left/rgb_image` | `sensor_msgs/Image` | - |
| `/aima/hal/sensor/stereo_head_front_right/rgb_image` | `sensor_msgs/Image` | - |

**QoS**: 全部 `qos_profile_sensor_data` (BEST_EFFORT)

> **注意**：只有 RGBD 前视默认有数据，双目相机可能未启动。

---

### 1.6 激光雷达 `/aima/hal/sensor/lidar_chest_front/lidar_pointcloud` → `sensor_msgs/PointCloud2`

---

## 二、交互 Services（TTS/音频/视频/表情）

### 2.1 语音播报 `/aimdk_5Fmsgs/srv/PlayTts`

**请求**：
```
CommonRequest header             # header.header.stamp = 当前时间
PlayTtsRequest tts_req
  string text                    # 播报文本（必填）
  TtsPriorityLevel priority_level # 优先级（必填，默认 INTERACTION_L6）
  uint32 priority_weight         # 优先级加权 0-99（可选）
  string domain                  # 调用方标识（必填）
  string trace_id                # 请求ID（可选）
  bool is_interrupted            # 打断同级播报（必填）
```

**响应**：
```
CommonResponse header             # header.code: 0=成功
PlayTtsResponse tts_resp
  string text                     # 播报文本回传
  TtsPriorityLevel priority_level
  uint32 priority_weight
  string domain
  string trace_id
  bool is_success                 # 是否成功
  string error_message            # 错误信息
  uint32 estimated_duration       # 预计耗时(ms)
```

**优先级 TtsPriorityLevel**：
| 值 | 层级 | 说明 |
|----|------|------|
| 0x00 | UNKNOWN | 未知 |
| 0x01 | BACKGROUND_L1 | 后台服务层 |
| 0x02 | SERVICE_L2 | 主动服务层 |
| 0x04 | MISSION_L4 | 任务执行层 |
| 0x06 | INTERACTION_L6 | **交互相应层（默认）** |
| 0x07 | SYSTEM_L7 | 系统提示层 |
| 0x08 | WARNING_L8 | 危险预警层 |
| 0x0a | SAFETY_L10 | 生命安全层 |

> **跨板重试**：调用时需 8 次重试，每次 timeout 0.25s。

---

### 2.2 播放音频文件 `/aimdk_5Fmsgs/srv/PlayAudioFile`

**请求**：
```
CommonRequest request
AudioFile file
  string pkg_name         # 调用方（必填）
  string file_name        # 文件名（必填）
  string file_path        # 路径（必填，不设使用系统默认）
  AudioInfo info          # 音频格式
  uint32 priority         # 优先级 1-10（必填，默认6）
  uint32 priority_weight  # 加权 1-100（可选）
builtin_interfaces/Time play_stamps  # 指定时刻播放（可选）
```

**响应**：
```
CommonResponse reponse
```

---

### 2.3 播放视频 `/face_ui_proxy/play_video` → `PlayVideo`

> 视频文件必须先上传到 PC3。

**请求**：
```
CommonRequest header
string video_path       # 视频路径
uint8 mode              # 1=播放一次, 2=循环播放
int32 priority          # 优先级
```

**响应**：
```
CommonResponse header
bool success
string message
```

---

### 2.4 播放表情 `/aimdk_5Fmsgs/srv/PlayEmoji`

**请求**：
```
CommonRequest header
uint8 emotion_id        # 表情ID
uint8 mode              # 1=播放一次, 2=循环
int32 priority          # 优先级
```

**表情 emotion_id**：
| ID | 表情 | ID | 表情 | ID | 表情 |
|----|------|----|------|----|------|
| 1 | 眨眼 | 40 | 闭眼 | 130 | 疑惑 |
| 10-11 | 平静 | 50 | 睁眼 | 140 | 震惊 |
| 20 | 游戏 | 60 | 无聊 | 150 | 撒娇 |
| 30-33 | 卖萌 | 70 | 异常 | 160 | 严肃 |
| | | 80 | 睡着 | 170 | 思考 |
| | | 90 | 快乐 | 180 | 愤怒 |
| | | 100-101 | 加倍开心 | 190 | 加倍愤怒 |
| | | 110 | 悲伤 | 200-210 | 崇拜 |
| | | 120 | 同情 | 220 | 充电 |

**响应**：
```
CommonResponse header
bool success
string message
```

---

### 2.5 麦克风/音频控制

| Service | 功能 |
|---------|------|
| `/aimdk_5Fmsgs/srv/SetMicSourceRequest` | 设置麦克风音源 |
| `/aimdk_5Fmsgs/srv/GetMicSourceRequest` | 查询当前音源 |
| `/aimdk_5Fmsgs/srv/SetVolume` | 设置音量 |
| `/aimdk_5Fmsgs/srv/GetVolume` | 查询音量 |
| `/aimdk_5Fmsgs/srv/SetMute` | 设置静音 |
| `/aimdk_5Fmsgs/srv/GetMute` | 查询静音状态 |
| `/aimdk_5Fmsgs/srv/RequestAudioFocus` | 请求音频焦点 |
| `/aimdk_5Fmsgs/srv/AbandonAudioFocus` | 释放音频焦点 |

---

## 三、运动控制 Services & Topics

### 3.1 速度控制 `/aima/mc/locomotion/velocity` → `McLocomotionVelocity`

**发布**（Topic）：
```
MessageHeader header
string source               # 输入源标识 "web_ui"
float64 forward_velocity    # 前后 m/s (+前 -后)
float64 lateral_velocity    # 左右 m/s (+左 -右)
float64 angular_velocity    # 旋转 rad/s (+左转 -右转)
```

**QoS**: RELIABLE, KEEP_LAST(10)

> **安全**：松开按键时应立即发布全零速度。

---

### 3.2 预设动作 `/aimdk_5Fmsgs/srv/SetMcPresetMotion`

**请求**：
```
RequestHeader header
McControlArea area          # 控制区域
  int32 value               # 0=NONE 1=左手 2=右手 4=头部 8=腰部
McPresetMotion motion       # 预设动作
  int32 value               # 动作ID
bool interrupt              # 是否打断前一个动作
string ani_path             # 自定义动作地址
uint64 play_timestamp       # 运行时间(ms UNIX), 0=立刻
```

**响应**：
```
CommonTaskResponse response
  ResponseHeader header     # header.code: 0=成功
  uint64 task_id            # 任务ID
  CommonState state         # 1=SUCCESS 2=FAILURE 400=RUNNING
```

**动作 motion.value 完整枚举**：

| ID | 动作 | 分类 |
|----|------|------|
| 1001 | 抬手 RAISE_HAND | 基础 |
| 1002 | 挥手 WAVE_HAND | 基础 |
| 1003 | 握手 SHAKE_HAND | 基础 |
| 1004 | 飞吻 FLYING_KISS_HAND | 基础 |
| 1008 | 击掌 CLAP_HAND | 基础 |
| 1009 | 碰拳 CLIPFIST | 基础 |
| 1013 | 敬礼 SALUTE | 基础 |
| 2001 | 转身挥手 | 组合 |
| 3001 | 鞠躬 INTERACTION_BOW | 交互 |
| 3002 | 点赞 INTERACTION_LIKE | 交互 |
| 3003 | 比YE INTERACTION_YE | 交互 |
| 3004 | 头顶比心 INTERACTION_SWEATHEART | 交互 |
| 3006 | 悲伤 INTERACTION_SAD | 交互 |
| 3007 | 轻轻挥手 INTERACTION_LIGHTWAVE | 交互 |
| 3008 | 拥抱 INTERACTION_HUG | 交互 |
| 3009 | 胸前打叉 INTERACTION_HANDX | 交互 |
| 3010 | 胸前挥手 INTERACTION_CHESTWAVE | 交互 |
| 3011 | 加油 INTERACTION_CHEER | 交互 |
| 3012 | 低空飞吻 INTERACTION_BLOWKISS | 交互 |
| 3013 | 巴斯舞1 INTERACTION_BASSDANCE1 | 交互 |
| 3014 | 巴斯舞2 INTERACTION_BASSDANCE2 | 交互 |
| 3015 | 击掌 HITCLAP | 交互 |
| 3016 | 说话手势 INTERACTION_SPEAK | 交互 |
| 3018 | 拍照姿势 INTERACTION_PHOTOPOSTURE | 交互 |
| 3019 | 三连拍 INTERACTION_PHOTOTRIPPLEPOSTURE | 交互 |
| 4001 | 点头 POINT_HEAD | 头部 |
| 4002 | 摇头 SHAKE_HEAD | 头部 |

---

### 3.3 运动模式控制 `/aimdk_5Fmsgs/srv/SetMcAction`

**请求**：
```
RequestHeader header
string source               # 输入源
McActionCommand command
  McAction action
    int32 value             # 运动模式ID
  string action_desc        # 描述
```

**运动模式 McAction.value**：
| 值 | 模式 |
|----|------|
| 1 | PASSIVE_DEFAULT 被动 |
| 2 | SOFT_EMERGENCY_STOP 软急停 |
| 3 | DAMPING_DEFAULT 阻尼 |
| 4 | ZERO_TORQUE_DEFAULT 零力矩 |
| 100 | JOINT_DEFAULT 位控站立 |
| 101 | JOINT_FREEZE 关节锁定 |
| 200 | STAND_DEFAULT 力控站立 |
| 201 | STAND_BODY_CONTROL 站立+身体运动 |
| 300 | LOCOMOTION_DEFAULT 行走 |
| 301 | RUN_DEFAULT 跑步 |
| 302 | LOCOMOTION_STEP 越野 |
| 400 | VR_REMOTE_CONTROLLER VR遥操 |
| 2000 | SIT_DOWN_DEFAULT 坐下 |
| 2002 | CROUCH_DOWN_DEFAULT 蹲下 |
| 2004 | LIE_DOWN_DEFAULT 躺倒 |
| 2005 | STAND_UP_DEFAULT 平躺站起 |
| 2006 | ASCEND_STAIRS 上楼梯 |
| 2008 | DESCEND_STAIRS 下楼梯 |

**响应**：
```
CommonResponse response
```

---

### 3.4 查询运动模式 `/aimdk_5Fmsgs/srv/GetMcAction`

**请求**：
```
CommonRequest request
```

**响应**：
```
ResponseHeader header
McActionInfo info
  McAction current_action       # 当前模式
  string action_desc            # 描述
  McActionStatus status         # 状态: 0=IDLE 100=RUNNING 200=TRANSITION
```

---

### 3.5 输入源管理

**设置输入源** `/aimdk_5Fmsgs/srv/SetMcInputSource`：
```
CommonRequest request
McInputAction action            # 1001=ADD 1002=MODIFY 1003=DELETE 2001=ENABLE 2002=DISABLE
McInputSource input_source
  string name                   # 输入源名(rc/vr/app_proxy/interaction/pnc)
  int32 priority                # 优先级 0-100
  int32 timeout                 # 超时(ms), 默认1000
---
CommonTaskResponse response
```

**查询输入源** `/aimdk_5Fmsgs/srv/GetCurrentInputSource`：
```
CommonRequest request
---
CommonTaskResponse response
McInputSource input_source
```

---

## 四、关节直接控制 Topic

### 4.1 关节指令 `/aima/hal/joint/{arm,leg,waist,head}/command` → `JointCommandArray`

**QoS**: RELIABLE

```
MessageHeader header
JointCommand[] joints
  string name             # 关节名
  float64 position        # 目标位置(rad)
  float64 velocity        # 目标速度(rad/s)
  float64 effort          # 前馈力矩(N·m)
  float64 stiffness       # 刚度 Kp
  float64 damping         # 阻尼 Kd
```

> **注意**：直接关节控制需配合 Ruckig 轨迹规划器（参考 SDK `motocontrol.py` 示例）。

---

## 五、SLAM / 导航

### 5.1 建图指令 `/integrated_command` → `std_msgs/String`

| 指令 | 说明 |
|------|------|
| `start_mapping` | 开始建图 |
| `stop_mapping:{name}` | 停止并保存，name=地图名 |

### 5.2 获取地图 `/aimdk_5Fmsgs/srv/GetStoredMapByName`

**请求**：
```
std_msgs/Header header
string map_name             # 地图名
```

**响应**：
```
uint64 code                 # 0=成功
std_msgs/Header header
nav_msgs/MapMetaData map_info  # 长宽、分辨率
uint64 map_version
string map_path             # PNG路径
int8[] data                 # 地图数据
NaviPoint[] navi_points     # 导航点
QRPoint[] qr_points         # 二维码点
HRPoint[] hr_points         # 高精度点
Path[] paths                # 路径
Region[] regions            # 区域（虚拟墙）
uint64 map_id
```

### 5.3 相关 Topics
| Topic | 类型 | 说明 |
|-------|------|------|
| `/relocalization_pose` | - | 重定位位姿 |
| `/slam/lidar_odom` | - | 激光里程计 |

---

## 六、系统管理

### 6.1 查询系统状态 `/aimdk_5Fmsgs/srv/GetSystemState`

**请求**：`CommonRequest header`

**响应**：
```
CommonResponse header
string cur_state            # 当前状态名
SystemStatus curr_status
  uint8 value               # 0=INIT 1=READY 2=MOVE 3=ROLLBACK 4=FALLBACK 5=FALLBACK_MOVE
```

| 状态值 | 含义 | 可执行业务 |
|--------|------|-----------|
| 0 IN_INITIAL | 起始态 | 否 |
| 1 IN_READY | 就绪态 | 是 |
| 2 IN_MOVE | 迁移态 | 否 |
| 3 IN_ROLLBACK | 回滚态 | 否 |
| 4 IN_FALLBACK | 异常态 | 否(接收迁移) |
| 5 IN_FALLBACK_MOVE | 异常迁移 | 否 |

### 6.2 迁移系统状态 `/aimdk_5Fmsgs/srv/MigrateSystemState`

**请求**：
```
CommonRequest header
string state            # 目标状态名
```

**响应**：`CommonResponse header`

---

## 七、其他接口

### 7.1 手部控制

| Service/Topic | 功能 |
|---------------|------|
| `/aimdk_5Fmsgs/srv/GetHandType` | 查询手型（五指/灵巧手） |
| `/aimdk_5Fmsgs/srv/GetAllJointState` | 查询所有关节状态 |
| `/aima/hal/joint/hand/command` | 手部关节指令（Topic） |
| `/aima/hal/joint/hand/state` | 手部关节状态（Topic） |

### 7.2 LED 控制

| Service | 功能 |
|---------|------|
| `/aimdk_5Fmsgs/srv/SetPmuLed` | 设置PMU指示灯 |

### 7.3 资源管理

| Service | 功能 |
|---------|------|
| `/aimdk_5Fmsgs/srv/GetRobotResources` | 查询机器人资源列表 |
| `/aimdk_5Fmsgs/srv/ExecuteActionResource` | 执行动作资源 |
| `/aimdk_5Fmsgs/srv/SetAgentPropertiesRequest` | 设置Agent属性 |

### 7.4 音频 Topics（只读）

| Topic | 类型 | 说明 |
|-------|------|------|
| `/aima/hal/audio/capture` | AudioCapture | 音频采集 |
| `/aima/hal/audio/playback` | AudioPlayback | 音频播放状态 |
| `/aima/hal/audio/play_state` | PlayStateChange | 播放状态变化 |
| `/aima/hal/audio/focus_response` | FocusResponse | 焦点响应 |
| `/agent/process_audio_output` | ProcessedAudioOutput | 处理后音频输出 |

### 7.5 交互 Topics

| Topic | 类型 | 说明 |
|-------|------|------|
| `/face_ui_proxy/status` | FaceEmojiStatus | 表情状态 |

---

## 附：QoS 配置速查

| 场景 | 配置 | 代码 |
|------|------|------|
| 传感器订阅 | BEST_EFFORT, KEEP_LAST(1) | `qos_profile_sensor_data` |
| 控制指令发布 | RELIABLE, KEEP_LAST(10) | 手动配置 |
| 跨板 Service 调用 | 默认 | 需 8 次重试，timeout 0.25s |

```python
# 传感器 QoS（推荐写法）
from rclpy.qos import qos_profile_sensor_data
self.create_subscription(MsgType, topic, callback, qos_profile_sensor_data)

# 控制指令 QoS
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
QoSProfile(
    reliability=ReliabilityPolicy.RELIABLE,
    history=HistoryPolicy.KEEP_LAST,
    depth=10,
    durability=DurabilityPolicy.VOLATILE
)

# 跨板 Service 重试模板
for i in range(8):
    req.header.header.stamp = self.get_clock().now().to_msg()
    future = client.call_async(req)
    rclpy.spin_until_future_complete(self, future, timeout_sec=0.25)
    if future.done(): break
```
