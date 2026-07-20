<script setup lang="ts">
import IconRobotIndustrial from '~icons/mdi/robot-industrial'

defineProps<{ joints: Record<string, { position: number; velocity: number }> }>()

function short(n: string) { return n.replace(/_joint$/, '').replace(/^left_/, 'L_').replace(/^right_/, 'R_') }
</script>

<template>
  <div class="card">
    <div class="card-head">
      <IconRobotIndustrial class="card-icon" />
      <span class="card-label">关节状态</span>
      <span class="badge">{{ Object.keys(joints).length }} DOF</span>
    </div>
    <div v-if="Object.keys(joints).length" class="table">
      <div class="th"><span>关节</span><span>位置</span><span>速度</span></div>
      <div v-for="[n, j] in Object.entries(joints).slice(0, 14)" :key="n" class="tr">
        <span class="td-name">{{ short(n) }}</span>
        <span class="td-pos">{{ j.position.toFixed(3) }}</span>
        <span class="td-vel">{{ j.velocity.toFixed(3) }}</span>
      </div>
    </div>
    <div v-else class="empty">等待数据...</div>
  </div>
</template>

<style scoped>
.card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 20px; transition: border-color 0.2s; grid-column: span 2; }
.card:hover { border-color: #2a3648; }
.card-head { display: flex; align-items: center; gap: 8px; margin-bottom: 16px; font-size: 14px; font-weight: 600; }
.card-icon { font-size: 20px; color: var(--accent); }
.card-label { color: var(--text); flex: 1; }
.badge { font-size: 11px; font-family: 'JetBrains Mono', monospace; color: var(--text-secondary); background: #1c2533; padding: 2px 10px; border-radius: var(--radius); }
.table { font-family: 'JetBrains Mono', monospace; font-size: 12px; }
.th { display: grid; grid-template-columns: 1fr 100px 100px; gap: 8px; padding: 6px 0; color: var(--text-secondary); font-size: 10px; text-transform: uppercase; letter-spacing: 0.06em; border-bottom: 1px solid var(--border); margin-bottom: 4px; }
.tr { display: grid; grid-template-columns: 1fr 100px 100px; gap: 8px; padding: 4px 0; border-radius: var(--radius); transition: background 0.15s; }
.tr:hover { background: rgba(255,255,255,0.02); }
.td-name { color: var(--text-secondary); }
.td-pos { font-weight: 500; text-align: right; }
.td-vel { color: var(--text-secondary); text-align: right; }
.empty { color: var(--text-secondary); text-align: center; padding: 28px; font-size: 13px; }
@media (max-width: 900px) { .card { grid-column: span 1; } }
</style>
