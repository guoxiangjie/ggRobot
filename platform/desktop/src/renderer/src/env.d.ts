/// <reference types="vite/client" />

import type { DesktopApi } from '../../preload/index'

declare global {
  // electron.vite.config.ts define 注入（package.json version）
  const __version__: string
  interface Window {
    desktop: DesktopApi
  }
}

export {}
