<script setup lang="ts">
import { ref, onMounted, onUnmounted, computed } from 'vue'
import {
  NButton, NInput, NModal, NPopconfirm, NProgress,
  NCard, NGrid, NGi, NEmpty
} from 'naive-ui'
import {
  getTasks, getTask, deleteTask, runTask, stopTask, getTaskStatus,
  generateTask,
  type Task, type TaskStatus
} from '@/api/fastapi'
import TaskEditor from '@/components/TaskEditor.vue'
import IconPlay from '~icons/mdi/play'
import IconStop from '~icons/mdi/stop'
import IconPlus from '~icons/mdi/plus'
import IconWand from '~icons/mdi/auto-fix'
import IconDelete from '~icons/mdi/delete'
import IconPencil from '~icons/mdi/pencil'
import IconSearch from '~icons/mdi/magnify'

const toast = ref('')
const toastType = ref<'success' | 'error' | 'warning'>('success')
function showToast(msg: string, type: 'success' | 'error' | 'warning' = 'success') {
  toast.value = msg; toastType.value = type
  setTimeout(() => { toast.value = '' }, 3000)
}

const tasks = ref<Task[]>([])
const taskStatus = ref<TaskStatus>({ running: false, task_id: '', task_name: '', total: 0, current: 0, progress: 0, current_step: null, started_at: '' })
const searchQuery = ref('')
const editorOpen = ref(false)
const editorTask = ref<Task>({ id: '', name: '新任务', desc: '', steps: [] })
const aiOpen = ref(false)
const aiPrompt = ref('')
const aiLoading = ref(false)
const aiError = ref('')

const filteredTasks = computed(() => {
  if (!searchQuery.value) return tasks.value
  const q = searchQuery.value.toLowerCase()
  return tasks.value.filter(t => t.name.toLowerCase().includes(q) || t.desc.toLowerCase().includes(q))
})

async function loadTasks() {
  try { const r = await getTasks(); tasks.value = r.tasks } catch { /* */ }
}

function openEditor(taskId?: string) {
  if (taskId) {
    getTask(taskId).then(t => {
      editorTask.value = JSON.parse(JSON.stringify(t))
      editorOpen.value = true
    }).catch(() => showToast('加载失败', 'error'))
  } else {
    editorTask.value = { id: '', name: '新任务', desc: '', steps: [] }
    editorOpen.value = true
  }
}

function onSaved() { loadTasks() }

async function runGenerate() {
  const prompt = aiPrompt.value.trim()
  if (!prompt || aiLoading.value) return
  aiLoading.value = true
  aiError.value = ''
  try {
    const res = await generateTask(prompt)
    if (!res.ok || !res.task) {
      aiError.value = res.error || '生成失败'
      return
    }
    aiOpen.value = false
    // 直接打开编辑器微调，保存后即成为正式任务
    editorTask.value = JSON.parse(JSON.stringify({ ...res.task, id: '' }))
    editorOpen.value = true
  } catch {
    aiError.value = '生成请求失败'
  } finally {
    aiLoading.value = false
  }
}

async function handleRun(taskId: string) {
  try {
    const r = await runTask(taskId)
    if (!r.ok) { showToast(r.error || '启动失败', 'error'); return }
    showToast('任务已启动')
    pollStatus()
  } catch { showToast('启动失败', 'error') }
}

async function handleDelete(id: string) {
  try { await deleteTask(id); showToast('已删除'); loadTasks() } catch { showToast('删除失败', 'error') }
}

let timer: ReturnType<typeof setInterval> | null = null
function pollStatus() {
  if (timer) return
  timer = setInterval(async () => {
    try {
      const s = await getTaskStatus()
      taskStatus.value = s
      if (!s.running) { stopPolling(); showToast('任务完成') }
    } catch { stopPolling() }
  }, 500)
}
function stopPolling() { if (timer) { clearInterval(timer); timer = null } }
async function handleStop() { try { await stopTask(); stopPolling(); showToast('已停止') } catch { /* */ } }

onMounted(loadTasks)
onUnmounted(stopPolling)
</script>

<template>
  <div class="task-page">
    <!-- ── 顶部 ── -->
    <header class="head">
      <div>
        <h1>作业</h1>
        <p>任务编排 · {{ tasks?.length || 0 }} 个任务</p>
      </div>
      <div class="head-right">
        <template v-if="taskStatus.running">
          <NButton type="error" size="small" @click="handleStop">
            <template #icon><IconStop /></template>
            停止 ({{ taskStatus.current }}/{{ taskStatus.total }})
          </NButton>
        </template>
      </div>
    </header>

    <!-- ── 搜索栏 ── -->
    <div class="search-bar">
      <NInput v-model:value="searchQuery" placeholder="搜索任务..." clearable size="small" style="width:260px">
        <template #prefix><IconSearch /></template>
      </NInput>
      <NButton type="primary" size="small" @click="openEditor()">
        <template #icon><IconPlus /></template>
        新建任务
      </NButton>
      <NButton type="info" secondary size="small" @click="aiOpen = true">
        <template #icon><IconWand /></template>
        AI 生成
      </NButton>
    </div>

    <!-- ── 运行状态条 ── -->
    <div class="status-bar" v-if="taskStatus.running">
      <NProgress :percentage="taskStatus.progress" :color="'#4da6ff'" :height="3" :border-radius="0"
        style="position:absolute;top:0;left:0;right:0" />
      <span class="status-text">▶ {{ taskStatus.task_name }} · {{ taskStatus.current }}/{{ taskStatus.total }}</span>
    </div>

    <!-- ── 宫格 ── -->
    <div class="grid-area" v-if="filteredTasks && filteredTasks.length">
      <NGrid :cols="5" :x-gap="16" :y-gap="16" responsive="screen">
        <NGi v-for="t in filteredTasks" :key="t.id">
          <NCard
            :class="['task-card', { 'task-card-running': taskStatus.running && taskStatus.task_id === t.id }]"
            size="small" hoverable
          >
            <div class="card-inner" @click="openEditor(t.id)">
              <div class="card-icon">{{ t.name.startsWith('打') ? '👋' : t.name.startsWith('趣') ? '💃' : t.name.startsWith('短') ? '🚶' : '📋' }}</div>
              <div class="card-name">{{ t.name }}</div>
              <div class="card-desc">{{ t.desc || '暂无描述' }}</div>
              <div class="card-meta">{{ t.step_count }} 个步骤</div>
            </div>
            <div class="card-actions" @click.stop>
              <NButton size="tiny" text @click="openEditor(t.id)"><template #icon><IconPencil /></template></NButton>
              <NButton v-if="!taskStatus.running" size="tiny" text type="success" @click="handleRun(t.id)"><template #icon><IconPlay /></template></NButton>
              <NPopconfirm @positive-click="handleDelete(t.id)">
                <template #trigger>
                  <NButton size="tiny" text type="error"><template #icon><IconDelete /></template></NButton>
                </template>
                确认删除「{{ t.name }}」？
              </NPopconfirm>
            </div>
          </NCard>
        </NGi>
      </NGrid>
    </div>

    <NEmpty v-else description="暂无任务，点击上方按钮创建" style="margin-top:80px" />

    <!-- toast -->
    <div v-if="toast" :class="['toast', 'toast-' + toastType]">{{ toast }}</div>

    <!-- ── 编辑弹窗 ── -->
    <NModal
      v-model:show="editorOpen"
      preset="card"
      :title="editorTask.id ? '编辑任务' : '新建任务'"
      style="width:min(1400px,97vw)"
      :mask-closable="false"
    >
      <TaskEditor v-if="editorOpen" :task="editorTask" @saved="onSaved" @close="editorOpen = false" />
    </NModal>

    <!-- ── AI 生成弹窗 ── -->
    <NModal v-model:show="aiOpen" preset="card" title="AI 生成编排任务" style="width:560px">
      <div class="ai-box">
        <NInput
          v-model:value="aiPrompt"
          type="textarea"
          placeholder="描述你想让机器人做的事，例如：让机器人自我介绍，然后鞠躬并挥手"
          :autosize="{ minRows: 3, maxRows: 6 }"
          :disabled="aiLoading"
        />
        <p v-if="aiError" class="ai-error">{{ aiError }}</p>
        <div class="ai-actions">
          <NButton size="small" type="primary" :loading="aiLoading" :disabled="!aiPrompt.trim()" @click="runGenerate">
            <template #icon><IconWand /></template>
            生成
          </NButton>
          <NButton size="small" quaternary @click="aiOpen = false">取消</NButton>
        </div>
        <p class="ai-tip">未配置 AI 接口时使用内置规则生成（支持：打招呼 / 跳舞 / 巡逻 / 比心 / 挥手 / 鞠躬 / 飞吻 / 前进等）。生成结果会打开编辑器，可微调后保存。</p>
      </div>
    </NModal>
  </div>
</template>

<style scoped>
.task-page { padding: 24px 0; min-height: calc(100vh - 52px); display: flex; flex-direction: column; }

.head { display: flex; align-items: center; justify-content: space-between; margin-bottom: 16px; }
.head h1 { font-size: 22px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }
.head-right { display: flex; gap: 8px; }

.search-bar { display: flex; align-items: center; gap: 12px; margin-bottom: 20px; }

.status-bar { position: relative; display: flex; align-items: center; padding: 10px 16px;
  border: 1px solid var(--border); border-radius: var(--radius); margin-bottom: 16px; background: rgba(77,166,255,0.06); }
.status-text { font-size: 13px; color: var(--accent); }

.grid-area { flex: 1; }
.task-card { border-radius: var(--radius); transition: all 0.2s; }
.task-card:hover { transform: translateY(-1px); }
.task-card-running { border-color: var(--accent) !important; box-shadow: 0 0 8px rgba(77,166,255,0.15); }
.card-inner { cursor: pointer; padding: 4px 0; }
.card-icon { font-size: 32px; margin-bottom: 8px; }
.card-name { font-size: 14px; font-weight: 700; margin-bottom: 4px; line-height: 1.3; }
.card-desc { font-size: 12px; color: var(--text-secondary); margin-bottom: 8px; line-height: 1.4;
  overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.card-meta { font-size: 11px; color: var(--text-secondary); opacity: 0.7; }
.card-actions { display: flex; gap: 2px; padding-top: 8px; margin-top: 8px;
  border-top: 1px solid var(--border); justify-content: center; }

.toast { position: fixed; top: 68px; left: 50%; transform: translateX(-50%); z-index: 9999;
  padding: 8px 24px; border-radius: 6px; font-size: 13px; font-weight: 600;
  pointer-events: none; animation: toastIn 0.25s ease; }
.toast-success { background: #1a3a2a; color: #3cc98e; border: 1px solid #3cc98e; }
.toast-error { background: #3a1a1a; color: #f44b4b; border: 1px solid #f44b4b; }
.toast-warning { background: #3a301a; color: #f0a020; border: 1px solid #f0a020; }
@keyframes toastIn { from { opacity: 0; transform: translateX(-50%) translateY(-8px); } to { opacity: 1; transform: translateX(-50%) translateY(0); } }

.ai-box { display: flex; flex-direction: column; gap: 12px; }
.ai-actions { display: flex; gap: 8px; }
.ai-error { margin: 0; font-size: 12px; color: var(--danger); }
.ai-tip { margin: 0; font-size: 11px; color: var(--text-secondary); opacity: 0.75; line-height: 1.6; }
</style>
