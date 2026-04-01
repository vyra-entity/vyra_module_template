/**
 * Pinia store for persistent UI settings.
 *
 * Settings are serialised to a single localStorage key so they survive
 * page reloads without a backend round-trip.
 */

import { defineStore } from 'pinia'
import { ref, watch } from 'vue'

const STORAGE_KEY = 'vyra:ui-settings'

function loadFromStorage(): Record<string, unknown> {
  try {
    return JSON.parse(localStorage.getItem(STORAGE_KEY) ?? '{}')
  } catch {
    return {}
  }
}

function saveToStorage(data: Record<string, unknown>): void {
  try {
    localStorage.setItem(STORAGE_KEY, JSON.stringify(data))
  } catch {
    // Storage may be unavailable (private mode, quota exceeded), ignore silently.
  }
}

export const useUiSettingsStore = defineStore('uiSettings', () => {
  const stored = loadFromStorage()

  /** Whether Side-Dock-Popup floating widgets are shown. */
  const sideDockPocketEnabled = ref<boolean>((stored.sideDockPocketEnabled as boolean) ?? true)

  watch(sideDockPocketEnabled, (val) => {
    saveToStorage({ ...loadFromStorage(), sideDockPocketEnabled: val })
  })

  return {
    sideDockPocketEnabled,
  }
})
