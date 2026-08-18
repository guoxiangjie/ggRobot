/**平台 API client — 127.0.0.1:{port}（ggplatform sidecar）*/

import axios, { AxiosInstance } from 'axios'
import { useAppStore } from '@/stores/app'

let client: AxiosInstance | null = null

export function platformApi(): AxiosInstance {
  if (!client) {
    client = axios.create({ timeout: 8000 })
    client.interceptors.request.use((cfg) => {
      cfg.baseURL = `http://127.0.0.1:${useAppStore.getState().port}`
      return cfg
    })
  }
  return client
}

// ── 类型 ──
export interface RobotRecord {
  id: string
  sn: string
  name: string
  model: string
  status: 'pending' | 'active'
  last_ip: string
  last_seen: string | null
  token: string
  summary?: RobotSummary
}

export interface RobotSummary {
  id: string
  sn: string
  name: string
  model: string
  status: string
  online: boolean
  token_ok: boolean
  battery_soc: number | null
  version: string
  last_ip: string
}

export const api = {
  listRobots: async (refresh = false): Promise<RobotRecord[]> => {
    const { data } = await platformApi().get(`/api/robots`, { params: refresh ? { refresh: 1 } : {} })
    return data.robots
  },
  patchRobot: async (id: string, patch: { name?: string }): Promise<RobotRecord> => {
    const { data } = await platformApi().patch(`/api/robots/${id}`, patch)
    return data
  },
  deleteRobot: async (id: string): Promise<void> => {
    await platformApi().delete(`/api/robots/${id}`)
  },
  rotateToken: async (id: string): Promise<string> => {
    const { data } = await platformApi().post(`/api/robots/${id}/token-rotate`)
    return data.token
  },
  scanSubnet: async (subnet: string): Promise<unknown[]> => {
    const { data } = await platformApi().post(`/api/discovery/scan`, null, {
      params: { subnet }, timeout: 30_000,
    })
    return data.found
  },
}

/**hub WS — 多机状态聚合订阅 */
export function hubWs(onRobots: (robots: RobotSummary[]) => void): () => void {
  const port = useAppStore.getState().port
  let ws: WebSocket | null = null
  let timer: ReturnType<typeof setTimeout> | null = null
  let closed = false

  const connect = (): void => {
    ws = new WebSocket(`ws://127.0.0.1:${port}/hub`)
    ws.onmessage = (ev) => {
      try {
        const msg = JSON.parse(ev.data) as { type: string; robots?: RobotSummary[] }
        if (msg.type === 'hub' && msg.robots) onRobots(msg.robots)
      } catch { /* */ }
    }
    ws.onclose = () => {
      if (!closed) timer = setTimeout(connect, 3000)  // 重连 3s
    }
  }
  connect()

  const ping = window.setInterval(() => {
    if (ws?.readyState === WebSocket.OPEN) ws.send('{"type":"ping"}')
  }, 5000)

  return () => {
    closed = true
    clearInterval(ping)
    if (timer) clearTimeout(timer)
    ws?.close()
  }
}
