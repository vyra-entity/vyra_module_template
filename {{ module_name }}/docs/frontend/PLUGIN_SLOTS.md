# VYRA Plugin Slot Architecture — Frontend Reference

This document describes the complete VYRA plugin slot system as implemented in all VYRA module frontends. It covers every slot ID, the global Plugin API, the manifest schema, the Side-Dock-Popup, and implementation guidelines.

---

## Table of Contents

1. [Overview](#1-overview)
2. [Manifest Schema](#2-manifest-schema)
3. [Global Plugin API](#3-global-plugin-api)
   - [Global Props (System → Plugin)](#31-global-props-system--plugin)
   - [Global Events (Plugin → System)](#32-global-events-plugin--system)
   - [Global Functions](#33-global-functions)
4. [Slot Registry](#4-slot-registry)
   - [Topbar Slots](#41-topbar-slots)
   - [Sidebar Slots](#42-sidebar-slots)
   - [Statusbar Slots](#43-statusbar-slots)
   - [Side-Dock-Popup Slots](#44-side-dock-popup-slots)
   - [Overlay & Popup Slots](#45-overlay--popup-slots)
   - [Background Slot](#46-background-slot)
   - [Context-Menu Slot](#47-context-menu-slot)
   - [Search-Provider Slot](#48-search-provider-slot)
   - [Notification-Provider Slot](#49-notification-provider-slot)
   - [Data-Visualizer Slot](#410-data-visualizer-slot)
   - [Empty-States Slot](#411-empty-states-slot)
   - [Route-Injection Slot](#412-route-injection-slot)
   - [Component-Decorator Slot](#413-component-decorator-slot)
   - [Settings Slot](#414-settings-slot)
5. [Side-Dock-Popup Behavior](#5-side-dock-popup-behavior)
6. [Wildcard Scope Matching](#6-wildcard-scope-matching)
7. [Building a Plugin](#7-building-a-plugin)
8. [Frontend File Reference](#8-frontend-file-reference)

---

## 1. Overview

The VYRA plugin slot system allows external plugins (loaded as ES modules from the NFS pool) to inject UI components into precisely defined areas of any VYRA module frontend. All module frontends share the same slot structure meaning a plugin written once can target any module.

**Architecture layers:**

```
manifest.yaml (slot declarations)
       │
       ▼
v2_modulemanager backend (plugin DB + resolution)
       │  /plugin/resolve_plugins
       ▼
Frontend plugin store (usePluginStore)
       │  defineAsyncComponent + dynamic import
       ▼
<PluginSlot slot-id="…" />
       │  injects usePluginApi
       ▼
Plugin Component (Vue 3 SFC from NFS pool)
```

The host passes a **Global Plugin API** to every plugin via Vue `provide`/`inject`. This gives each plugin access to the current user, the theme, navigation helpers, authenticated fetch, and persistent settings — without any direct coupling to host internals.

---

## 2. Manifest Schema

Each plugin describes its slot registrations in `manifest.yaml` under `entry_points.frontend.slots`. The `scope` field is a **list** of slot target strings that may contain `*` wildcards.

```yaml
entry_points:
  frontend:
    type: module
    file: plugins/my-plugin/1.0.0/ui/index.js
    css:
      - plugins/my-plugin/1.0.0/ui/style.css
    slots:
      - scope:                          # list of target slot IDs (replaces old single `id:`)
          - "topbar.menu"               # absolute: only in topbar.menu
          - "*.statusbar.actionbar"     # wildcard: statusbar.actionbar of any module
          - "v2_dashboard.home-widget"  # module-qualified slot
        component: MyComponent          # Named export from ui/index.js
        title: My Plugin                # Human-readable display name
        priority: 50                    # Higher = rendered first (0–100)
        minUserRole: operator           # Minimum role required (default: operator)
        searchKeywords:                 # For global CMD+K search indexing
          - my-plugin
          - example
        icon: assets/icon.svg           # Relative path from plugin root (optional)
```

> **Backwards compatibility**: The old `id: "slot-name"` (single string) is still accepted and internally converted to `scope: ["slot-name"]`.

### Wildcard matching rules

| Pattern | Matches |
|--------|---------|
| `topbar.menu` | Only `topbar.menu` |
| `*.topbar.menu` | `topbar.menu` in any module context |
| `v2_dashboard.*` | All slots of `v2_dashboard` |
| `*` | Every single-segment slot in any module |

The `*` wildcard matches exactly **one** path segment.

### Slot-specific extra attributes

Each slot type supports additional optional attributes in the manifest entry (see [Slot Registry](#4-slot-registry) for per-slot details).

---

## 3. Global Plugin API

Every plugin component receives the Global Plugin API via Vue `inject('vyra-plugin-api')`. The host (`App.vue`) calls `provide('vyra-plugin-api', api)` on mount, and `PluginSlot.vue` forwards the API as props to each rendered plugin.

TypeScript interface (available as `usePluginApi()` inside the host, or via inject in plugins):

```typescript
interface PluginGlobalApi {
  props: PluginGlobalProps
  events: PluginGlobalEvents
  functions: PluginGlobalFunctions
}
```

### 3.1 Global Props (System → Plugin)

Data the host passes to every plugin:

| Prop | Type | Description |
|------|------|-------------|
| `currentUser` | `{ username: string; roles: string[]; permissions: string[] }` | Authenticated user |
| `theme` | `'dark' \| 'light' \| 'high-contrast'` | Current UI theme |
| `systemLanguage` | `string` | ISO language code, e.g. `"de-DE"` |
| `activeContext` | `string` | Cleaned current route, e.g. `"modules.details"` |

`activeContext` maps the browser path to a clean dot-notation string:
- `/v2_modulemanager/modules/details?id=5` → `"modules.details"`
- `/v2_dashboard/home` → `"home"`

### 3.2 Global Events (Plugin → System)

Callbacks a plugin calls to communicate with the host:

| Event | Signature | Effect |
|-------|-----------|--------|
| `notify` | `(payload: { type: 'info'\|'success'\|'warn'\|'error'; message: string }) => void` | Triggers a global PrimeVue Toast |
| `navigationRequest` | `(payload: { target: string }) => void` | Navigates to the given path (validated) |
| `criticalError` | `(payload: { error: Error \| string }) => void` | Activates the dashboard error boundary |

Example usage in a plugin:

```typescript
const api = inject('vyra-plugin-api') as PluginGlobalApi
api.events.notify({ type: 'success', message: 'Export complete!' })
api.events.navigationRequest({ target: '/v2_modulemanager/modules' })
```

### 3.3 Global Functions

Tools the host provides for plugins:

| Function | Signature | Description |
|----------|-----------|-------------|
| `apiFetch` | `(endpoint: string, options?: RequestInit) => Promise<any>` | Authenticated HTTP wrapper (cookies auto-included) |
| `getSetting` | `(pluginKey: string, settingName: string) => Promise<any>` | Reads persistent plugin config from the backend |
| `setSetting` | `(pluginKey: string, settingName: string, value: any) => Promise<void>` | Saves persistent plugin config |
| `openModal` | `(componentId: string, props?: Record<string, unknown>) => void` | Opens a dialog via the overlay slot |
| `trackEvent` | `(eventName: string, data?: Record<string, unknown>) => void` | Sends telemetry/analytics to the host |

`apiFetch` respects the module's base URL and automatically includes session cookies. Relative endpoints are resolved against the current module's API base:

```typescript
// In a plugin:
const data = await api.functions.apiFetch('/modules/instances')
```

Settings are stored per plugin per user in the backend:

```typescript
await api.functions.setSetting('my-plugin', 'showAdvanced', true)
const val = await api.functions.getSetting('my-plugin', 'showAdvanced')
```

---

## 4. Slot Registry

The complete list of all defined slot IDs. Each slot is defined in `src/types/plugin_slots.ts`.

### 4.1 Topbar Slots

The topbar is the slim header bar at the top of the screen (`vyra-topbar`).

---

#### `topbar.menu`

Adds an entry to the main navigation menu in the topbar.

| Attribute | Type | Description |
|-----------|------|-------------|
| `icon` | `string` | PrimeIcons class (e.g. `"pi pi-star"`) |
| `label` | `string` | Display label shown next to icon |

| Event | Signature | Description |
|-------|-----------|-------------|
| `setBadgeCount` | `(count: number) => void` | Sets a badge number on the menu item |

On click the host performs a route change to the address defined in the plugin's `route-injection` slot or to the `to` attribute.

---

#### `topbar.display`

A central single-line info area in the topbar between the left and right sections.

- Renders one message at a time with ellipsis on overflow.
- The message **persists** until replaced by a new `display()` call.
- `blink()` causes the display area **background** to flash twice in the given color as a visual hint; the current message remains visible.

| Event | Signature | Description |
|-------|-----------|-------------|
| `display` | `(msg: string) => void` | Shows a message in the display area |
| `blink` | `(color: string) => void` | Flashes the display background twice (hex or CSS color); message stays visible |

---

### 4.2 Sidebar Slots

The sidebar is the collapsible navigation rail on the left (`VyraSidebar.vue`).

---

#### `sidebar.brand`

Replaces or augments the branding area at the top of the sidebar.

| Attribute | Type | Description |
|-----------|------|-------------|
| `logoUrl` | `string` | URL to the logo image |
| `shortName` | `string` | Abbreviated name shown in collapsed mode |

---

#### `sidebar.nav-group`

Adds a category header section to the sidebar navigation.

| Attribute | Type | Description |
|-----------|------|-------------|
| `title` | `string` | Group header label (uppercase) |
| `collapsible` | `boolean` | Whether the group can be collapsed |

---

#### `sidebar.nav-link`

Adds a navigation item to the sidebar. Performs a route change on click. The route address is validated before navigation.

| Attribute | Type | Description |
|-----------|------|-------------|
| `to` | `string` | Target route path |
| `icon` | `string` | PrimeIcons class |
| `label` | `string` | Display label |

---

### 4.3 Statusbar Slots

The statusbar is a new bar at the **bottom** of the screen (`VyraStatusbar.vue`).

---

#### `statusbar.actionbar`

Adds a quick-action button to the status bar.

| Attribute | Type | Description |
|-----------|------|-------------|
| `icon` | `string` | PrimeIcons class |
| `shortInfo` | `string` | Max 20 characters; truncated with ellipsis |

| Prop | Type | Description |
|------|------|-------------|
| `clickTrigger` | `'left' \| 'right' \| null` | Host sets this when user clicks left or right on the action. Plugin watches this prop to respond. |

The plugin watches `clickTrigger` and executes its action when it changes:

```typescript
watch(() => props.clickTrigger, (val) => {
  if (val === 'left') doAction()
  if (val === 'right') openContextMenu()
})
```

---

### 4.4 Side-Dock-Popup Slots

The Side-Dock-Popup (SDP) is a fly-in pocket on the **right side** of the screen (`SideDockPopup.vue`). See [Section 5](#5-side-dock-popup-behavior) for full behavioral description.

All SDP slots share these attributes:

| Attribute | Type | Description |
|-----------|------|-------------|
| `title` | `string` | Pocket label |
| `icon` | `string` | PrimeIcons class |
| `isPinnable` | `boolean` | Whether the popup can be pinned open |
| `moduleId` | `string \| null` | Related module instance ID (optional) |
| `priority` | `number` | Position in pocket (higher = top) and popup z-order |

---

#### `sdp.header`

Pockets in the **header** section — always visible regardless of the current page.

Use for global tools that should always be reachable (e.g. a chat widget, a help overlay).

---

#### `sdp.content`

Pockets in the **content** section — only shown when the `contextScope` filter matches `activeContext`.

| Attribute | Type | Description |
|-----------|------|-------------|
| `contextScope` | `string[]` | List of context patterns (supports `*` wildcard). Pocket is visible only when `activeContext` matches at least one pattern. |

Examples:
```yaml
contextScope:
  - "modules.details"   # only on the module detail page
  - "modules.*"         # anywhere in the modules area
  - "*"                 # always visible (same as sdp.header)
```

---

#### `sdp.footer`

Pockets in the **footer** section — always visible, intended for critical quick actions.

Typically used for: Emergency stop, Home navigation, Error reset.

---

### 4.5 Overlay & Popup Slots

#### `overlay`

A fullscreen container rendered above all other content for modals.

| Prop | Type | Description |
|------|------|-------------|
| `dimIntensity` | `number` | Background dim level 0.0–1.0 |
| `isDismissible` | `boolean` | Click-outside closes the overlay |

---

#### `popup`

Tooltips, dropdowns, and floating panels.

| Prop | Type | Description |
|------|------|-------------|
| `trigger` | `string` | CSS selector of the trigger element |
| `offset` | `[number, number]` | `[x, y]` offset from trigger |

---

### 4.6 Background Slot

#### `background`

Invisible worker components for background processes. The component renders with `display: none`.

| Event | Signature | Description |
|-------|-----------|-------------|
| `@onTick` | `() => void` | Called periodically by the host (every ~1 second) |
| `@onSuccess` | `(data: unknown) => void` | Plugin emits this when a background task completes |

---

### 4.7 Context-Menu Slot

#### `context-menu`

Lets plugins inject actions into the right-click context menu on selected objects.

The plugin component receives:
- `selection` prop containing the currently selected object
- Returns a list of menu items via `provide('contextMenuItems', items)`

Example items:
```typescript
[
  { label: 'Send log to Plugin X', icon: 'pi pi-send', action: () => {} },
  { label: 'Share with…', icon: 'pi pi-share-alt', action: () => {} },
]
```

---

### 4.8 Search-Provider Slot

#### `search-provider`

Integrates into the global CMD+K / Ctrl+K search dialog (`SearchProvider.vue`) that appears centered in the topbar.

The plugin receives the current `query: string` prop and emits `results`:

```typescript
emit('results', [
  { label: 'Restart Module', description: 'module-xyz is running', icon: 'pi pi-refresh', action: () => {} },
])
```

Results from all registered search providers are aggregated and shown in the search dialog.

---

### 4.9 Notification-Provider Slot

#### `notification-provider`

Defines custom notification/toast types. A plugin registering this slot can:
- Define new severity levels beyond `info/success/warn/error`
- Override the visual appearance of existing toast types
- Add persistent notification banners

---

### 4.10 Data-Visualizer Slot

#### `data-visualizer`

A special slot within detail views. Renders an alternative visualization of data.

Example: A graph plugin renders log data as a timeline chart inside the module detail panel.

---

### 4.11 Empty-States Slot

#### `empty-states`

Fills placeholder views when a section has no data. The plugin receives:
- `context: string` — which empty state area is shown (e.g. `"modules-list"`, `"feeds"`)

---

### 4.12 Route-Injection Slot

#### `route-injection`

Registers a completely new full-screen page under `/p/{pluginSlug}`.

| Attribute | Type | Description |
|-----------|------|-------------|
| `slug` | `string` | URL segment used in `/p/{slug}` |
| `title` | `string` | Page title shown in the browser tab and topbar |

The route is dynamically registered on plugin load. The plugin's component is the full page content.

Navigate to a plugin page:
```typescript
router.push(`/p/my-plugin`)
// or via the topbar.menu slot which calls navigationRequest
```

---

### 4.13 Component-Decorator Slot

#### `component-decorator`

Injects small UI elements (e.g. info icons, badges) directly next to labels or buttons in the host UI.

The decorator plugin receives:
- `targetSelector: string` — CSS selector identifying the element to decorate
- `position: 'before' | 'after' | 'above' | 'below'`

Example: A help plugin injects a `?` icon next to the "Suspend" button. On hover, a tooltip explains: "Sets the Docker container to scale=0".

---

### 4.14 Settings Slot

#### `settings.page`

Adds an entry to the Settings page (`SettingsView.vue`).

| Attribute | Type | Description |
|-----------|------|-------------|
| `category` | `'System' \| 'User' \| 'Automation'` | Groups the settings entry under a heading |

| Function | Signature | Description |
|----------|-----------|-------------|
| `saveUser` | `(key: string, value: unknown) => void` | Persists a value to the current user's metadata in the DB |

---

## 5. Side-Dock-Popup Behavior

The **Side-Dock-Popup (SDP)** is a right-side fly-in panel that manages plugin pockets.

### Layout

```
┌──────────────────────────────┐
│  [sdp.header]                │  ← always visible header pockets
│  ────────────────────────── │
│  [sdp.content]               │  ← page-context filtered pockets
│  (filtered by activeContext) │
│  ────────────────────────── │
│  [sdp.footer]                │  ← always visible quick-action pockets
└──────────────────────────────┘
```

### Pocket states

1. **Collapsed**: The pocket appears as a small bookmark icon in the pocket rail on the right edge.
2. **Expanded (Popup)**: Clicking a pocket bookmark opens it as a floating popup panel.
3. **Pinned**: An open popup can be pinned — it remains open even when the user clicks elsewhere.
4. **Closing**: Closing a popup moves it back to the collapsed bookmark state; it is never destroyed.

### Overflow rule

Each section (header / content / footer) shows a maximum of **5 pockets**. If more than 5 plugins register for a section, an overflow indicator "**+N**" appears at the position of the 6th pocket. Clicking it opens a secondary popup listing the remaining pockets.

Pockets within a section are sorted by `priority` descending (higher priority = closer to top of pocket rail).

### Popup positioning

Multiple open popups are stacked. Higher `priority` popups appear above lower ones. Pinned popups are always on top of unpinned ones.

### `contextScope` filtering (sdp.content only)

The `contextScope` attribute on `sdp.content` entries is a list of patterns matched against `activeContext`. Patterns support `*` as a single-segment wildcard.

| activeContext | contextScope | Visible |
|---------------|-------------|---------|
| `modules.details` | `["modules.details"]` | ✅ |
| `modules.details` | `["modules.*"]` | ✅ |
| `home` | `["modules.*"]` | ❌ |
| `anything` | `["*"]` | ✅ |

---

## 6. Wildcard Scope Matching

Slots declared in `manifest.yaml` with wildcards are resolved by the backend at `resolve_plugins` time.

| Manifest scope | Resolved for module | Resulting slot_id |
|----------------|--------------------|--------------------|
| `topbar.menu` | `v2_dashboard` | `topbar.menu` |
| `*.statusbar.actionbar` | `v2_dashboard` | `statusbar.actionbar` |
| `v2_modulemanager.*` | `v2_modulemanager` | `*` (all slots) |

The resolving module is identified by the requesting module's `scope_target` parameter in the `/plugin/resolve_plugins` call.

---

## 7. Building a Plugin

### Minimal plugin structure

```
my-plugin/
└── 1.0.0/
    ├── manifest.yaml
    └── ui/
        ├── index.js       # compiled Vue 3 SFC — must export Vue components by name
        └── style.css
```

### Minimal manifest.yaml

```yaml
id: my-plugin
name: My Plugin
version: 1.0.0
scope:
  type: MODULE
  target: v2_dashboard
compatible_with:
  - v2_dashboard
permissions:
  network: false
  storage: none
entry_points:
  frontend:
    type: module
    file: plugins/my-plugin/1.0.0/ui/index.js
    slots:
      - scope:
          - "topbar.menu"
        component: MyPluginMenu
        title: My Plugin
        priority: 50
        minUserRole: operator
        searchKeywords:
          - my-plugin
```

### Receiving the Plugin API in a component

```vue
<script setup lang="ts">
import { inject } from 'vue'
import type { PluginGlobalApi } from './types' // copy from plugin_slots.ts

const api = inject<PluginGlobalApi>('vyra-plugin-api')

function doSomething() {
  api?.events.notify({ type: 'success', message: 'Done!' })
}

async function loadData() {
  const data = await api?.functions.apiFetch('/modules/instances')
  return data
}
</script>
```

### Emitting slot-specific events (`topbar.display`)

```typescript
// In a topbar.display plugin:
const api = inject<PluginGlobalApi>('vyra-plugin-api')

// Show a message
api.events.display('System OK — 3 modules running')

// Flash the display background amber as a hint (message stays)
api.events.blink('#FF9800')
```

### Registering a `search-provider`

```vue
<script setup lang="ts">
import { inject, watch } from 'vue'

const props = defineProps<{ query: string }>()
const emit = defineEmits<{ results: [items: SearchResult[]] }>()

watch(() => props.query, (q) => {
  const matches = myData.filter(item => item.label.includes(q))
  emit('results', matches.map(m => ({
    label: m.label,
    description: m.description,
    icon: 'pi pi-search',
    action: () => navigateTo(m.url),
  })))
})
</script>
<template><span style="display:none" /></template>
```

---

## 8. Frontend File Reference

| File | Purpose |
|------|---------|
| `src/types/plugin_slots.ts` | Complete typed slot registry (`SLOT_REGISTRY`, `SlotCategory`, `PluginGlobalApi`) |
| `src/composables/usePluginApi.ts` | Host-side Plugin API factory (props, events, functions) |
| `src/components/PluginSlot.vue` | Generic slot renderer — loads plugins, injects API, error-boundary |
| `src/features/plugins/PluginSlotHost.vue` | Alternative slot host |
| `src/store/plugins.ts` | Plugin manifest store (Pinia) |
| `src/store/sideDockPopup.ts` | SDP pocket registry and state |
| `src/components/layout/SideDockPopup.vue` | Right-side fly-in pocket component |
| `src/components/layout/VyraStatusbar.vue` | Bottom statusbar with actionbar slots |
| `src/components/layout/SearchProvider.vue` | CMD+K global search dialog |
| `src/components/layout/ContextMenuProvider.vue` | Right-click context menu aggregator |
| `src/directives/pluginDecorator.ts` | `v-plugin-decorator` directive for component decorators |
| `src/router/index.ts` | Contains `/p/:pluginSlug` catch-all for route-injection plugins |
