/**单机器人详情容器 — 拉登记信息(ip/token) + 能力契约 + tab 导航（Dashboard/控制/相机）*/

import { useEffect, useState, useMemo, createContext, useContext } from 'react'
import { useParams, NavLink, Outlet } from 'react-router-dom'
import { Card, Tag, Typography, Spin, Empty } from '@douyinfe/semi-ui'
import { platformApi } from '@/api/platform'
import { makeAgentClient, type Capabilities } from '@/api/agent'

interface RobotCtx {
  ip: string
  token: string
  name: string
  caps: Capabilities | null
  capsOf: (type: string) => { type: string; params: Record<string, unknown> } | undefined
}

const Ctx = createContext<RobotCtx | null>(null)
export function useRobot(): RobotCtx {
  const c = useContext(Ctx)
  if (!c) throw new Error('useRobot outside RobotLayout')
  return c
}

export default function RobotLayout(): JSX.Element {
  const { id } = useParams<{ id: string }>()
  const [info, setInfo] = useState<{ ip: string; token: string; name: string } | null>(null)
  const [caps, setCaps] = useState<Capabilities | null>(null)
  const [error, setError] = useState('')

  useEffect(() => {
    let alive = true
    void (async () => {
      try {
        const { data } = await platformApi().get(`/api/robots/${id}`)
        if (!alive) return
        if (!data.last_ip) { setError('该机器人无 IP 记录（装机未完成）') ; return }
        setInfo({ ip: data.last_ip, token: data.token, name: data.name })
        // 能力契约（离线则空——页面降级）
        try {
          const hc = makeAgentClient(data.last_ip, data.token)
          const { data: cd } = await hc.get('/api/capabilities')
          if (alive) setCaps(cd as Capabilities)
        } catch { /* 离线 */ }
      } catch {
        if (alive) setError('平台查询失败')
      }
    })()
    return () => { alive = false }
  }, [id])

  const ctx = useMemo<RobotCtx | null>(() => info && ({
    ...info, caps,
    capsOf: (t) => caps?.capabilities.find((c) => c.type === t),
  }), [info, caps])

  if (error) {
    return <Empty title="无法打开" description={error} style={{ padding: 60 }} />
  }
  if (!ctx) return <div style={{ padding: 80, textAlign: 'center' }}><Spin size="large" /></div>

  const online = caps != null
  return (
    <Ctx.Provider value={ctx}>
      <div>
        <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 14 }}>
          <h1 className="page-title" style={{ marginBottom: 0 }}>{info!.name}</h1>
          <Tag size="small" color={online ? 'green' : 'grey'} shape="circle">
            {online ? '在线' : '离线'}
          </Tag>
          <Typography.Text type="tertiary" size="small">{info!.ip}</Typography.Text>
          {caps && <Typography.Text type="tertiary" size="small">契约 v{caps.catalog_version}</Typography.Text>}
        </div>

        {!online && (
          <Card style={{ marginBottom: 14 }}>
            <Typography.Text type="warning">机器人离线或未配对 — 仅显示登记信息</Typography.Text>
          </Card>
        )}

        <div className="robot-tabs">
          {[
            { to: 'dashboard', label: '仪表盘' },
            { to: 'control', label: '控制' },
            { to: 'camera', label: '相机' },
            { to: 'voice', label: '语音' },
            { to: 'emoji', label: '表情' },
            { to: 'media', label: '媒体' },
            { to: 'linkcraft', label: '灵创' },
            { to: 'system', label: '系统' },
          ].map((t) => (
            <NavLink key={t.to} to={t.to}
              className={({ isActive }) => `nav-item${isActive ? ' active' : ''}`}>
              {t.label}
            </NavLink>
          ))}
        </div>

        <Outlet />
      </div>
    </Ctx.Provider>
  )
}
