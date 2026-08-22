/**设置 — 锚点联动式（左一级菜单定位 / 右连续滚动总页，IntersectionObserver 跟随高亮）
   分区：外观 / 通用 / 遥控 / Agent / 关于。设置即生效（localStorage 或 IPC kv）。 */

import { useEffect, useRef, useState } from 'react'
import {
  Radio, RadioGroup, Switch, Input, InputNumber, Button, Typography, Progress, Tag,
} from '@douyinfe/semi-ui'
import {
  Palette, Wrench, Joystick, Package, Info, FolderOpen, AudioLines, Download, Trash2,
} from 'lucide-react'
import { toast } from '@/api/toast'
import { platformApi } from '@/api/platform'
import { useThemeStore, type ThemeMode } from '@/stores/theme'
import { useAppStore } from '@/stores/app'

// localStorage 设置项读写小工具
function lsGet(key: string, def: string): string {
  return localStorage.getItem(key) ?? def
}

// ── 设置行组件（label/说明 左，控件 右）──
function Row({ title, desc, children }: {
  title: string; desc?: string; children: React.ReactNode
}): JSX.Element {
  return (
    <div className="set-row">
      <div>
        <div style={{ fontWeight: 600, fontSize: 13 }}>{title}</div>
        {desc && <Typography.Text type="tertiary" size="small">{desc}</Typography.Text>}
      </div>
      <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>{children}</div>
    </div>
  )
}

function Section({ id, title, children }: {
  id: string; title: string; children: React.ReactNode
}): JSX.Element {
  return (
    <section id={`set-${id}`} className="set-section">
      <h2 className="set-title">{title}</h2>
      {children}
    </section>
  )
}

export default function SettingsPage(): JSX.Element {
  const scrollRef = useRef<HTMLDivElement>(null)
  const [active, setActive] = useState('appearance')
  const { mode, setMode } = useThemeStore()
  const { port } = useAppStore()

  // 通用
  const [autoLaunch, setAutoLaunch] = useState(false)
  const [subnet, setSubnet] = useState(lsGet('gg-scan-subnet', '10.10.4'))
  // 遥控
  const [spd, setSpd] = useState(() => {
    try {
      const v = JSON.parse(lsGet('gg-ctrl-speed', '{}')) as Partial<{ forward: number; lateral: number; angular: number }>
      return { forward: v.forward ?? 0.35, lateral: v.lateral ?? 0.4, angular: v.angular ?? 0.6 }
    } catch { return { forward: 0.35, lateral: 0.4, angular: 0.6 } }
  })
  // Agent
  const [debDir, setDebDir] = useState('')
  const [photoDir, setPhotoDir] = useState('')
  // 语音转写
  const [sv, setSv] = useState<{ downloaded: boolean; downloading: boolean } | null>(null)
  const [svProg, setSvProg] = useState<{ progress: number; speed: string; done: boolean; error?: string } | null>(null)
  // 关于
  const [sidecarVer, setSidecarVer] = useState('')

  const SECTIONS = [
    { key: 'appearance', label: '外观', icon: Palette },
    { key: 'general', label: '通用', icon: Wrench },
    { key: 'ctrl', label: '遥控', icon: Joystick },
    { key: 'asr', label: '语音', icon: AudioLines },
    { key: 'agent', label: 'Agent', icon: Package },
    { key: 'about', label: '关于', icon: Info },
  ]

  useEffect(() => {
    void window.desktop?.getAutoLaunch().then(setAutoLaunch).catch(() => { /* */ })
    void window.desktop?.settingsGet('debDir').then(setDebDir).catch(() => { /* */ })
    void window.desktop?.settingsGet('photoDir').then(setPhotoDir).catch(() => { /* */ })
    void platformApi().get('/healthz').then(({ data }) => setSidecarVer(data.version ?? ''))
      .catch(() => { /* */ })
    void window.desktop?.asrSvStatus().then(setSv).catch(() => { /* */ })
    return window.desktop?.onAsrProgress((p) => {
      setSvProg(p)
      if (p.done && !p.error) { void window.desktop?.asrSvStatus().then(setSv); toast.success('SenseVoice 模型下载完成') }
    })
  }, [])

  // scroll spy：进入视口比例最大的 section → 左侧高亮
  useEffect(() => {
    const root = scrollRef.current
    if (!root) return
    // 当前分区 = 最后一个顶边越过参考线（视口 15%）的 —— 多分区同时触发也不跳项
    const obs = new IntersectionObserver(() => {
      let cur = SECTIONS[0].key
      for (const { key } of SECTIONS) {
        const el = document.getElementById(`set-${key}`)
        if (el && el.getBoundingClientRect().top <= window.innerHeight * 0.15 + 30) cur = key
      }
      setActive(cur)
    }, { root, rootMargin: '-15% 0px -70% 0px', threshold: 0 })
    SECTIONS.forEach(({ key }) => {
      const el = document.getElementById(`set-${key}`)
      if (el) obs.observe(el)
    })
    return () => obs.disconnect()
  }, [])

  function jump(key: string): void {
    document.getElementById(`set-${key}`)?.scrollIntoView({ behavior: 'smooth', block: 'start' })
    setActive(key)
  }

  function saveSpd(next: Partial<typeof spd>): void {
    const merged = { ...spd, ...next }
    setSpd(merged)
    localStorage.setItem('gg-ctrl-speed', JSON.stringify(merged))
  }

  return (
    <div className="settings">
      {/* 左：锚点菜单 */}
      <div className="settings-side">
        <Typography.Text type="tertiary" size="small" style={{ padding: '0 10px' }}>设置</Typography.Text>
        {SECTIONS.map(({ key, label, icon: Icon }) => (
          <div key={key} className={`hall-item${active === key ? ' sel' : ''}`} onClick={() => jump(key)}>
            <Icon size={15} />
            <span style={{ fontSize: 13 }}>{label}</span>
          </div>
        ))}
      </div>

      {/* 右：连续滚动总页 */}
      <div className="settings-main" ref={scrollRef}>
        <Section id="appearance" title="外观">
          <Row title="主题模式" desc="跟随系统时随 OS 外观自动切换">
            <RadioGroup type="button" value={mode} onChange={(e) => setMode(e.target.value as ThemeMode)}>
              <Radio value="auto">跟随系统</Radio>
              <Radio value="light">日间</Radio>
              <Radio value="dark">夜间</Radio>
            </RadioGroup>
          </Row>
        </Section>

        <Section id="general" title="通用">
          <Row title="开机自启动" desc="登录系统后自动运行客户端">
            <Switch checked={autoLaunch} onChange={(v) => {
              setAutoLaunch(v)
              void window.desktop?.setAutoLaunch(v).then(() => toast.success(v ? '已开启' : '已关闭'))
                .catch(() => { setAutoLaunch(!v); toast.error('设置失败') })
            }} />
          </Row>
          <Row title="默认扫描网段" desc="设备页「扫描网段」的默认值">
            <Input value={subnet} style={{ width: 140 }}
              onChange={(v) => { setSubnet(v); localStorage.setItem('gg-scan-subnet', v) }} />
          </Row>
          <Row title="照片存储位置" desc="相机拍照的保存目录（默认 ~/Pictures/ggRobot）">
            <Input value={photoDir} readonly style={{ width: 220 }} placeholder="默认（图片文件夹）" />
            <Button size="small" icon={<FolderOpen size={13} />} onClick={async () => {
              const d = await window.desktop?.pickDirectory(photoDir)
              if (d) {
                setPhotoDir(d)
                void window.desktop?.settingsSet('photoDir', d)
                toast.success('已保存')
              }
            }}>选择</Button>
          </Row>
        </Section>

        <Section id="ctrl" title="遥控">
          <Row title="前进速度" desc="快捷遥控的前后行进速度（m/s）">
            <InputNumber value={spd.forward} min={0.05} max={1.2} step={0.05} style={{ width: 100 }}
              onChange={(v) => saveSpd({ forward: Number(v) || 0.35 })} />
          </Row>
          <Row title="平移速度" desc="快捷遥控的左右平移速度（m/s）">
            <InputNumber value={spd.lateral} min={0.05} max={1.2} step={0.05} style={{ width: 100 }}
              onChange={(v) => saveSpd({ lateral: Number(v) || 0.4 })} />
          </Row>
          <Row title="转向速度" desc="快捷遥控的原地旋转速度（rad/s）">
            <InputNumber value={spd.angular} min={0.1} max={1.5} step={0.1} style={{ width: 100 }}
              onChange={(v) => saveSpd({ angular: Number(v) || 0.6 })} />
          </Row>
        </Section>

        <Section id="asr" title="语音转写">
          <Row title="内置转写引擎（paraformer）" desc="随安装包内置，装完即用；中文短语音离线转写">
            <Tag size="small" color="green">已内置</Tag>
          </Row>
          <Row title="高精模型（SenseVoice）" desc="识别更准 + 情感/事件检测；下载后自动作为默认档（约 230MB，一次性）">
            {sv?.downloaded
              ? <Button size="small" type="danger" theme="borderless" icon={<Trash2 size={13} />}
                  onClick={async () => {
                    await window.desktop?.asrSvDelete()
                    setSv({ downloaded: false, downloading: false })
                    toast.success('已删除高精模型')
                  }}>删除模型</Button>
              : svProg && !svProg.done
                ? <Button size="small" type="danger" theme="borderless"
                    onClick={() => void window.desktop?.asrSvCancel().then(() => toast.info('已取消'))}>取消下载</Button>
                : <Button size="small" icon={<Download size={13} />} loading={false}
                    onClick={() => { setSvProg(null); void window.desktop?.asrSvDownload() }}>下载高精模型</Button>}
          </Row>
          {svProg && !svProg.done && (
            <div style={{ marginTop: -2, marginBottom: 8, padding: '0 16px' }}>
              <Progress percent={Math.round(svProg.progress)} />
              <Typography.Text type="tertiary" size="small">{svProg.speed}</Typography.Text>
            </div>
          )}
          {svProg?.done && svProg.error && (
            <div style={{ padding: '0 16px 6px' }}>
              <Typography.Text type="danger" size="small">下载失败：{svProg.error}</Typography.Text>
            </div>
          )}
        </Section>

        <Section id="agent" title="Agent">
          <Row title="默认 deb 目录" desc="装机向导 / Agent 更新选择安装包时的起始目录（选择后自动记住）">
            <Input value={debDir} readonly style={{ width: 260 }} placeholder="未设置（从上次选择记住）" />
            <Button icon={<FolderOpen size={13} />} onClick={async () => {
              const d = await window.desktop?.pickDirectory(debDir)
              if (d) {
                setDebDir(d)
                void window.desktop?.settingsSet('debDir', d)
                toast.success('已保存')
              }
            }}>选择</Button>
          </Row>
        </Section>

        <Section id="about" title="关于">
          <Row title="客户端版本">
            <code style={{ fontSize: 12 }}>v{__version__}</code>
          </Row>
          <Row title="平台服务" desc={`sidecar @ 127.0.0.1:${port}`}>
            <code style={{ fontSize: 12 }}>{sidecarVer ? `v${sidecarVer}` : '—'}</code>
          </Row>
          <Row title="数据目录" desc="机器人登记 / 编排等数据存储位置">
            <Button size="small" icon={<FolderOpen size={13} />}
              onClick={() => void window.desktop?.openUserDataDir()}>打开</Button>
          </Row>
          <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 12 }}>
            机器人集群控制系统 —— 多机型机器人管理平台
          </Typography.Text>
        </Section>
      </div>
    </div>
  )
}
