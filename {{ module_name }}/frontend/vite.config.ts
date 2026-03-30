import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import { fileURLToPath, URL } from 'node:url'

export default defineConfig({
  plugins: [vue()],
  base: '/{{ module_name }}/',
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
  server: {
    port: 3000,
    host: '0.0.0.0',
    hmr: {
      clientPort: 3000,
      protocol: 'ws',
      host: 'localhost'
    },
    proxy: {
      '/{{ module_name }}/api': {
        target: 'https://{{ module_name }}:8443',
        changeOrigin: true,
        secure: false,
        rewrite: (path) => path.replace(/^\/{{ module_name }}/, '')
      },
      '/{{ module_name }}/ws': {
        target: 'wss://{{ module_name }}:8443',
        changeOrigin: true,
        secure: false,
        ws: true,
        rewrite: (path) => path.replace(/^\/{{ module_name }}/, '')
      }
    }
  },
  build: {
    outDir: 'dist',
    assetsDir: 'assets',
    rollupOptions: {
      output: {
        assetFileNames: '[name]-[hash][extname]',
        chunkFileNames: '[name]-[hash].js',
        entryFileNames: '[name]-[hash].js'
      }
    }
  }
})
