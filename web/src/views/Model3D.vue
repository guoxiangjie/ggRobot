<script setup lang="ts">
import { ref, onMounted, onUnmounted, watch } from 'vue'
import { storeToRefs } from 'pinia'
import * as THREE from 'three'
import { createScene, applyTheme, type SceneContext } from '@/components/x2model/SceneSetup'
import { loadX2Model, partLabel, setJointAngle, type JointControl } from '@/components/x2model/X2Model'
import { NTag, NSlider, NButton, NInput, NPopover } from 'naive-ui'
import { useThemeStore } from '@/stores/theme'

const canvasRef = ref<HTMLCanvasElement | null>(null)
const { mode } = storeToRefs(useThemeStore())
const loading = ref(true)
const error = ref('')
const progress = ref(0)
const jointCount = ref(0)

let ctx: SceneContext | null = null
let meshMap = new Map<THREE.Mesh, string>()
let linkToJoint = new Map<string, string>()
let joints = new Map<string, JointControl>()
let highlighted: THREE.Mesh | null = null
const selectedColor = ref('#f0f4f8')
const presets = ['#f0f4f8','#b0bec5','#546e7a','#4da6ff','#4ade80','#f87171','#fbbf24','#a78bfa','#e8ecf1','#1e293b']

function applyColor(color: string) {
  selectedColor.value = color
  if (highlighted) {
    (highlighted.material as THREE.MeshStandardMaterial).color.set(color)
  }
}

function resetAllJoints() {
  joints.forEach((jc) => setJointAngle(jc, 0))
  selectedAngle.value = 0
}
const selectedName = ref('')
const selectedJoint = ref<JointControl | null>(null)
const jointNames = ref<string[]>([])
const selectedAngle = ref(0)

function handleResize() {
  if (!ctx || !canvasRef.value) return
  const w = canvasRef.value.clientWidth
  const h = canvasRef.value.clientHeight
  if (w === 0 || h === 0) return
  ctx.renderer.setPixelRatio(window.devicePixelRatio)
  ctx.renderer.setSize(w, h, false)
  ctx.camera.aspect = w / h
  ctx.camera.updateProjectionMatrix()
}

onMounted(async () => {
  if (!canvasRef.value) return

  try {
    ctx = createScene(canvasRef.value, mode.value === 'light')
    handleResize()

    const result = await loadX2Model((pct) => { progress.value = pct })
    ctx.scene.add(result.group)
    meshMap = result.meshMap
    linkToJoint = result.linkToJoint
    joints = result.joints
    jointCount.value = result.joints.size
    jointNames.value = Array.from(result.joints.keys()).sort()
    handleResize()
    loading.value = false

    // 点击选中部件的回调
    canvasRef.value!.addEventListener('click', (e) => {
      if (!ctx) return
      const rect = canvasRef.value!.getBoundingClientRect()
      const mouse = new THREE.Vector2(
        ((e.clientX - rect.left) / rect.width) * 2 - 1,
        -((e.clientY - rect.top) / rect.height) * 2 + 1,
      )
      const raycaster = new THREE.Raycaster()
      raycaster.setFromCamera(mouse, ctx.camera)

      // 取消上次高亮
      if (highlighted) {
        const m = (highlighted as THREE.Mesh).material as THREE.MeshStandardMaterial
        m.emissive.set(0x000000)
        m.emissiveIntensity = 0
      }

      const meshes = Array.from(meshMap.keys())
      const hits = raycaster.intersectObjects(meshes, false)

      if (hits.length > 0) {
        const mesh = hits[0].object as THREE.Mesh
        const linkName = meshMap.get(mesh) || ''
        const jointName = linkToJoint.get(linkName)
        const m = mesh.material as THREE.MeshStandardMaterial
        m.emissive.set(jointName ? 0x4ade80 : 0x4da6ff)  // 可动关节绿，不可动蓝
        m.emissiveIntensity = 0.6
        highlighted = mesh
        selectedColor.value = '#' + m.color.getHexString()
        selectedName.value = linkName

        if (jointName) {
          const jc = joints.get(jointName)
          if (jc) {
            selectedJoint.value = jc
            selectedAngle.value = 0
          }
        } else {
          selectedJoint.value = null
        }
      } else {
        highlighted = null
        selectedName.value = ''
        selectedJoint.value = null
      }
    })
  } catch (e: any) {
    error.value = e?.message || '模型加载失败'
    loading.value = false
  }

  function render() {
    if (!ctx) return
    requestAnimationFrame(render)
    ctx.controls.update()
    ctx.renderer.render(ctx.scene, ctx.camera)
  }
  render()

  const ro = new ResizeObserver(handleResize)
  ro.observe(canvasRef.value!.parentElement!)
  window.addEventListener('resize', handleResize)
  onUnmounted(() => {
    ro.disconnect()
    window.removeEventListener('resize', handleResize)
  })
})

watch(mode, (m) => { if (ctx) applyTheme(ctx, m === 'light') })

onUnmounted(() => {
  ctx?.renderer.dispose()
})
</script>

<template>
  <div class="model3d">
    <header class="head">
      <div>
        <h1>3D 模型</h1>
        <p>X2 数字孪生预览</p>
      </div>
      <NPopover trigger="hover" placement="bottom" v-if="!loading && !error">
        <template #trigger>
          <NTag size="small" round style="cursor:default;">
            {{ jointCount }} 个活动关节
          </NTag>
        </template>
        <div>
          <div v-for="name in jointNames" :key="name" class="tooltip-item">{{ partLabel(name) }}</div>
        </div>
      </NPopover>
    </header>

    <div class="model-body">
      <div class="canvas-wrap">
        <canvas ref="canvasRef" />

        <div v-if="loading" class="overlay">
          <div class="progress-ring">
            <svg viewBox="0 0 100 100">
              <circle cx="50" cy="50" r="42" class="ring-bg" />
              <circle cx="50" cy="50" r="42" class="ring-fill"
                :style="{ strokeDasharray: progress * 2.64 + ' 264' }" />
            </svg>
            <span class="ring-text">{{ progress }}%</span>
          </div>
          <p>加载模型中...</p>
        </div>

        <div v-if="error" class="overlay">
          <p style="color:var(--danger)">加载失败: {{ error }}</p>
        </div>

        <div v-if="!loading && !error" class="hint">
          拖拽旋转 · 滚轮缩放 · 右键平移
        </div>
      </div>

      <!-- 部件列表侧边 -->
      <aside v-if="!loading && !error" class="part-panel">
        <div class="panel-header">
          <span class="panel-title">部件信息</span>
          <NButton size="tiny" quaternary @click="resetAllJoints">↺ 全身复位</NButton>
        </div>

        <!-- 空状态 -->
        <div v-if="!selectedName" class="panel-empty">
          点击模型查看部件
        </div>

        <!-- 选中部件 -->
        <template v-else>
          <div class="panel-name">{{ partLabel(selectedName) }}</div>
          <div class="panel-type">{{ selectedJoint ? '🟢 活动关节' : '🔵 固定部件' }}</div>

          <div class="color-row">
            <span class="color-label">材质颜色</span>
            <div class="presets">
              <button
                v-for="c in presets" :key="c"
                class="swatch" :class="{ active: selectedColor === c }"
                :style="{ background: c }"
                @click="applyColor(c)"
              />
            </div>
            <div class="hex-row">
              <NInput v-model:value="selectedColor" size="tiny" placeholder="#f0f4f8" class="hex-input" @blur="applyColor(selectedColor)" @keyup.enter="applyColor(selectedColor)" />
            </div>
          </div>

          <div v-if="selectedJoint" class="joint-control">
            <div class="joint-label">
              关节角度
              <NButton size="tiny" quaternary @click="selectedAngle = 0; setJointAngle(selectedJoint!, 0)">↺ 复位</NButton>
            </div>
            <NSlider
              :value="selectedAngle"
              :min="Number(selectedJoint.lower.toFixed(2))"
              :max="Number(selectedJoint.upper.toFixed(2))"
              :step="0.01"
              @update:value="(v: number) => { selectedAngle = v; setJointAngle(selectedJoint!, v) }"
            />
            <div class="joint-range">
              <span>{{ selectedJoint.lower.toFixed(2) }}</span>
              <span class="joint-val">{{ selectedAngle.toFixed(2) }} rad</span>
              <span>{{ selectedJoint.upper.toFixed(2) }}</span>
            </div>
          </div>
        </template>
      </aside>
    </div>
  </div>
</template>

<style scoped>
.model3d { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 20px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }

.model-body { display: flex; gap: 16px; }
.canvas-wrap { flex: 1; position: relative; height: 620px; background: var(--surface); border: 1px solid var(--border); border-radius: var(--radius); overflow: hidden; }

.part-panel {
  width: 200px; flex-shrink: 0;
  background: var(--surface); border: 1px solid var(--border);
  border-radius: var(--radius); padding: 16px;
}
.panel-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 12px; }
.panel-title { font-size: 12px; font-weight: 700; color: var(--text-secondary); text-transform: uppercase; letter-spacing: 0.05em; }
.panel-empty { font-size: 13px; color: var(--text-secondary); opacity: 0.6; text-align: center; padding: 32px 0; }
.panel-name { font-size: 15px; font-weight: 700; margin-bottom: 4px; }
.panel-type { font-size: 12px; color: var(--text-secondary); margin-bottom: 8px; }

.color-row { margin-bottom: 12px; }
.color-label { font-size: 12px; color: var(--text-secondary); display: block; margin-bottom: 6px; }
.presets { display: flex; gap: 4px; flex-wrap: wrap; margin-bottom: 8px; }
.swatch { width: 22px; height: 22px; border-radius: 4px; border: 2px solid transparent; cursor: pointer; transition: border-color 0.15s; }
.swatch:hover { border-color: var(--text-secondary); }
.swatch.active { border-color: #fff; box-shadow: 0 0 4px var(--overlay); }
.hex-row { display: flex; }
.hex-input { font-family: 'JetBrains Mono', monospace; font-size: 12px; }
.tooltip-item { font-size: 12px; line-height: 1.6; white-space: nowrap; }

.joint-control { margin-top: 8px; padding: 12px; background: rgba(74,222,128,0.05); border: 1px solid rgba(74,222,128,0.12); border-radius: 6px; }
.joint-label { display: flex; justify-content: space-between; align-items: center; font-size: 12px; font-weight: 600; color: var(--text-secondary); margin-bottom: 10px; }
.joint-range { display: flex; justify-content: space-between; font-size: 11px; color: var(--text-secondary); font-family: 'JetBrains Mono', monospace; margin-top: 4px; }
.joint-val { color: var(--accent); font-weight: 600; }

.canvas-wrap canvas { display: block; width: 100%; height: 100%; }

.progress-ring { position: relative; width: 80px; height: 80px; }
.progress-ring svg { width: 100%; height: 100%; transform: rotate(-90deg); }
.ring-bg { fill: none; stroke: var(--border); stroke-width: 6; }
.ring-fill { fill: none; stroke: var(--accent); stroke-width: 6; stroke-linecap: round; transition: stroke-dasharray 0.2s ease; }
.ring-text { position: absolute; inset: 0; display: flex; align-items: center; justify-content: center;
  font-family: 'JetBrains Mono', monospace; font-size: 16px; font-weight: 700; color: var(--accent); }

.overlay {
  position: absolute; inset: 0;
  display: flex; flex-direction: column; align-items: center; justify-content: center;
  gap: 12px; color: var(--text-secondary); font-size: 14px;
}

.hint {
  position: absolute; bottom: 12px; right: 16px;
  font-size: 11px; color: var(--text-secondary);
}
</style>
