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
  model?: 'x2' | 'a3'
}


export interface InstallStep {
  step: 'connect' | 'pc3-setup' | 'read-sn' | 'register' | 'stop-legacy' | 'upload-deb' | 'upload-token'
      | 'install' | 'restart' | 'health-poll' | 'done'
  detail?: string
  progress?: number   // 0-1
  error?: string
  robotId?: string    // 批量更新时的机器路由（装机向导无此字段）
}

export interface UpdateRequest {
  host: string
  username: string
  password: string
  debPath: string
  robotId?: string    // 进度事件路由
}

export class AgentInstaller extends EventEmitter {
  private aborted = false

  constructor(private win: Electron.WebContents, private robotId = '') {
    super()
  }

  private emitStep(s: InstallStep): void {
    if (!this.win.isDestroyed()) this.win.send('install:progress', { ...s, robotId: this.robotId || undefined })
  }

  abort(): void {
    this.aborted = true
  }

  async run(req: InstallRequest): Promise<{ ok: boolean; sn?: string; error?: string }> {
    // 预探测：agent 已在跑 → 轻量配对（免装 deb，秒级）；否则完整装机
    const existing = await this.probeAgent(req.host)
    return existing ? this.runLight(req, existing) : this.runFull(req)
  }

  /**Agent 更新（已配对机）：connect → 推 deb → apt install（postinst 自动重启）→ 等恢复 + 版本核对
   *  不动 SN/token/登记——配对关系保持；apt 原子性保证失败时旧版本仍在跑。 */
  async runUpdate(req: UpdateRequest): Promise<{ ok: boolean; version?: string; error?: string }> {
    const wantVer = baseName(req.debPath).match(/_([\d][\w.~-]*?)(?:[-_~][^_]*?)?\.deb$/)?.[1] ?? ''
    const conn = new Client()
    try {
      await this.connect(conn, { ...req, name: '', platformPort: 0 } as InstallRequest)
      this.emitStep({ step: 'connect', detail: `已连接 ${req.username}@${req.host}` })

      const remoteDeb = `/tmp/${baseName(req.debPath)}`
      this.emitStep({ step: 'upload-deb', detail: `上传 ${baseName(req.debPath)}`, progress: 0 })
      await this.upload(conn, req.debPath, remoteDeb, (p) =>
        this.emitStep({ step: 'upload-deb', progress: p }))

      this.emitStep({ step: 'install', detail: 'apt install（服务自动重启）' })
      // --allow-downgrades：版本号来自 git describe，历史包编号可能更高；也支持主动回退版本
      const inst = await this.exec(conn, `sudo -n apt install -y --reinstall --allow-downgrades ${remoteDeb}`, 300_000)
      if (inst.code !== 0) {
        throw new Error(`apt install 失败 (exit ${inst.code}): ${inst.err.slice(-500)}`)
      }
      conn.end()

      // 等待 agent 重启恢复 + 版本核对（apt 后服务重启约需 5-30s）
      this.emitStep({ step: 'health-poll', detail: '等待服务重启就绪…' })
      const t0 = Date.now()
      for (;;) {
        if (this.aborted) throw new Error('aborted')
        const h = await this.probeHealth(req.host)
        if (h) {
          const got = h.version ?? ''
          if (!wantVer || got === wantVer) {
            this.emitStep({ step: 'health-poll', detail: `已恢复 · agent ${got || '未知版本'}` })
            this.emitStep({ step: 'done', detail: `更新成功 → ${got || wantVer}` })
            return { ok: true, version: got }
          }
          // 恢复了但版本还是旧的：postinst 可能未重启服务，再给一次重启
          this.emitStep({ step: 'health-poll', detail: `版本仍为 ${got}，尝试重启服务…` })
          await this.forceRestart(req)
          this.emitStep({ step: 'health-poll', detail: '等待服务重启就绪…' })
        }
        if (Date.now() - t0 > 120_000) {
          throw new Error('超时：agent 未恢复（可手动检查机器人 systemd 服务）')
        }
        await new Promise((r) => setTimeout(r, 3000))
      }
    } catch (e) {
      const msg = e instanceof Error ? e.message : String(e)
      this.emitStep({ step: 'done', error: msg })
      try { conn.end() } catch { /* */ }
      return { ok: false, error: msg }
    }
  }

  /**health 探测（返回带 version 的完整对象） */
  private async probeHealth(host: string): Promise<{ sn?: string; version?: string } | null> {
    try {
      const r = await fetch(`http://${host}:8300/api/health`, { signal: AbortSignal.timeout(2500) })
      if (r.ok) return (await r.json()) as { sn?: string; version?: string }
    } catch { /* */ }
    return null
  }

  /**兜底：SSH 重启 user 服务（版本未变时 postinst 可能没触发重启） */
  private async forceRestart(req: UpdateRequest): Promise<void> {
    const conn = new Client()
    try {
      await this.connect(conn, { ...req, name: '', platformPort: 0 } as InstallRequest)
      await this.exec(conn,
        `export XDG_RUNTIME_DIR=\${XDG_RUNTIME_DIR:-/run/user/$(id -u)}; systemctl --user restart ggrobot-agent || true`, 20_000)
      conn.end()
    } catch { /* 尽力而为 */ }
  }

  /** agent 已安装且存活时的轻量配对：register → SSH 直写 conf → systemctl --user restart */
  private async runLight(req: InstallRequest, health: { sn: string; model?: string }): Promise<{ ok: boolean; sn?: string; error?: string }> {
    const conn = new Client()
    try {
      await this.connect(conn, req)
      this.emitStep({ step: 'connect', detail: `已连接（检测到 agent 运行中，走快速配对）` })

      // SN：优先实时读（bash -ic AGIBOT_SN），失败用 health 上报值
      let sn = health.sn
      if (sn === 'unpaired' || !sn) {
        const out = await this.exec(conn,
          `cat /agibot/info/sn 2>/dev/null; bash -ic 'echo $AGIBOT_SN' 2>/dev/null; tr -d '\\0' < /proc/device-tree/serial-number 2>/dev/null; true`, 10_000)
        sn = out.out.split('\n').map((l) => l.trim().replace(/\0/g, '')).find((v) => v && !v.startsWith('$') && v.length >= 6) ?? sn
      }
      this.emitStep({ step: 'read-sn', detail: `SN = ${sn}` })

      this.emitStep({ step: 'register', detail: '平台登记设备' })
      const token = await this.registerAtPlatform(sn, req)

      // SSH 直写 conf（agi 域 ~/.config/ggrobot-agent.conf — 无需 root）
      this.emitStep({ step: 'upload-token', detail: '写入配对令牌' })
      const isA3 = req.model === 'a3' || health.model?.startsWith('a3')
      const conf = `token=${token}\nsn=${sn}\nmodel=${isA3 ? 'a3-ultra' : 'x2'}\nport=8300\n`
      await this.exec(conn, 'mkdir -p ~/.config', 5000)
      await this.writeRemoteFile(conn, '/home/agi/.config/ggrobot-agent.conf', conf)

      // agi 自己的 user 服务自己重启（无 sudo）
      const svc = isA3 ? 'ggrobot-a3' : 'ggrobot-agent'
      this.emitStep({ step: 'restart', detail: `重启 agent 服务（${svc}）` })
      const r = await this.exec(conn,
        `export XDG_RUNTIME_DIR=\${XDG_RUNTIME_DIR:-/run/user/$(id -u)}; systemctl --user restart ${svc}`, 20_000)
      if (r.code !== 0) throw new Error(`服务重启失败: ${r.err.slice(-200)}`)
      conn.end()

      this.emitStep({ step: 'health-poll', detail: '验证配对' })
      const result = await this.pollAndVerify(req.host, token, 60_000, (msg) =>
        this.emitStep({ step: 'health-poll', detail: msg }))
      if (!result.ok) throw new Error(`配对验证失败: ${result.error}`)

      this.emitStep({ step: 'done', detail: `快速配对成功 SN=${sn}` })
      return { ok: true, sn }
    } catch (e) {
      const msg = e instanceof Error ? e.message : String(e)
      this.emitStep({ step: 'done', error: msg })
      try { conn.end() } catch { /* */ }
      return { ok: false, error: msg }
    }
  }

  /** 完整装机（首次/agent 未运行） */
  private async runFull(req: InstallRequest): Promise<{ ok: boolean; sn?: string; error?: string }> {
    if (!req.debPath) {
      this.emitStep({ step: 'done', error: '机器人上没有 agent 且未选择 deb 安装包' })
      return { ok: false, error: 'missing deb' }
    }
    const conn = new Client()
    try {
      // ── 1. connect ──
      await this.connect(conn, req)
      this.emitStep({ step: 'connect', detail: `已连接 ${req.username}@${req.host}` })

      // ── 1.5 PC3 免密（新机器人开箱即用媒体上传；已通则跳过）──
      await this.setupPc3Keyless(conn, req)

      // ── 2. SSH 直读 SN（bash -ic 交互模拟：AGIBOT_SN 定义在 .bashrc 交互段，非交互读不到）──
      this.emitStep({ step: 'read-sn', detail: '读取设备 SN' })
      const snOut = await this.exec(conn,
        // ssh2 会话已以 agi 登录，直跑 bash -ic（交互模拟读 .bashrc 交互段）——勿套 runuser
        `bash -ic 'echo $AGIBOT_SN' 2>/dev/null; ` +
        `grep -h '^AGIBOT_SN=' /etc/environment 2>/dev/null | head -1 | cut -d= -f2; ` +
        `tr -d '\\0' < /proc/device-tree/serial-number 2>/dev/null; true`,
        10_000)
      let sn = ''
      for (const line of snOut.out.split('\n')) {
        const v = line.trim().replace(/\0/g, '')
        if (v && !v.startsWith('$') && v.length >= 6) { sn = v; break }   // 取第一个有效来源（AGIBOT_SN 优先）
      }
      if (!sn) sn = `x2-${req.host.split('.').pop()}`
      if (this.aborted) throw new Error('aborted')
      this.emitStep({ step: 'read-sn', detail: `SN = ${sn}` })

      // ── 3. 平台登记 → 换 token ──
      this.emitStep({ step: 'register', detail: '平台登记设备' })
      const token = await this.registerAtPlatform(sn, req)

      // ── 4. 停 1.0 旧服务（普通 pkill，容忍失败）──
      this.emitStep({ step: 'stop-legacy', detail: '停止 1.0 旧服务（如在跑）' })
      await this.exec(conn, 'pkill -f "python -m gg_robot" 2>/dev/null; sleep 1; true', 8000)

      // ── 5. 推 deb（sftp fastPut 带进度）──
      const remoteDeb = `/tmp/${baseName(req.debPath)}`
      this.emitStep({ step: 'upload-deb', detail: `上传 ${remoteDeb}`, progress: 0 })
      await this.upload(conn, req.debPath, remoteDeb, (p) =>
        this.emitStep({ step: 'upload-deb', progress: p }))

      // ── 6. 推 token + SN（/tmp/gg-token、/tmp/gg-sn，postinst 吸收——统一 SN 来源）──
      this.emitStep({ step: 'upload-token', detail: '下发配对 token 与 SN' })
      await this.writeRemoteFile(conn, '/tmp/gg-token', token + '\n')
      await this.writeRemoteFile(conn, '/tmp/gg-sn', sn + '\n')

      // ── 7. 免密安装（postinst: venv+SN烧录+conf+systemd 启动）──
      this.emitStep({ step: 'install', detail: 'apt install（依赖安装 + systemd 注册启动）' })
      const inst = await this.exec(conn, `sudo -n apt install -y --reinstall --allow-downgrades ${remoteDeb}`, 300_000)
      if (inst.code !== 0) {
        throw new Error(`apt install 失败 (exit ${inst.code}): ${inst.err.slice(-500)}`)
      }

      conn.end()

      // ── 8. 双确认（health 免token + status 带token 验证配对成功）──
      this.emitStep({ step: 'health-poll', detail: '等待 agent 就绪并验证配对（最长 3 分钟）' })
      const t0 = Date.now()
      const result = await this.pollAndVerify(req.host, token, 180_000, (msg) =>
        this.emitStep({ step: 'health-poll', detail: msg }))
      if (!result.ok) throw new Error(`agent 未就绪: ${result.error}（已等 ${Math.round((Date.now() - t0) / 1000)}s）`)

      this.emitStep({ step: 'done', detail: `安装成功 SN=${sn}` })
      return { ok: true, sn }
    } catch (e) {
      const msg = e instanceof Error ? e.message : String(e)
      this.emitStep({ step: 'done', error: msg })
      try { conn.end() } catch { /* */ }
      return { ok: false, error: msg }
    }
  }

  /** 预探测 agent 是否存活（health 免 token） */
  private async probeAgent(host: string): Promise<{ sn: string; model?: string } | null> {
    try {
      const r = await fetch(`http://${host}:8300/api/health`, { signal: AbortSignal.timeout(5000) })
      if (r.ok) {
        const j = (await r.json()) as { sn?: string; model?: string }
        if (j.sn) return { sn: j.sn, model: j.model }
      }
    } catch { /* 不在跑 */ }
    return null
  }

  /**PC2→PC3 免密配置（新机器人开箱即用媒体上传）：
   *  1. BatchMode 测试已通 → 跳过
   *  2. 无 key 则生成 ed25519
   *  3. sshpass 不在则 sudo apt 装（沙盒免密白名单）
   *  4. sshpass + 装机密码写入公钥到 PC3 → 复验 */
  private async setupPc3Keyless(conn: Client, req: InstallRequest): Promise<void> {
    const PC3 = '10.0.1.42'
    this.emitStep({ step: 'pc3-setup', detail: '检查 PC3 免密…' })

    // 1. 已通？
    const test = await this.exec(conn,
      `ssh -o BatchMode=yes -o ConnectTimeout=3 -o StrictHostKeyChecking=no agi@${PC3} "echo ok" 2>/dev/null`, 8000)
    if (test.out.trim() === 'ok') {
      this.emitStep({ step: 'pc3-setup', detail: 'PC3 免密已通，跳过' })
      return
    }

    // 2. 确保 key（无则生成）
    await this.exec(conn,
      `test -f ~/.ssh/id_ed25519 || ssh-keygen -t ed25519 -N "" -f ~/.ssh/id_ed25519 -q`, 10000)

    // 3. 确保 sshpass（沙盒 sudo apt 免密）
    const which = await this.exec(conn, 'command -v sshpass', 5000)
    if (which.code !== 0) {
      this.emitStep({ step: 'pc3-setup', detail: '安装 sshpass…' })
      const apt = await this.exec(conn, 'sudo -n apt install -y sshpass', 120_000)
      if (apt.code !== 0) {
        this.emitStep({ step: 'pc3-setup', detail: 'sshpass 安装失败，跳过（媒体上传将不可用）' })
        return
      }
    }

    // 4. 写入公钥（用装机密码认证一次）
    this.emitStep({ step: 'pc3-setup', detail: '配置 PC3 公钥…' })
    await this.exec(conn,
      `sshpass -p '${req.password.replace(/'/g, "'\\''")}' ` +
      `ssh-copy-id -i ~/.ssh/id_ed25519.pub -o ConnectTimeout=5 -o StrictHostKeyChecking=no agi@${PC3}`, 20000)

    // 5. 复验
    const verify = await this.exec(conn,
      `ssh -o BatchMode=yes -o ConnectTimeout=3 -o StrictHostKeyChecking=no agi@${PC3} "echo ok" 2>/dev/null`, 8000)
    if (verify.out.trim() === 'ok') {
      this.emitStep({ step: 'pc3-setup', detail: 'PC3 免密配置完成 ✓' })
    } else {
      this.emitStep({ step: 'pc3-setup', detail: 'PC3 免密仍不通（密码不对或 PC3 不可达），媒体上传暂不可用' })
    }
  }

  /** 平台登记换 token（pair/register：upsert by SN） */
  private async registerAtPlatform(sn: string, req: InstallRequest): Promise<string> {
    const reg = await fetch(`http://127.0.0.1:${req.platformPort}/api/pair/register`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ sn, ip: req.host, name: req.name }),
      signal: AbortSignal.timeout(5000),
    })
    if (!reg.ok) throw new Error(`平台登记失败 ${reg.status}`)
    const { token } = (await reg.json()) as { token: string }
    return token
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
  private async pollAndVerify(host: string, token: string, timeoutMs: number,
    onWait?: (msg: string) => void):
    Promise<{ ok: boolean; error?: string }> {
    const deadline = Date.now() + timeoutMs
    let lastErr = ''
    let n = 0
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
      n++
      onWait?.(`等待中 ${n * 3}s · ${lastErr}`)
      await new Promise((r) => setTimeout(r, 3000))
    }
    return { ok: false, error: lastErr }
  }
}

function baseName(p: string): string {
  return p.split('/').pop() ?? p
}
