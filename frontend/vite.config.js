// vite.config.js - Für Vite-basierte Vue.js Projekte
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

export default defineConfig({
  plugins: [vue()],
  server: {
    port: 3000,
    host: '0.0.0.0',
    proxy: {
      // Proxy alle /api Requests zum Backend
      '/api': {
        target: 'http://localhost:8443',
        changeOrigin: true,
        secure: false, // für selbst-signierte Zertifikate
      }
    }
  },
  build: {
    outDir: 'dist',
    assetsDir: 'assets',
    rollupOptions: {
      output: {
        // Für Flask static serving
        assetFileNames: '[name]-[hash][extname]',
        chunkFileNames: '[name]-[hash].js',
        entryFileNames: '[name]-[hash].js'
      }
    }
  }
})
