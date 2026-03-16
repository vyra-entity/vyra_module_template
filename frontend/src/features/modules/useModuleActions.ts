/**
 * useModuleActions – Context-aware action buttons for module instances.
 *
 * Returns a list of ActionItem objects sorted by ascending priority.
 * The caller should display the first 3 items as direct buttons and
 * pack the remainder into a dropdown (hiding the dropdown when empty).
 *
 * Priority index → visual position:
 *   0 = first direct button (Details is always 0)
 *   1 = second direct button
 *   2 = third direct button
 *   3+ = overflow dropdown items
 *
 * There are never gaps in priority; items are filled bottom-up.
 */

import type { ModuleInstance } from '../../types/common'

export type ActionSeverity = 'primary' | 'secondary' | 'success' | 'warn' | 'danger' | 'info' | 'contrast'
export type ActionVariant = 'outlined' | 'tonal' | 'text' | undefined

export interface ActionItem {
  /** Unique action key */
  key: string
  /** Display label */
  label: string
  /** PrimeIcons class, e.g. 'pi pi-play' */
  icon: string
  /** Visual severity (maps to PrimeVue Button severity) */
  severity: ActionSeverity
  /** Button variant */
  variant?: ActionVariant
  /** Sort priority – lower = earlier; items are compacted so there are no gaps */
  priority: number
  /** Whether the action should show a confirmation dialog before executing */
  requiresConfirm?: boolean
  /** Label shown in confirmation dialog */
  confirmMessage?: string
  /** Whether this action requires a lifecycle transition that might be in progress */
  isLifecycleAction?: boolean
  /** External URL to open (for Web Interface button) */
  href?: string
}

/**
 * Lifecycle state string constants (must match LifecycleState enum values).
 */
export const LifecycleState = {
  OFFLINE: 'offline',
  INITIALIZING: 'initializing',
  ACTIVE: 'active',
  RECOVERING: 'recovering',
  SUSPENDED: 'suspended',
  SHUTTING_DOWN: 'shutting_down',
} as const

export type LifecycleStateValue = (typeof LifecycleState)[keyof typeof LifecycleState]

/**
 * Severity mapping for lifecycle state badges.
 */
export const lifecycleSeverity: Record<string, ActionSeverity> = {
  [LifecycleState.ACTIVE]: 'success',
  [LifecycleState.OFFLINE]: 'secondary',
  [LifecycleState.SHUTTING_DOWN]: 'warn',
  [LifecycleState.RECOVERING]: 'warn',
  [LifecycleState.SUSPENDED]: 'info',
  [LifecycleState.INITIALIZING]: 'info',
}

/**
 * Build the ordered list of available actions for a given lifecycle state.
 *
 * @param lifecycleState  Current lifecycle state string (lowercase).
 * @param instance        The module instance record (for label/flags).
 * @param liveState       Optional additional live state data from the feed store.
 */
export function getActionsForState(
  lifecycleState: string | undefined | null,
  instance: ModuleInstance,
  liveState?: Record<string, any>
): ActionItem[] {
  const state = (lifecycleState ?? 'unknown').toLowerCase()
  const frontendUrl = instance.frontend_url ?? `/${instance.module_name}/`

  const actions: ActionItem[] = []

  // ── Priority 0: Details (always shown) ───────────────────────────────────
  actions.push({
    key: 'details',
    label: 'Details',
    icon: 'pi pi-info-circle',
    severity: 'secondary',
    variant: 'outlined',
    priority: 0,
  })

  // ── State-specific actions ────────────────────────────────────────────────

  switch (state) {
    case LifecycleState.ACTIVE:
      if (instance.permissions?.suspendable !== false) {
        actions.push({
          key: 'suspend',
          label: 'Suspend',
          icon: 'pi pi-pause',
          severity: 'info',
          priority: 1,
          isLifecycleAction: true,
          requiresConfirm: false,
        })
      }
      actions.push(
        {
          key: 'restart',
          label: 'Restart',
          icon: 'pi pi-refresh',
          severity: 'warn',
          variant: 'outlined',
          priority: instance.permissions?.suspendable !== false ? 2 : 1,
          requiresConfirm: true,
          confirmMessage: 'Restart this module instance?',
        },
        {
          key: 'stop',
          label: 'Stop',
          icon: 'pi pi-stop-circle',
          severity: 'warn',
          variant: 'tonal',
          priority: instance.permissions?.suspendable !== false ? 3 : 2,
          requiresConfirm: true,
          confirmMessage: 'Stop this module instance?',
        },
        {
          key: 'delete',
          label: 'Delete',
          icon: 'pi pi-trash',
          severity: 'danger',
          variant: 'outlined',
          priority: instance.permissions?.suspendable !== false ? 4 : 3,
          requiresConfirm: true,
          confirmMessage: 'Permanently delete this module instance?',
        }
      )
      break

    case LifecycleState.SUSPENDED:
      actions.push(
        {
          key: 'resume',
          label: 'Resume',
          icon: 'pi pi-play',
          severity: 'success',
          priority: 1,
          isLifecycleAction: true,
        },
        {
          key: 'restart',
          label: 'Restart',
          icon: 'pi pi-refresh',
          severity: 'warn',
          variant: 'outlined',
          priority: 2,
          requiresConfirm: true,
          confirmMessage: 'Restart this module instance?',
        },
        {
          key: 'stop',
          label: 'Stop',
          icon: 'pi pi-stop-circle',
          severity: 'warn',
          variant: 'tonal',
          priority: 3,
          requiresConfirm: true,
          confirmMessage: 'Stop this module instance?',
        },
        {
          key: 'delete',
          label: 'Delete',
          icon: 'pi pi-trash',
          severity: 'danger',
          variant: 'outlined',
          priority: 4,
          requiresConfirm: true,
          confirmMessage: 'Permanently delete this module instance?',
        }
      )
      break

    case LifecycleState.OFFLINE:
    case 'stopped':
    case 'unknown':
      actions.push(
        {
          key: 'start',
          label: 'Start',
          icon: 'pi pi-play',
          severity: 'success',
          priority: 1,
        },
        {
          key: 'restart',
          label: 'Restart',
          icon: 'pi pi-refresh',
          severity: 'secondary',
          variant: 'outlined',
          priority: 2,
          requiresConfirm: true,
          confirmMessage: 'Restart this module instance?',
        },
        {
          key: 'delete',
          label: 'Delete',
          icon: 'pi pi-trash',
          severity: 'danger',
          variant: 'outlined',
          priority: 3,
          requiresConfirm: true,
          confirmMessage: 'Permanently delete this module instance?',
        }
      )
      break

    case LifecycleState.RECOVERING:
      actions.push(
        {
          key: 'restart',
          label: 'Restart',
          icon: 'pi pi-refresh',
          severity: 'warn',
          priority: 1,
          requiresConfirm: true,
          confirmMessage: 'Force restart while module is recovering?',
        },
        {
          key: 'stop',
          label: 'Stop',
          icon: 'pi pi-stop-circle',
          severity: 'warn',
          variant: 'outlined',
          priority: 2,
          requiresConfirm: true,
          confirmMessage: 'Stop this module instance?',
        },
        {
          key: 'delete',
          label: 'Delete',
          icon: 'pi pi-trash',
          severity: 'danger',
          variant: 'outlined',
          priority: 3,
          requiresConfirm: true,
          confirmMessage: 'Permanently delete this module instance?',
        }
      )
      break

    case LifecycleState.INITIALIZING:
      actions.push(
        {
          key: 'stop',
          label: 'Stop',
          icon: 'pi pi-stop-circle',
          severity: 'warn',
          variant: 'outlined',
          priority: 1,
          requiresConfirm: true,
          confirmMessage: 'Stop this module while it is initializing?',
        },
        {
          key: 'delete',
          label: 'Delete',
          icon: 'pi pi-trash',
          severity: 'danger',
          variant: 'outlined',
          priority: 2,
          requiresConfirm: true,
          confirmMessage: 'Permanently delete this module instance?',
        }
      )
      break

    case LifecycleState.SHUTTING_DOWN:
      actions.push({
        key: 'delete',
        label: 'Delete',
        icon: 'pi pi-trash',
        severity: 'danger',
        variant: 'outlined',
        priority: 1,
        requiresConfirm: true,
        confirmMessage: 'Force delete while module is shutting down?',
      })
      break

    default:
      // Fallback for truly unknown states
      actions.push({
        key: 'delete',
        label: 'Delete',
        icon: 'pi pi-trash',
        severity: 'danger',
        variant: 'outlined',
        priority: 1,
        requiresConfirm: true,
        confirmMessage: 'Permanently delete this module instance?',
      })
      break
  }

  // Always show Web Interface button when a frontend URL is available
  if (frontendUrl) {
    actions.push({
      key: 'open_ui',
      label: 'Web Interface',
      icon: 'pi pi-external-link',
      severity: 'primary',
      variant: 'text',
      priority: 50,
      href: frontendUrl,
    })
  }

  // Guard: hide delete when instance is explicitly not removable
  if (instance.permissions?.removable === false) {
    const idx = actions.findIndex(a => a.key === 'delete')
    if (idx !== -1) actions.splice(idx, 1)
  }

  // Add update action whenever a newer version is available
  if (instance.has_updates) {
    actions.push({
      key: 'update',
      label: 'Update',
      icon: 'pi pi-arrow-circle-up',
      severity: 'primary',
      variant: 'outlined',
      priority: actions.length,
      requiresConfirm: true,
      confirmMessage: 'Dieses Modul auf die neueste Version aktualisieren?',
    })
  }

  // Sort by priority and compact (no gaps)
  actions.sort((a, b) => a.priority - b.priority)
  actions.forEach((a, i) => { a.priority = i })

  return actions
}

/**
 * Split actions into direct buttons (first 3) and overflow items (rest).
 */
export function splitActions(actions: ActionItem[]): {
  directButtons: ActionItem[]
  overflowItems: ActionItem[]
} {
  return {
    directButtons: actions.slice(0, 3),
    overflowItems: actions.slice(3),
  }
}
