import apiClient from '../../api/http'

/**
 * Plugin API — HTTP-Client für das Plugin-System
 *
 * Verwaltungsendpunkte laufen unter /plugin_admin_service/.
 * Plugin-Laufzeit-Endpunkte (WASM-Aufrufe, Assets) laufen unter /plugin/.
 */

export interface PluginListEntry {
  id:           string
  name:         string
  version:      string
  description:  string
  status:       string
  scope:        { type: string; target?: string }
  icon?:        string
  /** true wenn bereits in der lokalen DB installiert */
  is_installed: boolean
  /** true wenn Checksum verifiziert wurde */
  is_verified:  boolean
}

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

export interface PluginInstallRequest {
  plugin_id:      string
  version:        string
  scope_type?:    string
  /** Kommagetrennte IDs für INSTANCE-Multi-Scope; leer = alle Instanzen */
  scope_target?:  string
  config_overlay?: Record<string, unknown>
}

export interface PoolEntry {
  p_id:           string
  plugin_name_id: string
  version:        string
  nfs_path:       string
  checksum:       string | null
  is_verified:    boolean
  installed_at:   string | null
  metadata_json:  Record<string, unknown> | null
}

export interface AssignmentResponse {
  assignment_id:     string
  p_id:              string
  plugin_name_id:    string
  version:           string
  scope_type:        string
  scope_target:      string | null
  is_active:         boolean
  config_overlay:    Record<string, unknown> | null
  priority_override: number | null
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
  // -------------------------------------------------------------------------
  // Plugin Admin Service — Verwaltung (/plugin_admin_service/*)
  // -------------------------------------------------------------------------

  /** Alle verfügbaren Plugins aus dem Repository (inkl. is_installed, is_verified) */
  async listPlugins(): Promise<PluginListEntry[]> {
    const res = await apiClient.get('/plugin_admin_service/list')
    return res.data ?? []
  },

  /** Installierte Plugin-Versionen aus der lokalen DB */
  async listPool(): Promise<PoolEntry[]> {
    const res = await apiClient.get('/plugin_admin_service/pool')
    return res.data ?? []
  },

  /** Plugin installieren (container_manager + DB) */
  async installPlugin(req: PluginInstallRequest): Promise<{
    success:   boolean
    plugin_id: string
    version:   string
    nfs_path:  string
    message:   string
  }> {
    const res = await apiClient.post('/plugin_admin_service/install', req)
    return res.data
  },

  /** Plugin deinstallieren */
  async uninstallPlugin(pluginId: string, version: string): Promise<{ success: boolean; message: string }> {
    const res = await apiClient.delete(`/plugin_admin_service/${pluginId}/${version}`)
    return res.data
  },

  /** Alle Plugin-Zuweisungen abrufen (optional gefiltert) */
  async listAssignments(params?: {
    scope_type?:   string
    scope_target?: string
    p_id?:         string
  }): Promise<AssignmentResponse[]> {
    const res = await apiClient.get('/plugin_admin_service/assignments', { params })
    return res.data ?? []
  },

  /** Einzelne Zuweisung abrufen */
  async getAssignment(assignmentId: string): Promise<AssignmentResponse> {
    const res = await apiClient.get(`/plugin_admin_service/assignments/${assignmentId}`)
    return res.data
  },

  /** is_active einer Zuweisung umkehren */
  async toggleAssignment(assignmentId: string): Promise<AssignmentResponse> {
    const res = await apiClient.patch(`/plugin_admin_service/assignments/${assignmentId}/toggle`)
    return res.data
  },

  /** Scope-Targets einer MODULE/INSTANCE-Zuweisung setzen */
  async setScopeTargets(assignmentId: string, moduleIds: string[]): Promise<AssignmentResponse[]> {
    const res = await apiClient.patch(
      `/plugin_admin_service/assignments/${assignmentId}/scope-targets`,
      { module_ids: moduleIds }
    )
    return res.data
  },

  // -------------------------------------------------------------------------
  // Plugin Runtime — Laufzeit (/plugin/*)
  // -------------------------------------------------------------------------

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
    return res.data
  },

  /** URL zu einem Plugin-Asset (JS, CSS, SVG) */
  assetUrl(pluginId: string, version: string, filePath: string): string {
    return `/v2_modulemanager/api/plugin/assets/${pluginId}/${version}/${filePath}`
  }
}

