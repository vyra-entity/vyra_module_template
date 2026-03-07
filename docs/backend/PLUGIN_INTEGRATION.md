# Plugin-Integration in VYRA-Modulen

## Überblick

Dieses Dokument beschreibt, wie ein Modul (z.B. `v2_dashboard`) die Plugin-Infrastruktur
des VYRA-Ökosystems nutzt, um WASM-Plugins in seiner UI zu laden.

**Wichtig**: Das Modul führt die Plugins **nicht selbst aus** — das macht `v2_modulemanager`.
Das Modul fragt nur das UI-Manifest ab und lädt die Vue-Komponenten.

---

## Rollen der Beteiligten

| Komponente | Rolle |
|-----------|------|
| `v2_modulemanager` | Führt WASM aus, verwaltet DB, bietet REST + Zenoh API |
| `container_manager` | Kopiert Plugin-Dateien in NFS-Pool, prüft Checksums |
| `Dein Modul` | Fragt UI-Manifest ab, lädt Vue-Komponenten aus NFS-Proxy |
| `vyra_base.plugin` | Abstrakte Typen: BaseHostFunctions, WasmRuntime etc. |

---

## Schritt 1: PluginRegistry einbinden

Die `PluginRegistry` im Modul-Template ist bereits vorbereitet.

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
