<script setup lang="ts">
import { ref, onMounted, h } from 'vue'
import { getMediaList, uploadMedia, deleteMedia, playMedia, type MediaFile } from '@/api/fastapi'
import { NButton, NUpload, NDataTable, NPopconfirm, NSpace, NTag } from 'naive-ui'
import IconUpload from '~icons/mdi/upload'
import IconPlay from '~icons/mdi/play'
import IconDelete from '~icons/mdi/delete'
import IconRefresh from '~icons/mdi/refresh'

const files = ref<MediaFile[]>([])
const loading = ref(false)
const playing = ref<string | null>(null)

async function refresh() {
  loading.value = true
  try { const res = await getMediaList(); files.value = res.files } catch { /* */ }
  loading.value = false
}

async function onUpload({ file }: { file: any }) {
  if (!file.file) return
  await uploadMedia(file.file)
  await refresh()
}

async function onPlay(name: string) {
  playing.value = name
  try { await playMedia(name) } catch { /* */ }
  playing.value = null
}

async function onDelete(name: string) {
  await deleteMedia(name)
  await refresh()
}

function formatSize(bytes: number): string {
  if (bytes < 1024) return `${bytes} B`
  if (bytes < 1024 * 1024) return `${(bytes / 1024).toFixed(1)} KB`
  return `${(bytes / (1024 * 1024)).toFixed(1)} MB`
}

const columns = [
  { title: '文件名', key: 'name', ellipsis: { tooltip: true } },
  { title: '大小', key: 'size', width: 100, render: (r: MediaFile) => formatSize(r.size) },
  {
    title: '类型', key: 'kind', width: 80,
    render: (r: MediaFile) => r.kind === 'video'
      ? h(NTag, { size: 'small', type: 'info', bordered: false }, { default: () => '视频' })
      : h(NTag, { size: 'small', type: 'warning', bordered: false }, { default: () => '音频' })
  },
  {
    title: '操作', key: 'actions', width: 160,
    render: (r: MediaFile) => h(NSpace, { size: 'small' }, {
      default: () => [
        h(NButton, { size: 'tiny', quaternary: true, loading: playing.value === r.name, onClick: () => onPlay(r.name) }, { icon: () => h(IconPlay) }),
        h(NPopconfirm, { onPositiveClick: () => onDelete(r.name) }, {
          trigger: () => h(NButton, { size: 'tiny', quaternary: true }, { icon: () => h(IconDelete) }),
          default: () => '确定删除？',
        }),
      ]
    }),
  },
]

onMounted(refresh)
</script>

<template>
  <div class="media">
    <header class="head">
      <div>
        <h1>媒体</h1>
        <p>上传并播放音视频文件</p>
      </div>
      <NSpace>
        <NUpload :show-file-list="false" accept=".mp3,.wav,.mp4,.avi,.mov" @change="onUpload">
          <NButton size="small" quaternary>
            <template #icon><IconUpload /></template>
            上传
          </NButton>
        </NUpload>
        <NButton size="small" quaternary :loading="loading" @click="refresh">
          <template #icon><IconRefresh /></template>
        </NButton>
      </NSpace>
    </header>

    <NDataTable
      :columns="columns"
      :data="files"
      :row-key="(r: MediaFile) => r.name"
      size="small"
      :bordered="false"
    />
  </div>
</template>

<style scoped>
.media { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 24px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }
</style>
