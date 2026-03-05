/**
 * Sidebar Pinia Store – plain JavaScript version.
 *
 * Portable: copy this file + the three layout components into any VYRA module.
 * Only dependencies: Vue 3, Pinia, Vue Router.
 */
import { defineStore } from 'pinia'
import { ref, computed } from 'vue'

const STORAGE_KEY = 'vyra:sidebar:collapsed'

/**
 * Available group identifiers.
 * Add more groups here; they must also appear in GROUP_CONFIG.
 */
const GROUP_CONFIG = [
  { id: 'system',   label: 'System',        order: 0 },
  { id: 'main',     label: 'Navigation',    order: 1 },
  { id: 'analysis', label: 'Analyse',       order: 2 },
  { id: 'settings', label: 'Einstellungen', order: 3 },
]

/**
 * Default navigation items for the template.
 * Replace these with the module-specific routes.
 *
 * SidebarNavItem shape:
 *   id        {string}  – unique key
 *   label     {string}  – display text
 *   icon      {string}  – PrimeIcons class, e.g. "pi pi-home"
 *   routeName {string}  – Vue Router named route
 *   group     {string}  – one of GROUP_CONFIG ids
 *   priority  {number}  – higher = closer to top within group
 *   badge     {number?} – notification count (0 or undefined → hidden)
 *   tooltip   {string?} – override for collapsed tooltip
 */
const DEFAULT_ITEMS = [
  {
    id:        'home',
    label:     'Home',
    icon:      'pi pi-home',
    routeName: 'Home',
    group:     'main',
    priority:  100,
  },
]

export const useSidebarStore = defineStore('sidebar', () => {
  // ─── Collapse state (persisted) ──────────────────────────────────────────
  const isCollapsed = ref(localStorage.getItem(STORAGE_KEY) === 'true')

  function toggleCollapse() {
    isCollapsed.value = !isCollapsed.value
    localStorage.setItem(STORAGE_KEY, String(isCollapsed.value))
  }

  function setCollapsed(value) {
    isCollapsed.value = value
    localStorage.setItem(STORAGE_KEY, String(value))
  }

  // ─── Item registry ────────────────────────────────────────────────────────
  const navItems = ref([...DEFAULT_ITEMS])

  function registerItem(item) {
    const existing = navItems.value.findIndex(i => i.id === item.id)
    if (existing !== -1) {
      navItems.value[existing] = item
    } else {
      navItems.value.push(item)
    }
  }

  function unregisterItem(id) {
    const idx = navItems.value.findIndex(i => i.id === id)
    if (idx !== -1) navItems.value.splice(idx, 1)
  }

  function updateBadge(id, count) {
    const item = navItems.value.find(i => i.id === id)
    if (item) item.badge = count > 0 ? count : undefined
  }

  // ─── Computed: items grouped and sorted ───────────────────────────────────
  const groupedItems = computed(() => {
    const result = []

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
    isCollapsed,
    navItems,
    groupedItems,
    toggleCollapse,
    setCollapsed,
    registerItem,
    unregisterItem,
    updateBadge,
  }
})
