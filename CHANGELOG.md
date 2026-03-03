# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

## [Unreleased]

### Changed (2026-03-03)
- Feeder-Beispiele erweitert auf neue Tracking-Funktionen:
  - `execution_point` in bestehenden Condition-Beispielen ergänzt,
  - neue isolierte Beispiele `06` bis `09` für StateFeeder-ohne-Wrapper, News/Custom-Monitor-Wrapper und BEFORE/DURING/AFTER/ALWAYS-Regeln,
  - `examples/README.md` um Rule-/Tag-Filter und Runtime-Context-Hinweise erweitert.
- `examples/feeders/07_news_monitor_wrapper.py` und `08_custom_monitor_wrapper.py` korrigiert: Monitoring wrappt jetzt direkt echte `Component`-Methoden statt innerer Rückgabe-Funktionen.

### Added (2026-03-03)
- Leeres State-Callback-Template im `StateManager` via `UnifiedStateMachine.on_any_change(...)` ergänzt.
- Beispielhafte Feeder-Tracker-Anbindung im Component-Gerüst:
  - bool-only News-Condition-Registrierung
  - optionale Condition-Auswertung im Heartbeat-Kontext
- Neuer Top-Level Ordner `examples/` mit strukturierten Einzelfall-Beispielen für Feeder und Decorator-Nutzung.

### Fixed (2026-03-03)
- `pytest.ini`: Doppelten `addopts` Block entfernt, damit `pytest` wieder korrekt startet.

### Changed (2026-03-03)
- `Component` übergibt für `OperationalStateMachine` konsistent `unified_state_machine.fsm`.

### Added (2026-02-16)
- **Professional Structured Logging**: Complete migration from standard Python logging to `structlog`
  - New `logging_config.py` module with centralized configuration
  - `@log_call` decorator for automatic function call logging (entry, exit, duration, exceptions)
  - Unified `config/core_logging.json` configuration (replaces `ros2_logging.json` and `uvicorn_logging.json`)
  - JSON and colored console output formats
  - Automatic log rotation (10MB max, 10 backups)
  - Environment-based configuration: `LOG_LEVEL`, `LOG_FORMAT`, `VYRA_SLIM`, `VYRA_DEV_MODE`
  - Enhanced error context with structured fields
  - All log files unified in `/workspace/log/core/` directory

### Changed (2026-02-16)
- Updated `main.py` with structured logging throughout:
  - `application_runner()`, `setup_statusmanager()`, `ros_spinner_runner()`, `web_backend_runner()`, `initialize_module()`, `runner()`, `main()` all use `@log_call` decorator
  - Removed manual logging boilerplate
  - Enhanced signal handlers with structured context
- Updated `pyproject.toml` dependencies: added `structlog ^24.1.0`, `python-json-logger ^2.0.7`, `colorlog ^6.8.0`, `uvicorn ^0.30.0`, `fastapi ^0.115.0`

### Removed (2026-02-16)
- `config/ros2_logging.json` and `config/uvicorn_logging.json` (replaced by `config/core_logging.json`)
- Old logging setup function and manual logging calls
- Emoji-based log messages (replaced with structured fields)