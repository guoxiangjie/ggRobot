/**系统页 — 系统状态 + 开发者模式迁移（分级确认 + in_progress 轮询，语义照 1.0 Control）*/

import { useEffect, useRef, useState } from 'react'
import { Card, Tag, Button, Typography, Modal, Input } from '@douyinfe/semi-ui'
import { Cpu, ShieldAlert } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from './RobotLayout'
import A3SystemTab from './a3/A3SystemTab'

interface SysInfo { action: { desc: string; status: number } | null; system: { state: string; status: number } | null }

const STATE_LABEL: Record<string, string> = {
  Business: '业务模式', Ready: '就绪',
  Develop_Audio_Linux: '开发者·音频(Linux)', Develop_Audio_ROS: '开发者·音频(ROS)',
  Develop_Nav: '开发者·导航', Develop_MC: '开发者·MC（运动控制）',
}

export default function SystemTab(): JSX.Element {
  const { isA3 } = useRobot()
  if (isA3) return <A3SystemTab />
  return <X2SystemTab />
}

function X2SystemTab(): JSX.Element {
  const { ip, token, capsOf } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current
  const migrateStates = ((capsOf('status.system')?.params.migrate_states ?? []) as string[])

  const [sys, setSys] = useState<SysInfo | null>(null)
  const [busy, setBusy] = useState('')

  useEffect(() => {
    const load = (): void => {
      void http.get('/api/system').then(({ data }) => setSys(data)).catch(() => setSys(null))
    }
    load()
    const t = window.setInterval(load, 3000)
    return () => clearInterval(t)
  }, [http])

  const state = sys?.system?.state ?? '未知'
  const isDev = state.startsWith('Develop_')

  /**等迁移完成（2s × 12 轮询 state 变化，语义照 1.0 in_progress 处理） */
  async function waitMigrate(target: string): Promise<boolean> {
    for (let i = 0; i < 12; i++) {
      await new Promise((r) => setTimeout(r, 2000))
      try {
        const { data } = await http.get('/api/system')
        if (data?.system?.state === target) return true
      } catch { /* 继续轮询 */ }
    }
    return false
  }

  /**迁移（分级确认：MC 高危需输入 MC） */
  function migrate(target: string): void {
    const start = (): void => {
      setBusy(target)
      void (async () => {
        try {
          const { data } = await http.post('/api/system/migrate', { state: target }, { timeout: 30000 })
          if (data.ok) {
            toast.success(`已切换：${STATE_LABEL[target] ?? target}`)
          } else if (data.in_progress) {
            toast.info('迁移进行中…')
            const done = await waitMigrate(target)
            if (done) toast.success(`已切换：${STATE_LABEL[target] ?? target}`)
            else toast.warning('迁移超时，状态将自动刷新')
          } else {
            toast.error(data.message || '迁移失败')
          }
        } catch {
          toast.error('迁移请求失败')
        } finally {
          setBusy('')
        }
      })()
    }

    if (target === 'Develop_MC') {
      let code = ''
      Modal.confirm({
        title: '⚠️ 高危操作：进入 MC 开发者模式',
        content: (
          <div style={{ display: 'grid', gap: 8 }}>
            <Typography.Text type="danger" size="small">
              MC 模式直接控制运动单元，可能导致机器人失稳摔倒。确认请输入 MC：
            </Typography.Text>
            <Input placeholder="输入 MC 确认" onChange={(v) => { code = v }} />
          </div>
        ),
        onOk: () => {
          if (code !== 'MC') { toast.warning('确认码不正确') ; return }
          start()
        },
      })
    } else {
      Modal.confirm({
        title: `切换到 ${STATE_LABEL[target] ?? target}？`,
        content: '模式切换期间语音/动作等服务可能短暂不可用。',
        onOk: start,
      })
    }
  }

  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: 16 }}>
      <Card title={<span><Cpu size={15} style={{ verticalAlign: -2, marginRight: 6 }} />系统状态</span>}>
        <div style={{ display: 'grid', gap: 10, fontSize: 13 }}>
          <Row k="系统模式" v={
            <Tag size="small" shape="circle" color={isDev ? 'orange' : 'green'}>
              {STATE_LABEL[state] ?? state}
            </Tag>
          } />
          <Row k="状态码" v={String(sys?.system?.status ?? '-')} />
          <Row k="动作描述" v={sys?.action?.desc ?? '—'} />
          <Row k="动作状态" v={sys?.action ? (sys.action.status === 1 ? '执行中' : String(sys.action.status)) : '—'} />
        </div>
        <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 12 }}>
          3 秒自动刷新 · 正常业务态为 Business
        </Typography.Text>
      </Card>

      <Card title={<span><ShieldAlert size={15} style={{ verticalAlign: -2, marginRight: 6 }} />开发者模式</span>}>
        <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginBottom: 12 }}>
          切换系统状态（文档 5.6 白名单）。Develop_MC 为高危项，需二次确认。
        </Typography.Text>
        <div style={{ display: 'flex', flexWrap: 'wrap', gap: 8 }}>
          {migrateStates.map((s) => (
            <Button key={s} size="small" loading={busy === s}
              type={s === 'Develop_MC' ? 'danger' : s === 'Ready' ? 'tertiary' : 'primary'}
              onClick={() => migrate(s)}>
              {STATE_LABEL[s] ?? s}
            </Button>
          ))}
        </div>
      </Card>
    </div>
  )
}

function Row({ k, v }: { k: string; v: React.ReactNode }): JSX.Element {
  return (
    <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
      <span style={{ color: 'var(--semi-color-text-2)' }}>{k}</span><span>{v}</span>
    </div>
  )
}
