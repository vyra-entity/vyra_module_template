# VYRA Entrypoint Dependencies

Das `vyra_entrypoint.sh` wurde erweitert, um beim `VYRA_STARTUP_ACTIVE=true` automatisch verschiedene Dependencies zu installieren.

## 🔄 Installation-Reihenfolge

Wenn `VYRA_STARTUP_ACTIVE=true` gesetzt ist, werden folgende Dependencies installiert:

### 1. System-Pakete (APT)
- **Datei:** `.module/system-packages.txt`
- **Format:** Ein Paket pro Zeile, Kommentare mit `#`
- **Beispiel:**
  ```
  # Development Tools
  build-essential
  curl
  git
  vim
  ```

### 2. Node.js & npm (Latest LTS)
- **Automatisch:** Installation der neuesten LTS-Version über NodeSource
- **Fallback:** Wenn bereits installiert, wird übersprungen

### 3. Python Requirements (PIP)
- **Datei:** `.module/requirements.txt`
- **Format:** Standard pip requirements format
- **Beispiel:**
  ```
  flask==3.0.0
  gunicorn==23.0.0
  psutil>=5.9.0
  ```

### 4. Poetry Dependencies (Optional)
- **Datei:** `pyproject.toml`
- **Bedingung:** Nur wenn Poetry verfügbar ist
- **Konfiguration:** `virtualenvs.create false` für Container-Umgebung

### 5. VYRA Wheels
- **Dateien:** `wheels/*.whl`
- **Standard VYRA-Verhalten** (unverändert)

## 📁 Datei-Struktur

```
v2_dashboard/
├── .module/
│   ├── system-packages.txt    # APT-Pakete
│   └── requirements.txt       # Python-Pakete
├── pyproject.toml             # Poetry-Dependencies (optional)
├── wheels/                    # VYRA-Wheels
└── vyra_entrypoint.sh         # Erweitert mit Dependency-Installation
```

## 🚀 Verwendung

### Container-Start:
```bash
docker run -e VYRA_STARTUP_ACTIVE=true vyra_v2_dashboard
```

### Lokaler Test:
```bash
export VYRA_STARTUP_ACTIVE=true
./vyra_entrypoint.sh
```

## ✅ Features

- **Fehlerbehandlung:** Einzelne Pakete können fehlschlagen ohne Abbruch
- **Kompatibilität:** Abwärtskompatibel mit bestehendem VYRA-System
- **Flexibilität:** Jede Dependency-Kategorie ist optional
- **Aktuell:** Neueste npm/Node.js LTS Version
- **Logging:** Detaillierte Ausgaben für Debugging

## 🔧 Anpassung

Bearbeiten Sie die entsprechenden Dateien:

- **System-Pakete:** `.module/system-packages.txt`
- **Python-Pakete:** `.module/requirements.txt` oder `pyproject.toml`
- **Node.js-Version:** Anpassung in `vyra_entrypoint.sh` bei NodeSource URL

Das System ist nun bereit für automatische Dependency-Installation beim Container-Start!
