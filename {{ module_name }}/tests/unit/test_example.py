"""
Example unit tests for {{ module_name }} module.

These tests demonstrate the testing structure and patterns.
Run with: pytest -m unit tests/unit/test_example.py
"""

import pytest
import sys
from unittest.mock import Mock, MagicMock, patch
import os


# =============================================================================
# Backend Configuration Tests
# =============================================================================

class TestBackendConfig:
    """Test backend_webserver configuration."""
    
    def test_settings_default_values(self):
        """Test Settings class loads default values correctly."""
        from {{ module_name }}.{{ module_name }}.backend_webserver.core.config import Settings
        
        settings = Settings()
        
        assert settings.LOG_LEVEL == "INFO"
        assert settings.API_TITLE == "VYRA Module Manager API"
        assert isinstance(settings.WORKSPACE_ROOT, __import__("pathlib").Path)
    
    def test_settings_custom_values(self):
        """Test Settings class exposes log-level from current environment."""
        from {{ module_name }}.{{ module_name }}.backend_webserver.core.config import Settings
        
        # Settings class variables are evaluated at class-definition time, so
        # they reflect env vars present when the module was first imported.
        # Here we just verify that instantiation succeeds and the type is correct.
        settings = Settings()
        
        assert isinstance(settings.LOG_LEVEL, str)
        assert isinstance(settings.REDIS_PORT, int)
        assert isinstance(settings.REDIS_HOST, str)


# =============================================================================
# Dependency Injection Tests
# =============================================================================

class TestDependencies:
    """Test FastAPI dependency injection functions."""
    
    @pytest.mark.asyncio
    async def test_get_vyra_entity_success(self, mock_vyra_entity):
        """Test get_vyra_entity returns entity when container initialized."""
        from {{ module_name }}.{{ module_name }} import container_injection
        
        # Setup: Initialize container
        container_injection.set_entity(mock_vyra_entity)
        
        try:
            # Act
            entity = container_injection.get_entity()
            
            # Assert
            assert entity is not None
            assert entity == mock_vyra_entity
        finally:
            # Cleanup
            container_injection.reset()
    
    @pytest.mark.asyncio
    async def test_get_entity_not_initialized(self):
        """Test get_entity raises ContainerNotInitializedError when container not initialized."""
        from {{ module_name }}.{{ module_name }} import container_injection
        from {{ module_name }}.{{ module_name }}.container_injection import ContainerNotInitializedError
        
        # Ensure container is reset
        container_injection.reset()
        
        # Act & Assert
        with pytest.raises(ContainerNotInitializedError) as exc_info:
            container_injection.get_entity()

        assert "not initialized" in str(exc_info.value).lower()


# =============================================================================
# Component/Application Logic Tests
# =============================================================================

class TestApplicationComponent:
    """Test application component business logic."""
    
    def test_component_initialization(self, mock_vyra_entity):
        """Test Component initializes with correct dependencies."""
        mock_core_entity_module = MagicMock()
        mock_core_entity_module.VyraEntity = type("VyraEntity", (), {})
        sys.modules["vyra_base.core.entity"] = mock_core_entity_module

        from {{ module_name }}.{{ module_name }}.application.application import Component
        from {{ module_name }}.{{ module_name }}.taskmanager import TaskManager
        
        # Arrange
        mock_state_machine = MagicMock()
        taskmanager = TaskManager()
        
        # Act
        component = Component(
            unified_state_machine=mock_state_machine,
            entity=mock_vyra_entity,
            task_manager=taskmanager
        )
        
        # Assert
        assert component is not None
        assert component.entity == mock_vyra_entity
        # Add more assertions for your component's state


# =============================================================================
# Utility/Helper Function Tests
# =============================================================================

class TestUtilities:
    """Test utility and helper functions."""
    
    def test_module_name_dynamic_loading(self):
        """Test ASGI module imports and exposes application."""
        import {{ module_name }}.{{ module_name }}.backend_webserver.asgi as asgi_module
        
        assert hasattr(asgi_module, "application")


# =============================================================================
# Integration Points (Mocked)
# =============================================================================

class TestContainerInjection:
    """Test container injection setup and retrieval."""
    
    def test_container_set_and_get(self, mock_vyra_entity):
        """Test container injection stores and retrieves objects correctly."""
        from {{ module_name }}.{{ module_name }} import container_injection
        
        # Arrange & Act
        container_injection.set_entity(mock_vyra_entity)
        
        # Assert
        retrieved = container_injection.get_entity()
        assert retrieved == mock_vyra_entity
        
        # Cleanup
        container_injection.reset()
    
    def test_container_reset(self, mock_vyra_entity):
        """Test container injection reset clears all references."""
        from {{ module_name }}.{{ module_name }} import container_injection
        from {{ module_name }}.{{ module_name }}.container_injection import ContainerNotInitializedError
        
        # Arrange
        container_injection.set_entity(mock_vyra_entity)
        
        # Act
        container_injection.reset()
        
        # Assert
        with pytest.raises(ContainerNotInitializedError):
            container_injection.get_entity()


# =============================================================================
# Markers and Test Metadata
# =============================================================================

# Mark all tests in this file as unit tests
pytestmark = pytest.mark.unit
