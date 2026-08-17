<script setup lang="ts">
import { ref, onMounted, onBeforeUnmount } from 'vue'
import { create } from 'nipplejs'

const props = withDefaults(defineProps<{
  color?: string
  size?: number
}>(), { color: '#4da6ff', size: 120 })

const emit = defineEmits<{
  move: [vec: { x: number; y: number }]
}>()

const zoneRef = ref<HTMLElement>()
let manager: ReturnType<typeof create> | null = null

onMounted(() => {
  if (!zoneRef.value) return
  manager = create({
    zone: zoneRef.value,
    mode: 'static',
    position: { left: '50%', top: '50%' },
    color: props.color,
    size: props.size,
  })
  // nipplejs 1.0：cb 收单个 evt，vector 在 evt.data（归一化 -1~1，y 向上为正）
  manager.on('move', (evt) => {
    emit('move', { x: evt.data.vector.x, y: evt.data.vector.y })
  })
  manager.on('end', () => {
    emit('move', { x: 0, y: 0 })
  })
})

onBeforeUnmount(() => {
  manager?.destroy()
  manager = null
})
</script>

<template>
  <div
    ref="zoneRef"
    class="joy-zone"
    :style="{ width: props.size + 60 + 'px', height: props.size + 60 + 'px' }"
  />
</template>

<style scoped>
.joy-zone {
  position: relative;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 50%;
  background: radial-gradient(circle, var(--overlay), var(--overlay));
  border: 1px solid var(--border);
  touch-action: none;   /* 阻止触摸时页面滚动 */
}
</style>
