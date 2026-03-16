import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import type { RepositoryModule } from '../types/common'

export const useRepositoryStore = defineStore('repository', () => {
  // State
  const availableModules = ref<RepositoryModule[]>([])
  const loading = ref(false)
  const error = ref<string | null>(null)

  // Getters
  const moduleCount = computed(() => availableModules.value.length)
  const installedModules = computed(() => 
    availableModules.value.filter(m => m.status === 'installed')
  )
  const notInstalledModules = computed(() => 
    availableModules.value.filter(m => m.status === 'available')
  )

  // Actions
  function setAvailableModules(modules: RepositoryModule[]) {
    availableModules.value = modules
  }

  function updateModuleInstallStatus(moduleId: string, status: 'available' | 'installed' | 'update') {
    const module = availableModules.value.find(m => m.id === moduleId)
    if (module) {
      module.status = status
    }
  }

  function setLoading(value: boolean) {
    loading.value = value
  }

  function setError(message: string | null) {
    error.value = message
  }

  function clearError() {
    error.value = null
  }

  return {
    // State
    availableModules,
    loading,
    error,
    // Getters
    moduleCount,
    installedModules,
    notInstalledModules,
    // Actions
    setAvailableModules,
    updateModuleInstallStatus,
    setLoading,
    setError,
    clearError
  }
})
