<script setup lang="ts">
import { ref } from 'vue'
import { playEmoji } from '@/api/fastapi'
import { NButton, NRadioGroup, NRadio } from 'naive-ui'

const mode = ref(1)
const loading = ref<number | null>(null)

const categories = [
  {
    name: '基础', items: [
      { id: 1, label: '😉 眨眼' },
      { id: 40, label: '😑 闭眼' },
      { id: 50, label: '👀 睁眼' },
    ]
  },
  {
    name: '情绪', items: [
      { id: 90, label: '😊 快乐' },
      { id: 100, label: '😆 加倍开心' },
      { id: 101, label: '🤩 狂喜' },
      { id: 110, label: '😢 悲伤' },
      { id: 180, label: '😠 愤怒' },
      { id: 190, label: '🤬 加倍愤怒' },
      { id: 130, label: '🤔 疑惑' },
      { id: 140, label: '😲 震惊' },
      { id: 160, label: '😐 严肃' },
      { id: 170, label: '🤔 思考' },
      { id: 60, label: '😒 无聊' },
      { id: 80, label: '😴 睡着' },
      { id: 70, label: '⚠️ 异常' },
    ]
  },
  {
    name: '卖萌', items: [
      { id: 30, label: '🥺 卖萌1' },
      { id: 31, label: '😋 卖萌2' },
      { id: 32, label: '😜 卖萌3' },
      { id: 33, label: '🤪 卖萌4' },
      { id: 150, label: '😳 撒娇' },
      { id: 200, label: '🤩 崇拜' },
      { id: 210, label: '😍 加倍崇拜' },
      { id: 120, label: '🥲 同情' },
    ]
  },
  {
    name: '其他', items: [
      { id: 10, label: '😶 平静1' },
      { id: 11, label: '😐 平静2' },
      { id: 20, label: '🎮 游戏' },
      { id: 220, label: '🔋 充电' },
    ]
  },
]

async function trigger(id: number) {
  loading.value = id
  try { await playEmoji(id, mode.value) } catch { /* */ }
  loading.value = null
}
</script>

<template>
  <div class="emoji">
    <header class="head">
      <div>
        <h1>表情</h1>
        <p>控制 X2 面部表情</p>
      </div>
      <NRadioGroup v-model:value="mode" size="small">
        <NRadio :value="1">播放一次</NRadio>
        <NRadio :value="2">循环</NRadio>
      </NRadioGroup>
    </header>

    <div v-for="cat in categories" :key="cat.name" class="category">
      <h3 class="cat-name">{{ cat.name }}</h3>
      <div class="emoji-grid">
        <NButton
          v-for="item in cat.items"
          :key="item.id"
          size="small"
          :loading="loading === item.id"
          @click="trigger(item.id)"
        >
          {{ item.label }}
        </NButton>
      </div>
    </div>
  </div>
</template>

<style scoped>
.emoji { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 24px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

.category { margin-bottom: 24px; }
.cat-name { font-size: 13px; font-weight: 600; color: var(--text-secondary); margin-bottom: 10px; }

.emoji-grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(120px, 1fr)); gap: 8px; }
</style>
