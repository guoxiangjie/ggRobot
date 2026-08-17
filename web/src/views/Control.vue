<script setup lang="ts">
import { ref, watch, computed, onMounted, onBeforeUnmount } from 'vue'
import { useMagicKeys } from '@vueuse/core'
import TtsPanel from '@/components/TtsPanel.vue'
import MotionPanel from '@/components/MotionPanel.vue'
import VolumePanel from '@/components/VolumePanel.vue'
import { wsClient } from '@/api/ws'
import { switchMode, playTts, showLogo, hideLogo, getSystem, migrateSystemState } from '@/api/fastapi'
import { NButton, NPopconfirm, NSwitch, NSlider, NSelect, NTag, NModal, NInput, NSpace, useMessage } from 'naive-ui'
import IconArrowUpBold from '~icons/mdi/arrow-up-bold'
import IconArrowDownBold from '~icons/mdi/arrow-down-bold'
import IconArrowLeftBold from '~icons/mdi/arrow-left-bold'
import IconArrowRightBold from '~icons/mdi/arrow-right-bold'
import IconUndo from '~icons/mdi/undo-variant'
import IconRedo from '~icons/mdi/redo-variant'
import IconCellphone from '~icons/mdi/cellphone'
const keys = useMagicKeys()
const { w, a, s, d, q, e } = keys
const moveSpeed = ref(0.4)
const turnSpeed = ref(0.4)

// ── 运动开关 ──
const motorEnabled = ref(false)
let velTimer: ReturnType<typeof setInterval> | null = null

watch(motorEnabled, (on) => {
  playTts({ text: on ? '开启运动控制' : '关闭运动控制' })
  if (on) {
    velTimer = setInterval(() => {
      const ms = moveSpeed.value; const ts = turnSpeed.value
      const fwd = (w.value ? ms : 0) + (s.value ? -ms : 0)
      const lat = (a.value ? ms : 0) + (d.value ? -ms : 0)
      const ang = (q.value ? ts : 0) + (e.value ? -ts : 0)
      wsClient.sendVelocity(+fwd.toFixed(1), +lat.toFixed(1), +ang.toFixed(1))
    }, 50)
  } else {
    if (velTimer) { clearInterval(velTimer); velTimer = null }
    wsClient.sendVelocity(0, 0, 0)
  }
})

// ── 模式切换 ──
// v0.8.2+ 用 action_desc 字符串；但 SIT_DOWN/ZERO_TORQUE 后端不认字符串，
// 必须带 value 数字 ID（api_reference McAction.value：4=ZERO_TORQUE 2000=SIT_DOWN）
const modes: { id: string; label: string; icon: string; danger: boolean; value?: number }[] = [
  { id: 'DAMPING_DEFAULT', label: '阻尼', icon: '🛡️', danger: false },
  { id: 'STAND_DEFAULT', label: '站立', icon: '🧍', danger: false },
  { id: 'LOCOMOTION_DEFAULT', label: '行走', icon: '🚶', danger: false },
  { id: 'SIT_DOWN_DEFAULT', label: '坐下', icon: '🪑', danger: false, value: 2000 },
  { id: 'ZERO_TORQUE_DEFAULT', label: '零力矩', icon: '⚠️', danger: true, value: 4 },
]
const activeMode = ref<string | null>(null)

async function setMode(id: string) {
  activeMode.value = id
  try {
    const m = modes.find(m => m.id === id)
    await switchMode(id, m?.value)
  } catch { /* */ }
  activeMode.value = null
}

// ── 脸屏 Logo ──
const logoShown = ref(false)
async function toggleLogo(on: boolean) {
  try {
    await (on ? showLogo() : hideLogo())
  } catch {
    logoShown.value = !on  // 失败回退开关状态
  }
}

// 手机控制入口（新窗口打开 /phone 全屏遥控页，不影响当前桌面控制台）
function openPhone() {
  window.open('/phone', '_blank')
}

// ── 开发者模式（系统状态迁移）──
const message = useMessage()
const currentDevState = ref<string>('')        // 当前系统态（GetSystemState.cur_state）
const selectedState = ref<string | null>(null) // NSelect 选中的目标态
const migrating = ref(false)
const confirmOpen = ref(false)
const mcInput = ref('')

const devOptions = [
  { label: '✅ Ready · 恢复默认（退出开发者模式）', value: 'Ready', danger: 'low' as const },
  { label: '🔊 Develop_Audio_Linux · 停用 hal_audio', value: 'Develop_Audio_Linux', danger: 'low' as const },
  { label: '🔊 Develop_Audio_ROS · 停用 agent', value: 'Develop_Audio_ROS', danger: 'low' as const },
  { label: '🧭 Develop_Nav · 停用导航/建图/规划/感知', value: 'Develop_Nav', danger: 'mid' as const },
  { label: '⚠️ Develop_MC · 停用运动控制（极危）', value: 'Develop_MC', danger: 'high' as const },
]
const selectedOpt = computed(() => devOptions.find(o => o.value === selectedState.value))
// 判断是否开发者模式：只有 Develop_ 前缀才算。
// ⚠️ 机器正常业务态 cur_state 实测为 "Business"（非文档说的 "Ready"），不能用 !=='Ready' 判断。
const inDevMode = computed(() => currentDevState.value.startsWith('Develop_'))

function stateTagType(s: string): 'success' | 'warning' | 'error' {
  if (s.startsWith('Develop_')) return s.includes('Audio') ? 'warning' : 'error'  // Nav / MC
  return 'success'  // Ready / Business / 其他正常态
}
function stateLabel(s: string): string {
  const o = devOptions.find(o => o.value === s)
  if (o) return o.label
  if (!s) return '未知'
  // 非开发者模式的正常态（如实测的 Business）友好显示
  return s.startsWith('Develop_') ? s : `正常态（${s}）`
}

async function refreshDevState() {
  try {
    const sys = await getSystem()
    currentDevState.value = sys.system?.state ?? ''
  } catch { /* 离线 */ }
}

// 迁移可能跨板较慢、后端轮询窗口内未完成；前端兜底轮询直到状态变化或超时
let statePollTimer: ReturnType<typeof setInterval> | null = null
function startStatePolling() {
  stopStatePolling()
  const before = currentDevState.value
  let tries = 0
  statePollTimer = setInterval(async () => {
    tries++
    await refreshDevState()
    if (currentDevState.value !== before || tries >= 12) stopStatePolling()  // 状态变化或 ~24s 后停
  }, 2000)
}
function stopStatePolling() {
  if (statePollTimer) { clearInterval(statePollTimer); statePollTimer = null }
}

function openConfirm() {
  if (!selectedState.value || migrating.value) return
  if (selectedState.value === currentDevState.value) return
  mcInput.value = ''
  confirmOpen.value = true
}

async function doMigrate() {
  if (!selectedState.value) return
  migrating.value = true
  try {
    const res = await migrateSystemState(selectedState.value)
    if (res.ok && res.in_progress) {
      message.info('迁移已发起，仍在进行中，自动刷新当前态…', { duration: 6000 })
      startStatePolling()
    } else if (res.ok) {
      message.success(`已切换到 ${stateLabel(res.state ?? selectedState.value)}`)
      currentDevState.value = res.state ?? selectedState.value
    } else {
      message.warning(res.message || '切换未成功', { duration: 6000 })
      refreshDevState()
    }
  } catch {
    message.error('切换请求失败')
  } finally {
    migrating.value = false
    confirmOpen.value = false
  }
}

onMounted(refreshDevState)
onBeforeUnmount(stopStatePolling)
</script>

<template>
  <div class="control">
    <header class="ctrl-head">
      <div>
        <h1 class="ctrl-title">控制</h1>
        <p class="ctrl-sub">语音播报 · 预设动作 · 移动遥控</p>
      </div>
      <div class="ctrl-actions">
        <NButton size="small" quaternary @click="openPhone">
          <template #icon><IconCellphone /></template>
          手机控制
        </NButton>
        <div class="logo-ctrl">
          <span class="logo-label">脸屏 Logo</span>
          <NSwitch v-model:value="logoShown" @update:value="toggleLogo" size="small" />
        </div>
      </div>
    </header>

    <div class="ctrl-grid">
      <TtsPanel />
      <MotionPanel />
      <VolumePanel />

      <!-- 开发者模式（系统级 · 高危）：放在音量面板右侧 -->
      <div class="dev-card-wrap">
        <div class="dev-head">
          <span class="dev-title">⚠ 开发者模式（系统级 · 高危）</span>
          <div class="dev-state">
            <span class="dev-cap">当前</span>
            <NTag :type="stateTagType(currentDevState)" size="small" round>
              {{ stateLabel(currentDevState) || '未知' }}
            </NTag>
          </div>
        </div>
        <div v-if="inDevMode" class="dev-warn">
          ⚠ 机器人处于开发者模式（{{ stateLabel(currentDevState) }}），部分原生能力已停用。完成开发后请切回 Ready 或重启。
        </div>
        <div class="dev-row">
          <NSelect
            v-model:value="selectedState"
            :options="devOptions"
            size="small"
            placeholder="选择目标模式"
            style="flex: 1; min-width: 220px;"
          />
          <NButton
            size="small"
            type="warning"
            :loading="migrating"
            :disabled="!selectedState || selectedState === currentDevState || migrating"
            @click="openConfirm"
          >切换</NButton>
          <NButton size="small" quaternary :loading="migrating" @click="refreshDevState">刷新</NButton>
        </div>
        <p class="dev-hint">Develop_MC 会停用原生运动控制，机器人可能摔倒；Develop_Nav 停用自主导航/感知。完成后务必切回 Ready。</p>
      </div>
    </div>

    <!-- 遥控 + 模式 同行 -->
    <div class="section-label">
      遥控与模式
      <NSwitch v-model:value="motorEnabled" size="small" style="margin-left:12px;" />
      <span class="motor-state" :style="{ color: motorEnabled ? 'var(--success)' : 'var(--danger)' }">
        {{ motorEnabled ? '已开启' : '已关闭' }}
      </span>
    </div>
    <div class="remote-row" :class="{ disabled: !motorEnabled }">
      <!-- 方向控制 -->
      <div class="dpad-wrap">
      <div class="dpad">
        <!-- 前 W -->
        <button class="dpad-btn" :disabled="!motorEnabled" :class="{ active: w && motorEnabled }" style="grid-area: up;">
          <IconArrowUpBold />
          <small>W</small>
        </button>
        <!-- 左转 Q -->
        <button class="dpad-btn rot" :disabled="!motorEnabled" :class="{ active: q && motorEnabled }" style="grid-area: lt;">
          <IconUndo /><small>Q</small>
        </button>
        <!-- 中心 -->
        <div class="dpad-center" style="grid-area: ct;"></div>
        <!-- 右转 E -->
        <button class="dpad-btn rot" :disabled="!motorEnabled" :class="{ active: e && motorEnabled }" style="grid-area: rt;">
          <IconRedo /><small>E</small>
        </button>
        <!-- 后 S -->
        <button class="dpad-btn" :disabled="!motorEnabled" :class="{ active: s && motorEnabled }" style="grid-area: dn;">
          <IconArrowDownBold />
          <small>S</small>
        </button>
        <!-- 左 A -->
        <button class="dpad-btn" :disabled="!motorEnabled" :class="{ active: a && motorEnabled }" style="grid-area: lt2;">
          <IconArrowLeftBold /><small>A</small>
        </button>
        <!-- 右 D -->
        <button class="dpad-btn" :disabled="!motorEnabled" :class="{ active: d && motorEnabled }" style="grid-area: rt2;">
          <IconArrowRightBold /><small>D</small>
        </button>
      </div>
      <div class="dpad-desc">
        <div><kbd>W</kbd><kbd>S</kbd> 前后</div>
        <div><kbd>A</kbd><kbd>D</kbd> 横移</div>
        <div><kbd>Q</kbd><kbd>E</kbd> 转向</div>
        <div class="speed-ctls">
          <div class="speed-item">
            <span>移速 {{ moveSpeed.toFixed(1) }}</span>
            <NSlider v-model:value="moveSpeed" :min="0.2" :max="1.0" :step="0.1" style="width:100px;" :disabled="!motorEnabled" />
          </div>
          <div class="speed-item">
            <span>转速 {{ turnSpeed.toFixed(1) }}</span>
            <NSlider v-model:value="turnSpeed" :min="0.1" :max="1.0" :step="0.1" style="width:100px;" :disabled="!motorEnabled" />
          </div>
        </div>
        <div class="dpad-note">按键按下即亮，松开自动停止</div>
      </div>
      </div>

      <!-- 模式切换 -->
      <div class="mode-col">
        <NPopconfirm
          v-for="m in modes" :key="m.id"
          @positive-click="setMode(m.id)"
        >
          <template #trigger>
            <NButton
              size="small"
              :type="activeMode === m.id ? 'warning' : (m.danger ? 'error' : 'default')"
              :loading="activeMode === m.id"
              :disabled="!motorEnabled"
            >{{ m.icon }} {{ m.label }}</NButton>
          </template>
          <span v-if="m.danger" style="color: var(--danger); font-weight: 600;">
            ⚠ 「{{ m.label }}」会让机器人失力摔倒！确认？
          </span>
          <span v-else>确认切换到「{{ m.label }}」模式？</span>
        </NPopconfirm>
      </div>
    </div>

    <!-- 确认弹窗（分级：低危普通提示 / 中危红字警告 / MC 强制输入"MC"）-->
    <NModal
      v-model:show="confirmOpen"
      preset="card"
      :title="selectedOpt?.danger === 'high' ? '⚠ 极危操作确认' : '切换确认'"
      style="max-width: 460px;"
    >
      <div class="confirm-body">
        <template v-if="selectedOpt?.danger === 'high'">
          <p class="confirm-danger">⚠ 此操作将停用原生运动控制（Develop_MC），机器人会失去站立/行走保护，<b>可能摔倒</b>！</p>
          <p style="margin: 8px 0;">确认请输入 <b>MC</b>：</p>
          <NInput v-model:value="mcInput" placeholder="输入 MC 确认" />
        </template>
        <p v-else-if="selectedOpt?.danger === 'mid'" class="confirm-danger">
          ⚠ 将停用机器人自主导航/建图/规划/感知能力，确认切换？
        </p>
        <p v-else>确认切换到「{{ selectedOpt?.label }}」？</p>
      </div>
      <template #footer>
        <NSpace justify="end">
          <NButton size="small" @click="confirmOpen = false">取消</NButton>
          <NButton
            size="small"
            :type="selectedOpt?.danger === 'high' ? 'error' : 'primary'"
            :disabled="selectedOpt?.danger === 'high' && mcInput !== 'MC'"
            :loading="migrating"
            @click="doMigrate"
          >确认切换</NButton>
        </NSpace>
      </template>
    </NModal>
  </div>
</template>

<style scoped>
.control { padding: 32px 0; }
.ctrl-head { display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; }
.ctrl-actions { display: flex; align-items: center; gap: 16px; }
.logo-ctrl { display: flex; align-items: center; gap: 8px; }
.logo-label { font-size: 13px; color: var(--text-secondary); }
.ctrl-title { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.ctrl-sub { margin: 0; font-size: 13px; color: var(--text-secondary); }

.section-label { font-size: 13px; font-weight: 600; color: var(--text-secondary); margin-bottom: 10px; margin-top: 24px; }
.section-label:first-of-type { margin-top: 0; }

.ctrl-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(340px, 1fr)); gap: 18px; margin-bottom: 10px; }

.remote-row { display: flex; gap: 40px; align-items: flex-start; flex-wrap: wrap; }
.remote-row.disabled { opacity: 0.4; pointer-events: none; }
.motor-state { font-size: 12px; font-weight: 600; margin-left: 8px; vertical-align: middle; }

/* ── D-Pad ── */
.dpad-wrap { display: flex; gap: 32px; align-items: flex-start; }

.mode-col { display: flex; flex-direction: column; gap: 8px; padding-top: 12px; }
.dpad {
  display: grid;
  grid-template-areas:
    ".   up   .  "
    "lt  ct   rt "
    "lt2 dn   rt2";
  grid-template-columns: repeat(3, 80px);
  grid-template-rows: repeat(3, 80px);
  gap: 6px;
}

.dpad-btn {
  display: flex; flex-direction: column; align-items: center; justify-content: center;
  gap: 2px;
  background: var(--surface);
  border: 1px solid var(--border);
  border-radius: var(--radius);
  color: var(--text-secondary);
  cursor: pointer;
  transition: all 0.1s;
  font-size: 24px;
  user-select: none;
}

.dpad-btn.rot { font-size: 22px; }

.dpad-btn small {
  font-size: 10px;
  font-family: 'JetBrains Mono', monospace;
  font-weight: 600;
}

.dpad-btn.active {
  background: #1a3a5c;
  border-color: var(--accent);
  color: var(--accent);
  box-shadow: 0 0 12px rgba(77, 166, 255, 0.35);
}
[data-theme="light"] .dpad-btn.active {
  background: rgba(43, 143, 230, 0.14);
  box-shadow: 0 0 12px rgba(43, 143, 230, 0.25);
}

.dpad-center {
  background: transparent;
  border: 1px dashed var(--border);
  border-radius: 50%;
}

.dpad-desc {
  display: flex; flex-direction: column; gap: 6px;
  font-size: 13px; color: var(--text-secondary);
  padding-top: 12px;
}

.dpad-desc kbd {
  display: inline-block;
  background: var(--surface); border: 1px solid var(--border);
  border-radius: 3px; padding: 1px 6px;
  font-family: 'JetBrains Mono', monospace; font-size: 11px;
  margin-right: 4px;
}

.speed-ctls { margin-top: 8px; display: flex; flex-direction: column; gap: 4px; }
.speed-item { display: flex; align-items: center; gap: 8px; font-size: 12px; color: var(--text-secondary); }
.dpad-note { margin-top: 8px; font-size: 11px; color: var(--text-muted, #556270); }

/* ── 开发者模式 ── */
.dev-card-wrap {
  grid-column: span 2;
  background: var(--surface); border: 1px solid var(--border);
  border-radius: var(--radius); padding: 20px;
}
.dev-head { display: flex; align-items: center; justify-content: space-between; gap: 10px; margin-bottom: 12px; flex-wrap: wrap; }
.dev-title { font-size: 14px; font-weight: 600; color: var(--danger); }
.dev-warn {
  margin-bottom: 10px; padding: 8px 12px;
  background: rgba(244, 75, 75, 0.1); border: 1px solid rgba(244, 75, 75, 0.3);
  border-radius: var(--radius);
  color: var(--danger); font-size: 13px;
}
.dev-row { display: flex; align-items: center; gap: 12px; flex-wrap: wrap; }
.dev-state { display: flex; align-items: center; gap: 8px; }
.dev-cap { font-size: 12px; color: var(--text-secondary); }
.dev-hint { margin: 10px 0 0; font-size: 11px; color: var(--text-muted, #556270); line-height: 1.5; }
.confirm-body { font-size: 14px; line-height: 1.6; }
.confirm-danger { color: var(--danger); font-weight: 500; margin: 0; }
</style>
