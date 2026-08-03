<script setup lang="ts">
import { ref, onMounted, onUnmounted } from 'vue'
import {
  micToggle, micStatus, getMicAudio, getMicSource, setMicSource, forceAsr,
} from '@/api/fastapi'
import { NSwitch, NTag, NButton, NSelect, NAlert } from 'naive-ui'
import IconDownload from '~icons/mdi/download'
import IconMicrophone from '~icons/mdi/microphone'
import IconTextToSpeech from '~icons/mdi/text-to-speech'

const enabled = ref(false)
const vadState = ref(0)
const vadLabel = ref('无语音')
const segmentBytes = ref(0)
const lastSegmentBytes = ref(0)
const micSource = ref(0)
const recvCount = ref(0)
const text = ref('')
const history = ref<string[]>([])
const lastAudioB64 = ref('')
const hasAudio = ref(false)
const asrBusy = ref(false)
let timer: ReturnType<typeof setInterval> | null = null

const VAD_COLORS: Record<number, string> = {
  0: 'var(--text-secondary)',
  1: 'var(--accent)',
  2: 'var(--success)',
  3: 'var(--accent)',
}

async function toggle() {
  const res = await micToggle(!enabled.value)
  enabled.value = res.enabled
  if (enabled.value) {
    history.value = []
    timer = setInterval(poll, 500)
  } else {
    if (timer) { clearInterval(timer); timer = null }
    vadState.value = 0
    vadLabel.value = '无语音'
  }
}

async function poll() {
  try {
    const st = await micStatus()
    vadState.value = st.vad_state
    vadLabel.value = st.vad_label || ''
    segmentBytes.value = st.segment_bytes
    lastSegmentBytes.value = st.last_segment_bytes
    recvCount.value = st.recv_count
    if (st.text && st.text !== text.value) {
      text.value = st.text
      history.value.push(st.text)
    }
    if (st.last_segment_bytes && !hasAudio.value) {
      const audio = await getMicAudio()
      if (audio.ok && audio.data) {
        lastAudioB64.value = audio.data
        hasAudio.value = true
      }
    }
  } catch { /* 离线 */ }
}

async function onSourceChange(v: number) {
  micSource.value = v
  try { await setMicSource(v) } catch { /* */ }
}

async function loadSource() {
  try { const r = await getMicSource(); micSource.value = r.mic_source } catch { /* */ }
}

async function runAsr() {
  asrBusy.value = true
  try { await forceAsr() } catch { /* */ }
  setTimeout(() => { asrBusy.value = false }, 1500)
}

/** 把最近语音段（PCM 16k/16bit/mono）加 WAV 头下载，便于直接试听 */
function downloadWav() {
  if (!lastAudioB64.value) return
  const raw = atob(lastAudioB64.value)
  const bytes = new Uint8Array(raw.length)
  for (let i = 0; i < raw.length; i++) bytes[i] = raw.charCodeAt(i)
  const sampleRate = 16000, channels = 1, bits = 16
  const header = new ArrayBuffer(44)
  const dv = new DataView(header)
  const ws = (off: number, s: string) => { for (let i = 0; i < s.length; i++) dv.setUint8(off + i, s.charCodeAt(i)) }
  ws(0, 'RIFF'); dv.setUint32(4, 36 + bytes.length, true); ws(8, 'WAVE')
  ws(12, 'fmt '); dv.setUint32(16, 16, true); dv.setUint16(20, 1, true)
  dv.setUint16(22, channels, true); dv.setUint32(24, sampleRate, true)
  dv.setUint32(28, sampleRate * channels * bits / 8, true)
  dv.setUint16(32, channels * bits / 8, true); dv.setUint16(34, bits, true)
  ws(36, 'data'); dv.setUint32(40, bytes.length, true)
  const blob = new Blob([header, bytes], { type: 'audio/wav' })
  const url = URL.createObjectURL(blob)
  const a = document.createElement('a')
  a.href = url; a.download = `x2_mic_${Date.now()}.wav`; a.click()
  URL.revokeObjectURL(url)
}

onMounted(loadSource)
onUnmounted(() => { if (timer) clearInterval(timer) })
</script>

<template>
  <div class="voice">
    <header class="head">
      <div>
        <h1>语音</h1>
        <p>麦克风 VAD 采集 · 语音识别</p>
      </div>
    </header>

    <NAlert type="info" :bordered="false" class="wake-note">
      ⚠ VAD 需要先唤醒词激活（v0.9+）：原生智元交互下唤醒词短时激活采集；切到 only_voice 模式后首次唤醒词即长期激活。
    </NAlert>

    <!-- 控制栏 -->
    <div class="control-bar">
      <div class="mic-switch">
        <IconMicrophone style="font-size:20px;" :style="{ color: enabled ? 'var(--success)' : 'var(--text-secondary)' }" />
        <span>识别</span>
        <NSwitch :value="enabled" size="small" @update:value="toggle" />
        <NTag v-if="enabled" size="tiny" type="success" :bordered="false">采集中</NTag>
      </div>
      <div class="mic-source">
        <span class="src-label">麦克风</span>
        <NSelect
          :value="micSource"
          :options="[{ label: '内置麦', value: 0 }, { label: '外置麦', value: 1 }]"
          size="small"
          style="width: 120px;"
          @update:value="onSourceChange"
        />
      </div>
      <NButton v-if="hasAudio" size="small" quaternary @click="runAsr" :loading="asrBusy">
        <template #icon><IconTextToSpeech /></template>
        重新识别
      </NButton>
      <NButton v-if="hasAudio" size="small" quaternary @click="downloadWav">
        <template #icon><IconDownload /></template>
        下载 WAV
      </NButton>
    </div>

    <!-- 采集信息 -->
    <div class="info-grid">
      <div class="info-card">
        <span class="info-label">VAD 状态</span>
        <span class="info-val" :style="{ color: VAD_COLORS[vadState] || '' }">{{ vadLabel }}</span>
      </div>
      <div class="info-card">
        <span class="info-label">采样率</span>
        <span class="info-val">16000 Hz</span>
      </div>
      <div class="info-card">
        <span class="info-label">缓冲中</span>
        <span class="info-val">{{ (segmentBytes / 1024).toFixed(1) }} KB</span>
      </div>
      <div class="info-card">
        <span class="info-label">上一段</span>
        <span class="info-val">{{ (lastSegmentBytes / 1024).toFixed(1) }} KB</span>
      </div>
    </div>

    <!-- 识别结果 -->
    <div class="result-section">
      <div class="section-label">识别结果（{{ history.length }}）</div>
      <div class="result-box" :class="{ empty: !history.length }">
        <template v-if="history.length">
          <div v-for="(h, i) in history" :key="i" class="result-line">{{ h }}</div>
        </template>
        <template v-else>
          {{ enabled ? '等待语音输入...（先唤醒）' : '开启识别后开始采集' }}
        </template>
      </div>
    </div>
  </div>
</template>

<style scoped>
.voice { padding: 32px 0; }
.head { margin-bottom: 16px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

.wake-note { margin-bottom: 20px; font-size: 12px; }

.control-bar { display: flex; align-items: center; gap: 16px; margin-bottom: 20px; flex-wrap: wrap; }
.mic-switch { display: inline-flex; align-items: center; gap: 10px; padding: 10px 16px; background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); font-size: 14px; font-weight: 600; }
.mic-source { display: inline-flex; align-items: center; gap: 8px; }
.src-label { font-size: 13px; color: var(--text-secondary); }

.info-grid { display: grid; grid-template-columns: repeat(4, 1fr); gap: 12px; margin-bottom: 24px; }
.info-card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 14px; text-align: center; }
.info-label { display: block; font-size: 11px; color: var(--text-secondary); margin-bottom: 6px; }
.info-val { font-size: 16px; font-weight: 700; font-family: 'JetBrains Mono', monospace; }

.result-section { margin-top: 8px; }
.section-label { font-size: 13px; font-weight: 600; color: var(--text-secondary); margin-bottom: 10px; }
.result-box { min-height: 140px; background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 20px; font-size: 15px; line-height: 1.7; }
.result-box.empty { color: var(--text-secondary); font-style: italic; }
.result-line { padding: 4px 0; border-bottom: 1px dashed var(--border); }
.result-line:last-child { border-bottom: none; }

@media (max-width: 640px) { .info-grid { grid-template-columns: repeat(2, 1fr); } }
</style>
