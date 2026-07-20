/** 机器人传感器状态 — 通过 WebSocket 接收后端推送 */

import { defineStore } from 'pinia'
import { ref } from 'vue'
import { wsClient } from '@/api/ws'

export const useRobotStore = defineStore('robot', () => {
  const battery = ref({ percentage: 0, voltage: 0, current: 0, temperature: 0, power: 0 })
  const joints = ref<Record<string, { position: number; velocity: number }>>({})
  const imu = ref({ accel_x: 0, accel_y: 0, accel_z: 0 })

  function handleSensor(payload: any) {
    if (payload.battery) {
      battery.value = {
        percentage: payload.battery.percentage,
        voltage: payload.battery.voltage,
        current: payload.battery.current,
        temperature: payload.battery.temperature,
        power: payload.battery.power,
      }
    }
    if (payload.arms) {
      for (const j of payload.arms) {
        joints.value[j.name] = { position: j.position, velocity: j.velocity }
      }
    }
    if (payload.imu) {
      imu.value = {
        accel_x: payload.imu.accel_x,
        accel_y: payload.imu.accel_y,
        accel_z: payload.imu.accel_z,
      }
    }
  }

  function startSubscriptions() {
    wsClient.onSensor(handleSensor)
  }

  function stopSubscriptions() {
    wsClient.offSensor(handleSensor)
  }

  return { battery, joints, imu, startSubscriptions, stopSubscriptions }
})
