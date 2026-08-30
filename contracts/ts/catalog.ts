// ⚠️ 自动生成（contracts/gen.py），勿手改 — 真源: contracts/catalog.json
export const CATALOG_VERSION = 1;

export interface CapabilityCallParam { [field: string]: string }   // 字段名 → "类型 默认值 说明"
export interface CapabilityReportParam { [field: string]: string }

export interface CapabilityType {
  type: string
  category: 'motion' | 'expression' | 'perception' | 'status'
  desc: string
  call: CapabilityCallParam
  report: CapabilityReportParam
}

export interface Catalog {
  catalog_version: number
  desc: string
  capabilities: CapabilityType[]
}

export const CATALOG: Catalog = {
  "catalog_version": 1,
  "desc": "ggRobot 2.0 能力类型目录 v1 — 平台/agent/前端的共同契约。agent 上报'支持哪些类型+参数空间'，UI 按类型预置交互组件动态组装。新型号优先映射现有类型；确需新类型时 bump catalog_version 并平台发版。",
  "capabilities": [
    {
      "type": "speech.tts",
      "category": "expression",
      "desc": "语音播报",
      "call": {
        "text": "string 必填 播报文本",
        "is_interrupted": "boolean=true 打断当前播报",
        "priority_level": "number=6 优先级"
      },
      "report": {}
    },
    {
      "type": "motion.preset",
      "category": "motion",
      "desc": "预设动作（动作清单由 agent 上报，action_id 为 motion:area 复合键）",
      "call": {
        "action_id": "string 必填 motion:area 复合键",
        "interrupt": "boolean=true 打断进行中动作"
      },
      "report": {
        "actions": "list<{id, name, area, requires_stand}> 动作清单（requires_stand=需 STAND 模式前置）"
      }
    },
    {
      "type": "locomotion.velocity",
      "category": "motion",
      "desc": "连续速度遥控（WS 帧持续发送，松开发全零）",
      "call": {
        "forward": "number=0 m/s",
        "lateral": "number=0 m/s",
        "angular": "number=0 rad/s"
      },
      "report": {
        "axes": "list<string> 支持的轴（forward/lateral/angular）",
        "send_interval_ms": "number=50 发送间隔（20Hz）",
        "gears": "list<{id, name, forward, lateral, angular}> 速度档位"
      }
    },
    {
      "type": "mode.switch",
      "category": "motion",
      "desc": "运动模式切换（模式清单由 agent 上报，含必须数字 ID 的模式）",
      "call": {
        "mode": "string 必填 模式标识",
        "value": "number? 可选 数字模式 ID（部分模式后端只认数字）"
      },
      "report": {
        "modes": "list<{id, name, numeric_value?}> 模式清单（numeric_value 存在时调用必须携带）"
      }
    },
    {
      "type": "expression.face",
      "category": "expression",
      "desc": "面部表情",
      "call": {
        "emotion_id": "number 必填 表情 ID",
        "mode": "number=1 播放模式"
      },
      "report": {
        "emotions": "list<{id, name}> 表情清单"
      }
    },
    {
      "type": "media.play",
      "category": "expression",
      "desc": "音视频媒体播放（文件管理走平台，播放下发 agent）",
      "call": {
        "name": "string 必填 文件名",
        "action": "string=play play|stop"
      },
      "report": {
        "kinds": "list<string> 支持类型（audio/video）"
      }
    },
    {
      "type": "perception.camera",
      "category": "perception",
      "desc": "相机流（WS 二进制订阅：4B大端ms时间戳+JPEG）",
      "call": {
        "camera_id": "string 必填 切换活跃相机"
      },
      "report": {
        "cameras": "list<{id, label, topic}> 相机清单",
        "frame_interval_ms": "number=100 推帧间隔"
      }
    },
    {
      "type": "slam.mapping",
      "category": "perception",
      "desc": "SLAM 建图（开始/停止保存）",
      "call": {
        "command": "string 必填 start|stop",
        "map_name": "string? stop 时的保存名"
      },
      "report": {
        "supported": "boolean"
      }
    },
    {
      "type": "slam.localize",
      "category": "perception",
      "desc": "SLAM 重定位与实时位姿",
      "call": {
        "map_id": "string 必填",
        "x": "number=0 像素",
        "y": "number=0 像素"
      },
      "report": {
        "supported": "boolean"
      }
    },
    {
      "type": "status.battery",
      "category": "status",
      "desc": "电池状态（推送型，sensor.* WS 订阅）",
      "call": {},
      "report": {
        "topic": "string=sensor.battery"
      }
    },
    {
      "type": "status.imu",
      "category": "status",
      "desc": "IMU 姿态（推送型）",
      "call": {},
      "report": {
        "topic": "string=sensor.imu"
      }
    },
    {
      "type": "status.joints",
      "category": "status",
      "desc": "关节状态（推送型）",
      "call": {},
      "report": {
        "topic": "string=sensor.joints",
        "joint_names": "list<string> 关节名清单"
      }
    },
    {
      "type": "status.system",
      "category": "status",
      "desc": "系统状态/模式/开发者状态迁移（推送型+主动查询）",
      "call": {
        "state": "string? migrate 时的目标状态（开发者模式）"
      },
      "report": {
        "migrate_states": "list<string> 允许迁移的状态清单"
      }
    },
    {
      "type": "nav.goto",
      "category": "motion",
      "desc": "导航到点（A3；到点/坐标/直线/高精多模式）",
      "call": {
        "kind": "string=goal goal/pose2d/linear_goal/linear_pose2d/precise_goal",
        "map_id": "string 必填 当前地图 ID",
        "target_id": "number? 拓扑导航点 ID（与 x/y 二选一）",
        "x": "number? 目标 X（m）",
        "y": "number? 目标 Y（m）",
        "angle": "number=0 朝向（rad）"
      },
      "report": {
        "kinds": "list<string> 支持的导航模式",
        "task_id": "任务句柄（控制/查询用）"
      }
    },
    {
      "type": "nav.control",
      "category": "motion",
      "desc": "导航任务控制（A3；暂停/恢复/取消）",
      "call": {
        "op": "string 必填 pause/resume/cancel",
        "task_id": "number=0 任务 ID（0=最近）"
      },
      "report": {
        "ops": "list<string> 支持的操作"
      }
    },
    {
      "type": "dance.play",
      "category": "motion",
      "desc": "舞蹈播放（A3；技能资源，Start/Pause/Stop）",
      "call": {
        "command": "string=Start Start/Pause/Stop",
        "path": "string 技能资源路径",
        "session_id": "string? 会话 ID"
      },
      "report": {
        "skills": "list<{id, name, path, duration}> 技能清单"
      }
    },
    {
      "type": "motion.advance",
      "category": "motion",
      "desc": "动作高级控制（A3；暂停/复位/循环）",
      "call": {
        "motion_id": "string 动作资源路径（空=停止）",
        "pause": "boolean=false",
        "reset": "boolean=false",
        "repeat": "boolean=false",
        "duration_ms": "number=10000 最长运行时间"
      },
      "report": {}
    },
    {
      "type": "map.manage",
      "category": "perception",
      "desc": "地图管理（A3；RPC 数据源：列表/2D图/拓扑点/实时建图）",
      "call": {},
      "report": {
        "supported": "boolean"
      }
    },
    {
      "type": "status.emergency",
      "category": "status",
      "desc": "急停状态（有线/无线/软件）",
      "call": {},
      "report": {
        "topic": "sensor.emergency 推送通道"
      }
    }
  ]
};

export const CAPABILITY_TYPES: string[] = CATALOG.capabilities.map((c) => c.type);
