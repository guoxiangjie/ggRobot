// FastAPI REST 接口封装
import axios, { type AxiosInstance } from 'axios'

let api: AxiosInstance = axios.create({
  baseURL: '/',
  timeout: 5000,
})

// ── TTS ──
export interface TtsParams {
  text: string
  domain?: string
  is_interrupted?: boolean
  priority_level?: number
}

export async function playTts(params: TtsParams) {
  const { data } = await api.post('/api/tts', {
    text: params.text,
    domain: params.domain ?? 'web_ui',
    is_interrupted: params.is_interrupted ?? true,
    priority_level: params.priority_level ?? 6,
  })
  return data as { ok: boolean }
}

// ── 预设动作 ──
export async function playMotion(area: number, motionId: number, interrupt = false) {
  const { data } = await api.post('/api/motion', { area, motion_id: motionId, interrupt })
  return data as { ok: boolean; task_id?: number; error?: string }
}

// ── 速度指令（单次） ──
export async function sendVelocity(forward: number, lateral: number, angular: number) {
  const { data } = await api.post('/api/velocity', {
    forward,
    lateral,
    angular,
  })
  return data as { ok: boolean }
}

// ── 状态查询 ──
export async function getStatus() {
  const { data } = await api.get('/api/status')
  return data as {
    battery: Record<string, unknown>
    arms: Array<{ name: string; pos: number }>
    imu: Record<string, number>
  }
}

// ── 系统状态 ──
export async function getSystem() {
  const { data } = await api.get('/api/system')
  return data as {
    action: { desc: string; status: number } | null
    system: { state: string; status: number } | null
  }
}

// ── 开发者模式（系统状态迁移）──
export async function migrateSystemState(state: string) {
  const { data } = await api.post('/api/system/migrate', { state })
  return data as { ok: boolean; in_progress?: boolean; code?: number; state?: string; status?: number; message?: string }
}

// ── 表情 ──
export async function playEmoji(emotionId: number, mode: number = 1) {
  const { data } = await api.post('/api/emoji', { emotion_id: emotionId, mode })
  return data as { ok: boolean; message: string }
}

// ── 模式切换 ──
export async function switchMode(mode: string, value?: number) {
  // value 为数字模式 ID（SIT_DOWN=2000 / ZERO_TORQUE=4 等），后端优先使用
  const { data } = await api.post(`/api/mode?mode=${mode}${value != null ? `&value=${value}` : ''}`)
  return data as { ok: boolean }
}

// ── 媒体 ──
export interface MediaFile {
  name: string; size: number; kind: "audio" | "video"; ext: string
}

export async function getMediaList() {
  const { data } = await api.get('/api/media/list')
  return data as { files: MediaFile[] }
}

export async function uploadMedia(file: File, onProgress?: (pct: number) => void) {
  const form = new FormData()
  form.append('file', file)
  const { data } = await api.post('/api/media/upload', form, {
    timeout: 0,  // 大文件上传不超时（上传 + scp PC3 可能较久）
    onUploadProgress: (e) => {
      if (e.total && onProgress) onProgress(Math.round((e.loaded / e.total) * 100))
    },
  })
  return data as { ok: boolean; name?: string; size?: number; pc3_synced?: boolean; error?: string }
}

export async function deleteMedia(name: string) {
  const { data } = await api.delete(`/api/media/${name}`)
  return data as { ok: boolean }
}

export async function playMedia(name: string) {
  const form = new FormData()
  form.append('name', name)
  const { data } = await api.post('/api/media/play', form)
  return data as { ok: boolean; error?: string }
}

// ── MIC 采集 / VAD / ASR ──
export interface MicStatus {
  ok: boolean
  enabled: boolean
  vad_state: number
  vad_label?: string
  segment_bytes: number
  last_segment_bytes: number
  last_segment_ts: number
  mic_source: number
  text: string
  recv_count: number
}
export async function micStatus() { const { data } = await api.get('/api/mic'); return data as MicStatus }
export async function micToggle(enable: boolean) { const { data } = await api.post('/api/mic', { enable }); return data as { ok: boolean; enabled: boolean; vad_state: number; error?: string } }
export async function getMicAudio() { const { data } = await api.get('/api/mic/audio'); return data as { ok: boolean; data: string; size: number; text: string } }
export async function getMicSource() { const { data } = await api.get('/api/mic/source'); return data as { ok: boolean; mic_source: number; error?: string } }
export async function setMicSource(mic_source: number) { const { data } = await api.post('/api/mic/source', { mic_source }); return data as { ok: boolean; mic_source: number; error?: string } }
export async function forceAsr() { const { data } = await api.post('/api/mic/asr'); return data as { ok: boolean; started: boolean; error?: string } }

// ── 音量 ──
export async function getVolume() { const { data } = await api.get('/api/volume'); return data as { volume: number } }
export async function setVolume(volume: number) { const { data } = await api.post(`/api/volume?volume=${volume}`); return data as { volume: number } }
export async function getMute() { const { data } = await api.get('/api/mute'); return data as { is_mute: boolean } }
export async function setMute(is_mute: boolean) { const { data } = await api.post(`/api/mute?mute=${is_mute}`); return data as { is_mute: boolean } }

// ── 动作序列 ──
export async function runSequence() { const { data } = await api.post('/api/sequence'); return data as { ok: boolean } }

// ── 任务编排 ──
export interface TaskStep { type: string; [key: string]: unknown }
export interface Task {
  id: string; name: string; desc: string; steps: TaskStep[]
  updated_at?: string; step_count?: number
}
export interface TaskStatus {
  running: boolean; task_id: string; task_name: string
  total: number; current: number; progress: number
  current_step: TaskStep | null; started_at: string
}
export interface Capability {
  type: string; label: string; icon: string; color: string
  params: { name: string; label: string; type: string; required?: boolean; default?: unknown; options?: { label: string; value: unknown }[]; hint?: string }[]
}

export async function getTasks() { const { data } = await api.get('/api/tasks'); return data as { tasks: Task[] } }
export async function getTask(id: string) { const { data } = await api.get(`/api/tasks/${id}`); return data as Task }
export async function saveTask(task: Task) { const { data } = await api.post('/api/tasks', task); return data as Task }
export async function generateTask(prompt: string) {
  const { data } = await api.post('/api/tasks/generate', { prompt }, { timeout: 60000 })
  return data as { ok: boolean; task?: Task; error?: string }
}
export async function deleteTask(id: string) { const { data } = await api.delete(`/api/tasks/${id}`); return data as { ok: boolean } }
export async function runTask(id: string) { const { data } = await api.post(`/api/tasks/${id}/run`); return data as { ok: boolean; error?: string } }
export async function stopTask() { const { data } = await api.post('/api/tasks/stop'); return data as { ok: boolean } }
export async function getTaskStatus() { const { data } = await api.get('/api/tasks/status'); return data as TaskStatus }
export async function getCapabilities() { const { data } = await api.get('/api/capabilities'); return data as { capabilities: Capability[] } }
export interface RobotResource { resource_key: string; name: string; version: string; type: string }
export async function getResources() { const { data } = await api.get('/api/resources'); return data as { ok: boolean; error?: string; resources: RobotResource[] } }
export async function playResource(resourceKey: string, version: string, resourceType: string) {
  const { data } = await api.post('/api/resources/play', { resource_key: resourceKey, version, resource_type: resourceType })
  return data as { ok: boolean; code?: number; message?: string; error?: string }
}

// ── 手机端按键绑定 ──
export interface PhoneKeySlot {
  slot: number; name: string; resource_key: string; version: string; resource_type: string
}
export async function getPhoneKeys() {
  const { data } = await api.get('/api/phone/keys')
  return data as { keys: PhoneKeySlot[]; updated_at: string }
}
export async function savePhoneKeys(keys: PhoneKeySlot[]) {
  const { data } = await api.put('/api/phone/keys', { keys })
  return data as { keys: PhoneKeySlot[]; updated_at: string }
}

// ── 自由任务（项目）──
export interface ProjectNode {
  id?: string; name: string; icon: string; type: string
  [key: string]: unknown
}
export interface Project {
  id?: string; name: string; desc: string; icon: string
  nodes: ProjectNode[]; updated_at?: string; node_count?: number
}
export async function getProjects() {
  const { data } = await api.get('/api/projects')
  return data as { projects: { id: string; name: string; desc: string; icon: string; node_count: number; updated_at: string }[] }
}
export async function getProject(id: string) {
  const { data } = await api.get(`/api/projects/${id}`)
  return data as Project
}
export async function saveProject(project: Project) {
  const { data } = await api.post('/api/projects', project)
  return data as Project
}
export async function deleteProject(id: string) {
  const { data } = await api.delete(`/api/projects/${id}`)
  return data as { ok: boolean }
}
export async function runProjectNode(pid: string, nid: string) {
  // 单节点执行可能较长（velocity/tts wait_done），timeout:0 不限
  const { data } = await api.post(`/api/projects/${pid}/nodes/${nid}/run`, {}, { timeout: 0 })
  return data as { ok: boolean; error?: string; node_id?: string }
}
export async function stopProjectNode() {
  const { data } = await api.post('/api/projects/stop')
  return data as { ok: boolean }
}
export async function getProjectStatus() {
  const { data } = await api.get('/api/projects/status')
  return data as { running: boolean; node_id: string }
}
export async function getCameras() { const { data } = await api.get('/api/cameras'); return data as { cameras: { id: string; label: string; topic: string; active: boolean; selected: boolean }[] } }
export async function switchCamera(cameraId: string) { const { data } = await api.post('/api/camera/switch', { camera_id: cameraId }); return data as { ok: boolean; error?: string } }

// ── 脸屏 Logo ──
export async function showLogo() { const { data } = await api.post('/api/logo/show'); return data as { ok: boolean; error?: string } }
export async function hideLogo() { const { data } = await api.post('/api/logo/hide'); return data as { ok: boolean } }
