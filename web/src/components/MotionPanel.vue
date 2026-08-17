<script setup lang="ts">
import { ref } from 'vue'
import { playMotion } from '@/api/fastapi'
import { NButton } from 'naive-ui'
import IconRun from '~icons/mdi/run'
import { MOTION_LIST } from '@/config/motions'

const loading = ref<string | null>(null)

async function trigger(motion: number, area: number) {
  const key = `${motion}:${area}`
  loading.value = key
  try {
    await playMotion(area, motion, true)  // interrupt=true 打断前动作，连续点击可靠
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
      <span class="card-count">{{ MOTION_LIST.length }} 个</span>
    </div>
    <div class="motion-grid">
      <NButton
        v-for="m in MOTION_LIST"
        :key="`${m.motion}:${m.area}`"
        size="small"
        :loading="loading === `${m.motion}:${m.area}`"
        @click="trigger(m.motion, m.area)"
      >
        {{ m.name }}
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
  grid-column: span 2;  /* 预设动作按钮多，占两列加宽 */
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
.card-label { color: var(--text); flex: 1; }
.card-count { font-size: 12px; color: var(--text-secondary); font-weight: 400; }

.motion-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(104px, 1fr));
  gap: 8px;
}
</style>
