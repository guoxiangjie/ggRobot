<script setup lang="ts">
import { ref, onUnmounted } from 'vue'
import { micToggle, micStatus, getMicAudio } from '@/api/fastapi'
import { NSwitch, NTag, NButton } from 'naive-ui'
import IconDownload from '~icons/mdi/download'

function downloadPCM() {
  if (!lastAudioB64.value) return
  const raw = atob(lastAudioB64.value)
  const bytes = new Uint8Array(raw.length)
  for (let i = 0; i < raw.length; i++) bytes[i] = raw.charCodeAt(i)
  const blob = new Blob([bytes], { type: 'audio/pcm' })
  const url = URL.createObjectURL(blob)
  const a = document.createElement('a')
  a.href = url; a.download = `x2_mic_${Date.now()}.pcm`; a.click()
  URL.revokeObjectURL(url)
}
import IconMicrophone from '~icons/mdi/microphone'

const enabled = ref(false)
const info = ref<Record<string, unknown>>({})
const vadState = ref(0)
const segmentSize = ref(0)
const text = ref('')
const lastAudioB64 = ref('')
const hasAudio = ref(false)
let timer: ReturnType<typeof setInterval> | null = null

const VAD_LABELS: Record<number, string> = { 0: '无语音', 1: '开始说话', 2: '说话中', 3: '语音结束' }

async function toggle() {
  const res = await micToggle(!enabled.value)
  enabled.value = res.enabled
  if (enabled.value) {
    timer = setInterval(async () => {
      try {
        const st = await micStatus()
        info.value = st.info as Record<string, unknown>
        vadState.value = (st.info as any)?.vad_state ?? 0
        segmentSize.value = st.segment_size
        if (st.has_segment) {
          const audio = await getMicAudio()
          if (audio.ok) {
            text.value += `[收到语音段 ${(audio.size / 1024).toFixed(1)}KB]\n`
            lastAudioB64.value = audio.data
            hasAudio.value = true
          }
        }
      } catch { /* */ }
    }, 500)
  } else {
    if (timer) { clearInterval(timer); timer = null }
    info.value = {}; vadState.value = 0; segmentSize.value = 0; text.value = ''
  }
}

onUnmounted(() => { if (timer) clearInterval(timer) })
</script>

<template>
  <div class="voice">
    <header class="head">
      <div>
        <h1>语音</h1>
        <p>麦克风采集 · 语音识别</p>
      </div>
    </header>

    <!-- 控制栏 -->
    <div class="control-bar">
      <div class="mic-switch">
        <IconMicrophone style="font-size:20px;" :style="{ color: enabled ? 'var(--success)' : 'var(--text-secondary)' }" />
        <span>麦克风</span>
        <NSwitch :value="enabled" size="small" @update:value="toggle" />
        <NTag v-if="enabled" size="tiny" type="success" :bordered="false">采集中</NTag>
        <NButton v-if="hasAudio" size="tiny" quaternary @click="downloadPCM"><template #icon><IconDownload /></template>下载 PCM</NButton>
      </div>
    </div>

    <!-- 采集信息 + VAD 状态 -->
    <div v-if="enabled" class="info-grid">
      <div class="info-card">
        <span class="info-label">VAD 状态</span>
        <span class="info-val" :style="{ color: vadState === 2 ? 'var(--success)' : vadState === 3 ? 'var(--accent)' : '' }">
          {{ VAD_LABELS[vadState] || vadState }}
        </span>
      </div>
      <div class="info-card">
        <span class="info-label">采样率</span>
        <span class="info-val">{{ info.sample_rate || '-' }} Hz</span>
      </div>
      <div class="info-card">
        <span class="info-label">缓冲中</span>
        <span class="info-val">{{ ((info.segment_bytes as number || 0) / 1024).toFixed(1) }} KB</span>
      </div>
      <div class="info-card">
        <span class="info-label">上一段</span>
        <span class="info-val">{{ (segmentSize / 1024).toFixed(1) }} KB</span>
      </div>
    </div>

    <!-- 识别结果区 -->
    <div class="result-section">
      <div class="section-label">识别结果</div>
      <div class="result-box" :class="{ empty: !text }">
        {{ text || '等待语音输入...' }}
      </div>
    </div>
  </div>
</template>

<style scoped>
.voice { padding: 32px 0; }
.head { margin-bottom: 24px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

.control-bar { margin-bottom: 20px; }
.mic-switch { display: inline-flex; align-items: center; gap: 10px; padding: 10px 16px; background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); font-size: 14px; font-weight: 600; }

.info-grid { display: grid; grid-template-columns: repeat(4, 1fr); gap: 12px; margin-bottom: 24px; }
.info-card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 14px; text-align: center; }
.info-label { display: block; font-size: 11px; color: var(--text-secondary); margin-bottom: 6px; }
.info-val { font-size: 16px; font-weight: 700; font-family: 'JetBrains Mono', monospace; }

.result-section { margin-top: 8px; }
.section-label { font-size: 13px; font-weight: 600; color: var(--text-secondary); margin-bottom: 10px; }
.result-box { min-height: 120px; background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 20px; font-size: 15px; line-height: 1.6; white-space: pre-wrap; }
.result-box.empty { color: var(--text-secondary); font-style: italic; }

@media (max-width: 640px) { .info-grid { grid-template-columns: repeat(2, 1fr); } }
</style>
