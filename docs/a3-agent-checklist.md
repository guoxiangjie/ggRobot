# A3 agent 周一实机验证清单（2026-09-01）

> 离线开发完成（Phase A-D 全量代码），本文档是首次实机的分步验证 + 离线假设核对清单。
> 凭据：SSH agi/1；AP 热点密码 02270227；内网 HDU=10.42.10.10 / ADU=.11 / MDU=.12

## 0. 网络与 SSH（WiFi IP 现场 AimMaster 查）

- [ ] `ssh agi@<WiFi_IP>` 可登录；`ping 10.42.10.12`（内网 MDU 可达 = 三单元网络正常）
- [ ] HDU 上 `source /agibot/software/v0/entry/env/env.sh && ros2 topic list | head`（ROS 环境可用）

## 1. RPC 连通性（部署 agent 前手动 curl——核对端口表假设）

- [ ] `curl -m 3 -X POST http://10.42.10.10:59301/rpc/aimdk.protocol.AgentControlService/GetVoiceEnable -H 'Content-Type: application/json' -d '{}'`
- [ ] `curl -m 3 -X POST http://10.42.10.12:56322/rpc/aimdk.protocol.MotionControlActionService/GetAction -H 'Content-Type: application/json' -d '{}'`
- [ ] `curl -m 3 -X POST http://10.42.10.11:50807/rpc/aimdk.protocol.MappingService/GetStoredMapNames -H 'Content-Type: application/json' -d '{"command":"MappingCommand_GET_STORED_MAP_NAME"}'`
- [ ] 动作资源：`.../10.42.10.10:51049/.../ResourceService/GetResourceList -d '{"resource_type":"RESOURCE_TYPE_MOTION"}'`（**核对 resource_path 真实形态**）

## 2. 话题核对（RosMsgWrapper 假设）

- [ ] `ros2 topic list | grep -E "bms|emergency|arm_joint|locomotion|process_audio"`（**核对真实话题名**——文档短名 vs 实际 pb_ 前缀长名）
- [ ] `ros2 topic echo /motion/control/arm_joint_state --once`（标准 JointState？）
- [ ] BMS 话题名与 pb 反序列化字段（whl 装后再验）

## 3. agent 部署

- [ ] `make a3-deploy A3_IP=<WiFi_IP>`（脚本传 token，输出记住）
- [ ] `make a3-status` → health 200 + model=a3-ultra
- [ ] 失败排查：`make a3-log`（重点：env.sh 路径、ros2_plugin_proto local_setup、Jazzy setup.bash 路径——**三个 source 路径都是文档假设**）

## 4. 功能逐项（Mac 客户端零改动验证 —— 平台添加机器人填 WiFi_IP+token）

- [ ] 总览卡片在线、电量显示（BMS pb ✓）
- [ ] 仪表盘：关节（arm 14）/急停状态
- [ ] TTS 播报 + 「等播完」精确性（trace_id 轮询）
- [ ] 预设动作清单（资源拉取）→ 播放一个 → 停止
- [ ] 遥控：模式切 MOTION → WASD 行走（**比例换算手感**：max_forward=1.0，慢了调 robot.yaml）→ 松手停止
- [ ] 音量调节（上限 70 钳制）
- [ ] 相机：切头部双目左 → 有画面（**Image encoding 假设 rgb8**；深度相机 rgb 可能 iceoryx 后端收不到——先验鱼眼/双目）
- [ ] 编排：拉 types（dance/nav 出现）→ 排 tts+motion → 执行
- [ ] 导航（若有已建地图+导航点）：nav.goto target_id → 到点

## 5. 麦克风（可选，动交互模式前先问清楚）

- [ ] 当前模式 `GET /api/mic/mode`；若切 only_voice **需重启机器人**（现场确认可重启再动）
- [ ] only_voice 后 `/api/mic` recv_count 增长、语音段可拉

## 6. 离线假设核对表（不确定项，实机逐个确认）

| # | 假设 | 风险 |
|---|---|---|
| 1 | RosMsgWrapper 速度话题名带 `pb_3A...Channel` 后缀 | 名字不对则遥控不通（walk.py 为证，中风险） |
| 2 | velocity JSON `{"data":{...}}` + `mode:0` 数字 | 低（walk.py 原样） |
| 3 | BMS `bms_state==2` 判"在用"电池 | 低（有 reversed+兜底） |
| 4 | TTS 状态枚举字符串 `NOTInQue` 判播完 | 中（拼错则等满超时） |
| 5 | 相机 encoding rgb8 | 中（yuv 则该路黑，换路验证） |
| 6 | ros2_plugin_proto local_setup 路径 | 中（prebuilt 目录结构假设） |
| 7 | systemd user + linger 可用（无 X2 式沙盒） | 低（标准 Ubuntu） |
| 8 | SN 来源（conf 未填 sn 时 health=unpaired；实机找 SN 烧入） | 低 |
| 9 | `b""` 拼接 RosMsgWrapper.data 与官方示例 `[bytes([x])]` 等价 | 低 |
| 10 | 导航需 MOTION 模式 + 重定位（未做重定位流程，首验可能失败） | 已知（后续补 relocalize 流程） |

## 7. 已知待办（验证后做）

- 重定位流程（/api/slam/relocalize 的 A3 入参形态需实机校准，rpc.relocalize 是猜的）
- 表情播放（face/play 默认 iceoryx，需改 skillpilot.yaml——改机上配置有风险，实机评估）
- 平台装机向导/批量更新 A3 通道（tar 分发，替代 deb）
- 建图工作台 A3 数据源适配（slam.map JSON vs X2 slam.cloud 二进制——前端 MappingStudio 要加分支）
