# Tests for {module_name}

Umfassende Test-Suite mit Unit-, Integration- und E2E-Tests.

## Struktur

```
tests/
├── conftest.py              # Shared fixtures und Konfiguration
├── unit/                    # Unit Tests (isoliert, schnell, keine ext. Dependencies)
│   ├── test_example.py      # Beispiel-Tests für Backend Webserver
│   └── __init__.py
├── integration/             # Integration Tests (Redis, ROS2, Database)
│   └── __init__.py
├── e2e/                     # End-to-End Tests (komplette Workflows)
│   └── __init__.py
└── test_data/               # Test-Daten und Fixtures
```

## Test-Kategorien (Markers)

Tests sind mit pytest markers kategorisiert:

- `@pytest.mark.unit` - Unit Tests (Standard, schnell)
- `@pytest.mark.integration` - Integration Tests (benötigt ext. Services)
- `@pytest.mark.e2e` - End-to-End Tests (vollständige Workflows)
- `@pytest.mark.ros2` - Tests die ROS2 Node Initialisierung benötigen
- `@pytest.mark.redis` - Tests die Redis Connection benötigen
- `@pytest.mark.api` - Tests für REST API Endpoints
- `@pytest.mark.slow` - Tests die > 1 Sekunde dauern
- `@pytest.mark.smoke` - Schnelle Smoke Tests für CI/CD

## Tests ausführen

### Alle Tests
```bash
pytest
```

### Nur Unit Tests (empfohlen für schnelles Feedback)
```bash
pytest -m unit
```

### Integration Tests
```bash
# Benötigt: Redis, ROS2 environment
pytest -m integration
```

### E2E Tests
```bash
# Benötigt: Vollständiges System (Backend, ROS2, Redis)
pytest -m e2e
```

### Spezifische Test-Datei
```bash
pytest tests/unit/test_example.py
pytest tests/unit/test_example.py::TestBackendConfig::test_settings_default_values
```

### Mit Coverage Report
```bash
pytest --cov=src --cov-report=html --cov-report=term-missing
```

### Tests überspringen
```bash
# Smoke Tests überspringen
pytest -m "not smoke"

# Langsame Tests überspringen
pytest -m "not slow"

# Integration & E2E überspringen (nur Unit)
pytest -m "unit"
```

## Fixtures (conftest.py)

Siehe `conftest.py` für verfügbare Fixtures:

- `test_config` - Test-Konfiguration (Ports, Credentials, Pfade)
- `mock_redis_client` - Mock Redis-Client für Unit Tests
- `mock_ros2_node` - Mock ROS2 Node für Unit Tests
- `mock_vyra_entity` - Mock VyraEntity für Unit Tests

## Test-Daten

Test-Daten werden in `test_data/` abgelegt und können via Fixture geladen werden:

```python
def test_with_data(test_data_path):
    data_file = test_data_path / "example.json"
    # ...
```

## Best Practices

1. **Unit Tests**: Schnell, isoliert, keine externe Dependencies
2. **Mock alles**: Redis, ROS2, File System - alles was extern ist
3. **Arrange-Act-Assert**: Klare Struktur in jedem Test
4. **Ein Assert pro Test**: Fokussierte Tests sind besser
5. **Aussagekräftige Namen**: `test_authentication_fails_with_invalid_password`
6. **Cleanup**: Verwende `try/finally` oder Fixtures mit Cleanup

## Beispiel: Neuer Unit Test

```python
import pytest
from unittest.mock import Mock, MagicMock, patch

@pytest.mark.unit
class TestMyFeature:
    """Test suite for MyFeature."""
    
    def test_feature_success(self, mock_vyra_entity):
        """Test MyFeature works correctly."""
        # Arrange
        feature = MyFeature(mock_vyra_entity)
        
        # Act
        result = feature.do_something()
        
        # Assert
        assert result is True
```

## Continuous Integration

Tests werden automatisch in CI/CD Pipeline ausgeführt:
- PR: Unit Tests + Smoke Tests
- Main Branch: Alle Tests inkl. Integration

## Troubleshooting

**Import Errors**: Stelle sicher, dass PYTHONPATH korrekt gesetzt ist:
```bash
export PYTHONPATH=/workspace/src:$PYTHONPATH
pytest
```

**ROS2 Tests schlagen fehl**: Prüfe ROS2-Umgebung:
```bash
source /opt/ros/kilted/setup.bash
pytest -m ros2
```

**Redis Tests schlagen fehl**: Stelle sicher Redis läuft:
```bash
redis-cli ping  # sollte PONG zurückgeben
```
