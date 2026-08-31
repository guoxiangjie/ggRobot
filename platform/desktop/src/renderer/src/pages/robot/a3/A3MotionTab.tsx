/**A3 动作页 — 资源动作（真实时长）+ 高级控制（播放/暂停/停止/循环）+ 舞蹈
   与 X2 ControlTab 完全不同数据模型：motion_id=资源路径，duration 真实秒 */

import { useEffect, useRef, useState } from 'react'
import { Card, Button, Tag, Typography, Input, Empty, Progress } from '@douyinfe/semi-ui'
import { PersonStanding, Music, Pause, Square, Play, RotateCcw, RefreshCw } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from '../RobotLayout'

interface Motion { id: string; name: string; duration?: number }
interface Dance { name: string; path: string; duration?: number }

export default function A3MotionTab(): JSX.Element {
  const { ip, token } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const [motions, setMotions] = useState<Motion[]>([])
  const [dances, setDances] = useState<Dance[]>([])
  const [filter, setFilter] = useState('')
  const [playing, setPlaying] = useState<string | null>(null)
  const [elapsed, setElapsed] = useState(0)

  const load = (refresh = false): void => {
    void http.get(`/api/motions${refresh ? '?refresh=true' : ''}`).then(({ data }) =>
      setMotions(data.motions || [])).catch(() => {})
    void http.get(`/api/dances${refresh ? '?refresh=true' : ''}`).then(({ data }) =>
      setDances(data.dances || [])).catch(() => {})
  }
  useEffect(() => { load() }, [http])

  // 播放进度（本地按真实时长模拟）
  useEffect(() => {
    if (!playing) { setElapsed(0); return }
    const m = motions.find((x) => x.id === playing)
    const total = (m?.duration ?? 5) * 1000
    const t0 = Date.now()
    const t = window.setInterval(() => {
      const e = Date.now() - t0
      setElapsed(Math.min(1, e / total))
      if (e >= total) { window.clearInterval(t); setPlaying(null) }
    }, 100)
    return () => window.clearInterval(t)
  }, [playing, motions])

  async function play(id: string, repeat = false): Promise<void> {
    const m = motions.find((x) => x.id === id)
    try {
      await http.post('/api/motion', {
        motion_id: id, duration_ms: Math.round((m?.duration ?? 10) * 1000 + 2000),
        repeat,
      })
      setPlaying(id)
    } catch { toast.error('动作下发失败') }
  }
  async function ctrl(kind: 'pause' | 'stop'): Promise<void> {
    try {
      await http.post('/api/motion', kind === 'stop'
        ? { motion_id: '', reset: true }
        : { motion_id: '', pause: true })
      if (kind === 'stop') setPlaying(null)
      toast.success(kind === 'stop' ? '已停止' : '已暂停')
    } catch { toast.error('操作失败') }
  }
  async function playDance(path: string): Promise<void> {
    try {
      await http.post('/api/dance', { command: 'Start', path })
      toast.success('舞蹈开始（注意周围两米无障碍）')
    } catch { toast.error('舞蹈下发失败') }
  }

  const shown = motions.filter((m) => !filter || m.name.includes(filter))
  const cur = motions.find((x) => x.id === playing)

  return (
    <div style={{ display: 'flex', flexDirection: 'column', gap: 16 }}>
      {/* 控制条 */}
      <Card>
        <div style={{ display: 'flex', gap: 10, alignItems: 'center' }}>
          <Play size={16} color="var(--gg-success)" />
          <div style={{ flex: 1, minWidth: 0 }}>
            <Typography.Text size="small" ellipsis={{ showTooltip: true }}>
              {cur ? `${cur.name}（${cur.duration ?? '?'}s）` : '空闲'}
            </Typography.Text>
            {cur && <Progress percent={Math.round(elapsed * 100)} style={{ marginTop: 4, marginBottom: 0 }} />}
          </div>
          <Button size="small" icon={<Pause size={13} />} onClick={() => void ctrl('pause')}>暂停</Button>
          <Button size="small" type="danger" theme="borderless" icon={<Square size={13} />} onClick={() => void ctrl('stop')}>停止</Button>
        </div>
      </Card>

      <div style={{ display: 'grid', gridTemplateColumns: '1.4fr 1fr', gap: 16 }}>
        {/* 动作网格 */}
        <Card title={<span><PersonStanding size={15} style={{ verticalAlign: -2, marginRight: 6 }} />预设动作（{shown.length}）</span>}
          headerExtraContent={
            <div style={{ display: 'flex', gap: 6 }}>
              <Input size="small" value={filter} onChange={setFilter} placeholder="搜索" style={{ width: 120 }} />
              <Button size="small" theme="borderless" icon={<RefreshCw size={13} />} onClick={() => load(true)} />
            </div>
          }>
          {shown.length === 0
            ? <Empty title="无动作资源" description="机器人资源库为空或离线" style={{ padding: 40 }} />
            : (
              <div className="robot-grid" style={{ maxHeight: 560, overflow: 'auto' }}>
                {shown.map((m) => (
                  <div key={m.id} className="gg-card free-item">
                    <div style={{ fontWeight: 700, fontSize: 13, display: 'flex', justifyContent: 'space-between', gap: 6 }}>
                      <span style={{ overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{m.name}</span>
                      <Tag size="small" shape="circle">{m.duration ?? '?'}s</Tag>
                    </div>
                    <div style={{ display: 'flex', gap: 4, marginTop: 8 }}>
                      <Button size="small" theme="solid" icon={<Play size={12} />} onClick={() => void play(m.id)}>播放</Button>
                      <Button size="small" icon={<RotateCcw size={12} />} onClick={() => void play(m.id, true)}>循环</Button>
                    </div>
                  </div>
                ))}
              </div>
            )}
        </Card>

        {/* 舞蹈 */}
        <Card title={<span><Music size={15} style={{ verticalAlign: -2, marginRight: 6 }} />舞蹈（{dances.length}）</span>}>
          {dances.length === 0
            ? <Typography.Text type="tertiary" size="small">无舞蹈资源</Typography.Text>
            : (
              <div style={{ display: 'grid', gap: 8 }}>
                {dances.map((d) => (
                  <div key={d.path} className="gg-card free-item" style={{ padding: 12 }}>
                    <div style={{ fontWeight: 700, fontSize: 13 }}>{d.name}</div>
                    <Button size="small" theme="solid" icon={<Play size={12} />} style={{ marginTop: 8 }}
                      onClick={() => void playDance(d.path)}>开始舞蹈</Button>
                  </div>
                ))}
              </div>
            )}
          <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 10 }}>
            ⚠️ 舞蹈为全身动作，确保周围两米无障碍
          </Typography.Text>
        </Card>
      </div>
    </div>
  )
}
