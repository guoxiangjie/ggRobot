/** X2 模型 — STL + URDF 层级 + 关节控制 */

import * as THREE from 'three'
import { mergeVertices } from 'three/addons/utils/BufferGeometryUtils.js'
import { STLLoader } from 'three/addons/loaders/STLLoader.js'
import jointTreeUrl from '@/assets/models/x2_joints.json?url'

interface JointNode {
  name: string; mesh: string | null; joint_name?: string; joint_type?: string
  origin_xyz?: [number, number, number]; origin_rpy?: [number, number, number]
  axis_xyz?: [number, number, number]
  children: JointNode[]
}

function toThree(p: [number, number, number]) { return new THREE.Vector3(p[0], p[2], -p[1]) }
function rpyQuat(p: [number, number, number]) { const q=new THREE.Quaternion(); q.setFromEuler(new THREE.Euler(p[0],p[1],p[2],'XYZ')); return q }

const matShell  = new THREE.MeshStandardMaterial({ color: 0xf0f4f8, roughness: 0.35, metalness: 0.6 })
const matJoint  = new THREE.MeshStandardMaterial({ color: 0xb0bec5, roughness: 0.25, metalness: 0.8 })
const matSensor = new THREE.MeshStandardMaterial({ color: 0x546e7a, roughness: 0.3,  metalness: 0.5 })

function pickMat(name: string) {
  if (name.includes('imu') || name.includes('rgb') || name.includes('lidar') || name.includes('stereo')) return matSensor
  if (name.includes('hip') || name.includes('knee') || name.includes('ankle') || name.includes('shoulder') || name.includes('elbow') || name.includes('wrist') || name.includes('waist') || name.includes('head')) return matJoint
  return matShell
}

// 英文名→中文名
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
  rgbd_head_front_link: 'RGBD前视', stereo_head_front_link: '双目相机', rgb_head_rear_link: '后视RGB', rgb_head_center_link: '顶部RGB',
  lidar_link: '激光雷达', left_wrist_hand_link: '左手', right_wrist_hand_link: '右手',
}

export function partLabel(name: string) { return CN_MAP[name] || name.replace(/_link$/, '').replace(/_joint$/, '') }

export interface JointControl {
  group: THREE.Group
  axis: THREE.Vector3
  lower: number                // 角度下限(rad)
  upper: number                // 角度上限(rad)
}

export async function loadX2Model(onProgress?: (pct: number) => void): Promise<{
  group: THREE.Group
  joints: Map<string, JointControl>
  meshMap: Map<THREE.Mesh, string>
  linkToJoint: Map<string, string>   // link名 → joint名
}> {
  const report = (n: number) => onProgress?.(Math.round(n))

  // 关节树
  const tree: JointNode = await (await fetch(jointTreeUrl)).json()

  // 收集 STL
  const needed = new Set<string>()
  function collect(n: JointNode) { if(n.mesh) needed.add(n.mesh); for(const c of n.children) collect(c) }
  collect(tree)

  // 加载 STL
  const loader = new STLLoader()
  const geoMap = new Map<string, THREE.BufferGeometry>()
  const stlList = Array.from(needed)
  let loaded = 0; report(0)

  await Promise.all(stlList.map(async name => {
    try {
      const raw = await loader.loadAsync('/meshes/'+name)
      const geo = mergeVertices(raw, 0.001); geo.computeVertexNormals()
      geoMap.set(name, geo); raw.dispose()
    } catch { console.warn('missing:',name) }
    loaded++; report((loaded / stlList.length) * 90)
  }))
  report(95)

  // 建层级
  const root = new THREE.Group(); root.name='X2'
  const joints = new Map<string, JointControl>()
  const meshMap = new Map<THREE.Mesh, string>()
  const linkToJoint = new Map<string, string>()
  let count = 0

  function walk(node: JointNode, parent: THREE.Object3D) {
    const g = new THREE.Group(); g.name = node.name
    if (node.joint_type && node.origin_xyz) g.position.copy(toThree(node.origin_xyz))
    if (node.joint_type && node.origin_rpy) g.quaternion.multiply(rpyQuat(node.origin_rpy))

    // revolute 关节：加旋转层
    let attachPoint: THREE.Object3D = g
    if (node.joint_type === 'revolute' && node.joint_name) {
      const rotGroup = new THREE.Group()
      rotGroup.name = 'rot_' + node.joint_name
      g.add(rotGroup)
      attachPoint = rotGroup
      joints.set(node.joint_name, {
        group: rotGroup,
        axis: node.axis_xyz ? toThree(node.axis_xyz).normalize() : new THREE.Vector3(0,0,1),
        lower: (node as any).limit_lower ?? -3.14,
        upper: (node as any).limit_upper ?? 3.14,
      })
      linkToJoint.set(node.name, node.joint_name)
    }

    parent.add(g)

    if (node.mesh) {
      const geo = geoMap.get(node.mesh)
      if (geo) {
        const wrap = new THREE.Group(); wrap.rotation.set(-Math.PI/2, 0, 0)
        const mesh = new THREE.Mesh(geo, pickMat(node.name).clone())  // clone 独立材质，防止高亮扩散
        wrap.add(mesh)
        attachPoint.add(wrap)
        meshMap.set(mesh, node.name)
        count++
      }
    }

    for (const c of node.children) walk(c, attachPoint)
  }

  for (const c of tree.children) walk(c, root)

  // 初始朝向：绕 Y 旋转使面部朝向相机
  root.rotation.set(0, -0.8, 0)
  root.updateWorldMatrix(true, true)
  const box = new THREE.Box3().setFromObject(root)
  const sz = box.getSize(new THREE.Vector3())
  const ct = box.getCenter(new THREE.Vector3())
  const sc = 1.5 / Math.max(sz.x, sz.y, sz.z)
  root.scale.setScalar(sc)
  root.position.set(-ct.x*sc, -ct.y*sc + 0.35, -ct.z*sc)

  // 地面环
  const ring = new THREE.Mesh(new THREE.TorusGeometry(0.55,0.004,16,80), new THREE.MeshBasicMaterial({color:0x64748b}))
  ring.rotation.x=-Math.PI/2; ring.position.y=-0.85; root.add(ring)

  report(100)
  console.log(`X2: ${count} 部件, ${joints.size} 关节, ${sz.y.toFixed(1)}m 高`)
  return { group: root, joints, meshMap, linkToJoint }
}

/** 更新关节角度 */
export function setJointAngle(jc: JointControl, angleRad: number) {
  jc.group.quaternion.setFromAxisAngle(jc.axis, angleRad)
}
