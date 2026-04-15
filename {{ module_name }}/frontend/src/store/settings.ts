import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import apiClient from '../api/http'

/** Derive the localStorage key from the module's API base URL at runtime */
const SETTINGS_KEY = `vyra_${(apiClient.defaults.baseURL ?? '').replace(/\/api$/, '').replace(/^\//, '')}_settings`

export interface AppSettings {
  theme: 'light' | 'dark' | 'auto'
  language: string
  notifications: boolean
  autoRefresh: boolean
  refreshInterval: number
}

const DEFAULT_SETTINGS: AppSettings = {
  theme: 'light',
  language: 'de',
  notifications: true,
  autoRefresh: true,
  refreshInterval: 30
}

/**
 * Global Settings Store for {{ module_name }}.
 * Manages application-wide settings like theme, language, notifications, etc.
 */
export const useSettingsStore = defineStore('settings', () => {
  const settings = ref<AppSettings>({ ...DEFAULT_SETTINGS })

  /** Apply the current theme setting to the document root element. */
  const applyTheme = () => {
    const dark =
      settings.value.theme === 'dark' ||
      (settings.value.theme === 'auto' &&
        window.matchMedia('(prefers-color-scheme: dark)').matches)
    if (dark) {
      document.documentElement.classList.add('dark-mode')
    } else {
      document.documentElement.classList.remove('dark-mode')
    }
  }

  const loadSettings = () => {
    try {
      const stored = localStorage.getItem(SETTINGS_KEY)
      if (stored) {
        const parsed = JSON.parse(stored)
        settings.value = { ...DEFAULT_SETTINGS, ...parsed }
      }
    } catch (error) {
      console.error('Failed to load settings:', error)
    }
    applyTheme()
  }

  const saveSettings = () => {
    try {
      localStorage.setItem(SETTINGS_KEY, JSON.stringify(settings.value))
    } catch (error) {
      console.error('Failed to save settings:', error)
    }
  }

  const isDarkMode = computed(() => {
    if (settings.value.theme === 'auto') {
      return window.matchMedia('(prefers-color-scheme: dark)').matches
    }
    return settings.value.theme === 'dark'
  })

  const updateSettings = (newSettings: Partial<AppSettings>) => {
    settings.value = { ...settings.value, ...newSettings }
    saveSettings()
  }

  const setTheme = (theme: 'light' | 'dark' | 'auto') => {
    settings.value.theme = theme
    saveSettings()
    applyTheme()
  }

  const setLanguage = (language: string) => {
    settings.value.language = language
    saveSettings()
  }

  const toggleNotifications = () => {
    settings.value.notifications = !settings.value.notifications
    saveSettings()
  }

  const resetSettings = () => {
    settings.value = { ...DEFAULT_SETTINGS }
    saveSettings()
    applyTheme()
  }

  loadSettings()

  return {
    settings,
    isDarkMode,
    updateSettings,
    setTheme,
    setLanguage,
    toggleNotifications,
    resetSettings
  }
})
