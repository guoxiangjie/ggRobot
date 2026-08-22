/**语音页 — TTS + 音量/静音 + 麦克风 VAD/ASR（复刻 1.0 Voice 页，agent 直连）*/

import { useEffect, useRef, useState, useCallback } from 'react'
import { Card, Button, Input, Slider, Switch, Tag, Typography } from '@douyinfe/semi-ui'
import { Mic, MicOff, Volume2, Play, AudioLines, PlayCircle, ListMusic } from 'lucide-react'
import { makeAgentClient } from '@/api/agent'
import { toast } from '@/api/toast'
import { useRobot } from './RobotLayout'
import { platformApi } from '@/api/platform'

interface MicStatus {
  ok: boolean; enabled: boolean; vad_state: number; vad_label?: string
  segment_bytes: number; last_segment_ts: number; mic_source: number; text: string; recv_count: number
}

export default function VoiceTab(): JSX.Element {
  const { ip, token } = useRobot()
  const http = useRef(makeAgentClient(ip, token)).current

  // ── TTS ──
  const [text, setText] = useState('')
  const [busy, setBusy] = useState(false)
  async function speak(): Promise<void> {
    if (!text.trim()) return
    setBusy(true)
    try {
      await http.post('/api/tts', { text, domain: 'web_ui', is_interrupted: true, priority_level: 6 })
      toast.success('已播报')
    } catch { toast.error('播报失败') } finally { setBusy(false) }
  }

  // ── 音量/静音 ──
  const [volume, setVolume] = useState(50)
  const [muted, setMuted] = useState(false)
  const committed = useRef(50)   // 最近已知音量（拉取值/提交值），用于过滤挂载误触发
  useEffect(() => {
    void http.get('/api/volume').then(({ data }) => {
      const n = Number(data.volume)
      if (Number.isFinite(n)) { setVolume(n); committed.current = n }
    }).catch(() => {})
    void http.get('/api/mute').then(({ data }) => setMuted(!!data.is_mute)).catch(() => {})
  }, [http])
  // 松手提交（静默，失败才提示）；拖动过程零请求
  const applyVolume = useCallback((v: number) => {
    committed.current = v
    void http.post(`/api/volume?volume=${v}`).catch(() => toast.error('音量设置失败'))
  }, [http])

  // ── 麦克风 ──
  const [mic, setMic] = useState<MicStatus | null>(null)
  const [micOn, setMicOn] = useState(false)
  const [micSource, setMicSource] = useState<number | null>(null)
  useEffect(() => {
    const load = (): void => {
      void http.get('/api/mic').then(({ data }) => { setMic(data); setMicOn(data.enabled) })
        .catch(() => setMic(null))
    }
    load()
    const t = window.setInterval(load, 2000)
    return () => clearInterval(t)
  }, [http])
  useEffect(() => {
    void http.get('/api/mic/source').then(({ data }) => setMicSource(data.mic_source)).catch(() => {})
  }, [http])

  async function toggleMic(on: boolean): Promise<void> {
    try {
      const { data } = await http.post('/api/mic', { enable: on })
      setMicOn(data.enabled)
      toast.success(on ? '采集已开启（唤醒词激活 VAD）' : '采集已关闭')
    } catch { toast.error('操作失败') }
  }
  // ── 语音片段（VAD 段到达 → 列表 + 自动转写 + 回放）──
  interface Seg { id: number; ts: number; dur: number; b64: string; text: string; busy?: boolean }
  const [segs, setSegs] = useState<Seg[]>([])
  const lastTsRef = useRef(0)
  const segIdRef = useRef(0)

  useEffect(() => {
    if (!micOn) return
    let alive = true
    const poll = async (): Promise<void> => {
      try {
        // status 轮询已在上面的 mic interval；这里按 last_segment_ts 变化拉段
        if (!mic || !mic.last_segment_ts || mic.last_segment_ts === lastTsRef.current) return
        lastTsRef.current = mic.last_segment_ts
        const { data } = await http.get('/api/mic/audio')
        if (!alive || !data.ok || !data.data) return
        const dur = Math.max(0.1, data.size / 32000)   // 16k*2bytes
        const seg: Seg = { id: ++segIdRef.current, ts: mic.last_segment_ts, dur, b64: data.data, text: '', busy: true }
        setSegs((ls) => [seg, ...ls].slice(0, 20))
        // 自动转写（本地 sidecar；失败静默置提示）
        void platformApi().post('/api/asr/transcribe', { audio_b64: data.data, model: 'auto' }, { timeout: 30000 })
          .then(({ data: r }) => {
            setSegs((ls) => ls.map((x) => (x.id === seg.id ? { ...x, busy: false, text: r.ok ? r.text : '（转写失败）' } : x)))
          })
          .catch(() => setSegs((ls) => ls.map((x) => (x.id === seg.id ? { ...x, busy: false, text: '（转写不可用）' } : x))))
      } catch { /* */ }
    }
    void poll()
  }, [mic?.last_segment_ts, micOn, http])   // ts 变化即触发

  /**PCM(16k/16bit/mono, base64) → WAV Blob 播放 */
  function playSeg(seg: Seg): void {
    const bin = atob(seg.b64)
    const pcm = new Uint8Array(bin.length)
    for (let i = 0; i < bin.length; i++) pcm[i] = bin.charCodeAt(i)
    const header = new ArrayBuffer(44)
    const dv = new DataView(header)
    const ws = (off: number, str: string): void => { for (let i = 0; i < str.length; i++) dv.setUint8(off + i, str.charCodeAt(i)) }
    ws(0, 'RIFF'); dv.setUint32(4, 36 + pcm.length, true); ws(8, 'WAVE'); ws(12, 'fmt ')
    dv.setUint32(16, 16, true); dv.setUint16(20, 1, true); dv.setUint16(22, 1, true)
    dv.setUint32(24, 16000, true); dv.setUint32(28, 32000, true); dv.setUint16(32, 2, true); dv.setUint16(34, 16, true)
    ws(36, 'data'); dv.setUint32(40, pcm.length, true)
    const blob = new Blob([header, pcm], { type: 'audio/wav' })
    new Audio(URL.createObjectURL(blob)).play().catch(() => toast.warning('播放失败'))
  }

  async function switchSource(src: number): Promise<void> {
    try {
      await http.post('/api/mic/source', { mic_source: src })
      setMicSource(src)
      toast.success(src === 0 ? '已切内置麦克风' : '已切外置麦克风')
    } catch { toast.error('切换失败') }
  }

  const vadTag = (() => {
    if (!mic?.enabled) return <Tag size="small" color="grey" shape="circle">未开启</Tag>
    return mic.vad_state === 2
      ? <Tag size="small" color="green" shape="circle">语音段中</Tag>
      : <Tag size="small" color="blue" shape="circle">监听中</Tag>
  })()

  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: 16 }}>
      {/* TTS + 音量 */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: 16 }}>
        <Card title={<span><AudioLines size={15} style={{ verticalAlign: -2, marginRight: 6 }} />语音播报</span>}>
          <div style={{ display: 'flex', gap: 8 }}>
            <Input value={text} onChange={setText} placeholder="输入播报文本，Enter 发送"
              onEnterPress={() => void speak()} />
            <Button theme="solid" icon={<Play size={13} />} loading={busy} onClick={() => void speak()}>
              播报
            </Button>
          </div>
          <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 8 }}>
            播报会打断当前语音 · priority 6
          </Typography.Text>
        </Card>

        <Card title={<span><Volume2 size={15} style={{ verticalAlign: -2, marginRight: 6 }} />音量</span>}>
          {/* 一行式：左声音开关，右滑块撑满（0-100，静音时禁用；步进1，纯数值无单位） */}
          <div style={{ display: 'flex', alignItems: 'center', gap: 16, width: '100%' }}>
            <Switch checked={!muted} size="small"
              onChange={(v) => {
                setMuted(!v)
                void http.post(`/api/mute?mute=${!v}`).catch(() => toast.error('静音设置失败'))
              }} />
            <div style={{ flex: 1, minWidth: 0 }}>
              <Slider value={Number(volume) || 0} min={0} max={100} step={1}
                style={{ width: '100%', margin: 0 }}
                onChange={(v) => setVolume(Number(v) || 0)}
                onAfterChange={(v) => {
                  const n = Number(v) || 0
                  if (n !== committed.current) applyVolume(n)
                }}
                disabled={muted} />
            </div>
            <span style={{ width: 30, textAlign: 'right', fontWeight: 700, fontVariantNumeric: 'tabular-nums' }}>
              {Number(volume) || 0}
            </span>
          </div>
        </Card>
      </div>

      {/* 麦克风 */}
      <Card title={<span><Mic size={15} style={{ verticalAlign: -2, marginRight: 6 }} />麦克风 · VAD 采集</span>}>
        <div style={{ display: 'flex', alignItems: 'center', gap: 10, marginBottom: 14 }}>
          <Switch checked={micOn} onChange={(v) => void toggleMic(v)} />
          {micOn ? <Mic size={16} color="var(--gg-success)" /> : <MicOff size={16} color="var(--semi-color-text-2)" />}
          {vadTag}
        </div>

        <div style={{ display: 'flex', alignItems: 'center', gap: 8, marginBottom: 14 }}>
          <Typography.Text type="tertiary" size="small">设备：</Typography.Text>
          {[0, 1].map((s) => (
            <Tag key={s} size="small" shape="circle" type={micSource === s ? 'solid' : 'ghost'}
              style={{ cursor: 'pointer' }} onClick={() => void switchSource(s)}>
              {s === 0 ? '内置' : '外置'}
            </Tag>
          ))}
        </div>

        {mic && (
          <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', display: 'grid', gap: 6 }}>
            <Row k="接收段数" v={String(mic.recv_count)} />
            <Row k="最近语音段" v={`${(mic.segment_bytes / 1024).toFixed(1)} KB`} />
            <Row k="识别文本" v={mic.text || '—'} />
          </div>
        )}
        <Typography.Text type="tertiary" size="small" style={{ display: 'block', marginTop: 10 }}>
          v0.9+ 需唤醒词激活 VAD（采集开启后说唤醒词）
        </Typography.Text>
      </Card>

      {/* 语音片段：回放 + 本地转写 */}
      <Card title={<span><ListMusic size={15} style={{ verticalAlign: -2, marginRight: 6 }} />语音片段（{segs.length}）</span>}>
        {segs.length === 0
          ? <Typography.Text type="tertiary" size="small">
              {micOn ? '监听中——唤醒词激活后，每段语音自动转文字（本地模型，离线）' : '开启采集后语音段会出现在这里'}
            </Typography.Text>
          : (
            <div style={{ display: 'flex', flexDirection: 'column', gap: 6, maxHeight: 260, overflow: 'auto' }}>
              {segs.map((seg) => (
                <div key={seg.id} style={{ display: 'flex', alignItems: 'flex-start', gap: 8, padding: '6px 8px',
                  border: '1px solid var(--semi-color-border)', borderRadius: 8 }}>
                  <Button size="small" theme="borderless" icon={<PlayCircle size={15} />}
                    onClick={() => playSeg(seg)} />
                  <div style={{ flex: 1, minWidth: 0 }}>
                    <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)' }}>
                      {new Date(seg.ts * 1000).toLocaleTimeString('zh-CN', { hour12: false })} · {seg.dur.toFixed(1)}s
                    </div>
                    <div style={{ fontSize: 13, wordBreak: 'break-all' }}>
                      {seg.busy ? <span style={{ color: 'var(--semi-color-text-2)' }}>转写中…</span> : seg.text}
                    </div>
                  </div>
                </div>
              ))}
            </div>
          )}
      </Card>
    </div>
  )
}

function Row({ k, v }: { k: string; v: string }): JSX.Element {
  return (
    <div style={{ display: 'flex', justifyContent: 'space-between' }}>
      <span>{k}</span><span style={{ color: 'var(--semi-color-text-0)' }}>{v}</span>
    </div>
  )
}
