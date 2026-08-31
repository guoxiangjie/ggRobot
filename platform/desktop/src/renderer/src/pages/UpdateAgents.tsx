/**Agent 批量更新弹窗 — 选 deb + 一次密码 → 多机并发更新
   链路：connect → 上传 deb → apt install（postinst 自动重启）→ 等恢复 + 版本核对。
   不动 SN/token（配对保持）；单机失败不中断其他。 */

import { useEffect, useState } from 'react'
import { Modal, Input, Button, Typography, Progress, Tag } from '@douyinfe/semi-ui'
import { PackagePlus } from 'lucide-react'
import { toast } from '@/api/toast'
import { makeAgentClient } from '@/api/agent'
import type { RobotRecord } from '@/api/platform'
import type { InstallProgress } from '../../../preload/index'

const STEP_LABEL: Record<string, string> = {
  connect: 'SSH 连接', 'upload-deb': '上传安装包', install: 'apt 安装',
  'health-poll': '等待服务就绪', restart: '重启服务', done: '完成',
}

export default function UpdateAgents({ targets: allTargets, onClose, onDone }: {
  targets: RobotRecord[]
  onClose: () => void
  onDone: () => void
}): JSX.Element {
  // A3 走 tar 包一键装机链路（更新=重跑装机），本弹窗（deb/apt）仅 X2
  const targets = allTargets.filter((r) => !String(r.model || '').startsWith('a3'))
  const skippedA3 = allTargets.length - targets.length
  const [debPath, setDebPath] = useState('')
  const [username, setUsername] = useState('agi')
  const [password, setPassword] = useState('')
  const [running, setRunning] = useState(false)
  const [finished, setFinished] = useState(false)
  const [prog, setProg] = useState<Record<string, InstallProgress>>({})   // robotId → 最新步骤

  // 更新进度事件（带 robotId；装机向导事件不带，跳过）
  useEffect(() => {
    if (!window.desktop) return
    return window.desktop.onInstallProgress((p) => {
      const rid = p.robotId
      if (!rid) return
      setProg((prev) => ({ ...prev, [rid]: p }))
    })
  }, [])

  const wantVer = (): string => debPath.split('/').pop()?.match(/_([\d][\w.~-]*?)\.deb/)?.[1] ?? ''

  async function start(): Promise<void> {
    if (!debPath) { toast.warning('请选择 deb 安装包'); return }
    if (!password) { toast.warning('请输入 SSH 密码'); return }
    setRunning(true)
    setFinished(false)
    setProg({})
    // 更新前播报：给每台在线机说一句「更新中请稍后」（失败不阻塞更新）
    try {
      await Promise.allSettled(targets.filter((t) => t.last_ip && t.summary?.online !== false).map(async (t) => {
        const http = makeAgentClient(t.last_ip, t.token)
        await http.post('/api/tts', { text: 'Agent 后端更新中，请稍后' }, { timeout: 5000 })
      }))
      await new Promise((r) => setTimeout(r, 3000))   // 让话说完再断服务
    } catch { /* 播报失败不阻塞 */ }
    try {
      const r = await window.desktop.updateAgents({
        targets: targets.filter((t) => t.last_ip).map((t) => ({ robotId: t.id, name: t.name, host: t.last_ip })),
        username, password, debPath,
      })
      const okN = r.results.filter((x) => x.ok).length
      if (okN === r.results.length) {
        toast.success(`更新完成：${okN} 台全部成功`)
        onDone()
        onClose()
      } else {
        // 失败保留弹窗：每台原因显示在下方，可重试
        toast.warning(`更新结束：${okN}/${r.results.length} 台成功（失败原因见下方）`, 6)
        setFinished(true)
        onDone()
      }
    } catch {
      toast.error('更新请求失败')
    }
    setRunning(false)
  }

  return (
    <Modal title={`更新 Agent（${targets.length} 台）`} visible onCancel={() => { if (!running) onClose() }}
      bodyStyle={{ paddingTop: 18, paddingBottom: 22 }}
      footer={running ? null : finished ? <>
        <Button theme="borderless" onClick={onClose}>关闭</Button>
        <Button theme="solid" onClick={() => void start()}>重试</Button>
      </> : <>
        <Button theme="borderless" onClick={onClose}>取消</Button>
        <Button theme="solid" onClick={() => void start()}>开始更新</Button>
      </>}
      width={560}>
      {running || finished ? (
        <div style={{ display: 'flex', flexDirection: 'column', gap: 12, padding: '4px 0 12px' }}>
          {targets.map((t) => {
            const p = prog[t.id]
            const done = p?.step === 'done'
            return (
              <div key={t.id}>
                <div style={{ display: 'flex', alignItems: 'center', gap: 8, fontSize: 13 }}>
                  <b>{t.name}</b>
                  {done
                    ? <Tag size="small" color={p?.error ? 'red' : 'green'}>{p?.error ? '失败' : `✓ ${p?.detail?.split('→')[1]?.trim() || '成功'}`}</Tag>
                    : <Typography.Text type="tertiary" size="small">
                        {p ? `${STEP_LABEL[p.step] || p.step}${p.detail ? ' · ' + p.detail : ''}` : '等待中…'}
                      </Typography.Text>}
                </div>
                {p?.step === 'upload-deb' && p.progress != null && p.progress < 1 && !done && (
                  <Progress percent={Math.round(p.progress * 100)} style={{ marginTop: 2 }} />
                )}
                {done && p?.error && (
                  <Typography.Text type="danger" size="small" style={{ display: 'block', marginTop: 2, whiteSpace: 'normal' }}>
                    {p.error.slice(0, 200)}
                  </Typography.Text>
                )}
              </div>
            )
          })}
        </div>
      ) : (
        <div style={{ display: 'grid', gap: 12 }}>
          <Typography.Text type="tertiary" size="small">
            上传新 deb 并安装（apt 原子更新，失败自动保留旧版本；配对关系保持不变；更新期间机器人会短暂离线）
          </Typography.Text>
          {skippedA3 > 0 && (
            <Typography.Text type="warning" size="small">
              已跳过 {skippedA3} 台 A3 机型（A3 更新走「添加机器人 → A3 → 一键装机」重跑即可，幂等）
            </Typography.Text>
          )}
          <div>
            <Typography.Text type="tertiary" size="small">deb 安装包 *</Typography.Text>
            <div style={{ display: 'flex', gap: 8 }}>
              <Input value={debPath} onChange={setDebPath}
                placeholder="agents/x2/packaging/build/ggrobot-agent_x.x.x_all.deb" />
              <Button icon={<PackagePlus size={14} />} disabled={!window.desktop}
                onClick={async () => {
                  const p = await window.desktop.pickDeb()
                  if (p) setDebPath(p)
                }}>选择</Button>
            </div>
            {debPath && (
              <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 4 }}>
                目标版本：{wantVer() || '（未能从文件名解析）'}
              </Typography.Text>
            )}
          </div>
          <div>
            <Typography.Text type="tertiary" size="small">SSH 凭据（一次输入，应用到全部 {targets.length} 台）</Typography.Text>
            <div style={{ display: 'flex', gap: 8 }}>
              <Input value={username} onChange={setUsername} placeholder="agi" style={{ width: 100 }} />
              <Input mode="password" value={password} onChange={setPassword} placeholder="SSH 密码" />
            </div>
          </div>
          <div>
            <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginBottom: 6 }}>
              目标机器（当前版本 → 目标版本）
            </Typography.Text>
            {targets.map((t) => {
              const cur = t.summary?.version || t.agent_version || '?'
              return (
                <div key={t.id} style={{ display: 'flex', alignItems: 'center', gap: 8, padding: '4px 0', fontSize: 13 }}>
                  <b>{t.name}</b>
                  <code style={{ fontSize: 11 }}>{t.last_ip}</code>
                  <div style={{ flex: 1 }} />
                  <Typography.Text type="tertiary" size="small">
                    v{cur}{debPath ? ` → ${wantVer() ? 'v' + wantVer() : '?'}` : ''}
                  </Typography.Text>
                </div>
              )
            })}
          </div>
        </div>
      )}
    </Modal>
  )
}
