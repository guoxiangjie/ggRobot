/**A3 系统页 — Action 状态机切换（MOTION/PD_STAND/DAMPING）+ 设备信息 */

import { useEffect, useRef, useState } from 'react'
import { Card, Button, Tag, Typography } from '@douyinfe/semi-ui'
import { Settings2, RefreshCw } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from '../RobotLayout'

const ACTIONS = [
  { id: 'MOTION', label: '运动模式', desc: '行走/上肢动作（遥控前置）', color: 'green' },
  { id: 'PD_STAND', label: '位控站立', desc: '稳定站立', color: 'blue' },
  { id: 'DAMPING', label: '阻尼模式', desc: '关节高阻尼（搬运/收纳）', color: 'orange' },
] as const

export default function A3SystemTab(): JSX.Element {
  const { ip, token, name, model } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current
  const [cur, setCur] = useState('')
  const [health, setHealth] = useState<{ sn?: string; version?: string } | null>(null)

  const load = (): void => {
    void http.get('/api/mode').then(({ data }) => setCur(data.action?.replace('MotionControlAction_', '') || '')).catch(() => {})
    void http.get('/api/health').then(({ data }) => setHealth(data)).catch(() => {})
  }
  useEffect(() => {
    load()
    const t = window.setInterval(load, 5000)
    return () => clearInterval(t)
  }, [http])

  async function setAction(a: string): Promise<void> {
    try {
      await http.post(`/api/mode?mode=${a}`)
      toast.success(`已切换 ${a}`)
      setTimeout(load, 800)
    } catch { toast.error('切换失败') }
  }

  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1.3fr 1fr', gap: 16 }}>
      <Card title={<span><Settings2 size={15} style={{ verticalAlign: -2, marginRight: 6 }} />运动状态机</span>}
        headerExtraContent={<Button size="small" theme="borderless" icon={<RefreshCw size={13} />} onClick={load} />}>
        <div style={{ display: 'grid', gap: 10 }}>
          {ACTIONS.map((a) => (
            <div key={a.id} className="gg-card free-item" style={{
              padding: 14, borderColor: cur === a.id ? 'var(--semi-color-primary)' : undefined }}>
              <div style={{ display: 'flex', alignItems: 'center', gap: 10 }}>
                <div style={{ flex: 1 }}>
                  <div style={{ fontWeight: 700, fontSize: 13 }}>
                    {a.label} {cur === a.id && <Tag size="small" color="green" shape="circle">当前</Tag>}
                  </div>
                  <Typography.Text type="tertiary" size="small">{a.desc}</Typography.Text>
                </div>
                <Button size="small" theme={cur === a.id ? 'light' : 'solid'} disabled={cur === a.id}
                  onClick={() => void setAction(a.id)}>切换</Button>
              </div>
            </div>
          ))}
        </div>
        <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 10 }}>
          SIT_DOWN/LIE_DOWN 等涉及吊装的模式仅限手动操作，不开放
        </Typography.Text>
      </Card>

      <Card title="设备信息">
        <div style={{ display: 'grid', gap: 8, fontSize: 13 }}>
          <Row k="名称" v={name} />
          <Row k="机型" v={model.toUpperCase()} />
          <Row k="SN" v={health?.sn ?? '—'} />
          <Row k="Agent" v={health?.version ? `v${health.version}` : '—'} />
          <Row k="IP" v={ip} />
        </div>
      </Card>
    </div>
  )
}

function Row({ k, v }: { k: string; v: string }): JSX.Element {
  return (
    <div style={{ display: 'flex', justifyContent: 'space-between' }}>
      <span style={{ color: 'var(--semi-color-text-2)' }}>{k}</span>
      <span style={{ fontWeight: 600, wordBreak: 'break-all' }}>{v}</span>
    </div>
  )
}
