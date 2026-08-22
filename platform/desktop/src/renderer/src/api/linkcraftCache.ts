/**灵创资源清单缓存 — stale-while-revalidate
   灵创清单拉取慢（agent 走跨板 service，8-15s），每次打开弹窗都拉会卡顿：
   内存 Map（会话内秒开）+ localStorage 按设备持久化（跨启动秒开），
   每次打开后台静默刷新——成功更新缓存，失败继续用缓存。
   清单只在机器人装新动作时才变，不做 TTL 强失效。 */

import { makeAgentClient } from '@/api/agent'
import { platformApi } from '@/api/platform'

export interface LinkcraftItem { resource_key: string; name: string; version: string }

interface CacheEntry { ts: number; items: LinkcraftItem[] }

const mem = new Map<string, CacheEntry>()
const lsKey = (rid: string): string => `gg-linkcraft-${rid}`

function readEntry(robotId: string): CacheEntry | null {
  const m = mem.get(robotId)
  if (m) return m
  try {
    const raw = localStorage.getItem(lsKey(robotId))
    if (raw) {
      const e = JSON.parse(raw) as CacheEntry
      if (Array.isArray(e.items)) { mem.set(robotId, e); return e }
    }
  } catch { /* 损坏当无缓存 */ }
  return null
}

/**缓存项（立即返回，不触发网络） */
export function cachedLinkcraft(robotId: string): LinkcraftItem[] {
  return readEntry(robotId)?.items ?? []
}

/**缓存时间（显示"缓存 · HH:mm"用）；无缓存返回 0 */
export function cachedLinkcraftAt(robotId: string): number {
  return readEntry(robotId)?.ts ?? 0
}

function write(robotId: string, items: LinkcraftItem[]): void {
  const e = { ts: Date.now(), items }
  mem.set(robotId, e)
  try { localStorage.setItem(lsKey(robotId), JSON.stringify(e)) } catch { /* 满 */ }
}

/**后台拉最新（直连 agent /api/resources）；成功写缓存返回清单，失败返回 null（调用方继续用缓存） */
export async function refreshLinkcraft(robotId: string, conn?: { ip: string; token: string }): Promise<LinkcraftItem[] | null> {
  try {
    const c = conn ?? await (async () => {
      const { data: rb } = await platformApi().get(`/api/robots/${robotId}`)
      if (!rb.last_ip) return null
      return { ip: rb.last_ip, token: rb.token }
    })()
    if (!c) return null
    const { data } = await makeAgentClient(c.ip, c.token).get('/api/resources', { timeout: 15000 })
    // 响应结构 {ok, resources: [...]} —— 资源在 .resources 字段（FreePlay 曾踩坑）
    const items: LinkcraftItem[] = Array.isArray(data?.resources) ? data.resources : []
    if (!items.length) return null
    write(robotId, items)
    return items
  } catch {
    return null
  }
}
