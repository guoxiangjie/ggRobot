/**控制页 — 动作网格 + TTS + 模式组 + 键盘/摇杆遥控

遥控铁律（照搬 1.0 实测）：50ms(20Hz) interval 发送；停止必发全零 (0,0,0)；
断线/切页强制停；摇杆轴向映射 fwd=vec.y*max / lat=-vec.x*max / ang=-vec.x*angMax。
档位表来自能力契约 locomotion.velocity.params.gears。
*/

import { useEffect, useRef, useState, useCallback } from 'react'
import { Card, Button, Input, Tag, Typography, Toast, Switch, Modal } from '@douyinfe/semi-ui'
import { Gamepad2, Mic, Play, PersonStanding, Square } from 'lucide-react'
import nipplejs from 'nipplejs'
import { AgentWsClient } from '@/api/agentWs'
import { agentWsUrl, makeAgentClient } from '@/api/agent'
import { useRobot } from './RobotLayout'

interface MotionAction { id: string; name: string; area: number; requires_stand: boolean }
interface ModeItem { id: string; name: string; numeric_value?: number }
interface Gear { id: string; name: string; forward: number; lateral: number; angular: number }

const KEYMAP: Record<string, 'fwd+' | 'fwd-' | 'lat-' | 'lat+' | 'ang+' | 'ang-'> = {
  w: 'fwd+', s: 'fwd-', a: 'lat-', d: 'lat+', q: 'ang+', e: 'ang-',
}

export default function ControlTab(): JSX.Element {
  const { ip, token, capsOf } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const actions = ((capsOf('motion.preset')?.params.actions ?? []) as MotionAction[])
  const modes = ((capsOf('mode.switch')?.params.modes ?? []) as ModeItem[])
  const gears = ((capsOf('locomotion.velocity')?.params.gears ?? []) as Gear[])

  // ── WS（velocity 控制帧 + 会话丢失通知）──
  const wsRef = useRef<AgentWsClient | null>(null)
  const [wsOpen, setWsOpen] = useState(false)

  // ── 遥控状态 ──
  const [motorOn, setMotorOn] = useState(false)
  const [gearIdx, setGearIdx] = useState(1)
  const keys = useRef(new Set<string>())
  const joyVec = useRef({ x: 0, y: 0 })
  const motorOnRef = useRef(false)
  const gearRef = useRef<Gear | undefined>(gears[1])
  const sendTimer = useRef<number | null>(null)

  useEffect(() => { gearRef.current = gears[gearIdx] }, [gearIdx, gears])
  useEffect(() => { motorOnRef.current = motorOn }, [motorOn])

  const stopMotor = useCallback(() => {
    setMotorOn(false)
    motorOnRef.current = false
    wsRef.current?.sendVelocity(0, 0, 0)
  }, [])

  useEffect(() => {
    const c = new AgentWsClient(agentWsUrl(ip, token), {
      onStatus: (s) => {
        setWsOpen(s === 'open')
        if (s !== 'open') {
          // 断线保护：立即停循环（WS 已断发不出全零，重连后也不恢复旧速度）
          motorOnRef.current = false
          setMotorOn(false)
        }
      },
      onSessionLost: () => Toast.warning('控制权已被其他客户端接管'),
    })
    wsRef.current = c
    c.connect()
    return () => { stopMotor(); c.close() }
  }, [ip, token, stopMotor])

  // ── 键盘 ──
  useEffect(() => {
    const down = (e: KeyboardEvent): void => {
      if (e.target instanceof HTMLInputElement || e.target instanceof HTMLTextAreaElement) return
      const k = KEYMAP[e.key.toLowerCase()]
      if (k) { keys.current.add(e.key.toLowerCase()); e.preventDefault() }
    }
    const up = (e: KeyboardEvent): void => { keys.current.delete(e.key.toLowerCase()) }
    window.addEventListener('keydown', down)
    window.addEventListener('keyup', up)
    return () => { window.removeEventListener('keydown', down); window.removeEventListener('keyup', up) }
  }, [])

  // ── 20Hz 发送循环 ──
  useEffect(() => {
    if (!motorOn) return
    sendTimer.current = window.setInterval(() => {
      const g = gearRef.current ?? { forward: 0.5, lateral: 0.6, angular: 0.5 }
      let fwd = 0, lat = 0, ang = 0
      for (const k of keys.current) {
        const m = KEYMAP[k]
        if (m === 'fwd+') fwd += g.forward
        if (m === 'fwd-') fwd -= g.forward
        if (m === 'lat+') lat += g.lateral
        if (m === 'lat-') lat -= g.lateral
        if (m === 'ang+') ang += g.angular
        if (m === 'ang-') ang -= g.angular
      }
      // 摇杆合成（轴向映射照 1.0 Phone.vue：y↑=前进，x 左=+lateral/+angular → 取负）
      fwd += joyVec.current.y * g.forward
      lat += -joyVec.current.x * g.lateral
      ang += -joyVec.current.x * g.angular
      wsRef.current?.sendVelocity(+fwd.toFixed(2), +lat.toFixed(2), +ang.toFixed(2))
    }, 50)
    return () => {
      if (sendTimer.current != null) clearInterval(sendTimer.current)
      // 松开必发全零
      wsRef.current?.sendVelocity(0, 0, 0)
    }
  }, [motorOn])

  // ── 摇杆 ──
  const joyZone = useRef<HTMLDivElement>(null)
  useEffect(() => {
    if (!joyZone.current) return
    const joy = nipplejs.create({
      zone: joyZone.current, mode: 'static', position: { left: '50%', top: '50%' },
      color: '#4da6ff', size: 120,
    })
    joy.on('move', (_e, d) => { joyVec.current = d.vector })
    joy.on('end', () => { joyVec.current = { x: 0, y: 0 } })
    return () => joy.destroy()
  }, [])

  // ── 409 处理 ──
  const onCtrlErr = useCallback((e: { response?: { status?: number; data?: { locked_by?: { name?: string } } } }): void => {
    if (e.response?.status === 409) {
      const who = e.response.data?.locked_by?.name || '其他客户端'
      Modal.confirm({
        title: '机器人正被其他客户端控制',
        content: `当前控制者：${who}。要接管控制权吗？`,
        onOk: async () => { await http.post('/api/session/takeover?client_id=takeover&name=') ; Toast.success('已接管') },
      })
    } else {
      Toast.error('指令失败')
    }
  }, [http])

  // ── 动作 / TTS / 模式 ──
  const [playingKey, setPlayingKey] = useState('')
  async function playMotion(a: MotionAction): Promise<void> {
    const [motionId, area] = a.id.split(':').map(Number)
    setPlayingKey(a.id)
    try {
      const { data } = await http.post('/api/motion', { area, motion_id: motionId, interrupt: true })
      if (!data.ok) Toast.warning(data.error || '动作执行失败')
    } catch (e) { onCtrlErr(e as never) } finally { setPlayingKey('') }
  }

  const [tts, setTts] = useState('')
  const [ttsBusy, setTtsBusy] = useState(false)
  async function speak(): Promise<void> {
    if (!tts.trim()) return
    setTtsBusy(true)
    try {
      await http.post('/api/tts', { text: tts, domain: 'web_ui', is_interrupted: true, priority_level: 6 })
    } catch (e) { onCtrlErr(e as never) } finally { setTtsBusy(false) }
  }

  const [modeBusy, setModeBusy] = useState('')
  async function switchMode(m: ModeItem): Promise<void> {
    setModeBusy(m.id)
    try {
      const q = `mode=${m.id}${m.numeric_value != null ? `&value=${m.numeric_value}` : ''}`
      await http.post(`/api/mode?${q}`)
      Toast.success(`已切换：${m.name}`)
    } catch (e) { onCtrlErr(e as never) } finally { setModeBusy('') }
  }

  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1fr 340px', gap: 14 }}>
      {/* 左列：动作 + TTS */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: 14 }}>
        <Card title={<span><PersonStanding size={15} style={{ verticalAlign: -2, marginRight: 6 }} />预设动作（{actions.length}）— 需站立模式</span>}>
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(104px, 1fr))', gap: 8 }}>
            {actions.map((a) => (
              <Button key={a.id} size="small" loading={playingKey === a.id}
                onClick={() => void playMotion(a)} style={{ borderRadius: 8 }}>
                {a.name}
              </Button>
            ))}
          </div>
        </Card>

        <Card title={<span><Mic size={15} style={{ verticalAlign: -2, marginRight: 6 }} />语音播报</span>}>
          <div style={{ display: 'flex', gap: 8 }}>
            <Input value={tts} onChange={setTts} placeholder="输入播报文本，Enter 发送"
              onEnterPress={() => void speak()} />
            <Button theme="solid" icon={<Play size={13} />} loading={ttsBusy} onClick={() => void speak()}>播报</Button>
          </div>
        </Card>
      </div>

      {/* 右列：遥控 + 模式 */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: 14 }}>
        <Card title={<span><Gamepad2 size={15} style={{ verticalAlign: -2, marginRight: 6 }} />速度遥控</span>}>
          <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 8 }}>
            <Switch checked={motorOn} onChange={(v) => { if (v && !wsOpen) { Toast.warning('WS 未连接') ; return } setMotorOn(v) }} />
            <span style={{ fontSize: 13 }}>{motorOn ? '遥控中（WASD/QE 或摇杆）' : '遥控关闭'}</span>
            {motorOn && (
              <Button size="small" type="danger" icon={<Square size={12} />} onClick={stopMotor}>停</Button>
            )}
          </div>
          <div style={{ display: 'flex', gap: 6, marginBottom: 10 }}>
            {gears.map((g, i) => (
              <Tag key={g.id} size="small" shape="circle"
                type={i === gearIdx ? 'solid' : 'ghost'} style={{ cursor: 'pointer' }}
                onClick={() => setGearIdx(i)}>{g.name}</Tag>
            ))}
          </div>
          <div ref={joyZone} style={{ height: 170, position: 'relative', borderRadius: 10,
            background: 'rgba(255,255,255,0.03)', border: '1px solid var(--border)' }} />
          <Typography.Text type="tertiary" size="small" style={{ marginTop: 6, display: 'block' }}>
            20Hz 连续发送；松开/关闭自动全零；断线自动停
          </Typography.Text>
        </Card>

        <Card title="运动模式">
          <div style={{ display: 'flex', flexWrap: 'wrap', gap: 8 }}>
            {modes.map((m) => (
              <Button key={m.id} size="small" loading={modeBusy === m.id}
                onClick={() => void switchMode(m)} style={{ borderRadius: 8 }}>
                {m.name}
              </Button>
            ))}
          </div>
        </Card>
      </div>
    </div>
  )
}
