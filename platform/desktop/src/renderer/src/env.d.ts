import type { DesktopApi } from '../../preload/index'

declare global {
  interface Window {
    desktop: DesktopApi
  }
}

export {}
