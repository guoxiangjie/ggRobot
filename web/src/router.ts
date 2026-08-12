import { createRouter, createWebHistory } from 'vue-router'

const router = createRouter({
  history: createWebHistory(),
  routes: [
    { path: '/', name: 'dashboard', component: () => import('@/views/Dashboard.vue') },
    { path: '/control', name: 'control', component: () => import('@/views/Control.vue') },
    { path: '/task',    name: 'task',    component: () => import('@/views/Task.vue') },
    { path: '/project', name: 'project', component: () => import('@/views/Project.vue') },
    { path: '/slam', name: 'slam', component: () => import('@/views/Slam.vue') },
    { path: '/voice',   name: 'voice',   component: () => import('@/views/Voice.vue') },
    { path: '/camera', name: 'camera', component: () => import('@/views/Camera.vue') },
    { path: '/model', name: 'model', component: () => import('@/views/Model3D.vue') },
    { path: '/media', name: 'media', component: () => import('@/views/Media.vue') },
    { path: '/emoji', name: 'emoji', component: () => import('@/views/Emoji.vue') },
    { path: '/linkcraft', name: 'linkcraft', component: () => import('@/views/Linkcraft.vue') },
    { path: '/system', name: 'system', component: () => import('@/views/System.vue') },
    { path: '/phone', name: 'phone', component: () => import('@/views/Phone.vue'), meta: { fullscreen: true } },
  ],
})

export default router
