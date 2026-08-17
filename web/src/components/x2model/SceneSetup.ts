/** Three.js 场景 — 干净渲染（支持暗/亮主题）*/

import * as THREE from 'three'
import { OrbitControls } from 'three/addons/controls/OrbitControls.js'

export interface SceneContext {
  scene: THREE.Scene
  camera: THREE.PerspectiveCamera
  renderer: THREE.WebGLRenderer
  controls: OrbitControls
  clock: THREE.Clock
}

// 暗/亮主题的 3D 配色（背景 / 环境光 / 网格）。方向光保持白光为主，亮暗通用。
const DARK = { bg: '#111620', amb: '#8896a9', ambI: 0.8, gridA: '#334155', gridB: '#111620' }
const LIGHT = { bg: '#e8edf3', amb: '#ffffff', ambI: 0.6, gridA: '#c5cdd9', gridB: '#e8edf3' }

export function createScene(canvas: HTMLCanvasElement, isLight = false): SceneContext {
  const renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: false })
  renderer.setPixelRatio(window.devicePixelRatio)
  renderer.shadowMap.enabled = true
  renderer.toneMapping = THREE.ACESFilmicToneMapping
  renderer.toneMappingExposure = 1.0

  const c = isLight ? LIGHT : DARK
  const scene = new THREE.Scene()
  scene.background = new THREE.Color(c.bg)

  const camera = new THREE.PerspectiveCamera(45, 2, 0.1, 20)
  camera.position.set(2, 1.4, 2)
  camera.lookAt(0, 0.4, 0)

  // 环境光
  scene.add(new THREE.AmbientLight(c.amb, c.ambI))

  // 主光 右前上
  const key = new THREE.DirectionalLight('#ffffff', 5.0)
  key.position.set(2, 4, 3); key.castShadow = true; key.shadow.mapSize.set(1024, 1024)
  scene.add(key)

  // 补光 左前
  const fill = new THREE.DirectionalLight('#8cb8e8', 2.5)
  fill.position.set(-2, 1, 0); scene.add(fill)

  // 轮廓光 后上
  const rim = new THREE.DirectionalLight('#ffffff', 2.0)
  rim.position.set(0, 2, -3); scene.add(rim)

  // 底部补光
  const under = new THREE.DirectionalLight('#c8d6e5', 0.8)
  under.position.set(0, -1, 0.5); scene.add(under)

  // 头顶光
  const top = new THREE.DirectionalLight('#ffffff', 1.2)
  top.position.set(0, 3, 0); scene.add(top)

  // 正前方光
  const front = new THREE.DirectionalLight('#ffffff', 1.0)
  front.position.set(0, 0.8, 2); scene.add(front)

  // 地面
  const grid = new THREE.GridHelper(3, 20, c.gridA, c.gridB)
  grid.position.y = -0.85; scene.add(grid)

  // 轨道
  const controls = new OrbitControls(camera, renderer.domElement)
  controls.target.set(0, 0.35, 0)
  controls.enableDamping = true; controls.dampingFactor = 0.08
  controls.minDistance = 0.4; controls.maxDistance = 5
  controls.maxPolarAngle = Math.PI * 0.7
  controls.update()

  return { scene, camera, renderer, controls, clock: new THREE.Clock() }
}

/** 主题切换：改背景 + 环境光 + 重建网格（模型 mesh 不动，无重载闪烁）*/
export function applyTheme(ctx: SceneContext, isLight: boolean) {
  const c = isLight ? LIGHT : DARK
  ctx.scene.background = new THREE.Color(c.bg)
  for (const child of ctx.scene.children) {
    if (child instanceof THREE.AmbientLight) {
      child.color.set(c.amb)
      child.intensity = c.ambI
    }
  }
  const oldGrid = ctx.scene.children.find(o => o instanceof THREE.GridHelper) as THREE.GridHelper | undefined
  if (oldGrid) {
    ctx.scene.remove(oldGrid)
    oldGrid.geometry?.dispose()
    const grid = new THREE.GridHelper(3, 20, c.gridA, c.gridB)
    grid.position.y = -0.85
    ctx.scene.add(grid)
  }
}
