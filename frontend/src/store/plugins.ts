import { defineStore } from 'pinia'
import { ref, computed, defineAsyncComponent, markRaw } from 'vue'
import { pluginApi, type UiManifestEntry } from '../features/plugins/plugin.api'

/**
 * Plugin Store — state management for the plugin system
 *
 * - Holds the plugin list from the repository
 * - Loads the UI manifest and instantiates Vue components via defineAsyncComponent
 * - Provides slot assignments for the slot system
 */
export const usePluginStore = defineStore('plugins', () => {
  // -----------------------------------------------------------------------
  // State
  // -----------------------------------------------------------------------
  const loading          = ref(false)
  const error            = ref<string | null>(null)

  /** Loaded Vue components per slot: slot_id → Array of { entry, component } */
  const slotComponents   = ref<Record<string, { entry: UiManifestEntry; component: any }[]>>({})
  const manifestLoaded   = ref(false)

  // -----------------------------------------------------------------------
  // Getters
  // -----------------------------------------------------------------------
  const hasSlot = (slotId: string) => computed(
    () => (slotComponents.value[slotId]?.length ?? 0) > 0
  )

  // -----------------------------------------------------------------------
  // Actions
  // -----------------------------------------------------------------------

  /**
   * Load the UI manifest for a scope and instantiate all components.
   * Uses defineAsyncComponent so Vue lazily fetches each index.js from the backend.
   */
  async function resolvePlugins(scopeType = 'MODULE', scopeTarget?: string) {
    try {
      const manifest = await pluginApi.resolvePlugins({ scope_type: scopeType, scope_target: scopeTarget })
      const result: Record<string, { entry: UiManifestEntry; component: any }[]> = {}

      for (const [slotId, entries] of Object.entries(manifest.ui_slots)) {
        result[slotId] = entries.map(entry => ({
          entry,
          // Lazily imports index.js via ES module dynamic import
          component: markRaw(
            defineAsyncComponent(() =>
              import(/* @vite-ignore */ entry.js_entry_point)
            )
          )
        }))
      }

      slotComponents.value = result
      manifestLoaded.value  = true
    } catch (e: any) {
      error.value = e?.message ?? 'Failed to load UI manifest'
    }
  }

  /** Return components assigned to a slot */
  function getSlotComponents(slotId: string) {
    return slotComponents.value[slotId] ?? []
  }

  return {
    // State
    loading,
    error,
    slotComponents,
    manifestLoaded,
    // Getters
    hasSlot,
    // Actions
    resolvePlugins,
    getSlotComponents,
  }
})
