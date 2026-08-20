import { useEffect } from 'react'
import { Routes, Route, useNavigate, useLocation } from 'react-router-dom'
import { Toast } from '@douyinfe/semi-ui'
import { LayoutDashboard, Cpu, Bot, Clapperboard, Plus, Settings } from 'lucide-react'
import { useAppStore } from '@/stores/app'
import { startHub } from '@/stores/robots'
import { useUiStore } from '@/stores/ui'
import Overview from '@/pages/Overview'
import RobotList from '@/pages/RobotList'
import RobotPage from '@/pages/RobotPage'
import ChoreoPage from '@/pages/Choreo'
import AddRobotModal from '@/pages/AddRobot'
import RobotLayout from '@/pages/robot/RobotLayout'
import DashboardTab from '@/pages/robot/DashboardTab'
import ControlTab from '@/pages/robot/ControlTab'
import CameraTab from '@/pages/robot/CameraTab'
import VoiceTab from '@/pages/robot/VoiceTab'
import EmojiTab from '@/pages/robot/EmojiTab'
import MediaTab from '@/pages/robot/MediaTab'
import LinkcraftTab from '@/pages/robot/LinkcraftTab'
import SystemTab from '@/pages/robot/SystemTab'

function Sidebar(): JSX.Element {
  const nav = useNavigate()
  const setAddOpen = useUiStore((s) => s.setAddOpen)
  const { pathname } = useLocation()
  const items = [
    { icon: LayoutDashboard, path: '/', label: '总览' },
    { icon: Bot, path: '/robot', label: '机器人' },
    { icon: Clapperboard, path: '/choreo', label: '编排' },
    { icon: Cpu, path: '/robots', label: '设备' },
  ]
  // 精确匹配根路径；其余按段前缀（/robot 匹配 /robot/xxx，但不匹配 /robots）
  const isActive = (path: string): boolean =>
    path === '/' ? pathname === '/' : pathname === path || pathname.startsWith(path + '/')
  return (
    <div className="sidebar">
      {items.map(({ icon: Icon, path, label }) => (
        <div
          key={label}
          className={`nav-item${isActive(path) ? ' active' : ''}`}
          onClick={() => nav(path)}
        >
          <Icon size={22} strokeWidth={1.8} />
          <span className="nav-label">{label}</span>
        </div>
      ))}
      <div style={{ flex: 1 }} />
      <div className="nav-item" onClick={() => setAddOpen(true)}>
        <Plus size={22} strokeWidth={1.8} />
        <span className="nav-label">添加</span>
      </div>
      <div className="nav-item" style={{ opacity: 0.35 }}>
        <Settings size={22} strokeWidth={1.8} />
        <span className="nav-label">设置</span>
      </div>
    </div>
  )
}

export default function App(): JSX.Element {
  const init = useAppStore((s) => s.init)
  useEffect(() => { void init() }, [init])

  // Toast 全局配置：
  // - top 挪到自绘标题栏（48px drag 区）之下——drag 区截获其矩形内所有点击
  // - stack 堆叠（hover 展开，多条并列不干扰；源码 mergedOpts 合并 config，类型漏标故断言）
  useEffect(() => {
    Toast.config({ duration: 2, top: 56, stack: true } as never)
  }, [])
  useEffect(() => startHub(), [])   // hub 订阅全局一份（总览共用）

  return (
    <div style={{ height: '100%', display: 'flex' }}>
      {/* 侧栏全高（顶到窗口顶，红绿灯落在其上方区域） */}
      <Sidebar />
      <div style={{ flex: 1, display: 'flex', flexDirection: 'column', overflow: 'hidden' }}>
        <div className="titlebar">
          <span className="title">机器人集群控制系统</span>
        </div>
        <div className="content">
          <AddRobotModal />
          <Routes>
            <Route path="/" element={<Overview />} />
            <Route path="/robots" element={<RobotList />} />
            <Route path="/choreo" element={<ChoreoPage />} />
            <Route path="/robot" element={<RobotPage />}>
              <Route path=":id" element={<RobotLayout />}>
                <Route index element={<DashboardTab />} />
                <Route path="dashboard" element={<DashboardTab />} />
                <Route path="control" element={<ControlTab />} />
                <Route path="camera" element={<CameraTab />} />
                <Route path="voice" element={<VoiceTab />} />
                <Route path="emoji" element={<EmojiTab />} />
                <Route path="media" element={<MediaTab />} />
                <Route path="linkcraft" element={<LinkcraftTab />} />
                <Route path="system" element={<SystemTab />} />
              </Route>
            </Route>
          </Routes>
        </div>
      </div>
    </div>
  )
}
