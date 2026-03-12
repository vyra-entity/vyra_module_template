import { defineStore } from 'pinia'
import { ref, computed, defineAsyncComponent, markRaw } from 'vue'
import { pluginApi } from '../features/plugins/plugin.api'

/**
 * Plugin Store — state management for the plugin slot system.
 *
 * Loads the UI manifest from v2_modulemanager (via this module's backend proxy)
 * and instantiates Vue components lazily via defineAsyncComponent.
 */
export const usePluginStore = defineStore('plugins', () => {
  // -------------------------------------------------------------------------
  // State
  // -------------------------------------------------------------------------
  const slotComponents = ref({})
  const loading        = ref(false)
  const error          = ref(null)
  const manifestLoaded = ref(false)

  // -------------------------------------------------------------------------
  // Getters
  // -------------------------------------------------------------------------
  const hasSlot = (slotId) =>
    computed(() => (slotComponents.value[slotId]?.length ?? 0) > 0)

  // -------------------------------------------------------------------------
  // Actions
  // -------------------------------------------------------------------------

  /**
   * Fetch the UI manifest for a given scope and instantiate all slot components.
   *
   * @param {string} [scopeType='MODULE']   GLOBAL | TEMPLATE | MODULE | INSTANCE
   * @param {string} [scopeTarget]          Optional scope target identifier
   */
  async function resolvePlugins(scopeType = 'MODULE', scopeTarget) {
    loading.value = true
    error.value   = null
    try {
      const manifest = await pluginApi.resolvePlugins({
        scope_type:   scopeType,
        scope_target: scopeTarget,
      })
      const result = {}

      for (const [slotId, entries] of Object.entries(manifest.ui_slots ?? {})) {
        result[slotId] = entries.map(entry => ({
          entry,
          component: markRaw(
            defineAsyncComponent(() => import(/* @vite-ignore */ entry.js_entry_point)),
          ),
        }))
      }

      slotComponents.value = result
      manifestLoaded.value  = true
    } catch (e) {
      error.value = e?.message ?? 'Failed to load plugin manifest'
    } finally {
      loading.value = false
    }
  }

  /**
   * Return the components assigned to a slot.
   *
   * @param {string} slotId
   * @returns {Array}
   */
  function getSlotComponents(slotId) {
    return slotComponents.value[slotId] ?? []
  }

  return {
    slotComponents,
    loading,
    error,
    manifestLoaded,
    hasSlot,
    resolvePlugins,
    getSlotComponents,
  }
})
