# Plugin-Integration in VYRA-Modulen

## Überblick

Dieses Dokument beschreibt, wie ein Modul (z.B. `v2_dashboard`) die Plugin-Infrastruktur
des VYRA-Ökosystems nutzt, um WASM-Plugins in seiner UI zu laden und bidirektional
mit Plugin-Logik zu kommunizieren.

**Wichtig**: Plugins werden ausschließlich vom `v2_modulemanager` installiert und verwaltet.
Andere Module fragen das UI-Manifest ab, leiten Aufrufe weiter und empfangen Events via `PluginBridge`.

---

## Rollen der Beteiligten

| Komponente | Rolle |
|-----------|------|
| `v2_modulemanager` | Verwaltet Plugin-DB, führt WASM aus, bietet `get_ui_manifest`- und `call_plugin`-Zenoh-Services |
| `container_manager` | Kopiert Plugin-Dateien in NFS-Pool, prüft Checksums, validiert Plugins aus Repository |
| `Dein Modul` | Fragt UI-Manifest ab, leitet `call_plugin` weiter, empfängt/sendet Plugin-Events via `PluginBridge` |
| `vyra_base.plugin` | Abstrakte Typen: BaseHostFunctions, WasmRuntime etc. |

---

## Architektur

```
Frontend ◄──WS──► /ws/plugin/{plugin_id}/{channel}
                        │
                   PluginBridge (Singleton, In-Memory)
                   ┌────┴────────────────────────────┐
                   │  publish/receive/history         │
                   └────┬────────────────────────────┘
                        │ Zenoh
                   PluginClient ──► v2_modulemanager
                        │               (WASM Runtime)
                   /plugin/{id}/call
```

- **`PluginBridge`** — Singleton, verwaltet asyncio-Queues pro Channel. Leitet ausgehende Calls via Zenoh zum `v2_modulemanager` weiter; empfängt Events und broadcastet sie an WebSocket-Subscriber.
- **`PluginClient`** — Zenoh-Client-Wrapper; `get_ui_manifest()` + `call_plugin()`.
- **`FeedStreamer`** — Singleton, broadcast alle `FeedMessage`-Events an WebSocket-Verbindungen.

---

## Schritt 1: Services in Container einbinden

`container_injection.py` enthält bereits alle nötigen Provider:

```python
from {{ module_name }}.container_injection import (
    set_plugin_client,
    set_plugin_bridge,
    provide_plugin_client,
    provide_plugin_bridge,
)
```

---

## Schritt 2: Initialisierung im Lifespan (main_rest.py)

```python
from .services.plugin_bridge import PluginBridge
from ..container_injection import set_plugin_bridge

@asynccontextmanager
async def lifespan(app: FastAPI):
    # PluginBridge starten
    plugin_bridge = PluginBridge.get_instance()
    set_plugin_bridge(plugin_bridge)

    yield
    # Shutdown: keine explizite Aktion nötig
```

Der `PluginClient` wird in `_base_.py` / `main.py` gesetzt, nachdem die Zenoh-Interfaces bereit sind:

```python
from {{ module_name }}.plugin.plugin_client import PluginClient
from {{ module_name }}.container_injection import set_plugin_client

async def initialize_module(entity):
    plugin_client = PluginClient(entity)
    set_plugin_client(plugin_client)
```

---

## Schritt 3: REST-Endpoints (plugin/router.py)

```python
from fastapi import APIRouter, Depends
from ..container_injection import provide_plugin_client

router = APIRouter()

@router.get("/ui-manifest")
async def get_plugin_manifest(
    plugin_client = Depends(provide_plugin_client),
):
    return await plugin_client.get_ui_manifest()

@router.post("/{plugin_id}/call")
async def call_plugin(
    plugin_id: str,
    request: PluginCallRequest,
    plugin_client = Depends(provide_plugin_client),
):
    result = await plugin_client.call_plugin(plugin_id, request.function_name, request.data)
    return PluginCallResponse(plugin_id=plugin_id, result=result)
```

---

## Schritt 4: WebSocket-Endpoint (websocket/router.py)

Der `/ws/plugin/{plugin_id}/{channel}` Endpoint ist bereits in `websocket/router.py` eingebaut:

- Bei Connect: Historie der letzten 50 Nachrichten aus `PluginBridge` senden
- Eingehende WS-Frames (`client_to_server`): an `bridge.receive(channel, payload)` weiterleiten  
- Ausgehende Bridge-Events: via asyncio-Queue in Fan-out-Task zum Client senden

---

## Schritt 5: Vue-Komponenten laden (Frontend)

```typescript
// src/features/plugins/usePluginSlots.ts
import { ref, onMounted } from 'vue'
import { pluginApi } from './plugin.api'

export function usePluginSlots(slotId: string) {
  const components = ref<Component[]>([])

  onMounted(async () => {
    const manifest = await pluginApi.getUiManifest()
    const entries = manifest.slots[slotId] ?? []

    for (const entry of entries) {
      try {
        const mod = await import(/* @vite-ignore */ entry.js_entry_point)
        components.value.push(markRaw(mod.default))
      } catch (err) {
        console.warn('Plugin laden fehlgeschlagen:', entry.component_name, err)
      }
    }
  })

  return { components }
}
```

---

## Schritt 6: Bidirektionale Plugin-Kommunikation (WebSocket)

```typescript
// Frontend: Plugin-WebSocket öffnen
const ws = new WebSocket(`wss://host/ws/plugin/${pluginId}/main`)

ws.onmessage = (event) => {
  const msg = JSON.parse(event.data)
  if (msg.type === 'server_to_client') {
    // Plugin-Event verarbeiten
  }
}

// Aufruf an Plugin senden
ws.send(JSON.stringify({
  type: 'client_to_server',
  payload: { action: 'update', data: { value: 42 } }
}))
```

---

## Zenoh-Schnittstelle

Das Modul kommuniziert mit `v2_modulemanager` via Zenoh-Services:

```
get_ui_manifest:  v2_modulemanager_{id}/plugin/get_plugin_ui_manifest
call_plugin:      v2_modulemanager_{id}/plugin/call_plugin
```

Definiert in: `v2_modulemanager_interfaces/config/modulemanager_plugin.meta.json`

---

## Klassen-Referenz

| Klasse | Datei | Zweck |
|--------|-------|-------|
| `BaseEventBridge` | `backend_webserver/services/base_event_bridge.py` | ABC für alle Event-Bridges |
| `FeedStreamer` | `backend_webserver/services/feed_streamer.py` | Broadcast-Feed für Frontend-Updates |
| `PluginBridge` | `backend_webserver/services/plugin_bridge.py` | Bidirektionale Plugin-Event-Bridge |
| `PluginClient` | `plugin/plugin_client.py` | Zenoh-Proxy zu v2_modulemanager |
| `ConnectionManager` | `backend_webserver/websocket/service.py` | WebSocket-Verbindungsverwaltung |

---

## Weiterführende Dokumentation

- [WEBSOCKET_API.md](../backend/WEBSOCKET_API.md) — WebSocket-Protokoll  
- [Plugin-System (vyra_base_python)](../../../../VYRA/vyra_base_python/docs/backend/PLUGIN_SYSTEM.md)


---

## Rollen der Beteiligten

| Komponente | Rolle |
|-----------|------|
| `v2_modulemanager` | Läd Plugin Daten in DB und verwaltet (Plugin Mainifest API)|
| `container_manager` | Kopiert Plugin-Dateien in NFS-Pool, prüft Checksums, validiert Plugins aus Repository |
| `Dein Modul` | Fragt UI-Manifest ab, bietet Plugin Host Functions, lädt Vue-Komponenten aus NFS-Proxy, kommuniziert mit fremden oder eigener Plugin-Logic (Wasm) |
| `vyra_base.plugin` | Abstrakte Typen: BaseHostFunctions, WasmRuntime etc. |

---

## Schritt 1: PluginRegistry einbinden

Die `PluginRegistry` im Modul ist bereits vorbereitet.

**Datei**: `src/{{ module_name }}/{{ module_name }}/plugin/registry.py`

```python
from {{ module_name }}.plugin.registry import PluginRegistry

plugin_registry = PluginRegistry()
```

---

## Schritt 2: Setup im VyraEntity-Start

In `_base_.py` nach dem Entity-Start aufrufen:

```python
# In deiner _base_.py oder entity_setup.py
from {{ module_name }}.plugin.registry import PluginRegistry

class {{ module_name }}Entity:
    def __init__(self):
        self.plugin_registry = PluginRegistry()

    async def start(self, entity):
        await entity.set_interfaces(base_interfaces)
        # Plugin-Registry verbinden (Zenoh muss bereit sein)
        await self.plugin_registry.setup(entity)
```

---

## Schritt 3: UI-Manifest abfragen (Backend-API)

In deinem FastAPI-Router:

```python
from fastapi import APIRouter, Depends
from {{ module_name }}.plugin.registry import PluginRegistry

router = APIRouter()

@router.get("/plugin/ui-manifest")
async def get_plugin_manifest(
    scope_target: str | None = None,
    plugin_registry: PluginRegistry = Depends(get_plugin_registry),
):
    """
    Fragt das UI-Manifest bei v2_modulemanager an (via Zenoh).
    Gibt eine Slot-Belegung zurück, die das Frontend nutzt.
    """
    return await plugin_registry.get_ui_manifest(
        scope_type="MODULE",
        scope_target=scope_target or "{{ module_name }}",
    )
```

---

## Schritt 4: Vue-Komponenten laden (Frontend)

Im Frontend wird die JS-Komponente dynamisch via `import()` geladen:

```typescript
// src/features/plugins/usePluginSlots.ts
import { ref, onMounted } from 'vue'
import { pluginApi } from './plugin.api'

export function usePluginSlots(slotId: string) {
  const components = ref<Component[]>([])

  onMounted(async () => {
    const manifest = await pluginApi.getUiManifest('MODULE', '{{ module_name }}')
    const entries = manifest.slots[slotId] ?? []

    for (const entry of entries) {
      try {
        // Dynamischer Import der WASM-Komponente aus dem Proxy
        const mod = await import(/* @vite-ignore */ entry.js_entry_point)
        components.value.push(markRaw(mod.default))
      } catch (err) {
        console.warn('Plugin laden fehlgeschlagen:', entry.component_name, err)
      }
    }
  })

  return { components }
}
```

---

## Schritt 5 (optional): HostFunctions implementieren

Nur nötig wenn **das Modul selbst WasmRuntime betreibt** (unüblich — normalerweise macht das v2_modulemanager).

```python
from vyra_base.plugin import BaseHostFunctions
from vyra_base.com.transport import VyraPublisher

class {{ module_name }}HostFunctions(BaseHostFunctions):
    """
    Konkrete HostFunctions für {{ module_name }}.
    Wird nur benötigt wenn das Modul selbst WASM-Plugins ausführt.

    Referenz-Implementierung: v2_modulemanager/plugin/host_functions_impl.py
    """

    def __init__(self, publisher: VyraPublisher, zenoh_session) -> None:
        self._publisher = publisher
        self._session   = zenoh_session

    async def notify_ui(self, plugin_id: str, event_name: str, data: dict) -> None:
        await self._publisher.publish({
            "plugin_id":  plugin_id,
            "event_name": event_name,
            "data":       data,
        })

    async def zenoh_get(self, key: str) -> dict:
        return await self._session.get(key)

    async def zenoh_put(self, key: str, value: dict) -> None:
        await self._session.put(key, value)
```

---

## Zenoh-Schnittstelle

Das Modul kommuniziert mit v2_modulemanager via Zenoh-Service:

```
Topic: v2_modulemanager_{id}/plugin/get_plugin_ui_manifest
Typ:   VyraClient.call({scope_type, scope_target}) → {slots}
```

Definiert in: `v2_modulemanager_interfaces/config/modulemanager_plugin.meta.json`

---

## Weiterführende Dokumentation

- [Plugin-System Architektur](../../../../VYRA/vyra_base_python/docs/backend/PLUGIN_SYSTEM.md)
- [v2_modulemanager Plugin-Router](../../../VOS2_WORKSPACE/modules/v2_modulemanager_733256b82d6b48a48bc52b5ec73ebfff/src/v2_modulemanager/v2_modulemanager/backend_webserver/plugin/router.py)
- [BaseHostFunctions](../../../../VYRA/vyra_base_python/src/vyra_base/plugin/host_functions.py)
