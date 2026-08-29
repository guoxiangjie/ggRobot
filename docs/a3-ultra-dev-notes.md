# A3-Ultra 二开速查（v3.2 文档研读结晶）

> 来源：https://open.agibot.com/docs/aimdk/a3-ultra/v3_2/dev_guide（18 页全量研读，2026-08）
> 用途：ggRobot 平台 A3 agent 接入开发参考。原始页面提取件在 /tmp/a3docs/（易失，重要结论已抄录本文）

## 一、硬件与网络（vs X2）

| 项 | A3-Ultra | X2 对照 |
|---|---|---|
| 三计算单元 | **MDU**（RK3588 运控 10.42.10.12，⛔禁部署程序）/ **HDU**（RK3588S2 头部交互 10.42.10.10，✅推荐部署）/ **ADU**（Thor 具身智能 10.42.10.11，✅可部署） | PC1 运控 ⛔ / PC2 Orin ✅ / PC3 交互 |
| OS | Ubuntu 24.04 + ROS2 **Jazzy**（Fast DDS，DOMAIN_ID=232） | 22.04 + Humble |
| 机器人规格 | 1.74m/60kg/51DoF；腰 3 / 颈 2 / 单臂 7 / 单手 10-20；双电池 1152Wh | — |
| 相机 | 双目交互/左右后鱼眼×3/胸 D457/腰 D415/腕 D405×2（8路+） | 头部 RGBD 前后 |
| 外接 | 头部 Type-C（连 HDU）、背部调试仓网口（10.42.10.x 网段） | — |

内网固定 IP：HDU=10.42.10.10、ADU=10.42.10.11、MDU=10.42.10.12。WiFi IP 由 AimMaster 查。

## 二、接口形态（核心差异！）

**底层是 AimRT（智元自研，对标 ROS2），二开两种入口：**

1. **HTTP JSON RPC**（低频控制）：`POST http://{IP}:{PORT}/rpc/aimdk.protocol.{Service}/{Method}`，JSON 出入参，无鉴权。服务端口按单元分布（下表）。
2. **ROS2 Topic**（高频数据）：Jazzy + **QoS BEST_EFFORT/depth10**；跑前 `source /agibot/software/v0/entry/env/env.sh`。多数业务消息封装为 `ros2_plugin_proto/msg/RosMsgWrapper`（`serialization_type=="pb"`，`b"".join(msg.data)` 后用 `aimdk.protocol_pb2.XXX.ParseFromString` 反序列化；需 `pip install prebuilt/a3_aimdk-*.whl` + `source prebuilt/ros2_plugin_proto_aarch64/.../local_setup.bash`）。

### RPC 服务分布表（接入必备）

| 单元 | 端口 | 服务 | 能力 |
|---|---|---|---|
| HDU .10 | 59301 | AgentControlService | 静默模式 Get/SetVoiceEnable、交互运行模式 Get/SetAgentPropertiesRequest（only_voice/voice_face/normal） |
| HDU .10 | 59301 | TTSService | PlayTTS / PlayMediaFile(pcm/wav) / GetAudioStatus(trace_id 查状态) / StopTTSTraceId |
| HDU .10 | 56666 | HalAudioService | 音量 Get/SetAudioVolume（**上限 70，超了烧扬声器**）、麦克风源 Get/SetMicSourceRequest(0内置/1外置)、PlayFile/StopPlay |
| HDU .10 | 51049 | ResourceService | 资源 CRUD/列表/迁入迁出（动作/表情/音频/技能/地图/创作作品） |
| MDU .12 | 56322 | MotionControlActionService | SetAction/GetAction/GetAvailableActions（状态机切换） |
| MDU .12 | 56444 | MotionCommandService | **SendMotionCommand**（动作播放：路径+时长+暂停/复位/循环） |
| MDU .12 | 50587 | HDSService | GetAlertList 分级告警（A2000003 急停拍下 等） |
| ADU .11 | 50807 | MappingService/LocalizationService | 建图 Start/Stop、地图列表/2D图/拓扑点、实时建图数据 |
| ADU .11 | 53176 | PncService | **导航全家桶**（见下） |
| MDU .12 | 50080(本机) | PM | stop_app/start_app（关 motion_player 用，仅 MDU 本机 127.0.0.1） |

### ROS2 Topic 速查

| 话题 | 方向 | 消息 | 说明 |
|---|---|---|---|
| /motion/control/locomotion_velocity | 发 | RosMsgWrapper | **比例系数 -1.0~1.0**（非 m/s！），仅 MOTION 态 |
| /motion/control/arm_joint_command | 发 | JointState | 14 关节位控；velocity/effort 必须置 0 否则运控 crash；需先关 motion_player |
| /motion/control/neck_joint_command | 发 | JointState | yaw±0.9/pitch±0.3；50Hz |
| /motion/control/hand_joint_command | 发 | JointState | 0-2000 抽象值（0 张开）；AgiHand/O10Hand |
| /motion/control/move_waist | 发 | RosMsgWrapper | pitch±0.5/roll±0.3/yaw±1.57/height-0.4~0 |
| /motion/control/arm_joint_state 等 *_state | 收 | JointState | arm 14 / neck 2 / hand |
| /interaction/tts_status | 收 | RosMsgWrapper | 播报状态推送（normal 模式才有） |
| /agent/process_audio_output/pb_...ProcessedAudioOutput | 收 | RosMsgWrapper→pb | 降噪 PCM 16k/16bit/mono + VAD 状态（同 X2 话题名！） |
| /agent/wakeup/pb_...WakeUpResult | 收 | RosMsgWrapper→pb | 唤醒词+置信度（only_voice 下可用） |
| /agent/vision/face_id/pb_...FaceIdResult | 收 | RosMsgWrapper→pb | 人脸识别（voice_face 模式） |
| /aima/bms/data/pb_...BmsStateChannel | 收 | RosMsgWrapper→pb | 双电池：mV/mA/0.1℃/mAh/百分比/充电态 |
| /hal_state/emergency/pb_...EmergencyStateChannel | 收 | RosMsgWrapper→pb | 有线/无线/软件急停+TOF 报警 |
| /skill/pilot/skill_status | 收 | RosMsgWrapper | core 状态（6=Avatar 9=数采 13=建图中）+电池+自主充电 |
| /skill/pilot/face/play | 发 | RosMsgWrapper | 表情播放（默认 iceoryx，要改 skillpilot.yaml 加 ros2 后端+重启） |
| /hal/xxx/rgb（8 路） | 收 | sensor_msgs/Image | 1920×1536 30FPS 原始 RGB |
| /hal/xxx/stream | 收 | foxglove CompressedVideo | H265 10FPS（数采模式 30） |
| /hal/neck_middle_livox_lidar/pointcloud | 收 | PointCloud2 | 颈部激光雷达 |

## 三、控制语义

**Action 状态机**（MDU 56322）：PASSIVE(默认)→DAMPING→PD_STAND(09)→**MOTION(05)**（行走/上肢）→SIT_DOWN/STAND_UP/LIE_DOWN/GET_UP/PACKAGE_*/AVARAR。SetAction 异步，用 GetAction 查完成。仅推荐力控态间程序切换。

**动作播放**（MDU 56444 SendMotionCommand）：
```json
{"motion_id": "/agibot/data/resources/default/motion/握手/woshou1_Skeleton0.mcap",
 "duration_ms": 10000, "cmd_end": true, "cmd_pause": false, "cmd_reset": false, "cmd_repeat": false}
```
动作清单 = ResourceService/GetResourceList(RESOURCE_TYPE_MOTION)，duration 字段自带时长(ms) —— **比 X2 强：有真实时长 + 暂停/复位/循环**。播放/暂停/停止同一接口切字段。

**舞蹈**：SkillPilotService/SkillPackage {command: Start/Pause/Stop, path}（周围 2m 无障碍）。

**TTS**（HDU 59301）：文本 ≤1024 字节；priority_level 固定 INTERACTION_L6；trace_id 自带 → GetAudioStatus 查 InQue/Playing/NOTInQue，或订阅 /interaction/tts_status。estimated_duration **无效**（X2 可用）。

**导航**（ADU 53176，**全开放**）：PlanningNaviToGoal/Pose2D（规划避障）、LinearNavi*（先转后直行）、DirectNavi*（边走边转）、PreciseNaviToGoal（0.1m 高精）；SpinTurn/MoveForward；ActionCancel/Pause/Resume/GetState。前置：重定位成功 + MC 切 MOTION + map_id 一致。task_id 自生成需保存。

**地图**（ADU 50807）：GetStoredMapNames/Get2DWholeMap(base64 png+分辨率+原点)/GetTopoMsgs(导航点世界坐标)/StartMapping(no_realtime_data=true)/StopMapping(SAVING_MAP 保存)/**GetRealtimeMapData**（实时建图：cur_pos + lidar_points 像素点 + trajectory + base64 png —— 官方直接给，比 X2 自解析点云省一层）。

**像素↔世界换算**：`px = origin_x + x*resolution; py = origin_y - y*resolution`（resolution 单位 cm/px）。

## 四、交互接管（only_voice）

- SetAgentPropertiesRequest {"2": "only_voice"} → **重启机器人生效**；恢复 normal 同接口
- 开机需联网 ≥2min 完成音频鉴权，之后可离线
- only_voice：/agent/process_audio_output（纯净人声 PCM，可直接 ASR）+ /agent/wakeup；voice_face 加 /agent/vision/face_id
- 外置麦 VAD 状态 bug：实际输出 01111…12，需手动 +1 补偿（内置麦正常）
- 自定义对话需占扬声器：RequestAudioFocus（priority 6）→ /audiohal/audio/playback 流式 PCM（audio_msgs，需 source prebuilt/audio_msgs_proto…）；或直接用 PlayTTS
- LinkSoul 云端模式：灵心平台 AgentSDK（在线场景优先）

## 五、部署与铁律（影响 agent 打包分发）

1. **⛔严禁 apt 安装卸载**（X2 的 deb+apt 免密链路直接作废）→ 部署=scp/rsync 到 **HDU** `/agibot/data/home/agi/Desktop/`（白名单目录，不会被磁盘清理）+ python venv（系统 python3）或 docker
2. ⛔ MDU 不部署任何程序（运控专用，资源竞争会摔机）
3. ⛔ 不改系统配置（kernel/挂载/模块配置）；skillpilot.yaml 改 ros2 后端属"可改但有风险"级（文档自己给出的操作，需重启机器人）
4. **RPC 频率硬约束**：状态类持续轮询 ≤0.2Hz、短时查询 ≤1Hz → 传感器一律走 Topic 推送，RPC 只做动作触发
5. 依赖：AimDK 开发包（AimDK-A3_ultra-V3.2-0815）prebuilt/ 下 a3_aimdk-*.whl + ros2_plugin_proto（aarch64）；ROS2 Jazzy
6. Docker 场景需 --ipc=host --net=host + uid 1001(agi) + 同一份 ros_dds_configuration.xml + DOMAIN_ID=232

## 六、对 ggRobot 平台的接入结论

| 平台能力 | A3 落地方式 | 备注 |
|---|---|---|
| agent 分发 | **新方案**：tar/rsync + venv（沿用 sudoers? A3 无 apt 免密需求，SSH 直传即可）+ 自启（user systemd 待实机验证，X2 同款坑可能重现） | deb 链路仅 X2 保留 |
| 控制 | agent 内 requests 直调 HTTP RPC（HDU 本机 + MDU/ADU 内网 IP），命令队列骨架复用 X2 的（跨线程模型不变） | 无需 ROS2 Service Client！rclpy 只剩订阅传感器 + 少量 topic 发布 |
| 遥控 | locomotion_velocity 比例制：前端 m/s ÷ 档位上限 = 比例；持续发送 + 全零停止沿用 | 不需注册输入源（X2 需） |
| 预设动作 | GetResourceList(MOTION) 动态拉取（name/duration/路径）→ 上报能力契约 | 时长精确，编排无需实测估时 |
| TTS 等播完 | trace_id + GetAudioStatus 轮询（≤1Hz）或 /interaction/tts_status topic | 比 X2 只能估时强 |
| 编排步骤 | tts/motion/velocity/wait/third 全可映射；**新增 nav 导航步骤**（A3 独有）| 契约 catalog 加 nav 类型 |
| 建图工作台 | MappingService RPC（实时建图数据自带点云+轨迹+底图） | MappingStudio 换数据源适配层 |
| 相机 | MVP 用 /rgb Image(30FPS) → agent 转 JPEG → 复用 WS 4B+帧管道（1920×1536 降采样）；H265 流后续 WebCodecs | H265 Electron 兼容差，先绕开 |
| 语音转写 | only_voice + /agent/process_audio_output（与 X2 同名同格式！）→ 现有 VAD→平台 ASR 链路直接复用 | 加唤醒词上报展示 |
| 批量更新 | 无 apt → rsync 源码/tar + 重启进程；装机向导改部署通道 | |
| 急停 | EmergencyStateChannel topic 展示 + EStop 系统模式 | |

**风险/待实机验证清单**：
- user systemd 自启在 HDU 是否可用（沙盒/DDS 环境变量坑，对照 X2 的 agirun 经验）
- RosMsgWrapper 的 pb 反序列化性能（点云/音频流）
- RGB Image 30FPS×1920×1536 在 HDU 上的 JPEG 编码 CPU 占用（可降帧/降采样）
- 相机 /stream 深度相机默认 iceoryx 后端订阅不到的问题（非深度相机 rgb 无此问题）
- GetAvailableActions 与状态机实际切换时序
- AimDK 开发包（prebuilt whl/proto）获取渠道：文档站下载 or 厂商
