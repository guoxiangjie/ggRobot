import { toast } from '@/api/toast'
/**添加机器人（装机向导独立窗口页，#/add-robot）— 表单 → SSH 推装（一键到底）→ 完成
   agent 已运行时自动走快速配对（无需 deb）。装机中途关窗自动 abort。*/

import { useEffect, useRef, useState } from 'react'
import { Button, Input, Typography, Steps, Progress, Banner } from '@douyinfe/semi-ui'
import { PackagePlus } from 'lucide-react'
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

export default function AddRobotPage(): JSX.Element {
  const { port } = useAppStore()

  const [host, setHost] = useState('10.10.4.175')
  const [username, setUsername] = useState('agi')
  const [password, setPassword] = useState('')
  const [name, setName] = useState('')
  const [debPath, setDebPath] = useState('')

  const [running, setRunning] = useState(false)
  const [steps, setSteps] = useState<Record<string, InstallProgress>>({})
  const [done, setDone] = useState<'ok' | 'fail' | null>(null)
  const jobIdRef = useRef<string | null>(null)

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

  // 装机中途关窗（红绿灯）→ 中止 SSH 任务，不留孤儿 job
  useEffect(() => () => {
    if (jobIdRef.current) window.desktop?.installAbort(jobIdRef.current)
  }, [])

  async function start(): Promise<void> {
    if (!password) { toast.warning('请输入 SSH 密码') ; return }
    const dp = debPath || ''   // agent 已在跑时快速配对无需 deb
    setRunning(true)
    setDone(null)
    setSteps({})
    const { jobId } = await window.desktop.installAgent({
      host, username, password, debPath: dp, name, platformPort: port,
    })
    jobIdRef.current = jobId
  }

  const errStep = Object.values(steps).find((s) => s.error)

  return (
    <div>
      {/* 自绘标题条（drag 区，红绿灯落左侧留白）；主题暗色适配复用 .titlebar 规则 */}
      <div className="titlebar" style={{ paddingLeft: 84 }}>
        <span className="title">添加机器人（装机向导）</span>
      </div>
      <div style={{ padding: '20px 32px 28px', maxWidth: 720, margin: '0 auto' }}>
      <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginBottom: 16 }}>
        一键装机：SSH 推 deb → 免密 apt 安装 → systemd 常驻 → 自动配对；机器人上已有 agent 时自动走快速配对（秒级）
      </Typography.Text>

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
          <Typography.Text type="tertiary" size="small">deb 安装包（首次装机需要；快速配对可留空）</Typography.Text>
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
          <Button size="large" onClick={() => window.close()}>完成</Button>
        )}
      </div>

      {(running || done) && (
        <div style={{ marginTop: 14, maxHeight: 360, overflow: 'auto' }}>
          <Steps direction="vertical" size="small">
            {STEP_DEFS.filter((d) => steps[d.key]).map((d, i, arr) => {
              const s = steps[d.key]
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
        </div>
      )}

      {done === 'ok' && (
        <Banner type="success" closeIcon={null} style={{ marginTop: 12 }}
          description="装机完成，机器人已自动配对（总览 5 秒内点亮在线）" />
      )}
      {done === 'fail' && (
        <Banner type="danger" closeIcon={null} style={{ marginTop: 12 }}
          description={<>装机失败：{errStep?.error ?? '未知错误'}<br />
            可检查：机器人可达性 / SSH 密码 / deb 路径；失败可重试（幂等）</>} />
      )}
      </div>
    </div>
  )
}
