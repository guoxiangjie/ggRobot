<script setup lang="ts">
import { ref, watch, computed } from 'vue'
import {
  NButton, NInput, NModal, NSelect, NTag, NInputNumber,
  NScrollbar, NEmpty, NRadioGroup, NRadioButton, NSwitch, useMessage,
} from 'naive-ui'
import { saveTask, type Task, type TaskStep } from '@/api/fastapi'
import IconDelete from '~icons/mdi/delete'
import IconContentSave from '~icons/mdi/content-save'
import IconPlus from '~icons/mdi/plus'
import IconArrowUp from '~icons/mdi/arrow-up'
import IconArrowDown from '~icons/mdi/arrow-down'
import IconSettings from '~icons/mdi/cog-outline'
import IconTts from '~icons/mdi/text-to-speech'
import IconWait from '~icons/mdi/timer-sand'
import IconMotion from '~icons/mdi/human-greeting-variant'
import IconEmoji from '~icons/mdi/emoticon-outline'
import IconVelocity from '~icons/mdi/speedometer'
import IconVolume from '~icons/mdi/volume-high'
import IconMode from '~icons/mdi/tune-variant'
import IconMedia from '~icons/mdi/filmstrip'
import IconHttp from '~icons/mdi/api'
import IconLinkcraft from '~icons/mdi/robot-outline'
import { getResources, type RobotResource } from '@/api/fastapi'
import { MOTION_OPTIONS, motionLabel, motionKey, parseMotionKey } from '@/config/motions'

const props = defineProps<{ task: Task }>()
const emit = defineEmits<{ saved: []; close: [] }>()
const message = useMessage()

// 灵创动作资源（从机器人实时拉取）
const linkcraftResources = ref<RobotResource[]>([])
const linkcraftOptions = computed(() => linkcraftResources.value.map(r => ({
  label: `${r.type === 'BODY_MOTION' ? '全身' : '手臂'} · ${r.name}`,
  value: r.resource_key,
})))
const linkcraftMap = computed(() => {
  const m: Record<string, RobotResource> = {}
  linkcraftResources.value.forEach(r => { m[r.resource_key] = r })
  return m
})
async function loadResources() {
  try { const r = await getResources(); if (r.ok) linkcraftResources.value = r.resources } catch { /* 离线 */ }
}
loadResources()
function linkcraftLabel(key: string) {
  const r = linkcraftMap.value[key]
  return r ? `${r.type === 'BODY_MOTION' ? '全身' : '手臂'} · ${r.name}` : key
}

// ── 步骤类型定义 ──
interface ParamDef { name: string; label: string; type: string; required?: boolean; default?: unknown; options?: { label: string; value: unknown }[]; hint?: string }
// 运动模式 action_desc（v0.8.2+ 字符串，非数字ID）
const MODE_OPTIONS = [
  { label: '稳定站立', value: 'STAND_DEFAULT' },
  { label: '走跑', value: 'LOCOMOTION_DEFAULT' },
  { label: '阻尼', value: 'DAMPING_DEFAULT' },
  { label: '位控站立', value: 'JOINT_DEFAULT' },
  { label: '零力矩/急停', value: 'PASSIVE_DEFAULT' },
]
const MODE_LABELS: Record<string, string> = Object.fromEntries(MODE_OPTIONS.map(o => [o.value, o.label]))
const HTTP_METHOD_OPTIONS = [
  { label: 'GET', value: 'GET' },
  { label: 'POST', value: 'POST' },
  { label: 'PUT', value: 'PUT' },
  { label: 'DELETE', value: 'DELETE' },
  { label: 'PATCH', value: 'PATCH' },
]
// 表情 ID → 名称（来自 AimDK 文档枚举）
const EMOJI_OPTIONS = [
  { label: '眨眼', value: 1 },
  { label: '平静', value: 10 },
  { label: '游戏', value: 20 },
  { label: '卖萌', value: 30 },
  { label: '闭眼', value: 40 },
  { label: '睁眼', value: 50 },
  { label: '无聊', value: 60 },
  { label: '睡着', value: 80 },
  { label: '快乐', value: 90 },
  { label: '加倍开心', value: 100 },
  { label: '悲伤', value: 110 },
  { label: '同情', value: 120 },
  { label: '疑惑', value: 130 },
  { label: '震惊', value: 140 },
  { label: '撒娇', value: 150 },
  { label: '严肃', value: 160 },
  { label: '思考', value: 170 },
  { label: '愤怒', value: 180 },
  { label: '加倍愤怒', value: 190 },
  { label: '崇拜', value: 200 },
  { label: '充电', value: 220 },
]
function emojiLabel(id: number) { return EMOJI_OPTIONS.find(o => o.value === id)?.label || `表情#${id}` }
const STEP_TYPES = [
  { type: 'tts', label: '语音播报', icon: IconTts, color: '#4CAF50' },
  { type: 'wait', label: '等待', icon: IconWait, color: '#9E9E9E' },
  { type: 'motion', label: '预设动作', icon: IconMotion, color: '#FF9800' },
  { type: 'emoji', label: '表情', icon: IconEmoji, color: '#E91E63' },
  { type: 'velocity', label: '速度控制', icon: IconVelocity, color: '#2196F3' },
  { type: 'volume', label: '音量', icon: IconVolume, color: '#607D8B' },
  { type: 'mode', label: '运动模式', icon: IconMode, color: '#795548' },
  { type: 'media', label: '媒体播放', icon: IconMedia, color: '#673AB7' },
  { type: 'linkcraft', label: '灵创动作', icon: IconLinkcraft, color: '#00ACC1' },
  { type: 'http', label: '接口调用', icon: IconHttp, color: '#26A69A' },
] as const

const STEP_PARAMS: Record<string, ParamDef[]> = {
  tts: [
    { name: 'text', label: '播报文字', type: 'string', required: true },
    { name: 'wait_done', label: '精确等待播完', type: 'switch', default: true, hint: '订阅播放状态事件，语音播完再进入下一步（关闭则仅按下方时长等待）' },
    { name: 'motion_wait', label: '等动作做完', type: 'switch', default: true, hint: '开启：等 TTS 和动作都完成再下一步（取较晚者）；关闭：语音播完即停止动作进入下一步' },
    { name: 'delay', label: '额外等待(s)', type: 'number', default: 0, hint: '播完后额外等待，给表情/动作收尾' },
  ],
  wait: [{ name: 'duration', label: '等待时间(s)', type: 'number', default: 2 }],
  motion: [{ name: 'motion_id', label: '动作', type: 'number', required: true, hint: 'motion+area 绑定组合；需 STAND_DEFAULT 模式' }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 1 }],
  emoji: [{ name: 'emotion_id', label: '表情', type: 'number', required: true }, { name: 'mode', label: '模式', type: 'select', default: 1, options: [{ label: '播放一次', value: 1 }, { label: '循环', value: 2 }] }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 0.5 }],
  velocity: [{ name: 'forward', label: '前后(m/s)', type: 'number', default: 0.3 }, { name: 'lateral', label: '左右(m/s)', type: 'number', default: 0 }, { name: 'angular', label: '旋转(rad/s)', type: 'number', default: 0 }, { name: 'duration', label: '持续时间(s)', type: 'number', default: 2 }],
  volume: [{ name: 'volume', label: '音量(0-100)', type: 'number', default: 50 }],
  mode: [{ name: 'action_desc', label: '模式', type: 'select', required: true, default: 'STAND_DEFAULT', options: MODE_OPTIONS }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 1 }],
  media: [{ name: 'file_name', label: '文件名', type: 'string', required: true }, { name: 'delay', label: '完成后等待(s)', type: 'number', default: 2 }],
  linkcraft: [
    { name: 'resource_key', label: '动作（从机器人拉取）', type: 'string', required: true },
    { name: 'delay', label: '完成后等待(s)', type: 'number', default: 2 },
  ],
  http: [
    { name: 'method', label: '方法', type: 'select', required: true, default: 'GET', options: HTTP_METHOD_OPTIONS },
    { name: 'url', label: '接口地址', type: 'string', required: true, hint: '完整 HTTP(S) URL，支持 {{var.field}}' },
    { name: 'headers', label: '请求头(JSON)', type: 'string', hint: '可选，如 {"Authorization":"Bearer xxx"}' },
    { name: 'body', label: '请求体', type: 'string', hint: 'POST/PUT/PATCH 发送内容，支持 {{var.field}}' },
    { name: 'save_as', label: '响应存为变量', type: 'string', hint: '填变量名，data 字段自动提升，后续用 {{变量名.字段}}' },
    { name: 'expect_code', label: '期望业务码', type: 'number', hint: '填 code 值(如0)，不符则中止任务；留空不校验' },
    { name: 'timeout', label: '超时(s)', type: 'number', default: 10 },
    { name: 'delay', label: '完成后等待(s)', type: 'number', default: 0.5 },
  ],
}
const STEP_DEFAULTS: Record<string, Record<string, unknown>> = {
  ...Object.fromEntries(
    Object.entries(STEP_PARAMS).map(([type, params]) => [type, Object.fromEntries(params.filter(p => p.default !== undefined).map(p => [p.name, p.default]))])
  ),
  // TTS 节点支持并行挂载多个动作和表情，默认精确等待播完 + 等动作做完
  tts: { text: '', wait_done: true, motion_wait: true, delay: 0, motions: [], emojis: [] },
  // 预设动作：motion+area 绑定（默认右手挥手 1002:2）
  motion: { motion_id: 1002, area: 2, delay: 1 },
  // 灵创动作：resource_key + version/type/name（从机器人资源拉取）
  linkcraft: { resource_key: '', version: '', resource_type: '', name: '', delay: 2 },
}

function typeMeta(type: string) { return STEP_TYPES.find(s => s.type === type) || { label: type, icon: IconPlus, color: '#666' } }

// ── 编辑状态（左右布局：左链路 / 右配置）──
const editTask = ref<Task>({ id: '', name: '', desc: '', steps: [] })
const selectedIndex = ref<number | null>(null)   // 左侧选中的步骤下标
const stepDraft = ref<TaskStep>({} as TaskStep)  // 右侧配置的工作副本
const addMenuOpen = ref(false)
const draftMotions = computed<any[]>(() => ((stepDraft.value as any).motions || []))
const draftEmojis = computed<number[]>(() => ((stepDraft.value as any).emojis || []))

watch(() => props.task, (t) => {
  editTask.value = JSON.parse(JSON.stringify(t))
  selectedIndex.value = null
}, { immediate: true })

// ── 左侧：链路操作 ──
function selectStep(i: number) {
  selectedIndex.value = i
  stepDraft.value = JSON.parse(JSON.stringify(editTask.value.steps[i]))
}

function addStep(type: string) {
  editTask.value.steps.push({ type, ...STEP_DEFAULTS[type] })
  addMenuOpen.value = false
  selectStep(editTask.value.steps.length - 1)  // 自动选中，右侧打开配置
}

function deleteStep(index: number) {
  editTask.value.steps.splice(index, 1)
  if (selectedIndex.value === index) selectedIndex.value = null
  else if (selectedIndex.value != null && selectedIndex.value > index) selectedIndex.value--
}

function moveStep(index: number, dir: -1 | 1) {
  const target = index + dir
  if (target < 0 || target >= editTask.value.steps.length) return
  const arr = editTask.value.steps
  ;[arr[index], arr[target]] = [arr[target], arr[index]]
  if (selectedIndex.value === index) selectedIndex.value = target
  else if (selectedIndex.value === target) selectedIndex.value = index
}

// ── 右侧：步骤配置 ──
function applyStep() {
  if (selectedIndex.value == null) return
  const data = { ...stepDraft.value }
  // 灵创动作：根据 resource_key 自动补全 version/resource_type/name
  if (data.type === 'linkcraft' && data.resource_key) {
    const r = linkcraftMap.value[data.resource_key as string]
    if (r) { data.version = r.version; data.resource_type = r.type; data.name = r.name }
  }
  editTask.value.steps[selectedIndex.value] = data
  stepDraft.value = data
  message.success('步骤已更新')
}

function onLinkcraftChange(key: string) {
  const r = linkcraftMap.value[key]
  if (r) {
    ;(stepDraft.value as any).version = r.version
    ;(stepDraft.value as any).resource_type = r.type
    ;(stepDraft.value as any).name = r.name
  }
}

function stepSummary(step: TaskStep): string {
  switch (step.type) {
    case 'tts': {
      const text = `"${(step.text as string || '').slice(0, 20)}${(step.text as string || '').length > 20 ? '...' : ''}"`
      const extras: string[] = []
      const motions = (step.motions as Array<{ motion_id: number }>) || []
      const emojis = (step.emojis as number[]) || []
      if (motions.length) extras.push(`动作×${motions.length}`)
      if (emojis.length) extras.push(`表情×${emojis.length}`)
      return extras.length ? `${text} · ${extras.join(' ')}` : text
    }
    case 'motion': return motionLabel(Number(step.motion_id), Number(step.area))
    case 'emoji': return emojiLabel(step.emotion_id as number)
    case 'velocity': return `${step.forward} / ${step.lateral} / ${step.angular} m/s · ${step.duration}s`
    case 'wait': return `${step.duration}s`
    case 'mode': return MODE_LABELS[step.action_desc as string] || (step.action_desc as string) || ''
    case 'volume': return `音量 ${step.volume}%`
    case 'media': return `${step.file_name || '?'}`
    case 'linkcraft': return step.resource_key ? linkcraftLabel(step.resource_key as string) : '未选择'
    case 'http': return `${step.method || 'GET'} ${(step.url as string || '').slice(0, 30)}`
    default: return ''
  }
}

// ── TTS 挂载：动作 / 表情（编辑右侧选中的 tts 步骤）──
const mountOpen = ref(false)
const mountMode = ref<'motion' | 'emoji'>('motion')
const mountMotion = ref<{ kind: 'preset' | 'linkcraft'; motion_id: number; area: number; resource_key: string }>({ kind: 'preset', motion_id: 1002, area: 2, resource_key: '' })
const mountEmoji = ref<number>(90)

function openMount(mode: 'motion' | 'emoji') {
  mountMode.value = mode
  if (mode === 'motion') {
    mountMotion.value = { kind: 'preset', motion_id: 1002, area: 2, resource_key: '' }
  } else {
    mountEmoji.value = 90
  }
  mountOpen.value = true
}

function saveMount() {
  const step: any = stepDraft.value
  if (!step || step.type !== 'tts') { mountOpen.value = false; return }
  if (mountMode.value === 'motion') {
    if (!step.motions) step.motions = []
    if (mountMotion.value.kind === 'linkcraft') {
      const key = mountMotion.value.resource_key
      const r = linkcraftMap.value[key]
      step.motions.push({
        kind: 'linkcraft',
        resource_key: key,
        version: r?.version || '',
        resource_type: r?.type || '',
        name: r?.name || key,
      })
    } else {
      step.motions.push({ kind: 'preset', motion_id: mountMotion.value.motion_id, area: mountMotion.value.area })
    }
  } else {
    if (!step.emojis) step.emojis = []
    step.emojis.push(mountEmoji.value)
  }
  mountOpen.value = false
}

function removeMount(kind: 'motion' | 'emoji', mountIndex: number) {
  const step: any = stepDraft.value
  if (!step || step.type !== 'tts') return
  if (kind === 'motion' && step.motions) step.motions.splice(mountIndex, 1)
  if (kind === 'emoji' && step.emojis) step.emojis.splice(mountIndex, 1)
}

async function handleSave() {
  if (!editTask.value.name.trim()) { message.warning('请输入任务名称'); return }
  try {
    await saveTask(JSON.parse(JSON.stringify(editTask.value)))
    message.success('已保存')
    emit('saved'); emit('close')
  } catch { message.error('保存失败') }
}
</script>

<template>
  <div class="editor">
    <!-- 顶部：任务信息 + 保存 -->
    <div class="editor-top">
      <NInput v-model:value="editTask.name" placeholder="任务名称（必填）" size="small" style="width: 260px" />
      <NInput v-model:value="editTask.desc" placeholder="任务描述（可选）" size="small" />
      <NButton size="small" type="primary" @click="handleSave">
        <template #icon><IconContentSave /></template>
        保存任务
      </NButton>
    </div>

    <!-- 主体：左链路 / 右配置 -->
    <div class="editor-body">
      <!-- ── 左：链路展示 ── -->
      <div class="flow-pane">
        <div class="pane-head">
          <span class="pane-title">任务流程</span>
          <span class="pane-count">{{ editTask.steps.length }} 步</span>
        </div>
        <NScrollbar class="pane-scroll">
          <div class="steps-list">
            <template v-if="editTask.steps.length">
              <div class="step-marker">▶ 开始</div>
              <template v-for="(step, i) in editTask.steps" :key="i">
                <div class="connector"></div>
                <div class="step-card" :class="{ selected: selectedIndex === i }" @click="selectStep(i)">
                  <div class="step-main">
                    <div class="step-index">{{ i + 1 }}</div>
                    <div class="step-icon" :style="{ background: typeMeta(step.type).color + '22', color: typeMeta(step.type).color }">
                      <component :is="typeMeta(step.type).icon" style="font-size:20px" />
                    </div>
                    <div class="step-body">
                      <div class="step-type">{{ typeMeta(step.type).label }}</div>
                      <div class="step-desc">{{ stepSummary(step) }}</div>
                    </div>
                    <div class="step-actions" @click.stop>
                      <NButton size="tiny" text :disabled="i === 0" @click="moveStep(i, -1)"><IconArrowUp /></NButton>
                      <NButton size="tiny" text :disabled="i === editTask.steps.length - 1" @click="moveStep(i, 1)"><IconArrowDown /></NButton>
                      <NButton size="tiny" text type="error" @click="deleteStep(i)"><IconDelete /></NButton>
                    </div>
                  </div>
                </div>
              </template>
              <div class="connector"></div>
              <div class="step-marker end">■ 结束</div>
            </template>
            <NEmpty v-else description="还没有步骤，点击下方按钮添加" size="small" style="margin:36px 0" />
          </div>
        </NScrollbar>
        <div class="flow-add">
          <NButton dashed block size="small" @click="addMenuOpen = true">
            <template #icon><IconPlus /></template>
            添加步骤
          </NButton>
        </div>
      </div>

      <!-- ── 右：配置区域 ── -->
      <div class="config-pane">
        <template v-if="selectedIndex != null">
          <div class="pane-head config-head">
            <NTag :color="{ color: typeMeta(stepDraft.type).color, textColor: '#fff' }" size="small">
              {{ typeMeta(stepDraft.type).label }}
            </NTag>
            <span class="pane-count">步骤 {{ selectedIndex + 1 }} / {{ editTask.steps.length }}</span>
          </div>
          <NScrollbar class="pane-scroll">
            <div class="config-form">
              <template v-for="param in STEP_PARAMS[stepDraft.type as string] || []" :key="param.name">
                <div class="form-row" :class="{ 'switch-row': param.type === 'switch' }">
                  <template v-if="param.type === 'switch'">
                    <div class="switch-line">
                      <span class="form-label">{{ param.label }}</span>
                      <NSwitch v-model:value="(stepDraft as any)[param.name]" />
                    </div>
                  </template>
                  <template v-else>
                    <span class="form-label">{{ param.label }}</span>
                    <NInput v-if="param.type === 'string' && param.name !== 'resource_key'" v-model:value="(stepDraft as any)[param.name]" size="small" type="textarea" :autosize="{ minRows: 1, maxRows: 3 }" />
                    <NSelect
                      v-else-if="param.name === 'resource_key'"
                      v-model:value="(stepDraft as any)[param.name]"
                      size="small"
                      filterable
                      :options="linkcraftOptions"
                      :placeholder="linkcraftResources.length ? '选择灵创动作' : '未获取到动作（机器人离线或无资源）'"
                      @update:value="onLinkcraftChange"
                    />
                    <NSelect
                      v-else-if="param.name === 'motion_id'"
                      :value="motionKey(Number((stepDraft as any).motion_id) || 0, Number((stepDraft as any).area) || 0)"
                      size="small"
                      filterable
                      :options="MOTION_OPTIONS"
                      @update:value="(v: string) => { const c = parseMotionKey(v); (stepDraft as any).motion_id = c.motion; (stepDraft as any).area = c.area }"
                    />
                    <NSelect
                      v-else-if="param.name === 'emotion_id'"
                      v-model:value="(stepDraft as any)[param.name]"
                      size="small"
                      filterable
                      :options="EMOJI_OPTIONS"
                    />
                    <NInputNumber v-else-if="param.type === 'number'" v-model:value="(stepDraft as any)[param.name]" size="small" :step="0.1" style="width:100%" />
                    <NSelect
                      v-else-if="param.type === 'select'"
                      v-model:value="(stepDraft as any)[param.name]"
                      size="small"
                      :options="(param.options || []).map((o: any) => ({ label: o.label, value: o.value }))"
                    />
                  </template>
                  <span v-if="param.hint" class="form-hint">{{ param.hint }}</span>
                </div>
              </template>

              <!-- TTS 挂载区：并行动作 / 表情 -->
              <template v-if="stepDraft.type === 'tts'">
                <div class="form-row">
                  <span class="form-label">并行挂载</span>
                  <div class="mount-zone">
                    <div
                      v-for="(m, mi) in draftMotions" :key="'m'+mi"
                      class="mount-item"
                      :class="m.kind === 'linkcraft' ? 'linkcraft-item' : 'motion-item'"
                    >
                      <span v-if="m.kind === 'linkcraft'" class="mount-tag-text">{{ linkcraftLabel(m.resource_key) }}</span>
                      <span v-else class="mount-tag-text">{{ motionLabel(Number(m.motion_id), Number(m.area)) }}</span>
                      <NButton size="tiny" text type="error" @click="removeMount('motion', mi)">✕</NButton>
                    </div>
                    <div
                      v-for="(e, ei) in draftEmojis" :key="'e'+ei"
                      class="mount-item emoji-item"
                    >
                      <span class="mount-tag-text">{{ emojiLabel(e) }}</span>
                      <NButton size="tiny" text type="error" @click="removeMount('emoji', ei)">✕</NButton>
                    </div>
                    <div class="mount-buttons">
                      <NButton size="tiny" dashed @click="openMount('motion')">
                        <template #icon><IconPlus /></template>
                        动作
                      </NButton>
                      <NButton size="tiny" dashed @click="openMount('emoji')">
                        <template #icon><IconPlus /></template>
                        表情
                      </NButton>
                    </div>
                  </div>
                </div>
              </template>
            </div>
          </NScrollbar>
          <div class="config-footer">
            <NButton size="small" type="error" secondary @click="deleteStep(selectedIndex)">
              <template #icon><IconDelete /></template>
              删除步骤
            </NButton>
            <NButton size="small" type="primary" @click="applyStep">
              <template #icon><IconContentSave /></template>
              应用到步骤
            </NButton>
          </div>
        </template>

        <div v-else class="config-empty">
          <IconSettings style="font-size: 40px; opacity: 0.25;" />
          <p>点击左侧步骤卡片，在此配置参数</p>
          <p class="config-empty-sub">或点"添加步骤"开始编排</p>
        </div>
      </div>
    </div>

    <!-- 添加菜单 -->
    <NModal v-model:show="addMenuOpen" preset="card" title="选择步骤类型" style="width:480px">
      <div class="type-grid">
        <div
          v-for="t in STEP_TYPES" :key="t.type"
          class="type-item"
          @click="addStep(t.type)"
        >
          <div class="type-icon" :style="{ background: t.color + '22', color: t.color }">
            <component :is="t.icon" style="font-size:24px" />
          </div>
          <div class="type-label">{{ t.label }}</div>
        </div>
      </div>
    </NModal>

    <!-- 挂载编辑（动作/表情） -->
    <NModal
      v-model:show="mountOpen"
      preset="card"
      :title="mountMode === 'motion' ? '添加并行动作' : '添加并行表情'"
      style="width:380px"
    >
      <div style="display:flex;flex-direction:column;gap:14px">
        <template v-if="mountMode === 'motion'">
          <div class="form-row">
            <span class="form-label">动作来源</span>
            <NRadioGroup v-model:value="mountMotion.kind" size="small">
              <NRadioButton value="preset">预设动作</NRadioButton>
              <NRadioButton value="linkcraft">灵创动作</NRadioButton>
            </NRadioGroup>
          </div>
          <template v-if="mountMotion.kind === 'linkcraft'">
            <div class="form-row">
              <span class="form-label">灵创动作</span>
              <NSelect v-model:value="mountMotion.resource_key" size="small" filterable :options="linkcraftOptions" :placeholder="linkcraftResources.length ? '选择动作' : '未获取到（机器人离线）'" />
            </div>
          </template>
          <template v-else>
            <div class="form-row">
              <span class="form-label">动作</span>
              <NSelect
                :value="motionKey(mountMotion.motion_id, mountMotion.area)"
                size="small" filterable :options="MOTION_OPTIONS"
                @update:value="(v: string) => { const c = parseMotionKey(v); mountMotion.motion_id = c.motion; mountMotion.area = c.area }"
              />
            </div>
          </template>
        </template>
        <template v-else>
          <div class="form-row">
            <span class="form-label">表情</span>
            <NSelect v-model:value="mountEmoji" size="small" filterable :options="EMOJI_OPTIONS" />
          </div>
        </template>
        <div style="display:flex;gap:8px;justify-content:flex-end;margin-top:4px">
          <NButton size="small" @click="mountOpen = false">取消</NButton>
          <NButton size="small" type="primary" @click="saveMount">
            <template #icon><IconPlus /></template>
            添加
          </NButton>
        </div>
      </div>
    </NModal>
  </div>
</template>

<style scoped>
.editor { display: flex; flex-direction: column; height: 660px; }

/* ── 顶部 ── */
.editor-top { display: flex; align-items: center; gap: 10px; padding-bottom: 14px; border-bottom: 1px solid var(--border); margin-bottom: 14px; }

/* ── 左右主体 ── */
.editor-body { flex: 1; display: flex; gap: 14px; min-height: 0; }

.flow-pane, .config-pane {
  display: flex; flex-direction: column; min-height: 0;
  background: var(--bg); border: 1px solid var(--border); border-radius: var(--radius); overflow: hidden;
}
.flow-pane { width: 44%; flex-shrink: 0; }
.config-pane { flex: 1; }

.pane-head { display: flex; align-items: center; justify-content: space-between; padding: 10px 14px; border-bottom: 1px solid var(--border); background: rgba(255,255,255,0.02); }
.pane-title { font-size: 12px; font-weight: 700; color: var(--text-secondary); text-transform: uppercase; letter-spacing: 0.05em; }
.pane-count { font-size: 11px; color: var(--text-secondary); opacity: 0.8; font-family: 'JetBrains Mono', monospace; }
.config-head { justify-content: space-between; }
.pane-scroll { flex: 1; min-height: 0; }

/* ── 左：链路 ── */
.steps-list { display: flex; flex-direction: column; align-items: center; padding: 14px; }

.step-marker {
  padding: 4px 16px; border-radius: 16px; font-size: 11px; font-weight: 700;
  background: #1a3a1a; border: 1px solid #3cc98e; color: #3cc98e;
}
.step-marker.end { background: #1a1a2a; border-color: #4da6ff; color: #4da6ff; }
.connector { width: 2px; height: 14px; background: var(--border); }

.step-card {
  display: flex; flex-direction: column; gap: 8px; width: 100%;
  padding: 10px 12px; background: var(--surface); border: 1px solid var(--border);
  border-radius: var(--radius); cursor: pointer; transition: all 0.15s;
}
.step-card:hover { border-color: var(--accent); background: rgba(77,166,255,0.04); }
.step-card.selected { border-color: var(--accent); background: rgba(77,166,255,0.08); box-shadow: 0 0 10px rgba(77,166,255,0.12); }

.step-main { display: flex; align-items: center; gap: 12px; width: 100%; }
.step-index {
  width: 22px; height: 22px; border-radius: 50%; flex-shrink: 0;
  background: rgba(255,255,255,0.06); display: flex; align-items: center; justify-content: center;
  font-size: 11px; font-weight: 700; color: var(--text-secondary);
}
.step-icon { width: 36px; height: 36px; border-radius: 8px; flex-shrink: 0; display: flex; align-items: center; justify-content: center; }
.step-body { flex: 1; min-width: 0; }
.step-type { font-size: 13px; font-weight: 600; margin-bottom: 2px; }
.step-desc { font-size: 12px; color: var(--text-secondary); overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.step-actions { display: flex; gap: 2px; flex-shrink: 0; opacity: 0.55; transition: opacity 0.15s; }
.step-card:hover .step-actions { opacity: 1; }

.flow-add { padding: 10px 12px; border-top: 1px solid var(--border); }

/* ── 右：配置 ── */
.config-form { display: flex; flex-direction: column; gap: 12px; padding: 14px; }
.config-empty {
  flex: 1; display: flex; flex-direction: column; align-items: center; justify-content: center;
  gap: 10px; color: var(--text-secondary); font-size: 13px;
}
.config-empty p { margin: 0; }
.config-empty-sub { font-size: 11px; opacity: 0.7; }
.config-footer { display: flex; align-items: center; justify-content: space-between; padding: 10px 14px; border-top: 1px solid var(--border); }

/* ── TTS 挂载区 ── */
.mount-zone {
  display: flex; flex-wrap: wrap; gap: 6px; align-items: center;
  padding: 8px 10px; background: rgba(0,0,0,0.18); border: 1px dashed var(--border);
  border-radius: 6px;
}
.mount-item { display: inline-flex; align-items: center; gap: 6px; padding: 2px 8px; border-radius: 12px; font-size: 11px; }
.motion-item { background: rgba(255,152,0,0.14); color: #ffb74d; border: 1px solid rgba(255,152,0,0.3); }
.linkcraft-item { background: rgba(0,172,193,0.14); color: #4dd0e1; border: 1px solid rgba(0,172,193,0.3); }
.emoji-item { background: rgba(233,30,99,0.14); color: #f06292; border: 1px solid rgba(233,30,99,0.3); }
.mount-tag-text { white-space: nowrap; }
.mount-buttons { display: flex; gap: 6px; margin-left: auto; }

/* ── 添加菜单 ── */
.type-grid { display: grid; grid-template-columns: repeat(4, 1fr); gap: 12px; }
.type-item {
  display: flex; flex-direction: column; align-items: center; gap: 6px;
  padding: 16px 8px; background: var(--surface); border: 1px solid var(--border);
  border-radius: var(--radius); cursor: pointer; transition: all 0.15s;
}
.type-item:hover { border-color: var(--accent); transform: translateY(-1px); }
.type-icon { width: 44px; height: 44px; border-radius: 10px; display: flex; align-items: center; justify-content: center; }
.type-label { font-size: 12px; }

/* ── 表单 ── */
.form-row { display: flex; flex-direction: column; gap: 4px; }
.form-row.switch-row { gap: 6px; }
.switch-line { display: flex; align-items: center; justify-content: space-between; gap: 8px; }
.switch-line .form-label { margin: 0; }
.form-label { font-size: 12px; color: var(--text-secondary); font-weight: 600; }
.form-hint { font-size: 11px; color: var(--text-secondary); opacity: 0.7; line-height: 1.5; }
</style>
