# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

## [Unreleased]

### Fixed — Plugin manifest resolve uses canonical module target names (2026-04-30)

- `frontend/src/store/plugins.ts`
  - Added normalization for hash-suffixed module instance names before calling `/plugin/resolve_plugins`.
  - Prevents missing slot plugins in generated modules when routes include instance suffixes.

### Changed — Gateway WASM runtime now supports manifest service_exports dispatch (2026-04-30)

- `src/{{ module_name }}/{{ module_name }}/plugin/gateway_wasm_runtime.py`
  - Synced module-agnostic runtime behavior from PM implementation.
  - Added manifest-driven `entry_points.backend.service_exports` loading.
  - Added service-export dispatch path (`_dispatch_service_export`) with async/sync service method support.
  - Runtime start now supports service-export-only plugins (without WASM exports).

### Fixed — Active plugins: newest version display and slot dedup (2026-04-29)

- `frontend/src/features/settings/pages/PluginsPage.vue`
  - Active plugin list now deduplicates logical slots and prefers the newest semver for plugin header version.
  - Prevents stale version display (for example `1.0.0` instead of installed `1.0.1`) and duplicate slot rows.

### Fixed — Settings save visibility + deduplicated active plugin slots (2026-04-29)

- `frontend/src/features/settings/pages/GeneralPage.vue`
  - "Speichern" for module permissions is now only shown when settings were changed.
- `frontend/src/features/settings/pages/PluginsPage.vue`
  - Active plugin assignments are deduplicated by `assignment_id`.
  - Slot labels are normalized to unique values to avoid duplicated entries (for example `side-dock-popup.header`).

### Added — Settings: Module permissions from module_params.yaml (2026-04-29)

- Added new settings backend router:
  - `GET /settings/permissions` to load permissions from `.module/module_params.yaml`
  - `PUT /settings/permissions` to persist changes (admin only)
- Registered settings router in `backend_webserver/main_rest.py`.
- Added `frontend/src/api/settings.api.ts` for permissions load/save.
- Extended `frontend/src/features/settings/pages/GeneralPage.vue` with a new permissions section and admin save action.
- Added unit tests in `tests/unit/test_settings_permissions_router.py`.

### Fixed — Generated modules no longer default to protected mode (2026-04-29)

- `/.module/module_params.yaml` now sets `permissions.protected: false` by default.
- This ensures newly generated modules expose normal lifecycle actions in Module Manager unless explicitly configured otherwise.

### Enhanced — Professional smartphone responsive frontend baseline for generated modules (2026-04-28)

- Improved responsive layout baseline for generated module frontend shell: dynamic viewport (`100dvh`), safe-area insets, larger touch targets, and `viewport-fit=cover` in `frontend/index.html`.
- Optimized `frontend/src/App.vue`, `frontend/src/components/layout/VyraSidebar.vue`, and `frontend/src/components/layout/VyraStatusbar.vue` for smartphone/tablet behavior (drawer sidebar up to 768px, better topbar spacing, compact mobile statusbar).
- Upgraded `frontend/src/features/home/HomeView.vue` summary tiles for narrow phone widths.

### Fixed — SSL certificate readability check prevents PermissionError (2026-04-28)

- **Root cause**: `webserver.key` is owned by `root` with `600` permissions; non-root process cannot read it. `os.path.exists()` returns `True` (file exists) but uvicorn then raises `PermissionError: [Errno 13] Permission denied` when loading the cert chain.
- **`src/{{ module_name }}/{{ module_name }}/main.py`** — `web_backend_runner()` now checks `os.access(cert_path, os.R_OK)` in addition to `os.path.exists()` before enabling SSL. Logs `uvicorn_ssl_permission_denied` (ERROR) when files exist but cannot be read, falls back to HTTP.
- **`src/{{ module_name }}/{{ module_name }}/backend_webserver/asgi.py`** — Same fix applied to the `__main__` dev-runner SSL check.
- **`config/uvicorn.py`** — Same fix applied; prints clear error and fix hint (`chmod 644`) when permission is denied.

### Fixed — Template UserManager auth resolves module name dynamically (2026-04-24)

- **`src/{{ module_name }}/{{ module_name }}/backend_webserver/auth/auth_service.py`**
  - `_validate_usermanager_credentials()` now resolves the UserManager module name from `check-usermanager` response instead of hardcoding `v2_usermanager`.
  - Added `_resolve_usermanager_name()` with safe fallback to `v2_usermanager`.
  - Added explicit 403 handling (`access_denied`) passthrough for UserManager module access restrictions.
- **`src/{{ module_name }}/{{ module_name }}/backend_webserver/auth/router.py`**
  - Added MM-consistent HTTP 403 response when UserManager denies module access.

### Changed — Metadata docs now use canonical blueprints key (2026-04-23)

- **`../README.md`** and **`.module/README.md`** now describe `module_blueprints` / `blueprints` instead of legacy `module_template` / `template` for generated module metadata.

### Fixed — Dev full-mode startup now bypasses stale ROS2 console wrappers (2026-04-23)

- **`tools/startup_ros2_core.sh`** — In `VYRA_DEV_MODE=true`, new modules now start core from `/workspace/src/<module>` via `python3 -m <module>.main` after ROS2 setup.
- This prevents stale `install/` entry-point wrappers from crashing freshly generated modules during partial rebuild cycles.

### Changed — Usermanager detector now reads canonical blueprints key (2026-04-23)

- **`src/{{ module_name }}/{{ module_name }}/user/usermanager_detector.py`** — Detection logic now uses `module["blueprints"]` instead of legacy `module["template"]`.

### Changed — AuthPage aligned with v2_dashboard improvements

- **`frontend/src/features/settings/pages/AuthPage.vue`** — Replaced static auth-mode info card with dynamic auth mode indicator showing local/UserManager availability. Added `userManagerAvailable` ref fetched via `authApi.checkUserManagerAvailable()` on mount. Widened auth mode card to `col-12 md:col-6`. Changed user management section condition from `v-if="isAdmin"` to `v-if="authStore.authMode === 'local' || isAdmin"`. Added `Tag` "Nur für Admin" marker and `:disabled="!isAdmin"` to create-user form fields. Added v-if/v-else empty state for user list. Added `v-else` UserManager-info card block. Expanded minified CSS to multi-line.
- **`frontend/src/store/sidebar.ts`** — Reordered settings sub-navigation: `settings-auth` (priority 70) now appears before `settings-plugins` (priority 60), matching v2_dashboard order.

### Added — "Lokale Benutzerverwaltung" section in AuthPage

- **`frontend/src/features/settings/pages/AuthPage.vue`** — Added full local user management card (visible for admin users) with create user form, user list DataTable, and delete confirmation. Added imports for DataTable, Column, Tag, InputText, Select, ConfirmDialog, and authApi.
- **`frontend/src/api/auth.api.ts`** — Added `LocalUser` interface and `listLocalUsers()`, `createLocalUser()`, `deleteLocalUser()` API methods.

### Fixed — Password change HTTP 500 error

- **`user/internal_usermanager.py`** — Fixed reversed arguments in `user_manipulator.update()` call: data dict is now first arg, filters dict second (matching `DbManipulator.update(data, filters)` signature).

### Changed — AuthPage: auth delegation disclaimer

- **`frontend/src/features/settings/pages/AuthPage.vue`** — Added info message clarifying that this module delegates authentication to v2_usermanager.

### Fixed — Sidebar plugin icon

- **`frontend/src/store/sidebar.ts`** — Plugin icon changed from `pi-puzzle` to `pi-box`.

### Added — 401 session expiry interceptor

- **`frontend/src/api/http.ts`** — Added response interceptor: on 401 (outside /auth/) redirects to login.

### Fixed — App.vue layout and statusbar

- **`frontend/src/App.vue`** — `.vyra-app` uses `height: 100vh; overflow: hidden`; footer block removed.
- **`frontend/src/components/layout/VyraStatusbar.vue`** — Added copyright span.

### Fixed — Dark theme only partially applied (2026-04-16)

- **`frontend/src/assets/styles.css`** — Added `html.dark-mode` CSS block with dark mode variables. Fixed hardcoded `body { background: #f5f7fa }` → `var(--surface-ground, #f5f7fa)`.

### Fixed — Missing Toast component for plugin notifications (2026-04-16)

- **`frontend/src/App.vue`** — Added `<Toast />` component and `import Toast from 'primevue/toast'`. Without this, `pluginApi.events.notify()` calls (e.g., sdp-system-info "Test Notify") silently failed.

### Added — Sidebar settings tooltips when collapsed (2026-04-16)

- **`frontend/src/components/layout/VyraSidebar.vue`** — Added `v-tooltip.right` on settings navigation items and "Zurück" button, shown only when sidebar is collapsed.

### Refactored — auth.api.ts aligned with v2_usermanager (2026-01-25)

- **`frontend/src/api/auth.api.ts`** — `UserInfo` interface updated to match backend response (`user_id`, `role`, `level`, `token`, `module_id`). `listUsers()`/`createUser()` removed (moved to `admin.api.ts`).
- **`frontend/src/api/admin.api.ts`** — New file: extracted `AdminApi` class with `listUsers()` and `createUser()` (typed `LocalUser` interface).
- **`frontend/src/store/auth.ts`** — `roles` computed now derives from `user.role` (singular string → array).

### Refactored — Auth router, API and store improvements (2026-01-25)

- **`backend_webserver/auth/router.py`** — Added `_extract_token()` helper + `get_current_user` FastAPI dependency. Eliminated duplicated token-extraction logic. `ChangePasswordRequest` no longer includes `username` (derived from session token via dependency). HTTP 503 (was 500) for uninitialized service. `secure=True` on session cookie.
- **`backend_webserver/auth/auth_service.py`** — Replaced stub `_validate_usermanager_credentials` with full HTTP delegation to `v2_usermanager` (POST login + GET verify).
- **`frontend/src/api/auth.api.ts`** — `changePassword(oldPassword, newPassword)`: removed `username` parameter.
- **`frontend/src/store/auth.ts`** — Updated `changePassword` call (no `username` arg). Added `roles`, `isAdmin`, `userId` computed properties.

### Refactored — Dynamic module name in frontend (2026-01-25)

- **`frontend/src/features/settings/pages/PluginsPage.vue`** — Module name derived dynamically from `apiClient.defaults.baseURL`.
- **`frontend/src/App.vue`** — `resolvePlugins` uses dynamic `MODULE_NAME`.
- **`frontend/src/store/settings.ts`** — `localStorage` key uses dynamic `SETTINGS_KEY`.
- **`frontend/src/types/common.ts`** — Removed modulemanager-specific `ModuleInstance`, `RepositoryModule`, `Repository` interfaces.


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