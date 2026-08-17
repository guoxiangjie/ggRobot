/** 主题（暗/亮）— localStorage 持久化，同步到 <html data-theme> 供 CSS 变量切换 */

import { defineStore } from 'pinia'
import { ref, watch } from 'vue'

const KEY = 'ggrobot-theme'
export type ThemeMode = 'dark' | 'light'

export const useThemeStore = defineStore('theme', () => {
  const mode = ref<ThemeMode>((localStorage.getItem(KEY) as ThemeMode) || 'dark')

  function apply(m: ThemeMode) {
    document.documentElement.setAttribute('data-theme', m)
  }

  // 持久化 + 同步到 <html data-theme>（immediate: store 首次创建即应用，避免刷新闪烁）
  watch(mode, (m) => {
    localStorage.setItem(KEY, m)
    apply(m)
  }, { immediate: true })

  function toggle() {
    mode.value = mode.value === 'dark' ? 'light' : 'dark'
  }

  return { mode, toggle }
})
