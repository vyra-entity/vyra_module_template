# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

## [Unreleased]
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