/**
 * Composable that creates, provides, and injects the Global Plugin API.
 *
 * Usage in App.vue (root):
 *   import { providePluginApi } from './composables/usePluginApi'
 *   providePluginApi()
 *
 * Usage inside a plugin component:
 *   import { usePluginApi } from '<host>/composables/usePluginApi'
 *   const api = usePluginApi()
 */

import { inject, provide } from 'vue'
import { useRouter, useRoute } from 'vue-router'
import { useToast } from 'primevue/usetoast'
import { useAuthStore } from '../store/auth'
import apiClient from '../api/http'
import { useSideDockPopupStore } from '../store/sideDockPopup'
import type {
  PluginGlobalApi,
  PluginGlobalEvents,
  PluginGlobalFunctions,
  PluginGlobalProps,
  FetchOptions,
  NotifyOptions,
  SdpPocketRegistration,
} from '../types/plugin_slots'
import type { Component } from 'vue'

export const PLUGIN_API_INJECTION_KEY = 'vyra-plugin-api'

/**
 * Creates the Global Plugin API and provides it to all child components.
 * Must be called once at the root component (App.vue).
 */
export function providePluginApi(): PluginGlobalApi {
  const authStore = useAuthStore()
  const router = useRouter()
  const route = useRoute()
  const toast = useToast()

  const apiBase = (apiClient.defaults.baseURL ?? '').replace(/\/$/, '')

  const props: PluginGlobalProps = {
    get currentUser() {
      const u = authStore.user
      if (!u) return null
      return {
        username: u.username,
        role: 'operator' as const, // role field not in UserInfo yet
      }
    },
    get theme() {
      return document.documentElement.classList.contains('p-dark') ? 'dark' : 'light'
    },
    get systemLanguage() {
      return navigator.language.split('-')[0] ?? 'en'
    },
    get activeContext() {
      return String(route.name ?? route.path)
    },
  }

  const events: PluginGlobalEvents = {
    notify(options: NotifyOptions) {
      toast.add({
        severity: options.severity,
        summary: options.message,
        life: options.duration ?? 3000,
      })
    },
    navigationRequest(target: string) {
      if (target.startsWith('http') || target.startsWith('//')) {
        window.open(target, '_blank', 'noopener,noreferrer')
      } else {
        router.push(target)
      }
    },
    criticalError(error: Error) {
      console.error('[PluginGlobalApi] criticalError:', error)
      toast.add({
        severity: 'error',
        summary: 'Plugin Error',
        detail: error.message,
        life: 8000,
      })
    },
  }

  const functions: PluginGlobalFunctions = {
    async apiFetch(url: string, options?: FetchOptions) {
      const { useModuleBase, ...fetchInit } = options ?? {}
      const resolvedUrl = useModuleBase
        ? `${apiBase}/${url.replace(/^\//, '')}`
        : url
      return fetch(resolvedUrl, {
        credentials: 'include',
        ...fetchInit,
        headers: {
          'Content-Type': 'application/json',
          'Accept': 'application/json',
          ...((fetchInit.headers ?? {}) as Record<string, string>),
        },
      })
    },
    async getSetting(key: string) {
      const raw = localStorage.getItem(`vyra_plugin_setting_${key}`)
      return raw !== null ? JSON.parse(raw) : undefined
    },
    async setSetting(key: string, value: unknown) {
      localStorage.setItem(`vyra_plugin_setting_${key}`, JSON.stringify(value))
    },
    openModal(componentName: string, props?: Record<string, unknown>) {
      console.warn('[PluginGlobalApi] openModal not yet implemented:', componentName, props)
    },
    trackEvent(eventName: string, payload?: Record<string, unknown>) {
      console.debug('[PluginGlobalApi] trackEvent:', eventName, payload)
    },
    registerSdpPocket(registration: SdpPocketRegistration, component: unknown) {
      const sdpStore = useSideDockPopupStore()
      sdpStore.registerPocket({
        id: registration.id,
        title: registration.title,
        icon: registration.icon,
        section: registration.section,
        priority: registration.priority ?? 50,
        contextScope: registration.contextScope ?? [],
        pluginId: registration.id,
        component: component as Component,
        isPinnable: registration.isPinnable ?? true,
      })
    },
    unregisterSdpPocket(id: string) {
      const sdpStore = useSideDockPopupStore()
      sdpStore.unregisterPocket(id)
    },
  }

  const api: PluginGlobalApi = { props, events, functions }
  provide(PLUGIN_API_INJECTION_KEY, api)
  return api
}

/**
 * Returns the Global Plugin API injected by the host.
 * Use this inside plugin components to access host context and helpers.
 */
export function usePluginApi(): PluginGlobalApi | undefined {
  return inject<PluginGlobalApi>(PLUGIN_API_INJECTION_KEY)
}
