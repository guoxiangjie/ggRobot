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

// ── 表情 ──
export async function playEmoji(emotionId: number, mode: number = 1) {
  const { data } = await api.post('/api/emoji', { emotion_id: emotionId, mode })
  return data as { ok: boolean; message: string }
}

// ── 模式切换 ──
export async function switchMode(mode: string) {
  const { data } = await api.post(`/api/mode?mode=${mode}`)
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

export async function uploadMedia(file: File) {
  const form = new FormData()
  form.append('file', file)
  const { data } = await api.post('/api/media/upload', form)
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

// ── 音量 ──
export async function getVolume() { const { data } = await api.get('/api/volume'); return data as { volume: number } }
export async function setVolume(volume: number) { const { data } = await api.post(`/api/volume?volume=${volume}`); return data as { volume: number } }
export async function getMute() { const { data } = await api.get('/api/mute'); return data as { is_mute: boolean } }
export async function setMute(is_mute: boolean) { const { data } = await api.post(`/api/mute?mute=${is_mute}`); return data as { is_mute: boolean } }

// ── MIC ──
export async function micToggle(enable: boolean) { const { data } = await api.post('/api/mic', { enable }); return data as { enabled: boolean } }
export async function micStatus() { const { data } = await api.get('/api/mic'); return data as { enabled: boolean; info: Record<string, unknown>; has_segment: boolean; segment_size: number } }
export async function getMicAudio() { const { data } = await api.get('/api/mic/audio'); return data as { ok: boolean; data: string; size: number } }

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
export async function deleteTask(id: string) { const { data } = await api.delete(`/api/tasks/${id}`); return data as { ok: boolean } }
export async function runTask(id: string) { const { data } = await api.post(`/api/tasks/${id}/run`); return data as { ok: boolean; error?: string } }
export async function stopTask() { const { data } = await api.post('/api/tasks/stop'); return data as { ok: boolean } }
export async function getTaskStatus() { const { data } = await api.get('/api/tasks/status'); return data as TaskStatus }
export async function getCapabilities() { const { data } = await api.get('/api/capabilities'); return data as { capabilities: Capability[] } }
export interface RobotResource { resource_key: string; name: string; version: string; type: string }
export async function getResources() { const { data } = await api.get('/api/resources'); return data as { ok: boolean; error?: string; resources: RobotResource[] } }
export async function getCameras() { const { data } = await api.get('/api/cameras'); return data as { cameras: { id: string; label: string; topic: string; active: boolean; selected: boolean }[] } }
export async function switchCamera(cameraId: string) { const { data } = await api.post('/api/camera/switch', { camera_id: cameraId }); return data as { ok: boolean; error?: string } }

// ── 拍照 ──
export async function takePhoto() {
  const { data } = await api.post('/api/photo')
  return data as { ok: boolean; path?: string }
}
