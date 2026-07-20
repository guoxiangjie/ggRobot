<script setup lang="ts">
import { ref, computed } from 'vue'
import { playMotion } from '@/api/fastapi'
import { NButton, NSelect } from 'naive-ui'
import IconRun from '~icons/mdi/run'

const area = ref(2)

const areaOptions = [
  { label: '左手', value: 1 },
  { label: '右手', value: 2 },
  { label: '头部', value: 4 },
  { label: '腰部', value: 8 },
]

// 按区域分类的动作
const handMotions = [
  { id: 1002, label: '挥手' },
  { id: 1001, label: '抬手' },
  { id: 1003, label: '握手' },
  { id: 3002, label: '点赞' },
  { id: 3004, label: '比心' },
  { id: 3008, label: '拥抱' },
  { id: 1013, label: '敬礼' },
  { id: 3016, label: '说话手势' },
  { id: 3013, label: '巴斯舞' },
  { id: 1004, label: '飞吻' },
  { id: 1008, label: '击掌' },
  { id: 3003, label: '比YE' },
]

const headMotions = [
  { id: 4001, label: '点头' },
  { id: 4002, label: '摇头' },
]

const waistMotions = [
  { id: 3001, label: '鞠躬' },
]

const motions = computed(() => {
  if (area.value === 4) return headMotions
  if (area.value === 8) return waistMotions
  return handMotions
})

const loading = ref<number | null>(null)

async function trigger(id: number) {
  loading.value = id
  try {
    await playMotion(area.value, id)
  } catch (e) {
    console.error('动作失败', e)
  }
  loading.value = null
}
</script>

<template>
  <div class="card">
    <div class="card-head">
      <IconRun class="card-icon" />
      <span class="card-label">预设动作</span>
      <NSelect
        v-model:value="area"
        :options="areaOptions"
        size="tiny"
        style="width: 80px;"
      />
    </div>

    <div class="motion-grid">
      <NButton
        v-for="m in motions"
        :key="m.id"
        size="small"
        :loading="loading === m.id"
        @click="trigger(m.id)"
      >
        {{ m.label }}
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

.card:hover { border-color: #2a3648; }

.card-head {
  display: flex;
  align-items: center;
  gap: 8px;
  margin-bottom: 16px;
  font-size: 14px;
  font-weight: 600;
}

.card-icon { font-size: 20px; color: var(--accent); }
.card-label { color: var(--text); flex: 1; }

.motion-grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 8px;
}
</style>
