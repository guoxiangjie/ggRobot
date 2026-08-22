/**地图管理 — SLAM 建图 / 地图查看 / 重定位 / 实时位姿（1.0 Slam.vue 的 2.0 重写）
   多机语义：地图库在每台机器人本地（map.db），顶部切换机器人即切库；前端直连 agent（同自由页模式）。
   agent 端点全复用：/api/slam/mapping|maps|map|relocalize|origin|pose（零改动）。 */

import { useEffect, useState, useCallback, useRef } from 'react'
import { Button, Input, InputNumber, Select, Tag, Typography, Spin, Empty } from '@douyinfe/semi-ui'
import { Map as MapIcon, RefreshCw, Play, StopCircle, LocateFixed, Gamepad2 } from 'lucide-react'
import type { AxiosInstance } from 'axios'
import { toast } from '@/api/toast'
import { platformApi } from '@/api/platform'
import { makeAgentClient } from '@/api/agent'
import { useRobotsStore } from '@/stores/robots'

// agent 响应结构（routes/slam.py）
interface SlamMapMeta { map_id: string; map_name: string }
interface SlamMapData {
  ok?: boolean
  error?: string
  map_base64?: string
  map_info?: { width: number; height: number }
  navi_points?: { x: number; y: number }[]
  regions?: { type: number; drawing_type?: number; polygon?: number[][] }[]
}

export default function MapsPage(): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)
  const activeRobots = robots.filter((r) => r.online)

  const [robotId, setRobotId] = useState('')
  const [http, setHttp] = useState<AxiosInstance | null>(null)
  const [connErr, setConnErr] = useState('')

  // 地图列表 / 查看
  const [maps, setMaps] = useState<SlamMapMeta[]>([])
  const [selName, setSelName] = useState('')
  const [mapData, setMapData] = useState<SlamMapData | null>(null)
  const [loadingMap, setLoadingMap] = useState(false)
  const canvasRef = useRef<HTMLCanvasElement>(null)

  // 建图 / 重定位 / 位姿
  const [mapping, setMapping] = useState(false)
  const [mapName, setMapName] = useState('')
  const [relocMapId, setRelocMapId] = useState('')
  const [relocX, setRelocX] = useState(0)
  const [relocY, setRelocY] = useState(0)
  const [relocating, setRelocating] = useState(false)
  const [pose, setPose] = useState<Record<string, number>>({})

  const rb = robots.find((r) => r.id === robotId)
  const online = rb?.online ?? false

  // 默认选中第一台（在线优先；全离线也选中——离线态有明确提示而非空白）
  useEffect(() => {
    if (!robotId && robots.length) setRobotId((activeRobots[0] || robots[0]).id)
  }, [robots, activeRobots, robotId])

  // 切机器人：重建 agent client + 清状态 + 拉地图列表
  useEffect(() => {
    if (!robotId) return
    let alive = true
    setHttp(null); setConnErr(''); setMaps([]); setSelName(''); setMapData(null)
    setMapping(false); setRelocMapId(''); setPose({})
    void (async () => {
      try {
        const { data: r } = await platformApi().get(`/api/robots/${robotId}`)
        if (!alive) return
        if (!r.last_ip) { setConnErr('该机器人无 IP 记录'); return }
        const inst = makeAgentClient(r.last_ip, r.token)
        setHttp(() => inst)   // ⚠️ 实例是函数，必须 updater 包装，否则被 React 当 updater 执行
      } catch { if (alive) setConnErr('机器人信息获取失败') }
    })()
    return () => { alive = false }
  }, [robotId])

  const loadMaps = useCallback(async (): Promise<void> => {
    if (!http) return
    try {
      const { data } = await http.get('/api/slam/maps', { timeout: 8000 })
      if (data.error) toast.warning(data.error)
      setMaps(data.maps || [])
    } catch { setMaps([]) }
  }, [http])
  useEffect(() => { if (http && online) void loadMaps() }, [loadMaps, online])

  // 地图叠加层：导航点（绿）/ 虚拟墙（红多边形）—— 照 1.0 Slam.vue drawOverlay
  useEffect(() => {
    const cv = canvasRef.current
    const d = mapData
    if (!cv || !d?.map_info || !d.map_base64) return
    cv.width = d.map_info.width
    cv.height = d.map_info.height
    const ctx = cv.getContext('2d')
    if (!ctx) return
    ctx.clearRect(0, 0, cv.width, cv.height)
    ctx.fillStyle = '#3cc98e'
    for (const p of d.navi_points || []) {
      ctx.beginPath(); ctx.arc(p.x, p.y, 6, 0, Math.PI * 2); ctx.fill()
    }
    ctx.strokeStyle = '#f44b4b'; ctx.lineWidth = 4
    for (const r of d.regions || []) {
      if (r.type !== 2 || !r.polygon?.length) continue
      ctx.beginPath()
      r.polygon.forEach((pt, i) => (i ? ctx.lineTo(pt[0], pt[1]) : ctx.moveTo(pt[0], pt[1])))
      if (r.drawing_type === 1) ctx.closePath()
      ctx.stroke()
    }
  }, [mapData])

  async function viewMap(name: string): Promise<void> {
    setSelName(name)
    if (!http || !name) { setMapData(null); return }
    setLoadingMap(true)
    try {
      const { data } = await http.get(`/api/slam/map/${encodeURIComponent(name)}`, { timeout: 35000 })
      setMapData(data)
      if (!data.ok) toast.warning(data.error || '取图失败')
    } catch { toast.error('取图请求失败'); setMapData(null) }
    setLoadingMap(false)
  }

  async function doStopMapping(): Promise<void> {
    if (!http) return
    if (!mapName.trim()) { toast.warning('请输入地图名称'); return }
    try {
      const { data } = await http.post('/api/slam/mapping/stop', { map_name: mapName.trim() }, { timeout: 35000 })
      if (data.ok === false) { toast.warning(data.error || '保存失败'); return }
      setMapping(false); setMapName('')
      toast.success(`已保存：${mapName.trim()}`)
      void loadMaps()
    } catch { toast.error('保存请求失败') }
  }

  // 重定位选图 → 解析 origin 填默认 x/y
  useEffect(() => {
    if (!http || !relocMapId) return
    void (async () => {
      try {
        const { data } = await http.get(`/api/slam/origin/${relocMapId}`, { timeout: 6000 })
        if (data.ok && data.lines?.[1]) {
          const nums = String(data.lines[1]).match(/[-\d.]+/g)
          if (nums && nums.length >= 2) {
            setRelocX(Number(nums[0])); setRelocY(Number(nums[1]))
          }
        }
      } catch { /* origin 非关键 */ }
    })()
  }, [http, relocMapId])

  async function doRelocalize(): Promise<void> {
    if (!http) return
    if (!relocMapId) { toast.warning('请选择地图'); return }
    setRelocating(true)
    try {
      const { data } = await http.post('/api/slam/relocalize',
        { map_id: relocMapId, x: relocX, y: relocY }, { timeout: 35000 })
      if (data.ok) toast.success(`重定位成功：x=${data.pose?.x} y=${data.pose?.y}`, 5)
      else toast.warning(data.error || '重定位失败', 6)
    } catch { toast.error('重定位请求失败') }
    setRelocating(false)
  }

  // 实时位姿：在线时 1s 轮询，离线/切机自动停
  useEffect(() => {
    if (!http || !online) { setPose({}); return }
    let alive = true
    const timer = window.setInterval(async () => {
      try {
        const { data } = await http.get('/api/slam/pose', { timeout: 4000 })
        if (alive) setPose(data.pose || {})
      } catch { /* 单次失败忽略 */ }
    }, 1000)
    return () => { alive = false; clearInterval(timer) }
  }, [http, online])

  const mapImgUrl = mapData?.map_base64 ? `data:image/png;base64,${mapData.map_base64}` : ''

  if (!robots.length) {
    return <div className="page"><Empty title="暂无机器人" description="请先通过装机向导接入机器人" style={{ marginTop: 80 }} /></div>
  }

  return (
    <div className="page">
      <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'flex-start' }}>
        <div>
          <h1 className="page-title"><MapIcon style={{ verticalAlign: 'middle', marginRight: 8 }} />地图管理</h1>
          <p className="page-sub">SLAM 建图 / 地图查看（导航点·虚拟墙）/ 重定位 / 实时位姿</p>
        </div>
        <Select<string> value={robotId} style={{ width: 220 }}
          optionList={robots.map((r) => ({ label: `${r.name}${r.online ? '' : '（离线）'}`, value: r.id }))}
          onChange={(v) => setRobotId(String(v ?? ''))} />
      </div>

      {connErr && <Empty title="无法连接" description={connErr} style={{ marginTop: 60 }} />}
      {!connErr && !http && <div style={{ padding: 80, textAlign: 'center' }}><Spin size="large" /></div>}

      {http && !online && (
        <div className="choreo-run-bar">
          <div style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
            <Tag color="grey">离线</Tag>
            <Typography.Text>机器人当前离线——地图数据在机器人本地，建图/查看/重定位均需在线</Typography.Text>
          </div>
        </div>
      )}

      {http && (
        <>
          {/* 建图中警示条 */}
          {mapping && (
            <div className="choreo-run-bar">
              <div style={{ display: 'flex', alignItems: 'center', gap: 12, width: '100%' }}>
                <Tag color="orange">建图中</Tag>
                <Typography.Text>遥控机器人走一圈，回到此处停止并保存</Typography.Text>
                <Button size="small" icon={<Gamepad2 size={13} />}
                  onClick={() => void window.desktop?.openQuickCtrl()}>去遥控</Button>
              </div>
            </div>
          )}

          {/* 顶部三卡：建图 / 重定位 / 位姿 */}
          <div className="maps-grid">
            <div className="maps-card">
              <div className="maps-card-label">建图</div>
              {mapping ? (
                <div style={{ display: 'flex', gap: 8, alignItems: 'center', flexWrap: 'wrap' }}>
                  <Input value={mapName} onChange={setMapName} placeholder="地图名称" style={{ width: 140 }} />
                  <Button size="small" type="danger" theme="solid" icon={<StopCircle size={13} />}
                    onClick={() => void doStopMapping()}>停止并保存</Button>
                </div>
              ) : (
                <Button size="small" theme="solid" icon={<Play size={13} />} disabled={!online}
                  onClick={() => void window.desktop?.openMappingStudio()}>建图工作台</Button>
              )}
            </div>

            <div className="maps-card">
              <div className="maps-card-label">重定位</div>
              <div style={{ display: 'flex', gap: 6, alignItems: 'center', flexWrap: 'wrap' }}>
                <Select<string> value={relocMapId} placeholder="选择地图" style={{ width: 150 }} filter
                  optionList={maps.map((m) => ({ label: m.map_name, value: m.map_id }))}
                  onChange={(v) => setRelocMapId(String(v ?? ''))} />
                <InputNumber value={relocX} onChange={(v) => setRelocX(Number(v) || 0)} placeholder="x(像素)" style={{ width: 92 }} />
                <InputNumber value={relocY} onChange={(v) => setRelocY(Number(v) || 0)} placeholder="y(像素)" style={{ width: 92 }} />
                <Button size="small" theme="solid" icon={<LocateFixed size={13} />} loading={relocating} disabled={!online}
                  onClick={() => void doRelocalize()}>重定位</Button>
              </div>
            </div>

            <div className="maps-card">
              <div className="maps-card-label">实时位姿（lidar_odom）</div>
              <div style={{ display: 'flex', alignItems: 'center', gap: 10 }}>
                {pose.ts
                  ? <><Tag color="green" size="small">已定位</Tag>
                      <Typography.Text type="tertiary" size="small">x={pose.x} y={pose.y}</Typography.Text></>
                  : <Tag color="grey" size="small">无数据</Tag>}
              </div>
            </div>
          </div>

          {/* 地图列表 + 大图查看 */}
          <div style={{ display: 'flex', gap: 16, alignItems: 'flex-start' }}>
            <div style={{ width: 200, flexShrink: 0 }}>
              <div style={{ display: 'flex', alignItems: 'center', gap: 6, marginBottom: 8 }}>
                <Typography.Text type="tertiary" size="small" style={{ flex: 1 }}>地图（{maps.length}）</Typography.Text>
                <Button size="small" theme="borderless" icon={<RefreshCw size={12} />} onClick={() => void loadMaps()} />
              </div>
              {maps.length === 0
                ? <Typography.Text type="tertiary" size="small">尚未建图</Typography.Text>
                : maps.map((m) => (
                    <div key={m.map_id} className="maps-item" onClick={() => void viewMap(m.map_name)}
                      style={{ background: selName === m.map_name ? 'var(--semi-color-primary-light-default)' : 'transparent' }}>
                      <div style={{ fontWeight: 600, fontSize: 13, overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{m.map_name}</div>
                      <div style={{ fontSize: 10, color: 'var(--semi-color-text-2)' }}>id: {m.map_id}</div>
                    </div>
                  ))}
            </div>

            <div style={{ flex: 1, minWidth: 0 }}>
              {loadingMap
                ? <div style={{ padding: 100, textAlign: 'center' }}><Spin size="large" /></div>
                : mapImgUrl
                  ? <div className="maps-view">
                      <img src={mapImgUrl} className="maps-img" alt={selName} />
                      <canvas ref={canvasRef} className="maps-canvas" />
                    </div>
                  : mapData && mapData.ok === false
                    ? <Typography.Text type="danger">{mapData.error}</Typography.Text>
                    : <Typography.Text type="tertiary">选择左侧地图查看（导航点绿色 / 虚拟墙红色）</Typography.Text>}
            </div>
          </div>
        </>
      )}
    </div>
  )
}
