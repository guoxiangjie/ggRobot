/**灵创资源 — 实时拉取机器人动作资源，按全身/手臂分组网格播放
   播放结果二次判定（1.0 踩坑：aimdk 可能 code=0 但 message 含 failed）*/

import { useEffect, useRef, useState, useMemo } from 'react'
import { Card, Button, Tag, Typography } from '@douyinfe/semi-ui'
import { Sparkles, Play, RefreshCw } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from './RobotLayout'

interface RobotResource { resource_key: string; name: string; version: string; type?: string }

/** 类型推断与后端一致：resource_key 含 onnx → 全身 BODY，否则手臂 ARM */
function rType(r: RobotResource): 'BODY' | 'ARM' {
  return r.resource_key.toLowerCase().includes('onnx') ? 'BODY' : 'ARM'
}

export default function LinkcraftTab(): JSX.Element {
  const { ip, token } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const [resources, setResources] = useState<RobotResource[]>([])
  const [loading, setLoading] = useState(false)
  const [playing, setPlaying] = useState('')
  const [filter, setFilter] = useState<'' | 'BODY' | 'ARM'>('')

  async function load(): Promise<void> {
    setLoading(true)
    try {
      const { data } = await http({ method: 'get', url: '/api/resources', timeout: 15000 })
      setResources(data.resources ?? [])
      if (data.error) toast.warning(data.error)
    } catch {
      toast.error('拉取灵创资源失败')
    }
    setLoading(false)
  }

  useEffect(() => { void load() }, [http])

  const filtered = useMemo(() => resources.filter((r) => {
    if (filter && rType(r) !== filter) return false
    return true
  }), [resources, filter])

  const groups = [
    { label: '全身动作', match: (r: RobotResource) => rType(r) === 'BODY' },
    { label: '手臂动作', match: (r: RobotResource) => rType(r) === 'ARM' },
  ]

  async function play(r: RobotResource): Promise<void> {
    setPlaying(r.resource_key)
    try {
      const { data } = await http.post('/api/resources/play', {
        resource_key: r.resource_key,
        version: r.version,
        resource_type: rType(r),
      }, { timeout: 20000 })
      // 二次判定：code=0 但 message 含 failed/失败 → 实际未成功
      const failed = !!data.message && /failed|失败/i.test(data.message)
      if (data.ok && !failed) toast.success(`已播放：${r.name}`)
      else toast.warning(data.message || data.error || '播放未成功', 6)
    } catch {
      toast.error('播放请求失败')
    }
    setPlaying('')
  }

  return (
    <Card
      title={<span><Sparkles size={15} style={{ verticalAlign: -2, marginRight: 6 }} />灵创动作资源（{resources.length}）</span>}
      headerExtraContent={
        <div style={{ display: 'flex', gap: 8, alignItems: 'center' }}>
          {([['', '全部'], ['BODY', '全身'], ['ARM', '手臂']] as const).map(([v, label]) => (
            <Tag key={v} size="small" shape="circle" type={filter === v ? 'solid' : 'ghost'}
              style={{ cursor: 'pointer' }} onClick={() => setFilter(v as '' | 'BODY' | 'ARM')}>
              {label}
            </Tag>
          ))}
          <Button size="small" icon={<RefreshCw size={13} />} loading={loading} onClick={() => void load()} />
        </div>
      }
    >
      {filtered.length === 0 ? (
        <Typography.Text type="tertiary">
          {resources.length === 0 ? '机器人上暂无灵创资源（或离线）' : '无匹配结果'}
        </Typography.Text>
      ) : (
        groups.filter((g) => filtered.some(g.match)).map((g) => (
          <div key={g.label} style={{ marginBottom: 12 }}>
            <div style={{
              fontSize: 12, color: 'var(--semi-color-text-2)', fontWeight: 600,
              margin: '6px 0 8px', display: 'flex', alignItems: 'center', gap: 8,
            }}>
              {g.label} · {filtered.filter(g.match).length}
              <div style={{ flex: 1, height: 1, background: 'var(--semi-color-border)' }} />
            </div>
            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(180px, 1fr))', gap: 8 }}>
              {filtered.filter(g.match).map((r) => (
                <Button key={r.resource_key} size="small" loading={playing === r.resource_key}
                  icon={<Play size={12} />}
                  style={{ borderRadius: 8, padding: '10px 12px', height: 'auto', whiteSpace: 'normal' }}
                  onClick={() => void play(r)}>
                  {r.name}
                </Button>
              ))}
            </div>
          </div>
        ))
      )}
    </Card>
  )
}
