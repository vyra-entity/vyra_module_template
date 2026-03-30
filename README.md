# vyra_module_template

[Copier](https://copier.readthedocs.io/) template for scaffolding new VYRA modules.

> **This is not a runnable module.** It generates the full directory structure for a new module via `copier copy`.

---

## Target Directory

> **Default target: `module-storages/` inside VOS2_WORKSPACE**

```
/home/holgder/VOS2_WORKSPACE/module-storages/
```

The `post_copier_setup.sh` script (automatically called by Copier as a task) renames the generated folder into the canonical layout:

```
module-storages/
└── {module_name}_{uuid}/
    └── {version}/          ← actual module content lives here
```

A symlink is then managed by `tools/setup.sh`:

```
modules/{module_name}_{uuid}  →  ../module-storages/{module_name}_{uuid}/{version}/
```

**Only deviate from `module-storages/` if you are intentionally creating a standalone module outside the VYRA workspace (e.g. a separate git repository). In all other cases, always use `module-storages/` as the target.**

---

## Quick Start

```bash
# From VOS2_WORKSPACE root — standard usage
copier copy --trust ~/VYRA/vyra_module_template module-storages/ --vcs-ref HEAD
```

Copier will interactively ask for all fields, generate the module inside `module-storages/{module_name}/`, and then `post_copier_setup.sh` moves it into the canonical `{module_name}_{uuid}/{version}/` layout automatically.

### Using the latest tagged version instead of HEAD

```bash
# Omit --vcs-ref to let Copier pick the highest git tag
copier copy --trust ~/VYRA/vyra_module_template module-storages/
```

> See comments in `copier.yml` for details on how Copier resolves the template source.

---

## Template Fields (copier.yml)

### Required fields

| Field | Type | Description | Example |
|---|---|---|---|
| `module_name` | `str` | Module name in `snake_case`. Used as directory name, Python package name, and Docker image name. Only lowercase letters, digits, and underscores allowed. | `my_detector` |
| `module_display_name` | `str` | Human-readable display name shown in the dashboard UI. Defaults to title-case of `module_name`. | `My Detector Module` |
| `module_description` | `str` | Short description of the module. Written into `README.md` and `.module/module_data.yaml`. | `Detects anomalies in sensor data` |
| `module_version` | `str` | Semantic version (`Major.Minor.Patch`). No pre-release or build metadata tags. Defaults to `1.0.0`. | `1.0.0` |
| `module_template` | `str` | One or more template names (comma-separated) this module is based on. Used for tracking and registry metadata. | `basic` or `basic,production-line-1` |
| `author_name` | `str` | Name of the module author. | `Max Mustermann` |
| `author_email` | `str` | Email address of the module author. | `max@example.com` |

### Optional feature flags

| Field | Type | Default | Description |
|---|---|---|---|
| `enable_frontend` | `bool` | `true` | Include a web frontend (Vue/Vite). Set to `false` for backend-only modules. |
| `enable_dev_mode` | `bool` | `true` | Start in development mode (Vite dev server + hot-reload). Set to `false` for production-mode defaults. |
| `enable_slim_mode` | `bool` | `false` | Slim mode: no ROS2 nodes, Python-only. Ideal for lightweight or resource-constrained modules. FULL mode (default) includes own ROS2 nodes. |
| `build_after_copy` | `bool` | `true` | Automatically build the Docker image (both `development` and `production` variants) after scaffolding. |
| `publish_to_repo_after_copy` | `bool` | `true` | Automatically publish the module to the local repository after building. |

### Derived variables (no prompt, available in templates)

| Expression | Result | Usage |
|---|---|---|
| `{{ module_name }}` | `my_detector` | Directory name, Python package |
| `{{ module_display_name }}` | `My Detector Module` | UI label |
| `{{ module_name \| replace('_', '-') }}` | `my-detector` | Docker entrypoint / service name |
| `{{ module_name \| title \| replace('_','') }}` | `MyDetector` | Python class name |

---

## Generated Directory Structure

After `post_copier_setup.sh` completes:

```
module-storages/
└── {module_name}_{uuid}/          ← instance directory (UUID v4, 32 hex chars)
    └── {version}/                 ← versioned module root (e.g. 1.0.0/)
        ├── .module/
        │   └── module_data.yaml   ← name, version, description, uuid, author, template
        ├── .copier-answers.yml    ← copier metadata (do not edit manually)
        ├── Dockerfile
        ├── Makefile
        ├── README.md
        ├── vyra_entrypoint.sh
        ├── config/
        ├── src/
        ├── tests/
        ├── tools/
        │   ├── post_copier_setup.sh
        │   └── publish_to_repo.sh
        └── frontend/              ← only if enable_frontend=true
```

---

## What post_copier_setup.sh does

Copier invokes `tools/post_copier_setup.sh` automatically as a task after copying. It:

1. Reads `name` and `version` from `.module/module_data.yaml`
2. Generates a UUID v4 (32 hex chars, no dashes)
3. Writes the UUID back into `.module/module_data.yaml`
4. Moves the module from `module-storages/{module_name}/` → `module-storages/{module_name}_{uuid}/{version}/`
5. Optionally builds the Docker image (`build_after_copy=true`)
6. Optionally publishes to the local repository (`publish_to_repo_after_copy=true`)

You can also run the flags manually:

```bash
bash tools/post_copier_setup.sh --build --publish
```

---

## Updating an existing module

To apply template changes to an already-generated module, the module directory must be its own git repository (Copier uses `git diff-tree` internally):

```bash
cd module-storages/{module_name}_{uuid}/{version}
git init && git add -A && git commit -m "init"
copier update --trust --defaults --vcs-ref HEAD
```

---

## Slim vs. Full mode

| | Slim (`enable_slim_mode=true`) | Full (`enable_slim_mode=false`) |
|---|---|---|
| ROS2 nodes | None | Own ROS2 nodes |
| Complexity | Low | Higher |
| Resource usage | Minimal | Standard |
| Use case | Simple logic, lightweight modules | Complex business logic, inter-module communication |

---

## Template development

To modify the template itself and test changes:

```bash
# 1. Edit files inside {{ module_name }}/ or copier.yml
# 2. Commit (required for copier update on existing modules to work)
git -C ~/VYRA/vyra_module_template add -A
git -C ~/VYRA/vyra_module_template commit -m "feat: describe change"

# 3. Tag a new version (required if not using --vcs-ref HEAD)
git -C ~/VYRA/vyra_module_template tag v1.x.y HEAD

# 4. Test by copying a new module
copier copy --trust ~/VYRA/vyra_module_template module-storages/ --vcs-ref HEAD
```
