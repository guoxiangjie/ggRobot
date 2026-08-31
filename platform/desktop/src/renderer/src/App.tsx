import { useEffect } from 'react'
import { Routes, Route, useNavigate, useLocation } from 'react-router-dom'
import { Toast } from '@douyinfe/semi-ui'
import { LayoutDashboard, Cpu, Bot, Clapperboard, Zap, Map, Boxes, FlaskConical, Plug, Plus, Settings, Sun, Moon, Joystick } from 'lucide-react'
import { useAppStore } from '@/stores/app'
import logoUrl from '@/assets/logo.png'
import { startHub } from '@/stores/robots'
import { useThemeStore } from '@/stores/theme'
import Overview from '@/pages/Overview'
import RobotList from '@/pages/RobotList'
import RobotPage from '@/pages/RobotPage'
import FreePlayPage from '@/pages/FreePlay'
import ChoreoPage from '@/pages/Choreo'
import MapsPage from '@/pages/Maps'
import HallPage from '@/pages/Hall'
import LabPage from '@/pages/Lab'
import ThirdPartyPage from '@/pages/ThirdParty'
import QuickCtrlPage from '@/pages/QuickCtrl'
import MappingStudioPage from '@/pages/MappingStudio'
import SettingsPage from '@/pages/Settings'
import ChoreoEditPage from '@/pages/ChoreoEdit'
import AddRobotPage from '@/pages/AddRobot'
import RobotLayout from '@/pages/robot/RobotLayout'
import DashboardTab from '@/pages/robot/DashboardTab'
import NavTab from '@/pages/robot/a3/NavTab'
import ControlTab from '@/pages/robot/ControlTab'
import CameraTab from '@/pages/robot/CameraTab'
import VoiceTab from '@/pages/robot/VoiceTab'
import EmojiTab from '@/pages/robot/EmojiTab'
import MediaTab from '@/pages/robot/MediaTab'
import LinkcraftTab from '@/pages/robot/LinkcraftTab'
import SystemTab from '@/pages/robot/SystemTab'

function Sidebar(): JSX.Element {
  const nav = useNavigate()
  const { pathname } = useLocation()
  const items = [
    { icon: LayoutDashboard, path: '/', label: '总览' },
    { icon: Bot, path: '/robot', label: '机器人' },
    { icon: Zap, path: '/free', label: '自由' },
    { icon: Clapperboard, path: '/choreo', label: '编排' },
    { icon: Map, path: '/maps', label: '地图' },
    { icon: Boxes, path: '/hall', label: '展馆' },
    { icon: FlaskConical, path: '/lab', label: '实验室' },
    { icon: Plug, path: '/third', label: '三方' },
    { icon: Cpu, path: '/robots', label: '设备' },
  ]
  // 精确匹配根路径；其余按段前缀（/robot 匹配 /robot/xxx，但不匹配 /robots）
  const isActive = (path: string): boolean =>
    path === '/' ? pathname === '/' : pathname === path || pathname.startsWith(path + '/')
  return (
    <div className="sidebar">
      {/* 上块：主导航（占主空间，内容垂直居中） */}
      <div className="nav-group top">
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
      </div>
      {/* 底块：操作（添加 + 设置） */}
      <div className="nav-group">
        <div className="nav-item" onClick={() => void window.desktop?.openAddRobot()}>
          <Plus size={22} strokeWidth={1.8} />
          <span className="nav-label">添加</span>
        </div>
        <div className={`nav-item${pathname === '/settings' ? ' active' : ''}`} onClick={() => nav('/settings')}>
          <Settings size={22} strokeWidth={1.8} />
          <span className="nav-label">设置</span>
        </div>
      </div>
    </div>
  )
}

/**标题栏右侧主题切换 — 共享 useThemeStore（与设置页三态联动） */
function ThemeToggle(): JSX.Element {
  const { resolved, setMode } = useThemeStore()
  const dark = resolved === 'dark'
  return (
    <div className="titlebar-btn" onClick={() => setMode(dark ? 'light' : 'dark')}
      title={dark ? '切换到日间模式' : '切换到夜间模式'}>
      {dark ? <Sun size={16} strokeWidth={1.8} /> : <Moon size={16} strokeWidth={1.8} />}
    </div>
  )
}

export default function App(): JSX.Element {
  const init = useAppStore((s) => s.init)
  useEffect(() => { void init() }, [init])

  // Toast 全局配置：
  // - top 挪到自绘标题栏（54px drag 区）之下——drag 区截获其矩形内所有点击
  // - stack 堆叠（hover 展开，多条并列不干扰；源码 mergedOpts 合并 config，类型漏标故断言）
  useEffect(() => {
    Toast.config({ duration: 2, top: 62, stack: true } as never)
  }, [])
  useEffect(() => startHub(), [])   // hub 订阅全局一份（总览共用）

  // 向导/编排编辑独立窗口（#/add-robot、#/choreo-edit）：无主壳（侧栏/标题栏），纯页面
  const { pathname } = useLocation()
  if (pathname === '/add-robot') return <AddRobotPage />
  if (pathname === '/choreo-edit') return <ChoreoEditPage />
  if (pathname === '/quick-ctrl') return <QuickCtrlPage />
  if (pathname === '/mapping-studio') return <MappingStudioPage />

  return (
    <div style={{ height: '100%', display: 'flex' }}>
      {/* 侧栏全高（顶到窗口顶，红绿灯落在其上方区域） */}
      <Sidebar />
      <div style={{ flex: 1, display: 'flex', flexDirection: 'column', overflow: 'hidden' }}>
        <div className="titlebar">
          <img src={logoUrl} alt="logo" style={{ height: 22, width: 'auto' }} />
          <span className="title">机器人集群控制系统</span>
          <div className="spacer" />
          <div className="titlebar-btn" title="快捷遥控"
            onClick={() => void window.desktop?.openQuickCtrl()}>
            <Joystick size={16} strokeWidth={1.8} />
          </div>
          <ThemeToggle />
        </div>
        <div className="content">
          <Routes>
            <Route path="/" element={<Overview />} />
            <Route path="/robots" element={<RobotList />} />
            <Route path="/free" element={<FreePlayPage />} />
            <Route path="/choreo" element={<ChoreoPage />} />
            <Route path="/maps" element={<MapsPage />} />
            <Route path="/hall" element={<HallPage />} />
            <Route path="/lab" element={<LabPage />} />
            <Route path="/third" element={<ThirdPartyPage />} />
            <Route path="/settings" element={<SettingsPage />} />
            <Route path="/robot" element={<RobotPage />}>
              <Route path=":id" element={<RobotLayout />}>
                <Route index element={<DashboardTab />} />
                <Route path="dashboard" element={<DashboardTab />} />
          <Route path="nav" element={<NavTab />} />
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
