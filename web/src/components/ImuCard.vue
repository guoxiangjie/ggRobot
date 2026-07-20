<script setup lang="ts">
import IconAxisArrow from '~icons/mdi/axis-arrow'

defineProps<{ imu: { accel_x: number; accel_y: number; accel_z: number } }>()
</script>

<template>
  <div class="card">
    <div class="card-head">
      <IconAxisArrow class="card-icon" />
      <span class="card-label">IMU 加速度</span>
    </div>
    <div class="imu-grid">
      <div v-for="a in [
        { label: 'X', val: imu.accel_x },
        { label: 'Y', val: imu.accel_y },
        { label: 'Z', val: imu.accel_z }
      ]" :key="a.label" class="imu-axis">
        <span class="axis-letter">{{ a.label }}</span>
        <span class="axis-bar-wrap">
          <span class="axis-bar" :style="{
            width: Math.abs(a.val) * 80 + '%',
            background: a.val > 0 ? 'var(--accent)' : '#f87171'
          }" />
        </span>
        <span class="axis-val">{{ a.val.toFixed(2) }}<small>g</small></span>
      </div>
    </div>
  </div>
</template>

<style scoped>
.card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 20px; transition: border-color 0.2s; }
.card:hover { border-color: #2a3648; }
.card-head { display: flex; align-items: center; gap: 8px; margin-bottom: 20px; font-size: 14px; font-weight: 600; }
.card-icon { font-size: 20px; color: var(--accent); }
.card-label { color: var(--text); }
.imu-grid { display: flex; flex-direction: column; gap: 14px; }
.imu-axis { display: flex; align-items: center; gap: 10px; }
.axis-letter { width: 20px; font-family: 'JetBrains Mono', monospace; font-weight: 700; font-size: 15px; color: var(--text-secondary); text-align: center; }
.axis-bar-wrap { flex: 1; height: 6px; background: #1c2533; border-radius: var(--radius); overflow: hidden; }
.axis-bar { height: 100%; border-radius: var(--radius); transition: width 0.3s ease; min-width: 2px; }
.axis-val { font-family: 'JetBrains Mono', monospace; font-size: 13px; font-weight: 600; min-width: 72px; text-align: right; }
.axis-val small { font-weight: 400; color: var(--text-secondary); }
</style>
