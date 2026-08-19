import { useEffect, useState } from 'react'
import { Routes, Route, useNavigate, useLocation } from 'react-router-dom'
import { LayoutDashboard, Bot, Plus, Settings, OctagonX } from 'lucide-react'
import { Toast } from '@douyinfe/semi-ui'
import { useAppStore } from '@/stores/app'
import { useRobotsStore, startHub } from '@/stores/robots'
import { platformApi } from '@/api/platform'
import Overview from '@/pages/Overview'
import RobotList from '@/pages/RobotList'
import AddRobot from '@/pages/AddRobot'
import RobotLayout from '@/pages/robot/RobotLayout'
import DashboardTab from '@/pages/robot/DashboardTab'
import ControlTab from '@/pages/robot/ControlTab'
import CameraTab from '@/pages/robot/CameraTab'

function Sidebar(): JSX.Element {
  const nav = useNavigate()
  const { pathname } = useLocation()
  const items = [
    { icon: LayoutDashboard, path: '/', label: '总览' },
    { icon: Bot, path: '/robots', label: '机器人' },
  ]
  return (
    <div className="sidebar">
      {items.map(({ icon: Icon, path, label }) => (
        <div
          key={label}
          className={`nav-item${pathname === path ? ' active' : ''}`}
          title={label}
          onClick={() => nav(path)}
        >
          <Icon size={20} strokeWidth={1.8} />
        </div>
      ))}
      <div style={{ flex: 1 }} />
      <div className="nav-item" title="添加机器人" onClick={() => nav('/robots/add')}>
        <Plus size={20} strokeWidth={1.8} />
      </div>
      <div className="nav-item" title="设置（2.0.2+）" style={{ opacity: 0.35 }}>
        <Settings size={20} strokeWidth={1.8} />
      </div>
    </div>
  )
}

/**全局急停 — 对所有在线机器人并发零速度（平台聚合，token 不出后端） */
function EstopButton(): JSX.Element {
  const [busy, setBusy] = useState(false)
  const online = useRobotsStore((s) => s.summaries.filter((r) => r.online).length)
  return (
    <button
      className="estop-btn"
      disabled={busy}
      title={`全部停止（${online} 台在线）`}
      style={{ opacity: online === 0 ? 0.4 : 1 }}
      onClick={async () => {
        setBusy(true)
        try {
          const { data } = await platformApi().post('/api/estop', null, { timeout: 5000 })
          if (data.stopped.length > 0) Toast.success(`已停止 ${data.stopped.length} 台`)
          else if (data.total === 0) Toast.info('没有在线机器人')
          else Toast.warning('部分机器人未响应')
        } catch {
          Toast.error('急停指令发送失败')
        }
        setBusy(false)
      }}
    >
      <OctagonX size={13} /> 全部停止
    </button>
  )
}

export default function App(): JSX.Element {
  const init = useAppStore((s) => s.init)
  useEffect(() => { void init() }, [init])
  useEffect(() => startHub(), [])   // hub 订阅全局一份（总览/急停共用）

  return (
    <div style={{ height: '100%', display: 'flex', flexDirection: 'column' }}>
      <div className="titlebar">
        <span className="title">GG ROBOT</span>
        <div className="spacer" />
        <EstopButton />
      </div>
      <div style={{ flex: 1, display: 'flex', overflow: 'hidden' }}>
        <Sidebar />
        <div className="content">
          <Routes>
            <Route path="/" element={<Overview />} />
            <Route path="/robots" element={<RobotList />} />
            <Route path="/robots/add" element={<AddRobot />} />
            <Route path="/robot/:id" element={<RobotLayout />}>
              <Route index element={<DashboardTab />} />
              <Route path="dashboard" element={<DashboardTab />} />
              <Route path="control" element={<ControlTab />} />
              <Route path="camera" element={<CameraTab />} />
            </Route>
          </Routes>
        </div>
      </div>
    </div>
  )
}
