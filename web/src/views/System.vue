<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { getSystem } from '@/api/fastapi'
import { NTag, NButton } from 'naive-ui'
import IconRefresh from '~icons/mdi/refresh'

interface SystemInfo {
  action: { desc: string; status: number } | null
  system: { state: string; status: number } | null
}

const info = ref<SystemInfo>({ action: null, system: null })
const loading = ref(false)

function statusLabel(v: number): string {
  const map: Record<number, string> = { 0: 'IDLE', 100: 'RUNNING', 200: 'TRANSITION' }
  return map[v] ?? String(v)
}

function sysLabel(v: number): string {
  const map: Record<number, string> = { 0: '初始', 1: '就绪', 2: '迁移中', 3: '回滚', 4: '异常', 5: '异常迁移' }
  return map[v] ?? String(v)
}

// 是否处于开发者模式（cur_state 以 Develop_ 开头；机器正常业务态实测为 "Business"）
const isDevMode = computed(() => !!info.value.system?.state?.startsWith('Develop_'))

async function refresh() {
  loading.value = true
  try { info.value = await getSystem() } catch { /* 离线 */ }
  loading.value = false
}

onMounted(refresh)
</script>

<template>
  <div class="system">
    <header class="head">
      <div>
        <h1>系统</h1>
        <p>机器人运行状态与信息</p>
      </div>
      <NButton size="small" quaternary :loading="loading" @click="refresh">
        <template #icon><IconRefresh /></template>
        刷新
      </NButton>
    </header>

    <div class="grid">
      <!-- 系统状态 -->
      <div class="card" :class="{ 'card-dev': isDevMode }">
        <div class="card-label">系统状态</div>
        <div class="card-value" v-if="info.system">
          <NTag :type="info.system.status === 1 ? 'success' : info.system.status === 4 ? 'error' : 'warning'" round>
            {{ sysLabel(info.system.status) }}
          </NTag>
          <span class="sub">{{ info.system.state }}</span>
          <NTag v-if="isDevMode" type="error" size="small" round>开发者模式</NTag>
        </div>
        <div class="card-empty" v-else>—</div>
        <p v-if="isDevMode" class="dev-note">⚠ 原生能力已停用，完成开发后请在「控制」页切回 Ready</p>
      </div>

      <!-- 运动模式 -->
      <div class="card">
        <div class="card-label">运动模式</div>
        <div class="card-value" v-if="info.action">
          <NTag :type="info.action.status === 100 ? 'success' : 'default'" round>
            {{ statusLabel(info.action.status) }}
          </NTag>
          <span class="sub">{{ info.action.desc }}</span>
        </div>
        <div class="card-empty" v-else>—</div>
      </div>

      <!-- 连接信息 -->
      <div class="card span2">
        <div class="card-label">连接信息</div>
        <div class="conn-grid">
          <div class="conn-item">
            <span class="conn-key">rosbridge</span>
            <code>ws://10.0.1.41:9090</code>
          </div>
          <div class="conn-item">
            <span class="conn-key">FastAPI</span>
            <code>http://10.0.1.41:8000</code>
          </div>
          <div class="conn-item">
            <span class="conn-key">遥控 WS</span>
            <code>ws://10.0.1.41:8000/ws/velocity</code>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.system { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 24px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

.grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 16px; }

.card {
  background: var(--surface); border: 1px solid var(--border);
  border-radius: var(--radius); padding: 20px;
}
.span2 { grid-column: span 2; }
@media (max-width: 700px) { .span2 { grid-column: span 1; } }

.card-label { font-size: 13px; font-weight: 600; color: var(--text-secondary); margin-bottom: 12px; }
.card-value { display: flex; align-items: center; gap: 12px; }
.sub { font-size: 15px; font-weight: 600; }
.card-empty { font-size: 20px; color: var(--text-secondary); }
.card-dev { border-color: rgba(244, 75, 75, 0.5); }
.dev-note { margin: 10px 0 0; font-size: 12px; color: var(--danger); }

.conn-grid { display: flex; flex-direction: column; gap: 8px; }
.conn-item { display: flex; align-items: center; gap: 12px; }
.conn-key { font-size: 12px; color: var(--text-secondary); min-width: 80px; }
.conn-item code { font-size: 12px; font-family: 'JetBrains Mono', monospace; }
</style>
