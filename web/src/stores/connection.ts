/** 连接状态 — 自动检测 WebSocket 连通性 */

import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import { wsClient } from '@/api/ws'
import { useRobotStore } from '@/stores/robot'

export const useConnectionStore = defineStore('connection', () => {
  const connected = ref(false)
  const connecting = ref(false)
  const error = ref<string | null>(null)

  const statusText = computed(() => {
    if (connecting.value) return '连接中...'
    if (connected.value) return '已连接'
    return '未连接'
  })

  function connect() {
    connecting.value = true
    error.value = null
    wsClient.disconnect()
    wsClient.connect()

    // 轮询等待连接
    const timer = setInterval(() => {
      if (wsClient.connected) {
        clearInterval(timer)
        connected.value = true
        connecting.value = false
        useRobotStore().startSubscriptions()
      }
    }, 200)

    // 超时
    setTimeout(() => {
      if (!wsClient.connected && connecting.value) {
        clearInterval(timer)
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
