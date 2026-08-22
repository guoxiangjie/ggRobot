/**GG Robot 平台主进程 — 窗口（状态记忆）+ sidecar 生命周期*/

import { app, BrowserWindow, Menu } from 'electron'
import path from 'path'
import fs from 'fs'
import { is } from '@electron-toolkit/utils'
import { startSidecar, stopSidecar } from './sidecar'
import { registerIpc } from './ipc'

// 自绘标题栏的 drag 区域（renderer CSS 配合 -webkit-app-region: drag）
// y=21：titlebar 54px 文字垂直中心 27 − 红绿灯半高 6（12px 灯）
const TRAFFIC_LIGHT = { x: 12, y: 21 }

// ── 窗口状态记忆（bounds + 最大化）──
interface WinState { x?: number; y?: number; width: number; height: number; maximized: boolean }
const STATE_FILE = (): string => path.join(app.getPath('userData'), 'window-state.json')

function loadWinState(): WinState {
  try {
    return JSON.parse(fs.readFileSync(STATE_FILE(), 'utf-8')) as WinState
  } catch {
    return { width: 1400, height: 940, maximized: false }
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
    frame: false,
    titleBarStyle: 'hidden',            // 隐藏标题栏但保留红绿灯（frame:false 单独用会连红绿灯一起去掉）
    trafficLightPosition: TRAFFIC_LIGHT,


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
    // dev 默认不弹 DevTools（要开：GG_DEVTOOLS=1 pnpm dev，或菜单「显示 → 开发者工具」）
    if (is.dev && process.env.GG_DEVTOOLS) mainWindow?.webContents.openDevTools()
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

/**系统顶部应用菜单（macOS 菜单栏）——自定义中文；role 保留系统行为与快捷键 */
function setupApplicationMenu(): void {
  const template: Electron.MenuItemConstructorOptions[] = [
    {
      label: app.getName(),
      submenu: [
        { role: 'about', label: `关于 ${app.getName()}` },
        { type: 'separator' },
        { role: 'services', label: '服务' },
        { type: 'separator' },
        { role: 'hide', label: '隐藏' + app.getName() },
        { role: 'unhide', label: '显示全部' },
        { type: 'separator' },
        { role: 'quit', label: `退出 ${app.getName()}` },
      ],
    },
    {
      label: '编辑',
      submenu: [
        { role: 'undo', label: '撤销' },
        { role: 'redo', label: '重做' },
        { type: 'separator' },
        { role: 'cut', label: '剪切' },
        { role: 'copy', label: '复制' },
        { role: 'paste', label: '粘贴' },
        { role: 'selectAll', label: '全选' },
      ],
    },
    {
      label: '显示',
      submenu: [
        { role: 'reload', label: '重新加载' },
        { role: 'forceReload', label: '强制重新加载' },
        { role: 'toggleDevTools', label: '开发者工具' },
        { type: 'separator' },
        { role: 'resetZoom', label: '实际大小' },
        { role: 'zoomIn', label: '放大' },
        { role: 'zoomOut', label: '缩小' },
        { type: 'separator' },
        { role: 'togglefullscreen', label: '切换全屏' },
      ],
    },
    {
      label: '窗口',
      submenu: [
        { role: 'minimize', label: '最小化' },
        { role: 'zoom', label: '缩放' },
        { role: 'close', label: '关闭' },
      ],
    },
  ]
  Menu.setApplicationMenu(Menu.buildFromTemplate(template))
}

app.whenReady().then(() => {
  registerIpc()
  setupApplicationMenu()
  // dev 模式 Dock 也用产品图标（打包版由 electron-builder icns 负责）
  if (is.dev && process.platform === 'darwin') {
    try { app.dock?.setIcon(path.join(__dirname, '../../resources/icon.png')) } catch { /* */ }
  }
  void createWindow()
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) void createWindow()
  })
})

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit()
})

app.on('before-quit', () => stopSidecar())
