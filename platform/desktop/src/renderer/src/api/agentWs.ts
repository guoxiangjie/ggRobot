/**agent WS v2 客户端 — 直连机器人数据面

时序参数照搬 1.0 实测结论（web/src/api/ws.ts）：心跳 5s / 看门狗 15s / 重连 3s。
协议：sub/unsub wildcard + event JSON + 二进制相机帧（4B大端ts + JPEG）+ velocity 控制帧。
*/

const HEARTBEAT_INTERVAL = 5000
const PONG_TIMEOUT = 15000   // 无任何消息判定半开，主动断开重连
const RECONNECT_DELAY = 3000

export type WsStatus = 'connecting' | 'open' | 'closed'

export interface SensorData {
  battery: { percentage: number; voltage: number; current: number; temperature: number; power: string } | null
  imu: Record<string, number> | null
  arms: { name: string; position: number; velocity: number }[] | null
}

export class AgentWsClient {
  private ws: WebSocket | null = null
  private heartbeatTimer: number | null = null
  private watchdog = 0
  private closedByUser = false
  private topics = new Set<string>()

  constructor(
    private url: string,
    private handlers: {
      onEvent?: (topic: string, data: unknown, ts: number) => void
      onFrame?: (jpeg: Blob, tsMs: number) => void
      onStatus?: (s: WsStatus) => void
      onSessionLost?: (lockedBy: unknown) => void
    },
  ) {}

  connect(): void {
    this.closedByUser = false
    this.handlers.onStatus?.('connecting')
    this.ws = new WebSocket(this.url)
    this.ws.binaryType = 'arraybuffer'

    this.ws.onopen = () => {
      this.feedWatchdog()
      this.handlers.onStatus?.('open')
      // 重新订阅（重连后恢复）
      if (this.topics.size > 0) this.send({ v: 1, type: 'sub', topics: [...this.topics] })
      this.startHeartbeat()
    }

    this.ws.onmessage = (ev) => {
      this.feedWatchdog()
      if (ev.data instanceof ArrayBuffer) {
        // 二进制相机帧：4B大端ms时间戳 + JPEG
        if (ev.data.byteLength > 4 && this.handlers.onFrame) {
          const ts = new DataView(ev.data).getUint32(0)
          this.handlers.onFrame(new Blob([ev.data.slice(4)], { type: 'image/jpeg' }), ts)
        }
        return
      }
      try {
        const msg = JSON.parse(ev.data as string) as {
          v: number; type: string; topic?: string; data?: unknown; ts?: number
          locked_by?: unknown; event?: string
        }
        switch (msg.type) {
          case 'event':
            if (msg.topic) this.handlers.onEvent?.(msg.topic, msg.data, msg.ts ?? 0)
            break
          case 'session':
            if (msg.event === 'lost') this.handlers.onSessionLost?.(msg.data)
            break
          case 'pong':
          case 'suback':
            break
        }
      } catch { /* 非 JSON 忽略 */ }
    }

    this.ws.onclose = () => {
      this.stopHeartbeat()
      this.handlers.onStatus?.('closed')
      if (!this.closedByUser) setTimeout(() => this.connect(), RECONNECT_DELAY)
    }
  }

  close(): void {
    this.closedByUser = true
    this.stopHeartbeat()
    this.ws?.close()
  }

  sub(topics: string[]): void {
    topics.forEach((t) => this.topics.add(t))
    this.send({ v: 1, type: 'sub', topics })
  }

  unsub(topics: string[]): void {
    topics.forEach((t) => this.topics.delete(t))
    this.send({ v: 1, type: 'unsub', topics })
  }

  sendVelocity(forward: number, lateral: number, angular: number): void {
    this.send({ v: 1, type: 'velocity', forward, lateral, angular })
  }

  private send(obj: unknown): void {
    if (this.ws?.readyState === WebSocket.OPEN) this.ws.send(JSON.stringify(obj))
  }

  private startHeartbeat(): void {
    this.stopHeartbeat()
    this.heartbeatTimer = window.setInterval(() => {
      this.send({ v: 1, type: 'ping' })
      // 看门狗：超过 PONG_TIMEOUT 无任何消息 → 半开连接，强制重连
      if (Date.now() - this.watchdog > PONG_TIMEOUT) this.ws?.close()
    }, HEARTBEAT_INTERVAL)
  }

  private stopHeartbeat(): void {
    if (this.heartbeatTimer != null) {
      clearInterval(this.heartbeatTimer)
      this.heartbeatTimer = null
    }
  }

  private feedWatchdog(): void {
    this.watchdog = Date.now()
  }
}
