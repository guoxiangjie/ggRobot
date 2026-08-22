/**自由控制 — 即点即执行按钮墙（1.0 自由编排的 2.0 版）
   差异：每项绑定一台机器人；能力只留 TTS / 预设动作 / 灵创；语音+动作组合时并行下发。
   执行直连 agent（低延迟，不经平台）；重复点击 = 打断（agent 端 interrupt 语义）。 */

import { useEffect, useState, useCallback, useRef } from 'react'
import {
  Button, Modal, Input, TextArea, Select, Tag, Empty, Space, Typography, Radio, RadioGroup, Spin,
} from '@douyinfe/semi-ui'
import { Zap, Plus, Pencil, Trash2, AudioLines, PersonStanding, Sparkles, Bot } from 'lucide-react'
import { toast } from '@/api/toast'
import { platformApi, api, type FreeItem, type FreeAction } from '@/api/platform'
import { makeAgentClient } from '@/api/agent'
import { cachedLinkcraft, cachedLinkcraftAt, refreshLinkcraft, type LinkcraftItem } from '@/api/linkcraftCache'
import { useRobotsStore } from '@/stores/robots'

// agent 侧清单结构（与 ControlTab 一致；灵创结构见 linkcraftCache.ts 的 LinkcraftItem）
interface MotionAction { id: string; name: string; area: number; requires_stand: boolean }

function linkcraftType(key: string): string {
  return key.toLowerCase().includes('onnx') ? 'BODY' : 'ARM'   // 与后端类型推断一致
}

// ── 编辑弹窗 ──
interface EditState {
  id?: string
  label: string
  robot_id: string
  tts: string
  actionKind: '' | 'motion' | 'linkcraft'
  motionId: string
  resourceKey: string
}

function EditModal({ initial, onClose, onSaved }: {
  initial: EditState; onClose: () => void; onSaved: () => void
}): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)
  const [form, setForm] = useState<EditState>(initial)
  const [saving, setSaving] = useState(false)
  const [motions, setMotions] = useState<MotionAction[]>([])
  const [resources, setResources] = useState<LinkcraftItem[]>([])
  const [resFromCache, setResFromCache] = useState(false)
  const [listLoading, setListLoading] = useState(false)

  // 机器人详情缓存（ip/token，执行与清单拉取共用）— 模块级，页面也用
  const setF = (k: keyof EditState, v: string): void => setForm((f) => ({ ...f, [k]: v }))

  // 选定机器人后：预设动作直拉（快）；灵创先给缓存秒开，后台刷新（stale-while-revalidate）
  useEffect(() => {
    if (!form.robot_id) { setMotions([]); setResources([]); setResFromCache(false); return }
    let alive = true
    setListLoading(true)
    // 灵创：缓存立即上屏
    const cached = cachedLinkcraft(form.robot_id)
    setResources(cached)
    setResFromCache(cached.length > 0)
    void (async () => {
      try {
        const { data: rb } = await platformApi().get(`/api/robots/${form.robot_id}`)
        const http = makeAgentClient(rb.last_ip, rb.token)
        const [caps, fresh] = await Promise.allSettled([
          http.get('/api/capabilities', { timeout: 6000 }),
          refreshLinkcraft(form.robot_id, { ip: rb.last_ip, token: rb.token }),
        ])
        if (!alive) return
        if (caps.status === 'fulfilled') {
          const acts = caps.value.data?.capabilities?.find((c: { type: string }) => c.type === 'motion.preset')?.params?.actions
          setMotions(Array.isArray(acts) ? acts : [])
        }
        if (fresh.status === 'fulfilled' && fresh.value) {
          setResources(fresh.value)
          setResFromCache(false)
        } else if (!cached.length) {
          setResFromCache(false)   // 无缓存且刷新失败 → 手填兜底
        }
      } catch { /* 离线：预设动作留空可手填；灵创用缓存 */ }
      finally { if (alive) setListLoading(false) }
    })()
    return () => { alive = false }
  }, [form.robot_id])

  async function doSave(): Promise<void> {
    if (!form.robot_id) { toast.warning('请选择机器人'); return }
    if (!form.tts.trim() && !form.actionKind) { toast.warning('语音和动作至少填一项'); return }
    if (form.actionKind === 'motion' && !form.motionId) { toast.warning('请选择预设动作'); return }
    if (form.actionKind === 'linkcraft' && !form.resourceKey) { toast.warning('请选择灵创动作'); return }
    const action: FreeAction | null = form.actionKind === 'motion'
      ? (() => {
          // 动作清单 id 是 "3024:11"（动作号:部位）复合格式 —— 必须拆开存
          const [idStr, areaStr] = form.motionId.split(':')
          const m = motions.find((x) => x.id === form.motionId)
          return { kind: 'motion', motion_id: idStr, area: Number(areaStr) || m?.area || 2 }
        })()
      : form.actionKind === 'linkcraft'
        ? (() => {
            const r = resources.find((x) => x.resource_key === form.resourceKey)
            return { kind: 'linkcraft', resource_key: form.resourceKey, version: r?.version || '',
                     resource_type: linkcraftType(form.resourceKey) }
          })()
        : null
    setSaving(true)
    try {
      await api.saveFreeItem({
        id: form.id, label: form.label.trim() || '未命名', robot_id: form.robot_id,
        tts: form.tts.trim(), action,
      })
      toast.success('已保存')
      onSaved()
      onClose()
    } catch (e) {
      toast.error((e as { response?: { data?: { detail?: string } } })?.response?.data?.detail || '保存失败')
    }
    setSaving(false)
  }

  const robotOptions = robots.map((r) => ({ label: r.name, value: r.id }))

  return (
    <Modal title={form.id ? '编辑自由项' : '新增自由项'} visible onCancel={onClose}
      footer={<>
        <Button theme="borderless" onClick={onClose}>取消</Button>
        <Button theme="solid" loading={saving} onClick={() => void doSave()}>保存</Button>
      </>}
      style={{ width: 520 }}>
      <Space vertical align="start" style={{ width: '100%' }}>
        <div style={{ width: '100%' }}>
          <Typography.Text type="tertiary" size="small">名称</Typography.Text>
          <Input value={form.label} onChange={(v) => setF('label', v)} placeholder="如：迎宾欢迎" />
        </div>
        <div style={{ width: '100%' }}>
          <Typography.Text type="tertiary" size="small">绑定机器人 *</Typography.Text>
          <Select<string> value={form.robot_id} placeholder="选择机器人" style={{ width: '100%' }}
            optionList={robotOptions}
            onChange={(v) => setF('robot_id', String(v ?? ''))} />
        </div>
        <div style={{ width: '100%' }}>
          <Typography.Text type="tertiary" size="small">语音播报（可选，与动作同时播）</Typography.Text>
          <TextArea value={form.tts} onChange={(v) => setF('tts', v)} placeholder="要说的文字"
            autosize rows={3} maxCount={300} showCounter />
        </div>
        <div style={{ width: '100%' }}>
          <Typography.Text type="tertiary" size="small">动作（可选）</Typography.Text>
          <RadioGroup type="button" value={form.actionKind} onChange={(e) => setF('actionKind', e.target.value)}>
            <Radio value="">无</Radio>
            <Radio value="motion">预设动作</Radio>
            <Radio value="linkcraft">灵创动作</Radio>
          </RadioGroup>
        </div>
        {form.actionKind === 'motion' && (
          <div style={{ width: '100%' }}>
            <Typography.Text type="tertiary" size="small">
              预设动作{listLoading ? '（清单加载中…）' : motions.length ? '' : '（离线兜底：手填动作 ID）'}
            </Typography.Text>
            {motions.length
              ? <Select<string> value={form.motionId} placeholder="选择动作" filter style={{ width: '100%' }}
                  optionList={motions.map((m) => ({ label: m.name, value: m.id }))}
                  onChange={(v) => setF('motionId', String(v ?? ''))} />
              : <Input value={form.motionId} onChange={(v) => setF('motionId', v)} placeholder="动作 ID（如 1）" />}
          </div>
        )}
        {form.actionKind === 'linkcraft' && (
          <div style={{ width: '100%' }}>
            <Typography.Text type="tertiary" size="small">
              {(() => {
                if (listLoading) return '灵创动作（清单加载中…）'
                if (resources.length && resFromCache) {
                  const t = new Date(cachedLinkcraftAt(form.robot_id))
                  const hhmm = `${String(t.getHours()).padStart(2, '0')}:${String(t.getMinutes()).padStart(2, '0')}`
                  return `灵创动作（缓存 ${hhmm} · 后台刷新中）`
                }
                if (resources.length) return '灵创动作'
                return '灵创动作（离线兜底：手填 key）'
              })()}
            </Typography.Text>
            {resources.length
              ? <Select<string> value={form.resourceKey} placeholder="选择资源" filter style={{ width: '100%' }}
                  optionList={resources.map((r) => ({ label: r.name, value: r.resource_key }))}
                  onChange={(v) => setF('resourceKey', String(v ?? ''))} />
              : <Input value={form.resourceKey} onChange={(v) => setF('resourceKey', v)} placeholder="resource_key" />}
          </div>
        )}
      </Space>
    </Modal>
  )
}

// ── 主页面 ──
export default function FreePlayPage(): JSX.Element {
  const robots = useRobotsStore((s) => s.summaries)
  const [items, setItems] = useState<FreeItem[]>([])
  const [loading, setLoading] = useState(true)
  const [edit, setEdit] = useState<EditState | null>(null)
  const [firing, setFiring] = useState<string>('')   // 执行中的 item id

  // 机器人连接信息缓存 {robot_id: {ip, port, token}}（platform 拉一次）
  const connCache = useRef(new Map<string, { ip: string; port: number; token: string }>())

  const load = useCallback(async () => {
    setLoading(true)
    try { setItems(await api.listFreeItems()) } catch { toast.error('平台服务不可达') }
    setLoading(false)
  }, [])
  useEffect(() => { void load() }, [load])

  async function connOf(robotId: string): Promise<{ ip: string; port: number; token: string } | null> {
    const hit = connCache.current.get(robotId)
    if (hit) return hit
    try {
      const { data: rb } = await platformApi().get(`/api/robots/${robotId}`)
      const c = { ip: rb.last_ip, port: rb.port || 8300, token: rb.token }
      if (!c.ip) return null
      connCache.current.set(robotId, c)
      return c
    } catch { return null }
  }

  /**执行：TTS 与动作并行下发（agent 侧 TTS 子线程 + motion 队列天然并行；重复点击打断） */
  async function fire(item: FreeItem): Promise<void> {
    const rb = robots.find((r) => r.id === item.robot_id)
    if (!rb?.online) { toast.warning(`「${rb?.name || '机器人'}」离线`); return }
    const c = await connOf(item.robot_id)
    if (!c) { toast.error('机器人连接信息获取失败'); return }
    const http = makeAgentClient(c.ip, c.token)
    setFiring(item.id)
    const jobs: Promise<unknown>[] = []
    if (item.tts) jobs.push(http.post('/api/tts', { text: item.tts }, { timeout: 12000 }))
    if (item.action?.kind === 'motion') {
      // 历史数据兜底：motion_id 可能存过 "3024:11" 复合格式，拆开取动作号
      const mid = Number(String(item.action.motion_id).split(':')[0]) || 0
      jobs.push(http.post('/api/motion',
        { area: item.action.area ?? 2, motion_id: mid, interrupt: true },
        { timeout: 15000 }))
    } else if (item.action?.kind === 'linkcraft') {
      jobs.push(http.post('/api/resources/play',
        { resource_key: item.action.resource_key, version: item.action.version || '',
          resource_type: item.action.resource_type || linkcraftType(item.action.resource_key || '') },
        { timeout: 20000 }))
    }
    const rs = await Promise.allSettled(jobs)
    setFiring('')
    const failed = rs.filter((r) => r.status === 'rejected').length
    const badResp = rs.filter((r) => r.status === 'fulfilled' && (r.value as { data?: { ok?: boolean } })?.data?.ok === false).length
    if (failed + badResp === 0) toast.success(`已触发：${item.label}`)
    else toast.warning(`「${item.label}」部分未成功（${failed + badResp}/${jobs.length}）`)
  }

  function openEdit(item: FreeItem | null): void {
    setEdit(item
      ? {
          id: item.id, label: item.label, robot_id: item.robot_id, tts: item.tts,
          actionKind: item.action?.kind || '', motionId: item.action?.motion_id || '',
          resourceKey: item.action?.resource_key || '',
        }
      : { label: '', robot_id: '', tts: '', actionKind: '', motionId: '', resourceKey: '' })
  }

  async function doDelete(item: FreeItem): Promise<void> {
    try { await api.deleteFreeItem(item.id); toast.success('已删除'); void load() } catch { toast.error('删除失败') }
  }

  const robotName = (rid: string): string => robots.find((r) => r.id === rid)?.name || '未知机器人'

  return (
    <div className="page">
      <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'flex-start' }}>
        <div>
          <h1 className="page-title"><Zap style={{ verticalAlign: 'middle', marginRight: 8 }} />自由控制</h1>
          <p className="page-sub">点击即执行：语音 + 动作并行播发（共 {items.length} 项）</p>
        </div>
        <Button theme="solid" icon={<Plus size={14} />} onClick={() => openEdit(null)}>新增项</Button>
      </div>

      {loading ? (
        <div style={{ padding: 80, textAlign: 'center' }}><Spin size="large" /></div>
      ) : items.length === 0 ? (
        <Empty title="暂无自由项" description="点击右上角「新增项」，绑定机器人并配置语音/动作" style={{ marginTop: 80 }} />
      ) : (
        <div className="robot-grid" style={{ marginTop: 8 }}>
          {items.map((it) => {
            const rb = robots.find((r) => r.id === it.robot_id)
            const online = rb?.online
            const busy = firing === it.id
            return (
              <div key={it.id} className={`gg-card free-item${online ? '' : ' offline'}`}
                style={{ opacity: online ? 1 : 0.45, cursor: online ? 'pointer' : 'not-allowed' }}
                onClick={() => online && void fire(it)}>
                <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
                  {busy
                    ? <Spin size="small" />
                    : <span className="free-icons">
                        {it.tts && <AudioLines size={15} color="var(--semi-color-success)" />}
                        {it.action?.kind === 'motion' && <PersonStanding size={15} color="#FF9800" />}
                        {it.action?.kind === 'linkcraft' && <Sparkles size={15} color="var(--semi-color-primary)" />}
                      </span>}
                  <div style={{ fontWeight: 700, fontSize: 14, flex: 1, minWidth: 0,
                    overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{it.label}</div>
                  <Tag size="small" color="grey">
                    <span style={{ display: 'inline-flex', alignItems: 'center', gap: 3 }}>
                      <Bot size={11} />{robotName(it.robot_id)}
                    </span>
                  </Tag>
                </div>
                <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 6, minHeight: 18,
                  overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>
                  {it.tts && `🗣 ${it.tts}`}
                  {it.tts && it.action && ' ＋ '}
                  {it.action?.kind === 'motion' && `动作 ${it.action.motion_id}`}
                  {it.action?.kind === 'linkcraft' && `灵创 ${it.action.resource_key}`}
                </div>
                <div style={{ display: 'flex', justifyContent: 'flex-end', gap: 2, marginTop: 4 }}
                  onClick={(e) => e.stopPropagation()}>
                  <Button size="small" theme="borderless" icon={<Pencil size={12} />} onClick={() => openEdit(it)} />
                  <Button size="small" theme="borderless" type="danger" icon={<Trash2 size={12} />} onClick={() => void doDelete(it)} />
                </div>
              </div>
            )
          })}
        </div>
      )}

      {edit && <EditModal initial={edit} onClose={() => setEdit(null)} onSaved={() => void load()} />}
    </div>
  )
}
