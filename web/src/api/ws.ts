/** WebSocket 客户端 — 替代 roslib，直连后端 :8000/ws */

export type WsCallback<T = any> = (data: T) => void

type SensorPayload = {
  type: 'sensor'
  ts: number
  battery: { percentage: number; voltage: number; current: number; temperature: number; power: number } | null
  imu: { accel_x: number; accel_y: number; accel_z: number } | null
  arms: Array<{ name: string; position: number; velocity: number }>
}

type CameraFrameCallback = (frame: ArrayBuffer) => void

class WsClient {
  private ws: WebSocket | null = null
  private _connected = false
  private _autoReconnect = true
  private reconnectTimer: ReturnType<typeof setTimeout> | null = null

  private sensorCbs: Set<WsCallback<SensorPayload>> = new Set()
  private cameraCbs: Set<CameraFrameCallback> = new Set()
  private pongCbs: Set<WsCallback<null>> = new Set()

  get connected() {
    return this._connected
  }

  connect() {
    if (this.ws) return

    const url = `ws://${location.host}/ws`
    console.log('🔗 连接 WebSocket:', url)

    this.ws = new WebSocket(url)
    this.ws.binaryType = 'arraybuffer'

    this.ws.onopen = () => {
      this._connected = true
      console.log('✅ WebSocket 已连接')
      this.startHeartbeat()
    }

    this.ws.onmessage = (event) => {
      if (event.data instanceof ArrayBuffer) {
        // 相机帧（二进制）
        this.cameraCbs.forEach(cb => cb(event.data as ArrayBuffer))
        return
      }

      try {
        const msg = JSON.parse(event.data)
        if (msg.type === 'sensor') {
          this.sensorCbs.forEach(cb => cb(msg as SensorPayload))
        } else if (msg.type === 'pong') {
          this.pongCbs.forEach(cb => cb(null))
        }
      } catch {
        // ignore parse errors
      }
    }

    this.ws.onclose = () => {
      this._connected = false
      console.log('🔌 WebSocket 已断开')
      if (this._autoReconnect) {
        this.reconnectTimer = setTimeout(() => this.connect(), 3000)
      }
    }

    this.ws.onerror = (err) => {
      console.error('❌ WebSocket 错误', err)
    }
  }

  disconnect() {
    this._autoReconnect = false
    if (this.reconnectTimer) { clearTimeout(this.reconnectTimer); this.reconnectTimer = null }
    this.ws?.close()
    this.ws = null
    this._connected = false
  }

  // ── 传感器数据 ──
  onSensor(cb: WsCallback<SensorPayload>) { this.sensorCbs.add(cb) }
  offSensor(cb: WsCallback<SensorPayload>) { this.sensorCbs.delete(cb) }

  // ── 相机帧 ──
  onCamera(cb: CameraFrameCallback) { this.cameraCbs.add(cb) }
  offCamera(cb: CameraFrameCallback) { this.cameraCbs.delete(cb) }

  // ── 发送 ──
  send(data: Record<string, unknown>) {
    if (this.ws && this._connected) {
      this.ws.send(JSON.stringify(data))
    }
  }

  /** 发送速度指令 */
  sendVelocity(forward: number, lateral: number, angular: number) {
    this.send({ type: 'velocity', forward, lateral, angular })
  }

  // ── 心跳 ──
  private heartbeatTimer: ReturnType<typeof setInterval> | null = null

  private startHeartbeat() {
    if (this.heartbeatTimer) return
    this.heartbeatTimer = setInterval(() => {
      if (this.ws?.readyState === WebSocket.OPEN) {
        this.ws.send(JSON.stringify({ type: 'ping' }))
      }
    }, 5000)
  }
}

export const wsClient = new WsClient()
