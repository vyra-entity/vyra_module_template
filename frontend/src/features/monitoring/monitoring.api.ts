/**
 * API Client for Hardware Monitoring
 */

const API_BASE = '/{{ module_name }}/api'

export interface HardwareNode {
  node_id: string
  hostname: string
  container_manager_url: string
  role: string
  cpu_cores: number
  memory_total_gb: number
  memory_available_gb: number
  disk_total_gb: number
  disk_available_gb: number
  capabilities: {
    gpu: boolean
    high_memory: boolean
    high_cpu: boolean
    ssd: boolean
    custom_tags: string[]
  }
  is_healthy: boolean
  deployed_modules: number
  load_score: number
  last_health_check: string
}

export interface NodeStats {
  cpu: {
    percent: number
    count: number
  }
  memory: {
    usage_mb: number
    limit_mb: number
    percent: number
  }
  disk: {
    total_mb: number
    available_mb: number
    percent: number
  }
  network: {
    rx_mb_per_sec: number
    tx_mb_per_sec: number
  }
}

export interface ModuleStats {
  module_name: string
  instance_id: string
  node_id?: string
  status: string
  cpu?: {
    percent: number
    count: number
  }
  memory?: {
    usage_mb: number
    limit_mb: number
    percent: number
  }
  uptime_seconds?: number
}

class MonitoringApi {
  async getHardwareNodes(): Promise<HardwareNode[]> {
    const response = await fetch(`${API_BASE}/hardware/nodes`)
    if (!response.ok) {
      throw new Error('Failed to fetch hardware nodes')
    }
    const data = await response.json()
    return data.nodes || []
  }

  async getNodeStats(nodeId: string): Promise<NodeStats> {
    const response = await fetch(`${API_BASE}/hardware/nodes/${nodeId}/stats`)
    if (!response.ok) {
      throw new Error(`Failed to fetch stats for node ${nodeId}`)
    }
    return await response.json()
  }

  async getAllModuleStats(): Promise<ModuleStats[]> {
    const response = await fetch(`${API_BASE}/hardware/modules/stats/all`)
    if (!response.ok) {
      throw new Error('Failed to fetch module stats')
    }
    const data = await response.json()
    return data.modules || []
  }

  async getModuleStats(moduleName: string, instanceId: string, nodeId?: string): Promise<ModuleStats> {
    let url = `${API_BASE}/hardware/modules/${moduleName}/${instanceId}/stats`
    if (nodeId) {
      url += `?node_id=${nodeId}`
    }
    const response = await fetch(url)
    if (!response.ok) {
      throw new Error(`Failed to fetch stats for module ${moduleName}/${instanceId}`)
    }
    const data = await response.json()
    return data.stats
  }
}

export const monitoringApi = new MonitoringApi()
