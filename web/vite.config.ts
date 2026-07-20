import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import { VitePWA } from 'vite-plugin-pwa'
import Icons from 'unplugin-icons/vite'

export default defineConfig({
  plugins: [
    vue(),
    Icons({ compiler: 'vue3', autoInstall: true }),
    VitePWA({
      registerType: 'autoUpdate',
      manifest: {
        name: 'ggRobot 控制台',
        short_name: 'ggRobot',
        description: '灵犀 X2 机器人远程控制台',
        theme_color: '#0f172a',
        background_color: '#0f172a',
        display: 'standalone',
        icons: [
          { src: '/icon-192.png', sizes: '192x192', type: 'image/png' },
          { src: '/icon-512.png', sizes: '512x512', type: 'image/png' },
        ],
      },
    }),
  ],
  resolve: {
    alias: { '@': '/src' },
  },
  server: {
    host: '0.0.0.0',
  },
  base: '/',
})
