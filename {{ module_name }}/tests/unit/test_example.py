"""
Example unit tests for {module_name} module.

These tests demonstrate the testing structure and patterns.
Run with: pytest -m unit tests/unit/test_example.py
"""

import pytest
from unittest.mock import Mock, MagicMock, patch
import os


# =============================================================================
# Backend Configuration Tests
# =============================================================================

class TestBackendConfig:
    """Test backend_webserver configuration."""
    
    def test_settings_default_values(self):
        """Test Settings class loads default values correctly."""
        from {{ module_name }}.backend_webserver.core.config import Settings
        
        with patch.dict(os.environ, {"MODULE_NAME": "test_module"}):
            settings = Settings()
            
            assert settings.module_name == "test_module"
            assert settings.api_prefix == "/api/{{ module_name }}"
            assert settings.debug is False
            assert settings.log_level == "INFO"
    
    def test_settings_custom_values(self):
        """Test Settings class respects environment variables."""
        from {{ module_name }}.backend_webserver.core.config import Settings
        
        env_vars = {
            "MODULE_NAME": "custom_module",
            "LOG_LEVEL": "DEBUG",
        }
        
        with patch.dict(os.environ, env_vars):
            settings = Settings()
            
            assert settings.module_name == "custom_module"
            assert settings.log_level == "DEBUG"


# =============================================================================
# Dependency Injection Tests
# =============================================================================

class TestDependencies:
    """Test FastAPI dependency injection functions."""
    
    @pytest.mark.asyncio
    async def test_get_vyra_entity_success(self, mock_vyra_entity):
        """Test get_vyra_entity returns entity when container initialized."""
        from {{ module_name }} import container_injection
        from {{ module_name }}.backend_webserver.core.dependencies import get_vyra_entity
        
        # Setup: Initialize container
        container_injection.set_vyra_entity(mock_vyra_entity)
        
        try:
            # Act
            entity = get_vyra_entity()
            
            # Assert
            assert entity is not None
            assert entity == mock_vyra_entity
        finally:
            # Cleanup
            container_injection.reset()
    
    @pytest.mark.asyncio
    async def test_get_vyra_entity_not_initialized(self):
        """Test get_vyra_entity raises HTTPException when container not initialized."""
        from {{ module_name }} import container_injection
        from {{ module_name }}.backend_webserver.core.dependencies import get_vyra_entity
        from fastapi import HTTPException
        
        # Ensure container is reset
        container_injection.reset()
        
        # Act & Assert
        with pytest.raises(HTTPException) as exc_info:
            get_vyra_entity()
        
        assert exc_info.value.status_code == 503
        assert "not initialized" in str(exc_info.value.detail).lower()


# =============================================================================
# Component/Application Logic Tests
# =============================================================================

class TestApplicationComponent:
    """Test application component business logic."""
    
    def test_component_initialization(self, mock_vyra_entity):
        """Test Component initializes with correct dependencies."""
        from {{ module_name }}.application.application import Component
        from vyra_base.taskmanager.taskmanager import TaskManager
        
        # Arrange
        mock_state_machine = MagicMock()
        taskmanager = TaskManager()
        
        # Act
        component = Component(
            unified_state_machine=mock_state_machine,
            entity=mock_vyra_entity,
            taskmanager=taskmanager
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
        """Test that module name is loaded dynamically from environment."""
        from {{ module_name }}.backend_webserver.asgi import get_module_name
        
        # Test with environment variable
        with patch.dict(os.environ, {"MODULE_NAME": "test_{{ module_name }}"}):
            module_name = get_module_name()
            assert module_name == "test_{{ module_name }}"
        
        # Test with default fallback
        with patch.dict(os.environ, {}, clear=True):
            module_name = get_module_name()
            assert module_name == "{{ module_name }}"


# =============================================================================
# Integration Points (Mocked)
# =============================================================================

class TestContainerInjection:
    """Test container injection setup and retrieval."""
    
    def test_container_set_and_get(self, mock_vyra_entity):
        """Test container injection stores and retrieves objects correctly."""
        from {{ module_name }} import container_injection
        
        # Arrange & Act
        container_injection.set_vyra_entity(mock_vyra_entity)
        
        # Assert
        retrieved = container_injection.provide_vyra_entity()
        assert retrieved == mock_vyra_entity
        
        # Cleanup
        container_injection.reset()
    
    def test_container_reset(self, mock_vyra_entity):
        """Test container injection reset clears all references."""
        from {{ module_name }} import container_injection
        
        # Arrange
        container_injection.set_vyra_entity(mock_vyra_entity)
        
        # Act
        container_injection.reset()
        
        # Assert
        with pytest.raises(Exception):  # ContainerNotInitializedError
            container_injection.provide_vyra_entity()


# =============================================================================
# Markers and Test Metadata
# =============================================================================

# Mark all tests in this file as unit tests
pytestmark = pytest.mark.unit
