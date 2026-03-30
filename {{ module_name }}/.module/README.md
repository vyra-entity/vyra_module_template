# .module/ — Module Metadata & Installation Configuration

The `.module/` directory is the **control center** of every VYRA module. It contains module identity
metadata, runtime dependencies, behavior configuration, plugin interface declarations, and all
package lists that drive the automated installation pipeline. Every file here is read and acted
upon by the **Module Manager** (`v2_modulemanager`) — never edit these files manually on a running
system; redeploy instead.

---

## Table of Contents

- [.module/ — Module Metadata \& Installation Configuration](#module--module-metadata--installation-configuration)
  - [Table of Contents](#table-of-contents)
  - [Installation Execution Order](#installation-execution-order)
  - [File Reference](#file-reference)
    - [`module_data.yaml`](#module_datayaml)
    - [`module_dependencies.yaml`](#module_dependenciesyaml)
    - [`module_params.yaml`](#module_paramsyaml)
    - [`plugin_interfaces.yaml`](#plugin_interfacesyaml)
    - [`pre-install.sh`](#pre-installsh)
    - [`system-packages.txt`](#system-packagestxt)
    - [`requirements.txt`](#requirementstxt)
    - [`npm-packages.txt`](#npm-packagestxt)
  - [Summary Table](#summary-table)

---

## Installation Execution Order

When the Module Manager deploys or updates a module, installation steps run in a fixed sequence:

```
┌─────────────────────────────────────────────────────┐
│              MODULE MANAGER PIPELINE                │
├──────┬──────────────────────────────────────────────┤
│  1.  │ pre-install.sh          (shell script)       │
│      │   ↳ Runs before any package manager.         │
│      │     Add GPG keys, PPAs, custom repos here.   │
├──────┼──────────────────────────────────────────────┤
│  2.  │ system-packages.txt     (apt packages)       │
│      │   ↳ Installed via apt-get inside container.  │
├──────┼──────────────────────────────────────────────┤
│  3.  │ requirements.txt        (pip packages)       │
│      │   ↳ pip install -r requirements.txt          │
├──────┼──────────────────────────────────────────────┤
│  4.  │ npm-packages.txt        (npm packages)       │
│      │   ↳ Only when enable_frontend = true.        │
│      │     npm install -g <packages>                │
└──────┴──────────────────────────────────────────────┘
```

> **Tip**: Steps 2–4 are skipped entirely if the respective file is empty (only comments).
> `pre-install.sh` always runs as long as it is executable.

---

## File Reference

### `module_data.yaml`

**Central module metadata / header file.**

This is the single source of truth for module identity inside the VYRA ecosystem. The Module Manager
reads this file to register, display, and address the module. Most fields are populated
automatically by [Copier](https://copier.readthedocs.io/) when the module is generated from this
template. The `uuid` and `alias` fields are filled in by `post_copier_setup.sh` after generation.

```yaml
name: "{{ module_name }}"             # Technical identifier — snake_case, unique per installation
display_name: "{{ module_display_name }}"  # Human-readable name shown in dashboard
description: "{{ module_description }}"   # Short description shown in module registry
version: "{{ module_version }}"           # Semantic version (e.g. "1.0.0")
author: "{{ author_name }}"               # Primary author / maintainer
author_email: "{{ author_email }}"        # Contact / support email
template:                                 # Template tags — set from copier prompt
  - "slim"                                # e.g. slim | full | ros2 | frontend
uuid: ""                                  # Auto-generated UUID (36 chars) — DO NOT edit manually
alias: ""                                 # Short URL alias, e.g. "mm" for v2_modulemanager
```

| Field           | Set by         | Purpose                                                |
|-----------------|----------------|--------------------------------------------------------|
| `name`          | Copier         | Primary identifier used in routing and service naming  |
| `display_name`  | Copier         | Human-readable label in dashboard / API response       |
| `description`   | Copier         | Short description visible in module catalog            |
| `version`       | Copier / dev   | Versioning for update checks in Module Manager         |
| `author`        | Copier         | Shown in module info panel                            |
| `author_email`  | Copier         | Contact address                                       |
| `template`      | Copier         | Template variant tags; used for runtime capability checks |
| `uuid`          | post_copier_setup.sh | Universally unique ID — generated once, never changes |
| `alias`         | post_copier_setup.sh | Short routing alias (e.g. `mm`, `db`)             |

---

### `module_dependencies.yaml`

**Runtime dependency declarations.**

Describes what the module needs before it can start: Python version, OS architecture,
communication protocols, hardware devices, and other VYRA modules. The Container Manager validates
these constraints at startup and blocks launch if critical dependencies are not satisfied.

See `module_dependencies.example.yaml` for a full annotated example with all available sections
(`runtime`, `hardware`, `services`).

```yaml
runtime:
  python_version: ">=3.11"
  arch: "amd64"
  communication:
    - protocol: "redis"

services:
  - module_id: "v2_modulemanager"
    optional: false
```

> The base template ships with an **empty** `module_dependencies.yaml` (only comments).
> Fill it in to declare the actual requirements of your module.

---

### `module_params.yaml`

**Module behavior, permissions, and resource configuration.**

Controls how the Module Manager treats this module: whether it is visible, removable, can run as
multiple instances, and how health checks are performed. Also configures the state machine's
broadcast frequency and history buffers.

Key sections:

| Section         | Purpose                                                                       |
|-----------------|-------------------------------------------------------------------------------|
| `permissions`   | `visible`, `removable`, `updatable`, `suspendable`, `multi_instance`, `protected` |
| `behavior`      | `auto_start`, `health_check` (interval, timeout, retries, start period)       |
| `state_manager` | Broadcast Hz, max history sizes, debug transition logging                     |
| `resources`     | Optional CPU / memory limits and reservations (Docker Swarm `resources:` block) |
| `labels`        | Custom Docker deploy labels added to the service                               |

---

### `plugin_interfaces.yaml`

**WASM plugin host-function declarations.**

Lists all host functions that WASM plugins loaded by this module are allowed to call. The
`LinkerFactory` reads this file at startup to bind each entry to the corresponding Python method
on `PluginGateway`. Any function not declared here cannot be called from WASM.

Structure:

```yaml
linker_map:
  - namespace: "vyra"          # Import namespace as declared in the WASM module
    functions:
      - wasm_name: "log"       # Name the WASM code imports
        host_func: "log"       # PluginGateway method that gets called
```

Built-in functions (shipped with the template):

| `wasm_name`  | `host_func`      | Description                                      |
|--------------|------------------|--------------------------------------------------|
| `log`        | `log`            | Write a message to the VYRA logging system       |
| `publish`    | `publish_event`  | Publish a pub/sub event (JSON payload)           |
| `request`    | `send_request`   | Send a request and receive a JSON response       |

See [`plugin/README.md`](../src/{{ module_name }}/{{ module_name }}/plugin/README.md) for details
on implementing the corresponding methods in `PluginGateway`.

---

### `pre-install.sh`

**Pre-installation hook — runs first, before any package manager.**

This Bash script is executed by the Module Manager at the very beginning of the installation
pipeline, before `apt`, `pip`, or `npm` touch anything. Use it to:

- Add GPG keys and third-party APT repositories (PPAs)
- Download and install binaries not available via package managers
- Verify that base-image dependencies are present and print diagnostic output
- Set up environment variables or config files required by subsequent package installs

> The script runs inside the **container** as root.
> Always make it defensive (`set -e`, existence checks) so a failure here aborts the
> deployment instead of silently continuing with a broken environment.

Executed: **Step 1** of the installation pipeline.

---

### `system-packages.txt`

**APT system package list.**

One package name per line; lines starting with `#` are comments and are ignored. The Module
Manager runs `apt-get install -y <packages>` for all non-comment, non-empty lines.

Common use cases:

- Native C/C++ libraries needed by Python extensions (e.g. `libssl-dev`, `libusb-dev`)
- System tools required at runtime (e.g. `ffmpeg`, `libgpiod2`)
- Development headers that pip cannot install on its own

Executed: **Step 2** of the installation pipeline, after `pre-install.sh`.

> Node.js and npm are **pre-installed** in the VYRA base image. Do **not** add them here.

---

### `requirements.txt`

**Python pip package list.**

Standard `pip` requirements file format. Pinned versions (`==`) are recommended for reproducible
builds; `>=` ranges are acceptable for optional / less critical packages.

Groups to consider:

| Group                  | Examples                                               |
|------------------------|--------------------------------------------------------|
| Core framework         | `fastapi`, `pydantic`, `dependency-injector`           |
| Communication          | `redis`, `aiohttp`, `paho-mqtt`, `grpcio`              |
| Web server             | `uvicorn[standard]`, `requests`, `httpx`               |
| Hot-reload (dev)       | `watchdog`                                             |
| Industrial protocols   | `pymodbus`, `asyncua`                                  |
| Logging                | `python-json-logger`, `colorlog`                       |

Executed: **Step 3** of the installation pipeline, after `system-packages.txt`.

---

### `npm-packages.txt`

**Global npm package list.**

One package name per line; comments with `#`. The Module Manager runs
`npm install -g <package>` for each entry.

> This step only runs when `enable_frontend: true` is set in the Copier configuration.
> Packages needed by the Vue 3 frontend are managed by `package.json` inside `frontend/`.
> Only add **global** CLI tools here (e.g. build toolchains, global type generators).

Executed: **Step 4** of the installation pipeline — the last step, after `requirements.txt`.

---

## Summary Table

| File                            | Read by              | When executed / evaluated                         |
|---------------------------------|----------------------|---------------------------------------------------|
| `module_data.yaml`              | Module Manager       | At module registration and every status query     |
| `module_dependencies.yaml`      | Container Manager    | At startup, before the module container launches  |
| `module_params.yaml`            | Module Manager       | At deployment and each config reload              |
| `plugin_interfaces.yaml`        | PluginGateway        | At module startup when WASM plugins are loaded    |
| `pre-install.sh`                | Module Manager       | Step 1 — before any package manager runs          |
| `system-packages.txt`           | Module Manager       | Step 2 — apt-get install                          |
| `requirements.txt`              | Module Manager       | Step 3 — pip install -r                           |
| `npm-packages.txt`              | Module Manager       | Step 4 — npm install -g (frontend only)           |
