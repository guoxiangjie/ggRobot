<script setup lang="ts">
import { ref, onMounted, onUnmounted } from 'vue'
import { wsClient } from '@/api/ws'
import IconWebcam from '~icons/mdi/webcam'

const imageSrc = ref('')
const hasFrame = ref(false)

function onFrame(buf: ArrayBuffer) {
  // 格式: 4字节时间戳(ms) + JPEG 数据
  const jpeg = buf.slice(4)
  const blob = new Blob([jpeg], { type: 'image/jpeg' })
  const url = URL.createObjectURL(blob)
  if (imageSrc.value) URL.revokeObjectURL(imageSrc.value)
  imageSrc.value = url
  hasFrame.value = true
}

onMounted(() => {
  wsClient.onCamera(onFrame)
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
        <p class="cam-sub">RGBD 前视 · 自动推送</p>
      </div>
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
