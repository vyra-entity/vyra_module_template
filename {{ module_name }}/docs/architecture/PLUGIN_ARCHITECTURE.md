# Plugin Architecture — Consumer Module View

This document describes the plugin flow from a **consumer module** perspective.
For installation and DB management, see
[v2_modulemanager/docs/architecture/PLUGIN_ARCHITECTURE.md](../../../v2_modulemanager/docs/architecture/PLUGIN_ARCHITECTURE.md).

## Overview

Plugins are WebAssembly (WASM) + JavaScript bundles stored on a shared NFS volume.
`v2_modulemanager` owns the plugin database and the WASM runtime. **This module
does not run WASM locally** — it queries the manifest via Zenoh and routes calls
transparently to `v2_modulemanager`.

```
v2_modulemanager
    └── NFS Pool (/plugin_pool/)
        └── counter-widget/
            └── 1.0.0/
                ├── manifest.yaml
                ├── ui/
                │   └── index.js      (ES module, compiled Vue/Lit component)
                └── wasm/
                    └── logic.wasm    (WASM logic, executed in v2_modulemanager)
```

## Resolve Plugins Flow

```
This module — frontend
    GET /plugin/resolve_plugins?scope_type=MODULE&scope_target={{ module_name }}
        → backend_webserver/plugin/router.py
        → PluginGateway.resolve_plugins(...)
            → Zenoh: resolve_plugins @ v2_modulemanager
            → PluginManager._resolve_plugins_impl(...)
                SELECT assignments WHERE scope_type=MODULE AND scope_target='{{ module_name }}' AND is_active=True
                → { ui_slots: { "header-right": [{ component_name, js_entry_point, hosting_module_name, ... }] } }
        → stored in self._manifest_cache (in-memory)
        → returned to frontend
```

### INSTANCE Scope with Empty scope_target

When `scope_type=INSTANCE` and `scope_target` is empty, the query returns **all**
INSTANCE assignments without filtering on `scope_target`. This allows a single
assignment to serve all instances of a `module_name` without separate rows per instance.

## Plugin Call Flow

```
Frontend → POST /plugin/{plugin_id}/call
    → PluginGateway.call_plugin(plugin_id, function_name, data)
        → Zenoh: ui_function_call @ v2_modulemanager
        → GatewayWasmRuntimePool.call(...)
        → GatewayWasmRuntime executes WASM
        → result returned
```

The `hosting_module_name` field in the manifest entry indicates which module hosts
the WASM. The call is always routed to the hosting module (transparent to the
frontend).

## UI Rendering

```
Frontend (this module)
    loadManifest(scopeType, scopeTarget)
    → GET /plugin/resolve_plugins → { ui_slots: { "slot-id": [{ js_entry_point }] } }
    → defineAsyncComponent(() => import(js_entry_point))
    → <PluginSlotHost slot-id="slot-id" />  renders all components for that slot
```

## PluginGateway — Class Summary

| Method | Description |
|--------|-------------|
| `setup(entity)` | Creates Zenoh clients for `resolve_plugins` and `ui_function_call` |
| `resolve_plugins(scope_type, scope_target, module_name, module_id, p_id)` | Fetches manifest from v2_modulemanager, caches in RAM |
| `get_manifest()` | Returns in-memory manifest cache synchronously |
| `call_plugin(plugin_id, function_name, data)` | Routes call via `ui_function_call` to hosting module |
| `teardown()` | Closes all Zenoh clients |

## Security

- `is_verified` is set by `container_manager` after checksum validation
- Unverified plugins show a warning badge in the UI and require user confirmation
- Asset URLs are served by the `v2_modulemanager` asset proxy (path traversal prevention)

## Related Documentation

- [PLUGIN_INTEGRATION.md](../plugin/PLUGIN_INTEGRATION.md) — Setup guide for this module
- [PLUGIN_BRIDGE.md](../backend/PLUGIN_BRIDGE.md) — Event-Bridge & WebSocket architecture
