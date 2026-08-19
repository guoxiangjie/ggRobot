/**状态三件套 — 加载/空态/错误 的统一呈现（全页面复用）*/

import { Spin, Empty, Button } from '@douyinfe/semi-ui'
import type { ReactNode } from 'react'

export function LoadingBox({ height = 200, tip = '加载中...' }: { height?: number; tip?: string }): JSX.Element {
  return (
    <div style={{ height, display: 'flex', flexDirection: 'column', gap: 12, alignItems: 'center', justifyContent: 'center' }}>
      <Spin size="large" />
      <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>{tip}</span>
    </div>
  )
}

export function EmptyBox({ title, description, action }: {
  title: string; description?: ReactNode; action?: ReactNode
}): JSX.Element {
  return (
    <Empty
      image={<div style={{ fontSize: 40, opacity: 0.35 }}>🤖</div>}
      title={title}
      description={description}
      style={{ padding: '48px 0' }}
    >
      {action && <div style={{ marginTop: 12 }}>{action}</div>}
    </Empty>
  )
}

export function ErrorBox({ message, onRetry }: { message: string; onRetry?: () => void }): JSX.Element {
  return (
    <div style={{
      padding: 24, borderRadius: 10, textAlign: 'center',
      background: 'var(--semi-color-danger-light-default)', color: 'var(--semi-color-danger)',
    }}>
      <div style={{ fontSize: 28, marginBottom: 8 }}>⚠️</div>
      <div style={{ fontSize: 13, marginBottom: onRetry ? 12 : 0 }}>{message}</div>
      {onRetry && <Button size="small" onClick={onRetry}>重试</Button>}
    </div>
  )
}
