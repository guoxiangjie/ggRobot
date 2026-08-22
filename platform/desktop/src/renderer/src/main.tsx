import ReactDOM from 'react-dom/client'
import { HashRouter } from 'react-router-dom'
// Semi 官方默认主题整包 CSS（包 exports 未映射 css 子路径，走相对路径引入）
import '../../../node_modules/@douyinfe/semi-ui/dist/css/semi.min.css'
import '@/styles/global.css'
import '@/stores/theme'   // 主题三态初始化（模块副作用：首帧应用，防闪白）
import App from './App'

// dev 环境静音 Semi 组件的 findDOMNode 弃用警告（React 开发版对每次调用都打，
// Semi 官方已知待修；只过滤这一条，其他错误照常显示）
if (import.meta.env.DEV) {
  const origError = console.error
  console.error = (...args: unknown[]) => {
    if (typeof args[0] === 'string' && args[0].includes('findDOMNode is deprecated')) return
    origError(...args)
  }
}

ReactDOM.createRoot(document.getElementById('root')!).render(
  <HashRouter>
    <App />
  </HashRouter>,
)
