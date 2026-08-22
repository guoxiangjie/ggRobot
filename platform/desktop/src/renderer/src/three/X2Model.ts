/**X2 3D 模型 — 官方 GLB（节点名=URDF link 名，层级自带）+ 关节树 JSON（轴/限位）
   由 1.0 web/src/components/x2model/X2Model.ts 演进：散 STL 组装改为 GLTFLoader 一步加载，
   材质用官方导出（15 材质），关节驱动 = 节点原始四元数 × 轴旋转。
   多实例：loadX2Model() 只调一次，后续 makeInstance() clone 场景图（材质独立化）。 */

import * as THREE from 'three'
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js'
import jointTreeUrl from '@/assets/models/x2_joints.json?url'
import modelUrl from '@/assets/models/x2_model.glb?url'

interface JointNode {
  name: string; mesh: string | null; joint_name?: string; joint_type?: string
  origin_xyz?: [number, number, number]; origin_rpy?: [number, number, number]
  axis_xyz?: [number, number, number]
  limit_lower?: number; limit_upper?: number
  children: JointNode[]
}

/**ROS 坐标 → three 坐标（1.0 验证过的变换） */
function toThree(p: [number, number, number]): THREE.Vector3 {
  return new THREE.Vector3(p[0], p[2], -p[1])
}

// 英文名→中文名（1.0 全量搬）
const CN_MAP: Record<string, string> = {
  base_link: '基座', pelvis: '骨盆', torso_link: '躯干', torso_plus_link: '躯干',
  left_hip_pitch_link: '左髋俯仰', left_hip_roll_link: '左髋横滚', left_hip_yaw_link: '左髋偏航',
  left_knee_link: '左膝', left_ankle_pitch_link: '左踝俯仰', left_ankle_roll_link: '左踝横滚',
  right_hip_pitch_link: '右髋俯仰', right_hip_roll_link: '右髋横滚', right_hip_yaw_link: '右髋偏航',
  right_knee_link: '右膝', right_ankle_pitch_link: '右踝俯仰', right_ankle_roll_link: '右踝横滚',
  waist_yaw_link: '腰偏航', waist_pitch_link: '腰俯仰', waist_roll_link: '腰横滚',
  left_shoulder_pitch_link: '左肩俯仰', left_shoulder_roll_link: '左肩横滚', left_shoulder_yaw_link: '左肩偏航',
  left_elbow_link: '左肘', left_wrist_yaw_link: '左腕偏航', left_wrist_pitch_link: '左腕俯仰', left_wrist_roll_link: '左腕横滚',
  right_shoulder_pitch_link: '右肩俯仰', right_shoulder_roll_link: '右肩横滚', right_shoulder_yaw_link: '右肩偏航',
  right_elbow_link: '右肘', right_wrist_yaw_link: '右腕偏航', right_wrist_pitch_link: '右腕俯仰', right_wrist_roll_link: '右腕横滚',
  head_yaw_link: '头偏航', head_pitch_link: '头俯仰',
  imu_in_pelvis_link: '骨盆IMU', imu_in_torso_link: '躯干IMU', imu_in_head_link: '头部IMU',
  rgbd_head_front: 'RGBD前视', stereo_head_front: '双目相机', rgb_head_rear: '后视RGB', rgb_head_center: '顶部RGB',
  lidar_chest_front: '胸部激光', left_wrist_hand_link: '左手', right_wrist_hand_link: '右手',
}

export function partLabel(name: string): string {
  return CN_MAP[name] || name.replace(/_link$/, '').replace(/_joint$/, '')
}

export interface JointControl {
  node: THREE.Object3D          // GLB 里对应的 link 节点（旋转它 = 旋转子树）
  qOrig: THREE.Quaternion       // 节点原始四元数（关节零位）
  axis: THREE.Vector3
  lower: number                 // rad
  upper: number
}

export interface X2ModelInstance {
  group: THREE.Group
  joints: Map<string, JointControl>
  meshes: THREE.Mesh[]          // raycast 目标
  meshToLink: Map<THREE.Mesh, string>
  linkToJoint: Map<string, string>
  setDim: (dim: boolean) => void
}

/** 更新关节角度（rad） */
export function setJointAngle(jc: JointControl, angleRad: number): void {
  jc.node.quaternion.copy(jc.qOrig)
    .multiply(new THREE.Quaternion().setFromAxisAngle(jc.axis, angleRad))
}

let proto: {
  scene: THREE.Group
  joints: Map<string, JointControl>
  meshToLink: Map<THREE.Mesh, string>
  linkToJoint: Map<string, string>
} | null = null

/**加载原型（全局一次；47MB 本地加载） */
export async function loadX2Model(onProgress?: (pct: number) => void): Promise<void> {
  if (proto) return
  const tree: JointNode = await (await fetch(jointTreeUrl)).json()

  const gltf = await new Promise<{ scene: THREE.Group }>((resolve, reject) => {
    new GLTFLoader().load(modelUrl, resolve, (e) => {
      if (e.total) onProgress?.(Math.round((e.loaded / e.total) * 100))
    }, reject)
  })

  // GLB 节点名 → Object3D 索引
  const byName = new Map<string, THREE.Object3D>()
  gltf.scene.traverse((o) => { if (o.name) byName.set(o.name, o) })

  // 归一化：包一层 root，缩放到 1.5m 高、落地
  const root = new THREE.Group()
  root.name = 'X2'
  root.add(gltf.scene)
  root.rotation.set(0, -0.8, 0)
  root.updateWorldMatrix(true, true)
  const box = new THREE.Box3().setFromObject(root)
  const sz = box.getSize(new THREE.Vector3())
  const ct = box.getCenter(new THREE.Vector3())
  const sc = 1.5 / Math.max(sz.x, sz.y, sz.z)
  root.scale.setScalar(sc)
  root.position.set(-ct.x * sc, -ct.y * sc + 0.35, -ct.z * sc)

  // 地面环（选中态视觉锚）
  const ring = new THREE.Mesh(
    new THREE.TorusGeometry(0.55, 0.004, 16, 80),
    new THREE.MeshBasicMaterial({ color: 0x64748b }),
  )
  ring.rotation.x = -Math.PI / 2
  ring.position.y = -0.85
  root.add(ring)

  // 关节控制表：URDF 树的 joint_name → GLB 同名 link 节点
  const joints = new Map<string, JointControl>()
  const meshToLink = new Map<THREE.Mesh, string>()
  const linkToJoint = new Map<string, string>()
  const walk = (n: JointNode): void => {
    if (n.joint_name && n.joint_type === 'revolute') {
      const node = byName.get(n.name)
      if (node) {
        joints.set(n.joint_name, {
          node,
          qOrig: node.quaternion.clone(),
          axis: n.axis_xyz ? toThree(n.axis_xyz).normalize() : new THREE.Vector3(0, 0, 1),
          lower: n.limit_lower ?? -3.14,
          upper: n.limit_upper ?? 3.14,
        })
        linkToJoint.set(n.name, n.joint_name)
      }
    }
    if (n.mesh) {
      const node = byName.get(n.name)
      node?.traverse((o) => {
        if ((o as THREE.Mesh).isMesh) meshToLink.set(o as THREE.Mesh, n.name)
      })
    }
    n.children.forEach(walk)
  }
  walk(tree)

  proto = { scene: root, joints, meshToLink, linkToJoint }
}

/**克隆实例（材质独立化：高亮/半透明互不影响；关节控制表重建绑定到克隆节点） */
export function makeInstance(): X2ModelInstance {
  if (!proto) throw new Error('先 loadX2Model()')
  const group = proto.scene.clone(true)

  // 克隆后节点按名字重新索引，重建关节/网格表
  const byName = new Map<string, THREE.Object3D>()
  group.traverse((o) => { if (o.name) byName.set(o.name, o) })
  const joints = new Map<string, JointControl>()
  const meshes: THREE.Mesh[] = []
  const meshToLink = new Map<THREE.Mesh, string>()
  for (const [jname, jc] of proto.joints) {
    const node = byName.get(jc.node.name)
    if (!node) continue
    joints.set(jname, { ...jc, node, qOrig: node.quaternion.clone() })
  }
  // 遍历克隆树收集 mesh，通过父链最近的命名节点归到 link
  const linkNodes = new Set(byName.keys())
  group.traverse((o) => {
    const m = o as THREE.Mesh
    if (!m.isMesh) return
    m.material = (Array.isArray(m.material) ? m.material[0] : m.material).clone() as THREE.Material
    meshes.push(m)
    // 向上找最近的命名 link 节点
    let p: THREE.Object3D | null = m
    while (p && !linkNodes.has(p.name)) p = p.parent
    if (p) meshToLink.set(m, p.name)
  })

  const setDim = (dim: boolean): void => {
    for (const m of meshes) {
      const mat = m.material as THREE.MeshStandardMaterial
      mat.transparent = dim
      mat.opacity = dim ? 0.25 : 1
      mat.needsUpdate = true
    }
  }

  return { group, joints, meshes, meshToLink, linkToJoint: proto.linkToJoint, setDim }
}
