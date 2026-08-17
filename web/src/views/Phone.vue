<script setup lang="ts">
import { ref, computed, watch, onMounted, onBeforeUnmount, onDeactivated } from 'vue'
import { useRouter } from 'vue-router'
import { storeToRefs } from 'pinia'
import { wsClient } from '@/api/ws'
import { useConnectionStore } from '@/stores/connection'
import {
  getPhoneKeys, savePhoneKeys, playResource, getResources,
  type PhoneKeySlot, type RobotResource,
} from '@/api/fastapi'
import { NButton, NRadioGroup, NRadioButton, NModal, NSelect, NSpace, useMessage } from 'naive-ui'
import JoystickNipple from '@/components/JoystickNipple.vue'
import IconArrowLeft from '~icons/mdi/arrow-left'
import IconCog from '~icons/mdi/cog'

const router = useRouter()
const message = useMessage()
const conn = useConnectionStore()
const { connected } = storeToRefs(conn)

// ── 按键绑定 ──
const slots = ref<PhoneKeySlot[]>(Array.from({ length: 8 }, (_, i) => ({
  slot: i, name: '', resource_key: '', version: '', resource_type: '',
})))
const playing = ref<number | null>(null)

// ── 设置 modal ──
const settingsOpen = ref(false)
const resources = ref<RobotResource[]>([])
const draft = ref<PhoneKeySlot[]>([])

// ── 速度档（localStorage 持久）──
// SDK v1.0.0（mc_locomotion_velocity.py）各轴范围不同：
//   forward/lateral ±0.2~1.0 m/s，angular ±0.1~1.0 rad/s；< 0.005 视为零；低于最小阈值 mc 不迈步。
// 三轴分别设上限，慢档留余量 > 各自最小阈值。
type Gear = 'slow' | 'mid' | 'fast'
const GEAR: Record<Gear, { forward: number; lateral: number; angular: number }> = {
  slow: { forward: 0.3, lateral: 0.4, angular: 0.3 },
  mid:  { forward: 0.5, lateral: 0.6, angular: 0.5 },
  fast: { forward: 0.8, lateral: 0.8, angular: 0.8 },
}
const gear = ref<Gear>((localStorage.getItem('phone_gear') as Gear) || 'mid')
watch(gear, g => localStorage.setItem('phone_gear', g))
const forwardMax = computed(() => GEAR[gear.value].forward)
const lateralMax = computed(() => GEAR[gear.value].lateral)
const angularMax = computed(() => GEAR[gear.value].angular)

// ── 遥杆状态 + 50ms 合并发速 ──
const leftVec = ref({ x: 0, y: 0 })
const rightVec = ref({ x: 0, y: 0 })
let velTimer: ReturnType<typeof setInterval> | null = null

function clamp(v: number) { return Math.max(-1, Math.min(1, v)) }

function startTimer() {
  if (velTimer) return
  velTimer = setInterval(() => {
    // 对齐 Control.vue：上=+forward / 左=+lateral / 左转=+angular
    // nipplejs：y 上为正(+) → forward +；x 右为正(+) → 取负对齐「左=+lateral」「左转=+angular」
    const fwd = leftVec.value.y * forwardMax.value
    const lat = -leftVec.value.x * lateralMax.value
    const ang = -rightVec.value.x * angularMax.value
    wsClient.sendVelocity(+clamp(fwd).toFixed(2), +clamp(lat).toFixed(2), +clamp(ang).toFixed(2))
  }, 50)
}
function stopTimer() {
  if (velTimer) { clearInterval(velTimer); velTimer = null }
  wsClient.sendVelocity(0, 0, 0)
}
function ensureTimer() {
  const active = !!(leftVec.value.x || leftVec.value.y || rightVec.value.x)
  if (active && connected.value) startTimer()
  else if (!active) stopTimer()
}
function onLeft(v: { x: number; y: number }) { leftVec.value = v; ensureTimer() }
function onRight(v: { x: number; y: number }) { rightVec.value = v; ensureTimer() }

// 断线保护
watch(connected, ok => { if (!ok) stopTimer() })

// ── 8 按键播放灵创动作 ──
async function onPlay(s: PhoneKeySlot, i: number) {
  if (!s.resource_key) { message.warning('该按键未设置，请先在设置中绑定'); return }
  playing.value = i
  try {
    const res = await playResource(s.resource_key, s.version, s.resource_type)
    const failed = !!res.message && /failed|失败/i.test(res.message)
    if (res.ok && !failed) message.success(`播放：${s.name}`)
    else message.warning(res.message || '播放未成功', { duration: 6000 })
  } catch { message.error('播放请求失败') }
  playing.value = null
}

// ── 设置 ──
async function loadKeys() {
  try { const res = await getPhoneKeys(); slots.value = res.keys } catch { /* */ }
}
async function openSettings() {
  draft.value = slots.value.map(s => ({ ...s }))
  if (!resources.value.length) {
    try { const res = await getResources(); resources.value = res.resources || [] } catch { /* */ }
  }
  settingsOpen.value = true
}
const resourceOptions = computed(() => [
  { label: '（未设置）', value: '' },
  ...resources.value.map(r => ({
    label: `${r.name} [${r.resource_key.includes('onnx') ? '全身' : '手臂'}]`,
    value: r.resource_key,
  })),
])
function onSlotChange(idx: number, key: string) {
  const r = resources.value.find(r => r.resource_key === key)
  if (r) {
    draft.value[idx] = {
      slot: idx, name: r.name, resource_key: r.resource_key,
      version: r.version, resource_type: r.resource_key.includes('onnx') ? 'BODY' : 'ARM',
    }
  } else {
    draft.value[idx] = { slot: idx, name: '', resource_key: '', version: '', resource_type: '' }
  }
}
async function saveSettings() {
  try {
    const res = await savePhoneKeys(draft.value)
    slots.value = res.keys
    settingsOpen.value = false
    message.success('设置已保存')
  } catch { message.error('保存失败') }
}

onMounted(loadKeys)
onBeforeUnmount(stopTimer)
onDeactivated(stopTimer)   // keep-alive 切走也停速
</script>

<template>
  <div class="phone">
    <header class="topbar">
      <NButton size="small" quaternary @click="router.push('/')">
        <template #icon><IconArrowLeft /></template>
        首页
      </NButton>
      <NRadioGroup v-model:value="gear" size="small">
        <NRadioButton value="slow">慢</NRadioButton>
        <NRadioButton value="mid">中</NRadioButton>
        <NRadioButton value="fast">快</NRadioButton>
      </NRadioGroup>
      <NButton size="small" quaternary @click="openSettings">
        <template #icon><IconCog /></template>
        设置
      </NButton>
    </header>

    <div v-if="!connected" class="conn-warn">⚠ 未连接机器人，遥控无效</div>

    <section class="keys">
      <button
        v-for="(s, i) in slots" :key="i"
        class="key-btn"
        :class="{ empty: !s.resource_key, busy: playing === i }"
        :disabled="playing === i"
        @click="onPlay(s, i)"
      >
        {{ playing === i ? '播放中…' : (s.name || `按键 ${i + 1}`) }}
      </button>
    </section>

    <section class="sticks">
      <div class="stick">
        <JoystickNipple color="#4da6ff" @move="onLeft" />
        <small>移动 前后/平移</small>
      </div>
      <div class="stick">
        <JoystickNipple color="#3cc98e" @move="onRight" />
        <small>转向 左/右</small>
      </div>
    </section>

    <NModal v-model:show="settingsOpen" preset="card" title="按键设置" style="max-width: 480px;">
      <div class="settings">
        <div v-for="(s, i) in draft" :key="i" class="set-row">
          <span class="set-slot">按键 {{ i + 1 }}</span>
          <NSelect
            :value="s.resource_key"
            :options="resourceOptions"
            size="small"
            @update:value="(v: string) => onSlotChange(i, v)"
          />
        </div>
      </div>
      <template #footer>
        <NSpace justify="end">
          <NButton size="small" @click="settingsOpen = false">取消</NButton>
          <NButton size="small" type="primary" @click="saveSettings">保存</NButton>
        </NSpace>
      </template>
    </NModal>
  </div>
</template>

<style scoped>
.phone {
  display: flex;
  flex-direction: column;
  height: 100vh;
  height: 100dvh;
  background: var(--bg);
  padding: env(safe-area-inset-top) env(safe-area-inset-right) env(safe-area-inset-bottom) env(safe-area-inset-left);
  user-select: none;
  -webkit-user-select: none;
  touch-action: manipulation;
}
.topbar {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 8px 12px;
  border-bottom: 1px solid var(--border);
  flex-shrink: 0;
}
.conn-warn {
  padding: 8px;
  text-align: center;
  color: var(--danger);
  font-size: 13px;
  background: rgba(244, 75, 75, 0.1);
  flex-shrink: 0;
}
.keys {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 10px;
  padding: 12px;
  flex: 1;
  align-content: center;
}
.key-btn {
  padding: 18px 8px;
  font-size: 15px;
  font-weight: 600;
  background: var(--surface);
  color: var(--text);
  border: 1px solid var(--border);
  border-radius: var(--radius);
  cursor: pointer;
  min-height: 56px;
  transition: all 0.1s;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}
.key-btn.empty {
  color: var(--text-secondary);
  font-weight: 400;
  font-size: 13px;
}
.key-btn:active:not(:disabled) {
  background: #1a3a5c;
  border-color: var(--accent);
}
[data-theme="light"] .key-btn:active:not(:disabled) {
  background: rgba(43, 143, 230, 0.14);
}
.key-btn.busy { opacity: 0.6; }
.sticks {
  display: flex;
  justify-content: space-around;
  align-items: center;
  padding: 16px 12px 24px;
  flex-shrink: 0;
  border-top: 1px solid var(--border);
}
.stick {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 6px;
}
.stick small {
  font-size: 12px;
  color: var(--text-secondary);
}
.settings {
  display: flex;
  flex-direction: column;
  gap: 10px;
}
.set-row {
  display: flex;
  align-items: center;
  gap: 10px;
}
.set-slot {
  width: 56px;
  font-size: 13px;
  color: var(--text-secondary);
  flex-shrink: 0;
}
</style>
