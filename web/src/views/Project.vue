<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import {
  NButton, NInput, NModal, NSelect, NTag, NInputNumber, NSwitch, NScrollbar, NEmpty, useMessage,
} from 'naive-ui'
import {
  getProjects, getProject, saveProject, deleteProject, runProjectNode, stopProjectNode,
  getResources, type Project, type ProjectNode, type RobotResource,
} from '@/api/fastapi'
import { MOTION_OPTIONS, motionLabel, motionKey, parseMotionKey } from '@/config/motions'
import IconPlus from '~icons/mdi/plus'
import IconArrowLeft from '~icons/mdi/arrow-left'
import IconCog from '~icons/mdi/cog'
import IconStop from '~icons/mdi/stop'
import IconDelete from '~icons/mdi/delete'
import IconContentSave from '~icons/mdi/content-save'

const message = useMessage()

// ── 节点配置（内联，选项复用 TaskEditor）──
const MODE_OPTIONS = [
  { label: '稳定站立', value: 'STAND_DEFAULT' },
  { label: '走跑', value: 'LOCOMOTION_DEFAULT' },
  { label: '阻尼', value: 'DAMPING_DEFAULT' },
  { label: '位控站立', value: 'JOINT_DEFAULT' },
  { label: '零力矩/急停', value: 'PASSIVE_DEFAULT' },
]
const HTTP_METHOD_OPTIONS = [
  { label: 'GET', value: 'GET' }, { label: 'POST', value: 'POST' },
  { label: 'PUT', value: 'PUT' }, { label: 'DELETE', value: 'DELETE' }, { label: 'PATCH', value: 'PATCH' },
]
// MOTION_OPTIONS / motionLabel 已移至 @/config/motions（权威 29 组合，避免无效 motion×area）
const EMOJI_OPTIONS = [
  { label: '眨眼', value: 1 }, { label: '平静', value: 10 }, { label: '游戏', value: 20 },
  { label: '卖萌', value: 30 }, { label: '快乐', value: 90 }, { label: '加倍开心', value: 100 },
  { label: '悲伤', value: 110 }, { label: '疑惑', value: 130 }, { label: '震惊', value: 140 },
  { label: '撒娇', value: 150 }, { label: '思考', value: 170 }, { label: '愤怒', value: 180 },
  { label: '崇拜', value: 200 }, { label: '充电', value: 220 },
]
interface ParamDef { name: string; label: string; type: string; required?: boolean; default?: unknown; options?: { label: string; value: unknown }[]; hint?: string }
const STEP_TYPES = [
  { type: 'tts', label: '语音', icon: '🗣️', color: '#4CAF50' },
  { type: 'motion', label: '预设动作', icon: '🕺', color: '#FF9800' },
  { type: 'emoji', label: '表情', icon: '😊', color: '#E91E63' },
  { type: 'velocity', label: '速度', icon: '🏃', color: '#2196F3' },
  { type: 'mode', label: '运动模式', icon: '⚙️', color: '#795548' },
  { type: 'volume', label: '音量', icon: '🔊', color: '#607D8B' },
  { type: 'media', label: '媒体', icon: '🎬', color: '#673AB7' },
  { type: 'linkcraft', label: '灵创动作', icon: '🤖', color: '#00ACC1' },
  { type: 'wait', label: '等待', icon: '⏱️', color: '#9E9E9E' },
  { type: 'http', label: '接口', icon: '🌐', color: '#26A69A' },
] as const
const STEP_PARAMS: Record<string, ParamDef[]> = {
  tts: [
    { name: 'text', label: '播报文字', type: 'string', required: true },
    { name: 'wait_done', label: '精确等待播完', type: 'switch', default: true },
    { name: 'delay', label: '额外等待(s)', type: 'number', default: 0.5 },
  ],
  motion: [{ name: 'motion_id', label: '动作', type: 'number', required: true, hint: '需在稳定站立(STAND_DEFAULT)模式下执行；motion+area 为绑定组合' }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 1 }],
  emoji: [{ name: 'emotion_id', label: '表情', type: 'number', required: true }, { name: 'mode', label: '模式', type: 'select', default: 1, options: [{ label: '播放一次', value: 1 }, { label: '循环', value: 2 }] }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 0.5 }],
  velocity: [{ name: 'forward', label: '前后(m/s)', type: 'number', default: 0.3 }, { name: 'lateral', label: '左右(m/s)', type: 'number', default: 0 }, { name: 'angular', label: '旋转(rad/s)', type: 'number', default: 0 }, { name: 'duration', label: '持续时间(s)', type: 'number', default: 2 }],
  mode: [{ name: 'action_desc', label: '模式', type: 'select', required: true, default: 'STAND_DEFAULT', options: MODE_OPTIONS }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 1 }],
  volume: [{ name: 'volume', label: '音量(0-100)', type: 'number', default: 50 }],
  media: [{ name: 'file_name', label: '文件名', type: 'string', required: true, hint: 'PC3 上的音视频文件名' }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 2 }],
  linkcraft: [{ name: 'resource_key', label: '动作（从机器人拉取）', type: 'string', required: true }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 2 }],
  wait: [{ name: 'duration', label: '等待时间(s)', type: 'number', default: 2 }],
  http: [
    { name: 'method', label: '方法', type: 'select', required: true, default: 'GET', options: HTTP_METHOD_OPTIONS },
    { name: 'url', label: '接口地址', type: 'string', required: true, hint: '完整 HTTP(S) URL' },
    { name: 'headers', label: '请求头(JSON)', type: 'string', hint: '可选' },
    { name: 'body', label: '请求体', type: 'string', hint: 'POST/PUT/PATCH 发送' },
    { name: 'save_as', label: '响应存为变量', type: 'string' },
    { name: 'expect_code', label: '期望业务码', type: 'number', hint: '不符则中止；留空不校验' },
    { name: 'timeout', label: '超时(s)', type: 'number', default: 10 },
    { name: 'delay', label: '完成后等待(s)', type: 'number', default: 0.5 },
  ],
}
const STEP_DEFAULTS: Record<string, Record<string, unknown>> = {
  ...Object.fromEntries(
    Object.entries(STEP_PARAMS).map(([t, ps]) => [t, Object.fromEntries(ps.filter(p => p.default !== undefined).map(p => [p.name, p.default]))])
  ),
  tts: { text: '', wait_done: true, delay: 0.5, motions: [], emojis: [] },
  motion: { motion_id: 1002, area: 2, delay: 1 },
  linkcraft: { resource_key: '', version: '', resource_type: '', name: '', delay: 2 },
}
function typeMeta(t: string) { return STEP_TYPES.find(s => s.type === t) || { label: t, icon: '🔸', color: '#666' } }
function emojiLabel(id: number) { return EMOJI_OPTIONS.find(o => o.value === id)?.label || `表情#${id}` }
function nodeSummary(n: ProjectNode): string {
  switch (n.type) {
    case 'tts': return `"${String(n.text || '').slice(0, 16)}"`
    case 'motion': return motionLabel(Number(n.motion_id), Number(n.area))
    case 'emoji': return emojiLabel(Number(n.emotion_id))
    case 'velocity': return `${n.forward}/${n.lateral}/${n.angular} m/s · ${n.duration}s`
    case 'mode': return MODE_OPTIONS.find(o => o.value === n.action_desc)?.label || String(n.action_desc || '')
    case 'volume': return `音量 ${n.volume}%`
    case 'media': return String(n.file_name || '?')
    case 'linkcraft': return n.resource_key ? (linkcraftMap.value[n.resource_key as string]?.name || String(n.resource_key)) : '未选择'
    case 'wait': return `${n.duration}s`
    case 'http': return `${n.method || 'GET'} ${String(n.url || '').slice(0, 24)}`
    default: return ''
  }
}

// ── 灵创资源 ──
const linkcraftResources = ref<RobotResource[]>([])
const linkcraftOptions = computed(() => linkcraftResources.value.map(r => ({
  label: `${r.type === 'BODY_MOTION' ? '全身' : '手臂'} · ${r.name}`, value: r.resource_key,
})))
const linkcraftMap = computed(() => {
  const m: Record<string, RobotResource> = {}
  linkcraftResources.value.forEach(r => { m[r.resource_key] = r })
  return m
})
async function loadResources() {
  try { const r = await getResources(); if (r.ok) linkcraftResources.value = r.resources } catch { /* */ }
}

// ── 视图状态 ──
type ProjectSummary = { id: string; name: string; desc: string; icon: string; node_count: number; updated_at: string }
const view = ref<'list' | 'detail'>('list')
const projects = ref<ProjectSummary[]>([])
const currentProject = ref<Project | null>(null)
const search = ref('')
const filteredNodes = computed(() => {
  const q = search.value.trim().toLowerCase()
  const nodes = currentProject.value?.nodes || []
  if (!q) return nodes
  return nodes.filter(n => `${n.name} ${typeMeta(n.type).label} ${nodeSummary(n)}`.toLowerCase().includes(q))
})

// ── 执行 ──
const runningNodeId = ref('')
async function runNode(n: ProjectNode) {
  const pid = currentProject.value?.id
  const nid = n.id || ''
  if (!pid || !nid) return
  if (runningNodeId.value) {
    message.warning(runningNodeId.value === nid ? '该节点正在执行' : '有节点正在执行，请等待或点停止', { duration: 3000 })
    return
  }
  runningNodeId.value = nid
  try {
    const res = await runProjectNode(pid, nid)
    if (res.ok) message.success(`✅ ${n.name || typeMeta(n.type).label}`)
    else message.warning(res.error || '执行未成功', { duration: 6000 })
  } catch { message.error('执行请求失败') }
  finally { runningNodeId.value = '' }
}
async function stopAll() {
  try { await stopProjectNode(); message.info('已发送停止') } catch { /* */ }
  runningNodeId.value = ''
}

// ── 列表 ──
async function loadProjects() {
  try { const r = await getProjects(); projects.value = r.projects } catch { /* */ }
}
async function openProject(p: ProjectSummary) {
  view.value = 'detail'
  search.value = ''
  try { currentProject.value = await getProject(p.id) } catch { /* */ }
}
function backToList() { view.value = 'list'; currentProject.value = null; loadProjects() }
async function removeProject(p: ProjectSummary) {
  try { await deleteProject(p.id); message.success('已删除'); loadProjects() } catch { message.error('删除失败') }
}

// ── 编辑（项目 + 节点）──
const editOpen = ref(false)
const editProject = ref<Project>({ id: '', name: '', desc: '', icon: '📂', nodes: [] })
const addMenuOpen = ref(false)
function openEditor(p: ProjectSummary | null) {
  if (p) {
    getProject(p.id).then(t => { editProject.value = t; editOpen.value = true }).catch(() => {})
  } else {
    editProject.value = { id: '', name: '新项目', desc: '', icon: '📂', nodes: [] }
    editOpen.value = true
  }
}
function addNode(type: string) {
  editProject.value.nodes.push({ name: '', icon: '', type, ...JSON.parse(JSON.stringify(STEP_DEFAULTS[type] || {})) })
  addMenuOpen.value = false
  openNodeEdit(editProject.value.nodes.length - 1)
}
// 节点参数编辑
const nodeEditOpen = ref(false)
const nodeEditIndex = ref(-1)
const nodeEditData = ref<ProjectNode>({} as ProjectNode)
function openNodeEdit(i: number) {
  nodeEditIndex.value = i
  nodeEditData.value = JSON.parse(JSON.stringify(editProject.value.nodes[i]))
  nodeEditOpen.value = true
}
function saveNodeEdit() {
  const d = { ...nodeEditData.value }
  if (d.type === 'linkcraft' && d.resource_key) {
    const r = linkcraftMap.value[d.resource_key as string]
    if (r) { d.version = r.version; d.resource_type = r.type; d.name = d.name || r.name }
  }
  editProject.value.nodes[nodeEditIndex.value] = d
  nodeEditOpen.value = false
}
function deleteNode(i: number) {
  editProject.value.nodes.splice(i, 1)
  nodeEditOpen.value = false
}
async function handleSave() {
  if (!editProject.value.name.trim()) { message.warning('请输入项目名称'); return }
  try {
    const saved = await saveProject(JSON.parse(JSON.stringify(editProject.value)))
    message.success('已保存')
    editOpen.value = false
    await loadProjects()
    if (view.value === 'detail' && currentProject.value?.id === saved.id) {
      currentProject.value = await getProject(saved.id!)
    }
  } catch { message.error('保存失败') }
}

onMounted(() => { loadProjects(); loadResources() })
</script>

<template>
  <!-- 列表视图 -->
  <div v-if="view === 'list'" class="page">
    <header class="head">
      <div>
        <h1>自由任务</h1>
        <p>项目化的动作快捷台 · 点节点即时执行，无固定流程</p>
      </div>
      <NButton size="small" type="primary" @click="openEditor(null)">
        <template #icon><IconPlus /></template>新建项目
      </NButton>
    </header>
    <div v-if="projects.length" class="proj-grid">
      <div v-for="p in projects" :key="p.id" class="proj-card" @click="openProject(p)">
        <div class="proj-icon">{{ p.icon || '📂' }}</div>
        <div class="proj-body">
          <div class="proj-name">{{ p.name }}</div>
          <div class="proj-desc">{{ p.desc || (p.node_count + ' 个节点') }}</div>
        </div>
        <div class="proj-actions" @click.stop>
          <NButton size="tiny" quaternary @click="openEditor(p)"><IconCog /></NButton>
          <NButton size="tiny" quaternary type="error" @click="removeProject(p)"><IconDelete /></NButton>
        </div>
      </div>
    </div>
    <NEmpty v-else description="还没有项目，点击右上角新建" style="margin-top:60px" />
  </div>

  <!-- 详情视图 -->
  <div v-else class="page">
    <header class="head">
      <div class="detail-title">
        <NButton size="small" quaternary @click="backToList"><template #icon><IconArrowLeft /></template></NButton>
        <span class="proj-icon-sm">{{ currentProject?.icon || '📂' }}</span>
        <h2>{{ currentProject?.name }}</h2>
        <NTag v-if="runningNodeId" type="warning" size="small" round>执行中…</NTag>
      </div>
      <div class="detail-actions">
        <NInput v-model:value="search" placeholder="搜索节点" size="small" clearable style="width:180px" />
        <NButton v-if="runningNodeId" size="small" type="error" @click="stopAll"><template #icon><IconStop /></template>停止</NButton>
        <NButton size="small" quaternary @click="currentProject && openEditor({ id: currentProject.id!, name: currentProject.name, desc: currentProject.desc, icon: currentProject.icon, node_count: currentProject.nodes.length, updated_at: '' })">
          <template #icon><IconCog /></template>编辑
        </NButton>
      </div>
    </header>

    <div v-if="filteredNodes.length" class="node-grid">
      <button
        v-for="n in filteredNodes" :key="n.id"
        class="node-btn"
        :class="{ running: runningNodeId === n.id }"
        :disabled="!!runningNodeId"
        @click="runNode(n)"
      >
        <div class="node-icon" :style="{ background: typeMeta(n.type).color + '22', color: typeMeta(n.type).color }">
          {{ n.icon || typeMeta(n.type).icon }}
        </div>
        <div class="node-text">
          <div class="node-name">{{ n.name || typeMeta(n.type).label }}</div>
          <div class="node-sub">{{ nodeSummary(n) }}</div>
        </div>
        <div v-if="runningNodeId === n.id" class="node-spin">⏳</div>
      </button>
    </div>
    <NEmpty v-else :description="search ? '没有匹配节点' : '项目为空，点编辑添加节点'" style="margin-top:60px" />
  </div>

  <!-- 项目编辑 modal -->
  <NModal v-model:show="editOpen" preset="card" :title="editProject.id ? '编辑项目' : '新建项目'" style="max-width:780px">
    <div class="editor">
      <div class="edit-meta">
        <NInput v-model:value="editProject.icon" placeholder="图标emoji" size="small" style="width:90px" />
        <NInput v-model:value="editProject.name" placeholder="项目名称" size="small" style="width:200px" />
        <NInput v-model:value="editProject.desc" placeholder="项目描述" size="small" style="flex:1;min-width:160px" />
      </div>
      <div class="edit-section-label">节点（{{ editProject.nodes.length }}）· 点击编辑</div>
      <div class="edit-nodes">
        <NScrollbar style="max-height:360px">
          <div v-if="editProject.nodes.length" class="edit-node-list">
            <div v-for="(n, i) in editProject.nodes" :key="i" class="edit-node-row" @click="openNodeEdit(i)">
              <span class="edit-node-icon">{{ n.icon || typeMeta(n.type).icon }}</span>
              <span class="edit-node-name">{{ n.name || typeMeta(n.type).label }}</span>
              <span class="edit-node-sub">{{ nodeSummary(n) }}</span>
              <NButton size="tiny" text type="error" @click.stop="deleteNode(i)"><IconDelete /></NButton>
            </div>
          </div>
          <NEmpty v-else description="还没有节点" size="small" style="margin:30px 0" />
        </NScrollbar>
      </div>
      <NButton dashed block style="margin-top:10px" @click="addMenuOpen = true">
        <template #icon><IconPlus /></template>添加节点
      </NButton>
    </div>
    <template #footer>
      <div style="display:flex;justify-content:flex-end;gap:8px">
        <NButton size="small" @click="editOpen = false">取消</NButton>
        <NButton size="small" type="primary" @click="handleSave"><template #icon><IconContentSave /></template>保存</NButton>
      </div>
    </template>
  </NModal>

  <!-- 选择节点类型 -->
  <NModal v-model:show="addMenuOpen" preset="card" title="选择节点类型" style="max-width:460px">
    <div class="type-grid">
      <div v-for="t in STEP_TYPES" :key="t.type" class="type-item" @click="addNode(t.type)">
        <div class="type-icon" :style="{ background: t.color + '22', color: t.color }">{{ t.icon }}</div>
        <div class="type-label">{{ t.label }}</div>
      </div>
    </div>
  </NModal>

  <!-- 节点参数编辑 -->
  <NModal v-model:show="nodeEditOpen" preset="card" title="编辑节点" style="max-width:460px">
    <div class="node-edit-form">
      <div class="form-row" style="flex-direction:row;align-items:center;gap:8px">
        <NInput v-model:value="nodeEditData.icon" placeholder="图标" size="small" style="width:70px" />
        <NInput v-model:value="nodeEditData.name" placeholder="节点名称（可选）" size="small" style="flex:1" />
        <NTag size="small" :color="{ color: typeMeta(nodeEditData.type).color, textColor: '#fff' }">{{ typeMeta(nodeEditData.type).label }}</NTag>
      </div>
      <template v-for="param in STEP_PARAMS[nodeEditData.type] || []" :key="param.name">
        <div class="form-row" :class="{ 'switch-row': param.type === 'switch' }">
          <template v-if="param.type === 'switch'">
            <div class="switch-line">
              <span class="form-label">{{ param.label }}</span>
              <NSwitch v-model:value="(nodeEditData as any)[param.name]" />
            </div>
          </template>
          <template v-else>
            <span class="form-label">{{ param.label }}</span>
            <NInput v-if="param.type === 'string' && param.name !== 'resource_key'" v-model:value="(nodeEditData as any)[param.name]" size="small" type="textarea" :autosize="{ minRows: 1, maxRows: 3 }" />
            <NSelect v-else-if="param.name === 'resource_key'" v-model:value="(nodeEditData as any)[param.name]" size="small" filterable :options="linkcraftOptions" :placeholder="linkcraftResources.length ? '选择灵创动作' : '未获取到（机器人离线）'" />
            <NSelect
              v-else-if="param.name === 'motion_id'"
              :value="motionKey(Number(nodeEditData.motion_id) || 0, Number(nodeEditData.area) || 0)"
              size="small" filterable :options="MOTION_OPTIONS"
              @update:value="(v: string) => { const c = parseMotionKey(v); (nodeEditData as any).motion_id = c.motion; (nodeEditData as any).area = c.area }"
            />
            <NSelect v-else-if="param.name === 'emotion_id'" v-model:value="(nodeEditData as any)[param.name]" size="small" filterable :options="EMOJI_OPTIONS" />
            <NInputNumber v-else-if="param.type === 'number'" v-model:value="(nodeEditData as any)[param.name]" size="small" :step="0.1" style="width:100%" />
            <NSelect v-else-if="param.type === 'select'" v-model:value="(nodeEditData as any)[param.name]" size="small" :options="(param.options || []).map((o:any) => ({ label: o.label, value: o.value }))" />
          </template>
          <span v-if="param.hint" class="form-hint">{{ param.hint }}</span>
        </div>
      </template>
    </div>
    <template #footer>
      <div style="display:flex;justify-content:space-between;gap:8px">
        <NButton size="small" type="error" secondary @click="deleteNode(nodeEditIndex)"><template #icon><IconDelete /></template>删除</NButton>
        <div style="display:flex;gap:8px">
          <NButton size="small" @click="nodeEditOpen = false">取消</NButton>
          <NButton size="small" type="primary" @click="saveNodeEdit">确定</NButton>
        </div>
      </div>
    </template>
  </NModal>
</template>

<style scoped>
.page { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 24px; gap: 12px; flex-wrap: wrap; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

/* 列表 */
.proj-grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(280px, 1fr)); gap: 14px; }
.proj-card {
  display: flex; align-items: center; gap: 14px; padding: 16px;
  background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius);
  cursor: pointer; transition: all 0.15s;
}
.proj-card:hover { border-color: var(--accent); background: rgba(77,166,255,0.04); }
.proj-icon { font-size: 32px; flex-shrink: 0; }
.proj-body { flex: 1; min-width: 0; }
.proj-name { font-size: 15px; font-weight: 600; }
.proj-desc { font-size: 12px; color: var(--text-secondary); margin-top: 2px; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.proj-actions { display: flex; gap: 2px; flex-shrink: 0; }

/* 详情 */
.detail-title { display: flex; align-items: center; gap: 10px; }
.detail-title h2 { font-size: 20px; font-weight: 700; margin: 0; }
.proj-icon-sm { font-size: 24px; }
.detail-actions { display: flex; align-items: center; gap: 8px; flex-wrap: wrap; }

.node-grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(180px, 1fr)); gap: 12px; }
.node-btn {
  display: flex; align-items: center; gap: 10px; padding: 14px;
  background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius);
  cursor: pointer; transition: all 0.12s; text-align: left; position: relative;
  font-family: inherit; color: var(--text);
}
.node-btn:hover:not(:disabled) { border-color: var(--accent); transform: translateY(-1px); box-shadow: 0 4px 12px rgba(0,0,0,0.25); }
.node-btn:active:not(:disabled) { transform: translateY(0); }
.node-btn:disabled { opacity: 0.5; cursor: not-allowed; }
.node-btn.running { border-color: var(--accent); background: rgba(77,166,255,0.08); opacity: 1; }
.node-icon { width: 40px; height: 40px; border-radius: 8px; display: flex; align-items: center; justify-content: center; font-size: 22px; flex-shrink: 0; }
.node-text { flex: 1; min-width: 0; }
.node-name { font-size: 14px; font-weight: 600; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.node-sub { font-size: 11px; color: var(--text-secondary); margin-top: 2px; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.node-spin { position: absolute; top: 8px; right: 8px; font-size: 12px; animation: spin 1s linear infinite; }
@keyframes spin { to { transform: rotate(360deg); } }

/* 编辑器 */
.editor { display: flex; flex-direction: column; gap: 10px; }
.edit-meta { display: flex; gap: 8px; flex-wrap: wrap; }
.edit-section-label { font-size: 12px; color: var(--text-secondary); font-weight: 600; margin-top: 6px; }
.edit-nodes { background: var(--bg); border: 1px solid var(--border); border-radius: var(--radius); padding: 8px; }
.edit-node-list { display: flex; flex-direction: column; gap: 4px; }
.edit-node-row {
  display: flex; align-items: center; gap: 10px; padding: 8px 10px;
  background: var(--surface); border: 1px solid var(--border); border-radius: 4px; cursor: pointer;
}
.edit-node-row:hover { border-color: var(--accent); }
.edit-node-icon { font-size: 18px; flex-shrink: 0; }
.edit-node-name { font-size: 13px; font-weight: 600; min-width: 80px; }
.edit-node-sub { flex: 1; font-size: 12px; color: var(--text-secondary); overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }

.type-grid { display: grid; grid-template-columns: repeat(5, 1fr); gap: 10px; }
.type-item { display: flex; flex-direction: column; align-items: center; gap: 6px; padding: 14px 6px; background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); cursor: pointer; }
.type-item:hover { border-color: var(--accent); transform: translateY(-1px); }
.type-icon { width: 40px; height: 40px; border-radius: 8px; display: flex; align-items: center; justify-content: center; font-size: 22px; }
.type-label { font-size: 11px; }

.node-edit-form { display: flex; flex-direction: column; gap: 12px; }
.form-row { display: flex; flex-direction: column; gap: 4px; }
.form-row.switch-row { gap: 6px; }
.switch-line { display: flex; align-items: center; justify-content: space-between; gap: 8px; }
.switch-line .form-label { margin: 0; }
.form-label { font-size: 12px; color: var(--text-secondary); font-weight: 600; }
.form-hint { font-size: 11px; color: var(--text-secondary); opacity: 0.7; line-height: 1.5; }
</style>
