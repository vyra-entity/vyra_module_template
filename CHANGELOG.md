# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

## [Unreleased]

### Fixed — backend_webserver imports and cyclonedds security (2026-03-18)

#### `src/{{ module_name }}/{{ module_name }}/backend_webserver/__init__.py`
- Simplified to only export `app` from `main_rest`. Removed incorrect v2_modulemanager-specific router imports (`repository_router`, `modules_router`, `hardware_router`) that don't exist in the template's `main_rest.py`.

#### `.module/requirements.txt`
- Added missing `python-json-logger` and `colorlog` packages required by the logging system.

#### `config/cyclonedds.xml`
- Removed or fixed Security section that caused DDS startup failures in non-SROS2 environments.

#### `vyra_entrypoint.sh`
- **`FORCE_UPDATE` detection bug** — The checksum check previously only compared 3 hardcoded files (`vyra_core.meta.json`, `vyra_com.meta.json`, `vyra_security.meta.json`). Newly added `*.meta.json` files and new `.srv`/`.msg`/`.action` files were never detected, so NFS was never updated after `docker service update`.
- **Fix**: Replaced hardcoded 3-file check with a comprehensive check:
  1. Compares config JSON file count between src tree and NFS (detects new `*.meta.json`)
  2. Compares `.srv`/`.msg`/`.action` file count between src tree and NFS (detects new interface files)
  3. Checks checksums of ALL config JSON files (detects modified files)
  - Uses the `src/` tree (not the install tree) as source of truth for counts, so new files are detected even before a colcon rebuild.
- **Config push from src tree** — After deploying config from the install tree, newly added JSON config files from the src tree (not yet present in install) are now also merged into NFS `config/`.

#### `tools/hot_reload.py`
- **Startup sync check** — Added `_check_initial_sync()` method: at container startup, hot_reload now compares the src interface tree with the compiled install tree. If they differ (e.g. a `.srv` was added before the container started), a rebuild is scheduled after 10 s. Covers the case where `on_created` events are missed because files existed before the watchdog started.

### Fixed — hot_reload supervisord detection (2026-03-17)

- **`tools/hot_reload.py`** — Fixed race condition where hot_reload was launched before supervisord finished starting, causing `use_supervisord = False` to be cached for the entire session. Added retry logic (up to 60 s) at init time, auto-detection of supervisord config path, and per-restart re-checks.


### Changed — Plugin Cache RAM Fix & Docs Updated
- **`PluginGateway._manifest_cache`** *(new)* — Replaced file-based cache (`plugin/cache/plugin_manifest.json`) with in-memory `dict`. Removed `import json`, `from pathlib import Path`, `_CACHE_DIR` module constant, and `_CACHE_DIR.mkdir()` call.
- **`docs/plugin/PLUGIN_INTEGRATION.md`** — Rewritten: replaces outdated `PluginClient`/`get_ui_manifest` references with current `PluginGateway`/`resolve_plugins` API.
- **`docs/backend/PLUGIN_BRIDGE.md`** *(new)* — Event-Bridge architecture documentation (BaseEventBridge, FeedStreamer, PluginBridge, WebSocket endpoints).
- **`docs/architecture/PLUGIN_ARCHITECTURE.md`** *(new)* — Consumer-module view of plugin architecture with `{{ module_name }}` scope examples.

### Added — Bidirectional Plugin Gateway Architecture
- **`plugin/plugin_gateway.py`** *(new)* — Replaces `plugin_client.py`. `PluginGateway` sets up two Zenoh clients: `_resolve_client` → `resolve_plugins`@v2_modulemanager and `_ui_call_client` → `ui_function_call`@v2_modulemanager. Uses `{{ module_name }}` Copier placeholder for module identity. Methods: `resolve_plugins()`, `get_manifest()`, `call_plugin()`, `teardown()`.
- **`container_injection.py`**: `plugin_gateway` provider added — `set_plugin_gateway`, `get_plugin_gateway`, `provide_plugin_gateway` (replaces `plugin_client` variants).
- **`main.py`**: `PluginGateway` instantiation and `await setup(entity)` added during startup; registered via `container_injection.set_plugin_gateway()`.

### Changed — Bidirectional Plugin Gateway Architecture
- **`plugin/plugin_client.py`** deleted — replaced by `plugin/plugin_gateway.py`.
- **`plugin/__init__.py`**: exports `PluginGateway` instead of `PluginClient`.
- **`plugin/registry.py`** shim updated: `PluginRegistry = PluginGateway` (was `PluginClient`).
- **`/plugin/ui-manifest` → `/plugin/resolve_plugins`** in backend router and frontend `plugin.api.js`; `module_name` / `module_id` query params added.
- **`backend_webserver/plugin/router.py`**: `provide_plugin_client` → `provide_plugin_gateway`; handler calls `gateway.resolve_plugins()` / `gateway.call_plugin()`.

### Added (Phase 7 — Plugin-Bridge & BaseEventBridge)
- **`backend_webserver/services/base_event_bridge.py`**: Abstrakte ABC-Basisklasse für alle Event-Bridge-Implementierungen.
- **`backend_webserver/services/feed_streamer.py`**: Ersetzt altes `feed_manager.py`. Erweitert `BaseEventBridge`. `publish_feed(FeedMessage)` sync-API für Application-Caller.
- **`backend_webserver/services/plugin_bridge.py`**: Bidirektionale Singleton-Bridge für Plugin-Kommunikation via Zenoh-Kanäle. `publish`, `receive`, `register_handler`, `subscribe`, `unsubscribe`.
- **`backend_webserver/websocket/service.py`**: `ConnectionManager` Singleton mit `active_connections`, `operation_subscriptions`, `notify_operation_update()`, `operation_monitor()`.
- **`backend_webserver/plugin/__init__.py`**: Plugin-Router-Package.
- **`backend_webserver/plugin/router.py`**: `GET /ui-manifest` + `POST /{plugin_id}/call` — Zenoh-Proxy via `PluginClient`.
- **`plugin/plugin_client.py`**: Extended with `call_plugin(plugin_id, function_name, data)` method.

### Changed (Phase 7)
- **`backend_webserver/services/feed_manager.py`**: Gelöscht — replaced by `feed_streamer.py`.
- **`backend_webserver/websocket/router.py`**: Komplett überarbeitet. Entfernt inline `ConnectionManager`. Fixe Logging-Imports (`v2_modulemanager` referenz entfernt). `FeedManager` → `FeedStreamer`. Fügt `/plugin/{plugin_id}/{channel}` WebSocket-Endpoint hinzu.
- **`container_injection.py`**: `plugin_client` und `plugin_bridge` Provider hinzugefügt. `reset()` aktualisiert. `set/get/provide_plugin_client`, `set/get/provide_plugin_bridge` Funktionen hinzugefügt.
- **`backend_webserver/main_rest.py`**: Gebrochene Imports gefixt (`operation_monitor` jetzt aus `websocket/service`, `plugin_router` aus `plugin/router`). `plugin_manager.shutdown()` entfernt. `PluginBridge.get_instance()` + `set_plugin_bridge()` im Startup-Lifespan.

### Fixed
- **`Dockerfile`** — `setup_interfaces.py` verschoben: Aufruf wurde von vor `rm -rf /workspace/install /workspace/build` auf nach dahinter verlegt, direkt vor `colcon build`. Damit läuft `setup_interfaces.py` immer mit dem zuletzt installierten `vyra_base`-Wheel und garantiert, dass VBASE-Basistypen (`VBASEVolatileList`, `VBASEKeyValue`, etc.) in `src/${MODULE_NAME}_interfaces/msg/` vorhanden sind bevor `colcon build` die Interfaces kompiliert. Verhindert `ImportError: cannot import name 'VBASEVolatileList'` nach Wheel-Updates.

### Changed (Plugin-System Generalisierung)
- **`plugin/registry.py` komplett überarbeitet**: Alte importlib-basierte Python-Plugin-Registry (`PluginBase`, `PLUGIN_CONFIG`, `load_plugins()`) durch neue WASM-Plugin-UI-Registry ersetzt. `PluginRegistry` fragt jetzt das UI-Manifest bei `v2_modulemanager` via Zenoh-Client an (`get_plugin_ui_manifest`-Service). Kein statischer Plugin-Import mehr.

### Added
- **`docs/backend/PLUGIN_INTEGRATION.md`**: Neue Dokumentation für die Plugin-UI-Integration in Modulen — erklärt die Rollen, `PluginRegistry.setup()`, Frontend `import()`, HostFunctions-Template.

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