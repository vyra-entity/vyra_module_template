/**
 * Global Plugin Slot type definitions for VYRA modules.
 *
 * Every module frontend imports from this file to type-check plugin slot
 * registrations, manifest entries, and the Global Plugin API.
 */

import { MODULE_SLOT_REGISTRY } from './plugin_slots_module'

// ---------------------------------------------------------------------------
// Slot category taxonomy
// ---------------------------------------------------------------------------

export type SlotCategory =
  | 'topbar'
  | 'sidebar'
  | 'statusbar'
  | 'side-dock-popup'
  | 'overlay'
  | 'popup'
  | 'background'
  | 'context-menu'
  | 'notification-provider'
  | 'data-visualizer'
  | 'search-provider'
  | 'empty-states'
  | 'route-injection'
  | 'component-decorator'
  | 'settings'

export type UserRole = 'viewer' | 'operator' | 'admin' | 'superadmin'

// ---------------------------------------------------------------------------
// Global Plugin API — props, events, functions
// ---------------------------------------------------------------------------

/** Read-only context provided to every plugin by the host. */
export interface PluginGlobalProps {
  /** The currently authenticated user, or null when unauthenticated. */
  currentUser: {
    username: string
    role: UserRole
  } | null
  /** Current colour theme exposed by the host shell. */
  theme: 'light' | 'dark'
  /** System language as a BCP-47 language tag (e.g. 'en', 'de'). */
  systemLanguage: string
  /** Name of the currently active route / view. */
  activeContext: string
}

/** Options for the `notify` event. */
export interface NotifyOptions {
  message: string
  severity: 'info' | 'success' | 'warn' | 'error'
  /** Toast duration in milliseconds. 0 = sticky. Default: 3000. */
  duration?: number
}

/** Host-emitted side-effects that plugins can trigger. */
export interface PluginGlobalEvents {
  /** Show a toast notification in the host shell. */
  notify: (options: NotifyOptions) => void
  /** Navigate to an internal route path or an external URL. */
  navigationRequest: (target: string) => void
  /** Report a critical (unrecoverable) plugin error to the host. */
  criticalError: (error: Error) => void
}

/** Extra fetch options accepted by `apiFetch`. */
export interface FetchOptions extends RequestInit {
  /** When true the URL is treated as relative to the module's API base. */
  useModuleBase?: boolean
}

/** Helper functions provided by the host for use inside plugin components. */
export interface PluginGlobalFunctions {
  /**
   * Authenticated API fetch helper.
   * Pre-configured with `credentials: 'include'` and JSON headers.
   * Preferred method for calling back-end APIs from a plugin.
   */
  apiFetch: (url: string, options?: FetchOptions) => Promise<Response>
  /** Read a persisted plugin setting by key. */
  getSetting: (key: string) => Promise<unknown>
  /** Write a persisted plugin setting. */
  setSetting: (key: string, value: unknown) => Promise<void>
  /** Open a modal dialog backed by a named Vue component. */
  openModal: (componentName: string, props?: Record<string, unknown>) => void
  /** Emit a named telemetry / analytics event. */
  trackEvent: (eventName: string, payload?: Record<string, unknown>) => void
  /**
   * Register a pocket in the Side-Dock-Popup panel.
   * The `component` argument must be a resolved Vue component object
   * (e.g. imported SFC or `defineComponent(...)`).
   * The pocket appears immediately in the SDP trigger list.
   */
  registerSdpPocket: (registration: SdpPocketRegistration, component: unknown) => void
  /** Remove a previously registered SDP pocket by its id. */
  unregisterSdpPocket: (id: string) => void
}

/**
 * The full Global Plugin API object injected into every plugin component
 * as the `pluginApi` prop by the host's PluginSlot.
 */
export interface PluginGlobalApi {
  props: PluginGlobalProps
  events: PluginGlobalEvents
  functions: PluginGlobalFunctions
}

// ---------------------------------------------------------------------------
// Display Area API  (statusbar / topbar display slots)
// ---------------------------------------------------------------------------

/**
 * Injected as `displayApi` into plugins that render inside a display area.
 *
 * `blink(color)` — the current message **stays**; only the background of the
 * display area flashes twice briefly in the given hex colour as a visual hint.
 */
export interface DisplayAreaApi {
  /** Show a text message; stays until replaced or cleared. */
  show: (message: string) => void
  /** Clear the currently displayed message. */
  clear: () => void
  /**
   * Flash the display area background twice in the given hex colour.
   * The message is not removed or changed — only the background flashes.
   * Example: `displayApi.blink('#ff9900')`
   */
  blink: (color: string) => void
}

// ---------------------------------------------------------------------------
// Side-Dock-Popup API
// ---------------------------------------------------------------------------

/**
 * Registration data passed to `pluginApi.functions.registerSdpPocket()`.
 * The host mounts the Vue component once the pocket is opened by the user.
 */
export interface SdpPocketRegistration {
  /** Unique pocket identifier, e.g. `'my-plugin-status'`. */
  id: string
  /** Label shown in the trigger row. */
  title: string
  /** PrimeIcons class or asset URL, e.g. `'pi pi-chart-bar'`. */
  icon: string
  /** Which panel section the pocket appears in. */
  section: 'header' | 'content' | 'footer'
  /** Lower number = higher up in the list. Default: 50. */
  priority?: number
  /**
   * Route-name / context strings for which the pocket is shown.
   * Empty array = always visible.
   */
  contextScope?: string[]
  /** Whether the user may pin the pocket open. Default: true. */
  isPinnable?: boolean
}

/** Injected as `sdpApi` into plugins registered in side-dock-popup slots. */
export interface SdpPocketApi {
  open: () => void
  close: () => void
  pin: () => void
  unpin: () => void
  isPinned: () => boolean
  isOpen: () => boolean
}

// ---------------------------------------------------------------------------
// Search result (used by search-provider plugins)
// ---------------------------------------------------------------------------

export interface SearchResult {
  id: string
  title: string
  description?: string
  icon?: string
  /** Route path or callback to execute when the result is selected. */
  action: string | (() => void)
}

// ---------------------------------------------------------------------------
// Slot definition registry
// ---------------------------------------------------------------------------

export interface SlotDefinition {
  /** Slot identifier. Matches the `scope` entries in a plugin manifest. */
  id: string
  category: SlotCategory
  description: string
  /** Human-readable areas / host shell zones where this slot is rendered. */
  areas: string[]
  /** Maximum simultaneous active plugins. Undefined = unlimited. */
  maxPlugins?: number
  /** Additional prop names injected into plugins in this slot. */
  extraProps?: Record<string, string>
}

/** Registry of every well-known VYRA plugin slot. */
export const SLOT_REGISTRY: Readonly<Record<string, SlotDefinition>> = {
  // ── Topbar ────────────────────────────────────────────────────────────────
  'topbar.menu': {
    id: 'topbar.menu',
    category: 'topbar',
    description: 'Icon buttons rendered inside the topbar to the left of the alarm bell.',
    areas: ['Top navigation bar'],
    extraProps: { isCollapsed: 'boolean — true in compact / mobile mode' },
  },
  'topbar.display': {
    id: 'topbar.display',
    category: 'topbar',
    description: 'Single display area in the topbar centre for text messages.',
    areas: ['Top navigation bar — centre'],
    maxPlugins: 1,
    extraProps: { displayApi: 'DisplayAreaApi — show / clear / blink helpers' },
  },

  // ── Sidebar ───────────────────────────────────────────────────────────────
  'sidebar.nav': {
    id: 'sidebar.nav',
    category: 'sidebar',
    description: 'Navigation items injected into the main sidebar navigation section.',
    areas: ['Left sidebar — main nav'],
    extraProps: { isCollapsed: 'boolean — true in icon-only collapsed state' },
  },
  'sidebar.bottom': {
    id: 'sidebar.bottom',
    category: 'sidebar',
    description: 'Items injected into the sidebar bottom zone.',
    areas: ['Left sidebar — bottom zone'],
    extraProps: { isCollapsed: 'boolean' },
  },

  // ── Statusbar ─────────────────────────────────────────────────────────────
  'statusbar.infobar': {
    id: 'statusbar.infobar',
    category: 'statusbar',
    description: 'Left-aligned info area in the statusbar for short single-line contextual messages. Long text is truncated with ellipsis; full text shown as tooltip on hover.',
    areas: ['Bottom status bar — left side'],
  },
  'statusbar.actionbar': {
    id: 'statusbar.actionbar',
    category: 'statusbar',
    description: 'Action / status chips rendered in the bottom status bar.',
    areas: ['Bottom status bar'],
  },

  // ── Side-Dock-Popup ───────────────────────────────────────────────────────
  'side-dock-popup.header': {
    id: 'side-dock-popup.header',
    category: 'side-dock-popup',
    description: 'Pockets in the header section of the Side-Dock-Popup panel.',
    areas: ['Right side dock — header section'],
    maxPlugins: 5,
    extraProps: {
      sdpApi: 'SdpPocketApi',
      contextScope: 'string — active route / context filter',
    },
  },
  'side-dock-popup.content': {
    id: 'side-dock-popup.content',
    category: 'side-dock-popup',
    description: 'Pockets in the main content section of the Side-Dock-Popup panel.',
    areas: ['Right side dock — content section'],
    maxPlugins: 5,
    extraProps: { sdpApi: 'SdpPocketApi', contextScope: 'string' },
  },
  'side-dock-popup.footer': {
    id: 'side-dock-popup.footer',
    category: 'side-dock-popup',
    description: 'Pockets in the footer section of the Side-Dock-Popup panel.',
    areas: ['Right side dock — footer section'],
    maxPlugins: 5,
    extraProps: { sdpApi: 'SdpPocketApi', contextScope: 'string' },
  },

  // ── Invisible infrastructure ──────────────────────────────────────────────
  'background': {
    id: 'background',
    category: 'background',
    description: 'Invisible slot for background services (WebSocket bridges, timers, etc.).',
    areas: ['App root (invisible)'],
  },
  'overlay': {
    id: 'overlay',
    category: 'overlay',
    description: 'Full-screen overlay layer rendered above all content.',
    areas: ['App root — overlay layer'],
  },
  'popup': {
    id: 'popup',
    category: 'popup',
    description: 'Popup / modal provider layer — plugins can inject custom dialogs.',
    areas: ['App root — popup layer'],
  },
  'context-menu': {
    id: 'context-menu',
    category: 'context-menu',
    description: 'Context menu items aggregated by ContextMenuProvider.',
    areas: ['Context menu (right-click)'],
  },
  'notification-provider': {
    id: 'notification-provider',
    category: 'notification-provider',
    description: 'Custom notification providers (push, WebSocket alerts, etc.).',
    areas: ['App root (invisible)'],
  },

  // ── Data / Search / Route ─────────────────────────────────────────────────
  'data-visualizer': {
    id: 'data-visualizer',
    category: 'data-visualizer',
    description: 'Data visualiser widgets mounted in the content area of a view.',
    areas: ['Route-specific content area'],
  },
  'search-provider': {
    id: 'search-provider',
    category: 'search-provider',
    description: 'Provides search results to the global CMD+K search dialog.',
    areas: ['Search dialog (CMD+K)'],
    extraProps: {
      query: 'string — current search query',
      onResults: '(results: SearchResult[]) => void — submit results callback',
    },
  },
  'empty-states': {
    id: 'empty-states',
    category: 'empty-states',
    description: 'Replaces default empty-state illustrations in list / table views.',
    areas: ['Any list / table view — empty state placeholder'],
  },
  'route-injection': {
    id: 'route-injection',
    category: 'route-injection',
    description: 'Injects a new page reachable at /p/:pluginSlug.',
    areas: ['Router — /p/:pluginSlug'],
  },
  'component-decorator': {
    id: 'component-decorator',
    category: 'component-decorator',
    description: 'Wraps / decorates existing host components with additional UI.',
    areas: ['Any host component (via v-plugin-decorator directive)'],
  },

  // ── Settings ──────────────────────────────────────────────────────────────
  'settings': {
    id: 'settings',
    category: 'settings',
    description: 'Adds a settings card / section to the module Settings view.',
    areas: ['Settings page'],
  },

  // ── Module-specific slots ─────────────────────────────────────────────────
  // Exclusive to this module. Add them in ./plugin_slots_module.ts.
  ...MODULE_SLOT_REGISTRY,
} as const
