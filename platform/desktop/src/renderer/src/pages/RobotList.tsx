/**机器人管理 — 列表/改名/删除/网段扫描 + 弹窗内直接配对*/

import { useEffect, useState, useCallback } from 'react'
import { useNavigate } from 'react-router-dom'
import { Tag, Button, Table, Modal, Toast, Input, Typography, Banner } from '@douyinfe/semi-ui'
import { Plus, RefreshCw, ScanSearch, Trash2, Pencil } from 'lucide-react'
import { api, type RobotRecord } from '@/api/platform'
import { useAppStore } from '@/stores/app'
import type { InstallProgress } from '../../../preload/index'

interface ScanHit {
  ip: string; sn: string; model: string; version: string
  paired: boolean; registered: boolean; robot_id: string | null; name: string
}

export default function RobotList(): JSX.Element {
  const nav = useNavigate()
  const { port } = useAppStore()
  const [robots, setRobots] = useState<RobotRecord[]>([])
  const [loading, setLoading] = useState(false)
  const [scanOpen, setScanOpen] = useState(false)
  const [scanning, setScanning] = useState(false)
  const [scanHits, setScanHits] = useState<ScanHit[]>([])
  const [subnet, setSubnet] = useState('10.10.4')

  // ── 弹窗内直接配对（轻配对：agent 已在跑，写 token + 重启服务）──
  const [pairTarget, setPairTarget] = useState<ScanHit | null>(null)
  const [pairUser, setPairUser] = useState('agi')
  const [pairPass, setPairPass] = useState('')
  const [pairName, setPairName] = useState('')
  const [pairRunning, setPairRunning] = useState(false)
  const [pairProgress, setPairProgress] = useState<InstallProgress | null>(null)

  const load = useCallback(async (refresh = false) => {
    setLoading(true)
    try {
      setRobots(await api.listRobots(refresh))
    } catch {
      Toast.error('平台服务不可达')
    }
    setLoading(false)
  }, [])

  useEffect(() => { void load() }, [load])

  useEffect(() => {
    if (!window.desktop) return
    return window.desktop.onInstallProgress((p) => {
      if (p.step !== 'done') { setPairProgress(p); return }
      setPairRunning(false)
      setPairProgress(p)
      if (!p.error) {
        Toast.success('配对成功')
        setPairTarget(null)
        void load(true)
      }
    })
  }, [load])

  async function doPair(): Promise<void> {
    if (!pairTarget) return
    if (!pairPass) { Toast.warning('请输入 SSH 密码') ; return }
    setPairRunning(true)
    setPairProgress(null)
    await window.desktop.installAgent({
      host: pairTarget.ip, username: pairUser, password: pairPass,
      debPath: '', name: pairName, platformPort: port,
    })
  }

  async function doScan(): Promise<void> {
    setScanning(true)
    try {
      setScanHits((await api.scanSubnet(subnet)) as ScanHit[])
    } catch {
      Toast.error('扫描失败')
    }
    setScanning(false)
  }

  async function rename(rb: RobotRecord): Promise<void> {
    let name = rb.name
    Modal.confirm({
      title: '重命名机器人',
      content: (
        <Input defaultValue={rb.name} onChange={(v) => { name = v }}
          placeholder={rb.sn} style={{ marginTop: 8 }} />
      ),
      onOk: async () => {
        await api.patchRobot(rb.id, { name })
        void load()
      },
    })
  }

  function remove(rb: RobotRecord): void {
    Modal.confirm({
      title: `移除「${rb.name}」？`,
      content: '仅从平台删除登记（SN/token），机器人上的 agent 不受影响，可随时重新配对。',
      okType: 'danger',
      onOk: async () => {
        await api.deleteRobot(rb.id)
        Toast.success('已移除')
        void load()
      },
    })
  }

  return (
    <div className="page">
      <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 16 }}>
        <div style={{ flex: 1 }}>
          <h1 className="page-title">机器人</h1>
          <p className="page-sub" style={{ marginBottom: 0 }}>登记的设备 · SN 为物理身份</p>
        </div>
        <Button icon={<RefreshCw size={14} />} loading={loading}
          onClick={() => void load(true)}>刷新</Button>
        <Button icon={<ScanSearch size={14} />} onClick={() => { setScanOpen(true); void doScan() }}>
          扫描网段
        </Button>
        <Button theme="solid" icon={<Plus size={14} />} onClick={() => nav('/robots/add')}>
          添加机器人
        </Button>
      </div>

      <Table<RobotRecord>
        rowKey="id"
        dataSource={robots}
        empty="暂无机器人 — 点右上「添加机器人」装第一台"
        pagination={false}
        columns={[
          {
            title: '名称', dataIndex: 'name',
            render: (v: string, rb) => (
              <span style={{ fontWeight: 600 }}>
                {v}
                <Typography.Text type="tertiary" size="small" style={{ marginLeft: 8 }}>
                  {rb.model.toUpperCase()}
                </Typography.Text>
              </span>
            ),
          },
          { title: 'SN', dataIndex: 'sn', render: (v: string) => <code style={{ fontSize: 12 }}>{v}</code> },
          { title: 'IP', dataIndex: 'last_ip' },
          {
            title: '状态',
            render: (_v, rb) => {
              const s = rb.summary
              return (
                <div style={{ display: 'flex', gap: 6 }}>
                  <Tag size="small" color={s?.online ? 'green' : 'grey'} shape="circle">
                    {s?.online ? '在线' : '离线'}
                  </Tag>
                  {rb.status === 'pending' && <Tag size="small" color="orange" shape="circle">装机中</Tag>}
                  {s?.battery_soc != null && <Tag size="small" shape="circle">{s.battery_soc}%</Tag>}
                </div>
              )
            },
          },
          {
            title: '', width: 120,
            render: (_v, rb) => (
              <div style={{ display: 'flex', gap: 4 }}>
                <Button size="small" theme="borderless" icon={<Pencil size={13} />}
                  onClick={() => rename(rb)} />
                <Button size="small" theme="borderless" type="danger" icon={<Trash2 size={13} />}
                  onClick={() => remove(rb)} />
              </div>
            ),
          },
        ]}
      />

      <Modal
        title="扫描网段（探测 :8300 agent）"
        visible={scanOpen}
        footer={null}
        onCancel={() => setScanOpen(false)}
        width={620}
      >
        <div style={{ display: 'flex', gap: 8, marginBottom: 12 }}>
          <Input value={subnet} onChange={setSubnet} style={{ width: 160 }} placeholder="10.10.4" />
          <Button loading={scanning} icon={<ScanSearch size={14} />} onClick={() => void doScan()}>
            重新扫描
          </Button>
        </div>
        {scanHits.length === 0 && !scanning && <Typography.Text type="tertiary">未发现 agent</Typography.Text>}
        {scanHits.map((h) => (
          <div key={h.ip} style={{
            display: 'flex', alignItems: 'center', gap: 10, padding: '8px 0',
            borderBottom: '1px solid var(--border)',
          }}>
            <code style={{ fontSize: 12 }}>{h.ip}</code>
            <Typography.Text size="small">SN {h.sn}</Typography.Text>
            <div style={{ flex: 1 }} />
            {h.registered ? (
              <Tag size="small" color="blue" shape="circle">已登记 · {h.name}</Tag>
            ) : (
              <>
                <Tag size="small" color="amber" shape="circle">未登记</Tag>
                <Button size="small" theme="solid" onClick={() => {
                  setPairTarget(h); setPairPass(''); setPairProgress(null); setPairName('')
                }}>
                  配对
                </Button>
              </>
            )}
          </div>
        ))}

        {/* 弹窗内直接配对（agent 已在跑 → 快速配对，无需 deb） */}
        <Modal
          title={pairTarget ? `配对 ${pairTarget.ip}` : ''}
          visible={!!pairTarget}
          onCancel={() => { if (!pairRunning) setPairTarget(null) }}
          footer={null}
          width={460}
        >
          {!pairRunning && !pairProgress?.error && !pairProgress?.detail?.includes('成功') ? (
            <div style={{ display: 'grid', gap: 12 }}>
              <Typography.Text type="tertiary" size="small">
                SN {pairTarget?.sn} · 检测到 agent 运行中，将执行快速配对（写令牌 + 重启服务）
              </Typography.Text>
              <Input value={pairUser} onChange={setPairUser} placeholder="SSH 用户名（agi）" />
              <Input mode="password" value={pairPass} onChange={setPairPass} placeholder="SSH 密码" />
              <Input value={pairName} onChange={setPairName} placeholder="别名（可选，如：展厅 X2）" />
              <Button theme="solid" size="large" onClick={() => void doPair()}>开始配对</Button>
            </div>
          ) : (
            <div style={{ display: 'grid', gap: 10, padding: '8px 0' }}>
              {pairProgress?.error
                ? <Banner type="danger" closeIcon={null} description={pairProgress.error} />
                : <Banner type="info" closeIcon={null}
                    description={pairProgress?.detail ?? '连接中...'} />}
              {pairProgress?.error && (
                <Button onClick={() => { setPairProgress(null); setPairRunning(false) }}>重试</Button>
              )}
            </div>
          )}
        </Modal>
      </Modal>
    </div>
  )
}
