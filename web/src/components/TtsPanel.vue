<script setup lang="ts">
import { ref } from 'vue'
import { playTts } from '@/api/fastapi'
import { NButton, NInput } from 'naive-ui'
import IconTextToSpeech from '~icons/mdi/text-to-speech'
import IconSend from '~icons/mdi/send'

const text = ref('')
const loading = ref(false)

async function send() {
  if (!text.value.trim()) return
  loading.value = true
  try {
    await playTts({ text: text.value })
  } catch (e) {
    console.error('TTS 失败', e)
  }
  loading.value = false
}
</script>

<template>
  <div class="card">
    <div class="card-head">
      <IconTextToSpeech class="card-icon" />
      <span class="card-label">语音播报</span>
    </div>

    <div class="tts-body">
      <NInput
        v-model:value="text"
        type="textarea"
        placeholder="输入播报内容，Enter 发送..."
        :autosize="{ minRows: 2, maxRows: 4 }"
        :disabled="loading"
        @keyup.enter.exact="send"
      />
      <NButton
        type="primary"
        :loading="loading"
        @click="send"
        style="margin-top: 10px;"
      >
        <template #icon><IconSend /></template>
        播报
      </NButton>
    </div>
  </div>
</template>

<style scoped>
.card {
  background: var(--surface);
  border: 1px solid var(--border);
  border-radius: var(--radius);
  padding: 20px;
  transition: border-color 0.2s;
}

.card:hover { border-color: var(--border-hover); }

.card-head {
  display: flex;
  align-items: center;
  gap: 8px;
  margin-bottom: 16px;
  font-size: 14px;
  font-weight: 600;
}

.card-icon { font-size: 20px; color: var(--accent); }
.card-label { color: var(--text); }

.tts-body {
  display: flex;
  flex-direction: column;
}
</style>
