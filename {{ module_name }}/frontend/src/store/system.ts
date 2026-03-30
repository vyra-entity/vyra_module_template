import { defineStore } from 'pinia'
import { ref } from 'vue'

export interface SystemStats {
  cpu: number
  ram: number
  disk: number
  network: number
  uptime: string
}

export const useSystemStore = defineStore('system', () => {
  // State
  const backendStatus = ref<'running' | 'stopped' | 'checking'>('checking')
  const stats = ref<SystemStats>({
    cpu: 0,
    ram: 0,
    disk: 0,
    network: 0,
    uptime: '0h'
  })

  // Actions
  function setBackendStatus(status: 'running' | 'stopped' | 'checking') {
    backendStatus.value = status
  }

  function updateStats(newStats: Partial<SystemStats>) {
    stats.value = { ...stats.value, ...newStats }
  }

  return {
    // State
    backendStatus,
    stats,
    // Actions
    setBackendStatus,
    updateStats
  }
})
