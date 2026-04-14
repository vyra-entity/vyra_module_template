/**
 * Sidebar type definitions – portable contract for plugin integration.
 *
 * Copy this file (together with VyraSidebar.vue, SidebarNavItem.vue,
 * SidebarNavGroup.vue and store/sidebar.ts) into any VYRA module to
 * get the same sidebar with zero extra dependencies.
 */

/** Navigation groups that define visual sections in the sidebar */
export type SidebarGroup = 'system' | 'main' | 'analysis' | 'settings'

/** A single navigation item registered by a page or plugin */
export interface SidebarNavItem {
  /** Unique identifier – used for active-state detection and deregistration */
  id: string
  /** Display label shown next to the icon when sidebar is expanded */
  label: string
  /** PrimeIcons class string, e.g. "pi pi-home" */
  icon: string
  /** Vue Router route name to navigate to on click */
  routeName: string
  /** Visual group this item belongs to */
  group: SidebarGroup
  /**
   * Sort order within the group – higher number = closer to top.
   * Maps directly to the `priority` field in repository.json.
   */
  priority: number
  /**
   * Optional badge count shown as a red dot/number on the icon.
   * Set to 0 or undefined to hide the badge.
   */
  badge?: number
  /** Tooltip override – defaults to `label` if omitted */
  tooltip?: string
}

/** Configuration for a group header rendered between nav sections */
export interface SidebarNavGroup {
  id: SidebarGroup
  label: string
  /** Items sorted descending by priority (computed, not stored) */
  items: SidebarNavItem[]
}

/** A navigation item for the settings sub-navigation panel */
export interface SettingsNavItem {
  /** Unique identifier */
  id: string
  /** Display label shown next to the icon when sidebar is expanded */
  label: string
  /** PrimeIcons class string, e.g. "pi pi-sliders-h" */
  icon: string
  /** Vue Router route name to navigate to on click */
  routeName: string
  /** Sort order within the settings nav – higher number = closer to top */
  priority: number
}

/** Sidebar collapse state stored in localStorage */
export interface SidebarState {
  isCollapsed: boolean
}
