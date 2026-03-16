import apiClient from '../../api/http'
import type { ModuleInstance, OperationTask, Repository } from '../../types/common'

/**
 * Operation response from backend
 */
interface OperationResponse {
  operation_id: string
  operation_type: string
  status: string
  progress: number
  message: string
  module_name?: string
  instance_id: string
  error: string
  started_at: string
  completed_at: string
  status_url: string
  tasks: OperationTask[]
}

/**
 * API calls for module instances
 */
export const moduleInstanceApi = {
  /**
   * Get all installed module instances
   */
  async getInstances(includeHidden = true): Promise<Record<string, ModuleInstance[]>> {
    const params = new URLSearchParams({
      include_hidden: includeHidden.toString()
    })
    const response = await apiClient.get(`/modules/instances?${params}`)
    return response.data.modules || {}
  },

  /**
   * Delete a module instance
   */
  async deleteInstance(moduleId: string): Promise<OperationResponse> {
    const response = await apiClient.delete(`/modules/instances/${moduleId}`)
    return response.data
  },

  /**
   * Update a module instance
   */
  async updateInstance(
    moduleName: string, 
    moduleId: string, 
    version: string,
    repository: Repository,
    updateAllInstances: boolean = true): Promise<OperationResponse> {
    const response = await apiClient.post(`/modules/update`, {
      module_name: moduleName,
      module_id: moduleId,
      version: version,
      repository: repository,
      update_all_instances: updateAllInstances
    })
    return response.data
  },

  /**
   * Check for available updates across all modules
   */
  async checkUpdates(): Promise<{updates_available: Record<string, any>, checked_at: string}> {
    const response = await apiClient.get('/modules/updates/check')
    return response.data
  },

  /**
   * Set primary instance
   */
  async setPrimaryInstance(moduleName: string, instanceId: string): Promise<OperationResponse> {
    const response = await apiClient.post(`/modules/primary/${moduleName}/${instanceId}`)
    return response.data
  },

  /**
   * Restart a module instance (reloads NFS interfaces)
   */
  async restartInstance(instanceId: string): Promise<OperationResponse> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/restart`)
    return response.data
  },

  /**
   * Stop a module instance (sets enable=false)
   */
  async stopInstance(instanceId: string): Promise<OperationResponse> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/stop`)
    return response.data
  },

  /**
   * Start a module instance (sets enable=true)
   */
  async startInstance(instanceId: string): Promise<OperationResponse> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/start`)
    return response.data
  },

  // ---- Proxy calls (via Zenoh to remote module) ----

  /**
   * Fetch the interface list of a module instance via Zenoh proxy
   */
  async getInstanceInterfaces(instanceId: string): Promise<Record<string, any>> {
    const response = await apiClient.get(`/modules/instances/${instanceId}/interfaces`)
    return response.data
  },

  /**
   * Read current 3-layer state from target module
   */
  async getInstanceState(instanceId: string): Promise<Record<string, any>> {
    const response = await apiClient.get(`/modules/instances/${instanceId}/state`)
    return response.data
  },

  /**
   * Read all parameters of a module instance via Zenoh proxy
   */
  async getInstanceParams(instanceId: string): Promise<Record<string, any>> {
    const response = await apiClient.get(`/modules/instances/${instanceId}/params`)
    return response.data
  },

  /**
   * Read all volatile values of a module instance via Zenoh proxy
   */
  async getInstanceVolatiles(instanceId: string): Promise<Record<string, any>> {
    const response = await apiClient.get(`/modules/instances/${instanceId}/volatiles`)
    return response.data
  },

  /**
   * Set a parameter value on a module instance via Zenoh proxy
   */
  async setInstanceParam(instanceId: string, key: string, value: string): Promise<Record<string, any>> {
    const response = await apiClient.patch(`/modules/instances/${instanceId}/params/${key}`, { value })
    return response.data
  },

  /**
   * Create a new parameter (strict: fails if already exists)
   */
  async createInstanceParam(instanceId: string, key: string, value: string): Promise<Record<string, any>> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/params/${key}`, { value })
    return response.data
  },

  /**
   * Create a new parameter with full metadata and validation.
   */
  async createInstanceParamFull(
    instanceId: string,
    param: {
      name: string
      default_value: unknown
      type: string
      description: string
      displayname?: string
      visible?: boolean
      editable?: boolean
      min_value?: string | null
      max_value?: string | null
      range_value?: Record<string, unknown> | null
    }
  ): Promise<Record<string, any>> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/params`, param)
    return response.data
  },

  /**
   * Update display metadata (displayname, visible, editable) for an existing parameter.
   */
  async updateInstanceParamMeta(
    instanceId: string,
    key: string,
    meta: {
      displayname?: string
      visible?: boolean
      editable?: boolean
    }
  ): Promise<Record<string, any>> {
    const response = await apiClient.patch(`/modules/instances/${instanceId}/params/${key}/meta`, meta)
    return response.data
  },

  /**
   * Set a volatile value on a module instance via Zenoh proxy
   */
  async setInstanceVolatile(instanceId: string, key: string, value: string): Promise<Record<string, any>> {
    const response = await apiClient.patch(`/modules/instances/${instanceId}/volatiles/${key}`, { value })
    return response.data
  },

  /**
   * Create a new volatile (fails if already exists)
   */
  async createInstanceVolatile(instanceId: string, key: string, value: string): Promise<Record<string, any>> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/volatiles/${key}`, { value })
    return response.data
  },

  /**
   * Call an arbitrary function on a module instance via Zenoh proxy
   */
  async callInstanceFunction(
    instanceId: string,
    functionName: string,
    payload: Record<string, any> = {}
  ): Promise<Record<string, any>> {
    const response = await apiClient.post(
      `/modules/instances/${instanceId}/call/${functionName}`,
      payload
    )
    return response.data
  },

  // ---- Lifecycle control ----

  /**
   * Suspend a module instance (ACTIVE → SUSPENDED).
   * Calls request_lc_suspend action server on the target module.
   * Returns { success, message, final_state }.
   */
  async suspendInstance(instanceId: string): Promise<{ success: boolean; message: string; final_state: string }> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/suspend`)
    return response.data
  },

  /**
   * Resume a suspended module instance (SUSPENDED → ACTIVE).
   * Calls request_lc_resume action server on the target module.
   * Returns { success, message, final_state }.
   */
  async resumeInstance(instanceId: string): Promise<{ success: boolean; message: string; final_state: string }> {
    const response = await apiClient.post(`/modules/instances/${instanceId}/resume`)
    return response.data
  },

  /**
   * Subscribe to live log stream from a module instance via SSE.
   *
   * @param instanceId - UUID of the module instance
   * @param history    - Number of historical log lines to replay first (0–10000)
   * @param onMessage  - Callback invoked for each log entry
   * @returns EventSource instance (call .close() to unsubscribe)
   */
  subscribeToInstanceLogs(
    instanceId: string,
    onMessage: (entry: Record<string, any>) => void,
    history = 0
  ): EventSource {
    const baseUrl = apiClient.defaults.baseURL ?? ''
    const url = `${baseUrl}/modules/instances/${instanceId}/logs?history=${history}`
    const es = new EventSource(url)
    es.onmessage = (event) => {
      try {
        const data = JSON.parse(event.data)
        if (data?.type !== 'ping') {
          onMessage(data)
        }
      } catch {
        // ignore parse errors
      }
    }
    return es
  },

  /**
   * Subscribe to live feed data from a named feeder function via SSE.
   *
   * @param instanceId  - UUID of the module instance
   * @param feedName    - Feeder function name (must match a 'feeder' namespace interface)
   * @param onMessage   - Callback invoked for each data payload (pings are filtered out)
   * @returns EventSource instance (call .close() to unsubscribe)
   */
  subscribeToFeed(
    instanceId: string,
    feedName: string,
    onMessage: (data: Record<string, any>) => void
  ): EventSource {
    const baseUrl = apiClient.defaults.baseURL ?? ''
    const url = `${baseUrl}/modules/instances/${instanceId}/feeds/${encodeURIComponent(feedName)}`
    const es = new EventSource(url)
    es.onmessage = (event) => {
      try {
        const data = JSON.parse(event.data)
        if (data?.type !== 'ping') {
          onMessage(data)
        }
      } catch {
        // ignore parse errors
      }
    }
    return es
  },
}