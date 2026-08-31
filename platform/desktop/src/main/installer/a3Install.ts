/**A3 一键装机（全新机器人）— 上传安装包(tar.gz) + venv + systemd + 平台配对

与 X2 装机链路（agentInstall.ts，deb+apt）完全不同：A3 严禁 apt，部署 =
req.debPath = make a3-bundle 产出的安装包；部署 = sftp 上传 → 解压 → 远端 python3.11
venv 装依赖 → systemd user 自启 + linger → 写 conf（平台签发 token）→ 验证。
新机/已装机通用（幂等：重装=升级，token 每次重新签发）。

复用 agentInstall 的 InstallStep 协议（connect/read-sn/register/upload-deb/install/
restart/health-poll/done）——前端 Steps 展示零改动。
*/

import { EventEmitter } from 'events'
import fs from 'fs'
import { Client } from 'ssh2'

import { InstallRequest, InstallStep } from './agentInstall'

export const A3_REMOTE_DIR = '/agibot/data/home/agi/Desktop/ggrobot-a3'
const PIP_MIRROR = 'https://pypi.tuna.tsinghua.edu.cn/simple'

const SYSTEMD_UNIT = (dir: string) => `[Unit]
Description=ggRobot A3 agent
After=network-online.target

[Service]
Type=simple
WorkingDirectory=${dir}
ExecStart=/bin/bash -c 'source /agibot/software/v0/entry/env/env.sh && source /opt/ros/jazzy/setup.bash && source ${dir}/ros2_plugin_proto/share/ros2_plugin_proto/local_setup.bash && exec ${dir}/venv/bin/python -m gg_robot'
Environment=PYTHONUNBUFFERED=1
Environment=LANG=C.UTF-8
Restart=on-failure
RestartSec=3

[Install]
WantedBy=default.target
`

export class A3Installer extends EventEmitter {
  constructor(private win: Electron.WebContents) {
    super()
  }

  private emitStep(s: InstallStep): void {
    if (!this.win.isDestroyed()) this.win.send('install:progress', s)
  }

  /**中断（接口对齐 AgentInstaller；A3 链路暂为 no-op——SSH 命令各自带超时）*/
  abort(): void { /* no-op */ }


  async run(req: InstallRequest): Promise<{ ok: boolean; sn?: string; error?: string }> {
    const conn = new Client()
    try {
      // ── 1. connect ──
      await this.connect(conn, req)
      this.emitStep({ step: 'connect', detail: `已连接 ${req.username}@${req.host}` })

      // ── 2. SN（/agibot/info/sn；health 兜底由调用方探测值传入）──
      this.emitStep({ step: 'read-sn', detail: '读取设备 SN' })
      const snOut = await this.exec(conn, 'cat /agibot/info/sn 2>/dev/null; true', 8_000)
      let sn = snOut.out.split('\n').map((l) => l.trim()).find((v) => v && v.length >= 6) || ''
      if (!sn) sn = `a3-${req.host.split('.').pop()}`
      this.emitStep({ step: 'read-sn', detail: `SN = ${sn}` })

      // ── 3. 平台登记 → 签发 token ──
      this.emitStep({ step: 'register', detail: '平台登记设备' })
      const token = await this.registerAtPlatform(sn, req)

      // ── 4. 上传安装包（单文件 tar.gz，带进度）+ 解压 ──
      if (!req.debPath || !fs.existsSync(req.debPath)) {
        throw new Error('请选择 A3 安装包（make a3-bundle 产出的 ggrobot-a3-agent.tar.gz）')
      }
      this.emitStep({ step: 'upload-deb', detail: '上传安装包', progress: 0 })
      const size = fs.statSync(req.debPath).size
      await this.exec(conn, `mkdir -p ${A3_REMOTE_DIR}`, 8_000)
      await new Promise<void>((resolve, reject) => {
        conn.sftp((er, sftp) => {
          if (er) return reject(er)
          sftp.fastPut(req.debPath!, `${A3_REMOTE_DIR}/agent.tar.gz`, {
            step: (t: number) => this.emitStep({
              step: 'upload-deb', progress: Math.min(1, t / size),
              detail: `上传 ${(t / 1024).toFixed(0)}/${(size / 1024).toFixed(0)} KB` }),
          }, (e2: unknown) => (e2 ? reject(e2) : resolve()))
        })
      })
      this.emitStep({ step: 'upload-deb', progress: 1, detail: '解压安装包…' })
      const untar = await this.exec(conn,
        `cd ${A3_REMOTE_DIR} && tar -xzf agent.tar.gz && ls requirements.txt >/dev/null && echo GG_UNTAR_OK`,
        60_000)
      if (!untar.out.includes('GG_UNTAR_OK')) {
        throw new Error(`解压失败（包结构异常）: ${(untar.err || untar.out).slice(-200)}`)
      }

      // ── 5. venv + 依赖（python3.11：Jazzy rclpy 是 3.11 包）──
      this.emitStep({ step: 'install', detail: 'venv + 依赖安装（1-2 分钟）' })
      const inst = await this.exec(conn,
        `cd ${A3_REMOTE_DIR} && ` +
        `{ [ -x venv/bin/python ] && venv/bin/python --version 2>&1 | grep -q 'Python 3.11' || rm -rf venv; } && ` +
        `[ -x venv/bin/python ] || python3.11 -m venv venv; ` +
        `./venv/bin/pip install -q -r requirements.txt -i ${PIP_MIRROR} && ` +
        `./venv/bin/pip install -q --force-reinstall ./a3_aimdk-3.2.0-py3-none-any.whl && echo GG_OK`,
        420_000)
      if (!inst.out.includes('GG_OK')) {
        throw new Error(`依赖安装失败: ${(inst.err || inst.out).slice(-300)}`)
      }

      // ── 6. conf（平台 token）+ systemd 自启 + linger ──
      this.emitStep({ step: 'upload-token', detail: '写入配对令牌与自启服务' })
      const conf = `token=${token}\nsn=${sn}\nmodel=a3-ultra\nport=8300\n`
      await this.exec(conn, 'mkdir -p ~/.config ~/.config/systemd/user', 5_000)
      await this.writeRemoteFile(conn, '/home/agi/.config/ggrobot-agent.conf', conf)
      await this.writeRemoteFile(conn,
        '/home/agi/.config/systemd/user/ggrobot-a3.service', SYSTEMD_UNIT(A3_REMOTE_DIR))
      await this.exec(conn, 'loginctl enable-linger agi 2>/dev/null || sudo -n loginctl enable-linger agi 2>/dev/null || true', 8_000)

      // ── 7. 启动 ──
      this.emitStep({ step: 'restart', detail: '启动 agent 服务（systemd）' })
      const r = await this.exec(conn,
        `export XDG_RUNTIME_DIR=\${XDG_RUNTIME_DIR:-/run/user/$(id -u)}; ` +
        `systemctl --user daemon-reload && systemctl --user enable ggrobot-a3 >/dev/null 2>&1; ` +
        `systemctl --user restart ggrobot-a3`, 20_000)
      if (r.code !== 0) throw new Error(`服务启动失败: ${(r.err || r.out).slice(-200)}`)
      conn.end()

      // ── 8. 就绪验证（health + token）──
      this.emitStep({ step: 'health-poll', detail: '验证配对' })
      const ok = await this.pollVerify(req.host, token, 90_000, (m) =>
        this.emitStep({ step: 'health-poll', detail: m }))
      if (!ok) throw new Error('配对验证失败（health/token 不通）')

      this.emitStep({ step: 'done', detail: `一键装机成功 SN=${sn}` })
      return { ok: true, sn }
    } catch (e) {
      const msg = e instanceof Error ? e.message : String(e)
      this.emitStep({ step: 'done', error: msg })
      try { conn.end() } catch { /* */ }
      return { ok: false, error: msg }
    }
  }

  // ── 工具（与 agentInstall 同款行为）──

  private connect(conn: Client, req: InstallRequest): Promise<void> {
    return new Promise((resolve, reject) => {
      conn.on('ready', () => resolve())
      conn.on('error', reject)
      conn.connect({
        host: req.host, port: 22,
        username: req.username, password: req.password,
        readyTimeout: 12_000,
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

  private writeRemoteFile(conn: Client, remote: string, content: string): Promise<void> {
    return new Promise((resolve, reject) => {
      conn.sftp((er, sftp) => {
        if (er) return reject(er)
        sftp.writeFile(remote, content, (e2) => (e2 ? reject(e2) : resolve()))
      })
    })
  }

  /** 平台登记换 token（pair/register：upsert by SN，记 IP；X2 同款） */
  private async registerAtPlatform(sn: string, req: InstallRequest): Promise<string> {
    const reg = await fetch(`http://127.0.0.1:${req.platformPort}/api/pair/register`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ sn, ip: req.host, name: req.name, model: 'a3-ultra' }),
      signal: AbortSignal.timeout(5000),
    })
    if (!reg.ok) throw new Error(`平台登记失败 ${reg.status}`)
    const j = (await reg.json()) as { token?: string }
    if (!j.token) throw new Error('平台未返回 token')
    return j.token
  }

  private async pollVerify(host: string, token: string, timeoutMs: number, onMsg: (m: string) => void):
    Promise<boolean> {
    const deadline = Date.now() + timeoutMs
    while (Date.now() < deadline) {
      try {
        const r = await fetch(`http://${host}:8300/api/health`, { signal: AbortSignal.timeout(3000) })
        if (r.ok) {
          const j = await r.json() as { sn?: string }
          if (j.sn && j.sn !== 'unpaired') {
            const caps = await fetch(`http://${host}:8300/api/capabilities`, {
              headers: { Authorization: `Bearer ${token}` },
              signal: AbortSignal.timeout(4000),
            })
            if (caps.ok) return true
            onMsg('agent 就绪，token 验证中…')
          }
        }
      } catch { /* 未就绪继续 */ }
      onMsg('等待 agent 就绪…')
      await new Promise((r2) => setTimeout(r2, 2500))
    }
    return false
  }
}
