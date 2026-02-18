#!/bin/bash
# ==============================================================================
# publish_to_repo.sh - Publiziert ein Modul in das local_module_repository
# ==============================================================================
# Verwendung: ./tools/publish_to_repo.sh [REPO_PATH]
# ==============================================================================
set -e

MODULE_DIR=$(cd "$(dirname "$0")/.." && pwd)
REPO_PATH=${REPO_PATH:-"$MODULE_DIR/../../local_module_repository"}

# Resolve absolute path
REPO_PATH=$(cd "$REPO_PATH" 2>/dev/null && pwd) || {
    echo "❌ Repository nicht gefunden: $REPO_PATH"
    echo "   Setze REPO_PATH auf den lokalen Repository-Pfad oder übergib ihn als Argument:"
    echo "   REPO_PATH=/path/to/local_module_repository ./tools/publish_to_repo.sh"
    exit 1
}

if [ ! -f "$MODULE_DIR/.module/module_data.yaml" ]; then
    echo "❌ .module/module_data.yaml nicht gefunden in: $MODULE_DIR"
    exit 1
fi

# Extract module name (yq preferred, fallback to grep)
if command -v yq &>/dev/null; then
    MODULE_NAME=$(yq '.name' "$MODULE_DIR/.module/module_data.yaml")
else
    MODULE_NAME=$(grep "^name:" "$MODULE_DIR/.module/module_data.yaml" | cut -d: -f2 | tr -d ' "')
fi

if [ -z "$MODULE_NAME" ]; then
    echo "❌ Konnte MODULE_NAME nicht aus .module/module_data.yaml lesen"
    exit 1
fi

echo "📦 Publiziere Modul '$MODULE_NAME' ins Repository: $REPO_PATH"

SYNC_SCRIPT="$REPO_PATH/tools/sync_from_modules.sh"
if [ ! -f "$SYNC_SCRIPT" ]; then
    echo "❌ sync_from_modules.sh nicht gefunden: $SYNC_SCRIPT"
    exit 1
fi

"$SYNC_SCRIPT" "$(dirname "$MODULE_DIR")"
echo "✅ Modul '$MODULE_NAME' erfolgreich publiziert!"
