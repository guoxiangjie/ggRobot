/**全局机器人状态 — hub 订阅上移到 App 层，急停/总览共用*/

import { create } from 'zustand'
import { hubWs, type RobotSummary } from '@/api/platform'

interface RobotsState {
  summaries: RobotSummary[]
  hubConnected: boolean
}

export const useRobotsStore = create<RobotsState>(() => ({
  summaries: [],
  hubConnected: false,
}))

/**启动 hub 订阅（App 挂载时调用一次），返回退订函数 */
export function startHub(): () => void {
  return hubWs((robots) => {
    useRobotsStore.setState({ summaries: robots, hubConnected: true })
  })
}
