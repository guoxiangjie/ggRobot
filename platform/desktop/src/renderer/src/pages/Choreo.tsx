/**多机编排 — 列表 / 执行监控 / 时间线多轨编辑器（docs/choreo-design.md §6）

模型：编排 = tracks[]，每台机器人一条轨道，steps 按 at（相对执行开始秒）排序。
执行：平台分发各机轨道 → 广播 start_ts → agent 本地按 at 推进（时间戳锚定）。
监控：run 后轮询 /api/choreo/run/{id}/status（1s）到终态，展示每机结果。
*/

import { useEffect, useState, useCallback, useRef } from 'react'
import {
  Button, Modal, Input, Select, Tag, Switch, InputNumber, Empty, Space, Divider, Typography,
} from '@douyinfe/semi-ui'
import {
  Clapperboard, Plus, Play, Pencil, Trash2, RefreshCw, StopCircle, X, Clock,
} from 'lucide-react'
import { toast } from '@/api/toast'
import { api, hubWs, type Choreo, type ChoreoTrack, type ChoreoStep, type ChoreoRun } from '@/api/platform'
import { useRobotsStore } from '@/stores/robots'

// ── 步骤类型元数据（本地 fallback；打开编辑器时从 agent 上报覆盖，见 ChoreoEditor）──
type FieldDef = {
  name: string; label: string; kind: 'text' | 'number' | 'select' | 'switch'
  required?: boolean; default?: unknown; options?: { label: string; value: string | number }[]
}
type StepTypeMeta = { label: string; icon: string; color: string; fields: FieldDef[] }
const STEP_META: Record<string, StepTypeMeta> = {
  tts: { label: '语音', icon: '🗣️', color: '#4CAF50', fields: [
    { name: 'text', label: '播报文字', kind: 'text', required: true },
    { name: 'wait_done', label: '等播完', kind: 'switch', default: true },
  ] },
  motion: { label: '预设动作', icon: '🕺', color: '#FF9800', fields: [
    { name: 'motion_id', label: '动作 ID', kind: 'number', required: true },
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
    { name: 'resource_key', label: '动作包 key', kind: 'text', required: true },
    { name: 'resource_type', label: '类型', kind: 'select', default: 'BODY_MONTION', options: [
      { label: '全身', value: 'BODY_MONTION' }, { label: '手臂', value: 'ARM_MONTION' },
    ] },
  ] },
}
const STEP_ORDER = ['tts', 'motion', 'emoji', 'velocity', 'wait', 'mode', 'volume', 'media', 'linkcraft']

function stepSummary(s: ChoreoStep): string {
  switch (s.type) {
    case 'tts': return String(s.text || '').slice(0, 18)
    case 'motion': return `动作#${s.motion_id}:${s.area}`
    case 'emoji': return `表情#${s.emotion_id}`
    case 'velocity': return `${s.forward}/${s.lateral}/${s.angular} × ${s.duration}s`
    case 'wait': return `${s.duration}s`
    case 'mode': return String(s.action_desc || '')
    case 'volume': return `音量 ${s.volume}`
    case 'media': return String(s.file_name || '')
    case 'linkcraft': return String(s.resource_key || '')
    default: return ''
  }
}

// ── 步骤编辑弹窗 ──
interface StepEditState { trackIdx: number; stepIdx: number | null; type: string; form: Record<string, unknown>; at: number }
function StepModal({ state, types, onClose, onSave }: {
  state: StepEditState; types: Record<string, StepTypeMeta>; onClose: () => void; onSave: (s: StepEditState) => void
}): JSX.Element {
  const meta = types[state.type] || { label: state.type, icon: '🔸', color: '#666', fields: [] as FieldDef[] }
  const [form, setForm] = useState<Record<string, unknown>>(state.form)
  const [at, setAt] = useState(state.at)

  const setF = (name: string, v: unknown): void => setForm((f) => ({ ...f, [name]: v }))
  return (
    <Modal title={`${meta.label}步骤 @ ${at.toFixed(1)}s`} visible onCancel={onClose}
      footer={<>
        <Button theme="borderless" onClick={onClose}>取消</Button>
        <Button theme="solid" onClick={() => onSave({ ...state, form, at })}>保存</Button>
      </>}
      style={{ width: 440 }}>
      <Space vertical align="start" style={{ width: '100%' }}>
        {meta.fields.map((f) => {
          const val = form[f.name] ?? f.default ?? (f.kind === 'switch' ? false : '')
          if (f.kind === 'switch') {
            return (
              <Space key={f.name}>
                <Switch checked={Boolean(val)} onChange={(v) => setF(f.name, v)} />
                <Typography.Text>{f.label}</Typography.Text>
              </Space>
            )
          }
          if (f.kind === 'select') {
            const opts = (f.options || []).map((o) => ({ label: o.label, value: String(o.value) }))
            return (
              <div key={f.name} style={{ width: '100%' }}>
                <Typography.Text size="small" style={{ display: 'block', marginBottom: 4 }}>{f.label}</Typography.Text>
                {/* 显式泛型切断 Semi Select 深度实例化（TS2589） */}
                <Select<string>
                  value={String(val ?? '')}
                  optionList={opts}
                  onChange={(v) => setF(f.name, v)}
                  style={{ width: '100%' }}
                />
              </div>
            )
          }
          return (
            <div key={f.name} style={{ width: '100%' }}>
              <Typography.Text size="small" style={{ display: 'block', marginBottom: 4 }}>
                {f.label}{f.required ? ' *' : ''}
              </Typography.Text>
              {f.kind === 'number' ? (
                <InputNumber value={val as number} onChange={(v) => setF(f.name, v)} style={{ width: '100%' }} />
              ) : (
                <Input value={val as string} placeholder={f.required ? '必填' : ''}
                  onChange={(v) => setF(f.name, v)} style={{ width: '100%' }} />
              )}
            </div>
          )
        })}
        <div style={{ width: '100%' }}>
          <Typography.Text size="small" style={{ display: 'block', marginBottom: 4 }}>
            开始时刻 at（秒，相对执行开始；同轨顺序执行，此值为最早开始时刻）
          </Typography.Text>
          <InputNumber value={at} min={0} step={0.1} onChange={(v) => setAt(Number(v) || 0)} style={{ width: '100%' }} />
        </div>
      </Space>
    </Modal>
  )
}

// ── 编辑器弹窗 ──
function ChoreoEditor({ initial, onClose, onSaved }: {
  initial: Choreo | null; onClose: () => void; onSaved: () => void
}): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)
  const [name, setName] = useState(initial?.name || '')
  const [desc, setDesc] = useState(initial?.desc || '')
  const [tracks, setTracks] = useState<ChoreoTrack[]>(initial?.tracks || [])
  const [saving, setSaving] = useState(false)
  const [stepEdit, setStepEdit] = useState<StepEditState | null>(null)
  const [typePick, setTypePick] = useState<{ trackIdx: number; baseAt: number } | null>(null)
  // 步骤类型清单：本地 STEP_META 兜底，打开时从 agent 上报覆盖（多型号可裁剪）
  const [types, setTypes] = useState<Record<string, StepTypeMeta>>(STEP_META)

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

  const robotOptions = robots.filter((r) => r.status === 'active')
    .map((r) => ({ label: `${r.name}（${r.sn.slice(-4)}）`, value: r.id }))

  // 已选机器人（保持 tracks 顺序）
  const selectedIds = tracks.map((t) => t.robot_id)

  function toggleRobot(id: string): void {
    if (selectedIds.includes(id)) {
      setTracks((ts) => ts.filter((t) => t.robot_id !== id))
    } else {
      const r = robots.find((x) => x.id === id)
      setTracks((ts) => [...ts, { robot_id: id, robot_name: r?.name || id, steps: [] }])
    }
  }

  function sortSteps(steps: ChoreoStep[]): ChoreoStep[] {
    return [...steps].sort((a, b) => (a.at ?? 0) - (b.at ?? 0))
  }
  function patchSteps(trackIdx: number, steps: ChoreoStep[]): void {
    setTracks((ts) => ts.map((t, i) => (i === trackIdx ? { ...t, steps: sortSteps(steps) } : t)))
  }

  function saveStep(s: StepEditState): void {
    const step: ChoreoStep = { type: s.type, at: Number(s.at) || 0, ...s.form }
    setTracks((ts) => {
      const t = ts[s.trackIdx]
      if (!t) return ts
      const steps = [...t.steps]
      if (s.stepIdx === null) steps.push(step)
      else steps[s.stepIdx] = step
      return ts.map((x, i) => (i === s.trackIdx ? { ...x, steps: sortSteps(steps) } : x))
    })
    setStepEdit(null)
  }

  async function doSave(): Promise<void> {
    if (!name.trim()) { toast.warning('请填写编排名称'); return }
    if (!tracks.length) { toast.warning('至少选择一台机器人'); return }
    if (tracks.some((t) => !t.steps.length)) { toast.warning('存在空轨道（请添加步骤或移除该机器人）'); return }
    setSaving(true)
    try {
      await api.saveChoreo({ id: initial?.id, name: name.trim(), desc, tracks })
      toast.success('已保存')
      onSaved()
      onClose()
    } catch {
      toast.error('保存失败')
    }
    setSaving(false)
  }

  return (
    <Modal title={initial ? '编辑编排' : '新建编排'} visible onCancel={onClose}
      footer={<>
        <Button theme="borderless" onClick={onClose}>取消</Button>
        <Button theme="solid" loading={saving} onClick={doSave}>保存</Button>
      </>}
      style={{ width: 1000 }}>
      <Space vertical align="start" style={{ width: '100%' }}>
        <Space>
          <Input placeholder="编排名称" value={name} onChange={setName} style={{ width: 260 }} />
          <Input placeholder="描述（可选）" value={desc} onChange={setDesc} style={{ width: 420 }} />
        </Space>
        <div style={{ width: '100%' }}>
          <Typography.Text size="small">参与机器人（点击切换轨道，每台一条时间线）</Typography.Text>
          <div style={{ marginTop: 6, display: 'flex', flexWrap: 'wrap', gap: 8 }}>
            {robotOptions.map((o) => (
              <Tag key={o.value} size="large" color={selectedIds.includes(o.value) ? 'green' : 'grey'}
                style={{ cursor: 'pointer' }} onClick={() => toggleRobot(o.value)}>{o.label}</Tag>
            ))}
            {!robotOptions.length && <Typography.Text type="tertiary">暂无已激活机器人，请先在设备页配对</Typography.Text>}
          </div>
        </div>

        <Divider style={{ margin: '4px 0' }} />

        {/* 轨道区 */}
        {tracks.map((t, ti) => (
          <div key={t.robot_id} className="choreo-track">
            <div className="choreo-track-head">
              <span className="choreo-track-name">{t.robot_name}</span>
              <span className="choreo-track-count">{t.steps.length} 步</span>
              <Button size="small" icon={<Plus size={14} />}
                onClick={() => setTypePick({ trackIdx: ti, baseAt: t.steps.length ? Math.max(...t.steps.map((s) => Number(s.at) || 0)) + 1 : 0 })}>
                添加步骤
              </Button>
            </div>
            <div className="choreo-steps">
              {!t.steps.length && <Typography.Text type="tertiary" size="small">空轨道</Typography.Text>}
              {t.steps.map((s, si) => {
                const m = types[s.type] || { label: s.type, icon: '🔸', color: '#666' }
                return (
                  <div key={si} className="choreo-step" style={{ borderColor: m.color }}
                    onClick={() => setStepEdit({ trackIdx: ti, stepIdx: si, type: s.type, form: { ...s }, at: Number(s.at) || 0 })}>
                    <span className="choreo-step-at"><Clock size={10} />{(Number(s.at) || 0).toFixed(1)}s</span>
                    <span>{m.icon} {m.label}</span>
                    <span className="choreo-step-sum">{stepSummary(s)}</span>
                    <span className="choreo-step-del" onClick={(e) => { e.stopPropagation(); patchSteps(ti, t.steps.filter((_, i) => i !== si)) }}>
                      <X size={12} />
                    </span>
                  </div>
                )
              })}
            </div>
          </div>
        ))}
      </Space>

      {stepEdit && (
        <StepModal state={stepEdit} types={types}
          onClose={() => setStepEdit(null)}
          onSave={(s) => { if (!s.form.text && s.type === 'tts') { toast.warning('语音内容必填'); return } saveStep(s) }} />
      )}
      {typePick && (
        <TypePicker types={types}
          onPick={(t) => { setStepEdit({ trackIdx: typePick.trackIdx, stepIdx: null, type: t, form: {}, at: typePick.baseAt }); setTypePick(null) }}
          onClose={() => setTypePick(null)} />
      )}
    </Modal>
  )
}

// ── 编排类型选择（新步骤）──
function TypePicker({ types, onPick, onClose }: {
  types: Record<string, StepTypeMeta>; onPick: (t: string) => void; onClose: () => void
}): JSX.Element {
  // 顺序：STEP_ORDER 内优先（保持稳定排序），agent 新增类型追加尾部
  const order = [...STEP_ORDER.filter((t) => types[t]), ...Object.keys(types).filter((t) => !STEP_ORDER.includes(t))]
  return (
    <Modal title="选择步骤类型" visible onCancel={onClose} footer={null} style={{ width: 480 }}>
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: 8 }}>
        {order.map((t) => {
          const m = types[t]
          return (
            <div key={t} className="choreo-type-pick" onClick={() => onPick(t)}>
              <div style={{ fontSize: 20 }}>{m.icon}</div>
              <div>{m.label}</div>
            </div>
          )
        })}
      </div>
    </Modal>
  )
}

// ── 主页面 ──
export default function ChoreoPage(): JSX.Element {
  const [choreos, setChoreos] = useState<Choreo[]>([])
  const [loading, setLoading] = useState(false)
  const [editor, setEditor] = useState<{ open: boolean; choreo: Choreo | null }>({ open: false, choreo: null })
  const [running, setRunning] = useState<ChoreoRun | null>(null)
  const pollTimer = useRef<number | null>(null)

  const load = useCallback(async () => {
    setLoading(true)
    try { setChoreos(await api.listChoreos()) } catch { toast.error('平台服务不可达') }
    setLoading(false)
  }, [])

  useEffect(() => { void load() }, [load])

  // hub 实时订阅：其他端触发的运行也可见
  useEffect(() => hubWs(() => { /* robots 已由全局订阅 */ }, (runs) => {
    if (runs.length) setRunning(runs[0])
  }), [])

  useEffect(() => () => { if (pollTimer.current) clearInterval(pollTimer.current) }, [])

  async function doRun(id: string, name: string): Promise<void> {
    try {
      const r = await api.runChoreo(id)
      if (!r.ok || !r.run_id) { toast.error(r.error || '启动失败'); return }
      if (r.offline?.length) toast.warning(`以下机器人未参与：${r.offline.join('、')}`)
      setRunning({ run_id: r.run_id, choreo_id: id, name, state: 'running', start_ts: 0, robots: [], created_at: '', ended_at: '' })
      // 轮询到终态
      if (pollTimer.current) clearInterval(pollTimer.current)
      pollTimer.current = window.setInterval(async () => {
        try {
          const st = await api.choreoRunStatus(r.run_id as string)
          setRunning(st)
          if (['finished', 'stopped', 'failed'].includes(st.state)) {
            if (pollTimer.current) clearInterval(pollTimer.current)
            const fails = st.robots.filter((rb) => rb.failed?.length || rb.state === 'failed')
            if (st.state === 'finished' && !fails.length) toast.success(`编排「${name}」完成`)
            else toast.warning(`编排「${name}」结束：${st.robots.map((rb) => `${rb.name}:${rb.state}${rb.failed?.length ? `(失败${rb.failed.length})` : ''}`).join('，')}`)
          }
        } catch { /* 平台重启等，忽略单次失败 */ }
      }, 1000)
    } catch { toast.error('启动请求失败') }
  }

  async function doStop(): Promise<void> {
    if (!running) return
    try { await api.stopChoreoRun(running.run_id); toast.success('已发送停止') } catch { toast.error('停止失败') }
  }

  async function doDelete(c: Choreo): Promise<void> {
    try { await api.deleteChoreo(c.id); toast.success('已删除'); void load() } catch { toast.error('删除失败') }
  }

  return (
    <div className="page">
      <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'flex-start' }}>
        <div>
          <h1 className="page-title"><Clapperboard style={{ verticalAlign: 'middle', marginRight: 8 }} />多机编排</h1>
          <p className="page-sub">时间线多轨：每台机器人一条轨道，全局时间轴对齐执行（共 {choreos.length} 个编排）</p>
        </div>
        <Space>
          <Button icon={<RefreshCw size={14} />} onClick={() => void load()}>刷新</Button>
          <Button theme="solid" icon={<Plus size={14} />} onClick={() => setEditor({ open: true, choreo: null })}>新建编排</Button>
        </Space>
      </div>

      {/* 执行状态条 */}
      {running && (
        <div className="choreo-run-bar">
          <div style={{ display: 'flex', alignItems: 'center', gap: 12, width: '100%' }}>
            <Tag color={running.state === 'running' ? 'green' : 'grey'}>{running.state === 'running' ? '执行中' : running.state}</Tag>
            <b>{running.name}</b>
            {running.state === 'running' && <Button size="small" theme="borderless" type="danger" icon={<StopCircle size={14} />} onClick={() => void doStop()}>停止</Button>}
            <div style={{ flex: 1 }} />
            {running.robots.map((rb) => (
              <span key={rb.robot_id} style={{ fontSize: 12 }}>
                {rb.name}: <Tag size="small" color={rb.state === 'running' ? 'green' : rb.state === 'finished' ? 'blue' : 'red'}>
                  {rb.state === 'running' ? `${Math.max(rb.current + 1, 0)}/${rb.total}` : rb.state}
                </Tag>
              </span>
            ))}
          </div>
        </div>
      )}

      {/* 列表 */}
      {choreos.length === 0 && !loading ? (
        <Empty title="暂无编排" description="点击右上角「新建编排」，选择多台机器人排一条时间线" style={{ marginTop: 80 }} />
      ) : (
        <div className="robot-grid" style={{ marginTop: 16 }}>
          {choreos.map((c) => (
            <div key={c.id} className="gg-card hoverable choreo-card">
              <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'flex-start' }}>
                <div>
                  <div style={{ fontWeight: 700, fontSize: 15 }}>{c.name}</div>
                  <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 4, minHeight: 34 }}>{c.desc || '暂无描述'}</div>
                </div>
              </div>
              <div style={{ margin: '8px 0', fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                {c.robot_count ?? 0} 台机器人 · {c.step_count ?? 0} 个步骤
              </div>
              <Space>
                <Button size="small" theme="solid" type="primary" icon={<Play size={13} />} onClick={() => void doRun(c.id, c.name)}>执行</Button>
                <Button size="small" icon={<Pencil size={13} />} onClick={() => setEditor({ open: true, choreo: c })}>编辑</Button>
                <Button size="small" theme="borderless" type="danger" icon={<Trash2 size={13} />} onClick={() => void doDelete(c)}>删除</Button>
              </Space>
            </div>
          ))}
        </div>
      )}

      {editor.open && (
        <ChoreoEditor initial={editor.choreo} onClose={() => setEditor({ open: false, choreo: null })}
          onSaved={() => void load()} />
      )}
    </div>
  )
}
