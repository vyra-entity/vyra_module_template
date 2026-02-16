# Structured Logging mit Structlog

## Überblick

Das v2_modulemanager Modul verwendet professionelles strukturiertes Logging mittels **structlog**. Dies ermöglicht:

- 📊 **Strukturierte Logs** mit kontextreichen JSON-Ausgaben
- 🎨 **Colored Console Output** für Development
- 📝 **Professionelles Error Tracking** mit vollständigem Context
- 🔄 **Log Rotation** für Production
- 🔍 **Einfaches Debugging** durch konsistente Logging-Patterns

## Konfiguration

### Environment Variables

```bash
# Log Level (DEBUG, INFO, WARNING, ERROR, CRITICAL)
LOG_LEVEL=INFO

# Log Format (colored für Dev, json für Production)
LOG_FORMAT=colored

# VYRA Modus (slim = nur Python, full = mit ROS2)
VYRA_SLIM=false

# Development Mode (aktiviert mehr Debug-Infos)
VYRA_DEV_MODE=true
```

### Konfigurationsdatei

Die zentrale Logging-Konfiguration befindet sich in:
```
config/core_logging.json
```

Diese Datei definiert:
- Handler (Console, File mit Rotation)
- Formatter (JSON, Colored, Standard)
- Logger für verschiedene Komponenten
- Log Rotation Settings

## Verwendung

### Basic Logging

```python
from v2_modulemanager.v2_modulemanager.logging_config import get_logger

logger = get_logger(__name__)

# Einfaches Logging
logger.info("user_logged_in", user_id=123, username="admin")
logger.error("connection_failed", host="redis", port=6379, reason="timeout")
logger.debug("processing_item", item_id="abc123", step=3, total_steps=10)
```

### Function Call Logging

Der `@log_call` Decorator automatisiert das Logging von Funktionsaufrufen, Ergebnissen und Exceptions:

```python
from v2_modulemanager.v2_modulemanager.logging_config import log_call, get_logger

logger = get_logger(__name__)

@log_call
async def process_module(module_name: str, config: dict):
    """Function with automatic logging."""
    # processing...
    result = await do_something()
    return result

# Logs automatisch:
# - function_called (DEBUG): function, module, arguments (simple types only)
# - function_completed (INFO): function, module, duration_ms, success=True
# - Bei Exception (ERROR): function, module, duration_ms, full traceback

@log_call(logger=custom_logger)
def synchronous_function(x: int):
    """Auch für sync Funktionen."""
    return x * 2
```

**Features**:
- ✅ Funktioniert mit async und sync Funktionen
- ✅ Logging von Argumenten (simple types wie str, int, float, bool)
- ✅ Automatische Zeitmessung (duration_ms)
- ✅ Exception Logging mit vollständigem Context
- ✅ Flexible Logger-Auswahl (optional parameter)

### Manual Function Logging

Für mehr Kontrolle können Sie auch manuell loggen:

```python
from v2_modulemanager.v2_modulemanager.logging_config import (
    get_logger, 
    log_function_call, 
    log_function_result
)

logger = get_logger(__name__)

async def process_module(module_name: str, config: dict):
    log_function_call(
        logger,
        function="process_module",
        module_name=module_name,
        config_keys=list(config.keys())
    )
    
    try:
        # processing...
        result = await do_something()
        
        log_function_result(
            logger,
            success=True,
            function="process_module",
            module_name=module_name,
            items_processed=len(result)
        )
        
        return result
    except Exception as e:
        log_function_result(
            logger,
            success=False,
            function="process_module",
            error=str(e)
        )
        raise
```

### Exception Logging

```python
from v2_modulemanager.v2_modulemanager.logging_config import (
    get_logger, 
    log_exception
)

logger = get_logger(__name__)

try:
    result = await dangerous_operation()
except ValueError as e:
    log_exception(
        logger,
        e,
        context={
            "operation": "dangerous_operation",
            "user_id": 123,
            "attempt": 3
        }
    )
    raise
```

## Log-Ausgaben

### Development (Colored Console)

```
2026-02-16 10:30:45 - INFO     - v2_modulemanager.main:initialize_module:245 - module_initialization_started
2026-02-16 10 :30:45 - DEBUG    - v2_modulemanager._base_:build_entity:123 - building_entity
2026-02-16 10:30:45 - INFO     - v2_modulemanager._base_:build_entity:145 - entity_created module=v2_modulemanager node_name=v2_modulemanager_node uuid=abc-123
```

### Production (JSON)

```json
{
  "timestamp": "2026-02-16T10:30:45.123456Z",
  "level": "info",
  "event": "module_initialization_started",
  "module": "v2_modulemanager",
  "mode": "full",
  "logger": "v2_modulemanager.main",
  "function": "initialize_module",
  "line": 245
}
```

## Log-Dateien

Logs werden gespeichert in:
```
/workspace/log/core/
├── application.log      # Alle Logs (rotiert bei 10MB, 10 Backups)
└── errors.log          # Nur ERROR und CRITICAL (rotiert bei 10MB, 10 Backups)
```

### Log Rotation

- **Max File Size**: 10 MB
- **Backup Count**: 10 Dateien
- **Encoding**: UTF-8
- **Format**: JSON (für einfaches Parsen)

## Best Practices

### 1. Kontextreiche Logs

❌ **Schlecht:**
```python
logger.info("Processing started")
logger.error(f"Error: {e}")
```

✅ **Gut:**
```python
logger.info(
    "processing_started",
    module_name=module.name,
    item_count=len(items),
    user_id=current_user.id
)

log_exception(
    logger,
    e,
    context={
        "operation": "process_batch",
        "module": module.name,
        "item_count": len(items)
    }
)
```

### 2. Konsistente Event-Namen

Verwende `snake_case` Event-Namen, die die Aktion beschreiben:
- ✅ `user_logged_in`, `module_initialized`, `connection_failed`
- ❌ `User Login`, `init`, `error`

### 3. Strukturierte Daten

Verwende Key-Value Pairs statt String-Interpolation:
- ✅ `logger.info("user_action", user_id=123, action="login")`
- ❌ `logger.info(f"User {user_id} performed {action}")`

### 4. Log Levels

- **DEBUG**: Detaillierte diagnostic Informationen
- **INFO**: Normale business events (Start, Stop, Success)
- **WARNING**: Unerwartete aber nicht kritische Situationen
- **ERROR**: Errors die behandelt werden können
- **CRITICAL**: Schwere Errors die zum Absturz führen

### 5. Sensitive Daten

Sensitive Daten (Passwords, Tokens, API Keys) werden automatisch zensiert:
```python
logger.info("auth_attempt", username="admin", password="secret123")
# Output: username=admin, password=***CENSORED***
```

## Debugging-Tipps

### 1. Erhöhe Log Level temporär

```bash
LOG_LEVEL=DEBUG python -m v2_modulemanager.v2_modulemanager.main
```

### 2. Filtered Logs ansehen

```bash
# Nur Errors
tail -f /workspace/log/core/errors.log

# Nur ein Modul
grep "v2_modulemanager.registry" /workspace/log/core/application.log

# JSON Pretty Print
tail -f /workspace/log/core/application.log | jq
```

### 3. Live Monitoring

```bash
# All logs mit Color
tail -f /workspace/log/core/application.log | ccze -A

# Errors in Echtzeit
watch -n 1 'tail -20 /workspace/log/core/errors.log'
```

## Migration von altem Logging

Das Migration-Skript hat automatisch alle Dateien von Standard-Logging zu Structlog migriert:

```bash
python3 tools/migrate_to_structlog.py --dry-run  # Preview
python3 tools/migrate_to_structlog.py            # Apply
```

### Manuelle Anpassungen

Nach der Migration sollten kritische Funktionen um zusätzlichen Context erweitert werden:

**Vorher:**
```python
logger.info("Module registered")
```

**Nachher:**
```python
logger.info(
    "module_registered",
    module_name=module.name,
    module_id=module.id,
    version=module.version,
    provider=module.provider
)
```

## Troubleshooting

### Problem: Keine Logs sichtbar

**Lösung:**
1. Prüfe LOG_LEVEL: `echo $LOG_LEVEL`
2. Prüfe Log-Verzeichnis: `ls -la /workspace/log/core/`
3. Prüfe Berechtigungen: `chmod -R 755 /workspace/log/`

### Problem: Logs nicht formatiert

**Lösung:**
1. Prüfe LOG_FORMAT: `echo $LOG_FORMAT`
2. Installiere colorlog: `pip install colorlog`
3. Prüfe Terminal-Unterstützung: `echo $TERM`

### Problem: Log Rotation funktioniert nicht

**Lösung:**
1. Prüfe Disk Space: `df -h /workspace/log`
2. Prüfe Permissions: `ls -la /workspace/log/core/`
3. Prüfe core_logging.json: maxBytes und backupCount

## Weiterführende Resourcen

- [Structlog Documentation](https://www.structlog.org/)
- [Python JSON Logger](https://github.com/madzak/python-json-logger)
- [Log Rotation Best Practices](https://docs.python.org/3/library/logging.handlers.html#rotatingfilehandler)

## Support

Bei Problemen oder Fragen:
1. Prüfe die Logs in `/workspace/log/core/`
2. Erhöhe das Log Level auf DEBUG
3. Kontaktiere das Development Team
