/**GG Robot 平台主进程 — 窗口（状态记忆）+ sidecar 生命周期*/

import { app, BrowserWindow } from 'electron'
import path from 'path'
import fs from 'fs'
import { is } from '@electron-toolkit/utils'
import { startSidecar, stopSidecar } from './sidecar'
import { registerIpc } from './ipc'

// 自绘标题栏的 drag 区域（renderer CSS 配合 -webkit-app-region: drag）
const TRAFFIC_LIGHT = { x: 14, y: 16 }

// ── 窗口状态记忆（bounds + 最大化）──
interface WinState { x?: number; y?: number; width: number; height: number; maximized: boolean }
const STATE_FILE = (): string => path.join(app.getPath('userData'), 'window-state.json')

function loadWinState(): WinState {
  try {
    return JSON.parse(fs.readFileSync(STATE_FILE(), 'utf-8')) as WinState
  } catch {
    return { width: 1360, height: 860, maximized: false }
  }
}

function saveWinState(win: BrowserWindow): void {
  try {
    const bounds = win.getNormalBounds()   // 最大化时返回还原尺寸
    fs.writeFileSync(STATE_FILE(), JSON.stringify({
      ...bounds, maximized: win.isMaximized(),
    }))
  } catch { /* */ }
}

let mainWindow: BrowserWindow | null = null

async function createWindow(): Promise<void> {
  const state = loadWinState()
  mainWindow = new BrowserWindow({
    width: state.width,
    height: state.height,
    x: state.x,
    y: state.y,
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
  mainWindow.on('ready-to-show', () => {
    mainWindow?.show()
    if (state.maximized) mainWindow?.maximize()
    if (is.dev && !process.env.GG_NO_DEVTOOLS) mainWindow?.webContents.openDevTools()
  })
  // 状态记忆：resize/move 防抖保存 + 关闭时保存
  let saveTimer: NodeJS.Timeout | null = null
  const debounceSave = (): void => {
    if (saveTimer) clearTimeout(saveTimer)
    saveTimer = setTimeout(() => mainWindow && saveWinState(mainWindow), 800)
  }
  mainWindow.on('resize', debounceSave)
  mainWindow.on('move', debounceSave)
  mainWindow.on('close', () => mainWindow && saveWinState(mainWindow))
  mainWindow.on('closed', () => (mainWindow = null))

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
