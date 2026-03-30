"""
HTTP Clients Package

Provides HTTP-based communication clients.
"""
from .hardware import HardwareRegistryClient
from .module_http import ModuleHttpClient

__all__ = ['HardwareRegistryClient', 'ModuleHttpClient']
