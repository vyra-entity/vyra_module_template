"""
Plugin-Registry für VYRA-Module — UI-Manifest-Integration.

Dieses Template zeigt, wie ein Modul (z.B. v2_dashboard) das UI-Manifest
für Plugins anfragt, die im v2_modulemanager installiert sind.

Flow:
  1. Modul X startet seinen VyraEntity
  2. PluginRegistry.setup(entity) erstellt einen VyraClient zur Zenoh-Schnittstelle
     von v2_modulemanager (definiert in modulemanager_plugin.meta.json)
  3. Frontend lädt PluginRepositoryView → ruft /plugin/ui-manifest ab →
     das Backend-Proxy delegiert die Anfrage via Zenoh an v2_modulemanager

Zenoh-Service-Definition:
  ``v2_modulemanager_interfaces/config/modulemanager_plugin.meta.json``
  → service ``get_plugin_ui_manifest``

Wann HostFunctions benötigt werden:
  Wenn das Modul X selbst WASM-Plugins ausführt (nicht bei reiner UI-Integration),
  muss es ``BaseHostFunctions`` mit eigener Zenoh-/Publisher-Implementierung
  verwenden (siehe host_functions_impl.py in v2_modulemanager als Referenz).
"""

from __future__ import annotations

import logging
from typing import TYPE_CHECKING, Any

if TYPE_CHECKING:
    from vyra_base.entity import VyraEntity

logger = logging.getLogger(__name__)


class PluginRegistry:
    """
    UI-Plugin-Registry — ruft das Slot-Manifest von v2_modulemanager ab.

    Dieses Modul führt KEINE WASM-Plugins selbst aus.
    Es fragt das Manifest bei v2_modulemanager an und gibt es
    an das eigene Frontend weiter.

    Dafür nutzt es den Zenoh-Service ``plugin/get_plugin_ui_manifest``
    der in der modulemanager_plugin.meta.json definiert ist.

    Beispiel-Integration in _base_.py::

        from {{ module_name }}.plugin.registry import PluginRegistry

        plugin_registry = PluginRegistry()
        await plugin_registry.setup(entity)
        manifest = await plugin_registry.get_ui_manifest(scope_target="{{ module_name }}")
    """

    def __init__(self) -> None:
        self._client: Any = None   # VyraClient (nach setup() verfügbar)
        self._entity: Any = None

    async def setup(self, entity: "VyraEntity") -> None:
        """
        Erstellt den Zenoh-Client für den ``get_plugin_ui_manifest``-Service.

        Muss aufgerufen werden, nachdem der VyraEntity gestartet wurde und
        die Zenoh-Infrastruktur bereit ist.

        :param entity: Initialisierter VyraEntity dieses Moduls
        """
        from vyra_base.com.transport import InterfaceFactory

        self._entity = entity

        try:
            # Client-Interface für den Zenoh-Service des v2_modulemanager
            # Die Schnittstelle ist in modulemanager_plugin.meta.json definiert
            self._client = await InterfaceFactory.create_client(
                entity=entity,
                namespace="plugin",
                function_name="get_plugin_ui_manifest",
                # topic: {v2_modulemanager_name}/plugin/get_plugin_ui_manifest
                remote_module="v2_modulemanager",
            )
            logger.info("✅ PluginRegistry: Zenoh-Client für get_plugin_ui_manifest bereit")
        except Exception as exc:
            logger.warning("⚠️  PluginRegistry: Zenoh-Client konnte nicht initialisiert werden: %s", exc)
            self._client = None

    async def get_ui_manifest(
        self,
        scope_type:   str = "MODULE",
        scope_target: str | None = None,
    ) -> dict:
        """
        Fragt das UI-Slot-Manifest vom v2_modulemanager ab.

        Gibt ein Dict zurück mit Schüssel ``slots`` (slot_id → list of components).
        Leer wenn v2_modulemanager nicht erreichbar oder kein Plugin installiert.

        :param scope_type:   GLOBAL | TEMPLATE | MODULE
        :param scope_target: z.B. '{{ module_name }}' oder None für GLOBAL
        """
        if self._client is None:
            logger.warning("PluginRegistry.get_ui_manifest: Kein Zenoh-Client verfügbar")
            return {"scope_type": scope_type, "scope_target": scope_target, "slots": {}}

        try:
            result = await self._client.call({
                "scope_type":   scope_type,
                "scope_target": scope_target,
            })
            return result or {}
        except Exception as exc:
            logger.error("PluginRegistry.get_ui_manifest Fehler: %s", exc)
            return {"scope_type": scope_type, "scope_target": scope_target, "slots": {}}

    async def teardown(self) -> None:
        """Bereinigt Zenoh-Ressourcen."""
        if self._client is not None:
            try:
                await self._client.close()
            except Exception:
                pass
            self._client = None
        logger.info("PluginRegistry: Zenoh-Client geschlossen")

                logger.warning(f"[PluginRegistry] '{subdir.name}' is not a directory, skipping.")