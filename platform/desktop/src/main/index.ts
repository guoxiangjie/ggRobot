/**GG Robot 平台主进程 — 窗口 + sidecar 生命周期*/

import { app, BrowserWindow } from 'electron'
import path from 'path'
import { is } from '@electron-toolkit/utils'
import { startSidecar, stopSidecar } from './sidecar'
import { registerIpc } from './ipc'

// 自绘标题栏的 drag 区域（renderer CSS 配合 -webkit-app-region: drag）
const TRAFFIC_LIGHT = { x: 14, y: 16 }

let mainWindow: BrowserWindow | null = null

async function createWindow(): Promise<void> {
  mainWindow = new BrowserWindow({
    width: 1360,
    height: 860,
    minWidth: 1080,
    minHeight: 700,
    show: false,
    frame: false,                        // 无系统标题栏（自绘 + 红绿灯内嵌）
    trafficLightPosition: TRAFFIC_LIGHT,
    titleBarStyle: 'hidden',
    backgroundColor: '#16181d',
    webPreferences: {
      preload: path.join(__dirname, '../preload/index.js'),
      sandbox: false,
      contextIsolation: true,
      nodeIntegration: false,
    },
  })
  mainWindow.on('ready-to-show', () => mainWindow?.show())

  // ── sidecar 启动/复用 → 就绪后才加载页面（端口注入 renderer）──
  await startSidecar((ok, port) => {
    if (!mainWindow) return
    if (is.dev) {
      const devUrl = process.env['ELECTRON_RENDERER_URL'] as string
      mainWindow.loadURL(`${devUrl}?port=${port}`)
    } else {
      mainWindow.loadFile(path.join(__dirname, '../renderer/index.html'), { query: { port: String(port) } })
    }
    if (!ok) mainWindow.webContents.send('sidecar-failed')
  })

  mainWindow.on('closed', () => (mainWindow = null))
}

app.whenReady().then(() => {
  registerIpc()
  void createWindow()
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) void createWindow()
  })
})

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit()
})

app.on('before-quit', () => stopSidecar())
