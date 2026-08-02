<script setup lang="ts">
import { ref, computed, onMounted, h } from 'vue'
import { getResources, playResource, type RobotResource } from '@/api/fastapi'
import { NButton, NDataTable, NTag, NSpace, NInput, NSelect, useMessage } from 'naive-ui'
import IconPlay from '~icons/mdi/play'
import IconRefresh from '~icons/mdi/refresh'

const message = useMessage()
const resources = ref<RobotResource[]>([])
const loading = ref(false)
const playing = ref<string | null>(null)
const search = ref('')
const typeFilter = ref<string>('')

const typeOptions = [
  { label: '全部', value: '' },
  { label: '全身动作', value: 'BODY' },
  { label: '手臂动作', value: 'ARM' },
]

// 类型按 resource_key 含 onnx 判断（与后端 _play_resource 的 meta 推断一致）
function rType(r: RobotResource): 'BODY' | 'ARM' {
  return r.resource_key.toLowerCase().includes('onnx') ? 'BODY' : 'ARM'
}

const filtered = computed(() =>
  resources.value.filter(r => {
    if (typeFilter.value && rType(r) !== typeFilter.value) return false
    const q = search.value.trim().toLowerCase()
    if (q && !`${r.name} ${r.resource_key}`.toLowerCase().includes(q)) return false
    return true
  })
)

async function refresh() {
  loading.value = true
  try {
    const res = await getResources()
    resources.value = res.resources || []
    if (res.error) message.warning(res.error)
  } catch {
    message.error('拉取灵创动作失败')
  }
  loading.value = false
}

async function onPlay(r: RobotResource) {
  playing.value = r.resource_key
  try {
    const res = await playResource(r.resource_key, r.version, rType(r))
    // aimdk 可能 code==0 但 message 含 "task(s) failed"，需二次判定
    const failed = !!res.message && /failed|失败/i.test(res.message)
    if (res.ok && !failed) {
      message.success(`已播放：${r.name}`)
    } else {
      message.warning(res.message || res.error || '播放未成功', { duration: 6000 })
    }
  } catch {
    message.error('播放请求失败')
  }
  playing.value = null
}

const columns = [
  { title: '名称', key: 'name', ellipsis: { tooltip: true } },
  {
    title: '类型', key: 'type', width: 90,
    render: (r: RobotResource) => h(NTag, {
      size: 'small', bordered: false,
      type: rType(r) === 'BODY' ? 'success' : 'info',
    }, { default: () => rType(r) === 'BODY' ? '全身' : '手臂' })
  },
  { title: '版本', key: 'version', width: 100, ellipsis: { tooltip: true } },
  { title: 'resource_key', key: 'resource_key', ellipsis: { tooltip: true } },
  {
    title: '操作', key: 'actions', width: 90,
    render: (r: RobotResource) => h(NButton, {
      size: 'tiny', quaternary: true, type: 'primary',
      loading: playing.value === r.resource_key,
      onClick: () => onPlay(r),
    }, { icon: () => h(IconPlay), default: () => '播放' })
  },
]

onMounted(refresh)
</script>

<template>
  <div class="linkcraft">
    <header class="head">
      <div>
        <h1>灵创动作</h1>
        <p>机器人已部署的灵创动作资源 · 共 {{ resources.length }} 个</p>
      </div>
      <NSpace>
        <NInput v-model:value="search" placeholder="搜索名称 / key" clearable size="small" style="width: 180px" />
        <NSelect v-model:value="typeFilter" :options="typeOptions" size="small" style="width: 120px" />
        <NButton size="small" quaternary :loading="loading" @click="refresh">
          <template #icon><IconRefresh /></template>
        </NButton>
      </NSpace>
    </header>

    <NDataTable
      :columns="columns"
      :data="filtered"
      :row-key="(r: RobotResource) => r.resource_key"
      size="small"
      :bordered="false"
    />
  </div>
</template>

<style scoped>
.linkcraft { padding: 32px 0; }
.head { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 24px; }
.head h1 { font-size: 24px; font-weight: 700; margin: 0 0 4px; letter-spacing: -0.02em; }
.head p { margin: 0; font-size: 13px; color: var(--text-secondary); }
</style>
