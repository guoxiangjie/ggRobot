/**preload 安全桥 — 只暴露窄 API 面，业务全走 HTTP*/

import { contextBridge, ipcRenderer } from 'electron'

export interface InstallProgress {
  step: 'connect' | 'stop-legacy' | 'upload-deb' | 'upload-token' | 'install' | 'health-poll' | 'done'
  detail?: string
  progress?: number
  error?: string
}

const api = {
  getPlatformPort: (): Promise<number> => ipcRenderer.invoke('getPlatformPort'),
  openExternal: (url: string): Promise<void> => ipcRenderer.invoke('openExternal', url),
  pickDeb: (): Promise<string | null> => ipcRenderer.invoke('pickDeb'),

  installAgent: (req: {
    host: string; username: string; password: string; debPath: string; name: string; platformPort: number
  }): Promise<{ jobId: string }> => ipcRenderer.invoke('installAgent', req),

  installAbort: (jobId: string): Promise<boolean> => ipcRenderer.invoke('installAbort', jobId),

  onInstallProgress: (cb: (p: InstallProgress) => void): (() => void) => {
    const listener = (_i: unknown, data: InstallProgress): void => cb(data)
    ipcRenderer.on('install:progress', listener)
    return () => ipcRenderer.removeListener('install:progress', listener)  // React useEffect cleanup
  },
}

contextBridge.exposeInMainWorld('desktop', api)
export type DesktopApi = typeof api
