/**快捷遥控独立小窗（#/quick-ctrl）— 机器人下拉 + 六向按住式 + 键盘 WASD/QE + 速度档
   遥控铁律照 ControlTab：50ms(20Hz) WS 持续发送；松开/失焦/断线/关窗必发全零。
   键盘仅窗口聚焦时响应（blur 立即清键——切走窗口机器人必停）。
   速度 = 设置页基准（gg-ctrl-speed）× 档位系数（慢0.5 / 标准1 / 快1.5）。 */

import { useEffect, useRef, useState } from 'react'
import { Select, Tag, Radio, RadioGroup } from '@douyinfe/semi-ui'
import {
  ArrowUp, ArrowDown, ArrowLeft, ArrowRight, RotateCcw, RotateCw,
} from 'lucide-react'
import { platformApi } from '@/api/platform'
import { agentWsUrl } from '@/api/agent'
import { AgentWsClient } from '@/api/agentWs'
import { useRobotsStore } from '@/stores/robots'

type Dir = 'fwd' | 'back' | 'left' | 'right' | 'tl' | 'tr'
type Gear = 'slow' | 'mid' | 'fast'

// 基准速度：设置页「遥控」可调（localStorage gg-ctrl-speed）
const BASE = (() => {
  try {
    const v = JSON.parse(localStorage.getItem('gg-ctrl-speed') || '{}') as
      Partial<{ forward: number; lateral: number; angular: number }>
    return {
      forward: Number(v.forward) > 0 ? Number(v.forward) : 0.35,
      lateral: Number(v.lateral) > 0 ? Number(v.lateral) : 0.4,
      angular: Number(v.angular) > 0 ? Number(v.angular) : 0.6,
    }
  } catch {
    return { forward: 0.35, lateral: 0.4, angular: 0.6 }
  }
})()

const GEAR_RATIO: Record<Gear, number> = { slow: 0.5, mid: 1, fast: 1.5 }
const GEAR_LABEL: Record<Gear, string> = { slow: '慢', mid: '标准', fast: '快' }

// 键位映射（与 ControlTab 一致）
const KEYMAP: Record<string, Dir> = { w: 'fwd', s: 'back', a: 'left', d: 'right', q: 'tl', e: 'tr' }
const DIR_UI: Record<Dir, { label: string; key: string; icon: typeof ArrowUp }> = {
  fwd: { label: '前进', key: 'W', icon: ArrowUp },
  back: { label: '后退', key: 'S', icon: ArrowDown },
  left: { label: '左移', key: 'A', icon: ArrowLeft },
  right: { label: '右移', key: 'D', icon: ArrowRight },
  tl: { label: '左转', key: 'Q', icon: RotateCcw },
  tr: { label: '右转', key: 'E', icon: RotateCw },
}
// 方向 → 速度轴/符号
const DIR_AXIS: Record<Dir, { axis: 'forward' | 'lateral' | 'angular'; sign: 1 | -1 }> = {
  fwd: { axis: 'forward', sign: 1 }, back: { axis: 'forward', sign: -1 },
  left: { axis: 'lateral', sign: 1 }, right: { axis: 'lateral', sign: -1 },
  tl: { axis: 'angular', sign: 1 }, tr: { axis: 'angular', sign: -1 },
}

export default function QuickCtrlPage(): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)
  const [robotId, setRobotId] = useState('')
  const [conn, setConn] = useState<{ ip: string; token: string } | null>(null)
  const [wsOpen, setWsOpen] = useState(false)
  const [pressed, setPressed] = useState<Set<Dir>>(new Set())
  const [gear, setGear] = useState<Gear>((localStorage.getItem('gg-quick-gear') as Gear) || 'mid')
  const keysRef = useRef(new Set<Dir>())
  const wsRef = useRef<AgentWsClient | null>(null)
  const speedRef = useRef(BASE)

  useEffect(() => {
    speedRef.current = {
      forward: BASE.forward * GEAR_RATIO[gear],
      lateral: BASE.lateral * GEAR_RATIO[gear],
      angular: BASE.angular * GEAR_RATIO[gear],
    }
  }, [gear])

  // 默认选中第一台在线机
  useEffect(() => {
    if (!robotId && robots.length) {
      setRobotId((robots.find((r) => r.online) || robots[0]).id)
    }
  }, [robots, robotId])

  // 拉连接信息（ip/token）
  useEffect(() => {
    if (!robotId) return
    let alive = true
    void platformApi().get(`/api/robots/${robotId}`).then(({ data }) => {
      if (alive && data.last_ip) setConn({ ip: data.last_ip, token: data.token })
    }).catch(() => { /* */ })
    return () => { alive = false }
  }, [robotId])

  // WS 生命周期（切换机器人/关窗重建；断线保护清按键）
  // 窗口失焦即断开 —— 会话锁只在聚焦（真正可能遥控）时持有，开着小窗不阻塞编排等其他控制
  useEffect(() => {
    if (!conn) return
    let c: AgentWsClient | null = null
    const open = (): void => {
      if (c) return
      c = new AgentWsClient(agentWsUrl(conn.ip, conn.token), {
        onStatus: (s) => {
          setWsOpen(s === 'open')
          if (s !== 'open') { keysRef.current.clear(); setPressed(new Set()) }
        },
      })
      wsRef.current = c
      c.connect()
    }
    const close = (): void => {
      c?.close()
      c = null
      wsRef.current = null
      setWsOpen(false)
      keysRef.current.clear()
      setPressed(new Set())
    }
    if (document.hasFocus()) open()
    const onFocus = (): void => open()
    const onBlur = (): void => close()   // 失焦断开：机器人停 + 释放控制会话锁
    window.addEventListener('focus', onFocus)
    window.addEventListener('blur', onBlur)
    return () => {
      window.removeEventListener('focus', onFocus)
      window.removeEventListener('blur', onBlur)
      close()
    }
  }, [conn])

  // 键盘 WASD/QE（仅窗口聚焦生效；blur 立即清键——切走窗口必停）
  useEffect(() => {
    const sync = (): void => setPressed(new Set(keysRef.current))
    const down = (ev: KeyboardEvent): void => {
      const d = KEYMAP[ev.key.toLowerCase()]
      if (!d) return
      ev.preventDefault()
      keysRef.current.add(d); sync()
    }
    const up = (ev: KeyboardEvent): void => {
      const d = KEYMAP[ev.key.toLowerCase()]
      if (!d) return
      keysRef.current.delete(d); sync()
    }
    const onBlur = (): void => { keysRef.current.clear(); sync() }
    window.addEventListener('keydown', down)
    window.addEventListener('keyup', up)
    window.addEventListener('blur', onBlur)
    return () => {
      window.removeEventListener('keydown', down)
      window.removeEventListener('keyup', up)
      window.removeEventListener('blur', onBlur)
    }
  }, [])

  // 20Hz 发送循环（常开：WS 通着就发当前合成速度；全松开自然全零）
  useEffect(() => {
    const timer = window.setInterval(() => {
      const sp = speedRef.current
      let forward = 0, lateral = 0, angular = 0
      for (const k of keysRef.current) {
        const { axis, sign } = DIR_AXIS[k]
        if (axis === 'forward') forward += sp.forward * sign
        else if (axis === 'lateral') lateral += sp.lateral * sign
        else angular += sp.angular * sign
      }
      wsRef.current?.sendVelocity(+forward.toFixed(2), +lateral.toFixed(2), +angular.toFixed(2))
    }, 50)
    return () => {
      clearInterval(timer)
      wsRef.current?.sendVelocity(0, 0, 0)   // 关窗必发全零
    }
  }, [])

  const press = (d: Dir): void => {
    keysRef.current.add(d); setPressed(new Set(keysRef.current))
  }
  const release = (d: Dir): void => {
    keysRef.current.delete(d); setPressed(new Set(keysRef.current))
  }
  const bind = (d: Dir): {
    onPointerDown: () => void; onPointerUp: () => void
    onPointerLeave: () => void; onPointerCancel: () => void
  } => ({
    onPointerDown: () => press(d),
    onPointerUp: () => release(d),
    onPointerLeave: () => release(d),
    onPointerCancel: () => release(d),
  })

  const cell = (d: Dir): JSX.Element => {
    const on = pressed.has(d)
    const I = DIR_UI[d].icon
    return (
      <div key={d} className={`qc-btn${on ? ' on' : ''}${wsOpen ? '' : ' off'}`} {...bind(d)}>
        <I size={16} strokeWidth={2.2} />
        <span>{DIR_UI[d].label}</span>
        <span className="qc-key">{DIR_UI[d].key}</span>
      </div>
    )
  }

  return (
    <div className="qc">
      <div className="titlebar qc-bar">
        <span className="title" style={{ fontSize: 13, fontWeight: 700 }}>快捷遥控</span>
        <div className="spacer" />
        <Tag size="small" color={wsOpen ? 'green' : 'grey'}>{wsOpen ? '已连接' : '未连接'}</Tag>
      </div>

      <div style={{
        padding: '10px 14px 14px', display: 'flex', flexDirection: 'column', flex: 1,
      }}>
        {/* 顶部：机器人选择 + 速度档 */}
        <div style={{ display: 'flex', flexDirection: 'column', gap: 10 }}>
          <Select<string> value={robotId} style={{ width: '100%' }}
            optionList={robots.map((r) => ({ label: `${r.name}${r.online ? '' : '（离线）'}`, value: r.id }))}
            onChange={(v) => { setConn(null); setRobotId(String(v ?? '')) }} />

          <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
            <span className="qc-hint" style={{ textAlign: 'left' }}>速度</span>
            <RadioGroup type="button" buttonSize="small" value={gear}
              onChange={(e) => {
                const g = e.target.value as Gear
                setGear(g)
                localStorage.setItem('gg-quick-gear', g)
              }}>
              {(Object.keys(GEAR_RATIO) as Gear[]).map((g) => (
                <Radio key={g} value={g}>{GEAR_LABEL[g]}</Radio>
              ))}
            </RadioGroup>
          </div>
        </div>

        {/* 方向面板：剩余空间居中（四周留白一致） */}
        <div style={{
          flex: 1, display: 'flex', flexDirection: 'column',
          alignItems: 'center', justifyContent: 'center', gap: 4,
        }}>
          <div className="qc-pad">
            <div style={{ gridColumn: 2 }}>{cell('fwd')}</div>
            <div style={{ gridColumn: 1, gridRow: 2 }}>{cell('left')}</div>
            <div style={{ gridColumn: 2, gridRow: 2 }}>{cell('back')}</div>
            <div style={{ gridColumn: 3, gridRow: 2 }}>{cell('right')}</div>
          </div>
          <div className="qc-turn-row">
            {cell('tl')}
            {cell('tr')}
          </div>
          <div className="qc-hint">按住即走 · 键盘 WASD/QE · 窗口切走自动停</div>
        </div>
      </div>
    </div>
  )
}
