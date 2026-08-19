/**监控大盘 — 全局 hub store 驱动，所有机器人状态一屏看*/

import { useNavigate } from 'react-router-dom'
import { Card, Tag, Progress, Button } from '@douyinfe/semi-ui'
import { Bot, ScanSearch, Plus, ArrowRight } from 'lucide-react'
import { useRobotsStore } from '@/stores/robots'
import { useAppStore } from '@/stores/app'
import { EmptyBox } from '@/components/StateViews'

export default function Overview(): JSX.Element {
  const nav = useNavigate()
  const sidecarReady = useAppStore((s) => s.sidecarReady)
  const { summaries: robots, hubConnected } = useRobotsStore()

  const online = robots.filter((r) => r.online).length

  return (
    <div className="page">
      <h1 className="page-title">总览</h1>
      <p className="page-sub">
        {hubConnected ? `${robots.length} 台已登记 · ${online} 台在线` : '正在连接平台服务...'}
      </p>

      {robots.length === 0 && hubConnected && (
        <Card className="gg-card" bodyStyle={{ padding: 0 }}>
          <EmptyBox
            title="还没有机器人接入"
            description={
              <div style={{ display: 'grid', gap: 6, fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                <span>1. 机器人上安装 agent（首次：装机向导推 deb）</span>
                <span>2. 扫描网段发现设备</span>
                <span>3. 点击「配对」输入 SSH 密码，秒级接入</span>
              </div>
            }
            action={
              <div style={{ display: 'flex', gap: 10 }}>
                <Button icon={<ScanSearch size={14} />} onClick={() => nav('/robots')}>
                  去扫描网段
                </Button>
                <Button theme="solid" icon={<Plus size={14} />} onClick={() => nav('/robots/add')}>
                  装机向导
                </Button>
              </div>
            }
          />
        </Card>
      )}

      {robots.length > 0 && (
        <div className="robot-grid">
          {robots.map((r) => (
            <div key={r.id} onClick={() => nav(`/robot/${r.id}/dashboard`)}
              style={{ opacity: r.online ? 1 : 0.55, transition: 'opacity 0.3s' }}>
              <Card className="gg-card hoverable" bodyStyle={{ padding: 16 }}>
                <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 12 }}>
                  <div style={{
                    width: 38, height: 38, borderRadius: 10, display: 'flex',
                    alignItems: 'center', justifyContent: 'center',
                    background: r.online ? 'rgba(60,201,142,0.14)' : 'var(--semi-color-fill-1)',
                  }}>
                    <Bot size={20} color={r.online ? 'var(--gg-success)' : 'var(--semi-color-text-2)'} />
                  </div>
                  <div style={{ flex: 1, minWidth: 0 }}>
                    <div style={{ fontWeight: 600, fontSize: 14 }}>{r.name}</div>
                    <div style={{ fontSize: 11, color: 'var(--semi-color-text-2)' }}>
                      {r.model.toUpperCase()} · SN {r.sn.slice(-6)}
                    </div>
                  </div>
                  {r.online && <span className="pulse-dot" />}
                </div>

                {r.battery_soc != null && (
                  <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
                    <Progress percent={r.battery_soc} showInfo={false}
                      stroke={r.battery_soc > 30 ? 'var(--gg-success)' : 'var(--gg-danger)'}
                      style={{ flex: 1, margin: 0 }} />
                    <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{r.battery_soc}%</span>
                  </div>
                )}

                <div style={{ marginTop: 10, display: 'flex', gap: 6, alignItems: 'center' }}>
                  <Tag size="small" color={r.online ? 'green' : 'grey'} shape="circle">
                    {r.online ? '在线' : '离线'}
                  </Tag>
                  {r.status === 'pending' && <Tag size="small" color="orange" shape="circle">装机中</Tag>}
                  {r.token_ok && <Tag size="small" color="blue" shape="circle">已配对</Tag>}
                  {r.version && <Tag size="small" shape="circle">v{r.version}</Tag>}
                  <div style={{ flex: 1 }} />
                  <ArrowRight size={14} color="var(--semi-color-text-2)" />
                </div>
              </Card>
            </div>
          ))}
        </div>
      )}

      {!sidecarReady && <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>平台服务初始化中…</div>}
    </div>
  )
}
