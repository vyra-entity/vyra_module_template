"""
DEPRECATED: registry.py → Verwende plugin_client.py und PluginClient.

Dieser Import-Shim bleibt für Rückwärtskompatibilität.
"""
from .plugin_client import PluginClient as PluginRegistry  # noqa: F401

__all__ = ["PluginRegistry"]
