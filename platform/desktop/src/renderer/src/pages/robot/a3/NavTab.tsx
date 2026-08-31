/**A3 导航页（独有能力）— 地图选择 → 拓扑点列表 → 到点导航 + 任务控制（暂停/恢复/取消）
   前置：机器人已重定位 + MOTION 模式（未满足时 agent/PNC 会拒绝，错误提示透出） */

import { useEffect, useRef, useState } from 'react'
import { Card, Button, Typography, Select, Table, Banner } from '@douyinfe/semi-ui'
import { Compass, Play, Pause, Square, RefreshCw, MapPin } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from '../RobotLayout'

interface MapItem { map_id: string; map_name: string }
interface TopoPoint { point_id: number; name: string; pose?: { position?: { x?: number; y?: number } } }

export default function NavTab(): JSX.Element {
  const { ip, token } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const [maps, setMaps] = useState<MapItem[]>([])
  const [curMap, setCurMap] = useState('')
  const [points, setPoints] = useState<TopoPoint[]>([])
  const [task, setTask] = useState<{ task_id?: string; state?: string } | null>(null)
  const [busy, setBusy] = useState(false)

  const loadMaps = (): void => {
    void http.get('/api/slam/maps').then(({ data }) => {
      setMaps(data.maps || [])
      if (!curMap && data.maps?.[0]) setCurMap(data.maps[0].map_id)
    }).catch(() => {})
    void http.get('/api/slam/map/current').then(({ data }) => {
      if (data.map_id) setCurMap((c) => c || data.map_id)
    }).catch(() => {})
  }
  useEffect(() => { loadMaps() }, [http])

  // 地图切换 → 拉拓扑点
  useEffect(() => {
    if (!curMap) return
    void http.get(`/api/slam/map/${curMap}`).then(({ data }) => {
      setPoints((data.topo?.points || []) as TopoPoint[])
    }).catch(() => setPoints([]))
  }, [curMap, http])

  // 任务状态轮询（运行中 1s，空闲 5s）
  useEffect(() => {
    const t = window.setInterval(() => {
      void http.get('/api/nav/state').then(({ data }) => {
        if (data.ok) setTask({ task_id: data.task_id, state: data.state })
      }).catch(() => {})
    }, ['RUNNING', 'PAUSED'].includes(task?.state ?? '') ? 1000 : 5000)
    return () => clearInterval(t)
  }, [task?.state, http])

  const running = task?.state === 'RUNNING'

  async function goto(p: TopoPoint): Promise<void> {
    if (!curMap) return
    setBusy(true)
    try {
      const { data } = await http.post('/api/nav/goto', {
        kind: 'goal', map_id: curMap, target_id: p.point_id,
      })
      if (data.ok) { toast.success(`导航中 → ${p.name}`); setTask({ task_id: data.task_id, state: 'RUNNING' }) }
      else toast.error(data.error || '导航下发失败')
    } catch { toast.error('导航下发失败') } finally { setBusy(false) }
  }
  async function control(op: 'pause' | 'resume' | 'cancel'): Promise<void> {
    try {
      await http.post(`/api/nav/control?op=${op}&task_id=${task?.task_id ?? 0}`)
      toast.success(op === 'pause' ? '已暂停' : op === 'resume' ? '已恢复' : '已取消')
    } catch { toast.error('操作失败') }
  }

  return (
    <div style={{ display: 'flex', flexDirection: 'column', gap: 16 }}>
      {task?.state === 'RUNNING' && (
        <Banner type="info" closeIcon={null}
          description={<div style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
            <Compass size={15} className="spin" /> 导航任务执行中（task {String(task.task_id).slice(-6)}）
            <Button size="small" icon={<Pause size={12} />} onClick={() => void control('pause')}>暂停</Button>
            <Button size="small" type="danger" theme="borderless" icon={<Square size={12} />}
              onClick={() => void control('cancel')}>取消</Button>
          </div>} />
      )}
      {task?.state === 'PAUSED' && (
        <Banner type="warning" closeIcon={null}
          description={<div style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
            任务已暂停
            <Button size="small" icon={<Play size={12} />} onClick={() => void control('resume')}>恢复</Button>
            <Button size="small" type="danger" theme="borderless" onClick={() => void control('cancel')}>取消</Button>
          </div>} />
      )}

      <Card title={<span><Compass size={15} style={{ verticalAlign: -2, marginRight: 6 }} />定点导航</span>}
        headerExtraContent={
          <div style={{ display: 'flex', gap: 8 }}>
            <Select<string> value={curMap} onChange={(v) => setCurMap(String(v ?? ''))} style={{ width: 200 }}
              placeholder="选择地图" optionList={maps.map((m) => ({ label: `${m.map_name} (${m.map_id.slice(-6)})`, value: m.map_id }))} />
            <Button size="small" theme="borderless" icon={<RefreshCw size={13} />} onClick={loadMaps} />
          </div>
        }>
        {maps.length === 0
          ? <Typography.Text type="tertiary">无已建地图——先在「系统」页或 AimMaster 完成建图</Typography.Text>
          : points.length === 0
            ? <Typography.Text type="tertiary">此地图无导航点（AimMaster → 地图 → 点位标注后可用）</Typography.Text>
            : (
              <Table<TopoPoint> dataSource={points} pagination={false} size="small"
                rowKey="point_id"
                columns={[
                  { title: 'ID', dataIndex: 'point_id', width: 60 },
                  { title: '名称', dataIndex: 'name' },
                  {
                    title: '坐标', width: 160,
                    render: (_v, p) => <Typography.Text type="tertiary" size="small">
                      {p.pose?.position ? `${p.pose.position.x?.toFixed(2)}, ${p.pose.position.y?.toFixed(2)}` : '—'}
                    </Typography.Text>,
                  },
                  {
                    title: '', width: 110,
                    render: (_v, p) => <Button size="small" theme="solid" icon={<MapPin size={12} />}
                      loading={busy && running} disabled={running}
                      onClick={() => void goto(p)}>到点</Button>,
                  },
                ]} />
            )}
      </Card>

      <Typography.Text type="tertiary" size="small">
        前置条件：机器人已在当前地图完成重定位，且处于 MOTION 模式；到点精度约 0.4m。
      </Typography.Text>
    </div>
  )
}
