/**仪表盘 — agent WS 直连订阅 sensor.* → 电池/IMU/关节三卡（数据结构照 1.0 robot store）*/

import { useEffect, useState, useRef } from 'react'
import { Card, Tag, Progress, Typography } from '@douyinfe/semi-ui'
import { BatteryCharging, Compass, Activity } from 'lucide-react'
import { AgentWsClient, type SensorData } from '@/api/agentWs'
import { agentWsUrl } from '@/api/agent'
import { useRobot } from './RobotLayout'
import A3Dashboard from './a3/A3Dashboard'

export default function DashboardTab(): JSX.Element {
  const { isA3 } = useRobot()
  if (isA3) return <A3Dashboard />
  return <X2Dashboard />
}

function X2Dashboard(): JSX.Element {

  const { ip, token } = useRobot()
  const [sensor, setSensor] = useState<SensorData | null>(null)
  const [status, setStatus] = useState<'open' | 'closed' | 'connecting'>('connecting')
  const [lastTs, setLastTs] = useState(0)
  const clientRef = useRef<AgentWsClient | null>(null)

  useEffect(() => {
    const c = new AgentWsClient(agentWsUrl(ip, token), {
      onEvent: (topic, data) => {
        if (topic === 'sensor.all') {
          setSensor(data as SensorData)
          setLastTs(Date.now())
        }
      },
      onStatus: setStatus,
    })
    clientRef.current = c
    c.connect()
    c.sub(['sensor.*'])
    return () => c.close()
  }, [ip, token])

  const fresh = Date.now() - lastTs < 2000
  const b = sensor?.battery
  const imu = sensor?.imu
  const arms = sensor?.arms ?? []

  return (
    <div>
      <div style={{ display: 'flex', gap: 8, marginBottom: 14, alignItems: 'center' }}>
        <Tag size="small" color={status === 'open' && fresh ? 'green' : 'grey'} shape="circle">
          {status === 'open' ? (fresh ? '数据流正常' : '已连接·等待数据') : status === 'connecting' ? '连接中' : '已断开·自动重连'}
        </Tag>
      </div>

      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fit, minmax(300px, 1fr))', gap: 14 }}>
        {/* 电池 */}
        <Card
          title={<span><BatteryCharging size={15} style={{ verticalAlign: -2, marginRight: 6 }} />电池</span>}
        >
          {b ? (
            <div>
              <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 10 }}>
                <Progress percent={Math.round(b.percentage ?? 0)} showInfo={false}
                  style={{ flex: 1, margin: 0 }}
                  stroke={(b.percentage ?? 0) > 30 ? '#3cc98e' : '#f44b4b'} />
                <span style={{ fontSize: 22, fontWeight: 700 }}>{Math.round(b.percentage ?? 0)}%</span>
              </div>
              <Row k="电压" v={`${b.voltage?.toFixed(1) ?? '-'} V`} />
              <Row k="电流" v={`${b.current?.toFixed(1) ?? '-'} A`} />
              <Row k="温度" v={`${b.temperature?.toFixed(0) ?? '-'} ℃`} />
              <Row k="状态" v={b.power ?? '-'} />
            </div>
          ) : <Typography.Text type="tertiary">等待数据…</Typography.Text>}
        </Card>

        {/* IMU */}
        <Card title={<span><Compass size={15} style={{ verticalAlign: -2, marginRight: 6 }} />IMU</span>}>
          {imu ? (
            <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr 1fr', gap: 10 }}>
              {['accel_x', 'accel_y', 'accel_z'].map((k) => (
                <div key={k} style={{ textAlign: 'center', padding: '8px 0', background: 'var(--semi-color-fill-0)', borderRadius: 8 }}>
                  <div style={{ fontSize: 11, color: 'var(--semi-color-text-2)' }}>{k.replace('accel_', '加速度 ')}</div>
                  <div style={{ fontSize: 16, fontWeight: 600 }}>{(imu[k] ?? 0).toFixed(2)}</div>
                </div>
              ))}
            </div>
          ) : <Typography.Text type="tertiary">等待数据…</Typography.Text>}
        </Card>

        {/* 关节 */}
        <Card title={<span><Activity size={15} style={{ verticalAlign: -2, marginRight: 6 }} />关节（{arms.length}）</span>}>
          {arms.length > 0 ? (
            <div style={{ maxHeight: 220, overflow: 'auto' }}>
              {arms.map((a) => (
                <div key={a.name} style={{ display: 'flex', alignItems: 'center', gap: 8, padding: '3px 0', fontSize: 12 }}>
                  <span style={{ width: 110, overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{a.name}</span>
                  <div style={{ flex: 1, height: 4, background: 'rgba(255,255,255,0.06)', borderRadius: 2, position: 'relative' }}>
                    {/* 位置条：-π..π 归一化 */}
                    <div style={{
                      position: 'absolute', left: '50%', top: 0, bottom: 0, width: 2, background: 'var(--gg-accent)',
                      transform: `translateX(${Math.max(-50, Math.min(50, (a.position / Math.PI) * 50)) * 1 - 0}px)`,
                      marginLeft: `${Math.max(-50, Math.min(50, (a.position / Math.PI) * 50))}%`,
                    }} />
                  </div>
                  <span style={{ width: 64, textAlign: 'right', color: 'var(--semi-color-text-2)' }}>{a.position.toFixed(2)}</span>
                </div>
              ))}
            </div>
          ) : <Typography.Text type="tertiary">等待数据…</Typography.Text>}
        </Card>
      </div>
    </div>
  )
}

function Row({ k, v }: { k: string; v: string }): JSX.Element {
  return (
    <div style={{ display: 'flex', justifyContent: 'space-between', padding: '4px 0', fontSize: 13 }}>
      <span style={{ color: 'var(--semi-color-text-2)' }}>{k}</span><span>{v}</span>
    </div>
  )
}
