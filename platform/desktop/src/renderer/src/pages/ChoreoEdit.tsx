/**编排编辑独立窗口页（#/choreo-edit?id=）— 剪映式横向时间轨道
   模型：每机一条横向轨道，任务块依次排列（只能接在前一个后面，不可重叠）；
   不设"开始时刻"——保存时按顺序自动累计（at = Σ 前面任务时长），错峰用「等待」任务表达。
   块宽 = 时长；agent 执行语义不变（串行轨道天然无顺延）。 */

import { useEffect, useRef, useState } from 'react'
import { useSearchParams } from 'react-router-dom'
import {
  Button, Input, Select, Tag, InputNumber, Space, Typography, Spin, Modal, Slider,
} from '@douyinfe/semi-ui'
import {
  Save, Plus, AudioLines, PersonStanding, Smile, Gauge, Timer,
  Settings2, Volume2, Film, Sparkles, ZoomIn, ZoomOut,
} from 'lucide-react'
import type { LucideIcon } from 'lucide-react'
import { toast } from '@/api/toast'
import { api, platformApi, type ChoreoTrack, type ChoreoStep } from '@/api/platform'
import { makeAgentClient } from '@/api/agent'
import { cachedLinkcraft, refreshLinkcraft, type LinkcraftItem } from '@/api/linkcraftCache'
import { useRobotsStore } from '@/stores/robots'

// ── 步骤类型元数据（本地 fallback；打开时从 agent 上报覆盖）──
type FieldDef = {
  name: string; label: string; kind: 'text' | 'number' | 'select' | 'switch'
  required?: boolean; default?: unknown; options?: { label: string; value: string | number }[]
}
type StepTypeMeta = { label: string; icon: string; color: string; fields: FieldDef[] }
const STEP_META: Record<string, StepTypeMeta> = {
  tts: { label: '语音', icon: '🗣️', color: '#4CAF50', fields: [
    { name: 'text', label: '播报文字', kind: 'text', required: true },
    { name: 'wait_done', label: '等播完', kind: 'switch', default: true },
    { name: 'gesture_area', label: '配动手势（边说边做）', kind: 'select', default: '', options: [
      { label: '无', value: '' },
      ...Array.from({ length: 28 }, (_, i) => ({ label: `随机讲话${21 + i}`, value: String(21 + i) })),
    ] },
  ] },
  motion: { label: '预设动作', icon: '🕺', color: '#FF9800', fields: [
    { name: 'motion_id', label: '动作名称', kind: 'number', required: true },
    { name: 'area', label: '部位 1左臂/2右臂/3双臂/11全身', kind: 'number', default: 2 },
    { name: 'wait_done', label: '估时等待完成', kind: 'switch', default: true },
  ] },
  emoji: { label: '表情', icon: '😊', color: '#E91E63', fields: [
    { name: 'emotion_id', label: '表情 ID', kind: 'number', required: true },
    { name: 'mode', label: '模式 1一次/2循环', kind: 'number', default: 1 },
  ] },
  velocity: { label: '速度', icon: '🏃', color: '#2196F3', fields: [
    { name: 'forward', label: '前后 m/s', kind: 'number', default: 0.3 },
    { name: 'lateral', label: '左右 m/s', kind: 'number', default: 0 },
    { name: 'angular', label: '旋转 rad/s', kind: 'number', default: 0 },
    { name: 'duration', label: '持续秒', kind: 'number', default: 2 },
  ] },
  wait: { label: '等待', icon: '⏱️', color: '#9E9E9E', fields: [
    { name: 'duration', label: '等待秒', kind: 'number', default: 1 },
  ] },
  mode: { label: '运动模式', icon: '⚙️', color: '#795548', fields: [
    { name: 'action_desc', label: '模式', kind: 'select', required: true, default: 'STAND_DEFAULT', options: [
      { label: '稳定站立', value: 'STAND_DEFAULT' }, { label: '走跑', value: 'LOCOMOTION_DEFAULT' },
      { label: '阻尼', value: 'DAMPING_DEFAULT' }, { label: '位控站立', value: 'JOINT_DEFAULT' },
      { label: '零力矩/急停', value: 'PASSIVE_DEFAULT' },
    ] },
  ] },
  volume: { label: '音量', icon: '🔊', color: '#607D8B', fields: [
    { name: 'volume', label: '音量 0-100', kind: 'number', default: 50 },
  ] },
  media: { label: '媒体', icon: '🎬', color: '#673AB7', fields: [
    { name: 'file_name', label: '文件名（PC3 上）', kind: 'text', required: true },
  ] },
  linkcraft: { label: '灵创动作', icon: '🤖', color: '#00ACC1', fields: [
    { name: 'resource_key', label: '灵创动作名称', kind: 'text', required: true },
    { name: 'resource_type', label: '类型', kind: 'select', default: 'BODY_MONTION', options: [
      { label: '全身', value: 'BODY_MONTION' }, { label: '手臂', value: 'ARM_MONTION' },
    ] },
  ] },
}
const STEP_ORDER = ['tts', 'motion', 'emoji', 'velocity', 'wait', 'mode', 'volume', 'media', 'linkcraft']
// 选择器隐藏的类型（已有数据仍可显示，只是不能再新增）
const HIDDEN_TYPES = new Set(['mode', 'volume'])

/** 各类型步骤的时长默认估时（秒）——块宽数据源；弹窗可改 */
function defaultDuration(type: string, form: Record<string, unknown>): number {
  switch (type) {
    case 'tts': return Math.max(1, Math.ceil(String(form.text || '').length * 0.25))
    case 'motion': {
      const d = Number(form.motion_dur)
      if (d > 0) return d   // 清单实测时长（capabilities 上报）
      const area = Number(form.area)
      if (area >= 21 && area <= 48) return 4   // 讲话手势（人工估值，SDK 无完成回调）
      return area === 11 ? 3 : 2   // 兜底：全身 3s / 手臂 2s
    }
    case 'wait': case 'velocity': return Number(form.duration) || 2
    case 'linkcraft': case 'media': return 5
    default: return 0.5   // 表情等瞬时类
  }
}
const stepDur = (s: ChoreoStep): number =>
  Number(s.duration) || defaultDuration(s.type, s as unknown as Record<string, unknown>)

// 步骤类型图标：lucide 优先（agent 上报的 emoji 仅作未知类型兜底）
const TYPE_ICON: Record<string, LucideIcon> = {
  tts: AudioLines, motion: PersonStanding, emoji: Smile, velocity: Gauge,
  wait: Timer, mode: Settings2, volume: Volume2, media: Film, linkcraft: Sparkles,
}
function TypeIcon({ t, color, size = 18 }: { t: string; color: string; size?: number }): JSX.Element {
  const I = TYPE_ICON[t]
  return I
    ? <I size={size} color={color} strokeWidth={2} />
    : <span style={{ fontSize: Math.max(size - 6, 10) }}>{STEP_META[t]?.icon ?? '🔸'}</span>
}

// ── 步骤编辑弹窗（只配参数 + 时长；开始时刻自动 = 前序累计）──
interface StepEditState { trackIdx: number; stepIdx: number | null; type: string; form: Record<string, unknown>; startAt: number }
interface MotionOption { id: string; name: string; area: number; duration?: number }
function StepModal({ state, types, motions, linkcrafts, onClose, onSave }: {
  state: StepEditState; types: Record<string, StepTypeMeta>; motions: MotionOption[]; linkcrafts: LinkcraftItem[]
  onClose: () => void; onSave: (s: StepEditState) => void
}): JSX.Element {
  const meta = types[state.type] || { label: state.type, icon: '🔸', color: '#666', fields: [] as FieldDef[] }
  const [form, setForm] = useState<Record<string, unknown>>(state.form)
  const [dur, setDur] = useState(stepDur({ ...state.form, type: state.type } as unknown as ChoreoStep))

  const setF = (name: string, v: unknown): void => setForm((f) => ({ ...f, [name]: v }))
  return (
    <Modal title={meta.label} visible onCancel={onClose}
      footer={<>
        <Button theme="borderless" onClick={onClose}>取消</Button>
        <Button theme="solid" onClick={() => onSave({ ...state, form: { ...form, duration: dur } })}>保存</Button>
      </>}
      style={{ width: 440 }}>
      <Space vertical align="start" style={{ width: '100%' }}>
        {meta.fields.map((f) => {
          const val = form[f.name] ?? f.default ?? (f.kind === 'switch' ? false : '')
          if (f.kind === 'switch') return null   // 等播完等开关不暴露（agent 侧默认行为）
          // 预设动作：部位随动作下拉自动带出，不再单独暴露
          if (state.type === 'motion' && f.name === 'area') return null
          // 速度/等待：自带的秒数字段与统一时长重复——只填统一时长（保存时自动写入 form.duration）
          if ((state.type === 'velocity' || state.type === 'wait') && f.name === 'duration') return null
          // 灵创：类型由 key 自动推断（onnx→全身），不单独暴露
          if (state.type === 'linkcraft' && f.name === 'resource_type') return null
          if (f.kind === 'select') {
            const opts = (f.options || []).map((o) => ({ label: o.label, value: String(o.value) }))
            return (
              <div key={f.name} style={{ width: '100%' }}>
                <Typography.Text size="small" style={{ display: 'block', marginBottom: 4 }}>{f.label}</Typography.Text>
                <Select<string> value={String(val ?? '')} optionList={opts}
                  onChange={(v) => setF(f.name, v)} style={{ width: '100%' }} />
              </div>
            )
          }
          return (
            <div key={f.name} style={{ width: '100%' }}>
              <Typography.Text size="small" style={{ display: 'block', marginBottom: 4 }}>
                {state.type === 'linkcraft' && f.name === 'resource_key' ? '灵创动作名称' : state.type === 'motion' && f.name === 'motion_id' ? '动作名称' : f.label}{f.required ? ' *' : ''}
              </Typography.Text>
              {/* 预设动作：有清单时渲染下拉（复合值 拆 motion_id/area），离线兜底数字框 */}
              {state.type === 'linkcraft' && f.name === 'resource_key' && linkcrafts.length > 0 ? (
                <Select<string> filter style={{ width: '100%' }}
                  value={String(form.resource_key ?? '')}
                  optionList={linkcrafts.map((r) => ({ label: r.name, value: r.resource_key }))}
                  onChange={(v) => {
                    const key = String(v ?? '')
                    setF('resource_key', key)
                    setF('resource_type', key.toLowerCase().includes('onnx') ? 'BODY' : 'ARM')
                  }} />
              ) : state.type === 'motion' && f.name === 'motion_id' && motions.length > 0 ? (
                <Select<string> filter style={{ width: '100%' }}
                  value={`${Number(form.motion_id) || 0}:${Number(form.area) || 2}`}
                  optionList={motions.map((m) => ({ label: m.name, value: m.id }))}
                  onChange={(v) => {
                    const [mid, area] = String(v).split(':').map(Number)
                    setF('motion_id', mid)
                    setF('area', area)
                    const hit = motions.find((m) => m.id === String(v))
                    if (hit?.duration) setF('motion_dur', hit.duration)
                  }} />
              ) : f.kind === 'number' ? (
                <InputNumber value={val as number} onChange={(v) => setF(f.name, v)} style={{ width: '100%' }} />
              ) : (
                <Input value={val as string} placeholder={f.required ? '必填' : ''}
                  onChange={(v) => setF(f.name, v)} style={{ width: '100%' }} />
              )}
            </div>
          )
        })}
        <div style={{ width: '100%' }}>
          <Typography.Text size="small" style={{ display: 'block', marginBottom: 4 }}>时长（秒）</Typography.Text>
          <InputNumber value={dur} min={0.1} step={0.5} onChange={(v) => setDur(Number(v) || 1)} style={{ width: '100%' }} />
        </div>
      </Space>
    </Modal>
  )
}

// ── 任务类型选择 ──
function TypePicker({ types, onPick, onClose }: {
  types: Record<string, StepTypeMeta>; onPick: (t: string) => void; onClose: () => void
}): JSX.Element {
  const order = [
    ...STEP_ORDER.filter((t) => types[t] && !HIDDEN_TYPES.has(t)),
    ...Object.keys(types).filter((t) => !STEP_ORDER.includes(t) && !HIDDEN_TYPES.has(t)),
  ]
  return (
    <Modal title="选择任务类型" visible onCancel={onClose} footer={null} style={{ width: 440 }}>
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 12, paddingBottom: 28 }}>
        {order.map((t) => {
          const m = types[t]
          return (
            <div key={t} className="choreo-type-pick" onClick={() => onPick(t)}>
              <TypeIcon t={t} color={m.color} size={19} />
              <div>{m.label}</div>
            </div>
          )
        })}
      </div>
    </Modal>
  )
}

// ── 编辑页 ──
export default function ChoreoEditPage(): JSX.Element {
  const [params] = useSearchParams()
  const id = params.get('id') || ''
  const robots = useRobotsStore((s) => s.summaries)

  const [loading, setLoading] = useState(true)
  const [name, setName] = useState('')
  const [desc, setDesc] = useState('')
  const [tracks, setTracks] = useState<ChoreoTrack[]>([])
  const [saving, setSaving] = useState(false)
  const [stepEdit, setStepEdit] = useState<StepEditState | null>(null)
  const [typePick, setTypePick] = useState<number | null>(null)   // trackIdx
  const [types, setTypes] = useState<Record<string, StepTypeMeta>>(STEP_META)
  const [motions, setMotions] = useState<MotionOption[]>([])
  const [linkcrafts, setLinkcrafts] = useState<LinkcraftItem[]>([])
  const [pxSec, setPxSec] = useState(36)   // 比例尺（px/秒）
  // 拖拽：块重排（拖到轨道内落点）/ 删除（拖出轨道区域）
  const dragRef = useRef<{ ti: number; si: number } | null>(null)
  const [dragging, setDragging] = useState(false)
  const laneRefs = useRef<(HTMLDivElement | null)[]>([])

  // 拉取编排内容（旧数据按 at 排序转串行视图）
  useEffect(() => {
    api.getChoreo(id)
      .then((c) => {
        setName(c.name)
        setDesc(c.desc || '')
        setTracks((c.tracks || []).map((t) => ({
          ...t,
          steps: [...(t.steps || [])].sort((a, b) => (a.at ?? 0) - (b.at ?? 0)),
        })))
      })
      .catch(() => toast.error('编排加载失败'))
      .finally(() => setLoading(false))
  }, [id])

  // 步骤类型清单：agent 上报覆盖本地兜底
  useEffect(() => {
    api.getChoreoTypes().then((list) => {
      if (!list?.length) return
      const fromAgent: Record<string, StepTypeMeta> = {}
      for (const t of list) {
        fromAgent[t.type] = { label: t.label, icon: t.icon, color: t.color, fields: t.fields }
      }
      setTypes((prev) => ({ ...prev, ...fromAgent }))
    }).catch(() => { /* agent 离线等场景用本地 fallback */ })
  }, [])

  // 预设动作清单（第一台选中机）—— 离线时数字框兜底
  const firstRobotId = tracks[0]?.robot_id ?? ''
  useEffect(() => {
    if (!firstRobotId) { setMotions([]); return }
    let alive = true
    void platformApi().get(`/api/robots/${firstRobotId}`).then(({ data: rb }) => {
      if (!alive || !rb.last_ip) return null
      return makeAgentClient(rb.last_ip, rb.token).get('/api/capabilities', { timeout: 6000 })
    }).then((r) => {
      if (!alive || !r) return
      const acts = r.data?.capabilities?.find((c: { type: string }) => c.type === 'motion.preset')?.params?.actions
      if (Array.isArray(acts)) setMotions(acts)
    }).catch(() => { /* 离线：数字框兜底 */ })
    return () => { alive = false }
  }, [firstRobotId])

  // 灵创清单：缓存秒开 + 后台刷新（stale-while-revalidate）
  useEffect(() => {
    if (!firstRobotId) { setLinkcrafts([]); return }
    setLinkcrafts(cachedLinkcraft(firstRobotId))
    void refreshLinkcraft(firstRobotId).then((fresh) => { if (fresh) setLinkcrafts(fresh) })
  }, [firstRobotId])

  const selectedIds = tracks.map((t) => t.robot_id)

  function toggleRobot(rid: string): void {
    if (selectedIds.includes(rid)) {
      setTracks((ts) => ts.filter((t) => t.robot_id !== rid))
    } else {
      const r = robots.find((x) => x.id === rid)
      setTracks((ts) => [...ts, { robot_id: rid, robot_name: r?.name || rid, steps: [] }])
    }
  }

  /**轨道内第 upto 项的开始时刻（串行累计） */
  function startOf(trackIdx: number, upto: number): number {
    const steps = tracks[trackIdx]?.steps || []
    let t = 0
    for (let i = 0; i < upto && i < steps.length; i++) t += stepDur(steps[i])
    return +t.toFixed(2)
  }
  const trackEnd = (t: ChoreoTrack): number =>
    +t.steps.reduce((acc, s) => acc + stepDur(s), 0).toFixed(2)

  function saveStep(s: StepEditState): void {
    const { type, form } = s
    setTracks((ts) => ts.map((t, i) => {
      if (i !== s.trackIdx) return t
      const steps = [...t.steps]
      const step = { ...form, type } as unknown as ChoreoStep   // at 由保存时统一计算
      if (s.stepIdx === null) steps.push(step)
      else steps[s.stepIdx] = step
      return { ...t, steps }
    }))
    setStepEdit(null)
  }

  async function doSave(): Promise<void> {
    if (!name.trim()) { toast.warning('请填写编排名称'); return }
    // 串行轨道：at = Σ 前面任务时长（多机错峰用「等待」任务表达）
    const outTracks = tracks.map((t) => {
      let cursor = 0
      const steps = t.steps.map((s) => {
        const step = { ...s, at: +cursor.toFixed(2) }
        cursor += stepDur(s)
        return step
      })
      return { ...t, steps }
    })
    setSaving(true)
    try {
      await api.saveChoreo({ id, name: name.trim(), desc, tracks: outTracks })
      toast.success('已保存')
      window.close()   // 主窗口 focus 时自动刷新列表
    } catch {
      toast.error('保存失败')
    }
    setSaving(false)
  }

  if (loading) return <div style={{ padding: 120, textAlign: 'center' }}><Spin size="large" /></div>

  const total = Math.max(10, ...tracks.map(trackEnd)) + 2
  const totalPx = Math.round(total * pxSec)
  const ticks = Array.from({ length: Math.ceil(total) + 1 }, (_, i) => i)

  return (
    <div>
      {/* 自绘标题条 + 保存按钮（no-drag 豁免） */}
      <div className="titlebar" style={{ paddingLeft: 84, paddingRight: 16 }}>
        <span className="title">编辑编排{name ? ` — ${name}` : ''}</span>
        <div className="spacer" />
        <Button className="no-drag" size="small" theme="solid" icon={<Save size={13} />} loading={saving}
          onClick={() => void doSave()}>保存</Button>
      </div>

      <div style={{ padding: '20px 28px 32px', maxWidth: 1100, margin: '0 auto' }}>
        <Space>
          <Input placeholder="编排名称" value={name} onChange={setName} style={{ width: 260 }} />
          <Input placeholder="描述（可选）" value={desc} onChange={setDesc} style={{ width: 420 }} />
        </Space>

        <div style={{ marginTop: 16 }}>
          <Typography.Text size="small">参与机器人（点击切换轨道，每台一条时间轨道）</Typography.Text>
          <div style={{ marginTop: 6, display: 'flex', flexWrap: 'wrap', gap: 8 }}>
            {robots.map((r) => (
              <Tag key={r.id} size="large" color={selectedIds.includes(r.id) ? 'green' : 'grey'}
                style={{ cursor: 'pointer' }} onClick={() => toggleRobot(r.id)}>{r.name}</Tag>
            ))}
            {!robots.length && <Typography.Text type="tertiary">暂无机器人，请先在设备页配对</Typography.Text>}
          </div>
        </div>

        <div style={{ display: 'flex', alignItems: 'center', gap: 8, margin: '16px 0 8px' }}>
          <Typography.Text type="tertiary" size="small">
            任务从左到右依次执行；块宽＝时长；拖动排序 · 拖出轨道删除；多机错峰用「等待」任务 · 总时长 {total.toFixed(1)}s
          </Typography.Text>
          <div style={{ flex: 1 }} />
          <ZoomOut size={13} color="var(--semi-color-text-2)" />
          <Slider value={pxSec} min={16} max={80} step={8} style={{ width: 140 }}
            tooltipVisible={false} onChange={(v) => setPxSec(Number(Array.isArray(v) ? v[0] : v) || 36)} />
          <ZoomIn size={13} color="var(--semi-color-text-2)" />
        </div>

        {/* ── 剪映式横向轨道：左固定名称列（不随滚动）+ 右横向滚动时间轴 ── */}
        <div className="tl-outer">
          {/* 左：名称列 */}
          <div className="tl-leftcol">
            <div className="tl-corner">秒</div>
            {tracks.map((t, ti) => (
              <div key={t.robot_id} className="tl-head">
                <div style={{ fontWeight: 700, fontSize: 13, flex: 1, minWidth: 0,
                  overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{t.robot_name}</div>
                <Button size="small" theme="borderless" icon={<Plus size={13} />} title="追加任务"
                  onClick={() => setTypePick(ti)} />
              </div>
            ))}
          </div>
          {/* 右：滚动时间轴（滚动条只在此区域） */}
          <div className="tl-scroll">
            <div style={{ width: totalPx }}>
              <div className="tl-ruler-row">
                <div className="tl-ruler" style={{ width: totalPx, height: 22 }}>
                  {ticks.map((t) => (
                    <div key={t} className={`tl-tickline${t % 10 === 0 ? ' major' : ''}`} style={{ left: t * pxSec }}>
                      {t % 2 === 0 && <span className="tl-ticklabel">{t}</span>}
                    </div>
                  ))}
                </div>
              </div>
              {tracks.map((t, ti) => (
                <div key={t.robot_id} className="tl-row">
                  <div key={t.robot_id} className="tl-lane" style={{ width: totalPx }}
                    ref={(el) => { laneRefs.current[ti] = el }}
                    onDragOver={(e) => e.preventDefault()}
                    onDrop={(e) => {
                      e.preventDefault()
                      const d = dragRef.current
                      dragRef.current = null
                      if (!d) return
                      const el = laneRefs.current[ti]
                      if (!el) return
                      // 落点 x → 插入索引（比较各块中心）
                      const rect = el.getBoundingClientRect()
                      const x = e.clientX - rect.left
                      let idx = t.steps.length
                      for (let j = 0; j < t.steps.length; j++) {
                        const start = startOf(ti, j)
                        const dur = stepDur(t.steps[j])
                        if (x < (start + dur / 2) * pxSec) { idx = j; break }
                      }
                      setTracks((ts) => {
                        const src = ts[d.ti].steps[d.si]
                        const out = ts.map((tr, i) => {
                          if (i === d.ti) return { ...tr, steps: tr.steps.filter((_, j) => j !== d.si) }
                          return tr
                        })
                        // 目标轨道插入（注意源删除后索引位移）
                        const steps = [...out[ti].steps]
                        let ins = idx
                        if (d.ti === ti && d.si < idx) ins = idx - 1
                        steps.splice(ins, 0, src)
                        out[ti] = { ...out[ti], steps }
                        return out
                      })
                    }}>
                    {ticks.map((tk) => (
                      <div key={tk} className={`tl-grid${tk % 10 === 0 ? ' major' : ''}`} style={{ left: tk * pxSec }} />
                    ))}
                    {!t.steps.length && <span className="tl-empty">空轨道</span>}
                    {t.steps.map((s, si) => {
                      const m = types[s.type] || { label: s.type, icon: '🔸', color: '#666' }
                      const d = stepDur(s)
                      const w = Math.max(26, d * pxSec - 3)
                      return (
                        <div key={si} className={`tl-block${dragging ? ' grasp' : ''}`} style={{ left: startOf(ti, si) * pxSec + 2, width: w }}
                          draggable
                          onDragStart={(e) => {
                            dragRef.current = { ti, si }
                            setDragging(true)
                            e.dataTransfer.effectAllowed = 'move'
                            e.dataTransfer.setData('text/plain', '')   // Firefox 需要
                          }}
                          onDragEnd={(e) => {
                            setDragging(false)
                            // 未被轨道接住（drop 没发生）且落点在轨道区域外 → 删除；(0,0) 视为 ESC 取消
                            const d = dragRef.current
                            dragRef.current = null
                            if (!d || (e.clientX === 0 && e.clientY === 0)) return
                            const inLane = laneRefs.current.some((el) => {
                              if (!el) return false
                              const r = el.getBoundingClientRect()
                              return e.clientX >= r.left && e.clientX <= r.right && e.clientY >= r.top && e.clientY <= r.bottom
                            })
                            if (!inLane) {
                              setTracks((ts) => ts.map((x, i) => (i !== d.ti ? x : { ...x, steps: x.steps.filter((_, j) => j !== d.si) })))
                              toast.info('已删除任务')
                            }
                          }}
                          onClick={() => setStepEdit({ trackIdx: ti, stepIdx: si, type: s.type, form: { ...s }, startAt: startOf(ti, si) })}>
                          <div className="tl-block-main">
                            {w > 56 && <span className="tl-block-name">{m.label}</span>}
                            {w > 110 && <span className="tl-block-dur">{d % 1 === 0 ? d : d.toFixed(1)}s</span>}
                          </div>
                        </div>
                      )
                    })}
                  </div>
                </div>
              ))}
            </div>
          </div>
        </div>
      </div>

      {stepEdit && (
        <StepModal state={stepEdit} types={types} motions={motions} linkcrafts={linkcrafts}
          onClose={() => setStepEdit(null)}
          onSave={(s) => { if (!s.form.text && s.type === 'tts') { toast.warning('语音内容必填'); return } saveStep(s) }} />
      )}
      {typePick != null && (
        <TypePicker types={types}
          onPick={(t) => {
            setStepEdit({ trackIdx: typePick, stepIdx: null, type: t, form: {}, startAt: trackEnd(tracks[typePick]) })
            setTypePick(null)
          }}
          onClose={() => setTypePick(null)} />
      )}
    </div>
  )
}
