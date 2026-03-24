/**
 * Sidebar Pinia Store
 *
 * Manages collapse state (persisted to localStorage) and the registry of
 * navigation items.  Static items for the 4 built-in routes are registered
 * here; plugins can call registerItem() to add their own entries at runtime.
 */
import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import type { SidebarNavItem, SidebarNavGroup, SidebarGroup } from '../types/sidebar'

const STORAGE_KEY = 'vyra:sidebar:collapsed'

/** Visual order and labels for the available groups */
const GROUP_CONFIG: { id: SidebarGroup; label: string; order: number }[] = [
  { id: 'main',     label: 'Navigation',   order: 0 },
  { id: 'analysis', label: 'Analyse',      order: 1 },
  { id: 'system',   label: 'System',       order: 2 },
  { id: 'settings', label: 'Einstellungen', order: 3 },
]

/** Built-in navigation items for {{ module_name }} */
const DEFAULT_ITEMS: SidebarNavItem[] = [
  {
    id:        'home',
    label:     'Home',
    icon:      'pi pi-home',
    routeName: 'home',
    group:     'main',
    priority:  100,
  },
  {
    id:        'modules',
    label:     'Module',
    icon:      'pi pi-box',
    routeName: 'modules',
    group:     'main',
    priority:  90,
  },
  {
    id:        'repository',
    label:     'Repository',
    icon:      'pi pi-cloud-download',
    routeName: 'repository',
    group:     'main',
    priority:  80,
  },
  {
    id:        'installed-plugins',
    label:     'Plugins',
    icon:      'pi pi-th-large',
    routeName: 'installed-plugins',
    group:     'main',
    priority:  73,
  },
  {
    id:        'monitoring',
    label:     'Monitoring',
    icon:      'pi pi-chart-line',
    routeName: 'monitoring',
    group:     'analysis',
    priority:  100,
  },
  {
    id:        'settings',
    label:     'Einstellungen',
    icon:      'pi pi-cog',
    routeName: 'settings',
    group:     'system',
    priority:  100,
  },
]

export const useSidebarStore = defineStore('sidebar', () => {
  // ─── Collapse state (persisted) ────────────────────────────────────────────
  const isCollapsed = ref<boolean>(
    localStorage.getItem(STORAGE_KEY) === 'true'
  )

  function toggleCollapse(): void {
    isCollapsed.value = !isCollapsed.value
    localStorage.setItem(STORAGE_KEY, String(isCollapsed.value))
  }

  function setCollapsed(value: boolean): void {
    isCollapsed.value = value
    localStorage.setItem(STORAGE_KEY, String(value))
  }

  // ─── Item registry ──────────────────────────────────────────────────────────
  const navItems = ref<SidebarNavItem[]>([...DEFAULT_ITEMS])

  function registerItem(item: SidebarNavItem): void {
    const existing = navItems.value.findIndex(i => i.id === item.id)
    if (existing !== -1) {
      navItems.value[existing] = item   // update if already registered
    } else {
      navItems.value.push(item)
    }
  }

  function unregisterItem(id: string): void {
    const idx = navItems.value.findIndex(i => i.id === id)
    if (idx !== -1) navItems.value.splice(idx, 1)
  }

  function updateBadge(id: string, count: number): void {
    const item = navItems.value.find(i => i.id === id)
    if (item) item.badge = count > 0 ? count : undefined
  }

  // ─── Computed: items grouped and sorted ────────────────────────────────────
  const groupedItems = computed<SidebarNavGroup[]>(() => {
    const result: SidebarNavGroup[] = []

    for (const group of GROUP_CONFIG) {
      const items = navItems.value
        .filter(i => i.group === group.id)
        .sort((a, b) => b.priority - a.priority)

      if (items.length > 0) {
        result.push({ id: group.id, label: group.label, items })
      }
    }
    return result
  })

  return {
    // state
    isCollapsed,
    navItems,
    // getters
    groupedItems,
    // actions
    toggleCollapse,
    setCollapsed,
    registerItem,
    unregisterItem,
    updateBadge,
  }
})
