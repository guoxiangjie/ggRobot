/**多机编排 — 列表 / 执行监控 / 最近执行（docs/choreo-design.md §6）
   2026-08 交互改版：新建只填名称；点击卡片（或「编辑」）开独立窗口编辑（ChoreoEdit.tsx），
   编辑窗保存关闭后本页 focus 时自动刷新列表。
   执行：平台分发各机轨道 → 广播 start_ts → agent 本地按 at 推进（时间戳锚定）。 */

import { useEffect, useState, useCallback, useRef } from 'react'
import { Button, Modal, Input, Tag, Empty, Space, Typography } from '@douyinfe/semi-ui'
import {
  Clapperboard, Plus, Play, Pencil, Trash2, RefreshCw, StopCircle,
} from 'lucide-react'
import { toast } from '@/api/toast'
import { api, hubWs, type Choreo, type ChoreoRun } from '@/api/platform'

// 状态徽标统一中文（run 级与机器人级共用）
const STATE_CN: Record<string, string> = {
  running: '执行中', finished: '完成', stopped: '已停止', failed: '失败',
  unavailable: '未参与', loading: '分发中', pending: '待执行',
}

export default function ChoreoPage(): JSX.Element {
  const [choreos, setChoreos] = useState<Choreo[]>([])
  const [history, setHistory] = useState<ChoreoRun[]>([])
  const [loading, setLoading] = useState(false)
  const [creating, setCreating] = useState(false)
  const [newName, setNewName] = useState('')
  const [running, setRunning] = useState<ChoreoRun | null>(null)
  const pollTimer = useRef<number | null>(null)

  const load = useCallback(async () => {
    setLoading(true)
    try { setChoreos(await api.listChoreos()) } catch { toast.error('平台服务不可达') }
    try { setHistory(await api.choreoRuns()) } catch { /* 历史非关键 */ }
    setLoading(false)
  }, [])

  useEffect(() => { void load() }, [load])

  // 编辑窗保存关闭后本窗获得焦点 → 静默刷新列表
  useEffect(() => {
    const onFocus = (): void => { void load() }
    window.addEventListener('focus', onFocus)
    return () => window.removeEventListener('focus', onFocus)
  }, [load])

  // hub 实时订阅：其他端触发的运行也可见
  useEffect(() => hubWs(() => { /* robots 已由全局订阅 */ }, (runs) => {
    if (runs.length) setRunning(runs[0])
  }), [])

  useEffect(() => () => { if (pollTimer.current) clearInterval(pollTimer.current) }, [])

  // 新建：只填名称（轨道在编辑窗补）
  async function doCreate(): Promise<void> {
    if (!newName.trim()) { toast.warning('请填写编排名称'); return }
    try {
      await api.saveChoreo({ name: newName.trim(), desc: '', tracks: [] })
      toast.success('已创建，点击卡片编辑内容')
      setCreating(false); setNewName('')
      void load()
    } catch { toast.error('创建失败') }
  }

  function openEdit(id: string): void {
    void window.desktop?.openChoreoEdit(id)
  }

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
            void load()  // 刷新最近执行
            const fails = st.robots.filter((rb) => rb.failed?.length || rb.state === 'failed')
            if (st.state === 'finished' && !fails.length) toast.success(`编排「${name}」完成`)
            else toast.warning(`编排「${name}」结束：${
              st.robots.map((rb) => `${rb.name}:${rb.state}${rb.error ? `（${rb.error}）` : rb.failed?.length ? `(失败${rb.failed.length})` : ''}`).join('，')
            }`, 8)
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
          <Button theme="solid" icon={<Plus size={14} />} onClick={() => setCreating(true)}>新建编排</Button>
        </Space>
      </div>

      {/* 执行状态条 */}
      {running && (
        <div className="choreo-run-bar">
          <div style={{ display: 'flex', alignItems: 'center', gap: 12, width: '100%' }}>
            <Tag color={running.state === 'running' ? 'green' : 'grey'}>{STATE_CN[running.state] || running.state}</Tag>
            <b>{running.name}</b>
            {running.state === 'running' && <Button size="small" theme="borderless" type="danger" icon={<StopCircle size={14} />} onClick={() => void doStop()}>停止</Button>}
            <div style={{ flex: 1 }} />
            {running.robots.map((rb) => (
              <span key={rb.robot_id} style={{ fontSize: 12 }}>
                {rb.name}: <Tag size="small" color={rb.state === 'running' ? 'green' : rb.state === 'finished' ? 'blue' : rb.state === 'stopped' || rb.state === 'unavailable' ? 'grey' : 'red'}>
                  {rb.state === 'running' ? `${Math.max(rb.current + 1, 0)}/${rb.total}` : STATE_CN[rb.state] || rb.state}
                </Tag>
              </span>
            ))}
          </div>
        </div>
      )}

      {/* 列表：点击卡片开编辑窗 */}
      {choreos.length === 0 && !loading ? (
        <Empty title="暂无编排" description="点击右上角「新建编排」创建，再点击卡片编辑时间线" style={{ marginTop: 80 }} />
      ) : (
        <div className="robot-grid" style={{ marginTop: 16 }}>
          {choreos.map((c) => (
            <div key={c.id} className="gg-card hoverable choreo-card" style={{ cursor: 'pointer' }}
              onClick={() => openEdit(c.id)}>
              <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'flex-start' }}>
                <div>
                  <div style={{ fontWeight: 700, fontSize: 15 }}>{c.name}</div>
                  <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 4, minHeight: 34 }}>{c.desc || '暂无描述'}</div>
                </div>
              </div>
              <div style={{ margin: '8px 0', fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                {c.robot_count ?? 0} 台机器人 · {c.step_count ?? 0} 个步骤
              </div>
              <div onClick={(e) => e.stopPropagation()}>
                <Space>
                  <Button size="small" theme="solid" type="primary" icon={<Play size={13} />}
                    disabled={!c.step_count}
                    onClick={() => void doRun(c.id, c.name)}>执行</Button>
                  <Button size="small" icon={<Pencil size={13} />} onClick={() => openEdit(c.id)}>编辑</Button>
                  <Button size="small" theme="borderless" type="danger" icon={<Trash2 size={13} />} onClick={() => void doDelete(c)}>删除</Button>
                </Space>
              </div>
            </div>
          ))}
        </div>
      )}

      {/* 新建（只填名称） */}
      <Modal title="新建编排" visible={creating}
        onOk={() => void doCreate()} onCancel={() => setCreating(false)}
        okText="创建" cancelText="取消">
        <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginBottom: 8 }}>
          只需填写名称；创建后点击卡片编排时间线
        </Typography.Text>
        <Input placeholder="编排名称（如：双机迎宾）" value={newName} onChange={setNewName} autoFocus
          onEnterPress={() => void doCreate()} />
      </Modal>

      {/* 最近执行 */}
      {history.length > 0 && (
        <div style={{ marginTop: 28 }}>
          <div className="page-sub" style={{ marginBottom: 10 }}>最近执行</div>
          <div style={{ display: 'flex', flexDirection: 'column', gap: 8 }}>
            {history.slice(0, 3).map((r) => (
              <div key={r.run_id} className="choreo-run-bar" style={{ marginTop: 0 }}>
                <div style={{ display: 'flex', alignItems: 'center', gap: 10, width: '100%' }}>
                  <Tag color={r.state === 'finished' ? 'green' : r.state === 'stopped' ? 'orange' : 'red'}>{STATE_CN[r.state] || r.state}</Tag>
                  <b>{r.name}</b>
                  {(() => {
                    const fails = r.robots.filter((rb) => rb.state === 'failed')
                    return fails.length
                      ? <Tag size="small" color="red">{fails.map((f) => f.name).join('、')} 失败</Tag>
                      : null
                  })()}
                  <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{r.ended_at?.replace('T', ' ').slice(5, 19)}</span>
                </div>
              </div>
            ))}
          </div>
        </div>
      )}
    </div>
  )
}
