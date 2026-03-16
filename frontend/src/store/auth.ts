/**
 * Pinia Store for Authentication
 */
import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import { authApi, type UserInfo } from '../api/auth.api'

export const useAuthStore = defineStore('auth', () => {
  // State
  const user = ref<UserInfo | null>(null)
  const isAuthenticated = ref(false)
  const isLoading = ref(false)
  const userManagerAvailable = ref(false)

  // Computed
  const username = computed(() => user.value?.username || '')

  // Actions
  async function login(username: string, password: string, authMode: 'local' | 'usermanager' = 'local') {
    isLoading.value = true
    try {
      const response = await authApi.login({
        username,
        password,
        auth_mode: authMode
      })

      if (response.success) {
        // Verify token immediately after login
        await verifyAuth()
        return true
      }
      return false
    } catch (error) {
      console.error('Login failed:', error)
      throw error
    } finally {
      isLoading.value = false
    }
  }

  async function logout() {
    isLoading.value = true
    try {
      await authApi.logout()
      user.value = null
      isAuthenticated.value = false
    } catch (error) {
      console.error('Logout failed:', error)
    } finally {
      isLoading.value = false
    }
  }

  async function verifyAuth() {
    isLoading.value = true
    try {
      const userInfo = await authApi.verifyToken()
      if (userInfo) {
        user.value = userInfo
        isAuthenticated.value = true
        return true
      } else {
        user.value = null
        isAuthenticated.value = false
        return false
      }
    } catch (error) {
      console.error('Auth verification failed:', error)
      user.value = null
      isAuthenticated.value = false
      return false
    } finally {
      isLoading.value = false
    }
  }

  async function checkUserManager() {
    try {
      const status = await authApi.checkUserManagerAvailable()
      userManagerAvailable.value = status.available
    } catch (error) {
      console.error('Failed to check usermanager:', error)
      userManagerAvailable.value = false
    }
  }

  async function changePassword(oldPassword: string, newPassword: string) {
    if (!user.value) {
      throw new Error('No user logged in')
    }

    await authApi.changePassword(user.value.username, oldPassword, newPassword)
  }

  return {
    // State
    user,
    isAuthenticated,
    isLoading,
    userManagerAvailable,

    // Computed
    username,

    // Actions
    login,
    logout,
    verifyAuth,
    checkUserManager,
    changePassword
  }
})
