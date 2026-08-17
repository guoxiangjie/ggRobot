<script setup lang="ts">
import IconBattery from '~icons/mdi/battery'
import IconBatteryCharging from '~icons/mdi/battery-charging'
import IconLightningBolt from '~icons/mdi/lightning-bolt'
import IconThermometer from '~icons/mdi/thermometer'
import IconGauge from '~icons/mdi/gauge'

defineProps<{
  battery: {
    percentage: number
    voltage: number
    current: number
    temperature: number
    power: number
  }
}>()

function chargeState(current: number): 'charging' | 'discharging' | 'idle' {
  if (current > 0.1) return 'charging'
  if (current < -0.1) return 'discharging'
  return 'idle'
}

function barColor(pct: number): string {
  if (pct > 50) return 'var(--success)'
  if (pct > 20) return '#eab308'
  return 'var(--danger)'
}
</script>

<template>
  <div class="card">
    <div class="card-head">
      <IconBattery class="card-icon" />
      <span class="card-label">电池</span>
    </div>

    <!-- 主电量 -->
    <div class="gauge-row">
      <div class="gauge-ring" :style="{ '--pct': battery.percentage }">
        <svg viewBox="0 0 100 100">
          <circle cx="50" cy="50" r="42" class="ring-bg" />
          <circle
            cx="50" cy="50" r="42"
            class="ring-fill"
            :style="{
              stroke: barColor(battery.percentage),
              strokeDasharray: `${battery.percentage * 2.64} 264`,
            }"
          />
        </svg>
        <div class="ring-value">
          <span class="ring-num">{{ battery.percentage }}</span>
          <span class="ring-unit">%</span>
        </div>
      </div>

      <div class="gauge-stats">
        <div class="stat">
          <IconLightningBolt />
          <span class="stat-label">功率</span>
          <span class="stat-val">{{ battery.power }}<small>W</small></span>
        </div>
        <div class="stat">
          <IconGauge />
          <span class="stat-label">电压</span>
          <span class="stat-val">{{ battery.voltage }}<small>V</small></span>
        </div>
        <div class="stat">
          <IconThermometer />
          <span class="stat-label">温度</span>
          <span class="stat-val">{{ battery.temperature }}<small>℃</small></span>
        </div>
        <div class="stat">
          <IconBatteryCharging />
          <span class="stat-label">状态</span>
          <span
            class="stat-val"
            :style="{ color: chargeState(battery.current) === 'charging' ? 'var(--success)' : chargeState(battery.current) === 'discharging' ? 'var(--text)' : 'var(--text-secondary)' }"
          >
            {{ chargeState(battery.current) === 'charging' ? '充电中' : chargeState(battery.current) === 'discharging' ? '放电中' : '静止' }}
          </span>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.card {
  background: var(--surface);
  border: 1px solid var(--border);
  border-radius: var(--radius);
  padding: 20px;
  transition: border-color 0.2s;
}

.card:hover { border-color: var(--border-hover); }

.card-head {
  display: flex;
  align-items: center;
  gap: 8px;
  margin-bottom: 20px;
  font-size: 14px;
  font-weight: 600;
}

.card-icon { font-size: 20px; color: var(--accent); }
.card-label { color: var(--text); }

/* ring gauge */
.gauge-row {
  display: flex;
  gap: 28px;
  align-items: center;
}

.gauge-ring {
  position: relative;
  width: 110px;
  height: 110px;
  flex-shrink: 0;
}

.gauge-ring svg {
  width: 100%;
  height: 100%;
  transform: rotate(-90deg);
}

.ring-bg {
  fill: none;
  stroke: var(--border);
  stroke-width: 6;
}

.ring-fill {
  fill: none;
  stroke-width: 6;
  stroke-linecap: round;
  transition: stroke-dasharray 0.6s ease, stroke 0.6s ease;
}

.ring-value {
  position: absolute;
  inset: 0;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

.ring-num {
  font-size: 28px;
  font-weight: 700;
  font-family: 'JetBrains Mono', 'SF Mono', monospace;
  line-height: 1;
}

.ring-unit {
  font-size: 12px;
  color: var(--text-secondary);
  margin-top: 2px;
}

/* stats */
.gauge-stats {
  display: flex;
  flex-direction: column;
  gap: 10px;
  flex: 1;
}

.stat {
  display: flex;
  align-items: center;
  gap: 8px;
  font-size: 20px;
}

.stat svg {
  font-size: 16px;
  color: var(--text-secondary);
  flex-shrink: 0;
}

.stat-label {
  font-size: 12px;
  color: var(--text-secondary);
  flex: 1;
}

.stat-val {
  font-family: 'JetBrains Mono', 'SF Mono', monospace;
  font-size: 14px;
  font-weight: 600;
}

.stat-val small {
  font-size: 11px;
  font-weight: 400;
  color: var(--text-secondary);
  margin-left: 2px;
}
</style>
