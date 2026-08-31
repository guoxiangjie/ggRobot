/**A3 仪表盘 — 关节 14 项 + Action 状态 + 实时告警（A3 独有 HDS 分级告警）+ 系统信息
   电池：BMS 话题 iceoryx 无数据（待厂商通道），v1 从告警/system 缺省显示 */

import { useEffect, useRef, useState } from 'react'
import { Card, Tag, Typography, Button } from '@douyinfe/semi-ui'
import { Activity, AlertTriangle, Cpu, RefreshCw } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { useRobot } from '../RobotLayout'

interface Alert { code: string; level: string; text: string }

export default function A3Dashboard(): JSX.Element {
  const { ip, token } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const [arms, setArms] = useState<Array<{ name: string; position: number; velocity: number; effort: number }>>([])
  const [system, setSystem] = useState<{ action?: string; action_status?: string; alerts?: Alert[]; alerts_count?: number } | null>(null)
  const [battery, setBattery] = useState<Record<string, unknown> | null>(null)

  const load = (): void => {
    void http.get('/api/status').then(({ data }) => setArms(data.arms || [])).catch(() => {})
    void http.get('/api/system').then(({ data }) => setSystem(data)).catch(() => setSystem(null))
  }

  useEffect(() => {
    load()
    const t = window.setInterval(load, 5000)   // system 5s（agent 侧已缓存，限频合规）
    return () => clearInterval(t)
  }, [http])

  useEffect(() => {
    // WS sensor.all（关节实时）——低频 HTTP 兜底之上再叠加推送
    const ws = new WebSocket(`ws://${ip}:8300/ws?token=${encodeURIComponent(token)}&client_id=a3-dash&name=仪表盘`)
    ws.onopen = () => ws.send(JSON.stringify({ v: 1, type: 'sub', topics: ['sensor.*'] }))
    ws.onmessage = (ev) => {
      try {
        const msg = JSON.parse(ev.data) as { type: string; topic: string; data: Record<string, unknown> }
        if (msg.type === 'event' && msg.topic === 'sensor.all') {
          const d = msg.data
          if (Array.isArray(d.arms) && d.arms.length) setArms(d.arms as typeof arms)
          if (d.battery) setBattery(d.battery as Record<string, unknown>)
        }
      } catch { /* */ }
    }
    return () => ws.close()
  }, [ip, token])

  const alerts = system?.alerts || []
  const levelColor = (lv: string): 'red' | 'orange' | 'yellow' | 'grey' =>
    lv.startsWith('H1') || lv.startsWith('H2') ? 'red'
      : lv.startsWith('H3') ? 'orange'
        : lv.startsWith('H4') || lv.startsWith('H5') ? 'yellow' : 'grey'

  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1.2fr 1fr', gap: 16 }}>
      {/* 左：关节 */}
      <Card title={<span><Activity size={15} style={{ verticalAlign: -2, marginRight: 6 }} />上肢关节（14）</span>}
        headerExtraContent={<Button size="small" theme="borderless" icon={<RefreshCw size={13} />} onClick={load} />}>
        {arms.length === 0
          ? <Typography.Text type="tertiary">等待关节数据（确认机器人在线）…</Typography.Text>
          : (
            <div style={{ display: 'grid', gap: 6, maxHeight: 480, overflow: 'auto' }}>
              {arms.map((j) => {
                const deg = (j.position * 180 / Math.PI).toFixed(1)
                const pct = Math.min(100, Math.abs(j.position) / 3 * 100)
                return (
                  <div key={j.name} style={{ display: 'grid', gridTemplateColumns: '190px 1fr 90px', gap: 8, alignItems: 'center' }}>
                    <Typography.Text size="small" ellipsis={{ showTooltip: true }}>{j.name.replace('_joint', '')}</Typography.Text>
                    <div style={{ height: 8, background: 'var(--semi-color-fill-1)', borderRadius: 4, overflow: 'hidden' }}>
                      <div style={{ width: `${pct}%`, height: '100%', background: 'var(--semi-color-primary)' }} />
                    </div>
                    <Typography.Text size="small" type="tertiary" style={{ fontVariantNumeric: 'tabular-nums' }}>
                      {deg}° / {(j.effort ?? 0).toFixed(1)}
                    </Typography.Text>
                  </div>
                )
              })}
            </div>
          )}
      </Card>

      {/* 右：状态 + 告警 */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: 16 }}>
        <Card title={<span><Cpu size={15} style={{ verticalAlign: -2, marginRight: 6 }} />运动状态</span>}>
          <div style={{ display: 'flex', gap: 8, alignItems: 'center', marginBottom: 8 }}>
            <Typography.Text type="tertiary" size="small">Action：</Typography.Text>
            <Tag size="small" color={system?.action === 'MOTION' ? 'green' : 'blue'} shape="circle">
              {system?.action ?? '—'}
            </Tag>
            {system?.action_status && <Tag size="small" shape="circle">{system.action_status}</Tag>}
          </div>
          <div style={{ display: 'flex', gap: 8, alignItems: 'center' }}>
            <Typography.Text type="tertiary" size="small">电池：</Typography.Text>
            {battery
              ? <Tag size="small" color={(Number(battery.charge) || 0) < 20 ? 'red' : 'green'} shape="circle">
                  {String(battery.charge ?? '?')}%
                </Tag>
              : <Typography.Text type="tertiary" size="small">待数据通道（BMS iceoryx）</Typography.Text>}
          </div>
        </Card>

        <Card title={<span><AlertTriangle size={15} style={{ verticalAlign: -2, marginRight: 6 }} />告警（{alerts.length}）</span>}>
          {alerts.length === 0
            ? <Typography.Text type="success" size="small">无活动告警 ✓</Typography.Text>
            : (
              <div style={{ display: 'grid', gap: 8, maxHeight: 340, overflow: 'auto' }}>
                {alerts.map((a) => (
                  <div key={a.code} style={{ display: 'flex', gap: 8, alignItems: 'center' }}>
                    <Tag size="small" color={levelColor(a.level)} shape="circle">{a.level}</Tag>
                    <div style={{ flex: 1, minWidth: 0 }}>
                      <Typography.Text size="small" ellipsis={{ showTooltip: true }}>{a.text}</Typography.Text>
                    </div>
                    <Typography.Text type="tertiary" size="small">{a.code}</Typography.Text>
                  </div>
                ))}
              </div>
            )}
        </Card>
      </div>
    </div>
  )
}
