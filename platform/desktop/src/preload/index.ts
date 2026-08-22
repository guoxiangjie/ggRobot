/**preload 安全桥 — 只暴露窄 API 面，业务全走 HTTP*/

import { contextBridge, ipcRenderer } from 'electron'

export interface InstallProgress {
  step: 'connect' | 'stop-legacy' | 'upload-deb' | 'upload-token' | 'install' | 'health-poll' | 'restart' | 'done'
  detail?: string
  progress?: number
  error?: string
  robotId?: string   // 批量更新时的机器路由
}

const api = {
  getPlatformPort: (): Promise<number> => ipcRenderer.invoke('getPlatformPort'),
  openExternal: (url: string): Promise<void> => ipcRenderer.invoke('openExternal', url),
  openAddRobot: (): Promise<boolean> => ipcRenderer.invoke('openAddRobot'),
  openChoreoEdit: (choreoId: string): Promise<boolean> => ipcRenderer.invoke('openChoreoEdit', choreoId),
  openQuickCtrl: (): Promise<boolean> => ipcRenderer.invoke('openQuickCtrl'),
  openMappingStudio: (): Promise<boolean> => ipcRenderer.invoke('openMappingStudio'),
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

  updateAgents: (req: {
    targets: { robotId: string; name: string; host: string }[]
    username: string; password: string; debPath: string
  }): Promise<{ results: { robotId: string; name: string; ok: boolean; version?: string; error?: string }[] }> =>
    ipcRenderer.invoke('updateAgents', req),

  // ── 设置 ──
  settingsGet: (key: string): Promise<string> => ipcRenderer.invoke('settingsGet', key),
  settingsSet: (key: string, value: string): Promise<boolean> => ipcRenderer.invoke('settingsSet', key, value),
  pickDirectory: (def?: string): Promise<string | null> => ipcRenderer.invoke('pickDirectory', def ?? ''),
  openUserDataDir: (): Promise<string> => ipcRenderer.invoke('openUserDataDir'),
  savePhoto: (data: ArrayBuffer, nameHint: string): Promise<string> => ipcRenderer.invoke('savePhoto', data, nameHint),
  getAutoLaunch: (): Promise<boolean> => ipcRenderer.invoke('getAutoLaunch'),
  setAutoLaunch: (on: boolean): Promise<boolean> => ipcRenderer.invoke('setAutoLaunch', on),
}

contextBridge.exposeInMainWorld('desktop', api)
export type DesktopApi = typeof api
