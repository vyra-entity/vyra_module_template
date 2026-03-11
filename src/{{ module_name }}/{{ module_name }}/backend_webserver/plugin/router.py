"""
Plugin Router — {{ module_name }}

Endpunkte:
  GET  /plugin/ui-manifest              — UI-Slot-Manifest von v2_modulemanager (via PluginClient)
  POST /plugin/{plugin_id}/call         — Plugin-Funktion via v2_modulemanager ausführen

Dieses Modul führt keine WASM-Plugins lokal aus — alle Plugin-Operationen
werden an v2_modulemanager delegiert.
"""

from __future__ import annotations

import logging
from typing import Any

from fastapi import APIRouter, Depends, HTTPException, Query
from pydantic import BaseModel, Field

from ...container_injection import provide_plugin_client

logger = logging.getLogger(__name__)

router = APIRouter()


# ---------------------------------------------------------------------------
# Pydantic models
# ---------------------------------------------------------------------------

class PluginCallRequest(BaseModel):
    function_name: str = Field(description="Name der aufzurufenden Plugin-Funktion")
    data: dict[str, Any] = Field(default_factory=dict, description="Eingabeparameter")


class PluginCallResponse(BaseModel):
    plugin_id: str
    function_name: str
    result: dict[str, Any]
    success: bool = True


# ---------------------------------------------------------------------------
# GET /ui-manifest
# ---------------------------------------------------------------------------

@router.get(
    "/ui-manifest",
    summary="UI-Slot-Manifest von v2_modulemanager (scope-basiert)",
)
async def get_ui_manifest(
    scope_type: str = Query(default="MODULE", description="GLOBAL, TEMPLATE oder MODULE"),
    scope_target: str | None = Query(default=None, description="Scope-Ziel"),
    plugin_client=Depends(provide_plugin_client),
):
    """
    Gibt das Plugin-Slot-Manifest zurück.
    Delegiert via VYRA-Transportschicht an v2_modulemanager.
    """
    try:
        result = await plugin_client.get_ui_manifest(scope_type=scope_type, scope_target=scope_target)
        return result
    except Exception as exc:
        logger.error("ui-manifest Fehler: %s", exc)
        raise HTTPException(status_code=502, detail=f"v2_modulemanager nicht erreichbar: {exc}")


# ---------------------------------------------------------------------------
# POST /{plugin_id}/call — proxy to v2_modulemanager
# ---------------------------------------------------------------------------

@router.post(
    "/{plugin_id}/call",
    response_model=PluginCallResponse,
    summary="Plugin-Funktion via v2_modulemanager aufrufen",
)
async def call_plugin_function(
    plugin_id: str,
    body: PluginCallRequest,
    plugin_client=Depends(provide_plugin_client),
):
    """
    Führt eine Plugin-Funktion im v2_modulemanager-WASM-Runtime aus.
    Delegiert den Aufruf per Zenoh RPC.
    """
    try:
        result = await plugin_client.call_plugin(
            plugin_id=plugin_id,
            function_name=body.function_name,
            data=body.data,
        )
        return PluginCallResponse(
            plugin_id=plugin_id,
            function_name=body.function_name,
            result=result,
            success=True,
        )
    except Exception as exc:
        logger.error("Plugin-Aufruf Fehler [%s.%s]: %s", plugin_id, body.function_name, exc)
        raise HTTPException(status_code=502, detail=f"Plugin-Aufruf fehlgeschlagen: {exc}")
