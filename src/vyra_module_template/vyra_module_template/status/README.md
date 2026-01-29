# Status Node - 3-Layer State Machine Management

## Übersicht

Der Status Node verwaltet die 3-Layer State Machine für das v2_modulemanager Modul basierend auf der `vyra_base` State Machine Implementierung.

### Die 3 Layer

1. **Lifecycle Layer** - Existenz und Aktivierung
   - `UNINITIALIZED` → `INITIALIZING` → `ACTIVE` → `SHUTTING_DOWN` → `DEACTIVATED`
   - Verwaltet: Start, Initialisierung, Shutdown, Recovery

2. **Operational Layer** - Laufzeitaktivität  
   - `IDLE` → `READY` → `RUNNING` → `PAUSED`/`BLOCKED`/`DELEGATING` → `COMPLETED`
   - Verwaltet: Task-Ausführung, Pausen, Blockierungen

3. **Health Layer** - System-Gesundheit
   - `OK` → `WARNING` → `OVERLOADED` → `FAULTED` → `CRITICAL`
   - Verwaltet: Fehler, Warnungen, Überlastung

### Layer-Interaktion

- **Lifecycle → Operational**: Lifecycle bestimmt welche Operational States erlaubt sind
- **Health → Lifecycle**: Health kann Lifecycle-Transitions erzwingen (z.B. Fault → Recovery)
- **Health → Operational**: Health kann Operational einschränken (z.B. Overload → Pause)

## ROS2 Interfaces

### Service: `set_status`

**Request** (String mit JSON):
```json
{
  "layer": "lifecycle|operational|health",
  "action": "start|shutdown|ready|fault|...",
  "metadata": {
    "reason": "manual",
    ...
  }
}
```

**Response** (String mit JSON):
```json
{
  "success": true,
  "current_status": {
    "lifecycle": "Active",
    "operational": "Ready",
    "health": "OK",
    "timestamp": "2025-12-11T10:30:00",
    "metadata": {...}
  },
  "message": "Successfully executed lifecycle.start",
  "error": null
}
```

### Topic: `get_status`

**Typ**: `std_msgs/String` (JSON)

**Payload**:
```json
{
  "lifecycle": "Active",
  "operational": "Running",
  "health": "OK",
  "timestamp": "2025-12-11T10:30:00.123",
  "metadata": {
    "module_name": "v2_modulemanager",
    "is_operational": true,
    "is_healthy": true
  }
}
```

**Update-Rate**: 1 Hz (nur bei Änderungen)

### Topic: `state_feed`

**Typ**: `v2_dashboard_interfaces/VBASEStateFeed`

Standard VYRA State Feed für System-Integration.

## Verwendung

### Automatischer Start

Der Status Node startet automatisch beim Container-Start:

1. `UNINITIALIZED` → `INITIALIZING` (auto)
2. `INITIALIZING` → `ACTIVE` (auto)
3. `IDLE` → `READY` (auto)

Der Modul ist nach Start sofort operational.

### Status Abfragen (Python)

```python
from v2_modulemanager.status import StatusSubscriber, ThreeLayerStatus

def on_status_update(status: ThreeLayerStatus):
    print(f"Lifecycle: {status.lifecycle}")
    print(f"Operational: {status.operational}")
    print(f"Health: {status.health}")

subscriber = StatusSubscriber(node, on_status_update)
```

### Status Setzen (Python - nur v2_modulemanager Package)

```python
from v2_modulemanager.status import StatusServiceClient

client = StatusServiceClient(node)

# Lifecycle actions
client.shutdown_module(reason="maintenance")
client.start_module()

# Operational actions
client.start_task({"task_id": "123", "type": "deploy"})
client.pause_task(reason="user_request")
client.resume_task()

# Health actions
client.report_warning({"cpu": "85%"})
client.report_fault(error="Connection lost")
client.clear_health()
```

### Status Setzen (ROS2 CLI)

```bash
# Shutdown module
ros2 service call /v2_modulemanager/set_status std_msgs/String \
  'data: "{\"layer\": \"lifecycle\", \"action\": \"shutdown\", \"metadata\": {\"reason\": \"manual\"}}"'

# Start task
ros2 service call /v2_modulemanager/set_status std_msgs/String \
  'data: "{\"layer\": \"operational\", \"action\": \"start_task\", \"metadata\": {\"task_id\": \"123\"}}"'

# Report fault
ros2 service call /v2_modulemanager/set_status std_msgs/String \
  'data: "{\"layer\": \"health\", \"action\": \"report_fault\", \"metadata\": {\"error\": \"Test error\"}}"'
```

### Status Monitoren (ROS2 CLI)

```bash
# Subscribe to status updates
ros2 topic echo /v2_modulemanager/get_status

# Subscribe to state feed
ros2 topic echo /v2_modulemanager/state_feed
```

## Verfügbare Actions

### Lifecycle Layer

| Action | Von | Nach | Beschreibung |
|--------|-----|------|--------------|
| `start` | UNINITIALIZED | INITIALIZING | Starte Initialisierung |
| `complete_init` | INITIALIZING | ACTIVE | Initialisierung erfolgreich |
| `fail_init` | INITIALIZING | RECOVERING | Initialisierung fehlgeschlagen |
| `shutdown` | ACTIVE | SHUTTING_DOWN | Kontrolliertes Herunterfahren |
| `recover` | FAULTED | RECOVERING | Starte Recovery |
| `complete_recovery` | RECOVERING | ACTIVE | Recovery erfolgreich |
| `fail_recovery` | RECOVERING | DEACTIVATED | Recovery fehlgeschlagen |

### Operational Layer

| Action | Von | Nach | Beschreibung |
|--------|-----|------|--------------|
| `ready` | IDLE | READY | Bereit für Tasks |
| `start_task` | READY | RUNNING | Task starten |
| `pause` | RUNNING | PAUSED | Task pausieren |
| `resume` | PAUSED | RUNNING | Task fortsetzen |
| `block` | RUNNING | BLOCKED | Ressourcen blockiert |
| `unblock` | BLOCKED | RUNNING | Blockierung aufgehoben |
| `delegate` | RUNNING | DELEGATING | An anderes Modul delegieren |
| `complete` | RUNNING | COMPLETED | Task abgeschlossen |
| `reset` | COMPLETED | READY/IDLE | Zurück zu Idle/Ready |

### Health Layer

| Action | Von | Nach | Beschreibung |
|--------|-----|------|--------------|
| `report_warning` | OK | WARNING | Warnung melden |
| `report_overload` | WARNING | OVERLOADED | Überlastung melden |
| `report_fault` | WARNING | FAULTED | Fehler melden |
| `clear_warning` | WARNING | OK | Warnung beheben |
| `reduce_load` | OVERLOADED | WARNING | Last reduzieren |
| `recover` | FAULTED | OK | Fehler beheben |
| `escalate_critical` | FAULTED | CRITICAL | Kritischer Fehler |

## Integration mit vyra_base

Der Status Node nutzt die `UnifiedStateMachine` aus `vyra_base.state.unified`:

```python
from vyra_base.state.unified import UnifiedStateMachine

# 3-Layer State Machine
state_machine = UnifiedStateMachine()

# Lifecycle
state_machine.start()
state_machine.complete_initialization()

# Operational
state_machine.ready()
state_machine.start_task({"task_id": "123"})

# Health
state_machine.report_warning({"cpu": "85%"})

# Query
states = state_machine.get_all_states()
# {'lifecycle': 'Active', 'operational': 'Running', 'health': 'Warning'}
```

## SROS2 Security

**Policies werden später generiert.**

Geplante Access-Rechte:

- **Read Access** (get_status Topic): Alle Module
- **Write Access** (set_status Service): Nur v2_modulemanager Package Nodes
- **State Feed**: Publish nur Status Node, Subscribe alle Module

## Testing

```bash
# Start status node
ros2 run v2_modulemanager status_node

# Test lifecycle
ros2 service call /v2_modulemanager/set_status std_msgs/String \
  'data: "{\"layer\": \"lifecycle\", \"action\": \"shutdown\"}"'

# Monitor status
ros2 topic echo /v2_modulemanager/get_status
```

## Logging

Der Status Node loggt alle State-Transitions:

```
[INFO] [status_node]: 🚀 Auto-starting module lifecycle...
[INFO] [status_node]:   ✓ Lifecycle: INITIALIZING
[INFO] [status_node]:   ✓ Lifecycle: ACTIVE
[INFO] [status_node]:   ✓ Operational: READY
[INFO] [status_node]: ✅ Module successfully activated!
```

## Fehlerbehandlung

Bei Fehlern wird automatisch Health-Layer aktualisiert:

1. **Warning**: Logs + Health WARNING state
2. **Fault**: Health FAULTED + optional Lifecycle RECOVERING
3. **Critical**: Health CRITICAL + Lifecycle SHUTTING_DOWN

```python
try:
    # Critical operation
    risky_operation()
except Exception as e:
    # Automatically triggers Health → FAULTED → Lifecycle RECOVERING
    client.report_fault(error=str(e))
```
