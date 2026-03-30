# Plugin System

This package implements the WASM plugin runtime for the `{{ module_name }}` module.

## What Plugins Are

Plugins are **WebAssembly (WASM) modules** compiled from any WASM-compatible language
(e.g. Rust, C/C++, AssemblyScript). They are loaded and executed at runtime by
`PluginGateway` without any restart of the host module.

Plugins extend the module's functionality without requiring changes to the module's source code.
They are installed and managed exclusively through the Module Manager — never copied manually
into the container.

## Plugin Installation

Plugins are published to a VYRA plugin repository and installed via the Module Manager:

```bash
curl -k -X POST https://localhost/v2_modulemanager/api/plugins/install \
  -H "Content-Type: application/json" \
  -d '{"plugin_name": "my-plugin", "version": "1.0.0"}'
```

After installation the Module Manager loads the plugin into the running `PluginGateway` without a module restart.

## What Plugins Can Access — `plugin_interfaces.yaml`

The host functions available to a WASM plugin are declared in:

```
.module/plugin_interfaces.yaml
```

This file lists a `linker_map` that maps WASM-side function names to the gate functions
implemented in `PluginGateway`:

```yaml
linker_map:
  - namespace: "vyra"
    functions:
      - wasm_name: "log"
        host_func: "log"

      - wasm_name: "publish"
        host_func: "publish_event"

      - wasm_name: "request"
        host_func: "send_request"
```

- `wasm_name` — the function name the WASM binary calls (imported from the `vyra` namespace)
- `host_func` — the corresponding Python gate function on `PluginGateway`

## Implementing Gate Functions in `PluginGateway`

Every `host_func` listed in `plugin_interfaces.yaml` **must be implemented** as a method on
`PluginGateway`. The WASM runtime will fail to load if a declared gate function is missing.

Example implementations matching the default `plugin_interfaces.yaml`:

```python
class PluginGateway:

    def log(self, msg: str, level: str) -> None:
        """Gate function: called by WASM plugins to emit a log line."""
        logger = get_logger("plugin")
        getattr(logger, level.lower(), logger.info)(msg)

    def publish_event(self, topic: str, payload: str) -> None:
        """Gate function: called by WASM plugins to publish an event on the CAL."""
        # Forward to the entity's publish interface
        self._entity.publish(topic, payload)

    def send_request(self, service: str, payload: str) -> str:
        """Gate function: called by WASM plugins to call a remote service."""
        return self._entity.call_service(service, payload)
```

Add new gate functions here whenever a new entry is added to `plugin_interfaces.yaml`.

## UI Access and Cross-Module Plugins

Plugins can inject frontend components into the module's Vue UI via the **plugin bridge**
(`backend_webserver/services/plugin_bridge.py`). The bridge exposes plugin events and
component registration over WebSocket, so plugins render inside the host module's frontend.

Plugins can also interact **across module boundaries** — for example, a plugin installed in
`{{ module_name }}` can publish events that are consumed by another module's frontend via the
shared Zenoh/Redis channels. This allows plugins to act as integration points between modules
without tight coupling.
