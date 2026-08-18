import { useEffect } from 'react'
import { Routes, Route, useNavigate, useLocation } from 'react-router-dom'
import { LayoutDashboard, Bot, Plus, Settings } from 'lucide-react'
import { useAppStore } from '@/stores/app'
import Overview from '@/pages/Overview'
import RobotList from '@/pages/RobotList'
import AddRobot from '@/pages/AddRobot'

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
      <div className="nav-item" title="设置（M5+）" style={{ opacity: 0.35 }}>
        <Settings size={20} strokeWidth={1.8} />
      </div>
    </div>
  )
}

export default function App(): JSX.Element {
  const init = useAppStore((s) => s.init)
  useEffect(() => { void init() }, [init])

  return (
    <div style={{ height: '100%', display: 'flex', flexDirection: 'column' }}>
      <div className="titlebar">
        <span className="title">GG ROBOT</span>
      </div>
      <div style={{ flex: 1, display: 'flex', overflow: 'hidden' }}>
        <Sidebar />
        <div className="content">
          <Routes>
            <Route path="/" element={<Overview />} />
            <Route path="/robots" element={<RobotList />} />
            <Route path="/robots/add" element={<AddRobot />} />
          </Routes>
        </div>
      </div>
    </div>
  )
}
