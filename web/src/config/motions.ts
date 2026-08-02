/** 预设动作权威清单 — 来源 AimSDK 文档 tbl-preset-motion（v0.8.0+）

只有下面这些 (motion, area) 组合在实机上有效；其他组合会被静默忽略（"不能用"的根因）。
⚠️ 所有预设动作必须在 STAND_DEFAULT（稳定站立）模式下执行，否则不动。
area 编码：1=左臂 2=右臂 3=双臂 11=全身；4=头部(4001/4002 点头/摇头，SDK枚举有但文档tbl未列、待实机验证)。
interrupt：node._do_motion 默认 True（文档 5.1.4 建议，打断当前动作，连续触发更可靠）；step.interrupt 可覆盖。
*/
export interface MotionCombo { motion: number; area: number; name: string }

export const MOTION_LIST: MotionCombo[] = [
  // ── 手臂动作（area 1/2/3）──
  { motion: 1002, area: 2, name: '右手挥手' },
  { motion: 1002, area: 1, name: '左手挥手' },
  { motion: 1001, area: 2, name: '右手举手' },
  { motion: 1001, area: 1, name: '左手举手' },
  { motion: 1003, area: 2, name: '右手握手' },
  { motion: 1003, area: 1, name: '左手握手' },
  { motion: 1004, area: 2, name: '右手飞吻' },
  { motion: 1004, area: 1, name: '左手飞吻' },
  { motion: 1007, area: 3, name: '双手比心' },
  { motion: 1007, area: 2, name: '右手比心' },
  { motion: 1007, area: 1, name: '左手比心' },
  { motion: 1008, area: 2, name: '右手击掌' },
  { motion: 1008, area: 1, name: '左手击掌' },
  { motion: 1010, area: 3, name: '双手平举' },
  { motion: 1010, area: 2, name: '右手平举' },
  { motion: 1010, area: 1, name: '左手平举' },
  { motion: 1011, area: 2, name: '胸前右手挥手' },
  { motion: 1011, area: 1, name: '胸前左手挥手' },
  { motion: 1013, area: 2, name: '右手敬礼' },
  { motion: 1013, area: 1, name: '左手敬礼' },
  // ── 全身动作（area 11）──
  { motion: 3017, area: 11, name: '鼓掌' },
  { motion: 3031, area: 11, name: '拜拜' },
  { motion: 3001, area: 11, name: '鞠躬' },
  { motion: 3007, area: 11, name: '动感光波' },
  { motion: 3008, area: 11, name: '拥抱' },
  { motion: 3009, area: 11, name: '双手打叉' },
  { motion: 3011, area: 11, name: '加油' },
  { motion: 3024, area: 11, name: '挠头' },
  { motion: 3025, area: 11, name: '抓屁股' },
  // ── 头部动作（area 4；SDK 枚举有 4001/4002 但文档 tbl 未列，待实机验证）──
  { motion: 4001, area: 4, name: '点头' },
  { motion: 4002, area: 4, name: '摇头' },
]

export const AREA_LABEL: Record<number, string> = { 1: '左臂', 2: '右臂', 3: '双臂', 11: '全身' }

/** NSelect 选项：value 用 "motion:area" 复合键，确保选中的是合法组合 */
export const MOTION_OPTIONS = MOTION_LIST.map(m => ({ label: m.name, value: `${m.motion}:${m.area}` }))

export function motionKey(motion: number, area: number): string {
  return `${motion}:${area}`
}
export function motionLabel(motion: number, area: number): string {
  return MOTION_LIST.find(m => m.motion === motion && m.area === area)?.name || `动作#${motion}`
}
export function parseMotionKey(key: string): { motion: number; area: number } {
  const [motion, area] = String(key).split(':').map(Number)
  return { motion: motion || 0, area: area || 0 }
}
