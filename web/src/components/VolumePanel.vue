<script setup lang="ts">
import { ref, onMounted } from 'vue'
import { getVolume, setVolume, getMute, setMute, playTts } from '@/api/fastapi'
import { NSlider, NSwitch } from 'naive-ui'
import IconVolumeHigh from '~icons/mdi/volume-high'

const volume = ref(50)
const isMute = ref(false)
const loading = ref(true)
let speakTimer: ReturnType<typeof setTimeout> | null = null

onMounted(async () => {
  try {
    const [v, m] = await Promise.all([getVolume(), getMute()])
    volume.value = v.volume
    isMute.value = m.is_mute
  } catch { /* */ }
  loading.value = false
})

async function onVolume(v: number) {
  volume.value = v
  try { await setVolume(v) } catch { /* */ }
  // 松开后播报
  if (speakTimer) clearTimeout(speakTimer)
  speakTimer = setTimeout(() => playTts({ text: `音量${v}` }), 400)
}

async function onMute(v: boolean) {
  isMute.value = v
  try { await setMute(v) } catch { /* */ }
}
</script>

<template>
  <div class="card">
    <div class="card-head">
      <IconVolumeHigh class="card-icon" />
      <span class="card-label">音量</span>
      <NSwitch :value="isMute" size="small" @update:value="onMute" />
    </div>
    <NSlider :value="volume" :min="0" :max="100" :step="1" :disabled="loading || isMute" @update:value="onVolume" />
    <div class="vol-row">
      <span>{{ isMute ? '🔇 静音' : volume }}</span>
    </div>
  </div>
</template>

<style scoped>
.card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 20px; }
.card-head { display: flex; align-items: center; gap: 8px; margin-bottom: 12px; font-size: 14px; font-weight: 600; }
.card-icon { font-size: 20px; color: var(--accent); }
.card-label { color: var(--text); flex: 1; }
.vol-row { display: flex; justify-content: center; font-size: 13px; color: var(--text-secondary); margin-top: 4px; font-family: 'JetBrains Mono', monospace; }
</style>
