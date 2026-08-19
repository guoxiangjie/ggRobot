/**添加机器人（装机向导）— 表单 → SSH 推装（一键到底）→ 完成*/

import { useEffect, useState } from 'react'
import { useNavigate, useSearchParams } from 'react-router-dom'
import { Card, Button, Input, Typography, Steps, Progress, Toast, Banner } from '@douyinfe/semi-ui'
import { PackagePlus, ArrowLeft } from 'lucide-react'
import { useAppStore } from '@/stores/app'
import type { InstallProgress } from '../../../preload/index'

const STEP_DEFS: { key: string; label: string }[] = [
  { key: 'connect', label: 'SSH 连接' },
  { key: 'read-sn', label: '读取 SN' },
  { key: 'register', label: '平台登记' },
  { key: 'stop-legacy', label: '停 1.0 服务' },
  { key: 'upload-deb', label: '推送安装包' },
  { key: 'upload-token', label: '下发配对令牌' },
  { key: 'install', label: '安装（apt + systemd）' },
  { key: 'restart', label: '重启服务' },
  { key: 'health-poll', label: '就绪验证' },
  { key: 'done', label: '完成' },
]

export default function AddRobot(): JSX.Element {
  const nav = useNavigate()
  const { port } = useAppStore()
  const [searchParams] = useSearchParams()

  // 从扫描弹窗跳转时预填 IP（HashRouter 的 query 需用 useSearchParams 解析）
  const [host, setHost] = useState(searchParams.get('ip') ?? '10.10.4.175')
  const [username, setUsername] = useState('agi')
  const [password, setPassword] = useState('')
  const [name, setName] = useState('')
  const [debPath, setDebPath] = useState('')

  const [running, setRunning] = useState(false)
  const [steps, setSteps] = useState<Record<string, InstallProgress>>({})
  const [done, setDone] = useState<'ok' | 'fail' | null>(null)

  useEffect(() => {
    if (!window.desktop) return
    return window.desktop.onInstallProgress((p) => {
      setSteps((prev) => ({ ...prev, [p.step]: p }))
      if (p.step === 'done') {
        setRunning(false)
        setDone(p.error ? 'fail' : 'ok')
      }
    })
  }, [])

  async function start(): Promise<void> {
    if (!password) { Toast.warning('请输入 SSH 密码') ; return }
    // deb 仅完整装机需要（检测到 agent 已运行时自动走快速配对，无需 deb）
    const dp = debPath || ''

    setRunning(true)
    setDone(null)
    setSteps({})
    await window.desktop.installAgent({
      host, username, password, debPath: dp, name, platformPort: port,
    })
  }

  const errStep = Object.values(steps).find((s) => s.error)

  return (
    <div className="page" style={{ maxWidth: 720 }}>
      <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 16 }}>
        <Button icon={<ArrowLeft size={14} />} theme="borderless" onClick={() => nav('/robots')} />
        <div>
          <h1 className="page-title">添加机器人</h1>
          <p className="page-sub" style={{ marginBottom: 0 }}>
            一键装机：SSH 推 deb → 免密 apt 安装 → systemd 常驻 → 自动配对
          </p>
        </div>
      </div>

      <Card style={{ marginBottom: 16 }}>
        <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: 14 }}>
          <div>
            <Typography.Text type="tertiary" size="small">机器人 IP</Typography.Text>
            <Input value={host} onChange={setHost} placeholder="10.10.4.175" />
          </div>
          <div>
            <Typography.Text type="tertiary" size="small">SSH 用户名</Typography.Text>
            <Input value={username} onChange={setUsername} placeholder="agi" />
          </div>
          <div>
            <Typography.Text type="tertiary" size="small">SSH 密码</Typography.Text>
            <Input mode="password" value={password} onChange={setPassword} placeholder="agi 账号密码" />
          </div>
          <div>
            <Typography.Text type="tertiary" size="small">别名（可选）</Typography.Text>
            <Input value={name} onChange={setName} placeholder="实验室 X2-1号" />
          </div>
          <div style={{ gridColumn: '1 / -1' }}>
            <Typography.Text type="tertiary" size="small">deb 安装包（make agent-deb 产物）</Typography.Text>
            <div style={{ display: 'flex', gap: 8 }}>
              <Input value={debPath} onChange={setDebPath}
                placeholder="agents/x2/packaging/build/ggrobot-agent_*.deb" />
              <Button disabled={!window.desktop} icon={<PackagePlus size={14} />}
                onClick={async () => {
                  const p = await window.desktop.pickDeb()
                  if (p) setDebPath(p)
                }}>选择</Button>
            </div>
          </div>
        </div>
        <div style={{ marginTop: 16, display: 'flex', gap: 10 }}>
          <Button theme="solid" size="large" loading={running} onClick={() => void start()}>
            开始装机
          </Button>
          {done === 'ok' && (
            <Button size="large" onClick={() => nav('/')}>去总览看看</Button>
          )}
        </div>
      </Card>

      {(running || done) && (
        <Card>
          <Steps direction="vertical" size="small" style={{ maxHeight: 420, overflow: 'auto' }}>
            {STEP_DEFS.filter((d) => steps[d.key]).map((d, i, arr) => {
              const s = steps[d.key]
              // 只显示已发生的步骤；最后一步进行中（done 除外）
              const status: 'finish' | 'error' | 'process' =
                s.error ? 'error'
                  : i === arr.length - 1 && d.key !== 'done' ? 'process'
                    : 'finish'
              return (
                <Steps.Step
                  key={d.key}
                  title={d.label}
                  status={status}
                  description={
                    s?.error
                      ? <Typography.Text type="danger" size="small">{s.error}</Typography.Text>
                      : s?.detail
                        ? <Typography.Text type="tertiary" size="small">{s.detail}</Typography.Text>
                        : null
                  }
                />
              )
            })}
          </Steps>
          {steps['upload-deb']?.progress != null && steps['upload-deb'].progress < 1 && (
            <Progress percent={Math.round(steps['upload-deb'].progress * 100)} style={{ marginTop: 8 }} />
          )}
        </Card>
      )}

      {done === 'ok' && (
        <Banner type="success" closeIcon={null} style={{ marginTop: 12 }}
          description="装机完成，机器人已自动配对（hub 最长 5s 后点亮在线状态）" />
      )}
      {done === 'fail' && (
        <Banner type="danger" closeIcon={null} style={{ marginTop: 12 }}
          description={<>装机失败：{errStep?.error ?? '未知错误'}<br />
            可检查：机器人可达性 / SSH 密码 / deb 路径；失败可重试（幂等，token 不会被覆盖）</>} />
      )}
    </div>
  )
}
