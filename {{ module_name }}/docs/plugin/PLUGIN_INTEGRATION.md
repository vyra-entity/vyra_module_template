# Plugin Integration in VYRA Modules

## Overview

This document describes how a consumer module uses the VYRA plugin infrastructure
to load WASM plugins into its UI and communicate bidirectionally with plugin logic.

**Important**: Plugins are installed and managed exclusively by `v2_modulemanager`.
Consumer modules query the UI manifest, forward calls, and receive events via
`PluginBridge`.

---

## Roles

| Component | Role |
|-----------|------|
| `v2_modulemanager` | Manages plugin DB, executes WASM, provides `resolve_plugins` and `ui_function_call` Zenoh services |
| `container_manager` | Copies plugin files to NFS pool, verifies checksums, validates plugins from repository |
| `This module` | Queries UI manifest, forwards `call_plugin`, receives/sends plugin events via `PluginBridge` |
| `vyra_base.plugin` | Abstract types: `PluginRuntime`, `PluginCallError`, etc. |

---

## Architecture

```
Frontend ◄──WS──► /ws/plugin/{plugin_id}/{channel}
                        │
                   PluginBridge (Singleton, In-Memory)
                   ┌────┴────────────────────────────┐
                   │  publish / receive / history     │
                   └────┬────────────────────────────┘
                        │ Zenoh
                   PluginGateway ──► v2_modulemanager
                        │               (WASM Runtime)
                   /plugin/resolve_plugins
                   /plugin/{id}/call
```

- **`PluginGateway`** — Manages two Zenoh clients: `_resolve_client` → `resolve_plugins`@v2_modulemanager, `_ui_call_client` → `ui_function_call`@v2_modulemanager. Caches the manifest in RAM.
- **`PluginBridge`** — Singleton, manages asyncio queues per channel. Forwards outgoing calls via Zenoh to `v2_modulemanager`; receives events and broadcasts them to WebSocket subscribers.
- **`FeedStreamer`** — Singleton, broadcasts all `FeedMessage` events to WebSocket connections.

---

## Step 1: Lifecycle — main.py

`PluginGateway` is initialised in `main.py` after the entity is ready:

```python
from .plugin.plugin_gateway import PluginGateway
from .container_injection import set_plugin_gateway

plugin_gateway = PluginGateway()
await plugin_gateway.setup(entity)
set_plugin_gateway(plugin_gateway)
```

---

## Step 2: Container Injection

`container_injection.py` provides all necessary providers:

```python
from {{ module_name }}.container_injection import (
    set_plugin_gateway,
    get_plugin_gateway,
    provide_plugin_gateway,
    set_plugin_bridge,
    provide_plugin_bridge,
)
```

---

## Step 3: REST Endpoints (backend_webserver/plugin/router.py)

```python
from fastapi import APIRouter, Depends, HTTPException, Query
from ...container_injection import provide_plugin_gateway

router = APIRouter()

@router.get("/resolve_plugins")
async def resolve_plugins(
    scope_type: str = Query(default="MODULE"),
    scope_target: str | None = Query(default=None),
    module_name: str | None = Query(default=None),
    module_id: str | None = Query(default=None),
    p_id: str | None = Query(default=None),
    gateway=Depends(provide_plugin_gateway),
):
    return await gateway.resolve_plugins(
        scope_type=scope_type,
        scope_target=scope_target,
        module_name=module_name,
        module_id=module_id,
        p_id=p_id,
    )

@router.post("/{plugin_id}/call")
async def call_plugin_function(plugin_id: str, body: PluginCallRequest, gateway=Depends(provide_plugin_gateway)):
    result = await gateway.call_plugin(plugin_id, body.function_name, body.data)
    return PluginCallResponse(plugin_id=plugin_id, function_name=body.function_name, result=result)
```

---

## Step 4: Frontend API (plugin.api.ts)

```typescript
import { apiClient } from '@/api/client'

export const pluginApi = {
  async resolvePlugins(params?: {
    scope_type?: string
    scope_target?: string
    module_name?: string
    module_id?: string
    p_id?: string
  }) {
    const res = await apiClient.get('/plugin/resolve_plugins', { params })
    return res.data
  },

  async callPlugin(pluginId: string, functionName: string, data: Record<string, unknown> = {}) {
    const res = await apiClient.post(`/plugin/${pluginId}/call`, {
      function_name: functionName,
      data,
    })
    return res.data
  },
}
```

---

## Step 5: Frontend Store (store/plugins.ts)

```typescript
import { defineStore } from 'pinia'
import { pluginApi } from '@/features/plugins/plugin.api'

export const usePluginStore = defineStore('plugins', {
  state: () => ({
    manifest: { ui_slots: {}, plugin_metadata: [] } as ResolvePluginsResponse,
    loading: false,
  }),
  actions: {
    async loadManifest(scopeTarget?: string) {
      this.loading = true
      try {
        this.manifest = await pluginApi.resolvePlugins({ scope_target: scopeTarget })
      } finally {
        this.loading = false
      }
    },
  },
})
```

---

## Step 6: Frontend Rendering (PluginSlotHost.vue)

Plugins are rendered in UI slots using dynamic `import()`:

```vue
<template>
  <div v-for="component in slotComponents" :key="component.component_name">
    <component :is="asyncComponents[component.component_name]" />
  </div>
</template>

<script setup lang="ts">
import { defineAsyncComponent } from 'vue'
const asyncComponents = Object.fromEntries(
  slotComponents.value.map(c => [
    c.component_name,
    defineAsyncComponent(() => import(/* @vite-ignore */ c.js_entry_point)),
  ])
)
</script>
```

---

## PluginBridge — WebSocket Events

```python
from backend_webserver.services.plugin_bridge import PluginBridge

bridge = PluginBridge.get_instance()

# Send event to frontend
await bridge.publish("counter-widget/events", {"value": 5})

# Register handler for incoming frontend messages
bridge.register_handler("counter-widget/ui", my_async_handler)
```

WebSocket endpoint: `GET /ws/plugin/{plugin_id}/{channel}`

---

## Related Documentation

- [PLUGIN_BRIDGE.md](../backend/PLUGIN_BRIDGE.md) — Event-Bridge architecture
- [PLUGIN_ARCHITECTURE.md](../architecture/PLUGIN_ARCHITECTURE.md) — Full plugin flow
- [REST_API_CLIENT_ARCHITECTURE.md](../frontend/REST_API_CLIENT_ARCHITECTURE.md) — Frontend API layer
