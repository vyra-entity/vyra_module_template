# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

## [Unreleased]

### Added — Dark theme, settings store, plugins settings page (2026-01-27)

- **`src/store/settings.ts`** — New Pinia store `useSettingsStore` with theme (light/dark/auto), language, notifications toggle. Persists to localStorage. Applies `html.dark-mode` class to document root.
- **`src/features/settings/pages/PluginsPage.vue`** — New settings page listing all active plugins with UI-slot overview and toggle functionality.
- **`src/features/settings/pages/AppearancePage.vue`** — Rewritten with theme `SelectButton` (light/dark/auto) and language `Dropdown` using `useSettingsStore`.
- **`src/store/sidebar.ts`** — Added `settings-plugins` entry (priority 60). Settings route changed from `settings` to `settings-general`.
- **`src/router/index.ts`** — Added `settings-plugins` route as child of `/settings`.
- **`src/style.css`** — Added `html.dark-mode {}` CSS variable overrides for dark mode (surface, text, scrollbar, sidebar variables).
- **`src/App.vue`** — Added `useSettingsStore` + `apiClient` imports. Bell button now conditionally rendered via `bellVisible` (based on `settings.notifications`).

### Added — VYRA_SLIM mode: skip ROS2 build and runtime ROS2 setup

- **`Dockerfile`** — Added `ARG VYRA_SLIM=false`. All ROS2 build steps (rm install/, protobuf install, `setup_interfaces.py`, `colcon build`, `install_backup`, interface staging) are now wrapped in a single `if SLIM; then skip; else full-build; fi` block. SLIM mode creates empty stub dirs so the runtime `COPY --from=builder` instructions still succeed.
- **`vyra_entrypoint.sh`** — All ROS2-specific startup sections are now guarded with `if [ "${VYRA_SLIM:-false}" != "true" ]`: ROS2 sourcing (`source /opt/ros/kilted/setup.bash`), `install/` directory restoration + `source install/setup.bash` (critical — would crash without a colcon build), `setup_interfaces.py` call, NFS Interface Management, SROS2 Setup + Final Environment. In SLIM mode the keystore directory is still created as a safe fallback.

### Changed — SDP redesigned as floating right-edge icon tabs (2026-04-01)

- **`src/components/layout/SideDockPopup.vue`** — Complete rewrite. Floating icon tabs on the right edge; hover shows label, click opens popup panel, pin keeps it open.
- **`src/store/sideDockPopup.ts`** — Added `closeAllUnpinned()` and `closePocketForcefully(id)`. `closePanel()` now delegates to `closeAllUnpinned()`.
- **`src/store/uiSettings.ts`** — New Pinia store `useUiSettingsStore` with `sideDockPocketEnabled` (localStorage-persisted, default `true`).
- **`src/features/settings/SettingsView.vue`** — Side-Dock Widgets toggle card replaces the placeholder.
- **`src/App.vue`** — `SideDockPopup` conditionally rendered via `uiSettingsStore.sideDockPocketEnabled`.

### Fixed — Plugin bare specifier resolution for "vue" (2026-04-01)

- **`frontend/index.html`** — Added `<script type="importmap">` mapping `"vue"` → `/{{ module_name }}/vendor/vue.esm-browser.prod.js`.
- **`frontend/package.json`** — Added `postinstall` script that copies `vue.esm-browser.prod.js` to `public/vendor/` after `npm install`.

### Fixed — vite.config.ts: DNS-Fehler ENOTFOUND im Dev-Proxy behoben (2026-03-31)
- **`frontend/vite.config.ts`**: Proxy-Target von `https://{{ module_name }}:8443` auf `https://localhost:8443` geändert.
  Module mit Hash-Suffix im Swarm-Servicenamen (z.B. `testv8_<hash>`) sind per kurzem Modulnamen
  nicht auflösbar. Da Vite und Backend immer im gleichen Container laufen, ist `localhost` die
  universell korrekte Lösung für alle aus diesem Template erzeugten Module.

### Changed — plugin_gateway: service-based NFS path lookup (2026-04-01)

- **`plugin/plugin_gateway.py`**: Removed direct `PluginPool` DB import from `_lookup_nfs_path`. NFS path is now resolved by calling the `plugin/get_nfs_path` Zenoh service exposed by `v2_modulemanager`.
- Added `_get_nfs_path_client` field and expanded `_setup_resolve_client()` to create both `resolve_plugins` and `get_nfs_path` clients.
- Added `_read_modulemanager_id()` static method that reads `labels.modulemanager.module_id` from `/workspace/.module/module_params.yaml` to identify the correct `v2_modulemanager` instance to route calls to.
- Added teardown for `_get_nfs_path_client`.

### Fixed — copier.yml: Jinja2 TemplateSyntaxError in root README.md (2026-03-30)

- **`copier.yml`**: Added `README.md` to `_exclude`. The root `README.md` is template
  documentation and must not be processed as a Jinja2 template (it contained escaped
  pipe characters inside Jinja2 expression delimiters, causing `TemplateSyntaxError:
  unexpected char '\'`).
- **`README.md`**: Replaced escaped pipe characters with Jinja2 raw-block wrapping in
  the derived variables table to produce valid Jinja2 even if the file is processed
  directly.

### Changed — copier template wraps content in `{{ module_name }}/` subdir (2026-03-30)

- All template files now live inside a `{{ module_name }}/` directory in the template
  repo. Copier renders this directory name to the actual module name at copy time.
- Users can now specify only the parent destination folder instead of a dummy subdir:
  ```
  copier copy ~/VYRA/vyra_module_template module-storages/ --trust --vcs-ref HEAD
  ```
  `post_copier_setup.sh` continues to work unchanged — it renames
  `module-storages/<module_name>/` → `module-storages/<module_name>_<uuid>/<version>/`.
- Updated `_answers_file`, `_exclude`, and `_tasks` in `copier.yml` to reflect new paths.
- Added `log` to `_exclude` so the empty runtime `log/` dir is not created at the
  destination root.

### Changed — decouple ROS2 imports, SLIM-mode path resolution (2026-03-27)

- **`_base_.py`**: Removed all `{{ module_name }}_interfaces.*`, `std_msgs.msg` imports. Added `VYRA_SLIM` guard for `ament_index_python`. Added `_get_package_dir()` / `_get_workspace_root()` helpers. `StateEntry`, `NewsEntry`, `ErrorEntry` no longer pass `_type`. `transient_base_types` and `parameter_types` set to `{}`.
- **`interface.py`**: `ament_index_python` import conditional on `VYRA_SLIM`. `_load_metadata()` uses Python source tree in SLIM mode.

### Added — publish_to_repo.sh: run update_index.sh after publishing (2026-03-25)

- After `sync_from_modules.py` completes, `tools/publish_to_repo.sh` now automatically
  calls `local_repository/tools/update_index.sh` to rebuild `index.json` with the newly
  published module entry.

### Fixed — copier uses stale v1.3.0 tag instead of local HEAD (2026-03-25)

- Removed `_vcs_ref: HEAD` from `copier.yml` — this key is NOT read by copier for
  template resolution and was dead/misleading configuration.
- Deleted local-only tags `v1.1.0`, `v1.2.0`, `v1.3.0` which pointed to old commits
  (e.g. `v1.3.0` → commit with `module_version: default: "0.0.0"`). These tags were
  never pushed to origin and caused `get_latest_tag()` to always pick the stale commit.
- Created tag `v1.4.0` at the current HEAD so copier now resolves to the correct
  template with `module_version: default: "1.0.0"`.
- Updated comment in `copier.yml` to explain the actual copier behaviour: copier picks
  the HIGHEST PEP 440 git tag when no `--vcs-ref` is given. Use
  `copier copy <template> <dest> --trust --vcs-ref HEAD` to force local HEAD.

### Fixed — copier.yml: clarified _vcs_ref: HEAD behavior and gitignore caveat (2026-03-25)

- `copier.yml`: corrected the `_vcs_ref: HEAD` comment. The setting makes copier use
  git HEAD (committed state) as the template source — NOT the working tree.
  Added a note explaining that `copier update` fails with exit code 128 when the
  destination module lives in a gitignored path (e.g. `module-storages/`). Fix:
  `git init && git add -A && git commit -m init` in the module dir first, then
  `copier update --trust --defaults --vcs-ref HEAD`. Alternatively use
  `copier copy --trust --force` to regenerate all files from HEAD.

### Changed — module-storages path convention (2026-03-24)

- `copier.yml` `_tasks`: replaced `cd ../..` with a dynamic workspace-root
  discovery that walks up the directory tree searching for `docker-compose.yml`.
  This makes the task work from any nesting depth, e.g.
  `module-storages/<version>/<module>/` as well as `modules/<module>/`.
- `tools/publish_to_repo.sh`: replaced the hardcoded `../../local_repository`
  default with the same upward workspace-root search so the script resolves
  correctly from any path depth.
- `VOS2_WORKSPACE/tools/quick_rebuild_module.sh`: extended module search to
  also cover `module-storages/<version>/<module>/` (depth 2 under
  `module-storages/`) in addition to the legacy `modules/` directory.
- `docs/development/COPIER_QUICKUSE.md`: updated all example `copier copy`
  destination paths to use `module-storages/<version>/` instead of `modules/`.

### Fixed — setup_interfaces.py workspace detection (2026-03-19)

- `tools/setup_interfaces.py` `main()`: replaced the name-based heuristic
  (`script_dir.name.startswith("v2_") or == "vyra_module_template"`) with a
  directory-content check (`src/` or `.module/` present). Any module directory
  is now correctly detected as a local-development workspace, so CMakeLists.txt
  can be generated locally without requiring the directory to start with `v2_`.

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