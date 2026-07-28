/** 连接状态 — 由 wsClient 的重连/断开回调驱动，订阅注册幂等 */

import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import { wsClient } from '@/api/ws'
import { useRobotStore } from '@/stores/robot'

export const useConnectionStore = defineStore('connection', () => {
  const connected = ref(false)
  const connecting = ref(false)
  const error = ref<string | null>(null)
  let _hooked = false   // 回调是否已挂载（幂等，避免重复绑定）

  const statusText = computed(() => {
    if (connecting.value) return '连接中...'
    if (connected.value) return '已连接'
    return '未连接'
  })

  /** 连上后恢复传感器订阅（幂等：onSensor 是 Set，重复注册安全） */
  function onUp() {
    connected.value = true
    connecting.value = false
    error.value = null
    useRobotStore().startSubscriptions()
  }

  function onDown() {
    connected.value = false
  }

  function connect() {
    connecting.value = true
    error.value = null

    // 一次性挂载回调：wsClient.onReconnect/onDisconnect 现在是 Set，重复 add 安全
    if (!_hooked) {
      wsClient.onReconnect(onUp)
      wsClient.onDisconnect(onDown)
      _hooked = true
    }

    wsClient.disconnect()
    wsClient.connect()

    // 超时兜底：10s 内未连上则报错（连接成功后由 onUp 清除 connecting）
    setTimeout(() => {
      if (!wsClient.connected && connecting.value) {
        connecting.value = false
        error.value = 'WebSocket 连接超时'
      }
    }, 10000)
  }

  function disconnect() {
    wsClient.disconnect()
    connected.value = false
  }

  function autoConnect() {
    connect()
  }

  return { connected, connecting, error, statusText, connect, disconnect, autoConnect }
})
