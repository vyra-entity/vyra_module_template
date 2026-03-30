"""
REST API Module
"""

from .main_rest import app  # noqa: F401

__all__: list[str] = [
    "app",
]