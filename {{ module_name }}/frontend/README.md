# Frontend

Vue 3 + TypeScript frontend for the `{{ module_name }}` module. Built with [Vite](https://vitejs.dev/),
styled with [PrimeVue](https://primevue.org/) (Aura theme), and state-managed with
[Pinia](https://pinia.vuejs.org/).

In development mode (`VYRA_DEV_MODE=true`) Vite runs with a reverse proxy to the backend on port 8443.
In production the compiled output is served by Nginx.

## Development

```bash
cd frontend
npm install
npm run dev          # start Vite dev server on port 3000 (with backend proxy)
npm run build        # production build into dist/
npm run type-check   # run vue-tsc type checking
npm run lint         # ESLint + Prettier
```

The Vite dev server proxies all `/{{ module_name }}/api/` and `/{{ module_name }}/ws/` requests to
the backend container at `https://{{ module_name }}:8443`. The proxy is configured in `vite.config.ts`.

## Source Structure (`src/`)

```
src/
├── main.ts              ← Application entry: createApp + bootstrap + mount
├── App.vue              ← Root component: sidebar, topbar, router-view, error feed dialog
├── style.css            ← Legacy global styles (prefer assets/styles.css for new styles)
│
├── app/
│   ├── bootstrap.ts     ← Installs plugins (Pinia, PrimeVue, Router) on the Vue app instance
│   └── plugins.ts       ← Creates and configures Pinia store, PrimeVue theme, global services
│
├── api/
│   ├── auth.api.ts      ← Authentication REST calls (login, logout, verify, change-password)
│   └── http.ts          ← Axios instance with base URL and auth interceptors
│
├── assets/
│   ├── styles.css       ← Global CSS custom properties, layout utilities, component overrides
│   └── *.svg            ← Static image assets (logos, icons)
│
├── components/
│   ├── layout/          ← Application shell components (VyraSidebar, SidebarNavItem, SidebarNavGroup)
│   ├── ModuleFeedPanel.vue   ← Live event feed timeline (state / news / error events)
│   ├── PluginSlot.vue        ← Renders a plugin-injected UI component by slot name
│   ├── TaskProgressDialog.vue ← Modal showing long-running operation progress
│   └── UpdateModal.vue       ← Module update notification dialog
│
├── composables/
│   ├── useModuleFeed.ts       ← Wraps the module feed WebSocket store for easy consumption in components
│   ├── useOperationTracking.ts ← Polls operation state, shows toast notifications on completion
│   └── useSidebarNavigation.ts ← Helpers for registering dynamic nav items in the sidebar
│
├── features/
│   ├── auth/
│   │   └── LoginView.vue      ← Full-page login form, calls auth store
│   ├── home/
│   │   └── HomeView.vue       ← Default landing view after login
│   ├── monitoring/
│   │   ├── MonitoringView.vue ← Live state and health monitoring dashboard
│   │   └── monitoring.api.ts  ← REST calls specific to monitoring endpoints
│   ├── operations/
│   │   └── operation.api.ts   ← REST calls for operation tracking endpoints
│   ├── plugins/
│   │   ├── PluginSlotHost.vue ← Hosts plugin-injected Vue components in a named slot
│   │   └── plugin.api.ts      ← REST calls for plugin management endpoints
│   └── settings/
│       └── SettingsView.vue   ← User settings (password change, preferences)
│
├── router/
│   └── index.ts         ← Vue Router routes and navigation guard
│
├── store/
│   ├── index.ts         ← Pinia root (re-exports all stores)
│   ├── auth.ts          ← Authentication state: token, user info, login/logout actions
│   ├── moduleFeed.ts    ← WebSocket singleton: state/news/error feed with auto-reconnect
│   ├── sidebar.ts       ← Sidebar collapse state and dynamic nav item registry
│   ├── system.ts        ← Global system info (module name, version, VYRA deployment metadata)
│   └── plugins.ts       ← Installed plugin registry and slot-to-component mapping
│
└── types/
    ├── common.ts        ← Shared API response types, module instance types, task status enums
    └── sidebar.ts       ← TypeScript interfaces for sidebar nav item and group descriptors
```

## Stores (Pinia)

All state is managed through Pinia stores. Import stores where needed:

```typescript
import { useAuthStore } from '@/store/auth'
import { useModuleFeedStore } from '@/store/moduleFeed'
import { useSidebarStore } from '@/store/sidebar'
```

| Store | Responsibility |
|---|---|
| `auth` | Login state, access token, user info, `verifyAuth()` called by route guard |
| `moduleFeed` | WebSocket singleton for the live event feed. Ref-counted — multiple components share one socket. Auto-reconnects with exponential backoff. |
| `sidebar` | Collapsed/expanded state (persisted to `localStorage`), dynamic nav item registry, badge support |
| `system` | Module name, display name, version — loaded on startup |
| `plugins` | Registry of installed plugins and their injected frontend slots |

## Router

Routes are defined in `router/index.ts`. All routes except `/{{ module_name }}/login` require
authentication. The route guard calls `useAuthStore().verifyAuth()` and redirects to the login
page if the token is invalid.

Adding a new page:

1. Create a feature view under `features/<area>/<AreaView>.vue`
2. Add the route in `router/index.ts`
3. Register a sidebar nav item via `useSidebarStore().registerNavItem(...)` if needed

## Features

Each subdirectory under `features/` represents one page or functional area of the UI.
A feature typically contains one or more view components and, if it has dedicated API calls,
a `<feature>.api.ts` file alongside.

Keep feature-specific logic inside the feature directory. Shared logic belongs in `composables/`
or `store/`.

## Components

`components/` holds reusable UI building blocks that are not tied to a specific route.
`components/layout/` contains the application shell (sidebar, nav items).

## Composables

`composables/` contains Vue Composition API functions (`use*`) that encapsulate reusable
reactive logic — for example, subscribing to the feed store, polling an operation's state,
or managing sidebar nav registration.

## API Clients (`api/`)

HTTP calls to the backend REST API are centralised here. The `http.ts` Axios instance handles
the base URL, auth token injection via interceptors, and error normalisation.
Feature-specific endpoints can be co-located in the feature folder as `<feature>.api.ts`.

## Path Alias

`@/` resolves to `src/` (configured in `tsconfig.json` and `vite.config.ts`):

```typescript
import { useAuthStore } from '@/store/auth'
import type { ApiResponse } from '@/types/common'
```
