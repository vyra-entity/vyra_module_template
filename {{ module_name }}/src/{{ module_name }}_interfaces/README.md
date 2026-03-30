# {{ module_name }}_interfaces

This package defines the external interfaces of the `{{ module_name }}` module — the remote-callable
functions, publishers, and action servers that are exposed over the VYRA Communication Abstraction
Layer (CAL).

Interfaces are **auto-generated** during `colcon build` from JSON config files. You do not write
`.msg`, `.srv`, or `.action` files by hand.

## Directory Structure

```
{{ module_name }}_interfaces/
├── config/          ← Interface definition files (*.meta.json)          ← YOU EDIT THESE
├── proto/           ← Protobuf schema files (*.proto)                   ← YOU EDIT THESE
├── proto_gen/
│   ├── python/      ← Generated Python bindings  (*_pb2.py, *_pb2.pyi)
│   └── cpp/         ← Generated C++ bindings     (*.pb.h, *.pb.cc)
├── msg/             ← Generated ROS2 message types
├── srv/             ← Generated ROS2 service types
├── action/          ← Generated ROS2 action types
├── package.xml
└── CMakeLists.txt
```

Only `config/` and `proto/` are edited manually. Everything else is generated.

## Protobuf Interfaces (`proto/`)

For protocols that do not use ROS2 IDL — namely **Zenoh**, **Redis**, and **UDS** — message
serialization is handled with [Protocol Buffers](https://protobuf.dev/). The `.proto` schema
files live in `proto/` and define the wire format for all non-ROS2 messages.

The preferred naming convention mirrors the config files:

```
proto/<module_name>_<area>.proto
```

Example: `proto/{{ module_name }}_sensors.proto`, `proto/{{ module_name }}_control.proto`.

### Code Generation

From the `.proto` files, bindings are generated for both Python and C++ and placed in:

| Language | Output folder | Files |
|---|---|---|
| Python | `proto_gen/python/` | `*_pb2.py` (runtime), `*_pb2.pyi` (type stubs) |
| C++ | `proto_gen/cpp/` | `*.pb.h` (header), `*.pb.cc` (implementation) |

Regenerate after editing a `.proto` file:

```bash
# Python
protoc --python_out=proto_gen/python \
       --pyi_out=proto_gen/python \
       -I proto proto/<file>.proto

# C++
protoc --cpp_out=proto_gen/cpp \
       -I proto proto/<file>.proto
```

### General-Purpose Serialization

The Protobuf schemas are **not** restricted to a single protocol or use case. Although they
primarily drive the Zenoh, Redis, and UDS transport layers, they can be reused freely:

- Persisting structured data to disk or SQLite
- Serializing payloads sent over gRPC or HTTP
- Exchanging data with external systems or other languages (C++, Go, Rust)
- Any context where a well-defined, versionable binary or JSON-compatible format is needed

## NFS Interface Share

To allow all modules in the VYRA deployment to access each other's interface definitions
(Protobuf schemas and generated bindings), the `{{ module_name }}_interfaces` package is mounted
from a shared **NFS volume**. This means:

- The `proto/` and `proto_gen/` directories are available to every module container without
  copying files manually.
- C++ modules or external tools can include the generated headers directly from the NFS path.
- Updates to schemas (rerun of `protoc`) are immediately visible to all consumers after the
  NFS write completes — no container restart required for consumers that dynamically import.

The NFS mount is configured in `docker-compose.yml` under the module's volume definitions and
uses an IP address (not a hostname) in the `driver_opts` to avoid Docker Swarm DNS limitations.

The shared mount path inside containers is:

```
/workspace/interfaces/{{ module_name }}_interfaces/
```

## Config File Format (`.meta.json`)

Each config file contains a JSON array of interface definitions. Preferred naming:

```
config/<module_name>_<area>.meta.json
```

The name can be freely chosen but must be unique within `config/`. Multiple config files are merged
during generation — split interfaces by functional area (e.g. `sensors`, `control`, `diagnostics`).

### Full Example

```json
[
    {
        "tags": ["zenoh"],
        "type": "service",
        "functionname": "get_status",
        "displayname": "Get Status",
        "description": "Returns the current operational status of the module.",
        "filetype": ["{{ module_name | upper | replace('_', '') }}GetStatus.srv"],
        "params": [],
        "returns": [
            {
                "name": "status",
                "datatype": "str",
                "displayname": "Status",
                "description": "Current status string."
            }
        ],
        "access_level": 1,
        "displaystyle": {
            "visible": true,
            "published": true,
            "category": "Diagnostics"
        }
    },
    {
        "tags": ["zenoh"],
        "type": "message",
        "functionname": "temperature_feed",
        "displayname": "Temperature Feed",
        "description": "Continuously published temperature measurements.",
        "filetype": ["{{ module_name | upper | replace('_', '') }}TemperatureFeed.msg"],
        "params": [
            {
                "name": "value",
                "datatype": "float",
                "displayname": "Temperature",
                "description": "Temperature in degrees Celsius."
            }
        ]
    },
    {
        "tags": ["zenoh"],
        "type": "action",
        "functionname": "run_calibration",
        "displayname": "Run Calibration",
        "description": "Long-running calibration procedure with progress feedback.",
        "filetype": ["{{ module_name | upper | replace('_', '') }}RunCalibration.action"],
        "params": [
            {
                "name": "mode",
                "datatype": "str",
                "displayname": "Mode",
                "description": "Calibration mode: auto or manual."
            }
        ],
        "returns": [
            {
                "name": "offset",
                "datatype": "float",
                "displayname": "Offset",
                "description": "Computed calibration offset."
            }
        ],
        "access_level": 2,
        "displaystyle": {
            "visible": true,
            "published": false,
            "category": "Calibration"
        }
    }
]
```

### Field Reference

| Field | Required | Description |
|---|---|---|
| `tags` | yes | Protocol(s) this interface is exposed on (see protocol tags below) |
| `type` | yes | Interface type: `service`, `message`, or `action` |
| `functionname` | yes | Python function name — must match the callback in `application.py` exactly |
| `displayname` | yes | Human-readable name shown in the Module Manager UI |
| `description` | yes | Short description of the interface |
| `filetype` | yes | List with the generated IDL filename(s) (`.srv`, `.msg`, `.action`) or Protobuf schema filename(s) (`.proto`) for non-ROS2 protocols |
| `params` | yes | Input parameters — list of `{name, datatype, displayname, description}` |
| `returns` | yes (services/actions) | Return values — same structure as `params` |
| `access_level` | no | Minimum access level required to call this interface (default: 0 = public) |
| `displaystyle.visible` | no | Whether the interface appears in the Module Manager UI (default: false) |
| `displaystyle.published` | no | Whether the interface is listed in the public API catalog |
| `displaystyle.category` | no | UI grouping category |

### Protocol Tags

| Tag value | Protocol | Mode |
|---|---|---|
| `"zenoh"` | Zenoh pub/sub and query | Full and SLIM Mode |
| `"ros2"` | ROS2 DDS | Full Mode only |
| `"redis"` | Redis pub/sub channels | Full and SLIM Mode |
| `"uds"` | Unix Domain Sockets (local IPC) | Full and SLIM Mode |

Multiple tags can be applied simultaneously: `["zenoh", "redis"]`.

### Interface Types

| `type` | Generated file | Use case |
|---|---|---|
| `service` | `.srv` | Request/response — caller waits for a result |
| `message` | `.msg` | Publisher — fire-and-forget event stream |
| `action` | `.action` | Long-running task with incremental feedback and cancellation support |

### Supported Data Types

`bool`, `int`, `float`, `str`, `datetime`, `duration`, `string[]`, `int32[]`, `object`

## Regenerating Interfaces

**ROS2 IDL types** — after editing any `.meta.json` config file, rebuild inside the module container:

```bash
source /opt/ros/kilted/setup.bash
colcon build --packages-select {{ module_name }}_interfaces
```

The generated `.srv` / `.msg` / `.action` IDL files will appear in `msg/`, `srv/`, and `action/`.

**Protobuf types** — after editing any `.proto` file, run `protoc` as shown in the
[Protobuf Code Generation](#code-generation) section above. The `proto_gen/` directories
are written directly and do not require `colcon build`.

## Troubleshooting

If interfaces are not registered or callbacks fail to bind at runtime, check the log file:

```
logs/core_stdout.log
```

Common causes:
- `functionname` in the config does not match the Python callback name exactly (case-sensitive)
- A `filetype` entry references a filename that does not match the generated IDL file
- `colcon build` was not re-run after editing config files
- Multiple config entries share the same `functionname` (only the first is used; a warning is logged)
