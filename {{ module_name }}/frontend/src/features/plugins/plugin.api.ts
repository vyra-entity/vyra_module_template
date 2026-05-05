import apiClient from '../../api/http'

/**
 * Plugin Runtime API — HTTP-Client für laufende Plugins
 *
 * Laufzeit-Endpunkte (WASM-Aufrufe, Slot-Auflösung, Assets) laufen unter /plugin/.
 * Verwaltungs-Endpunkte (Install/Uninstall/Pool) → plugin_admin_service/plugin_admin_service.api.ts
 */

export interface PluginCallRequest {
  function_name: string
  data:          Record<string, unknown>
}

export interface PluginCallResponse {
  plugin_id:     string
  function_name: string
  result:        Record<string, unknown>
  success:       boolean
}

export interface UiManifestEntry {
  comp_id:         string
  slot_id:         string
  /** List of scope target IDs (new field; mirrors `scope:` in manifest.yaml). */
  slot_ids:        string[]
  component_name:  string
  js_entry_point:  string
  plugin_id:       string
  version:         string
  assignment_id:   string
  is_active:       boolean
  scope_type:      string
  scope_target:    string | null
  slot_scope_type: string | null
  slot_scope_target: string | null
  is_frontend_scope: boolean
  ui_binding_id:   string | null
  communication_module_name: string | null
  hosting_module_name: string
  /** Human-readable plugin title shown in UI. */
  title:           string
  /** Render priority (lower = rendered first). Default: 50. */
  priority:        number
  /** Minimum user role required to see/use this plugin. */
  min_user_role:   string
  /** Search keywords used by the global search-provider. */
  search_keywords: string[]
  /** Icon asset URL or PrimeIcons class name. */
  icon:            string | null
  /** Slot category type (mirrors SlotCategory). */
  slot_type:       string
}

export interface ResolvePluginsResponse {
  scope_type:      string
  scope_target:    string | null
  p_id:            string | null
  ui_slots:        Record<string, UiManifestEntry[]>
  plugin_metadata: Array<{
    p_id:           string
    plugin_name_id: string
    version:        string
    metadata_json:  Record<string, unknown> | null
    checksum:       string | null
    is_verified:    boolean
    installed_at:   string | null
  }>
}

export const pluginApi = {
  /**
   * Generischer Plugin-Funktionsaufruf (WASM-Runtime im Backend).
   */
  async callPlugin(
    pluginId:     string,
    functionName: string,
    data:         Record<string, unknown> = {}
  ): Promise<PluginCallResponse> {
    const body: PluginCallRequest = { function_name: functionName, data }
    const res = await apiClient.post(`/plugin/${pluginId}/call`, body)
    return res.data
  },

  /** Resolve slot manifest for a scope (from DB) */
  async resolvePlugins(params?: {
    scope_type?:   string
    scope_target?: string
    module_name?:  string
    module_id?:    string
    p_id?:         string
  }): Promise<ResolvePluginsResponse> {
    const res = await apiClient.get('/plugin/resolve_plugins', { params: {
      scope_type:   params?.scope_type,
      scope_target: params?.scope_target,
      module_name:  params?.module_name,
      module_id:    params?.module_id,
      p_id:         params?.p_id,
    }})
    console.log('Resolved plugins:', res.data)
    return res.data
  },
}
