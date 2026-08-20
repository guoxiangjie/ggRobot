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

// ── 多机编排 ──
export interface ChoreoStep {
  type: string
  at: number
  [k: string]: unknown
}
export interface ChoreoTrack {
  robot_id: string
  robot_name: string
  steps: ChoreoStep[]
}
export interface Choreo {
  id: string
  name: string
  desc: string
  tracks: ChoreoTrack[]
  robot_count?: number
  step_count?: number
  created_at?: string
  updated_at?: string
}
export interface ChoreoRunRobot {
  robot_id: string
  name: string
  state: string
  current: number
  total: number
  failed: { index: number; type: string; at: number; error: string }[]
  error?: string
}
export interface ChoreoRun {
  run_id: string
  choreo_id: string
  name: string
  state: string
  start_ts: number
  robots: ChoreoRunRobot[]
  created_at: string
  ended_at: string
}

// ── 编排步骤类型清单（agent 上报，前端表单动态组装）──
export interface ChoreoStepField {
  name: string
  label: string
  kind: 'text' | 'number' | 'select' | 'switch'
  required?: boolean
  default?: unknown
  options?: { label: string; value: string | number }[]
}
export interface ChoreoStepType {
  type: string
  label: string
  icon: string
  color: string
  fields: ChoreoStepField[]
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
  // ── 编排 ──
  listChoreos: async (): Promise<Choreo[]> => {
    const { data } = await platformApi().get('/api/choreos')
    return data.choreos
  },
  getChoreo: async (id: string): Promise<Choreo> => {
    const { data } = await platformApi().get(`/api/choreos/${id}`)
    return data
  },
  saveChoreo: async (choreo: { id?: string; name: string; desc: string; tracks: ChoreoTrack[] }): Promise<Choreo> => {
    const { data } = choreo.id
      ? await platformApi().patch(`/api/choreos/${choreo.id}`, choreo)
      : await platformApi().post('/api/choreos', choreo)
    return data
  },
  deleteChoreo: async (id: string): Promise<void> => {
    await platformApi().delete(`/api/choreos/${id}`)
  },
  runChoreo: async (id: string): Promise<{ ok: boolean; run_id?: string; offline?: string[]; error?: string }> => {
    const { data } = await platformApi().post(`/api/choreos/${id}/run`)
    return data
  },
  stopChoreoRun: async (runId: string): Promise<{ ok: boolean }> => {
    const { data } = await platformApi().post(`/api/choreo/run/${runId}/stop`)
    return data
  },
  choreoRunStatus: async (runId: string): Promise<ChoreoRun> => {
    const { data } = await platformApi().get(`/api/choreo/run/${runId}/status`)
    return data
  },
  getChoreoTypes: async (): Promise<ChoreoStepType[]> => {
    const { data } = await platformApi().get(`/api/choreo/types`, { timeout: 3000 })
    return data.types
  },
  choreoRuns: async (): Promise<ChoreoRun[]> => {
    const { data } = await platformApi().get(`/api/choreo/runs`)
    return data.runs
  },
}

/**hub WS — 多机状态聚合订阅（robots + 编排运行） */
export function hubWs(
  onRobots: (robots: RobotSummary[]) => void,
  onChoreo?: (runs: ChoreoRun[]) => void,
): () => void {
  const port = useAppStore.getState().port
  let ws: WebSocket | null = null
  let timer: ReturnType<typeof setTimeout> | null = null
  let closed = false

  const connect = (): void => {
    ws = new WebSocket(`ws://127.0.0.1:${port}/hub`)
    ws.onmessage = (ev) => {
      try {
        const msg = JSON.parse(ev.data) as { type: string; robots?: RobotSummary[]; choreo?: ChoreoRun[] }
        if (msg.type === 'hub') {
          if (msg.robots) onRobots(msg.robots)
          if (msg.choreo && onChoreo) onChoreo(msg.choreo)
        }
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
