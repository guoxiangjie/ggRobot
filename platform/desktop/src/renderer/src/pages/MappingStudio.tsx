/**建图工作台（#/mapping-studio）— 实时点云 + 遥控 + 建图控制
   点云：WS 订阅 slam.cloud 二进制帧（agent 仅建图中推）
     帧格式：4B大端ms时间戳(publish_frame) + pose_x,pose_y,yaw(3×f32 LE) + n(u16) + n×(x,y int16 LE cm 机体系)
     前端按帧内位姿变换到世界系，10cm 网格去重累积；视图跟随机器人。
   遥控：键盘 WASD/QE + 屏上方向盘，同一条 WS 发 velocity（20Hz 铁律：持续发送/松开全零/失焦清键）。 */

import { useEffect, useRef, useState } from 'react'
import { Select, Button, Input, Tag } from '@douyinfe/semi-ui'
import { Play, StopCircle, Route } from 'lucide-react'
import { platformApi } from '@/api/platform'
import { makeAgentClient, agentWsUrl } from '@/api/agent'
import { useRobotsStore } from '@/stores/robots'

type Dir = 'fwd' | 'back' | 'left' | 'right' | 'tl' | 'tr'
const KEYMAP: Record<string, Dir> = { w: 'fwd', s: 'back', a: 'left', d: 'right', q: 'tl', e: 'tr' }
const SPEED = { forward: 0.35, lateral: 0.4, angular: 0.6 }
const DIR_AXIS: Record<Dir, { axis: 'forward' | 'lateral' | 'angular'; sign: 1 | -1 }> = {
  fwd: { axis: 'forward', sign: 1 }, back: { axis: 'forward', sign: -1 },
  left: { axis: 'lateral', sign: 1 }, right: { axis: 'lateral', sign: -1 },
  tl: { axis: 'angular', sign: 1 }, tr: { axis: 'angular', sign: -1 },
}

const SCALE = 42          // px / 米
const GRID_CM = 10        // 点云去重网格（厘米）

// 世界点存 Set（10cm 格打包 key），10 万格内性能无忧
const gkey = (gx: number, gy: number): number => (gx + 50000) * 100000 + (gy + 50000)

export default function MappingStudioPage(): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)

  const [robotId, setRobotId] = useState('')
  const [conn, setConn] = useState<{ ip: string; token: string } | null>(null)
  const [wsOpen, setWsOpen] = useState(false)
  const [mapping, setMapping] = useState(false)
  const [mapName, setMapName] = useState('')
  const [pressed, setPressed] = useState<Set<Dir>>(new Set())
  const [cloudCount, setCloudCount] = useState(0)
  const [pose, setPose] = useState<{ x: number; y: number; yaw: number } | null>(null)

  const canvasRef = useRef<HTMLCanvasElement>(null)
  const wsRef = useRef<WebSocket | null>(null)
  const keysRef = useRef(new Set<Dir>())
  const pointsRef = useRef(new Set<number>())
  const trailRef = useRef<number[]>([])
  const poseRef = useRef<{ x: number; y: number; yaw: number } | null>(null)
  const frameNRef = useRef(0)

  useEffect(() => {
    if (!robotId && robots.length) setRobotId((robots.find((r) => r.online) || robots[0]).id)
  }, [robots, robotId])

  useEffect(() => {
    if (!robotId) return
    let alive = true
    void platformApi().get(`/api/robots/${robotId}`).then(({ data }) => {
      if (alive && data.last_ip) setConn({ ip: data.last_ip, token: data.token })
    }).catch(() => { /* */ })
    return () => { alive = false }
  }, [robotId])

  // WS：点云订阅（binary）+ 遥控发送（同连接）
  useEffect(() => {
    if (!conn) return
    const ws = new WebSocket(agentWsUrl(conn.ip, conn.token))
    ws.binaryType = 'arraybuffer'
    wsRef.current = ws
    ws.onopen = (): void => {
      setWsOpen(true)
      ws.send(JSON.stringify({ v: 1, type: 'sub', topics: ['slam.cloud', 'slam.map'] }))
    }
    ws.onclose = (): void => {
      setWsOpen(false)
      keysRef.current.clear()
      setPressed(new Set())
    }
    ws.onmessage = (ev): void => {
      if (typeof ev.data === 'string') {
        // A3 数据源：slam.map JSON（cur_pos/lidar_points/trajectory 均为地图像素，res≈20mm/px）
        try {
          const msg = JSON.parse(ev.data) as { type?: string; topic?: string; data?: {
            cur_pos?: { position?: { u: number; v: number }; angle?: number }
            lidar_points?: Array<{ u: number; v: number }>; trajectory?: Array<{ u: number; v: number }> } }
          if (msg.type === 'event' && msg.topic === 'slam.map' && msg.data) {
            const PX_M = 0.02   // 20mm/px
            const pts = pointsRef.current
            for (const p of msg.data.lidar_points || []) {
              pts.add(gkey(Math.round(p.u * PX_M * 10), Math.round(p.v * PX_M * 10)))   // 米→10cm 格
            }
            const tr = trailRef.current
            for (const t of msg.data.trajectory || []) {
              const x = t.u * PX_M, y = t.v * PX_M
              const lastX = tr.length >= 2 ? tr[tr.length - 2] : null
              if (lastX == null || Math.hypot(x - lastX, y - tr[tr.length - 1]) > 0.3) tr.push(x, y)
            }
            const c = msg.data.cur_pos?.position
            if (c) poseRef.current = { x: c.u * PX_M, y: c.v * PX_M, yaw: msg.data.cur_pos?.angle ?? 0 }
            frameNRef.current++
            if (frameNRef.current % 4 === 1) { setPose(poseRef.current); setCloudCount(pts.size) }
          }
        } catch { /* 非 JSON 忽略 */ }
        return
      }
      const buf = ev.data as ArrayBuffer
      if (buf.byteLength < 18) return
      const dv = new DataView(buf)
      const px = dv.getFloat32(4, true)
      const py = dv.getFloat32(8, true)
      const yaw = dv.getFloat32(12, true)
      const n = dv.getUint16(16, true)
      const cos = Math.cos(yaw), sin = Math.sin(yaw)
      const pts = pointsRef.current
      for (let i = 0; i < n; i++) {
        const lx = dv.getInt16(18 + i * 4, true) / 100
        const ly = dv.getInt16(20 + i * 4, true) / 100
        const wx = px + lx * cos - ly * sin
        const wy = py + lx * sin + ly * cos
        pts.add(gkey(Math.round(wx * (100 / GRID_CM)), Math.round(wy * (100 / GRID_CM))))
      }
      // 轨迹（离上点 >0.3m 才记）
      const tr = trailRef.current
      const lastX = tr.length >= 2 ? tr[tr.length - 2] : null
      if (lastX == null || Math.hypot(px - lastX, py - tr[tr.length - 1]) > 0.3) {
        tr.push(px, py)
      }
      poseRef.current = { x: px, y: py, yaw }
      frameNRef.current++
      if (frameNRef.current % 8 === 1) {
        setPose(poseRef.current)
        setCloudCount(pts.size)
      }
    }
    return () => {
      ws.close()
      wsRef.current = null
    }
  }, [conn])

  // 渲染循环（150ms 重画：点云/轨迹/机器人，视图跟随）
  useEffect(() => {
    const timer = window.setInterval(() => {
      const cv = canvasRef.current
      if (!cv) return
      const ctx = cv.getContext('2d')
      if (!ctx) return
      const w = cv.width, h = cv.height
      ctx.clearRect(0, 0, w, h)
      const p = poseRef.current
      // 网格底（1m）
      ctx.strokeStyle = 'rgba(128,140,150,0.15)'
      ctx.lineWidth = 1
      for (let gx = 0; gx < w; gx += SCALE) { ctx.beginPath(); ctx.moveTo(gx, 0); ctx.lineTo(gx, h); ctx.stroke() }
      for (let gy = 0; gy < h; gy += SCALE) { ctx.beginPath(); ctx.moveTo(0, gy); ctx.lineTo(w, gy); ctx.stroke() }
      // 视图原点 = 机器人（居中）；无位姿时画布中心为世界原点
      const ox = w / 2 - (p?.x ?? 0) * SCALE
      const oy = h / 2 + (p?.y ?? 0) * SCALE   // 世界 y 向上 → 屏幕翻转
      const toS = (wx: number, wy: number): [number, number] => [ox + wx * SCALE, oy - wy * SCALE]
      // 轨迹
      const tr = trailRef.current
      if (tr.length >= 4) {
        ctx.strokeStyle = 'rgba(77,166,255,0.85)'
        ctx.lineWidth = 2
        ctx.beginPath()
        ctx.moveTo(...toS(tr[0], tr[1]))
        for (let i = 2; i < tr.length; i += 2) ctx.lineTo(...toS(tr[i], tr[i + 1]))
        ctx.stroke()
      }
      // 点云（10cm 格）
      ctx.fillStyle = 'rgba(70,80,90,0.78)'
      const dots = pointsRef.current
      for (const k of dots) {
        const gx = Math.floor(k / 100000) - 50000
        const gy = (k % 100000) - 50000
        const [sx, sy] = toS(gx * GRID_CM / 100, gy * GRID_CM / 100)
        if (sx < -4 || sx > w + 4 || sy < -4 || sy > h + 4) continue
        ctx.fillRect(sx - 1, sy - 1, 2.4, 2.4)
      }
      // 机器人（位置 + 朝向）
      const [rx, ry] = p ? toS(p.x, p.y) : [w / 2, h / 2]
      ctx.save()
      ctx.translate(rx, ry)
      ctx.rotate(-(p?.yaw ?? 0))
      ctx.fillStyle = '#4da6ff'
      ctx.beginPath()
      ctx.moveTo(9, 0); ctx.lineTo(-6, 6); ctx.lineTo(-6, -6); ctx.closePath(); ctx.fill()
      ctx.restore()
    }, 150)
    return () => clearInterval(timer)
  }, [])

  // 键盘遥控（窗口聚焦生效；失焦清键）
  useEffect(() => {
    const sync = (): void => setPressed(new Set(keysRef.current))
    const down = (ev: KeyboardEvent): void => {
      const d = KEYMAP[ev.key.toLowerCase()]
      if (!d) return
      ev.preventDefault()
      keysRef.current.add(d); sync()
    }
    const up = (ev: KeyboardEvent): void => {
      const d = KEYMAP[ev.key.toLowerCase()]
      if (!d) return
      keysRef.current.delete(d); sync()
    }
    const onBlur = (): void => { keysRef.current.clear(); sync() }
    window.addEventListener('keydown', down)
    window.addEventListener('keyup', up)
    window.addEventListener('blur', onBlur)
    return () => {
      window.removeEventListener('keydown', down)
      window.removeEventListener('keyup', up)
      window.removeEventListener('blur', onBlur)
    }
  }, [])

  // 20Hz 速度发送（WS 常开）
  useEffect(() => {
    const timer = window.setInterval(() => {
      const ws = wsRef.current
      if (!ws || ws.readyState !== WebSocket.OPEN) return
      let forward = 0, lateral = 0, angular = 0
      for (const k of keysRef.current) {
        const { axis, sign } = DIR_AXIS[k]
        if (axis === 'forward') forward += SPEED.forward * sign
        else if (axis === 'lateral') lateral += SPEED.lateral * sign
        else angular += SPEED.angular * sign
      }
      ws.send(JSON.stringify({ v: 1, type: 'velocity', forward: +forward.toFixed(2), lateral: +lateral.toFixed(2), angular: +angular.toFixed(2) }))
    }, 50)
    return () => {
      clearInterval(timer)
      wsRef.current?.send(JSON.stringify({ v: 1, type: 'velocity', forward: 0, lateral: 0, angular: 0 }))
    }
  }, [])

  // 建图中关窗确认（丢弃轨迹警示；保存请先停止）
  useEffect(() => {
    const h = (e: BeforeUnloadEvent): void => {
      if (mapping) e.returnValue = '建图进行中：关窗将丢失未保存的扫描，请先「停止并保存」'
    }
    window.onbeforeunload = h
    return () => { window.onbeforeunload = null }
  }, [mapping])

  async function start(): Promise<void> {
    if (!conn) return
    try {
      const { data } = await makeAgentClient(conn.ip, conn.token)
        .post('/api/slam/mapping/start', null, { timeout: 10000 })
      if (data.ok === false) { return }
      setMapping(true)
      pointsRef.current.clear(); trailRef.current = []; frameNRef.current = 0
    } catch { /* */ }
  }

  async function stop(): Promise<void> {
    if (!conn) return
    if (!mapName.trim()) return
    try {
      await makeAgentClient(conn.ip, conn.token)
        .post('/api/slam/mapping/stop', { map_name: mapName.trim() }, { timeout: 35000 })
      setMapping(false)
      window.close()   // 主地图页 focus 自动刷新
    } catch { /* */ }
  }

  const press = (d: Dir): void => { keysRef.current.add(d); setPressed(new Set(keysRef.current)) }
  const release = (d: Dir): void => { keysRef.current.delete(d); setPressed(new Set(keysRef.current)) }
  const bind = (d: Dir): React.HTMLAttributes<HTMLDivElement> => ({
    onPointerDown: () => press(d), onPointerUp: () => release(d),
    onPointerLeave: () => release(d), onPointerCancel: () => release(d),
  })
  const cell = (d: Dir, extraStyle?: React.CSSProperties): JSX.Element => {
    const on = pressed.has(d)
    const labels: Record<Dir, string> = { fwd: '↑', back: '↓', left: '←', right: '→', tl: '↺', tr: '↻' }
    return (
      <div key={d} className={`ms-btn${on ? ' on' : ''}`} {...bind(d)} style={extraStyle}>
        {labels[d]}
        <span className="ms-key">{{ fwd: 'W', back: 'S', left: 'A', right: 'D', tl: 'Q', tr: 'E' }[d]}</span>
      </div>
    )
  }

  return (
    <div className="ms">
      <div className="titlebar" style={{ paddingLeft: 84, paddingRight: 16 }}>
        <span className="title" style={{ fontSize: 13, fontWeight: 700 }}>建图工作台</span>
        <div className="spacer" />
        <Tag size="small" color={wsOpen ? 'green' : 'grey'}>{wsOpen ? '已连接' : '未连接'}</Tag>
      </div>

      <div style={{ padding: '12px 16px', display: 'flex', flexDirection: 'column', gap: 10, height: 'calc(100% - 40px)' }}>
        {/* 工具行 */}
        <div style={{ display: 'flex', alignItems: 'center', gap: 10 }}>
          <Select<string> value={robotId} style={{ width: 170 }} disabled={mapping}
            optionList={robots.map((r) => ({ label: `${r.name}${r.online ? '' : '（离线）'}`, value: r.id }))}
            onChange={(v) => { setConn(null); setRobotId(String(v ?? '')) }} />
          {!mapping
            ? <Button theme="solid" size="small" icon={<Play size={13} />} disabled={!wsOpen}
                onClick={() => void start()}>开始建图</Button>
            : <Button theme="solid" size="small" type="danger" icon={<StopCircle size={13} />}
                disabled={!mapName.trim()} onClick={() => void stop()}>停止并保存</Button>}
          {mapping && (
            <Input size="small" value={mapName} onChange={setMapName} placeholder="地图名称" style={{ width: 150 }} />
          )}
          <div style={{ flex: 1 }} />
          <span style={{ fontSize: 11, color: 'var(--semi-color-text-2)', display: 'inline-flex', gap: 4, alignItems: 'center' }}>
            <Route size={12} />
            {pose ? `x ${pose.x.toFixed(1)} y ${pose.y.toFixed(1)}` : '无位姿'} · {cloudCount} 点
          </span>
        </div>

        {/* 点云画布 */}
        <div className="ms-canvas-wrap">
          <canvas ref={canvasRef} width={732} height={330} className="ms-canvas" />
          {!mapping && (
            <div className="ms-hint-overlay">
              {mapping ? '' : '开始建图后此处实时显示激光点云（墙体轮廓）与行走轨迹'}
            </div>
          )}
        </div>

        {/* 遥控方向盘 */}
        <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'center', gap: 18 }}>
          <div className="ms-pad">
            <div style={{ gridColumn: 2 }}>{cell('fwd')}</div>
            <div style={{ gridColumn: 1, gridRow: 2 }}>{cell('left')}</div>
            <div style={{ gridColumn: 2, gridRow: 2 }}>{cell('back')}</div>
            <div style={{ gridColumn: 3, gridRow: 2 }}>{cell('right')}</div>
          </div>
          <div style={{ display: 'flex', flexDirection: 'column', gap: 6 }}>
            {cell('tl', { width: 72 })}{cell('tr', { width: 72 })}
          </div>
        </div>
        <div className="ms-hint">按住即走 · 键盘 WASD/QE · 窗口切走自动停</div>
      </div>
    </div>
  )
}
