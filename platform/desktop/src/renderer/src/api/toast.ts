/**Toast 统一出口 — 全局 stack 堆叠（hover 展开）+ 避开标题栏 drag 区
   Semi 的全局 Toast.config 在容器已创建后不会重读 stack（源码 L110 分支依赖
   单条 opts），因此在此包装并给每条显式传 stack，确保堆叠必生效。 */

import { Toast } from '@douyinfe/semi-ui'

interface ToastOpts {
  content: React.ReactNode
  duration?: number
  id?: string
  showClose?: boolean
  icon?: React.ReactNode
}

/** 基础调用：注入 stack/位置（top 62 = 自绘标题栏下方，drag 区截获点击） */
function call(method: 'success' | 'error' | 'warning' | 'info', o: ToastOpts): void {
  Toast[method]({
    ...o,
    duration: o.duration ?? 2,
    stack: true,
    top: 62,
  } as never)
}

export const toast = {
  success: (content: React.ReactNode, duration?: number) => call('success', { content, duration }),
  error: (content: React.ReactNode, duration?: number) => call('error', { content, duration }),
  warning: (content: React.ReactNode, duration?: number) => call('warning', { content, duration }),
  info: (content: React.ReactNode, duration?: number) => call('info', { content, duration }),
}
