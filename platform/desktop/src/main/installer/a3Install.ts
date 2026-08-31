/**A3 一键装机（全新机器人）— SSH 上传 agent（源码+SDK 协议件）+ venv + systemd + 平台配对

与 X2 装机链路（agentInstall.ts，deb+apt）完全不同：A3 严禁 apt，部署 =
sftp 递归上传 agents/a3 源码 + prebuilt（whl/ros2_plugin_proto）→ 远端 python3.11
venv 装依赖 → systemd user 自启 + linger → 写 conf（平台签发 token）→ 验证。
新机/已装机通用（幂等：重装=升级，token 每次重新签发）。

复用 agentInstall 的 InstallStep 协议（connect/read-sn/register/upload-deb/install/
restart/health-poll/done）——前端 Steps 展示零改动。
*/

import { EventEmitter } from 'events'
import fs from 'fs'
import path from 'path'
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

  /**装机资源根：dev=项目目录；打包版=resources/a3-agent（electron-builder extraResources）*/
  private assetsRoot(): string {
    const devRoot = path.resolve(__dirname, '../../../../../../agents/a3')
    if (fs.existsSync(path.join(devRoot, 'requirements.txt'))) return devRoot
    // extraResources 布局：resources/a3-agent/{gg_robot,config,requirements.txt,a3_aimdk.whl,ros2_plugin_proto}
    return path.join(process.resourcesPath ?? '', 'a3-agent')
  }

  private sdkPrebuilt(): string {
    const dev = path.resolve(__dirname, '../../../../../../agibot_a3_Ultra_aimdk-dev3.2/prebuilt')
    if (fs.existsSync(dev)) return dev
    return path.join(process.resourcesPath ?? '', 'a3-agent')   // 打包版与 agent 资源同根
  }

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

      // ── 4. 上传 agent（源码 + SDK 协议件 ~3MB）──
      this.emitStep({ step: 'upload-deb', detail: '上传 agent 与协议件（~3MB）', progress: 0 })
      const assets = this.assetsRoot()
      const prebuilt = this.sdkPrebuilt()
      await this.exec(conn, `mkdir -p ${A3_REMOTE_DIR}/config`, 8_000)
      let done = 0
      const files: Array<[string, string]> = []   // [local, remote]
      const walk = (localDir: string, rel: string): void => {
        for (const ent of fs.readdirSync(localDir, { withFileTypes: true })) {
          if (ent.name === '__pycache__' || ent.name === '.venv' || ent.name === 'deploy') continue
          const lp = path.join(localDir, ent.name)
          const rp = `${A3_REMOTE_DIR}/${rel}/${ent.name}`
          if (ent.isDirectory()) { walk(lp, `${rel}/${ent.name}`) } else files.push([lp, rp])
        }
      }
      walk(path.join(assets, 'gg_robot'), 'gg_robot')
      walk(path.join(assets, 'config'), 'config')
      files.push([path.join(assets, 'requirements.txt'), `${A3_REMOTE_DIR}/requirements.txt`])
      const whl = fs.existsSync(path.join(prebuilt, 'a3_aimdk-3.2.0-py3-none-any.whl'))
        ? path.join(prebuilt, 'a3_aimdk-3.2.0-py3-none-any.whl')
        : path.join(this.assetsRoot(), 'a3_aimdk-3.2.0-py3-none-any.whl')   // 打包版：与 agent 资产同根
      files.push([whl, `${A3_REMOTE_DIR}/a3_aimdk.whl`])
      const protoDir = fs.existsSync(path.join(prebuilt, 'ros2_plugin_proto_aarch64'))
        ? path.join(prebuilt, 'ros2_plugin_proto_aarch64')
        : path.join(this.assetsRoot(), 'ros2_plugin_proto_aarch64')
      walk(protoDir, 'ros2_plugin_proto')
      for (const [lp, rp] of files) {
        await this.exec(conn, `mkdir -p "$(dirname "${rp}")"`, 5_000)
        await this.upload(conn, lp, rp)
        done++
        this.emitStep({ step: 'upload-deb', progress: done / files.length, detail: `上传 ${done}/${files.length}` })
      }

      // ── 5. venv + 依赖（python3.11：Jazzy rclpy 是 3.11 包）──
      this.emitStep({ step: 'install', detail: 'venv + 依赖安装（1-2 分钟）' })
      const inst = await this.exec(conn,
        `cd ${A3_REMOTE_DIR} && ` +
        `{ [ -x venv/bin/python ] && venv/bin/python --version 2>&1 | grep -q 'Python 3.11' || rm -rf venv; } && ` +
        `[ -x venv/bin/python ] || python3.11 -m venv venv; ` +
        `./venv/bin/pip install -q -r requirements.txt -i ${PIP_MIRROR} && ` +
        `./venv/bin/pip install -q --force-reinstall ./a3_aimdk.whl && echo GG_OK`,
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

  private upload(conn: Client, local: string, remote: string): Promise<void> {
    return new Promise((resolve, reject) => {
      conn.sftp((er, sftp) => {
        if (er) return reject(er)
        sftp.fastPut(local, remote, (e2) => (e2 ? reject(e2) : resolve()))
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

  private async registerAtPlatform(sn: string, req: InstallRequest): Promise<string> {
    const r = await fetch(`http://127.0.0.1:${req.platformPort}/api/robots`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ sn, name: req.name || undefined, model: 'a3-ultra', port: 8300 }),
      signal: AbortSignal.timeout(5000),
    })
    if (r.status === 409) {   // 已登记 → 换新 token（重装=重新配对）
      const list = await (await fetch(`http://127.0.0.1:${req.platformPort}/api/robots`,
        { signal: AbortSignal.timeout(5000) })).json() as { robots?: Array<{ id: string; sn: string }> }
      const exist = list.robots?.find((x) => x.sn === sn)
      if (!exist) throw new Error('登记冲突但未找到原记录')
      const rot = await (await fetch(`http://127.0.0.1:${req.platformPort}/api/robots/${exist.id}/token-rotate`,
        { method: 'POST', signal: AbortSignal.timeout(5000) })).json() as { token?: string }
      if (!rot.token) throw new Error('token 轮换失败')
      if (req.name) {
        await fetch(`http://127.0.0.1:${req.platformPort}/api/robots/${exist.id}`, {
          method: 'PATCH', headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ name: req.name }), signal: AbortSignal.timeout(5000),
        }).catch(() => { /* 改名失败无妨 */ })
      }
      return rot.token
    }
    if (!r.ok) throw new Error(`平台登记失败 HTTP ${r.status}`)
    const j = await r.json() as { token?: string }
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
