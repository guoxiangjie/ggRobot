/**IPC 面（窄 API）— getPlatformPort / openExternal / installAgent / onInstallProgress */

import { ipcMain, shell, dialog, BrowserWindow } from 'electron'
import { AgentInstaller, InstallRequest } from './installer/agentInstall'
import { platformPort } from './sidecar'

export function registerIpc(): void {
  ipcMain.handle('getPlatformPort', () => platformPort())

  ipcMain.handle('openExternal', (_e, url: string) => {
    if (/^https?:\/\//.test(url)) shell.openExternal(url)
  })

  // 选择本地 deb 文件（装机向导）
  ipcMain.handle('pickDeb', async (e) => {
    const win = BrowserWindow.fromWebContents(e.sender)
    const r = await dialog.showOpenDialog(win!, {
      title: '选择 agent .deb 安装包',
      filters: [{ name: 'Deb 包', extensions: ['deb'] }],
      properties: ['openFile'],
    })
    return r.canceled ? null : r.filePaths[0]
  })

  // 装机向导：返回 jobId，进度走 install:progress 事件
  const installers = new Map<string, AgentInstaller>()
  ipcMain.handle('installAgent', async (e, req: InstallRequest) => {
    const jobId = `job-${Date.now()}-${Math.floor(Math.random() * 1e4)}`
    const installer = new AgentInstaller(e.sender)
    installers.set(jobId, installer)
    // 异步跑，立即返回 jobId；结果也走 install:progress(done)
    void installer.run(req).finally(() => installers.delete(jobId))
    return { jobId }
  })

  ipcMain.handle('installAbort', (_e, jobId: string) => {
    installers.get(jobId)?.abort()
    return true
  })
}
