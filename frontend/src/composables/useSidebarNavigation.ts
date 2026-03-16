/**
 * useSidebarNavigation – plugin API for the sidebar.
 *
 * Any component or plugin that needs to add/remove items from the sidebar
 * should use this composable instead of accessing the store directly.
 * This keeps the store an implementation detail and makes it easy to swap.
 *
 * Usage example (inside a plugin's setup()):
 *   const { registerSidebarItem, unregisterSidebarItem, updateSidebarBadge } =
 *     useSidebarNavigation()
 *
 *   onMounted(() => registerSidebarItem({
 *     id:        'my-plugin',
 *     label:     'Mein Plugin',
 *     icon:      'pi pi-star',
 *     routeName: 'myPlugin',
 *     group:     'main',
 *     priority:  75,
 *   }))
 *
 *   onUnmounted(() => unregisterSidebarItem('my-plugin'))
 */
import { useSidebarStore } from '../store/sidebar'
import type { SidebarNavItem } from '../types/sidebar'

export function useSidebarNavigation() {
  const sidebarStore = useSidebarStore()

  return {
    /** Register or update a sidebar item.  Safe to call multiple times. */
    registerSidebarItem: (item: SidebarNavItem): void => {
      sidebarStore.registerItem(item)
    },

    /** Remove a sidebar item by its id. */
    unregisterSidebarItem: (id: string): void => {
      sidebarStore.unregisterItem(id)
    },

    /**
     * Update the badge count on an item.
     * Pass 0 to hide the badge.
     */
    updateSidebarBadge: (id: string, count: number): void => {
      sidebarStore.updateBadge(id, count)
    },

    /** Current collapse state (readonly computed ref) */
    isCollapsed: sidebarStore.isCollapsed,

    /** Toggle collapse state (e.g. for a custom toggle button) */
    toggleSidebar: (): void => {
      sidebarStore.toggleCollapse()
    },
  }
}
