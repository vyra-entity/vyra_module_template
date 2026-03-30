# ROS2 Hot Reload Guide

## Übersicht

Das Hot-Reload-System ermöglicht es, ROS2-Nodes zur Laufzeit automatisch neu zu bauen und zu starten, wenn Quellcode-Änderungen erkannt werden.

## Features

- 🔥 **Automatischer Rebuild**: Erkennt Änderungen an Python-Dateien und startet automatisch `colcon build`
- 🔄 **Automatischer Restart**: Startet den ROS2-Node nach erfolgreichem Build neu
- ⏱️ **Debouncing**: Verhindert mehrfache Rebuilds bei schnellen aufeinanderfolgenden Änderungen (2s Verzögerung)
- 📝 **Logging**: Detaillierte Logs über alle Rebuild- und Restart-Vorgänge

## Installation

### 1. Abhängigkeiten installieren

Im Container:
```bash
pip install watchdog --break-system-packages
```

Oder füge zu `.module/requirements.txt` hinzu:
```
watchdog>=3.0.0
```

### 2. Executable-Rechte setzen

```bash
chmod +x /workspace/tools/ros2_hot_reload.py
chmod +x /workspace/tools/tests/test_hot_reload.py
```

## Verwendung

### Manuelle Nutzung

```bash
# Im Container
cd /workspace
python3 tools/ros2_hot_reload.py [PACKAGE_NAME] [NODE_NAME]

# Beispiel für {module_name}
python3 tools/ros2_hot_reload.py {module_name} core
```

### Über Umgebungsvariablen

```bash
export ROS2_PACKAGE_NAME={module_name}
export ROS2_NODE_NAME=core
export ROS2_WATCH_PATH=/workspace/src
python3 tools/ros2_hot_reload.py
```

### Als Supervisord-Service

Füge zu `/etc/supervisor/conf.d/supervisord.conf` hinzu:

```ini
[program:ros2_hot_reload]
command=python3 /workspace/tools/ros2_hot_reload.py {module_name} core
directory=/workspace
autostart=false
autorestart=true
startsecs=5
stopwaitsecs=10
stdout_logfile=/workspace/log/ros2/hot_reload_stdout.log
stderr_logfile=/workspace/log/ros2/hot_reload_stderr.log
environment=
    ROS_DOMAIN_ID=%(ENV_ROS_DOMAIN_ID)s,
    ROS2_PACKAGE_NAME="{module_name}",
    ROS2_NODE_NAME="core"
```

Aktivierung:
```bash
# In .env setzen
ENABLE_ROS2_HOT_RELOAD=true
```

## Test-Suite

```bash
# Test ausführen
python3 tools/tests/test_hot_reload.py
```

Der Test:
1. ✅ Erstellt eine Test-Datei
2. ✅ Wartet auf Hot-Reload-Erkennung
3. ✅ Modifiziert die Datei
4. ✅ Prüft ob Rebuild erfolgte
5. ✅ Räumt Test-Dateien auf

## Workflow-Beispiel

1. **Starte Hot-Reload-Watcher**:
   ```bash
   docker exec -it <container_name> bash
   cd /workspace
   python3 tools/ros2_hot_reload.py {module_name} core
   ```

2. **Editiere Code auf dem Host**:
   ```bash
   # Auf dem Host-System
   cd VOS2_WORKSPACE/modules/{module_name}_*/src/{module_name}/{module_name}/
   vim application/registry.py  # Änderungen vornehmen
   ```

3. **Beobachte Auto-Rebuild**:
   ```
   📝 File changed: registry.py
   🔨 Starting rebuild process...
   ⏹️ Stopping node: core
   🔧 Building package: {module_name}
   ✅ Build successful
   🚀 Starting node: core
   ✅ Node started (PID: 12345)
   ```

## Konfiguration

### Überwachte Dateitypen
- `.py` Dateien in `src/` Verzeichnissen

### Debounce-Zeit
Standardmäßig 2 Sekunden, anpassbar in `ROS2HotReloadHandler.__init__()`:
```python
def __init__(self, ..., debounce_seconds: float = 2.0):
```

### Watched Directories
Standardmäßig `/workspace/src`, änderbar via:
```bash
export ROS2_WATCH_PATH=/workspace/src/{module_name}
```

## Integration mit Development Mode

In `vyra_entrypoint.sh`:

```bash
if [ "$VYRA_DEV_MODE" = "true" ]; then
    echo "🔥 Enabling ROS2 Hot Reload..."
    
    # Start hot reload in background
    nohup python3 /workspace/tools/ros2_hot_reload.py {module_name} core \
        > /workspace/log/ros2/hot_reload.log 2>&1 &
    
    HOT_RELOAD_PID=$!
    echo "✅ ROS2 Hot Reload started (PID: $HOT_RELOAD_PID)"
fi
```

## Troubleshooting

### Hot Reload erkennt keine Änderungen
- Prüfe ob Dateien tatsächlich in `/workspace/src/` liegen
- Prüfe Dateiendung (nur `.py` wird überwacht)
- Prüfe Logs: `cat /workspace/log/ros2/hot_reload.log`

### Build schlägt fehl
- Prüfe Build-Logs in `/workspace/log/ros2/`
- Teste manuell: `colcon build --packages-select {module_name}`
- Prüfe Syntax-Fehler im geänderten Code

### Node startet nicht nach Rebuild
- Prüfe ob `install/setup.bash` existiert
- Prüfe ob Node-Executable vorhanden: `ros2 pkg executables {module_name}`
- Prüfe ROS2-Environment: `env | grep ROS`

### Debouncing-Probleme
- Reduziere `debounce_seconds` für schnelleres Reagieren
- Erhöhe `debounce_seconds` bei zu vielen Rebuilds

## Performance-Überlegungen

- **Build-Zeit**: Ca. 5-30 Sekunden je nach Package-Größe
- **CPU-Last**: Minimal während Überwachung, hoch während Build
- **RAM-Nutzung**: ~50-100 MB für Watcher-Prozess
- **I/O-Last**: Gering, nur bei File-System-Events

## Best Practices

1. **Nur für Development**: Hot Reload nur im Dev-Mode aktivieren
2. **Selektive Überwachung**: Nur relevante Packages überwachen
3. **Build-Optimierung**: `--packages-select` statt Full-Workspace-Build
4. **Logging**: Immer Logs beobachten für Fehler-Diagnose
5. **Backup**: Immer Git-Commits vor größeren Änderungen

## Erweiterungen

### Multi-Package Support
```python
# Mehrere Packages überwachen
packages = ["{module_name}", "v2_dashboard"]
for pkg in packages:
    handler = ROS2HotReloadHandler(workspace_path, pkg, "core")
    observer.schedule(handler, f"/workspace/src/{pkg}", recursive=True)
```

### Custom Build-Optionen
```python
def _build_package(self) -> int:
    result = subprocess.run([
        "colcon", "build",
        "--packages-select", self.package_name,
        "--cmake-args", "-DCMAKE_BUILD_TYPE=Debug",  # Debug statt Release
        "--symlink-install"  # Schnellere Builds
    ], ...)
```

### Notification System
```python
def _trigger_rebuild(self):
    # Send notification to Redis/ROS2 topic
    self.redis_client.publish("hot_reload_events", {
        "action": "rebuild_started",
        "package": self.package_name,
        "timestamp": time.time()
    })
```

## Siehe auch

- [ROS2 Colcon Documentation](https://colcon.readthedocs.io/)
- [Watchdog Documentation](https://python-watchdog.readthedocs.io/)
- [Supervisord Documentation](http://supervisord.org/)
