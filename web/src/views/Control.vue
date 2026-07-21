<script setup lang="ts">
import { ref, watch } from 'vue'
import { useMagicKeys } from '@vueuse/core'
import TtsPanel from '@/components/TtsPanel.vue'
import MotionPanel from '@/components/MotionPanel.vue'
import VolumePanel from '@/components/VolumePanel.vue'
import { wsClient } from '@/api/ws'
import { switchMode, playTts, showLogo, hideLogo } from '@/api/fastapi'
import { NButton, NPopconfirm, NSwitch, NSlider } from 'naive-ui'
import IconArrowUpBold from '~icons/mdi/arrow-up-bold'
import IconArrowDownBold from '~icons/mdi/arrow-down-bold'
import IconArrowLeftBold from '~icons/mdi/arrow-left-bold'
import IconArrowRightBold from '~icons/mdi/arrow-right-bold'
import IconUndo from '~icons/mdi/undo-variant'
import IconRedo from '~icons/mdi/redo-variant'
const keys = useMagicKeys()
const { w, a, s, d, q, e } = keys
const moveSpeed = ref(0.3)
const turnSpeed = ref(0.3)

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
// v0.8.2+ 用 action_desc 字符串（非数字ID）
const modes = [
  { id: 'DAMPING_DEFAULT', label: '阻尼', icon: '🛡️' },
  { id: 'STAND_DEFAULT', label: '站立', icon: '🧍' },
  { id: 'LOCOMOTION_DEFAULT', label: '行走', icon: '🚶' },
]
const activeMode = ref<string | null>(null)

async function setMode(id: string) {
  activeMode.value = id
  try { await switchMode(id) } catch { /* */ }
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
</script>

<template>
  <div class="control">
    <header class="ctrl-head">
      <div>
        <h1 class="ctrl-title">控制</h1>
        <p class="ctrl-sub">语音播报 · 预设动作 · 移动遥控</p>
      </div>
      <div class="logo-ctrl">
        <span class="logo-label">脸屏 Logo</span>
        <NSwitch v-model:value="logoShown" @update:value="toggleLogo" size="small" />
      </div>
    </header>

    <div class="ctrl-grid">
      <TtsPanel />
      <MotionPanel />
      <VolumePanel />
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
            <NSlider v-model:value="moveSpeed" :min="0.1" :max="0.8" :step="0.1" style="width:100px;" :disabled="!motorEnabled" />
          </div>
          <div class="speed-item">
            <span>转速 {{ turnSpeed.toFixed(1) }}</span>
            <NSlider v-model:value="turnSpeed" :min="0.1" :max="0.8" :step="0.1" style="width:100px;" :disabled="!motorEnabled" />
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
              :type="activeMode === m.id ? 'warning' : 'default'"
              :loading="activeMode === m.id"
              :disabled="!motorEnabled"
            >{{ m.icon }} {{ m.label }}</NButton>
          </template>
          确认切换到「{{ m.label }}」模式？
        </NPopconfirm>
      </div>
    </div>
  </div>
</template>

<style scoped>
.control { padding: 32px 0; }
.ctrl-head { display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; }
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
</style>
