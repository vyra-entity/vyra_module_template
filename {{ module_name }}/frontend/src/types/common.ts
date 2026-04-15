/**
 * Common types used across the application
 */

export interface ApiResponse<T = any> {
  success: boolean
  data?: T
  error?: string
  message?: string
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
