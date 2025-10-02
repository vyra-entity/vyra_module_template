#!/bin/bash

# Vue.js Build Integration Script für VYRA Dashboard

set -e

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
PROJECT_ROOT="$SCRIPT_DIR/../../../.."
FRONTEND_DIR="$PROJECT_ROOT/frontend"
BACKEND_STATIC_DIR="$SCRIPT_DIR/../src/v2_dashboard/v2_dashboard/application/static"
BACKEND_TEMPLATES_DIR="$SCRIPT_DIR/../src/v2_dashboard/v2_dashboard/application/templates"

echo "🚀 VYRA Dashboard - Vue.js Build Integration"
echo "============================================="

# Prüfe ob Frontend-Verzeichnis existiert
if [ ! -d "$FRONTEND_DIR" ]; then
    echo "❌ Frontend-Verzeichnis nicht gefunden: $FRONTEND_DIR"
    echo "💡 Erstelle zunächst Ihr Vue.js Projekt in diesem Verzeichnis"
    exit 1
fi

# Wechsle ins Frontend-Verzeichnis
cd "$FRONTEND_DIR"

echo "📦 Installiere NPM Dependencies..."
if [ -f "package.json" ]; then
    npm install
else
    echo "❌ package.json nicht gefunden in $FRONTEND_DIR"
    exit 1
fi

echo "🔨 Baue Vue.js Projekt..."
npm run build

# Prüfe ob dist-Verzeichnis erstellt wurde
if [ ! -d "dist" ]; then
    echo "❌ Build fehlgeschlagen - dist-Verzeichnis nicht gefunden"
    exit 1
fi

echo "📂 Kopiere Build-Dateien zum Backend..."

# Erstelle Backend-Verzeichnisse falls sie nicht existieren
mkdir -p "$BACKEND_STATIC_DIR"
mkdir -p "$BACKEND_TEMPLATES_DIR"

# Kopiere dist-Inhalte
if [ -d "dist/assets" ]; then
    echo "📋 Kopiere Assets..."
    cp -r dist/assets/* "$BACKEND_STATIC_DIR/"
fi

if [ -f "dist/index.html" ]; then
    echo "📋 Kopiere index.html..."
    cp dist/index.html "$BACKEND_TEMPLATES_DIR/"
    
    # Aktualisiere Asset-Pfade in index.html für Flask
    sed -i 's|/assets/|/static/|g' "$BACKEND_TEMPLATES_DIR/index.html"
    
    echo "✅ Asset-Pfade angepasst für Flask"
fi

echo ""
echo "✅ Vue.js Build erfolgreich integriert!"
echo "🌐 Starte den VYRA Dashboard Server um das Frontend zu sehen"
echo ""

# Optional: Zeige Build-Statistiken
if [ -f "dist/index.html" ]; then
    echo "📊 Build-Statistiken:"
    echo "   HTML: $(wc -c < dist/index.html) Bytes"
    
    if [ -d "dist/assets" ]; then
        echo "   Assets: $(find dist/assets -type f | wc -l) Dateien"
        total_size=$(find dist/assets -type f -exec wc -c {} + | tail -1 | awk '{print $1}')
        echo "   Gesamtgröße: $total_size Bytes"
    fi
fi
