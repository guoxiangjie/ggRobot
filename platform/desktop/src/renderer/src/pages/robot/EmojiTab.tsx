/**表情页 — 能力契约 expression.face 的 21 项表情网格（播放一次/循环）*/

import { useEffect, useRef, useState } from 'react'
import { Card, Button, Tag, Typography } from '@douyinfe/semi-ui'
import { Smile } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from './RobotLayout'

interface Emotion { id: number; name: string }

export default function EmojiTab(): JSX.Element {
  const { ip, token, capsOf } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current
  const emotions = ((capsOf('expression.face')?.params.emotions ?? []) as Emotion[])
  const [mode, setMode] = useState<1 | 2>(1)
  const [playing, setPlaying] = useState<number | null>(null)

  useEffect(() => {
    if (emotions.length === 0) return   // 离线时静默
  }, [emotions.length])

  async function play(e: Emotion): Promise<void> {
    setPlaying(e.id)
    try {
      await http.post('/api/emoji', { emotion_id: e.id, mode })
      toast.success(`播放：${e.name}`)
    } catch { toast.error('播放失败') } finally { setPlaying(null) }
  }

  return (
    <Card title={<span><Smile size={15} style={{ verticalAlign: -2, marginRight: 6 }} />面部表情（{emotions.length}）</span>}
      headerExtraContent={
        <div style={{ display: 'flex', gap: 6 }}>
          {([1, 2] as const).map((m) => (
            <Tag key={m} size="small" shape="circle" type={mode === m ? 'solid' : 'ghost'}
              style={{ cursor: 'pointer' }} onClick={() => setMode(m)}>
              {m === 1 ? '播放一次' : '循环'}
            </Tag>
          ))}
        </div>
      }
    >
      {emotions.length > 0 ? (
        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(96px, 1fr))', gap: 8 }}>
          {emotions.map((e) => (
            <Button key={e.id} loading={playing === e.id} style={{ borderRadius: 8 }}
              onClick={() => void play(e)}>
              {e.name}
            </Button>
          ))}
        </div>
      ) : (
        <Typography.Text type="tertiary">机器人离线或未上报表情清单</Typography.Text>
      )}
    </Card>
  )
}
