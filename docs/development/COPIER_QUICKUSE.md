# Copier Quickuse — VYRA Module Template

Dieses Dokument beschreibt, wie du mit [Copier](https://copier.readthedocs.io/) neue VYRA-Module erstellst, bestehende Module auf den neuesten Template-Stand bringst und die weiteren Tools des Templates nutzt.

---

## Voraussetzungen

```bash
pip install copier
# Optional, aber empfohlen für publish_to_repo.sh
pip install yq
```

---

## 1. Neues Modul erstellen

### Interaktiv (empfohlen)

```bash
copier copy /home/holgder-dach/VYRA/vyra_module_template /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_<hash>
```

Copier fragt Schritt für Schritt ab:

```
🎤 Modul-Name (snake_case, z.B. my_detector)
   > my_detector

🎤 Anzeigename (z.B. My Detector Module)
   > My Detector Module

🎤 Kurze Beschreibung des Moduls
   > Erkennt Objekte im Kamerabild

🎤 Dein Name
   > Max Mustermann

🎤 Deine E-Mail-Adresse
   > max@example.com

🎤 Soll ein Vue.js-Frontend eingebunden werden? [Y/n]
   > Y

🎤 Soll VYRA_DEV_MODE=true als Standard gesetzt werden? [Y/n]
   > Y

🎤 Soll VYRA_SLIM=true als Standard gesetzt werden? [y/N]
   > N
```

### Nicht-interaktiv (CI / Skripte)

```bash
copier copy /home/holgder-dach/VYRA/vyra_module_template /tmp/my_detector \
  --data module_name=my_detector \
  --data module_display_name="My Detector Module" \
  --data module_description="Erkennt Objekte im Kamerabild" \
  --data author_name="Max Mustermann" \
  --data author_email="max@example.com" \
  --data enable_frontend=true \
  --data enable_dev_mode=true \
  --data enable_slim_mode=false
```

### Ergebnis

Nach dem Kopiervorgang liegen **alle** Template-Variablen bereits ausgefüllt vor:

```
my_detector/
├── src/my_detector/my_detector/   # Python-Paket
├── src/my_detector_interfaces/    # ROS2-Interfaces
├── frontend/                      # Vue.js (wenn enable_frontend=true)
├── config/nginx.conf
├── .env                           # MODULE_NAME=my_detector
├── .module/module_data.yaml       # Modul-Metadaten
├── .copier-answers.yml            # Gespeicherte Antworten (nicht committen)
├── tools/publish_to_repo.sh
└── ...
```

> **Hinweis**: `.copier-answers.yml` ist in `.gitignore` eingetragen und enthält alle gespeicherten Template-Antworten für spätere Updates.

---

## 2. Bestehendes Modul auf neuen Template-Stand bringen (`copier update`)

Wenn das Template aktualisiert wurde (z. B. neue Files, geänderte Config-Defaults), kannst du die Änderungen in dein bestehendes Modul übernehmen — ohne deine eigenen Anpassungen zu verlieren.

### Voraussetzung

Die Datei `.copier-answers.yml` muss im Modulverzeichnis vorhanden sein (wird beim ersten `copier copy` automatisch erstellt).

### Update ausführen

```bash
cd /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_<hash>
copier update
```

Copier:
1. Liest die gespeicherten Antworten aus `.copier-answers.yml`
2. Berechnet das Diff zwischen altem und neuem Template-Stand
3. Wendet nur die **Änderungen** an — deine eigenen Modifikationen bleiben erhalten
4. Zeigt Konflikte als `*.rej`-Dateien an, die du manuell lösen kannst

### Update mit geänderter Template-Quelle

```bash
# Wenn das Template an einem anderen Pfad liegt:
copier update --defaults --trust \
  /home/holgder-dach/VYRA/vyra_module_template
```

### Konflikte lösen

```bash
# Zeigt alle Konflikt-Dateien:
find . -name "*.rej"

# Nach dem Lösen:
rm **/*.rej
git add -A
git commit -m "chore: apply template update"
```

---

## 3. Template-Variablen nachträglich ändern

Willst du z. B. den Autor-Namen korrigieren oder ein Feature nachträglich aktivieren:

```bash
cd /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_<hash>
copier update --overwrite
```

Mit `--overwrite` fragt Copier alle Variablen erneut ab (Standardwerte aus `.copier-answers.yml` vorausgefüllt) und überschreibt die generierten Dateien.

Oder gezielt eine Variable überschreiben:

```bash
copier update --overwrite --data enable_frontend=false
```

---

## 4. Modul ins lokale Repository publizieren

Nachdem das Modul erstellt oder aktualisiert wurde, kann es im `local_module_repository` registriert werden:

```bash
cd /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_<hash>
./tools/publish_to_repo.sh
```

Das Skript:
1. Liest `MODULE_NAME` aus `.module/module_data.yaml`
2. Ruft `local_module_repository/tools/sync_from_modules.sh` auf
3. Synchronisiert das Modul ins Repository

Alternativer Repository-Pfad:

```bash
REPO_PATH=/custom/path/to/local_module_repository ./tools/publish_to_repo.sh
```

> **Hinweis**: Template-Module (Name enthält `template`) werden vom Sync-Skript automatisch übersprungen.

---

## 5. Jinja2-Variablen im Überblick

| Variable | Beispiel-Wert | Verwendung |
|---|---|---|
| `{{ module_name }}` | `my_detector` | Verzeichnisnamen, Imports, Pakete |
| `{{ module_display_name }}` | `My Detector Module` | README, API-Titel |
| `{{ module_description }}` | `Erkennt Objekte...` | README, Metadaten |
| `{{ author_name }}` | `Max Mustermann` | pyproject.toml, Metadaten |
| `{{ author_email }}` | `max@example.com` | pyproject.toml, Metadaten |
| `{{ module_name \| replace('_', '-') }}` | `my-detector` | Poetry-Entrypoint-Name |
| `{{ module_name \| title \| replace('_','') }}` | `MyDetector` | Klassenname (PascalCase) |

### Feature-Flags

| Flag | Default | Effekt |
|---|---|---|
| `enable_frontend` | `true` | Schließt `frontend/` und `config/nginx.conf` ein |
| `enable_dev_mode` | `true` | Setzt `VYRA_DEV_MODE=true` in `.env` |
| `enable_slim_mode` | `false` | Setzt `VYRA_SLIM=true` in `.env` (kein ROS2) |

---

## 6. Typische Workflows

### Workflow A — Schnellstart neues Modul

```bash
# 1. Modul aus Template generieren
copier copy /home/holgder-dach/VYRA/vyra_module_template \
  /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_$(python3 -c "import uuid; print(uuid.uuid4().hex)")

# 2. Ins Modulverzeichnis wechseln
cd /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_*

# 3. Git initialisieren
git init && git add -A && git commit -m "feat: initial module from template"

# 4. Im Repository registrieren
./tools/publish_to_repo.sh
```

### Workflow B — Template-Update einspielen

```bash
# 1. Template aktualisieren (git pull im Template-Repo)
cd /home/holgder-dach/VYRA/vyra_module_template
git pull

# 2. Update ins Modul übernehmen
cd /home/holgder-dach/VOS2_WORKSPACE/modules/my_detector_<hash>
copier update

# 3. Konflikte prüfen und lösen
find . -name "*.rej"

# 4. Committen
git add -A && git commit -m "chore: template update $(date +%Y-%m-%d)"
```

### Workflow C — Modul ohne Frontend (Slim)

```bash
copier copy /home/holgder-dach/VYRA/vyra_module_template /tmp/my_slim_module \
  --data module_name=my_slim_module \
  --data module_description="Slim backend-only module" \
  --data author_name="Dev" \
  --data author_email="dev@example.com" \
  --data enable_frontend=false \
  --data enable_slim_mode=true
```

---

## 7. Fehlerbehandlung

### `copier update` findet keine Antwortdatei

```
ERROR: .copier-answers.yml not found
```

→ Führe einmalig `copier copy ... --overwrite` aus, um `.copier-answers.yml` zu erzeugen.

### Validator-Fehler beim Modul-Namen

```
Nur Kleinbuchstaben, Zahlen und Unterstriche erlaubt
```

→ `module_name` muss `snake_case` sein: `my_module` ✅, `MyModule` ❌, `my-module` ❌

### Konflikt-Dateien nach Update

```bash
# Alle Konflikt-Dateien anzeigen:
find . -name "*.rej" -type f

# Inhalt prüfen (zeigt was Copier wollte, aber nicht anwenden konnte):
cat src/my_detector/my_detector/application/application.py.rej
```

---

## Weiterführende Dokumentation

- [docs/GIT_TEMPLATE_AS_UPSTREAM_GUIDE.md](GIT_TEMPLATE_AS_UPSTREAM_GUIDE.md) — Alternative: Template als git upstream
- [docs/MODULE_REPOSITORY.md](MODULE_REPOSITORY.md) — local_module_repository Details
- [docs/BUILD_SYSTEM.md](BUILD_SYSTEM.md) — Colcon Build & Docker
- [Copier Dokumentation](https://copier.readthedocs.io/)
