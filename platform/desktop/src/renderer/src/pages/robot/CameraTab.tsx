/**相机页 — WS 订阅 cam.* 二进制帧（4B ts + JPEG → Blob → objectURL，换帧 revoke）+ 相机切换*/

import { useEffect, useRef, useState } from 'react'
import { Card, Tag, Button } from '@douyinfe/semi-ui'
import { Camera as CamIcon, CameraIcon } from 'lucide-react'
import { AgentWsClient } from '@/api/agentWs'
import { agentWsUrl, makeAgentClient } from '@/api/agent'
import { useRobot } from './RobotLayout'
import { toast } from '@/api/toast'

interface CamItem { id: string; label: string; topic: string; active?: boolean; selected?: boolean }

export default function CameraTab(): JSX.Element {
  const { ip, token, name, capsOf } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const contractCams = ((capsOf('perception.camera')?.params.cameras ?? []) as CamItem[])
  const [cams, setCams] = useState<CamItem[]>(contractCams)
  const [selected, setSelected] = useState<string>(
    contractCams.find((c) => c.active)?.id ?? contractCams[0]?.id ?? '')
  const [imgUrl, setImgUrl] = useState('')
  const [fps, setFps] = useState(0)
  const urlRef = useRef('')
  const lastBlobRef = useRef<Blob | null>(null)

  // 实时相机列表（agent 权威）
  useEffect(() => {
    void http.get('/api/cameras').then(({ data }) => {
      const list = (data.cameras ?? []) as CamItem[]
      if (list.length > 0) {
        setCams(list)
        const act = list.find((c) => c.active) ?? list.find((c) => c.selected)
        if (act) setSelected((s) => s || act.id)
      }
    }).catch(() => { /* 离线 */ })
  }, [http])

  // WS 帧流
  const frameCount = useRef(0)
  useEffect(() => {
    const c = new AgentWsClient(agentWsUrl(ip, token), {
      onFrame: (blob) => {
        lastBlobRef.current = blob
        const url = URL.createObjectURL(blob)
        if (urlRef.current) URL.revokeObjectURL(urlRef.current)   // 换帧 revoke 防泄漏
        urlRef.current = url
        setImgUrl(url)
        frameCount.current++
      },
    })
    c.connect()
    c.sub(['cam.*'])
    const fpsTimer = window.setInterval(() => {
      setFps(frameCount.current * 10)
      frameCount.current = 0
    }, 1000)
    return () => {
      clearInterval(fpsTimer)
      c.close()
      if (urlRef.current) URL.revokeObjectURL(urlRef.current)
    }
  }, [ip, token])

  /**拍照：当前帧存为 JPEG（路径在设置-通用可自定义，默认 ~/Pictures/ggRobot） */
  async function snapshot(): Promise<void> {
    const blob = lastBlobRef.current
    if (!blob) { toast.warning('还没有画面'); return }
    try {
      const buf = await blob.arrayBuffer()
      const cam = cams.find((c) => c.id === selected)
      const full = await window.desktop.savePhoto(buf, `${name}_${cam?.id || 'cam'}`)
      toast.success(`已保存：${full}`, 5)
    } catch { toast.error('拍照失败') }
  }

  async function switchCam(id: string): Promise<void> {
    setSelected(id)
    setImgUrl('')   // 切换清帧
    try {
      await http.post('/api/camera/switch', { camera_id: id })
    } catch { /* */ }
  }

  return (
    <Card
      title={<span><CamIcon size={15} style={{ verticalAlign: -2, marginRight: 6 }} />相机流</span>}
      headerExtraContent={
        <div style={{ display: 'flex', alignItems: 'center', gap: 6 }}>
          <Button size="small" icon={<CameraIcon size={13} />} disabled={!imgUrl}
            onClick={() => void snapshot()}>拍照</Button>
          {fps > 0 && <Tag size="small" color="green" shape="circle">{fps} fps</Tag>}
          {cams.map((c) => (
            <Button key={c.id} size="small" theme={c.id === selected ? 'solid' : 'borderless'}
              onClick={() => void switchCam(c.id)}>{c.label}</Button>
          ))}
        </div>
      }
    >
      <div style={{
        aspectRatio: '16 / 9', background: '#000', borderRadius: 10, overflow: 'hidden',
        display: 'flex', alignItems: 'center', justifyContent: 'center', position: 'relative',
      }}>
        {imgUrl ? (
          <img src={imgUrl} alt="camera" style={{ maxWidth: '100%', maxHeight: '100%', display: 'block' }} />
        ) : (
          <span style={{ color: 'var(--semi-color-text-2)', fontSize: 13 }}>
            等待画面…（需先在机器人上切换到该相机）
          </span>
        )}
      </div>
    </Card>
  )
}
