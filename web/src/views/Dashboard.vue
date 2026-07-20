<script setup lang="ts">
import { storeToRefs } from 'pinia'
import { useRobotStore } from '@/stores/robot'
import BatteryCard from '@/components/BatteryCard.vue'
import ImuCard from '@/components/ImuCard.vue'
import JointCard from '@/components/JointCard.vue'

const robot = useRobotStore()
const { battery, joints, imu } = storeToRefs(robot)
</script>

<template>
  <div class="dashboard">
    <header class="dash-head">
      <div>
        <h1 class="dash-title">仪表盘</h1>
        <p class="dash-sub">实时监控 X2 运行状态</p>
      </div>
    </header>

    <div class="dash-grid">
      <BatteryCard :battery="battery" />
      <ImuCard :imu="imu" />
      <JointCard :joints="joints" />
    </div>
  </div>
</template>

<style scoped>
.dashboard {
  padding: 32px 0;
}

.dash-head {
  margin-bottom: 28px;
}

.dash-title {
  font-size: 24px;
  font-weight: 700;
  margin: 0 0 4px;
  letter-spacing: -0.02em;
}

.dash-sub {
  margin: 0;
  font-size: 13px;
  color: var(--text-secondary);
}

.dash-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(340px, 1fr));
  gap: 18px;
}
</style>
