// X2 AimDK 消息类型定义 —— 对应 SDK msg/srv 文件
// 只定义 Web 控制台当前用到的字段，后续按需扩展

// ── 通用头 ──
export interface RosTime {
  sec: number
  nanosec: number
}

export interface MessageHeader {
  stamp: RosTime
  frame_id: string
  sequence: number
  meas_stamp: RosTime
}

export interface RequestHeader {
  stamp: RosTime
}

export interface ResponseHeader {
  stamp: RosTime
  code: number
}

// ── 电池 ──
export interface PmuState {
  // BMS
  battery_pack_voltage: number
  battery_current: number
  battery_output_power: number
  battery_temperature: number
  battery_remaining_capacity: number
  battery_remaining_capacity_percentage: number
  battery_cycle_count: number
  // PMU
  pmu_temperature: number
  fan_speed: number
  fan_pecentage: number
  orin_current: number
  orin_voltage: number
  head_power_voltage: number
  bus_48v_voltage: number
  output_12v_voltage: number
}

// ── 关节 ──
export interface JointState {
  name: string
  position: number
  velocity: number
  effort: number
  error_code: number
}

export interface JointStateArray {
  header: MessageHeader
  state: { value: number }
  joints: JointState[]
}

// ── 速度指令 ──
export interface McLocomotionVelocity {
  header: MessageHeader
  source: string
  forward_velocity: number
  lateral_velocity: number
  angular_velocity: number
}

// ── TTS ──
export interface PlayTtsRequest {
  text: string
  domain: string
  trace_id: string
  is_interrupted: boolean
  priority_weight: number
  priority_level: { value: number }
}

export interface PlayTtsResponse {
  text: string
  is_success: boolean
  error_message: string
  estimated_duration: number
}

// ── 预设动作 ──
export interface McPresetMotion {
  value: number
}

export interface McControlArea {
  value: number // v0.8.0+：1=左臂 2=右臂 3=双臂 11=全身（非旧位掩码 1/2/4/8）
}

export interface SetMcPresetMotionRequest {
  area: McControlArea
  motion: McPresetMotion
  interrupt: boolean
}

export interface CommonTaskResponse {
  response: {
    header: ResponseHeader
    task_id: number
    state: { value: number }
  }
}

// ── 动作查询 ──
export interface McActionInfo {
  current_action: { value: number }
  action_desc: string
  status: { value: number }
}

// ── 触摸 ──
export interface TouchState {
  header: MessageHeader
  event_type: number
  is_touched: boolean[]
}

// ── 机器人状态 ──
export interface RobotStatus {
  battery: {
    percentage: number
    voltage: number
    current: number
    temperature: number
    power: number
    charging: boolean
  }
  imu: {
    accel_x: number
    accel_y: number
    accel_z: number
    gyro_x: number
    gyro_y: number
    gyro_z: number
  }
  joints: Record<string, { position: number; velocity: number }>
  touch: {
    touched: boolean
    event: number
  }
}
