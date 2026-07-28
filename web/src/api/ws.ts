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

const HEARTBEAT_INTERVAL = 5000   // 每 5s 发一次 ping
const PONG_TIMEOUT = 15000        // 超过 15s（约 3 次 ping）无任何消息即判定连接死亡
const RECONNECT_DELAY = 3000

class WsClient {
  private ws: WebSocket | null = null
  private _connected = false
  private _autoReconnect = true
  private reconnectTimer: ReturnType<typeof setTimeout> | null = null
  private heartbeatTimer: ReturnType<typeof setInterval> | null = null
  private watchdogTimer: ReturnType<typeof setInterval> | null = null
  private _lastMsgAt = 0

  private sensorCbs: Set<WsCallback<SensorPayload>> = new Set()
  private cameraCbs: Set<CameraFrameCallback> = new Set()
  private pongCbs: Set<WsCallback<null>> = new Set()
  private reconnectCbs: Set<() => void> = new Set()
  private disconnectCbs: Set<() => void> = new Set()

  get connected() {
    return this._connected
  }

  connect() {
    if (this.ws) return

    this._autoReconnect = true

    const url = `ws://${location.host}/ws`
    console.log('🔗 连接 WebSocket:', url)

    this.ws = new WebSocket(url)
    this.ws.binaryType = 'arraybuffer'

    this.ws.onopen = () => {
      this._connected = true
      this._lastMsgAt = Date.now()
      console.log('✅ WebSocket 已连接')
      this.startHeartbeat()
      this.startWatchdog()
      // 通知所有监听者（首次连接 + 每次重连都走这里）
      this.reconnectCbs.forEach(cb => cb())
    }

    this.ws.onmessage = (event) => {
      this._lastMsgAt = Date.now()
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
      this._handleDisconnect()
      console.log('🔌 WebSocket 已断开')
      if (this._autoReconnect) {
        this.reconnectTimer = setTimeout(() => this.connect(), RECONNECT_DELAY)
      }
    }

    this.ws.onerror = (err) => {
      console.error('❌ WebSocket 错误', err)
    }
  }

  private _handleDisconnect() {
    this._connected = false
    this.stopHeartbeat()
    this.stopWatchdog()
    this.disconnectCbs.forEach(cb => cb())
  }

  disconnect() {
    this._autoReconnect = false
    if (this.reconnectTimer) { clearTimeout(this.reconnectTimer); this.reconnectTimer = null }
    this.stopHeartbeat()
    this.stopWatchdog()
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

  // ── 重连/断开回调（Set，支持多个监听者，不会互相覆盖）──
  onReconnect(cb: () => void) { this.reconnectCbs.add(cb) }
  offReconnect(cb: () => void) { this.reconnectCbs.delete(cb) }
  onDisconnect(cb: () => void) { this.disconnectCbs.add(cb) }
  offDisconnect(cb: () => void) { this.disconnectCbs.delete(cb) }

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
  private startHeartbeat() {
    if (this.heartbeatTimer) return
    this.heartbeatTimer = setInterval(() => {
      if (this.ws?.readyState === WebSocket.OPEN) {
        this.ws.send(JSON.stringify({ type: 'ping' }))
      }
    }, HEARTBEAT_INTERVAL)
  }

  private stopHeartbeat() {
    if (this.heartbeatTimer) { clearInterval(this.heartbeatTimer); this.heartbeatTimer = null }
  }

  // ── 看门狗：服务端静默断开（TCP 半开，onclose 不触发）时主动关闭触发重连 ──
  // 避免连接"假活"——socket 还在但数据不来，表现为传感器数据冻结。
  private startWatchdog() {
    if (this.watchdogTimer) return
    this.watchdogTimer = setInterval(() => {
      if (this.ws && this._connected && Date.now() - this._lastMsgAt > PONG_TIMEOUT) {
        console.warn(`⚠️ WebSocket ${PONG_TIMEOUT / 1000}s 无消息，判定半开连接，主动断开重连`)
        // close() 触发 onclose → 走重连逻辑（_autoReconnect 已置 true）
        this.ws.close()
      }
    }, HEARTBEAT_INTERVAL)
  }

  private stopWatchdog() {
    if (this.watchdogTimer) { clearInterval(this.watchdogTimer); this.watchdogTimer = null }
  }
}

export const wsClient = new WsClient()
