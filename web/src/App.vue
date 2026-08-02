<script setup lang="ts">
import { onMounted, h, computed, type Component } from 'vue'
import { storeToRefs } from 'pinia'
import { NLayout, NLayoutHeader, NLayoutContent, NMenu, NConfigProvider, NMessageProvider, darkTheme, zhCN, NTag, type MenuOption } from 'naive-ui'
import { useRouter, useRoute } from 'vue-router'
import { useConnectionStore } from '@/stores/connection'
import IconDashboard from '~icons/mdi/view-dashboard-outline'
import IconTask from '~icons/mdi/run'
import IconProject from '~icons/mdi/view-grid-outline'
import IconControl from '~icons/mdi/gamepad-circle-outline'
import IconCamera from '~icons/mdi/webcam'
import IconModel from '~icons/mdi/cube-outline'
import IconMedia from '~icons/mdi/filmstrip-box-multiple'
import IconEmoji from '~icons/mdi/emoticon-outline'
import IconSystem from '~icons/mdi/cog-outline'
import IconLinkcraft from '~icons/mdi/human-handsup'
import IconLanConnect from '~icons/mdi/lan-connect'
import IconLanDisconnect from '~icons/mdi/lan-disconnect'

const router = useRouter()
const route = useRoute()
const conn = useConnectionStore()
const fullscreen = computed(() => !!route.meta.fullscreen)
const { connected, connecting } = storeToRefs(conn)

onMounted(() => {
  conn.autoConnect()
})

function renderIcon(icon: Component) {
  return () => h(icon, { style: { fontSize: '18px' } })
}

const menuOptions: MenuOption[] = [
  { label: '仪表盘', key: 'dashboard', icon: renderIcon(IconDashboard) },
  { label: '控制',   key: 'control',   icon: renderIcon(IconControl) },
  { label: '作业',   key: 'task',      icon: renderIcon(IconTask) },
  { label: '自由',   key: 'project',   icon: renderIcon(IconProject) },
  { label: '相机',   key: 'camera',    icon: renderIcon(IconCamera) },
  { label: '孪生',   key: 'model',     icon: renderIcon(IconModel) },
  { label: '媒体',   key: 'media',     icon: renderIcon(IconMedia) },
  { label: '表情',   key: 'emoji',     icon: renderIcon(IconEmoji) },
  { label: '灵创',   key: 'linkcraft', icon: renderIcon(IconLinkcraft) },
  { label: '系统',   key: 'system',    icon: renderIcon(IconSystem) },
]

function onMenuChange(key: string) {
  router.push({ name: key })
}
</script>

<template>
  <NConfigProvider :theme="darkTheme" :locale="zhCN">
    <NMessageProvider>
    <router-view v-if="fullscreen" v-slot="{ Component }">
      <keep-alive><component :is="Component" /></keep-alive>
    </router-view>
    <NLayout v-else class="app">
      <NLayoutHeader bordered class="topbar-wrap">
        <div class="topbar">
          <span class="brand">ggRobot</span>
          <NMenu
            mode="horizontal"
            :value="(route.name as string)"
            :options="menuOptions"
            @update:value="onMenuChange"
          />
          <div class="conn-status">
            <IconLanConnect v-if="connected" style="color: var(--success);" />
            <IconLanDisconnect v-else style="color: var(--danger);" />
            <NTag :type="connected ? 'success' : 'default'" size="small" round>
              {{ connecting ? '连接中...' : (connected ? '已连接' : '未连接') }}
            </NTag>
          </div>
        </div>
      </NLayoutHeader>
      <NLayoutContent class="main-content" :native-scrollbar="false">
        <div class="content">
          <router-view v-slot="{ Component }">
            <keep-alive>
              <component :is="Component" />
            </keep-alive>
          </router-view>
        </div>
      </NLayoutContent>
    </NLayout>
    </NMessageProvider>
  </NConfigProvider>
</template>

<style>
:root {
  --bg: #090c12;
  --surface: #111620;
  --border: #1c2533;
  --text: #e1e6ed;
  --text-secondary: #8896a9;
  --accent: #4da6ff;
  --danger: #f44b4b;
  --success: #3cc98e;
  --radius: 6px;
}

body {
  margin: 0;
  background: var(--bg);
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
  -webkit-font-smoothing: antialiased;
}

html, body, #app { height: 100%; margin: 0; overflow: hidden; }

.app {
  height: 100vh;
  overflow: hidden;
}

.topbar-wrap {
  height: 52px;
  flex-shrink: 0;
  overflow: hidden;
}

.main-content {
  height: calc(100vh - 52px);
  overflow: hidden;
}

.topbar {
  display: flex;
  align-items: center;
  max-width: 1200px;
  margin: 0 auto;
  padding: 0 12px;
  height: 52px;
  gap: 10px;
}

/* 菜单项间距：menu 已 flex:1 占满中间空间，padding 给宽裕点更舒展 */
.topbar .n-menu-item-content {
  padding-left: 16px !important;
  padding-right: 16px !important;
}

/* 菜单整体水平居中：占满 brand 与 conn-status 之间的剩余空间，items 居中排列 */
.topbar .n-menu {
  flex: 1 1 auto;
  justify-content: center;
}

.content {
  max-width: 1200px;
  margin: 0 auto;
  padding: 0 24px;
}

.brand {
  font-size: 16px;
  font-weight: 700;
  white-space: nowrap;
  letter-spacing: -0.01em;
  flex-shrink: 0;
}

.conn-status {
  display: flex;
  align-items: center;
  gap: 6px;
  font-size: 13px;
  flex-shrink: 0;
  margin-left: auto;
}
</style>
