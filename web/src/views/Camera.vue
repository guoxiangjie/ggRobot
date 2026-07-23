<script setup lang="ts">
import { ref, computed, onMounted, onUnmounted } from 'vue'
import { wsClient } from '@/api/ws'
import { getCameras, switchCamera } from '@/api/fastapi'
import { NSelect } from 'naive-ui'
import IconWebcam from '~icons/mdi/webcam'

interface Cam { id: string; label: string; active: boolean; selected: boolean }

const imageSrc = ref('')
const hasFrame = ref(false)
const cameras = ref<Cam[]>([])
const activeCamera = ref<string | null>(null)
const selectOpts = computed(() => cameras.value.filter(c => c.active).map(c => ({ label: c.label, value: c.id })))
const activeLabel = computed(() => cameras.value.find(c => c.id === activeCamera.value)?.label ?? '相机')

function onFrame(buf: ArrayBuffer) {
  // 格式: 4字节时间戳(ms) + JPEG 数据
  const jpeg = buf.slice(4)
  const blob = new Blob([jpeg], { type: 'image/jpeg' })
  const url = URL.createObjectURL(blob)
  if (imageSrc.value) URL.revokeObjectURL(imageSrc.value)
  imageSrc.value = url
  hasFrame.value = true
}

async function loadCameras() {
  try {
    const res = await getCameras()
    cameras.value = res.cameras
    const sel = res.cameras.find(c => c.selected) || res.cameras.find(c => c.active)
    activeCamera.value = sel?.id ?? null
  } catch { /* */ }
}

async function onChange(id: string) {
  activeCamera.value = id
  hasFrame.value = false
  if (imageSrc.value) { URL.revokeObjectURL(imageSrc.value); imageSrc.value = '' }
  try { await switchCamera(id) } catch { /* */ }
}

onMounted(() => {
  wsClient.onCamera(onFrame)
  loadCameras()
})

onUnmounted(() => {
  wsClient.offCamera(onFrame)
  if (imageSrc.value) URL.revokeObjectURL(imageSrc.value)
})
</script>

<template>
  <div class="camera">
    <header class="cam-head">
      <div>
        <h1 class="cam-title">相机</h1>
        <p class="cam-sub">{{ activeLabel }} · 自动推送</p>
      </div>
      <NSelect
        v-if="selectOpts.length"
        :value="activeCamera"
        :options="selectOpts"
        size="small"
        style="width: 168px;"
        placeholder="选择相机"
        @update:value="onChange"
      />
    </header>

    <div class="cam-frame">
      <img v-if="hasFrame" :src="imageSrc" alt="Camera" />
      <div v-else class="cam-placeholder">
        <IconWebcam style="font-size: 48px; opacity: 0.3;" />
        <p>等待画面...</p>
      </div>
    </div>
  </div>
</template>

<style scoped>
.camera { padding: 32px 0; }

.cam-head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 20px; }
.cam-title { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.cam-sub { margin: 0; font-size: 13px; color: var(--text-secondary); }

.cam-frame {
  aspect-ratio: 16 / 9; background: #000;
  border: 1px solid var(--border); border-radius: var(--radius);
  overflow: hidden; display: flex; align-items: center; justify-content: center;
}

.cam-frame img { width: 100%; height: 100%; object-fit: contain; }

.cam-placeholder { display: flex; flex-direction: column; align-items: center; gap: 12px; color: var(--text-secondary); font-size: 14px; }
</style>
