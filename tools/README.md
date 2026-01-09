# <MODULENAME> Tools

Tools für das <MODULENAME> Modul.

---

## 📋 Übersicht

- [Build & Deployment](#-build--deployment) - Frontend-Build und Module-Deployment
- [ROS2 Tools](#-ros2-tools) - Interface-Setup, Hot-Reload, SROS2
- [Development Tools](#-development-tools) - Dev-Server, Testing, Cleanup
- [Security Tools](#-security-tools) - SSL-Zertifikate, SROS2-Policies
- [Module Tools](#-module-tools) - Module umbenennen und anpassen
- [Network Tools](#-network-tools) - Docker-Netzwerk-Setup

---

## 🏗️ Build & Deployment

### \`build_frontend.sh\`

Baut das Vue.js/React Frontend und integriert es ins Backend.

**Verwendung:**
\`\`\`bash
./tools/build_frontend.sh
\`\`\`

**Funktionen:**
- Installiert NPM Dependencies (\`npm install\`)
- Baut Frontend-Projekt (\`npm run build\`)
- Kopiert Build-Artefakte ins Backend
  - \`dist/assets/\` → \`backend/static/\`
  - \`dist/index.html\` → \`backend/templates/\`
- Validiert Build-Output

**Voraussetzungen:**
- Node.js und npm installiert
- \`package.json\` im Frontend-Verzeichnis vorhanden
- Frontend-Projekt korrekt konfiguriert

**Beispiel-Workflow:**
\`\`\`bash
# Entwicklung: Frontend im Dev-Mode
cd frontend
npm run dev

# Production: Build und Integration
cd ..
./tools/build_frontend.sh
\`\`\`

---

## 🤖 ROS2 Tools

### \`setup_interfaces.py\`

Richtet ROS2-Interfaces (Messages, Services, Actions) für das Modul ein.

**Verwendung:**
\`\`\`bash
# Standard Interface Package
python3 tools/setup_interfaces.py

# Eigenes Interface Package
python3 tools/setup_interfaces.py --interface_pkg <MODULENAME>_interfaces

# Dynamisches Interface Package
python3 tools/setup_interfaces.py --dynamic_src_path /tmp/dynamic_interfaces
\`\`\`

**Optionen:**
- \`--interface_pkg\` - Name des Interface-Packages (Standard: vyra_module_interfaces)
- \`--dynamic_src_path\` - Pfad für dynamische Interface-Packages

**Funktionen:**
- Erstellt/aktualisiert ROS2 Interface-Packages
- Scannt \`storage/interfaces/\` nach .msg, .srv, .action Dateien
- Generiert package.xml und CMakeLists.txt
- Fügt nötige Dependencies hinzu

**Beispiel-Struktur:**
\`\`\`
storage/interfaces/
├── msg/
│   └── CustomMessage.msg
├── srv/
│   └── CustomService.srv
└── action/
    └── CustomAction.action
\`\`\`

### \`generate_grpc_protos.py\`

Generiert Python-Code aus gRPC .proto Dateien.

**Verwendung:**
\`\`\`bash
# Standard (storage/interfaces/ → src/rest_api/grpc_generated/)
python3 tools/generate_grpc_protos.py

# Eigene Verzeichnisse
python3 tools/generate_grpc_protos.py \\
  --proto-dir /custom/protos \\
  --output-dir /custom/output
\`\`\`

**Optionen:**
- \`--proto-dir\` - Verzeichnis mit .proto Dateien (Standard: /workspace/storage/interfaces/)
- \`--output-dir\` - Output-Verzeichnis (Standard: /workspace/src/rest_api/grpc_generated/)

**CI/CD Integration:**
\`\`\`dockerfile
# In Dockerfile
RUN python /workspace/tools/generate_grpc_protos.py
\`\`\`

### \`ros2_hot_reload.py\`

Hot-Reload für ROS2-Nodes während der Entwicklung.

**Verwendung:**
\`\`\`bash
# Aus start_hot_reload.sh
python3 tools/ros2_hot_reload.py --package <MODULENAME> --node <nodename>
\`\`\`

**Funktionen:**
- Überwacht Python-Dateien auf Änderungen
- Startet Node bei Änderungen automatisch neu
- Erhält ROS2-Kontext
- Ideal für iterative Entwicklung

### \`start_hot_reload.sh\`

Quick-Start für ROS2 Hot-Reload.

**Verwendung:**
\`\`\`bash
# Standard (<MODULENAME> Package)
./tools/start_hot_reload.sh

# Eigenes Package
./tools/start_hot_reload.sh <MODULENAME> <nodename>
\`\`\`

**Funktionen:**
- Prüft Container-Umgebung
- Installiert watchdog (falls nötig)
- Startet ros2_hot_reload.py

### \`generate_sros2_policy.py\`

Mergt statische und dynamische SROS2-Policy-Dateien.

**Verwendung:**
\`\`\`bash
python3 tools/generate_sros2_policy.py \\
  --static config/sros2_policy_static.xml \\
  --dynamic config/sros2_policy_dynamic.xml \\
  --output sros2_keystore/policies/
\`\`\`

**Funktionen:**
- Mergt statische (eigene Publish/Reply) und dynamische (Wildcards) Policies
- Erstellt vereinheitlichte policy.xml
- Für SROS2-Sicherheitssetup

### \`startup_ros2_core.sh\`

Startet ROS2-Core-Services des Moduls.

**Verwendung:**
\`\`\`bash
./tools/startup_ros2_core.sh
\`\`\`

### \`startup_ros2_node.sh\`

Startet einen spezifischen ROS2-Node.

**Verwendung:**
\`\`\`bash
./tools/startup_ros2_node.sh <MODULENAME> <nodename>
\`\`\`

### \`startup_ros2_status.sh\`

Zeigt ROS2-Status und aktive Nodes (nur v2_dashboard).

**Verwendung:**
\`\`\`bash
./tools/startup_ros2_status.sh
\`\`\`

**Zeigt:**
- Aktive Nodes
- Topics
- Services
- Actions

---

## 🛠️ Development Tools

### \`check_dev_server.sh\`

Prüft den Status des Development-Servers (Vite/Webpack).

**Verwendung:**
\`\`\`bash
./tools/check_dev_server.sh
\`\`\`

**Prüft:**
- Dev-Server-Prozess-Status
- Port-Verfügbarkeit
- Log-Dateien
- HMR (Hot Module Replacement) Status

**Beispielausgabe:**
\`\`\`
✅ Dev Server: RUNNING
   Port: 5173
   PID: 1234
   HMR: Active
\`\`\`

### \`restart_dev_server.sh\`

Startet den Development-Server neu.

**Verwendung:**
\`\`\`bash
./tools/restart_dev_server.sh
\`\`\`

**Funktionen:**
- Stoppt laufende Dev-Server-Prozesse (Vite, Webpack)
- Bereinigt alte Log-Dateien
- Startet Dev-Server neu mit aktueller Konfiguration
- Zeigt Server-URL und Port

**Anwendungsfälle:**
- Nach Konfigurations-Änderungen
- Bei HMR-Problemen
- Nach Package-Updates

### \`debug_executables.sh\`

Zeigt Debug-Informationen über installierte ROS2-Executables (nur v2_dashboard).

**Verwendung:**
\`\`\`bash
./tools/debug_executables.sh
\`\`\`

**Zeigt:**
- Installierte ROS2-Packages
- Verfügbare Executables
- Entry-Points in setup.py
- Installations-Pfade

**Nützlich bei:**
- "Executable not found" Fehlern
- Package-Installation-Problemen
- Deployment-Debugging

### \`quick_test_hot_reload.sh\`

Schneller Test für Hot-Reload-Funktionalität.

**Verwendung:**
\`\`\`bash
./tools/quick_test_hot_reload.sh
\`\`\`

**Funktionen:**
- Testet watchdog-Installation
- Prüft Hot-Reload-Konfiguration
- Zeigt aktive Watcher

### \`cleanup_thread_logs.sh\`

Räumt alte ROS2-Thread-Log-Dateien auf.

**Verwendung:**
\`\`\`bash
./tools/cleanup_thread_logs.sh
\`\`\`

**Funktionen:**
- Entfernt \`python3_*.log\` aus \`/workspace/log/ros2\`
- Für Speicherplatz und Übersichtlichkeit

### \`cleanup_zombie_processes.sh\`

Bereinigt Zombie-Prozesse im Container.

**Verwendung:**
\`\`\`bash
./tools/cleanup_zombie_processes.sh
\`\`\`

**Funktionen:**
- Findet und beendet Zombie-Prozesse
- Gibt Ressourcen frei

---

## 🔐 Security Tools

### \`create_ssl_certificates.sh\`

Erstellt selbst-signierte SSL-Zertifikate für Modul-Komponenten.

**Verwendung:**
\`\`\`bash
# Backend-Zertifikat
./tools/create_ssl_certificates.sh --name webserver

# Frontend-Zertifikat
./tools/create_ssl_certificates.sh --name frontend

# API-Gateway-Zertifikat
./tools/create_ssl_certificates.sh --name api-gateway

# Eigene Domain und Gültigkeitsdauer
./tools/create_ssl_certificates.sh \\
  --name webserver \\
  --domain <MODULENAME>.vyra.local \\
  --days 730
\`\`\`

**Optionen:**
- \`--name\` - Zertifikatsname (webserver, frontend, api-gateway, redis-tls)
- \`--domain\` - Domain-Name (Standard: localhost)
- \`--days\` - Gültigkeitsdauer in Tagen (Standard: 365)

**Output:**
\`\`\`
storage/certificates/
├── webserver.crt
├── webserver.key
├── frontend.crt
└── frontend.key
\`\`\`

**Integration in nginx.conf:**
\`\`\`nginx
ssl_certificate /workspace/storage/certificates/webserver.crt;
ssl_certificate_key /workspace/storage/certificates/webserver.key;
\`\`\`

---

## 🏷️ Module Tools

### \`rename_module.sh\`

Benennt das Modul komplett um - alle Referenzen, Verzeichnisse und Dateien.

**Verwendung:**
\`\`\`bash
# Mit Modulnamen
./tools/rename_module.sh my_new_module_name

# Aus module_data.yaml lesen
./tools/rename_module.sh

# Mit altem Namen (falls nicht vyra_module_template)
./tools/rename_module.sh my_new_name --old_name=old_module_name
\`\`\`

**Was wird umbenannt:**
- Verzeichnisnamen (\`src/<OLD>\` → \`src/<NEW>\`)
- Package-Namen in allen Dateien
- Python Packages und Module
- Konfigurationsdateien:
  - \`package.xml\`
  - \`setup.py\`, \`setup.cfg\`
  - \`pyproject.toml\`
  - \`module_config.yaml\`
  - \`.env\`
  - \`vyra_entrypoint.sh\`
- Resource-Dateien
- ROS2-spezifische Dateien
- Alle Imports und Referenzen im Code

**Workflow:**
\`\`\`bash
# 1. Template klonen
git clone <repo>/vyra_module_template my_new_module

# 2. In Modul-Verzeichnis wechseln
cd my_new_module

# 3. Modul umbenennen
./tools/rename_module.sh my_new_module

# 4. Überprüfen
grep -r "vyra_module_template" . --exclude-dir=.git
# Sollte keine Treffer mehr geben (außer in dieser README)

# 5. Container bauen und testen
docker compose build
docker compose up -d
\`\`\`

**Ideal beim:**
- Klonen von vyra_module_template
- Erstellen neuer Module aus Template
- Umbenennen bestehender Module

---

## 🌐 Network Tools

### \`create_docker_network.sh\`

Erstellt Docker-Netzwerk für das Modul (nur v2_dashboard).

**Verwendung:**
\`\`\`bash
./tools/create_docker_network.sh
\`\`\`

**Funktionen:**
- Erstellt Bridge-Netzwerk
- Konfiguriert Subnetz
- Ermöglicht Container-Kommunikation

**Beispiel:**
\`\`\`bash
# Netzwerk erstellen
./tools/create_docker_network.sh

# Prüfen
docker network ls | grep vyra
\`\`\`

---

## 🚀 Runtime Scripts

### \`vyra_entrypoint_runtime.sh\`

Container-Entrypoint für das Modul (wird von Docker verwendet).

**Funktionen:**
- Initialisiert ROS2-Umgebung
- Startet Backend-Services (FastAPI/Uvicorn)
- Startet Frontend-Server (Dev/Prod)
- Handled Container-Lifecycle

**Modi:**
\`\`\`bash
# Production Mode
VYRA_DEV_MODE=false ./tools/vyra_entrypoint_runtime.sh

# Development Mode (mit HMR)
VYRA_DEV_MODE=true ./tools/vyra_entrypoint_runtime.sh
\`\`\`

### \`setup_ros_global.sh\`

Richtet globale ROS2-Umgebung im Container ein (nur v2_dashboard).

**Verwendung:**
\`\`\`bash
source ./tools/setup_ros_global.sh
\`\`\`

**Konfiguriert:**
- ROS2 Umgebungsvariablen
- Workspace-Sourcing
- CycloneDDS-Konfiguration

### \`wait-for-redis.sh\`

Wartet auf Redis-Verfügbarkeit vor dem Start.

**Verwendung:**
\`\`\`bash
./tools/wait-for-redis.sh
\`\`\`

**Funktionen:**
- Prüft Redis-Verbindung
- Retry-Logik (max. 30 Versuche)
- Timeout-Handling

---

## 📁 Weitere Verzeichnisse

### \`container_manager_api/\`

Python-API-Client für Container Manager (nur v2_modulemanager).

### \`devel/\`

Entwicklungs-Hilfsskripte und Prototypen.

### \`ros/\`

ROS2-spezifische Hilfsskripte:
- Launch-Files
- Node-Konfigurationen
- ROS2-Utilities

### \`tests/\`

Test-Skripte und Test-Utilities (nur v2_modulemanager).

### \`readme/\`

Zusätzliche README-Dateien und Dokumentation (nur v2_modulemanager).

---

## 💡 Best Practices

### Lokale Entwicklung

**1. Development Mode aktivieren:**
\`\`\`bash
# In .env
echo "VYRA_DEV_MODE=true" >> .env
\`\`\`

**2. Dev-Server starten:**
\`\`\`bash
docker compose up -d <MODULENAME>
docker exec -it <MODULENAME> bash
./tools/restart_dev_server.sh
\`\`\`

**3. Frontend-Änderungen:**
- Hot Module Replacement (HMR) aktiv
- Änderungen werden sofort sichtbar
- Kein Rebuild nötig

**4. Backend-Änderungen mit Hot-Reload:**
\`\`\`bash
./tools/start_hot_reload.sh
\`\`\`

### Production Deployment

**1. Frontend bauen:**
\`\`\`bash
./tools/build_frontend.sh
\`\`\`

**2. SSL-Zertifikate erstellen:**
\`\`\`bash
./tools/create_ssl_certificates.sh --name webserver --days 365
\`\`\`

**3. Production Mode:**
\`\`\`bash
# In .env
VYRA_DEV_MODE=false
\`\`\`

**4. Container neu starten:**
\`\`\`bash
docker compose restart <MODULENAME>
\`\`\`

### Interface-Änderungen

**1. Interface-Dateien bearbeiten:**
\`\`\`bash
# Neue Message erstellen
cat > storage/interfaces/msg/Status.msg << EOF
string module_name
bool is_active
float64 cpu_usage
EOF
\`\`\`

**2. Interfaces generieren:**
\`\`\`bash
python3 tools/setup_interfaces.py
\`\`\`

**3. Rebuild:**
\`\`\`bash
colcon build --packages-select vyra_module_interfaces
source install/setup.bash
\`\`\`

### Testing

**1. Development Server prüfen:**
\`\`\`bash
./tools/check_dev_server.sh
\`\`\`

**2. ROS2 Status prüfen:**
\`\`\`bash
# Nodes listen
ros2 node list

# Topics listen
ros2 topic list
\`\`\`

**3. Backend API testen:**
\`\`\`bash
curl -k https://localhost/api/\<MODULENAME\>/health | jq .
\`\`\`

**4. Frontend testen:**
\`\`\`bash
curl -k https://localhost/\<MODULENAME\>/
\`\`\`

### Debugging

**1. Executables prüfen (v2_dashboard):**
\`\`\`bash
./tools/debug_executables.sh
\`\`\`

**2. Logs ansehen:**
\`\`\`bash
# Container Logs
docker logs <MODULENAME>

# Vite Logs
docker exec <MODULENAME> cat /workspace/log/vite.log

# ROS2 Logs
docker exec <MODULENAME> cat /workspace/log/ros2/latest.log
\`\`\`

**3. Dev-Server neu starten:**
\`\`\`bash
./tools/restart_dev_server.sh
\`\`\`

**4. Hot-Reload testen:**
\`\`\`bash
./tools/quick_test_hot_reload.sh
\`\`\`

### Wartung

**1. Logs aufräumen:**
\`\`\`bash
./tools/cleanup_thread_logs.sh
\`\`\`

**2. Zombie-Prozesse bereinigen:**
\`\`\`bash
./tools/cleanup_zombie_processes.sh
\`\`\`

**3. SSL-Zertifikate erneuern:**
\`\`\`bash
./tools/create_ssl_certificates.sh --name webserver --force
\`\`\`

---

## 🔗 Verwandte Dokumentationen

- Workspace Tools: \`/home/holgder/VOS2_WORKSPACE/tools/README.md\`
- Container Manager Tools: \`/home/holgder/VOS2_WORKSPACE/container_manager/tools/README.md\`
- Andere Module: \`../*/tools/README.md\`
- Frontend-Dokumentation: \`frontend/README.md\`
- Backend-Dokumentation: \`docs/BACKEND_README.md\`

---

## 🆘 Troubleshooting

### "Executable not found"

\`\`\`bash
# Debug-Informationen anzeigen
./tools/debug_executables.sh  # (v2_dashboard)

# Rebuild
colcon build --packages-select <MODULENAME>
source install/setup.bash
\`\`\`

### Dev-Server startet nicht

\`\`\`bash
# Server-Status prüfen
./tools/check_dev_server.sh

# Neu starten
./tools/restart_dev_server.sh

# Logs prüfen
docker exec <MODULENAME> cat /workspace/log/vite.log
\`\`\`

### Frontend-Build schlägt fehl

\`\`\`bash
# Dependencies neu installieren
cd frontend
rm -rf node_modules package-lock.json
npm install

# Build erneut versuchen
cd ..
./tools/build_frontend.sh
\`\`\`

### SSL-Zertifikat-Fehler

\`\`\`bash
# Neue Zertifikate generieren
./tools/create_ssl_certificates.sh --name webserver --force

# Nginx neu starten
docker exec <MODULENAME> nginx -s reload
\`\`\`

### Hot-Reload funktioniert nicht

\`\`\`bash
# Watchdog prüfen
./tools/quick_test_hot_reload.sh

# Manuell neu starten
docker exec -it <MODULENAME> bash
./tools/start_hot_reload.sh
\`\`\`

### ROS2-Interfaces werden nicht gefunden

\`\`\`bash
# Interfaces neu generieren
python3 tools/setup_interfaces.py

# Workspace neu bauen
colcon build --packages-select vyra_module_interfaces
source install/setup.bash

# ROS2-Node neu starten
./tools/startup_ros2_node.sh <MODULENAME> <nodename>
\`\`\`
