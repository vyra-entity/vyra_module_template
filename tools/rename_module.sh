#!/bin/bash

# ============================================================================
# VYRA Module Rename Script
# ============================================================================
# Benennt ein VYRA-Modul komplett um - alle Dateien, Verzeichnisse und Inhalte
#
# Verwendung:
#   ./tools/rename_module.sh <new_module_name> [--old_name=<old_name>]
#   ./tools/rename_module.sh  # Liest Namen aus .module/module_data.yaml
#
# Beispiele:
#   ./tools/rename_module.sh my_new_module
#   ./tools/rename_module.sh my_new_module --old_name=vyra_module_template
# ============================================================================

set -e  # Beende bei Fehler

# Farben für Ausgabe
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Funktionen für farbige Ausgabe
print_info() { echo -e "${BLUE}ℹ️  $1${NC}"; }
print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; exit 1; }

# ============================================================================
# Parameter verarbeiten
# ============================================================================

NEW_MODULE_NAME=""
OLD_MODULE_NAME="vyra_module_template"

# Prüfe ob Modulname als Parameter übergeben wurde
if [ -z "$1" ]; then
    # Versuche Namen aus .module/module_data.yaml zu lesen
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    MODULE_DATA_FILE="$SCRIPT_DIR/../.module/module_data.yaml"
    
    if [ -f "$MODULE_DATA_FILE" ]; then
        NEW_MODULE_NAME=$(grep "^name:" "$MODULE_DATA_FILE" | sed 's/^name:[[:space:]]*//' | tr -d '"' | tr -d "'")
        if [ -n "$NEW_MODULE_NAME" ]; then
            print_info "Kein Modulname übergeben, verwende Namen aus module_data.yaml: $NEW_MODULE_NAME"
        else
            print_error "Konnte Namen nicht aus $MODULE_DATA_FILE lesen"
        fi
    else
        print_error "Verwendung: $0 <new_module_name> oder .module/module_data.yaml muss existieren"
    fi
else
    NEW_MODULE_NAME=$1
    print_info "Verwende übergebenen Modulnamen: $NEW_MODULE_NAME"
fi

# Prüfe auf --old_name Parameter
for arg in "$@"; do
    if [[ "$arg" == "--old_name="* ]]; then
        OLD_MODULE_NAME="${arg#--old_name=}"
        break
    fi
done

# Validierung
if [ -z "$NEW_MODULE_NAME" ]; then
    print_error "Modulname darf nicht leer sein"
fi

if [ "$NEW_MODULE_NAME" = "$OLD_MODULE_NAME" ]; then
    print_warning "Neuer Name ist identisch mit altem Namen - keine Änderungen nötig"
    exit 0
fi

# Pfad zum Script-Verzeichnis
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MODULE_ROOT="$(dirname "$SCRIPT_DIR")"

echo ""
print_info "═══════════════════════════════════════════════════════════"
print_info "  VYRA Module Umbenennung"
print_info "═══════════════════════════════════════════════════════════"
echo "  Alt: $OLD_MODULE_NAME"
echo "  Neu: $NEW_MODULE_NAME"
echo "  Pfad: $MODULE_ROOT"
print_info "═══════════════════════════════════════════════════════════"
echo ""

# Bestätigung einholen
read -p "Fortfahren? (y/n) " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    print_warning "Abgebrochen"
    exit 0
fi

cd "$MODULE_ROOT"

# ============================================================================
# 1. Verzeichnisse umbenennen
# ============================================================================

print_info "Schritt 1: Verzeichnisse umbenennen..."

# Node-Verzeichnis im Package
NODE_DIR="src/$OLD_MODULE_NAME/$OLD_MODULE_NAME"
if [ -d "$NODE_DIR" ]; then
    print_success "Benenne Node-Verzeichnis um: $NODE_DIR → src/$OLD_MODULE_NAME/$NEW_MODULE_NAME"
    mv "$NODE_DIR" "src/$OLD_MODULE_NAME/$NEW_MODULE_NAME"
else
    print_warning "Node-Verzeichnis nicht gefunden: $NODE_DIR"
fi

# ROS2 Package-Verzeichnis
ROS2_PACKAGE_DIR="src/$OLD_MODULE_NAME"
if [ -d "$ROS2_PACKAGE_DIR" ]; then
    print_success "Benenne ROS2-Package um: $ROS2_PACKAGE_DIR → src/$NEW_MODULE_NAME"
    mv "$ROS2_PACKAGE_DIR" "src/$NEW_MODULE_NAME"
else
    print_warning "ROS2-Package-Verzeichnis nicht gefunden: $ROS2_PACKAGE_DIR"
fi

# Interface Package-Verzeichnis (vyra_module_interfaces → <module>_interfaces)
OLD_INTERFACE_DIR="src/vyra_module_interfaces"
NEW_INTERFACE_DIR="src/${NEW_MODULE_NAME}_interfaces"
if [ -d "$OLD_INTERFACE_DIR" ]; then
    print_success "Benenne Interface-Package um: $OLD_INTERFACE_DIR → $NEW_INTERFACE_DIR"
    mv "$OLD_INTERFACE_DIR" "$NEW_INTERFACE_DIR"
elif [ -d "src/${OLD_MODULE_NAME}_interfaces" ]; then
    print_success "Benenne Interface-Package um: src/${OLD_MODULE_NAME}_interfaces → $NEW_INTERFACE_DIR"
    mv "src/${OLD_MODULE_NAME}_interfaces" "$NEW_INTERFACE_DIR"
else
    print_warning "Interface-Package-Verzeichnis nicht gefunden: $OLD_INTERFACE_DIR"
fi

# ============================================================================
# 2. Konfigurationsdateien aktualisieren
# ============================================================================

print_info "Schritt 2: Konfigurationsdateien aktualisieren..."

# package.xml
PACKAGE_XML="src/$NEW_MODULE_NAME/package.xml"
if [ -f "$PACKAGE_XML" ]; then
    print_success "Aktualisiere $PACKAGE_XML"
    sed -i "s/<name>$OLD_MODULE_NAME<\/name>/<name>$NEW_MODULE_NAME<\/name>/g" "$PACKAGE_XML"
    sed -i "s|<description>.*</description>|<description>$NEW_MODULE_NAME - VYRA Module</description>|g" "$PACKAGE_XML"
else
    print_warning "Datei nicht gefunden: $PACKAGE_XML"
fi

# setup.py
SETUP_PY="src/$NEW_MODULE_NAME/setup.py"
if [ -f "$SETUP_PY" ]; then
    print_success "Aktualisiere $SETUP_PY"
    sed -i "s/package_name\s*=\s*['\"]$OLD_MODULE_NAME['\"]/package_name = '$NEW_MODULE_NAME'/g" "$SETUP_PY"
    sed -i "s/'$OLD_MODULE_NAME'/'$NEW_MODULE_NAME'/g" "$SETUP_PY"
    sed -i "s/\"$OLD_MODULE_NAME\"/\"$NEW_MODULE_NAME\"/g" "$SETUP_PY"
else
    print_warning "Datei nicht gefunden: $SETUP_PY"
fi

# setup.cfg
SETUP_CFG="src/$NEW_MODULE_NAME/setup.cfg"
if [ -f "$SETUP_CFG" ]; then
    print_success "Aktualisiere $SETUP_CFG"
    sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$SETUP_CFG"
else
    print_warning "Datei nicht gefunden: $SETUP_CFG"
fi

# pyproject.toml
PYPROJECT_FILE="pyproject.toml"
if [ -f "$PYPROJECT_FILE" ]; then
    print_success "Aktualisiere $PYPROJECT_FILE"
    # module_name in [tool.vyra] section
    sed -i "/^\[tool\.vyra\]/,/^\[/{s/module_name\s*=\s*.*/module_name = \"$NEW_MODULE_NAME\"/}" "$PYPROJECT_FILE"
    # name in [tool.poetry] section
    sed -i "/^\[tool\.poetry\]/,/^\[/{s/^name\s*=\s*.*/name = \"$NEW_MODULE_NAME\"/}" "$PYPROJECT_FILE"
else
    print_warning "Datei nicht gefunden: $PYPROJECT_FILE"
fi

# module_config.yaml
MODULE_CONFIG="src/$NEW_MODULE_NAME/resource/module_config.yaml"
if [ -f "$MODULE_CONFIG" ]; then
    print_success "Aktualisiere $MODULE_CONFIG"
    sed -i "s/^package_name:.*/package_name: $NEW_MODULE_NAME/" "$MODULE_CONFIG"
else
    print_warning "Datei nicht gefunden: $MODULE_CONFIG"
fi

# ROS2 Resource-Datei
RESOURCE_FILE_OLD="src/$NEW_MODULE_NAME/resource/$OLD_MODULE_NAME"
RESOURCE_FILE_NEW="src/$NEW_MODULE_NAME/resource/$NEW_MODULE_NAME"
if [ -f "$RESOURCE_FILE_OLD" ]; then
    print_success "Benenne Resource-Datei um: $RESOURCE_FILE_OLD → $RESOURCE_FILE_NEW"
    mv "$RESOURCE_FILE_OLD" "$RESOURCE_FILE_NEW"
else
    print_warning "Resource-Datei nicht gefunden: $RESOURCE_FILE_OLD"
fi

# .env Datei
ENV_FILE=".env"
if [ -f "$ENV_FILE" ]; then
    print_success "Aktualisiere $ENV_FILE"
    if grep -q "^MODULE_NAME=" "$ENV_FILE"; then
        sed -i "s/^MODULE_NAME=.*/MODULE_NAME=$NEW_MODULE_NAME/" "$ENV_FILE"
    else
        echo "MODULE_NAME=$NEW_MODULE_NAME" >> "$ENV_FILE"
    fi
else
    print_warning "Datei nicht gefunden: $ENV_FILE (wird ggf. später erstellt)"
fi

# .env.example
ENV_EXAMPLE=".env.example"
if [ -f "$ENV_EXAMPLE" ]; then
    print_success "Aktualisiere $ENV_EXAMPLE"
    if grep -q "^MODULE_NAME=" "$ENV_EXAMPLE"; then
        sed -i "s/^MODULE_NAME=.*/MODULE_NAME=$NEW_MODULE_NAME/" "$ENV_EXAMPLE"
    else
        echo "MODULE_NAME=$NEW_MODULE_NAME" >> "$ENV_EXAMPLE"
    fi
fi

# ============================================================================
# 3. Entrypoint und Runtime-Skripte
# ============================================================================

print_info "Schritt 3: Entrypoint und Runtime-Skripte aktualisieren..."

# vyra_entrypoint.sh
ENTRYPOINT="vyra_entrypoint.sh"
if [ -f "$ENTRYPOINT" ]; then
    print_success "Aktualisiere $ENTRYPOINT"
    sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$ENTRYPOINT"
fi

# startup_module.sh (falls vorhanden)
STARTUP_MODULE="tools/startup_module.sh"
if [ -f "$STARTUP_MODULE" ]; then
    print_success "Aktualisiere $STARTUP_MODULE"
    sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$STARTUP_MODULE"
fi

# ============================================================================
# 4. Python-Dateien durchsuchen und aktualisieren
# ============================================================================

print_info "Schritt 4: Python-Imports und Referenzen aktualisieren..."

# Finde alle Python-Dateien und aktualisiere Imports
PYTHON_FILES=$(find src -name "*.py" 2>/dev/null || true)
if [ -n "$PYTHON_FILES" ]; then
    for file in $PYTHON_FILES; do
        if grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
            print_success "Aktualisiere Python-Datei: $file"
            sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
        fi
    done
else
    print_warning "Keine Python-Dateien gefunden"
fi

# ============================================================================
# 5. Weitere Dateitypen aktualisieren
# ============================================================================

print_info "Schritt 5: Weitere Dateitypen aktualisieren..."

# YAML-Dateien
YAML_FILES=$(find . -name "*.yaml" -o -name "*.yml" 2>/dev/null | grep -v ".git" || true)
if [ -n "$YAML_FILES" ]; then
    for file in $YAML_FILES; do
        if grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
            print_success "Aktualisiere YAML-Datei: $file"
            sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
        fi
    done
fi

# JSON-Dateien
JSON_FILES=$(find . -name "*.json" 2>/dev/null | grep -v "node_modules" | grep -v ".git" || true)
if [ -n "$JSON_FILES" ]; then
    for file in $JSON_FILES; do
        if grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
            print_success "Aktualisiere JSON-Datei: $file"
            sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
        fi
    done
fi

# XML-Dateien (SROS2, Config, etc.)
XML_FILES=$(find . -name "*.xml" 2>/dev/null | grep -v ".git" || true)
if [ -n "$XML_FILES" ]; then
    for file in $XML_FILES; do
        if grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
            print_success "Aktualisiere XML-Datei: $file"
            sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
        fi
    done
fi

# TOML-Dateien
TOML_FILES=$(find . -name "*.toml" 2>/dev/null | grep -v ".git" || true)
if [ -n "$TOML_FILES" ]; then
    for file in $TOML_FILES; do
        if grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
            print_success "Aktualisiere TOML-Datei: $file"
            sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
        fi
    done
fi

# Shell-Skripte
SH_FILES=$(find tools -name "*.sh" 2>/dev/null || true)
if [ -n "$SH_FILES" ]; then
    for file in $SH_FILES; do
        # Überspringe dieses Script selbst
        if [ "$file" != "tools/rename_module.sh" ] && grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
            print_success "Aktualisiere Shell-Script: $file"
            sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
        fi
    done
fi

# Dockerfile
if [ -f "Dockerfile" ] && grep -q "$OLD_MODULE_NAME" "Dockerfile" 2>/dev/null; then
    print_success "Aktualisiere Dockerfile"
    sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "Dockerfile"
fi

# docker-compose Dateien
for dc_file in docker-compose.yml docker-compose.yaml docker-compose.*.yml docker-compose.*.yaml; do
    if [ -f "$dc_file" ] && grep -q "$OLD_MODULE_NAME" "$dc_file" 2>/dev/null; then
        print_success "Aktualisiere $dc_file"
        sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$dc_file"
    fi
done

# ============================================================================
# 5.5. Interface Package References aktualisieren
# ============================================================================

print_info "Schritt 5.5: Interface Package Referenzen aktualisieren..."

# Update vyra_module_interfaces → <module>_interfaces references
OLD_INTERFACE_NAME="vyra_module_interfaces"
if [ "$OLD_MODULE_NAME" != "vyra_module_template" ]; then
    OLD_INTERFACE_NAME="${OLD_MODULE_NAME}_interfaces"
fi
NEW_INTERFACE_NAME="${NEW_MODULE_NAME}_interfaces"

if [ "$OLD_INTERFACE_NAME" != "$NEW_INTERFACE_NAME" ]; then
    print_info "Ersetze $OLD_INTERFACE_NAME → $NEW_INTERFACE_NAME"
    
    # Python files
    PY_FILES=$(find src tools -name "*.py" 2>/dev/null | grep -v ".git" | grep -v "build/" || true)
    if [ -n "$PY_FILES" ]; then
        for file in $PY_FILES; do
            if grep -q "$OLD_INTERFACE_NAME" "$file" 2>/dev/null; then
                print_success "Aktualisiere Interface-Referenz in: $file"
                sed -i "s/$OLD_INTERFACE_NAME/$NEW_INTERFACE_NAME/g" "$file"
            fi
        done
    fi
    
    # XML files (package.xml, CMakeLists.txt)
    INTERFACE_XML_FILES=$(find src -name "package.xml" -o -name "CMakeLists.txt" -o -name "*.cmake" 2>/dev/null | grep -v "build/" || true)
    if [ -n "$INTERFACE_XML_FILES" ]; then
        for file in $INTERFACE_XML_FILES; do
            if grep -q "$OLD_INTERFACE_NAME" "$file" 2>/dev/null; then
                print_success "Aktualisiere Interface-Referenz in: $file"
                sed -i "s/$OLD_INTERFACE_NAME/$NEW_INTERFACE_NAME/g" "$file"
            fi
        done
    fi
    
    # setup.cfg
    if [ -f "src/$NEW_MODULE_NAME/setup.cfg" ] && grep -q "$OLD_INTERFACE_NAME" "src/$NEW_MODULE_NAME/setup.cfg" 2>/dev/null; then
        print_success "Aktualisiere Interface-Referenz in setup.cfg"
        sed -i "s/$OLD_INTERFACE_NAME/$NEW_INTERFACE_NAME/g" "src/$NEW_MODULE_NAME/setup.cfg"
    fi
    
    # ROS service/action definition files
    INTERFACE_DEF_FILES=$(find src -name "*.srv" -o -name "*.msg" -o -name "*.action" 2>/dev/null | grep -v "build/" || true)
    if [ -n "$INTERFACE_DEF_FILES" ]; then
        for file in $INTERFACE_DEF_FILES; do
            if grep -q "$OLD_INTERFACE_NAME" "$file" 2>/dev/null; then
                print_success "Aktualisiere Interface-Referenz in: $file"
                sed -i "s/$OLD_INTERFACE_NAME/$NEW_INTERFACE_NAME/g" "$file"
            fi
        done
    fi
fi

# ============================================================================
# 6. Frontend aktualisieren (falls vorhanden)
# ============================================================================

if [ -d "frontend" ]; then
    print_info "Schritt 6: Frontend aktualisieren..."
    
    # package.json
    if [ -f "frontend/package.json" ] && grep -q "$OLD_MODULE_NAME" "frontend/package.json" 2>/dev/null; then
        print_success "Aktualisiere frontend/package.json"
        sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "frontend/package.json"
    fi
    
    # TypeScript/JavaScript Dateien
    TS_JS_FILES=$(find frontend/src -name "*.ts" -o -name "*.js" -o -name "*.vue" -o -name "*.tsx" -o -name "*.jsx" 2>/dev/null || true)
    if [ -n "$TS_JS_FILES" ]; then
        for file in $TS_JS_FILES; do
            if grep -q "$OLD_MODULE_NAME" "$file" 2>/dev/null; then
                print_success "Aktualisiere Frontend-Datei: $file"
                sed -i "s/$OLD_MODULE_NAME/$NEW_MODULE_NAME/g" "$file"
            fi
        done
    fi
fi

# ============================================================================
# 7. Zusammenfassung
# ============================================================================

echo ""
print_info "═══════════════════════════════════════════════════════════"
print_success "Modul erfolgreich umbenannt!"
print_info "═══════════════════════════════════════════════════════════"
echo ""
print_info "Nächste Schritte:"
echo "  1. Überprüfen Sie die Änderungen:"
echo "     grep -r \"$OLD_MODULE_NAME\" . --exclude-dir=.git --exclude-dir=node_modules --exclude-dir=build"
echo ""
echo "  2. Testen Sie das Modul:"
echo "     docker compose build"
echo "     docker compose up -d"
echo ""
echo "  3. ROS2 Workspace neu bauen:"
echo "     docker exec -it $NEW_MODULE_NAME bash"
echo "     colcon build"
echo "     source install/setup.bash"
echo ""
print_success "Fertig!"
