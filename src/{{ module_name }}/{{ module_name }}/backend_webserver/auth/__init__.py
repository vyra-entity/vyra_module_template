"""
Authentication package for v2_modulemanager
"""

from .auth_service import AuthenticationService
from .router import router as auth_router, set_auth_service

__all__ = ['AuthenticationService', 'auth_router', 'set_auth_service']
