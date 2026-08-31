/**媒体库 — 上传（自动同步 PC3 脸屏）/ 列表 / 播放 / 删除
   上传直连 agent（大文件 timeout 0 + 进度）；100% 后仍有 PC3 同步阶段 */

import { useEffect, useRef, useState, useCallback } from 'react'
import { Card, Button, Table, Tag, Popconfirm, Progress, Typography } from '@douyinfe/semi-ui'
import { FolderUp, Play, Trash2, RefreshCw, FileVideo, FileAudio } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from './RobotLayout'
import { Empty } from '@douyinfe/semi-ui'

interface MediaFile { name: string; size: number; kind: 'audio' | 'video'; ext: string }

function fmtSize(bytes: number): string {
  if (bytes < 1024) return `${bytes} B`
  if (bytes < 1024 * 1024) return `${(bytes / 1024).toFixed(1)} KB`
  return `${(bytes / (1024 * 1024)).toFixed(1)} MB`
}

export default function MediaTab(): JSX.Element {
  const { isA3 } = useRobot()
  if (isA3) {
    return <Empty title="A3 机型暂不提供此功能" description="A3 表情/媒体走资源体系（v2）；灵创为 X2 专属" style={{ padding: 80 }} />
  }
  return <X2MediaTab />
}

function X2MediaTab(): JSX.Element {
  const { ip, token } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  const [files, setFiles] = useState<MediaFile[]>([])
  const [loading, setLoading] = useState(false)
  const [playing, setPlaying] = useState('')
  const [pct, setPct] = useState<number | null>(null)   // null=不在上传
  const [dragOver, setDragOver] = useState(false)
  const inputRef = useRef<HTMLInputElement>(null)

  const load = useCallback(async () => {
    setLoading(true)
    try {
      const { data } = await http.get('/api/media/list')
      setFiles(data.files ?? [])
    } catch { toast.error('列表拉取失败') }
    setLoading(false)
  }, [http])

  useEffect(() => { void load() }, [load])

  const upload = useCallback(async (file: File) => {
    const form = new FormData()
    form.append('file', file)
    setPct(0)
    try {
      const { data } = await http({
        method: 'post', url: '/api/media/upload', data: form,
        timeout: 0,   // 大文件不限时（含 PC3 同步耗时）
        onUploadProgress: (e) => {
          if (e.total) setPct(Math.round((e.loaded / e.total) * 100))
        },
      })
      if (data.ok) {
        if (data.pc3_synced === false) {
          toast.warning(`已上传 ${data.name}，但未同步到 PC3 脸屏（机器人侧 scp 失败）`, 8)
        } else {
          toast.success(`已上传并同步到脸屏：${data.name}`)
        }
        void load()
      } else {
        toast.error(data.error || '上传失败')
      }
    } catch {
      toast.error('上传失败')
    }
    setPct(null)
  }, [http, load])

  async function play(name: string): Promise<void> {
    setPlaying(name)
    try {
      const form = new FormData()
      form.append('name', name)
      const { data } = await http.post('/api/media/play', form)
      if (!data.ok) toast.warning(data.error || '播放未成功')
    } catch { toast.error('播放请求失败') }
    setPlaying('')
  }

  async function remove(name: string): Promise<void> {
    try {
      await http.delete(`/api/media/${encodeURIComponent(name)}`)
      toast.success('已删除（含 PC3）')
      void load()
    } catch { toast.error('删除失败') }
  }

  return (
    <div style={{ display: 'flex', flexDirection: 'column', gap: 16 }}>
      {/* 上传区（点击/拖拽） */}
      <Card bodyStyle={{ padding: 0 }}>
        <div
          onClick={() => inputRef.current?.click()}
          onDragOver={(e) => { e.preventDefault(); setDragOver(true) }}
          onDragLeave={() => setDragOver(false)}
          onDrop={(e) => {
            e.preventDefault(); setDragOver(false)
            const f = e.dataTransfer.files?.[0]
            if (f) void upload(f)
          }}
          style={{
            padding: '26px 0', textAlign: 'center', cursor: 'pointer',
            border: `2px dashed ${dragOver ? 'var(--semi-color-primary)' : 'var(--semi-color-border)'}`,
            borderRadius: 10, transition: 'border-color 0.15s',
            color: dragOver ? 'var(--semi-color-primary)' : 'var(--semi-color-text-2)',
          }}
        >
          <FolderUp size={26} style={{ verticalAlign: -8, marginRight: 8 }} />
          点击选择或拖拽音视频文件到此处上传
          <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 6 }}>
            支持 mp3 / wav / mp4 / avi / mov · 上传后自动同步到机器人脸屏（PC3）
          </Typography.Text>
        </div>
        <input ref={inputRef} type="file" hidden accept=".mp3,.wav,.mp4,.avi,.mov,.mkv"
          onChange={(e) => { const f = e.target.files?.[0]; if (f) void upload(f); e.target.value = '' }} />
        {pct != null && (
          <div style={{ display: 'flex', alignItems: 'center', gap: 12, padding: '10px 16px' }}>
            <Progress percent={pct} showInfo={false} style={{ flex: 1, margin: 0 }} />
            <span style={{ fontSize: 12, color: 'var(--semi-color-text-2)', minWidth: 110 }}>
              {pct < 100 ? `上传中 ${pct}%` : '同步到 PC3 脸屏…'}
            </span>
          </div>
        )}
      </Card>

      {/* 文件列表 */}
      <Card
        title={`媒体文件（${files.length}）`}
        headerExtraContent={
          <Button size="small" icon={<RefreshCw size={13} />} loading={loading} onClick={() => void load()}>
            刷新
          </Button>
        }
      >
        <Table<MediaFile>
          rowKey="name"
          dataSource={files}
          size="small"
          pagination={files.length > 12 ? { pageSize: 12 } : false}
          empty="暂无文件 — 上传第一个音视频"
          columns={[
            {
              title: '文件名', dataIndex: 'name',
              render: (v: string, r) => (
                <span style={{ display: 'inline-flex', alignItems: 'center', gap: 8 }}>
                  {r.kind === 'video'
                    ? <FileVideo size={15} color="var(--semi-color-primary)" />
                    : <FileAudio size={15} color="var(--semi-color-tertiary)" />}
                  {v}
                </span>
              ),
            },
            { title: '大小', dataIndex: 'size', width: 100, render: (v: number) => fmtSize(v) },
            {
              title: '类型', dataIndex: 'kind', width: 80,
              render: (v: string) => v === 'video'
                ? <Tag size="small" color="blue" shape="circle">视频</Tag>
                : <Tag size="small" color="orange" shape="circle">音频</Tag>,
            },
            {
              title: '', width: 110,
              render: (_v, r) => (
                <div style={{ display: 'flex', gap: 4 }}>
                  <Button size="small" theme="borderless" icon={<Play size={13} />}
                    loading={playing === r.name} onClick={() => void play(r.name)} />
                  <Popconfirm title={`删除 ${r.name}？（机器人本地与 PC3 同删）`} onConfirm={() => void remove(r.name)}>
                    <Button size="small" theme="borderless" type="danger" icon={<Trash2 size={13} />} />
                  </Popconfirm>
                </div>
              ),
            },
          ]}
        />
      </Card>
    </div>
  )
}
