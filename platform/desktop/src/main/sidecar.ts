/** FastAPI sidecar 子进程管理 — dev 直跑 venv python，prod 跑打包二进制 */

import { spawn, ChildProcess } from 'child_process'
import { app } from 'electron'
import net from 'net'
import path from 'path'
import fs from 'fs'
import { is } from '@electron-toolkit/utils'

const BASE_PORT = 8310
let child: ChildProcess | null = null
let restarts = 0
let currentPort = BASE_PORT
let quitting = false

function isFree(port: number): Promise<boolean> {
  return new Promise((resolve) => {
    const srv = net.createServer()
    srv.once('error', () => resolve(false))
    srv.once('listening', () => srv.close(() => resolve(true)))
    srv.listen(port, '127.0.0.1')
  })
}

/** 端口协商：8310 起被占递增（≤20） */
export async function negotiatePort(): Promise<number> {
  for (let p = BASE_PORT; p < BASE_PORT + 20; p++) {
    if (await isFree(p)) return p
  }
  throw new Error('no free port in 8310-8330')
}

function logFile(): number {
  const dir = path.join(app.getPath('userData'), 'logs')
  fs.mkdirSync(dir, { recursive: true })
  return fs.openSync(path.join(dir, 'sidecar.log'), 'a')
}

function spawnOnce(port: number): ChildProcess {
  let file: string
  let args: string[]
  let cwd: string
  if (is.dev) {
    const serverRoot = path.resolve(app.getAppPath(), '../../server')
    const venvPy = path.resolve(serverRoot, '.venv/bin/python')
    file = fs.existsSync(venvPy) ? venvPy : 'python3'
    args = ['-m', 'ggplatform']
    cwd = serverRoot
  } else {
    // PyInstaller --onedir：可执行文件在同名目录内
    file = path.join(process.resourcesPath, 'sidecar', 'ggplatform', 'ggplatform')
    args = ['--port', String(port)]
    cwd = path.dirname(file)   // prod 无 server 源码目录，cwd 用二进制所在目录
  }
  const p = spawn(file, args, {
    cwd,
    env: {
      ...process.env,
      GG_PLATFORM_PORT: String(port),
      PYTHONUNBUFFERED: '1',
      // 数据库放 userData（.app 包内可能只读且重装即丢）
      GG_PLATFORM_DB: path.join(app.getPath('userData'), 'data.db'),
    },
  })
  const fd = logFile()
  p.on('error', (e) => {
    try { fs.writeSync(fd, `[spawn-error] ${e.message}\n`) } catch { /* */ }
    console.error('[sidecar] spawn 失败:', e)
  })
  p.stdout?.on('data', (d) => fs.writeSync(fd, d))
  p.stderr?.on('data', (d) => fs.writeSync(fd, d))
  return p
}

/** 启动 sidecar，就绪（/healthz 200）后回调。
 *  单例复用：若已有 ggplatform 在 8310-8330 任一端口活着（其他 App 窗口留下的），
 *  直接复用它 — 多窗口共享同一 sidecar/DB，杜绝多实例多库打架。 */
export async function startSidecar(onReady: (ok: boolean, port: number) => void): Promise<void> {
  // 1. 探测已存在的 sidecar（复用）
  for (let p = BASE_PORT; p < BASE_PORT + 20; p++) {
    try {
      const r = await fetch(`http://127.0.0.1:${p}/healthz`, { signal: AbortSignal.timeout(500) })
      if (r.ok) {
        const j = (await r.json()) as { service?: string }
        if (j.service === 'ggplatform') {
          currentPort = p
          console.log(`[sidecar] 复用已运行实例 :${p}`)
          return onReady(true, p)
        }
      }
    } catch { /* 端口无实例，继续 */ }
  }

  // 2. 无实例 → 协商端口 + 拉起
  const port = await negotiatePort()
  bootAndPoll(port, onReady)
}

function bootAndPoll(port: number, onReady: (ok: boolean, port: number) => void): void {
  currentPort = port

  const boot = (): boolean => {
    if (quitting) return false
    child = spawnOnce(port)
    child.on('exit', (_code) => {
      if (!quitting && restarts < 5) {
        restarts++
        console.warn(`[sidecar] 退出，${restarts * 1000}ms 后重启（第 ${restarts} 次）`)
        setTimeout(() => boot(), restarts * 1000)
      }
    })
    return true
  }
  if (!boot()) return

  // 就绪探测（--onedir 首启也要解压，给足 15s）
  const deadline = Date.now() + 15_000
  const poll = async (): Promise<void> => {
    if (Date.now() > deadline) return onReady(false, port)
    try {
      const r = await fetch(`http://127.0.0.1:${port}/healthz`, { signal: AbortSignal.timeout(800) })
      if (r.ok) return onReady(true, port)
    } catch {
      /* 未就绪继续等 */
    }
    await new Promise((r) => setTimeout(r, 300))
    return poll()
  }
  void poll()
}

/** 退出处理：不杀 sidecar（其他窗口可能共用，下个 App 秒连复用） */
export function stopSidecar(): void {
  quitting = true
  child?.removeAllListeners('exit')
}

export function platformPort(): number {
  return currentPort
}
