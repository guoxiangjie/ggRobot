/**监控大盘 — hub WS 订阅，所有机器人状态一屏看*/

import { useEffect, useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { Card, Tag, Progress, Empty, Spin } from '@douyinfe/semi-ui'
import { Bot, Wifi, WifiOff } from 'lucide-react'
import { hubWs, type RobotSummary } from '@/api/platform'
import { useAppStore } from '@/stores/app'

export default function Overview(): JSX.Element {
  const nav = useNavigate()
  const sidecarReady = useAppStore((s) => s.sidecarReady)
  const [robots, setRobots] = useState<RobotSummary[]>([])
  const [connected, setConnected] = useState(false)

  useEffect(() => {
    if (!sidecarReady) return
    return hubWs((list) => {
      setConnected(true)
      setRobots(list)
    })
  }, [sidecarReady])

  const online = robots.filter((r) => r.online).length

  return (
    <div className="page">
      <h1 className="page-title">总览</h1>
      <p className="page-sub">
        {connected ? `${robots.length} 台已登记 · ${online} 台在线` : '正在连接平台服务...'}
      </p>

      {!connected ? (
        <div style={{ padding: 80, textAlign: 'center' }}>
          <Spin size="large" />
        </div>
      ) : robots.length === 0 ? (
        <Empty
          title="还没有机器人"
          description="点左侧 + 号，通过装机向导把第一台机器人接入平台"
          style={{ padding: 60 }}
        />
      ) : (
        <div className="robot-grid">
          {robots.map((r) => (
            <div key={r.id} onClick={() => nav('/robots')}>
              <Card bodyStyle={{ padding: 16 }}>
              <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 12 }}>
                <div style={{
                  width: 38, height: 38, borderRadius: 10, display: 'flex',
                  alignItems: 'center', justifyContent: 'center',
                  background: r.online ? 'rgba(60,201,142,0.14)' : 'rgba(139,147,163,0.12)',
                }}>
                  <Bot size={20} color={r.online ? '#3cc98e' : '#8b93a3'} />
                </div>
                <div style={{ flex: 1, minWidth: 0 }}>
                  <div style={{ fontWeight: 600, fontSize: 14 }}>{r.name}</div>
                  <div style={{ fontSize: 11, color: '#8b93a3' }}>
                    {r.model.toUpperCase()} · SN {r.sn.slice(-6)}
                  </div>
                </div>
                {r.online
                  ? <Wifi size={16} color="#3cc98e" />
                  : <WifiOff size={16} color="#8b93a3" />}
              </div>

              {r.battery_soc != null && (
                <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
                  <Progress percent={r.battery_soc} showInfo={false}
                    stroke={r.battery_soc > 30 ? '#3cc98e' : '#f44b4b'}
                    style={{ flex: 1, margin: 0 }} />
                  <span style={{ fontSize: 12, color: '#8b93a3' }}>{r.battery_soc}%</span>
                </div>
              )}

              <div style={{ marginTop: 10, display: 'flex', gap: 6 }}>
                <Tag size="small" color={r.online ? 'green' : 'grey'} shape="circle">
                  {r.online ? '在线' : '离线'}
                </Tag>
                {r.status === 'pending' && <Tag size="small" color="orange" shape="circle">装机中</Tag>}
                {r.token_ok && <Tag size="small" color="blue" shape="circle">已配对</Tag>}
                {r.version && <Tag size="small" shape="circle">v{r.version}</Tag>}
              </div>
              </Card>
            </div>
          ))}
        </div>
      )}
    </div>
  )
}
