/**机器人页 — 主从布局：左侧设备列表（紧凑行），右侧选中设备详情（tab）*/

import { useEffect } from 'react'
import { useParams, useNavigate, Outlet } from 'react-router-dom'
import { Bot, Wifi, WifiOff } from 'lucide-react'
import { useRobotsStore } from '@/stores/robots'
import { EmptyBox } from '@/components/StateViews'

export default function RobotPage(): JSX.Element {
  const { id } = useParams<{ id: string }>()
  const nav = useNavigate()
  const { summaries: robots } = useRobotsStore()

  // 无选中且有机器人 → 自动选第一个
  useEffect(() => {
    if (!id && robots.length > 0) nav(`/robot/${robots[0].id}/dashboard`, { replace: true })
  }, [id, robots, nav])

  return (
    <div style={{ display: 'flex', gap: 16, height: '100%', overflow: 'hidden', padding: 16 }}>
      {/* 左侧：设备列表（紧凑行，选中底色高亮） */}
      <div style={{ width: 200, flexShrink: 0, overflow: 'auto', display: 'flex', flexDirection: 'column', gap: 2 }}>
        {robots.length === 0 ? (
          <EmptyBox title="无设备" description="通过装机向导接入第一台" />
        ) : (
          robots.map((r) => {
            const selected = r.id === id
            return (
              <div key={r.id} onClick={() => nav(`/robot/${r.id}/dashboard`)}
                style={{
                  padding: '8px 10px', borderRadius: 8, cursor: 'pointer',
                  background: selected ? 'var(--semi-color-primary-light-default)' : 'transparent',
                }}>
                <div style={{ display: 'flex', alignItems: 'center', gap: 8 }}>
                  <div style={{
                    width: 28, height: 28, borderRadius: 6, display: 'flex', flexShrink: 0,
                    alignItems: 'center', justifyContent: 'center',
                    background: r.online ? 'var(--semi-color-primary-light-default)' : 'var(--semi-color-fill-1)',
                  }}>
                    <Bot size={14} color={r.online ? 'var(--semi-color-primary)' : 'var(--semi-color-text-2)'} />
                  </div>
                  <div style={{ flex: 1, minWidth: 0 }}>
                    <div style={{
                      fontWeight: 600, fontSize: 13, overflow: 'hidden',
                      textOverflow: 'ellipsis', whiteSpace: 'nowrap',
                      color: selected ? 'var(--semi-color-primary)' : 'inherit',
                    }}>
                      {r.name}
                    </div>
                    <div style={{ fontSize: 10, color: 'var(--semi-color-text-2)' }}>
                      {r.last_ip}
                      {r.battery_soc != null && ` · ${r.battery_soc}%`}
                    </div>
                  </div>
                  {r.online
                    ? <Wifi size={12} color="var(--gg-success)" />
                    : <WifiOff size={12} color="var(--semi-color-text-2)" />}
                </div>
              </div>
            )
          })
        )}
      </div>

      {/* 中缝分隔线（flex gap 16 → 线两侧各 16，正居间隙中点） */}
      <div style={{ width: 1, flexShrink: 0, background: 'color-mix(in srgb, var(--semi-color-border) 50%, transparent)' }} />

      {/* 右侧：详情（RobotLayout 的 tab 内容） */}
      <div style={{ flex: 1, overflow: 'auto', minWidth: 0, paddingBottom: 8 }}>
        <Outlet />
      </div>
    </div>
  )
}
