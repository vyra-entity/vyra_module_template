/**
 * Admin API Client — local user management
 *
 * Provides access to admin-only endpoints for managing local users.
 * These endpoints are only accessible when the module is running in local auth
 * mode and require a valid admin session token.
 */

const API_BASE = '/{{ module_name }}/api'

export interface LocalUser {
  username: string
}

class AdminApi {
  private async _errorMessage(response: Response, fallback: string): Promise<string> {
    const ct = response.headers.get('content-type') ?? ''
    if (ct.includes('application/json')) {
      try {
        const body = await response.json()
        return body.detail || fallback
      } catch {
        // JSON parse failed despite content-type header
      }
    }
    return `${fallback} (HTTP ${response.status})`
  }

  /** List all local users. Requires admin session. */
  async listUsers(): Promise<LocalUser[]> {
    const response = await fetch(`${API_BASE}/auth/users`, {
      credentials: 'include',
    })
    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Failed to list users'))
    }
    const data = await response.json()
    return data.users
  }

  /** Create a new local user. Requires admin session. */
  async createUser(username: string, password: string): Promise<void> {
    const response = await fetch(`${API_BASE}/auth/users`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, password }),
      credentials: 'include',
    })
    if (!response.ok) {
      throw new Error(await this._errorMessage(response, 'Failed to create user'))
    }
  }
}

export const adminApi = new AdminApi()
