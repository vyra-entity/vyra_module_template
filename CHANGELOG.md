# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

## [Unreleased]

### Added (2026-03-05)
- **Frontend Sidebar (Basis-Struktur)**: Portierbare, kollabierbare Sidebar-Basisstruktur identisch zu `v2_modulemanager`, jedoch in plain JS (kein TypeScript, kein PrimeVue). Nur Abhängigkeiten: Vue 3, Pinia, Vue Router, PrimeIcons CSS.
- **`src/store/sidebar.js`**: Plain-JS Pinia-Store mit `groupedItems`, `registerItem`, `unregisterItem`, `updateBadge`.
- **`src/components/layout/SidebarNavItem.vue`**: Einzelnes Nav-Element (plain JS).
- **`src/components/layout/SidebarNavGroup.vue`**: Gruppen-Header (plain JS).
- **`src/components/layout/VyraSidebar.vue`**: Haupt-Sidebar mit Props `title` + `backendStatus`, Slots `#brand` und `#bottom` für Modul-spezifische Anpassungen. Responsive Drawer bei `≤480px`.
- **`src/composables/useSidebarNavigation.js`**: Plugin-API-Composable für dynamische Sidebar-Einträge.

### Changed (2026-03-05)
- **`src/App.vue`**: Layout von `flex-column` (Navbar oben) auf `flex-row` (Sidebar links + Main rechts) umgebaut. Slim-Topbar zeigt Seitentitel aus Route-Meta. Backend-Status wird per `axios.get('/api/status')` ermittelt und an Sidebar weitergereicht.
- **`src/main.js`**: `primeicons/primeicons.css` importiert (Voraussetzung für `pi pi-*` Icon-Klassen in der Sidebar).

- `user/internal_usermanager.py`, `user/tb_users.py`, `user/usermanager.py` als lokaler Fallback-Usermanager aus `v2_modulemanager` übernommen. Kein Cross-Module-Token-Generating — reine lokale Benutzerverwaltung.
- `user/__init__.py` erweitert: exportiert jetzt `InternalUserManager`, `UserManager`, `usermanager_runner`, `User`, `UserRole`, `UserLevel` zusätzlich zu `UserManagerClient`.

### Changed (2026-03-04)
- Lokalen Usermanager entfernt (`user/usermanager.py`, `internal_usermanager.py`, `tb_users.py`).
- `user/usermanager_client.py` hinzugefügt: externer Usermanager-Client zur Token-Beschaffung für Zugriffe mit erhöhtem Security-Level.
- `main.py` von lokalem Usermanager auf `UserManagerClient` migriert und `usermanager_client_runner` als TaskManager-Task integriert.
- `user/__init__.py` auf Client-Exporte bereinigt.

### Documentation (2026-03-04)
- Dokumentation in Querschnittsstruktur übernommen: `docs/architecture`, `docs/api`, `docs/operations`, `docs/migrations`.
- `docs/README.md` auf Template-Variante mit Platzhaltern (`{{ module_name }}`, `{{ module_display_name }}`) und strukturierter Navigation umgestellt.
- Root-Policy umgesetzt: Im `docs/`-Root liegen nur noch `README.md` und `INDEX.md`.
- Vorherige Root-Dokumente in passende Unterordner verschoben; nicht eindeutig zuordenbare Datei nach `docs/deprecated/` verlagert.

### Added (2026-03-04)
- Beispiele über Feeder hinaus erweitert:
  - `examples/state/01_state_transition_flow.py`
  - `examples/interfaces/01_remote_service_pattern.py`
  - `examples/helper/01_file_io_config_pattern.py`
  - `examples/security/01_access_policy_pattern.py`
- `examples/README.md` um die neuen Kategorien ergänzt.

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