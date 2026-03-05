/**
 * useSidebarNavigation – plugin API for the sidebar.
 *
 * Use this composable instead of accessing the store directly so that
 * the store remains an implementation detail.
 *
 * Usage:
 *   import { useSidebarNavigation } from '../composables/useSidebarNavigation'
 *
 *   const { registerSidebarItem, unregisterSidebarItem } = useSidebarNavigation()
 *
 *   onMounted(() =>
 *     registerSidebarItem({
 *       id: 'settings', label: 'Einstellungen',
 *       icon: 'pi pi-cog', routeName: 'Settings',
 *       group: 'settings', priority: 50,
 *     })
 *   )
 *   onUnmounted(() => unregisterSidebarItem('settings'))
 */
import { useSidebarStore } from '../store/sidebar'

export function useSidebarNavigation() {
  const sidebarStore = useSidebarStore()

  return {
    /** Register or update a sidebar item. */
    registerSidebarItem: (item) => sidebarStore.registerItem(item),

    /** Remove a sidebar item by id. */
    unregisterSidebarItem: (id) => sidebarStore.unregisterItem(id),

    /**
     * Set the badge count for an item.
     * Pass 0 to hide the badge.
     */
    updateSidebarBadge: (id, count) => sidebarStore.updateBadge(id, count),

    /** Toggle the sidebar collapse state. */
    toggleSidebar: () => sidebarStore.toggleCollapse(),
  }
}
