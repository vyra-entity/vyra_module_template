import { defineStore } from 'pinia'
import { ref, computed, defineAsyncComponent, markRaw, h } from 'vue'
import { pluginApi, type UiManifestEntry } from '../features/plugins/plugin.api'

/** Silent placeholder rendered when a plugin fails to load or throws at runtime. */
const PluginErrorFallback = markRaw({ render: () => h('span', { style: 'display:none' }) })

function normalizeScopeTarget(scopeTarget?: string): string | undefined {
  const raw = (scopeTarget ?? '').trim()
  if (!raw) {
    return undefined
  }
  // Convert hash-suffixed module instance names to canonical module names.
  return raw.replace(/_[0-9a-f]{32}$/i, '')
}

/**
 * Plugin Store — generic plugin slot loading
 *
 * Loads the UI manifest and instantiates Vue components via defineAsyncComponent.
 * Provides slot assignments for the slot system.
 *
 * Admin operations (plugin list, install/uninstall) live in `usePluginAdminStore`.
 */
export const usePluginStore = defineStore('plugins', () => {
  // -----------------------------------------------------------------------
  // State
  // -----------------------------------------------------------------------
  /** Loaded Vue components per slot: slot_id → Array of { entry, component } */
  const slotComponents = ref<Record<string, { entry: UiManifestEntry; component: any }[]>>({})
  const loadingManifest = ref(false)
  const manifestLoaded = ref(false)
  const error          = ref<string | null>(null)

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
   * Each plugin is wrapped with an error component and onError handler so that
   * a broken plugin never crashes the host application.
   */
  async function resolvePlugins(scopeType = 'MODULE', scopeTarget?: string) {
    loadingManifest.value = true
    error.value = null
    try {
      const normalizedScopeTarget = normalizeScopeTarget(scopeTarget)
      const manifest = await pluginApi.resolvePlugins({
        scope_type: scopeType,
        scope_target: normalizedScopeTarget,
        module_name: normalizedScopeTarget,
      })
      const result: Record<string, { entry: UiManifestEntry; component: any }[]> = {}

      for (const [slotId, entries] of Object.entries(manifest.ui_slots)) {
        result[slotId] = entries.map(entry => ({
          entry,
          // Lazily imports index.js via ES module dynamic import.
          // errorComponent + onError ensure a broken plugin shows nothing and
          // does not propagate the error to the host.
          component: markRaw(
            defineAsyncComponent({
              loader: () => import(/* @vite-ignore */ entry.js_entry_point),
              errorComponent: PluginErrorFallback,
              onError(err, _retry, fail) {
                console.error(`[PluginSlot] Plugin '${entry.plugin_id}' (${entry.js_entry_point}) failed to load:`, err)
                fail()
              },
            })
          )
        }))
      }

      slotComponents.value = result
    } catch (e: any) {
      error.value = e?.message ?? 'Failed to load UI manifest'
      slotComponents.value = {}
    } finally {
      manifestLoaded.value = true
      loadingManifest.value = false
    }
  }

  /** Return components assigned to a slot. */
  function getSlotComponents(slotId: string) {
    return slotComponents.value[slotId] ?? []
  }

  return {
    // State
    slotComponents,
    loadingManifest,
    manifestLoaded,
    error,
    // Getters
    hasSlot,
    // Actions
    resolvePlugins,
    getSlotComponents,
  }
})
