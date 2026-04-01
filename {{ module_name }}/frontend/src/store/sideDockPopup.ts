/**
 * Pinia store for the Side-Dock-Popup (SDP) panel.
 *
 * The SDP is a right-side fly-in panel with three sections: header, content,
 * footer. Each section holds up to SDP_MAX_POCKETS_PER_SECTION pockets;
 * additional pockets are listed in an overflow "+N more" element.
 *
 * Pockets are registered programmatically by plugin components that target
 * a `side-dock-popup.*` slot.
 */

import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import type { Component } from 'vue'
import type { SdpPocketApi } from '../types/plugin_slots'

export type SdpSection = 'header' | 'content' | 'footer'

export interface SdpPocket {
  /** Unique pocket identifier (e.g. `${pluginId}-${slotId}`). */
  id: string
  title: string
  /** PrimeIcons class name or asset URL for the pocket trigger icon. */
  icon: string
  section: SdpSection
  priority: number
  /**
   * Route name / context strings for which this pocket is visible.
   * Empty array = always visible.
   */
  contextScope: string[]
  pluginId: string
  /** The resolved plugin component instance. */
  component: Component
  isPinnable: boolean
  isOpen: boolean
  isPinned: boolean
}

/** Maximum visible pockets per section before overflow is shown. */
export const SDP_MAX_POCKETS_PER_SECTION = 5

export const useSideDockPopupStore = defineStore('sideDockPopup', () => {
  const pockets = ref<SdpPocket[]>([])
  const activePocketId = ref<string | null>(null)
  const isPanelOpen = ref(false)

  const sortedPockets = computed(() =>
    [...pockets.value].sort((a, b) => a.priority - b.priority),
  )

  /**
   * Pockets visible in a section for the given activeContext.
   * Applies contextScope filtering.
   */
  function pocketsInSection(section: SdpSection, activeContext: string): SdpPocket[] {
    return sortedPockets.value.filter(
      (p) =>
        p.section === section &&
        (p.contextScope.length === 0 ||
          p.contextScope.some((s) => _matchScope(s, activeContext))),
    )
  }

  /**
   * Number of pockets exceeding SDP_MAX_POCKETS_PER_SECTION for a section.
   * Used to render the "+N more" overflow indicator.
   */
  function overflowCount(section: SdpSection, activeContext: string): number {
    return Math.max(
      0,
      pocketsInSection(section, activeContext).length - SDP_MAX_POCKETS_PER_SECTION,
    )
  }

  /** Register a new pocket. Silently ignored if a pocket with the same id exists. */
  function registerPocket(pocket: Omit<SdpPocket, 'isOpen' | 'isPinned'>): void {
    if (!pockets.value.find((p) => p.id === pocket.id)) {
      pockets.value.push({ ...pocket, isOpen: false, isPinned: false })
    }
  }

  /** Remove a pocket. If it was active, panel focus is cleared. */
  function unregisterPocket(id: string): void {
    pockets.value = pockets.value.filter((p) => p.id !== id)
    if (activePocketId.value === id) activePocketId.value = null
  }

  /** Open (expand) a pocket. Also ensures the SDP panel is visible. */
  function openPocket(id: string): void {
    const pocket = pockets.value.find((p) => p.id === id)
    if (pocket) {
      pocket.isOpen = true
      activePocketId.value = id
      isPanelOpen.value = true
    }
  }

  /**
   * Close a pocket. Pinned pockets are ignored — call unpinPocket first.
   */
  function closePocket(id: string): void {
    const pocket = pockets.value.find((p) => p.id === id)
    if (pocket && !pocket.isPinned) {
      pocket.isOpen = false
      if (activePocketId.value === id) activePocketId.value = null
    }
  }

  /** Pin a pocket so it stays open when the panel loses focus. */
  function pinPocket(id: string): void {
    const pocket = pockets.value.find((p) => p.id === id)
    if (pocket) {
      pocket.isPinned = true
      pocket.isOpen = true
    }
  }

  /** Unpin a pocket (it remains open until explicitly closed). */
  function unpinPocket(id: string): void {
    const pocket = pockets.value.find((p) => p.id === id)
    if (pocket) pocket.isPinned = false
  }

  /** Close the SDP panel. Un-pinned pockets are collapsed. */
  function closePanel(): void {
    isPanelOpen.value = false
    pockets.value.forEach((p) => {
      if (!p.isPinned) p.isOpen = false
    })
    activePocketId.value = null
  }

  /**
   * Returns a SdpPocketApi object bound to a pocket id.
   * Passed as the `sdpApi` prop into plugins in side-dock-popup slots.
   */
  function getPocketApi(id: string): SdpPocketApi {
    return {
      open: () => openPocket(id),
      close: () => closePocket(id),
      pin: () => pinPocket(id),
      unpin: () => unpinPocket(id),
      isPinned: () => pockets.value.find((p) => p.id === id)?.isPinned ?? false,
      isOpen: () => pockets.value.find((p) => p.id === id)?.isOpen ?? false,
    }
  }

  return {
    pockets,
    activePocketId,
    isPanelOpen,
    sortedPockets,
    pocketsInSection,
    overflowCount,
    registerPocket,
    unregisterPocket,
    openPocket,
    closePocket,
    pinPocket,
    unpinPocket,
    closePanel,
    getPocketApi,
  }
})

// ---------------------------------------------------------------------------
// Scope matching helper
// ---------------------------------------------------------------------------

/**
 * Match a scope pattern against an active context string.
 *
 * - `*`  matches any single dot-separated segment
 * - `**` matches the entire remaining string (full wildcard)
 * - Exact string match otherwise
 *
 * @example
 *   _matchScope('home', 'home')            // true
 *   _matchScope('*.modules', 'v2.modules') // true
 *   _matchScope('**', 'any/context')       // true
 */
function _matchScope(pattern: string, context: string): boolean {
  if (pattern === '**') return true
  if (pattern === context) return true
  const regexStr = pattern
    .split('.')
    .map((seg) =>
      seg === '*' ? '[^.]+' : seg === '**' ? '.+' : _escapeRegex(seg),
    )
    .join('\\.')
  return new RegExp(`^${regexStr}$`).test(context)
}

function _escapeRegex(str: string): string {
  return str.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')
}
