/**主题三态（auto/light/dark）— 标题栏按钮与设置页共享的唯一真源
   auto = 跟随系统（renderer 媒体查询，零 IPC）；localStorage('gg-theme') 持久化。
   模块加载即应用（main.tsx 顶部 import，首帧正确无闪白）。 */

import { create } from 'zustand'

export type ThemeMode = 'auto' | 'light' | 'dark'
const KEY = 'gg-theme'

function systemDark(): boolean {
  return window.matchMedia('(prefers-color-scheme: dark)').matches
}
function resolve(mode: ThemeMode): 'light' | 'dark' {
  if (mode === 'auto') return systemDark() ? 'dark' : 'light'
  return mode
}
function apply(res: 'light' | 'dark'): void {
  document.body.setAttribute('theme-mode', res)
  document.documentElement.style.background = res === 'dark' ? '#17171a' : '#ffffff'
}

interface ThemeState {
  mode: ThemeMode
  resolved: 'light' | 'dark'
  setMode: (m: ThemeMode) => void
}

export const useThemeStore = create<ThemeState>((set) => ({
  mode: 'light',
  resolved: 'light',
  setMode: (mode) => {
    const resolved = resolve(mode)
    localStorage.setItem(KEY, mode)
    apply(resolved)
    set({ mode, resolved })
  },
}))

// ── 初始化（模块加载即执行）──
const initMode = ((localStorage.getItem(KEY) as ThemeMode | null) ?? 'light')
const initResolved = resolve(initMode)
apply(initResolved)
useThemeStore.setState({ mode: initMode, resolved: initResolved })

// auto 模式跟随系统切换
window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', () => {
  const { mode } = useThemeStore.getState()
  if (mode !== 'auto') return
  const r = resolve('auto')
  apply(r)
  useThemeStore.setState({ resolved: r })
})
