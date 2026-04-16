/**
 * API Client for Authentication (session-based)
 */

const API_BASE = '/{{ module_name }}/api'

export interface LoginRequest {
  username: string
  password: string
  auth_mode?: 'local' | 'usermanager'
}

export interface UserManagerStatus {
  available: boolean
  message: string
}

export interface LocalUser {
  username: string
  email?: string
  role?: string
  level?: number
  enabled?: boolean
  lock_edit?: boolean
  created_at?: string
  last_login?: string
}

export interface LoginResponse {
  success: boolean
  token: string
  username: string
  auth_mode: string
  message: string
}

export interface UserInfo {
  username: string
  user_id: number
  role: string
  level: number
  token: string
  module_id: string
}

class AuthApi {
  /** Safely extract an error message from a Response without assuming JSON. */
  private async _errorMessage(response: Response, fallback: string): Promise<string> {
    const ct = response.headers.get('content-type') ?? ''
    if (ct.includes('application/json')) {
      try {
        const body = await response.json()
        const detail = body.detail
        if (typeof detail === 'string') return detail
        if (Array.isArray(detail)) return detail.map((e: any) => e.msg ?? JSON.stringify(e)).join('; ')
        return body.message || fallback
      } catch {
        // JSON parse failed despite content-type header
      }
    }
    return `${fallback} (HTTP ${response.status})`
  }

  async login(request: LoginRequest): Promise<LoginResponse> {
    const response = await fetch(`${API_BASE}/auth/login`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(request),
      credentials: 'include',
    })

    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Login failed'))
    }

    return await response.json()
  }

  async logout(): Promise<void> {
    const response = await fetch(`${API_BASE}/auth/logout`, {
      method: 'POST',
      credentials: 'include',
    })

    if (!response.ok) {
      throw new Error('Logout failed')
    }
  }

  async verifyToken(): Promise<UserInfo | null> {
    try {
      const response = await fetch(`${API_BASE}/auth/verify`, {
        credentials: 'include',
      })

      if (!response.ok) return null

      const data = await response.json()
      return data.user ?? null
    } catch (error) {
      console.error('Token verification failed:', error)
      return null
    }
  }

  async changePassword(oldPassword: string, newPassword: string): Promise<void> {
    const response = await fetch(`${API_BASE}/auth/change-password`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        old_password: oldPassword,
        new_password: newPassword,
      }),
      credentials: 'include',
    })

    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Password change failed'))
    }
  }

  async checkUserManagerAvailable(): Promise<UserManagerStatus> {
    try {
      const response = await fetch(`${API_BASE}/auth/check-usermanager`, {
        credentials: 'include',
      })
      if (!response.ok) return { available: false, message: 'Nicht erreichbar' }
      return await response.json()
    } catch {
      return { available: false, message: 'Kein externer UserManager erreichbar' }
    }
  }

  async listLocalUsers(): Promise<LocalUser[]> {
    const response = await fetch(`${API_BASE}/auth/users`, {
      credentials: 'include',
    })
    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Failed to list users'))
    }
    const data = await response.json()
    return data.users ?? []
  }

  async createLocalUser(username: string, password: string, role: string = 'viewer'): Promise<void> {
    const response = await fetch(`${API_BASE}/auth/users`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, password, role }),
      credentials: 'include',
    })
    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Failed to create user'))
    }
  }

  async deleteLocalUser(username: string): Promise<void> {
    const response = await fetch(`${API_BASE}/auth/users/${encodeURIComponent(username)}`, {
      method: 'DELETE',
      credentials: 'include',
    })
    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Failed to delete user'))
    }
  }
}

export const authApi = new AuthApi()
