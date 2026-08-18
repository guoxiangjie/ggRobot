/**SSH 装机向导（一键到底）— connect → SSH直读SN → 平台登记换token → 推token+deb → 免密apt → 双确认

sudoers 铁律：远程只允许 `sudo -n apt install`（免密白名单仅 /usr/bin/apt）；
systemctl/写 /etc 全在 deb 的 postinst 内（apt 安装时以 root 执行）。
token 下发走 sftp /tmp/gg-token → postinst 吸收，绕开 sudo tee。
*/

import { Client } from 'ssh2'
import fs from 'fs'
import { EventEmitter } from 'events'

export interface InstallRequest {
  host: string
  username: string   // 通常 agi
  password: string
  debPath: string    // 本地 deb 路径
  name: string       // 机器人别名（登记用）
  platformPort: number  // 平台 sidecar 端口（登记换 token）
}

export interface InstallStep {
  step: 'connect' | 'read-sn' | 'register' | 'stop-legacy' | 'upload-deb' | 'upload-token'
      | 'install' | 'health-poll' | 'done'
  detail?: string
  progress?: number   // 0-1
  error?: string
}

export class AgentInstaller extends EventEmitter {
  private aborted = false

  constructor(private win: Electron.WebContents) {
    super()
  }

  private emitStep(s: InstallStep): void {
    if (!this.win.isDestroyed()) this.win.send('install:progress', s)
  }

  abort(): void {
    this.aborted = true
  }

  async run(req: InstallRequest): Promise<{ ok: boolean; sn?: string; error?: string }> {
    const conn = new Client()
    try {
      // ── 1. connect ──
      await this.connect(conn, req)
      this.emitStep({ step: 'connect', detail: `已连接 ${req.username}@${req.host}` })

      // ── 2. SSH 直读 SN（AGIBOT_SN 整机 SN，兜底 Jetson 模组 SN）──
      this.emitStep({ step: 'read-sn', detail: '读取设备 SN' })
      const snOut = await this.exec(conn,
        `runuser -u ${req.username} -- bash -lc 'echo $AGIBOT_SN' 2>/dev/null || cat /proc/device-tree/serial-number 2>/dev/null || true`,
        10_000)
      let sn = snOut.out.trim().split('\n').pop()?.trim() ?? ''
      if (!sn || sn.startsWith('$')) {
        sn = `x2-${snOut.out.trim() || req.host.split('.').pop()}`
      }
      if (this.aborted) throw new Error('aborted')
      this.emitStep({ step: 'read-sn', detail: `SN = ${sn}` })

      // ── 3. 平台登记 → 换 token ──
      this.emitStep({ step: 'register', detail: '平台登记设备' })
      const reg = await fetch(`http://127.0.0.1:${req.platformPort}/api/pair/register`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ sn, ip: req.host, name: req.name }),
        signal: AbortSignal.timeout(5000),
      })
      if (!reg.ok) throw new Error(`平台登记失败 ${reg.status}`)
      const { token } = (await reg.json()) as { token: string }

      // ── 4. 停 1.0 旧服务（普通 pkill，容忍失败）──
      this.emitStep({ step: 'stop-legacy', detail: '停止 1.0 旧服务（如在跑）' })
      await this.exec(conn, 'pkill -f "python -m gg_robot" 2>/dev/null; sleep 1; true', 8000)

      // ── 5. 推 deb（sftp fastPut 带进度）──
      const remoteDeb = `/tmp/${baseName(req.debPath)}`
      this.emitStep({ step: 'upload-deb', detail: `上传 ${remoteDeb}`, progress: 0 })
      await this.upload(conn, req.debPath, remoteDeb, (p) =>
        this.emitStep({ step: 'upload-deb', progress: p }))

      // ── 6. 推 token（/tmp/gg-token，postinst 吸收）──
      this.emitStep({ step: 'upload-token', detail: '下发配对 token' })
      await this.writeRemoteFile(conn, '/tmp/gg-token', token + '\n')

      // ── 7. 免密安装（postinst: venv+SN烧录+conf+systemd 启动）──
      this.emitStep({ step: 'install', detail: 'apt install（依赖安装 + systemd 注册启动）' })
      const inst = await this.exec(conn, `sudo -n apt install -y --reinstall ${remoteDeb}`, 300_000)
      if (inst.code !== 0) {
        throw new Error(`apt install 失败 (exit ${inst.code}): ${inst.err.slice(-500)}`)
      }

      conn.end()

      // ── 8. 双确认（health 免token + status 带token 验证配对成功）──
      this.emitStep({ step: 'health-poll', detail: '等待 agent 就绪并验证配对（最长 3 分钟）' })
      const result = await this.pollAndVerify(req.host, token, 180_000)
      if (!result.ok) throw new Error(`agent 未就绪: ${result.error}`)

      this.emitStep({ step: 'done', detail: `安装成功 SN=${sn}` })
      return { ok: true, sn }
    } catch (e) {
      const msg = e instanceof Error ? e.message : String(e)
      this.emitStep({ step: 'done', error: msg })
      try { conn.end() } catch { /* */ }
      return { ok: false, error: msg }
    }
  }

  private connect(conn: Client, req: InstallRequest): Promise<void> {
    return new Promise((resolve, reject) => {
      conn
        .on('ready', () => resolve())
        .on('error', reject)
        .connect({
          host: req.host,
          username: req.username,
          password: req.password,
          readyTimeout: 10_000,
        })
    })
  }

  private exec(conn: Client, cmd: string, timeoutMs: number):
    Promise<{ code: number; out: string; err: string }> {
    return new Promise((resolve, reject) => {
      const timer = setTimeout(() => reject(new Error(`命令超时: ${cmd.slice(0, 60)}`)), timeoutMs)
      conn.exec(cmd, { pty: false }, (er, stream) => {
        if (er) { clearTimeout(timer); return reject(er) }
        let out = '', errS = ''
        stream.on('data', (d: Buffer) => (out += d.toString()))
        stream.stderr.on('data', (d: Buffer) => (errS += d.toString()))
        stream.on('close', (code: number) => {
          clearTimeout(timer)
          resolve({ code: code ?? 0, out, err: errS })
        })
      })
    })
  }

  private upload(conn: Client, local: string, remote: string, onPct: (p: number) => void):
    Promise<void> {
    return new Promise((resolve, reject) => {
      conn.sftp((er, sftp) => {
        if (er) return reject(er)
        const size = fs.statSync(local).size
        sftp.fastPut(local, remote, {
          step: (transferred: number) => onPct(Math.min(1, transferred / size)),
        }, (e2) => (e2 ? reject(e2) : resolve()))
      })
    })
  }

  private writeRemoteFile(conn: Client, remote: string, content: string): Promise<void> {
    return new Promise((resolve, reject) => {
      conn.sftp((er, sftp) => {
        if (er) return reject(er)
        const buf = Buffer.from(content, 'utf8')
        const stream = sftp.createWriteStream(remote)
        stream.on('error', reject)
        stream.on('close', () => resolve())
        stream.end(buf)
      })
    })
  }

  /**health 通 + token 验证通过 = 装机配对闭环 */
  private async pollAndVerify(host: string, token: string, timeoutMs: number):
    Promise<{ ok: boolean; error?: string }> {
    const deadline = Date.now() + timeoutMs
    let lastErr = ''
    while (Date.now() < deadline && !this.aborted) {
      try {
        const h = await fetch(`http://${host}:8300/api/health`, { signal: AbortSignal.timeout(1500) })
        if (h.ok) {
          const s = await fetch(`http://${host}:8300/api/status`, {
            headers: { Authorization: `Bearer ${token}` },
            signal: AbortSignal.timeout(2000),
          })
          if (s.ok) return { ok: true }
          lastErr = `health 通但 token 校验 ${s.status}`
        } else {
          lastErr = `health ${h.status}`
        }
      } catch (e) {
        lastErr = e instanceof Error ? e.message : String(e)
      }
      await new Promise((r) => setTimeout(r, 3000))
    }
    return { ok: false, error: lastErr }
  }
}

function baseName(p: string): string {
  return p.split('/').pop() ?? p
}
