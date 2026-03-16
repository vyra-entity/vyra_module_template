import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import type { ModuleInstance } from '../types/common'

export const useModuleStore = defineStore('modules', () => {
  // State
  const modules = ref<ModuleInstance[]>([])
  const loading = ref(false)
  const error = ref<string | null>(null)

  // Getters
  const moduleCount = computed(() => modules.value.length)
  const runningModules = computed(() => 
    modules.value.filter(m => m.status === 'running')
  )
  const stoppedModules = computed(() => 
    modules.value.filter(m => m.status === 'stopped')
  )

  // Actions
  function setModules(newModules: ModuleInstance[]) {
    modules.value = newModules
  }

  function addModule(module: ModuleInstance) {
    modules.value.push(module)
  }

  function updateModule(instanceId: string, updates: Partial<ModuleInstance>) {
    const index = modules.value.findIndex(m => m.instance_id === instanceId)
    if (index !== -1) {
      modules.value[index] = { ...modules.value[index], ...updates }
    }
  }

  function removeModule(instanceId: string) {
    const index = modules.value.findIndex(m => m.instance_id === instanceId)
    if (index !== -1) {
      modules.value.splice(index, 1)
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
    modules,
    loading,
    error,
    // Getters
    moduleCount,
    runningModules,
    stoppedModules,
    // Actions
    setModules,
    addModule,
    updateModule,
    removeModule,
    setLoading,
    setError,
    clearError
  }
})
