/**实验室 — 实验性功能孵化区（占位）
   当前卡片仅占位：后续接入真实功能（避障行走 = agents/x2/navigation 激光避障模块的桌面端入口）。 */

import { Typography, Tag } from '@douyinfe/semi-ui'
import { Radar, ScanSearch, PersonStanding, Hand } from 'lucide-react'

const LABS = [
  {
    key: 'avoidance',
    title: '避障行走',
    desc: '激光避障安全过滤器（ROI 裁剪 + RANSAC 地面去除 + 9 扇区状态机），机器人自动前进/过滤遥控指令避障',
    icon: Radar,
  },
  {
    key: 'detection',
    title: '物体识别',
    desc: '基于相机画面的目标检测与识别（规划中）',
    icon: ScanSearch,
  },
  {
    key: 'follow',
    title: '人体跟随',
    desc: '识别前方人员并保持距离自主跟随（相机检测 + 速度闭环，迎宾导览场景）',
    icon: PersonStanding,
  },
  {
    key: 'gesture',
    title: '手势识别',
    desc: '识别挥手/比心等手势触发对应动作（手部关键点检测 → 动作映射）',
    icon: Hand,
  },
]

export default function LabPage(): JSX.Element {
  return (
    <div className="page">
      <div>
        <h1 className="page-title">实验室</h1>
        <p className="page-sub">实验性功能孵化区 —— 功能成型前先占位预告</p>
      </div>
      <div className="robot-grid" style={{ marginTop: 8 }}>
        {LABS.map((l) => (
          <div key={l.key} className="gg-card free-item" style={{ opacity: 0.75 }}>
            <div style={{ display: 'flex', alignItems: 'center', gap: 10 }}>
              <l.icon size={20} color="var(--semi-color-primary)" />
              <div style={{ fontWeight: 700, fontSize: 15 }}>{l.title}</div>
              <Tag size="small" color="grey">规划中</Tag>
            </div>
            <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 8, lineHeight: 1.6 }}>
              {l.desc}
            </Typography.Text>
          </div>
        ))}
      </div>
    </div>
  )
}
