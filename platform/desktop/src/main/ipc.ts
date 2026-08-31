/**IPC 面（窄 API）— getPlatformPort / openExternal / openAddRobot / installAgent / onInstallProgress / 设置 */

import path from 'path'
import fs from 'fs'
import { ipcMain, shell, dialog, app, BrowserWindow } from 'electron'
import { is } from '@electron-toolkit/utils'
import { AgentInstaller, InstallRequest } from './installer/agentInstall'
import { A3Installer } from './installer/a3Install'
import { platformPort } from './sidecar'

// ── 简易 kv 设置存储（userData/settings.json；renderer 侧 localStorage 之外需要 main 持有的项）──
const SETTINGS_FILE = (): string => path.join(app.getPath('userData'), 'settings.json')
function readSettings(): Record<string, string> {
  try { return JSON.parse(fs.readFileSync(SETTINGS_FILE(), 'utf-8')) as Record<string, string> }
  catch { return {} }
}
function writeSettings(s: Record<string, string>): void {
  try { fs.writeFileSync(SETTINGS_FILE(), JSON.stringify(s, null, 2)) } catch { /* */ }
}

// 添加机器人向导窗口（单例：重复开 → 聚焦）
let addWin: BrowserWindow | null = null

export function registerIpc(): void {
  ipcMain.handle('getPlatformPort', () => platformPort())

  ipcMain.handle('openExternal', (_e, url: string) => {
    if (/^https?:\/\//.test(url)) shell.openExternal(url)
  })

  // 装机向导独立窗口：同 renderer 加 #/add-robot 路由；非模态（等待装机时可操作主窗口）
  ipcMain.handle('openAddRobot', async () => {
    if (addWin) { addWin.show(); addWin.focus(); return true }
    const win = new BrowserWindow({
      width: 760, height: 680, minWidth: 720, minHeight: 620,
      title: '添加机器人',
      frame: false,
      titleBarStyle: 'hidden',                       // 与主窗口一致：自绘标题条 + 红绿灯
      trafficLightPosition: { x: 12, y: 21 },
      resizable: true,
      show: false,
      webPreferences: {
        preload: path.join(__dirname, '../preload/index.js'),
        sandbox: false, contextIsolation: true, nodeIntegration: false,
      },
    })
    addWin = win
    win.on('closed', () => { addWin = null })
    const port = platformPort()
    if (is.dev) {
      const devUrl = process.env['ELECTRON_RENDERER_URL'] as string
      await win.loadURL(`${devUrl}?port=${port}#/add-robot`)
    } else {
      await win.loadFile(path.join(__dirname, '../renderer/index.html'),
        { query: { port: String(port) }, hash: '/add-robot' })
    }
    win.show()
    return true
  })

  // 选择本地 deb 文件（装机向导/Agent 更新；记住上次目录）
  ipcMain.handle('pickDeb', async (e) => {
    const win = BrowserWindow.fromWebContents(e.sender)
    const r = await dialog.showOpenDialog(win!, {
      title: '选择 agent 安装包（X2=deb / A3=tar.gz）',
      filters: [{ name: '安装包', extensions: ['deb', 'gz', 'tgz'] }],
      properties: ['openFile'],
      defaultPath: readSettings().debDir || undefined,
    })
    if (r.canceled || !r.filePaths[0]) return null
    const s = readSettings()
    s.debDir = path.dirname(r.filePaths[0])
    writeSettings(s)
    return r.filePaths[0]
  })

  // ── 设置页 ──
  ipcMain.handle('settingsGet', (_e, key: string) => readSettings()[key] ?? '')
  ipcMain.handle('settingsSet', (_e, key: string, value: string) => {
    const s = readSettings()
    s[key] = value
    writeSettings(s)
    return true
  })
  ipcMain.handle('pickDirectory', async (e, def: string) => {
    const win = BrowserWindow.fromWebContents(e.sender)
    const r = await dialog.showOpenDialog(win!, {
      title: '选择目录', properties: ['openDirectory'], defaultPath: def || undefined,
    })
    return r.canceled || !r.filePaths[0] ? null : r.filePaths[0]
  })
  ipcMain.handle('openUserDataDir', () => shell.openPath(app.getPath('userData')))
  // 相机拍照：保存 JPEG 帧到照片目录（设置可自定义；默认 ~/Pictures/ggRobot）
  ipcMain.handle('savePhoto', (_e, data: ArrayBuffer, nameHint: string) => {
    const dir = readSettings().photoDir || path.join(app.getPath('pictures'), 'ggRobot')
    fs.mkdirSync(dir, { recursive: true })
    const ts = new Date()
    const pad = (n: number): string => String(n).padStart(2, '0')
    const fname = `${nameHint}_${ts.getFullYear()}${pad(ts.getMonth() + 1)}${pad(ts.getDate())}_${pad(ts.getHours())}${pad(ts.getMinutes())}${pad(ts.getSeconds())}.jpg`
    const full = path.join(dir, fname)
    fs.writeFileSync(full, new Uint8Array(data))
    return full
  })
  // ── SenseVoice 高精模型下载（~230MB，两文件；URL 前缀可在 settings 覆盖，默认国内镜像）──
  const SV_FILES = ['model.int8.onnx', 'tokens.txt']
  const svDir = (): string => path.join(app.getPath('userData'), 'asr-models', 'sensevoice')
  let svAbort = false
  const sendSv = (win: Electron.WebContents, progress: number, speed: string, done: boolean, error = ''): void => {
    if (!win.isDestroyed()) win.send('asr:progress', { progress, speed, done, error })
  }
  ipcMain.handle('asrSvStatus', () => {
    const dir = svDir()
    return {
      downloaded: SV_FILES.every((f) => fs.existsSync(path.join(dir, f))),
      downloading: !svAbort && fs.existsSync(path.join(dir, '.downloading')),
    }
  })
  ipcMain.handle('asrSvDownload', async (e) => {
    if (!svAbort && fs.existsSync(path.join(svDir(), '.downloading'))) return { ok: false, error: '已有下载进行中' }
    svAbort = false
    fs.mkdirSync(svDir(), { recursive: true })
    fs.writeFileSync(path.join(svDir(), '.downloading'), '1')
    const base = readSettings().asrUrl
      || 'https://hf-mirror.com/csukuangfj/sherpa-onnx-sense-voice-zh-en-ja-ko-yue-int8-2025-09-09/resolve/main'
    try {
      for (let fi = 0; fi < SV_FILES.length; fi++) {
        const f = SV_FILES[fi]
        const r = await fetch(`${base}/${f}`, { redirect: 'follow' })
        if (!r.ok || !r.body) throw new Error(`下载 ${f} 失败: HTTP ${r.status}`)
        const total = Number(r.headers.get('content-length')) || (f.endsWith('.onnx') ? 232 * 1024 * 1024 : 150 * 1024)
        const out = fs.createWriteStream(path.join(svDir(), f + '.part'))
        let recv = 0
        const t0 = Date.now()
        const reader = r.body.getReader()
        for (;;) {
          if (svAbort) throw new Error('已取消')
          const { done, value } = await reader.read()
          if (done) break
          recv += value.byteLength
          out.write(value)
          const mb = recv / 1048576
          const speed = (mb / ((Date.now() - t0) / 1000)).toFixed(1)
          // 进度：onnx 占 99.9%，tokens 收尾
          sendSv(e.sender, Math.min(99, ((fi + recv / total) / SV_FILES.length) * 100), `${mb.toFixed(0)}MB ${speed}MB/s`, false)
        }
        await new Promise((res) => out.end(res))
        fs.renameSync(path.join(svDir(), f + '.part'), path.join(svDir(), f))
      }
      fs.rmSync(path.join(svDir(), '.downloading'))
      sendSv(e.sender, 100, '', true)
      return { ok: true, dir: svDir() }
    } catch (err) {
      fs.rmSync(path.join(svDir(), '.downloading'), { force: true })
      const msg = err instanceof Error ? err.message : String(err)
      sendSv(e.sender, 0, '', true, msg)
      return { ok: false, error: msg }
    }
  })
  ipcMain.handle('asrSvCancel', () => { svAbort = true; return true })
  ipcMain.handle('asrSvDelete', () => {
    svAbort = true
    fs.rmSync(svDir(), { recursive: true, force: true })
    return true
  })

  ipcMain.handle('getAutoLaunch', () => app.getLoginItemSettings().openAtLogin)
  ipcMain.handle('setAutoLaunch', (_e, on: boolean) => {
    app.setLoginItemSettings({ openAtLogin: on })
    return true
  })

  // 装机向导：返回 jobId，进度走 install:progress 事件
  const installers = new Map<string, AgentInstaller | A3Installer>()
  ipcMain.handle('installAgent', async (e, req: InstallRequest) => {
    const jobId = `job-${Date.now()}-${Math.floor(Math.random() * 1e4)}`
    // A3：全新链路（SSH 上传 agent+venv+systemd；新机/已装机通用幂等）；X2：deb+apt 链路
    const installer = req.model === 'a3'
      ? new A3Installer(e.sender)
      : new AgentInstaller(e.sender)
    installers.set(jobId, installer)
    // 异步跑，立即返回 jobId；结果也走 install:progress(done)
    void installer.run(req).finally(() => installers.delete(jobId))
    return { jobId }
  })

  ipcMain.handle('installAbort', (_e, jobId: string) => {
    installers.get(jobId)?.abort()
    return true
  })

  // Agent 批量更新：多机并发（每机独立 AgentInstaller，进度事件带 robotId 路由）
  ipcMain.handle('updateAgents', async (e, req: {
    targets: { robotId: string; name: string; host: string }[]
    username: string; password: string; debPath: string
  }) => {
    const jobs = req.targets.map((t) => {
      const installer = new AgentInstaller(e.sender, t.robotId)
      return installer.runUpdate({
        host: t.host, username: req.username, password: req.password,
        debPath: req.debPath, robotId: t.robotId,
      }).then((r) => ({ robotId: t.robotId, name: t.name, ...r }))
    })
    const results = await Promise.all(jobs)
    return { ok: true, results }
  })

  // 编排编辑独立窗口：按 choreoId 单例（同编排重复开 → 聚焦；不同编排可各开一窗）
  const choreoWins = new Map<string, BrowserWindow>()
  ipcMain.handle('openChoreoEdit', async (_e, choreoId: string) => {
    const exist = choreoWins.get(choreoId)
    if (exist && !exist.isDestroyed()) { exist.show(); exist.focus(); return true }
    const win = new BrowserWindow({
      width: 1040, height: 740, minWidth: 960, minHeight: 660,
      title: '编辑编排',
      frame: false,
      titleBarStyle: 'hidden',
      trafficLightPosition: { x: 12, y: 21 },
      resizable: true,
      show: false,
      webPreferences: {
        preload: path.join(__dirname, '../preload/index.js'),
        sandbox: false, contextIsolation: true, nodeIntegration: false,
      },
    })
    choreoWins.set(choreoId, win)
    win.on('closed', () => choreoWins.delete(choreoId))
    const port = platformPort()
    if (is.dev) {
      const devUrl = process.env['ELECTRON_RENDERER_URL'] as string
      await win.loadURL(`${devUrl}?port=${port}#/choreo-edit?id=${choreoId}`)
    } else {
      await win.loadFile(path.join(__dirname, '../renderer/index.html'),
        { query: { port: String(port) }, hash: `/choreo-edit?id=${choreoId}` })
    }
    win.show()
    return true
  })

  // 建图工作台窗口（单例）：实时点云 + 遥控 + 建图控制
  let mapWin: BrowserWindow | null = null
  ipcMain.handle('openMappingStudio', async () => {
    if (mapWin) { mapWin.show(); mapWin.focus(); return true }
    const win = new BrowserWindow({
      width: 780, height: 620, minWidth: 720, minHeight: 560,
      title: '建图工作台',
      frame: false,
      titleBarStyle: 'hidden',
      trafficLightPosition: { x: 12, y: 21 },
      resizable: true,
      show: false,
      webPreferences: {
        preload: path.join(__dirname, '../preload/index.js'),
        sandbox: false, contextIsolation: true, nodeIntegration: false,
      },
    })
    mapWin = win
    win.on('closed', () => { mapWin = null })
    const port = platformPort()
    if (is.dev) {
      const devUrl = process.env['ELECTRON_RENDERER_URL'] as string
      await win.loadURL(`${devUrl}?port=${port}#/mapping-studio`)
    } else {
      await win.loadFile(path.join(__dirname, '../renderer/index.html'),
        { query: { port: String(port) }, hash: '/mapping-studio' })
    }
    win.show()
    return true
  })

  // 快捷遥控小窗（单例）：机器人下拉 + 六向按住式遥控
  let quickWin: BrowserWindow | null = null
  ipcMain.handle('openQuickCtrl', async () => {
    if (quickWin) { quickWin.show(); quickWin.focus(); return true }   // show 才会前置（mac）
    const win = new BrowserWindow({
      width: 300, height: 440, minWidth: 280, minHeight: 400,
      title: '快捷遥控',
      frame: false,
      titleBarStyle: 'hidden',
      trafficLightPosition: { x: 10, y: 12 },
      resizable: false,
      show: false,
      webPreferences: {
        preload: path.join(__dirname, '../preload/index.js'),
        sandbox: false, contextIsolation: true, nodeIntegration: false,
      },
    })
    quickWin = win
    win.on('closed', () => { quickWin = null })
    const port = platformPort()
    if (is.dev) {
      const devUrl = process.env['ELECTRON_RENDERER_URL'] as string
      await win.loadURL(`${devUrl}?port=${port}#/quick-ctrl`)
    } else {
      await win.loadFile(path.join(__dirname, '../renderer/index.html'),
        { query: { port: String(port) }, hash: '/quick-ctrl' })
    }
    win.show()
    return true
  })
}
