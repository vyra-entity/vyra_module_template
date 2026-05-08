/**
 * Module-specific plugin slot definitions for this VYRA module.
 *
 * Add slots here that are EXCLUSIVE to this module and must NOT be
 * added to the shared plugin_slots.ts registry used across all modules.
 *
 * This object is spread into SLOT_REGISTRY at the end of plugin_slots.ts.
 *
 * @example
 * ```ts
 * // To add a new module-exclusive slot, append an entry here:
 * 'my-module.custom-panel': {
 *   id: 'my-module.custom-panel',
 *   category: 'sidebar',
 *   description: 'A panel exclusive to this module.',
 *   areas: ['Left sidebar — custom zone'],
 *   extraProps: { myProp: 'string' },
 * },
 * ```
 */

import type { SlotDefinition } from './plugin_slots'

/**
 * Module-specific slot registry.
 * Currently empty — add module-exclusive slot definitions here.
 */
export const MODULE_SLOT_REGISTRY: Record<string, SlotDefinition> = {}
