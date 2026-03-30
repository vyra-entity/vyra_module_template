import apiClient from '../../api/http'

/**
 * Plugin Runtime API — HTTP client for running plugins.
 *
 * Runtime endpoints (WASM calls, slot resolution) are under /plugin/.
 * Admin endpoints (install/uninstall/pool) → plugin_admin_service/plugin_admin_service.api.ts
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
  slot_id:        string
  component_name: string
  js_entry_point: string
  plugin_id:      string
  version:        string
  assignment_id:  string
  is_active:      boolean
  scope_type:     string
  scope_target:   string | null
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
   * Generic plugin function call (WASM runtime in the backend).
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
    return res.data
  },
}

