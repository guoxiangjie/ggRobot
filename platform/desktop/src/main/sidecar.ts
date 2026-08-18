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
  const serverRoot = path.resolve(app.getAppPath(), is.dev ? '../../server' : '../../server')
  let file: string
  let args: string[]
  if (is.dev) {
    const venvPy = path.resolve(serverRoot, '.venv/bin/python')
    file = fs.existsSync(venvPy) ? venvPy : 'python3'
    args = ['-m', 'ggplatform']
  } else {
    file = path.join(process.resourcesPath, 'sidecar', 'ggplatform')
    args = ['--port', String(port)]
  }
  const p = spawn(file, args, {
    cwd: serverRoot,
    env: { ...process.env, GG_PLATFORM_PORT: String(port), PYTHONUNBUFFERED: '1' },
  })
  const fd = logFile()
  p.stdout?.on('data', (d) => fs.writeSync(fd, d))
  p.stderr?.on('data', (d) => fs.writeSync(fd, d))
  return p
}

/** 启动 sidecar，就绪（/healthz 200）后回调 */
export function startSidecar(port: number, onReady: (ok: boolean) => void): void {
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
    if (Date.now() > deadline) return onReady(false)
    try {
      const r = await fetch(`http://127.0.0.1:${port}/healthz`, { signal: AbortSignal.timeout(800) })
      if (r.ok) return onReady(true)
    } catch {
      /* 未就绪继续等 */
    }
    await new Promise((r) => setTimeout(r, 300))
    return poll()
  }
  void poll()
}

export function stopSidecar(): void {
  quitting = true
  child?.kill('SIGTERM')
  setTimeout(() => child?.kill('SIGKILL'), 3000)
}

export function platformPort(): number {
  return currentPort
}
