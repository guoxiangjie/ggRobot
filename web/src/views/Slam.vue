<script setup lang="ts">
import { ref, computed, onMounted, onBeforeUnmount, watch, nextTick } from 'vue'
import { NButton, NSelect, NInput, NInputNumber, NTag, useMessage } from 'naive-ui'
import {
  getMapList, getSlamMap, startMapping, stopMapping, relocalize, getSlamPose, getSlamOrigin,
  type SlamMap, type SlamMapData,
} from '@/api/fastapi'
import IconMap from '~icons/mdi/map'
import IconRefresh from '~icons/mdi/refresh'
import IconPlay from '~icons/mdi/play'
import IconStop from '~icons/mdi/stop'

const message = useMessage()

// ── 地图列表 ──
const maps = ref<SlamMap[]>([])
const mapOptions = computed(() => maps.value.map(m => ({ label: `${m.map_name} (id:${m.map_id})`, value: m.map_name })))
const selectedMap = ref<string | null>(null)
async function loadMaps() {
  try {
    const r = await getMapList()
    maps.value = r.maps
    if (r.error) message.warning(r.error)
  } catch { /* */ }
}

// ── 取图展示（PNG + canvas 叠加导航点/虚拟墙）──
const mapData = ref<SlamMapData | null>(null)
const mapImgUrl = ref('')
const loadingMap = ref(false)
const canvasRef = ref<HTMLCanvasElement>()
async function onSelectMap(name: string | null) {
  if (!name) { mapData.value = null; mapImgUrl.value = ''; return }
  loadingMap.value = true
  try {
    const r = await getSlamMap(name)
    mapData.value = r
    if (r.ok && r.map_base64) mapImgUrl.value = `data:image/png;base64,${r.map_base64}`
    else message.warning(r.error || '取图失败')
  } catch { message.error('取图请求失败') }
  loadingMap.value = false
}
watch(mapImgUrl, async () => { await nextTick(); drawOverlay() })
function drawOverlay() {
  const cv = canvasRef.value; const d = mapData.value
  if (!cv || !d?.map_info) return
  cv.width = d.map_info.width; cv.height = d.map_info.height
  const ctx = cv.getContext('2d'); if (!ctx) return
  ctx.clearRect(0, 0, cv.width, cv.height)
  ctx.fillStyle = '#3cc98e'
  for (const p of d.navi_points || []) { ctx.beginPath(); ctx.arc(p.x, p.y, 6, 0, Math.PI * 2); ctx.fill() }
  ctx.strokeStyle = '#f44b4b'; ctx.lineWidth = 4
  for (const r of d.regions || []) {
    if (r.type !== 2 || !r.polygon?.length) continue
    ctx.beginPath()
    r.polygon.forEach((pt, i) => { i ? ctx.lineTo(pt[0], pt[1]) : ctx.moveTo(pt[0], pt[1]) })
    if (r.drawing_type === 1) ctx.closePath()
    ctx.stroke()
  }
}

// ── 建图 ──
const mapping = ref(false)
const mapName = ref('')
async function doStart() {
  try { await startMapping(); mapping.value = true; message.success('开始建图，遥控机器人走一圈') }
  catch { message.error('请求失败') }
}
async function doStop() {
  if (!mapName.value.trim()) { message.warning('请输入地图名称'); return }
  try {
    await stopMapping(mapName.value.trim())
    mapping.value = false; message.success(`已保存：${mapName.value}`)
    mapName.value = ''; loadMaps()
  } catch { message.error('请求失败') }
}

// ── 重定位 ──
const relocOptions = computed(() => maps.value.map(m => ({ label: `${m.map_name} (id:${m.map_id})`, value: m.map_id })))
const relocMapId = ref<string | null>(null)
const relocX = ref(0)
const relocY = ref(0)
const relocating = ref(false)
async function loadOrigin() {
  if (!relocMapId.value) return
  try {
    const r = await getSlamOrigin(relocMapId.value)
    if (r.ok && r.lines && r.lines[1]) {
      const nums = r.lines[1].match(/[-\d.]+/g)
      if (nums && nums.length >= 2) { relocX.value = Number(nums[0]); relocY.value = Number(nums[1]) }
      message.info(`origin: ${r.lines[1]}（已尝试解析为 x/y）`, { duration: 5000 })
    }
  } catch { /* */ }
}
watch(relocMapId, loadOrigin)
async function doRelocalize() {
  if (!relocMapId.value) { message.warning('请选择地图'); return }
  relocating.value = true
  try {
    const r = await relocalize(relocMapId.value, relocX.value, relocY.value)
    if (r.ok) message.success(`重定位成功：x=${r.pose?.x} y=${r.pose?.y}`)
    else message.warning(r.error || '重定位失败', { duration: 8000 })
  } catch { message.error('重定位请求失败') }
  relocating.value = false
}

// ── 实时位姿 ──
const slamPose = ref<Record<string, number>>({})
let poseTimer: ReturnType<typeof setInterval> | null = null
async function pollPose() {
  try { const r = await getSlamPose(); slamPose.value = r.pose || {} } catch { /* */ }
}
function startPoll() { stopPoll(); poseTimer = setInterval(pollPose, 500) }
function stopPoll() { if (poseTimer) { clearInterval(poseTimer); poseTimer = null } }

onMounted(() => { loadMaps(); startPoll() })
onBeforeUnmount(stopPoll)
</script>

<template>
  <div class="slam">
    <header class="head">
      <div>
        <h1><IconMap style="vertical-align:middle" /> 建图与定位</h1>
        <p>SLAM 建图 / 地图查看 / 重定位（导航到点 SDK 未开放，暂不含）</p>
      </div>
      <NButton size="small" quaternary @click="loadMaps"><template #icon><IconRefresh /></template>刷新地图列表</NButton>
    </header>

    <div class="grid">
      <!-- 建图 -->
      <div class="card">
        <div class="card-label">建图</div>
        <div class="mapping-row">
          <NButton v-if="!mapping" size="small" type="primary" @click="doStart"><template #icon><IconPlay /></template>开始建图</NButton>
          <template v-else>
            <NInput v-model:value="mapName" placeholder="地图名称" size="small" style="width:140px" />
            <NButton size="small" type="error" @click="doStop"><template #icon><IconStop /></template>停止并保存</NButton>
          </template>
          <NTag v-if="mapping" type="warning" size="small" round>建图中…遥控机器人走一圈</NTag>
        </div>
      </div>

      <!-- 重定位 -->
      <div class="card">
        <div class="card-label">重定位</div>
        <div class="reloc-row">
          <NSelect v-model:value="relocMapId" :options="relocOptions" placeholder="选择地图" size="small" style="width:200px" />
          <NInputNumber v-model:value="relocX" placeholder="x(像素)" size="small" />
          <NInputNumber v-model:value="relocY" placeholder="y(像素)" size="small" />
          <NButton size="small" type="primary" :loading="relocating" @click="doRelocalize">重定位</NButton>
        </div>
      </div>

      <!-- 实时位姿 -->
      <div class="card">
        <div class="card-label">实时位姿 (lidar_odom)</div>
        <div class="pose">
          <NTag v-if="slamPose.ts" size="small" type="success" round>已定位</NTag>
          <NTag v-else size="small" type="default" round>无数据</NTag>
          <span v-if="slamPose.ts" class="pose-val">x={{ slamPose.x }} y={{ slamPose.y }}</span>
        </div>
      </div>
    </div>

    <!-- 地图展示 -->
    <div class="card map-card">
      <div class="card-label">地图查看（导航点绿色 / 虚拟墙红色）</div>
      <div class="map-ctrl">
        <NSelect v-model:value="selectedMap" :options="mapOptions" placeholder="选择地图查看" size="small" style="width:280px" @update:value="onSelectMap" />
        <NButton size="small" quaternary :loading="loadingMap" @click="selectedMap && onSelectMap(selectedMap)"><template #icon><IconRefresh /></template>刷新</NButton>
      </div>
      <div v-if="mapImgUrl" class="map-view">
        <img :src="mapImgUrl" class="map-img" />
        <canvas ref="canvasRef" class="map-canvas"></canvas>
      </div>
      <div v-else-if="mapData && !mapData.ok" class="map-err">{{ mapData.error }}</div>
      <div v-else class="map-empty">选择一张地图查看</div>
    </div>
  </div>
</template>

<style scoped>
.slam { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 24px; gap: 12px; flex-wrap: wrap; }
.head h1 { font-size: 22px; font-weight: 700; margin: 0 0 4px; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

.grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 16px; margin-bottom: 16px; }
.card { background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); padding: 18px; }
.card-label { font-size: 13px; font-weight: 600; color: var(--text-secondary); margin-bottom: 12px; }

.mapping-row, .reloc-row { display: flex; align-items: center; gap: 8px; flex-wrap: wrap; }
.pose { display: flex; align-items: center; gap: 10px; font-size: 13px; }
.pose-val { color: var(--text-secondary); }

.map-card { min-height: 200px; }
.map-ctrl { display: flex; gap: 8px; margin-bottom: 12px; flex-wrap: wrap; }
.map-view { position: relative; display: inline-block; max-width: 100%; }
.map-img { display: block; max-width: 100%; image-rendering: pixelated; }
.map-canvas { position: absolute; left: 0; top: 0; width: 100%; height: 100%; pointer-events: none; }
.map-err { color: var(--danger); font-size: 13px; padding: 20px 0; }
.map-empty { color: var(--text-secondary); font-size: 13px; padding: 30px 0; text-align: center; }
</style>
