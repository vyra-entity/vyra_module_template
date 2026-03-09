"""
PluginClient — Client für den ``get_plugin_ui_manifest``-Vyra-Transport-Service.

Dieses Template zeigt, wie ein Modul (z.B. v2_dashboard) das UI-Manifest
für Plugins anfragt, die im v2_modulemanager installiert sind.

Flow:
  1. PluginClient.setup(entity) erstellt einen VyraClient via InterfaceFactory
  2. Frontend lädt PluginRepositoryView → ruft /plugin/ui-manifest ab →
     BackendRouter delegiert an PluginClient.get_ui_manifest()
  3. v2_modulemanager antwortet mit Slot-Belegung aus DB

Vyra-Service-Definition:
  ``v2_modulemanager_interfaces/config/modulemanager_plugin.meta.json``
  → service ``get_plugin_ui_manifest``

Verwendung in _base_.py::

    from {{ module_name }}.plugin.plugin_client import PluginClient
    from {{ module_name }}.container_injection import set_plugin_client

    plugin_client = PluginClient()
    await plugin_client.setup(entity)
    set_plugin_client(plugin_client)
"""

from __future__ import annotations

import logging
from typing import TYPE_CHECKING, Any

from vyra_base.com.core.factory import InterfaceFactory

if TYPE_CHECKING:
    from vyra_base.core import VyraEntity

logger = logging.getLogger(__name__)


class PluginClient:
    """
    Client für den v2_modulemanager Vyra-Plugin-Service.

    Dieses Modul führt keine eigenen WASM-Plugins aus.
    Es fragt das Manifest bei v2_modulemanager an und gibt es
    an das eigene Frontend weiter.

    Verwendet InterfaceFactory.create_client() — kein direkter Vyra-Zugriff.

    Beispiel-Integration in _base_.py::

        from {{ module_name }}.plugin.plugin_client import PluginClient

        plugin_client = PluginClient()
        await plugin_client.setup(entity)
        manifest = await plugin_client.get_ui_manifest(scope_target="{{ module_name }}")
    """

    def __init__(self) -> None:
        self._client: Any = None

    async def setup(self, entity: "VyraEntity") -> None:
        """
        Erstellt den Vyra-Client für den ``get_plugin_ui_manifest``-Service.

        Muss aufgerufen werden, nachdem der VyraEntity gestartet wurde.

        :param entity: Initialisierter VyraEntity dieses Moduls
        """
        try:
            self._client = await InterfaceFactory.create_client(
                name="get_plugin_ui_manifest",
                module_name="v2_modulemanager",
                namespace="plugin",
            )
            logger.info("✅ PluginClient: Client für 'get_plugin_ui_manifest' bereit")
        except Exception as exc:
            logger.warning("⚠️  PluginClient: Client konnte nicht initialisiert werden: %s", exc)
            self._client = None

    async def get_ui_manifest(
        self,
        scope_type:   str = "MODULE",
        scope_target: str | None = None,
    ) -> dict:
        """
        Fragt das UI-Slot-Manifest vom v2_modulemanager ab.

        :param scope_type:   GLOBAL | TEMPLATE | MODULE
        :param scope_target: z.B. '{{ module_name }}', None für GLOBAL
        :returns:            Dict mit 'slots' (slot_id → list of components)
        """
        if self._client is None:
            logger.warning("PluginClient.get_ui_manifest: Kein Client verfügbar")
            return {"scope_type": scope_type, "scope_target": scope_target, "slots": {}}

        try:
            result = await self._client.call({
                "scope_type":   scope_type,
                "scope_target": scope_target,
            })
            return result or {}
        except Exception as exc:
            logger.error("PluginClient.get_ui_manifest Fehler: %s", exc)
            return {"scope_type": scope_type, "scope_target": scope_target, "slots": {}}

    async def teardown(self) -> None:
        """Schließt den Vyra-Client."""
        if self._client is not None:
            try:
                await self._client.close()
            except Exception:
                pass
            self._client = None
        logger.info("PluginClient: Client geschlossen")
