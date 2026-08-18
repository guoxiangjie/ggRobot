/**全局 app 状态 — sidecar 端口 / 本机 client_id（会话锁身份）*/

import { create } from 'zustand'

function readPortFromQuery(): number {
  const m = new URLSearchParams(location.search).get('port')
  return m ? Number(m) : 8310
}

function loadClientId(): string {
  let cid = localStorage.getItem('gg.client_id')
  if (!cid) {
    cid = `desktop-${Math.random().toString(36).slice(2, 8)}-${Date.now().toString(36)}`
    localStorage.setItem('gg.client_id', cid)
  }
  return cid
}

interface AppState {
  port: number
  clientId: string
  sidecarReady: boolean
  setPort: (p: number) => void
  init: () => Promise<void>
}

export const useAppStore = create<AppState>((set) => ({
  port: readPortFromQuery(),
  clientId: loadClientId(),
  sidecarReady: false,

  setPort: (port) => set({ port }),

  init: async () => {
    // query 优先；拿不到再问 main 进程（Electron 环境）
    const q = new URLSearchParams(location.search).get('port')
    if (!q && window.desktop) {
      try {
        const p = await window.desktop.getPlatformPort()
        set({ port: p })
      } catch { /* dev 浏览器直开无 desktop */ }
    }
    set({ sidecarReady: true })
  },
}))
