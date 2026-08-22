/**展馆 — 3D 集群展厅：多机摆放（在线实体/离线半透明）、拖拽浏览、点击部件、关节滑杆
   由 1.0 Model3D.vue 重写为 React；模型 = 官方 GLB（X2Model.ts 加载/克隆）。
   多型号扩展：MODEL_REGISTRY 按机器人 model 字段分发（未知型号占位胶囊）。 */

import { useEffect, useRef, useState, useCallback } from 'react'
import { Spin, Tag, Typography, Slider, Button, Empty } from '@douyinfe/semi-ui'
import { Boxes, Crosshair, RotateCcw } from 'lucide-react'
import * as THREE from 'three'
import { createScene, applyTheme, isLightTheme, type SceneContext } from '@/three/SceneSetup'
import { loadX2Model, makeInstance, setJointAngle, partLabel, type X2ModelInstance } from '@/three/X2Model'
import { useRobotsStore } from '@/stores/robots'

// 部件改色调色板（1.0 同款精选）
const PALETTE = ['#f0f4f8', '#b0bec5', '#546e7a', '#4da6ff', '#4ade80', '#f87171', '#fbbf24', '#a78bfa']

interface SelPart { robotId: string; robotName: string; link: string; jointName?: string }

export default function HallPage(): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)
  const canvasRef = useRef<HTMLCanvasElement>(null)
  const wrapRef = useRef<HTMLDivElement>(null)
  const ctxRef = useRef<SceneContext | null>(null)
  const instancesRef = useRef(new Map<string, X2ModelInstance>())
  const highlightRef = useRef<THREE.Mesh | null>(null)
  const rafRef = useRef(0)

  const [ready, setReady] = useState(false)
  const [progress, setProgress] = useState(0)
  const [selRobot, setSelRobot] = useState('')
  const [selPart, setSelPart] = useState<SelPart | null>(null)
  const [angleDeg, setAngleDeg] = useState(0)

  // ── 场景初始化（一次） ──
  useEffect(() => {
    const canvas = canvasRef.current
    if (!canvas) return
    const ctx = createScene(canvas)
    ctxRef.current = ctx

    const resize = (): void => {
      const w = wrapRef.current?.clientWidth ?? 0
      const h = wrapRef.current?.clientHeight ?? 0
      if (!w || !h) return
      ctx.renderer.setPixelRatio(window.devicePixelRatio)
      ctx.renderer.setSize(w, h, false)
      ctx.camera.aspect = w / h
      ctx.camera.updateProjectionMatrix()
    }
    resize()
    const ro = new ResizeObserver(resize)
    if (wrapRef.current) ro.observe(wrapRef.current)

    const render = (): void => {
      rafRef.current = requestAnimationFrame(render)
      ctx.controls.update()
      ctx.renderer.render(ctx.scene, ctx.camera)
    }
    render()

    // 主题跟随（body theme-mode 变化 → 3D 配色）
    const themeObs = new MutationObserver(() => applyTheme(ctx, isLightTheme()))
    themeObs.observe(document.body, { attributes: true, attributeFilter: ['theme-mode'] })

    void loadX2Model(setProgress).then(() => setReady(true))

    return () => {
      cancelAnimationFrame(rafRef.current)
      ro.disconnect()
      themeObs.disconnect()
      ctx.renderer.dispose()
      ctxRef.current = null
      instancesRef.current.clear()
    }
  }, [])

  // ── 机器人列表 → 场景实例同步（增删 + 在线离线 + 摆位） ──
  useEffect(() => {
    const ctx = ctxRef.current
    if (!ctx || !ready) return
    const map = instancesRef.current

    for (const r of robots) {
      if (!map.has(r.id)) {
        if (r.model === 'x2') {
          const inst = makeInstance()
          map.set(r.id, inst)
          ctx.scene.add(inst.group)
        }
        // 未知型号：暂不放（占位胶囊后续型号注册表再补）
      }
    }
    for (const [rid, inst] of map) {
      if (!robots.find((r) => r.id === rid)) {
        ctx.scene.remove(inst.group)
        map.delete(rid)
      }
    }
    // 摆位：横向排开居中；在线实体 / 离线半透明
    const list = robots.filter((r) => map.has(r.id))
    list.forEach((r, i) => {
      const inst = map.get(r.id)!
      inst.group.position.set((i - (list.length - 1) / 2) * 1.8, 0, 0)
      inst.setDim(!r.online)
    })
    // 默认选中第一台
    if (!selRobot && list.length) setSelRobot(list[0].id)
  }, [robots, ready, selRobot])

  // 聚焦选中机器人
  useEffect(() => {
    const ctx = ctxRef.current
    const inst = instancesRef.current.get(selRobot)
    if (!ctx || !inst) return
    ctx.controls.target.set(inst.group.position.x, 0.35, 0)
    ctx.controls.update()
  }, [selRobot])

  // ── 点击拾取部件 ──
  useEffect(() => {
    const canvas = canvasRef.current
    if (!canvas || !ready) return
    const onClick = (e: MouseEvent): void => {
      const ctx = ctxRef.current
      if (!ctx) return
      const rect = canvas.getBoundingClientRect()
      const mouse = new THREE.Vector2(
        ((e.clientX - rect.left) / rect.width) * 2 - 1,
        -((e.clientY - rect.top) / rect.height) * 2 + 1,
      )
      const raycaster = new THREE.Raycaster()
      raycaster.setFromCamera(mouse, ctx.camera)
      const all: THREE.Mesh[] = []
      for (const inst of instancesRef.current.values()) all.push(...inst.meshes)
      const hits = raycaster.intersectObjects(all, false)
      // 复位上次高亮
      if (highlightRef.current) {
        const m = highlightRef.current.material as THREE.MeshStandardMaterial
        m.emissive?.set(0x000000); m.emissiveIntensity = 0
      }
      if (hits.length) {
        const mesh = hits[0].object as THREE.Mesh
        let robotId = ''
        for (const [rid, inst] of instancesRef.current) {
          if (inst.meshes.includes(mesh)) { robotId = rid; break }
        }
        const inst = instancesRef.current.get(robotId)
        const link = inst?.meshToLink.get(mesh) || ''
        const mat = mesh.material as THREE.MeshStandardMaterial
        const jointName = inst?.linkToJoint.get(link)
        mat.emissive?.set(jointName ? 0x4ade80 : 0x4da6ff)   // 可动关节绿 / 固定件蓝
        mat.emissiveIntensity = 0.6
        highlightRef.current = mesh
        setSelPart({ robotId, robotName: robots.find((r) => r.id === robotId)?.name || '', link, jointName })
        setSelRobot(robotId)
        setAngleDeg(0)
      } else {
        highlightRef.current = null
        setSelPart(null)
      }
    }
    canvas.addEventListener('click', onClick)
    return () => canvas.removeEventListener('click', onClick)
  }, [ready, robots])

  // ── 关节滑杆 ──
  const jc = selPart?.jointName ? instancesRef.current.get(selPart.robotId)?.joints.get(selPart.jointName) : undefined

  const onSlide = useCallback((v: number | number[] | undefined): void => {
    if (!jc || v == null) return
    const deg = Number(Array.isArray(v) ? v[0] : v) || 0
    setAngleDeg(deg)
    setJointAngle(jc, (deg * Math.PI) / 180)
  }, [jc])

  function resetJoints(): void {
    if (!selRobot) return
    const inst = instancesRef.current.get(selRobot)
    if (!inst) return
    inst.joints.forEach((j) => setJointAngle(j, 0))
    setAngleDeg(0)
  }

  function paint(color: string): void {
    if (highlightRef.current) {
      ;(highlightRef.current.material as THREE.MeshStandardMaterial).color.set(color)
    }
  }

  const limits = jc ? { min: Math.ceil((jc.lower * 180) / Math.PI), max: Math.floor((jc.upper * 180) / Math.PI) } : null

  return (
    <div className="hall">
      {/* 左侧设备列表 */}
      <div className="hall-side">
        <Typography.Text type="tertiary" size="small" style={{ padding: '0 10px' }}>设备（{robots.length}）</Typography.Text>
        {robots.map((r) => (
          <div key={r.id} className={`hall-item${selRobot === r.id ? ' sel' : ''}`} onClick={() => setSelRobot(r.id)}>
            <span className="pulse-dot" style={r.online ? undefined : { background: 'var(--semi-color-text-2)', animation: 'none' }} />
            <span style={{ flex: 1, minWidth: 0, overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap', fontSize: 13 }}>
              {r.name}
            </span>
            <span style={{ fontSize: 10, color: 'var(--semi-color-text-2)' }}>{r.model?.toUpperCase()}</span>
          </div>
        ))}
      </div>

      {/* 3D 画布 */}
      <div className="hall-stage" ref={wrapRef}>
        <canvas ref={canvasRef} className="hall-canvas" />
        {!ready && (
          <div className="hall-loading">
            <Spin size="large" />
            <Typography.Text type="tertiary" size="small" style={{ marginTop: 10 }}>加载 X2 模型… {progress}%</Typography.Text>
          </div>
        )}
        {ready && robots.length === 0 && (
          <div className="hall-loading"><Empty title="暂无设备" description="接入机器人后在此展示" /></div>
        )}

        {/* 右下：部件/关节面板 */}
        {selPart && (
          <div className="hall-panel">
            <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 8 }}>
              <Boxes size={14} />
              <b style={{ fontSize: 13 }}>{partLabel(selPart.link)}</b>
              {selPart.jointName
                ? <Tag size="small" color="green">可动关节</Tag>
                : <Tag size="small" color="blue">固定件</Tag>}
              <span style={{ fontSize: 11, color: 'var(--semi-color-text-2)' }}>{selPart.robotName}</span>
            </div>
            {jc && limits && (
              <div style={{ marginBottom: 6 }}>
                <Typography.Text type="tertiary" size="small">关节角度：{angleDeg}°（限位 {limits.min}° ~ {limits.max}°）</Typography.Text>
                <Slider value={angleDeg} min={limits.min} max={limits.max} step={1} onChange={onSlide} />
              </div>
            )}
            <div style={{ display: 'flex', alignItems: 'center', gap: 6, flexWrap: 'wrap' }}>
              <Typography.Text type="tertiary" size="small">改色：</Typography.Text>
              {PALETTE.map((c) => (
                <span key={c} onClick={() => paint(c)}
                  style={{ width: 14, height: 14, borderRadius: '50%', background: c, cursor: 'pointer', border: '1px solid var(--semi-color-border)' }} />
              ))}
              <Button size="small" theme="borderless" icon={<RotateCcw size={12} />} onClick={resetJoints}>全部归零</Button>
            </div>
          </div>
        )}

        {/* 左下提示 */}
        <div className="hall-hint">
          <Crosshair size={11} style={{ verticalAlign: -1 }} />
          <span>拖拽旋转 · 滚轮缩放 · 点击部件查看（绿=可动关节）</span>
        </div>
      </div>
    </div>
  )
}
