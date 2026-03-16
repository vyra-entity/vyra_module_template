/**
 * Common types used across the application
 */

export interface ApiResponse<T = any> {
  success: boolean
  data?: T
  error?: string
  message?: string
}

export interface ModuleInstance {
  module_name: string
  instance_id: string
  version: string
  /** Legacy coarse-grained status from Docker – prefer using the live state fields below */
  status: 'running' | 'stopped' | 'error' | 'unknown'
  /** Module template type (e.g. 'basic', 'slim') – from repository metadata */
  template?: string
  /** Repository metadata labels: flags, icon, checksum, size, synced_at */
  labels?: {
    flags?: {
      frontend_active?: boolean
      backend_active?: boolean
    }
    icon?: string
    checksum?: string
    size?: number
    synced_at?: string
  }
  path?: string              // Added for file paths
  author?: string
  frontend_url?: string
  description?: string
  permissions?: {
    visible?: boolean
    removable?: boolean
    updatable?: boolean
    protected?: boolean
    multi_instance?: boolean
  }
  primary?: boolean
  has_updates?: boolean
  available_updates?: Array<{
    repository_id: string
    repository_name: string
    repository_type: string
    available_version: string
    module_hash: string
    description?: string
  }>
}

export interface RepositoryModule {
  id: string
  name: string
  displayName: string
  version: string
  description: string
  author: string
  template: string
  icon: string
  license: string
  status: 'available' | 'installed' | 'update'
  dependencies?: {
    vyra_modules?: string[]
    python?: string[]
    system?: string[]
  }
  installed_count?: number
}

export interface Repository {
  id: string
  name: string
  displayName?: string  // Computed from name if not provided
  url: string
  type: 'local' | 'https'
  priority: number
  disabled: boolean
  description?: string
  stats?: {
    total_modules: number
    installed_modules: number
    available_modules: number
    last_updated: string | null
  }
  modules?: RepositoryModule[]
}

/**
 * Operation status tracking types
 */
export enum TaskStatus {
  PENDING = 'pending',
  RUNNING = 'running',
  COMPLETED = 'completed',
  FAILED = 'failed',
  SKIPPED = 'skipped'
}

export interface OperationTask {
  id: string
  title: string
  description?: string
  status: TaskStatus
  progress?: number
  error?: string
  started_at?: string
  completed_at?: string
}

/**
 * Module Feed types
 */
export interface ModuleFeed {
  module_name: string
  module_id: string
  feed_type: 'state' | 'error' | 'news'
  message: string
  timestamp: string
  data: Record<string, any>
}

export interface UserPrompt {
  id: string
  type: 'warning' | 'error' | 'info' | 'question'
  title: string
  message: string
  options: Array<{
    label: string
    value: string
    variant?: 'primary' | 'danger' | 'secondary'
  }>
  default_option?: string
}

export interface OperationStatus {
  operation_id: string
  operation_type?: string  // Added for operation tracking
  module_name?: string      // Added for module context
  status: 'pending' | 'running' | 'success' | 'failed' | 'waiting_for_user'
  message?: string
  progress?: number
  tasks: OperationTask[]
  current_task_id?: string
  user_prompt?: UserPrompt
  error?: string
  result?: any
}
