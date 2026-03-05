"""User management package — external client + internal fallback manager."""

from .usermanager_client import UserManagerClient, usermanager_client_runner
from .internal_usermanager import InternalUserManager
from .tb_users import User, UserRole, UserLevel
from .usermanager import UserManager, usermanager_runner

__all__ = [
    # External client (used when v2_usermanager module is available)
    "UserManagerClient",
    "usermanager_client_runner",
    # Internal fallback manager (local user storage, no token generation)
    "InternalUserManager",
    "UserManager",
    "usermanager_runner",
    # DB model
    "User",
    "UserRole",
    "UserLevel",
]
