/**三方能力 — 可配置 HTTP 调用库（编排步骤/事件钩子复用；由平台代发）
   占位符 {{key}} 在 url/headers/body 中由入参替换；「测试」当场验证接口。 */

import { useEffect, useState, useCallback } from 'react'
import {
  Button, Modal, Input, TextArea, Select, Tag, Empty, Space, Typography,
} from '@douyinfe/semi-ui'
import { Plug, Plus, Pencil, Trash2, FlaskConical, RefreshCw } from 'lucide-react'
import { toast } from '@/api/toast'
import { api, type ThirdApiDef } from '@/api/platform'

interface EditState {
  id?: string
  name: string
  desc: string
  method: string
  url: string
  headers: { key: string; value: string }[]
  body: string
  params: { key: string; label: string; default: string }[]
  timeout: number
}
const EMPTY: EditState = {
  name: '', desc: '', method: 'GET', url: '', headers: [], body: '', params: [], timeout: 10,
}

export default function ThirdPartyPage(): JSX.Element {
  const [apis, setApis] = useState<ThirdApiDef[]>([])
  const [loading, setLoading] = useState(true)
  const [edit, setEdit] = useState<EditState | null>(null)
  const [testing, setTesting] = useState(false)
  const [testArgs, setTestArgs] = useState<Record<string, string>>({})
  const [testResult, setTestResult] = useState<string>('')

  const load = useCallback(async () => {
    setLoading(true)
    try { setApis(await api.listThirdApis()) } catch { toast.error('平台服务不可达') }
    setLoading(false)
  }, [])
  useEffect(() => { void load() }, [load])

  /**a=null → 打开新建（EMPTY）；关闭弹窗请用 closeEdit（置 null） */
  function openEdit(a: ThirdApiDef | null): void {
    setTestResult(''); setTestArgs({})
    setEdit(a
      ? {
          id: a.id, name: a.name, desc: a.desc, method: a.method, url: a.url,
          headers: a.headers || [], body: a.body || '',
          params: (a.params || []).map((p) => ({ key: p.key, label: p.label, default: p.default || '' })),
          timeout: a.timeout,
        }
      : { ...EMPTY })
  }
  function closeEdit(): void {
    setEdit(null); setTestResult(''); setTestArgs({})
  }

  async function doSave(): Promise<void> {
    if (!edit) return
    if (!edit.name.trim() || !edit.url.trim()) { toast.warning('名称和 URL 必填'); return }
    try {
      await api.saveThirdApi({ ...edit, name: edit.name.trim(), url: edit.url.trim() })
      toast.success('已保存')
      closeEdit()
      void load()
    } catch (e) {
      toast.error((e as { response?: { data?: { detail?: string } } })?.response?.data?.detail || '保存失败')
    }
  }

  async function doTest(): Promise<void> {
    if (!edit) return
    if (!edit.url.trim()) { toast.warning('URL 必填'); return }
    setTesting(true); setTestResult('')
    try {
      const r = await api.testThirdApi({
        method: edit.method, url: edit.url, headers: edit.headers,
        body: edit.body, args: testArgs, timeout: edit.timeout,
      })
      setTestResult(`HTTP ${r.status} ${r.ok ? '✓' : '✗'}\n${r.text}`)
    } catch (e) {
      setTestResult(`请求失败: ${(e as Error).message}`)
    }
    setTesting(false)
  }

  async function doDelete(a: ThirdApiDef): Promise<void> {
    try { await api.deleteThirdApi(a.id); toast.success('已删除'); void load() } catch { toast.error('删除失败') }
  }

  const setF = <K extends keyof EditState>(k: K, v: EditState[K]): void =>
    setEdit((e) => (e ? { ...e, [k]: v } : e))

  return (
    <div className="page">
      <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'flex-start' }}>
        <div>
          <h1 className="page-title"><Plug style={{ verticalAlign: 'middle', marginRight: 8 }} />三方能力</h1>
          <p className="page-sub">可配置的 HTTP 接口调用库 —— 编排里当步骤用（自动出现在类型选择器），事件钩子复用</p>
        </div>
        <Space>
          <Button icon={<RefreshCw size={14} />} onClick={() => void load()}>刷新</Button>
          <Button theme="solid" icon={<Plus size={14} />} onClick={() => openEdit(null)}>新建能力</Button>
        </Space>
      </div>

      {!loading && apis.length === 0 && (
        <Empty title="暂无三方能力" description="点右上「新建能力」配置第一个接口（如开门控制器、企业微信通知）" style={{ marginTop: 80 }} />
      )}

      <div className="robot-grid" style={{ marginTop: 8 }}>
        {apis.map((a) => (
          <div key={a.id} className="gg-card free-item">
            <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
              <Tag size="small" color={a.method === 'POST' ? 'orange' : 'blue'}>{a.method}</Tag>
              <div style={{ fontWeight: 700, fontSize: 14, flex: 1, minWidth: 0,
                overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{a.name}</div>
            </div>
            <div style={{ fontSize: 11, color: 'var(--semi-color-text-2)', marginTop: 6, minHeight: 32,
              overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{a.desc || a.url}</div>
            <div style={{ fontSize: 11, color: 'var(--semi-color-text-2)', marginTop: 2,
              overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>
              {a.url}{a.params.length ? ` · ${a.params.length} 个入参` : ''}
            </div>
            <div style={{ display: 'flex', justifyContent: 'flex-end', gap: 2, marginTop: 6 }}>
              <Button size="small" icon={<FlaskConical size={12} />} onClick={() => {
                openEdit(a)
                const args: Record<string, string> = {}
                for (const p of a.params || []) args[p.key] = p.default || ''
                setTestArgs(args)
              }}>测试</Button>
              <Button size="small" icon={<Pencil size={12} />} onClick={() => openEdit(a)} />
              <Button size="small" theme="borderless" type="danger" icon={<Trash2 size={12} />} onClick={() => void doDelete(a)} />
            </div>
          </div>
        ))}
      </div>

      {/* 编辑 + 测试台 */}
      <Modal title={edit?.id ? `编辑 · ${edit.name}` : '新建三方能力'} visible={!!edit}
        onCancel={closeEdit} width={620}
        footer={<>
          <Button theme="borderless" onClick={closeEdit}>取消</Button>
          <Button icon={<FlaskConical size={13} />} loading={testing} onClick={() => void doTest()}>测试</Button>
          <Button theme="solid" onClick={() => void doSave()}>保存</Button>
        </>}>
        {edit && (
          <div style={{ display: 'grid', gap: 10 }}>
            <div style={{ display: 'flex', gap: 8 }}>
              <div style={{ flex: 1 }}>
                <Typography.Text type="tertiary" size="small">名称 *</Typography.Text>
                <Input value={edit.name} onChange={(v) => setF('name', v)} placeholder="如：开门控制器" />
              </div>
              <div style={{ width: 100 }}>
                <Typography.Text type="tertiary" size="small">方法</Typography.Text>
                <Select<string> value={edit.method} style={{ width: '100%' }}
                  optionList={[{ label: 'GET', value: 'GET' }, { label: 'POST', value: 'POST' }]}
                  onChange={(v) => setF('method', String(v ?? 'GET'))} />
              </div>
            </div>
            <div>
              <Typography.Text type="tertiary" size="small">描述</Typography.Text>
              <Input value={edit.desc} onChange={(v) => setF('desc', v)} placeholder="用途说明（可选）" />
            </div>
            <div>
              <Typography.Text type="tertiary" size="small">URL *（{'{{入参}}'} 占位，如 ?city={'{{city}}'}）</Typography.Text>
              <Input value={edit.url} onChange={(v) => setF('url', v)} placeholder="http://192.168.1.10:8080/open?door={{door_id}}" />
            </div>
            <div>
              <Typography.Text type="tertiary" size="small">入参声明（使用方在编排里填；key 对应占位符）</Typography.Text>
              {edit.params.map((p, i) => (
                <div key={i} style={{ display: 'flex', gap: 6, marginBottom: 6 }}>
                  <Input value={p.key} placeholder="key" style={{ width: 110 }}
                    onChange={(v) => setF('params', edit.params.map((x, j) => (j === i ? { ...x, key: v } : x)))} />
                  <Input value={p.label} placeholder="显示名" style={{ width: 110 }}
                    onChange={(v) => setF('params', edit.params.map((x, j) => (j === i ? { ...x, label: v } : x)))} />
                  <Input value={p.default} placeholder="默认值" style={{ flex: 1 }}
                    onChange={(v) => setF('params', edit.params.map((x, j) => (j === i ? { ...x, default: v } : x)))} />
                  <Button size="small" theme="borderless" type="danger" onClick={() => setF('params', edit.params.filter((_, j) => j !== i))}>×</Button>
                </div>
              ))}
              <Button size="small" theme="light" icon={<Plus size={12} />}
                onClick={() => setF('params', [...edit.params, { key: '', label: '', default: '' }])}>加入参</Button>
            </div>
            <div>
              <Typography.Text type="tertiary" size="small">Headers（value 可含占位符）</Typography.Text>
              {edit.headers.map((h, i) => (
                <div key={i} style={{ display: 'flex', gap: 6, marginBottom: 6 }}>
                  <Input value={h.key} placeholder="Key" style={{ width: 150 }}
                    onChange={(v) => setF('headers', edit.headers.map((x, j) => (j === i ? { ...x, key: v } : x)))} />
                  <Input value={h.value} placeholder="Value" style={{ flex: 1 }}
                    onChange={(v) => setF('headers', edit.headers.map((x, j) => (j === i ? { ...x, value: v } : x)))} />
                  <Button size="small" theme="borderless" type="danger" onClick={() => setF('headers', edit.headers.filter((_, j) => j !== i))}>×</Button>
                </div>
              ))}
              <Button size="small" theme="light" icon={<Plus size={12} />}
                onClick={() => setF('headers', [...edit.headers, { key: '', value: '' }])}>加 Header</Button>
            </div>
            {edit.method === 'POST' && (
              <div>
                <Typography.Text type="tertiary" size="small">Body 模板（JSON，占位符替换后发送）</Typography.Text>
                <TextArea value={edit.body} onChange={(v) => setF('body', v)} rows={3}
                  placeholder={"{\"cmd\": \"{{cmd}}\", \"floor\": {{floor}}}"} autosize />
              </div>
            )}
            <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
              <Typography.Text type="tertiary" size="small">超时</Typography.Text>
              <Input value={String(edit.timeout)} onChange={(v) => setF('timeout', Number(v) || 10)} style={{ width: 70 }} />
              <Typography.Text type="tertiary" size="small">秒</Typography.Text>
            </div>

            {/* 测试区 */}
            {edit.params.some((p) => p.key) && (
              <div>
                <Typography.Text type="tertiary" size="small">测试入参</Typography.Text>
                <div style={{ display: 'flex', flexWrap: 'wrap', gap: 6 }}>
                  {edit.params.filter((p) => p.key).map((p) => (
                    <span key={p.key} style={{ display: 'inline-flex', alignItems: 'center', gap: 4, fontSize: 12 }}>
                      {p.label || p.key}:
                      <Input size="small" value={testArgs[p.key] ?? ''} style={{ width: 120 }}
                        onChange={(v) => setTestArgs((t) => ({ ...t, [p.key]: v }))} />
                    </span>
                  ))}
                </div>
              </div>
            )}
            {testResult && (
              <div style={{
                background: 'var(--semi-color-fill-0)', borderRadius: 8, padding: 10,
                fontFamily: 'monospace', fontSize: 11, whiteSpace: 'pre-wrap', maxHeight: 200, overflow: 'auto',
              }}>{testResult}</div>
            )}
          </div>
        )}
      </Modal>
    </div>
  )
}
