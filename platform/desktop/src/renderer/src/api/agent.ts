/**agent API client — 前端直连各机器人（http://{ip}:8300，Bearer token）*/

import axios, { AxiosInstance } from 'axios'
import { useAppStore } from '@/stores/app'

export function makeAgentClient(ip: string, token: string): AxiosInstance {
  const clientId = useAppStore.getState().clientId
  const http = axios.create({
    baseURL: `http://${ip}:8300`,
    timeout: 5000,
    headers: {
      Authorization: `Bearer ${token}`,
      'X-Client-Id': clientId,
    },
  })
  return http
}

/**agent WS 直连（token 走 query —— 浏览器 WS 无自定义 header）*/
export function agentWsUrl(ip: string, token: string, path = '/ws'): string {
  const { clientId } = useAppStore.getState()
  return `ws://${ip}:8300${path}?token=${encodeURIComponent(token)}&client_id=${encodeURIComponent(clientId)}`
}

// ── agent 契约类型（M5 页面用）──
export interface AgentHealth {
  ok: boolean; service: string; sn: string; model: string; version: string; paired: boolean
}
export interface Capabilities {
  catalog_version: number; sn: string; model: string; version: string
  capabilities: { type: string; params: Record<string, unknown> }[]
}
export interface SensorPayload {
  battery: { percentage: number; voltage: number; current: number; temperature: number; power: string } | null
  imu: Record<string, number> | null
  arms: { name: string; position: number; velocity: number }[] | null
}
