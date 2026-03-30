#!/bin/bash

# Changelog Manager Script
# Verwaltet eine CHANGELOG.md Datei im übergeordneten Verzeichnis

# Bestimme das übergeordnete Verzeichnis
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARENT_DIR="$(dirname "$SCRIPT_DIR")"
CHANGELOG_FILE="$PARENT_DIR/CHANGELOG.md"

# Farben für bessere Lesbarkeit (optional)
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Funktion: Changelog initialisieren
init_changelog() {
    if [ ! -f "$CHANGELOG_FILE" ]; then
        echo "# Changelog" > "$CHANGELOG_FILE"
        echo "" >> "$CHANGELOG_FILE"
        echo "Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert." >> "$CHANGELOG_FILE"
        echo "" >> "$CHANGELOG_FILE"
        echo -e "${GREEN}✓ Neue CHANGELOG.md erstellt: $CHANGELOG_FILE${NC}"
    else
        echo -e "${BLUE}ℹ CHANGELOG.md existiert bereits: $CHANGELOG_FILE${NC}"
    fi
}

# Funktion: Eintrag hinzufügen
add_entry() {
    local entry="$1"
    local timestamp=$(date '+%Y-%m-%d %H:%M:%S')
    local date_only=$(date '+%Y-%m-%d')
    
    # Temporäre Datei für die Bearbeitung
    local temp_file=$(mktemp)
    
    # Prüfe, ob heute bereits ein Abschnitt existiert
    if grep -q "## \[$date_only\]" "$CHANGELOG_FILE"; then
        # Füge zum existierenden Tagesabschnitt hinzu
        awk -v date="## [$date_only]" -v entry="- [$timestamp] - $entry" '
        {
            print
            if ($0 == date && !inserted) {
                print entry
                inserted=1
            }
        }' "$CHANGELOG_FILE" > "$temp_file"
    else
        # Erstelle neuen Tagesabschnitt
        # Finde die erste Zeile nach dem Header (nach Zeile 3) und füge dort ein
        awk -v date="$date_only" -v timestamp="$timestamp" -v entry="$entry" '
        BEGIN { inserted=0 }
        {
            if (NR == 4 && !inserted) {
                print "## [" date "]"
                print "- [" timestamp "] - " entry
                print ""
                inserted=1
            }
            print
        }' "$CHANGELOG_FILE" > "$temp_file"
    fi
    
    # Ersetze die Original-Datei
    mv "$temp_file" "$CHANGELOG_FILE"
    
    echo -e "${GREEN}✓ Eintrag hinzugefügt${NC}"
}

# Funktion: Changelog anzeigen
show_changelog() {
    if [ -f "$CHANGELOG_FILE" ]; then
        echo -e "${BLUE}=== Aktueller Changelog ===${NC}"
        cat "$CHANGELOG_FILE"
    else
        echo "Keine CHANGELOG.md gefunden."
    fi
}

# Hauptprogramm
main() {
    # Initialisiere Changelog
    init_changelog
    
    echo ""
    echo "=== Changelog Manager ==="
    echo ""
    echo "Was wurde erledigt? (Beende mit Strg+D)"
    echo ""
    
    # Lese mehrzeilige Eingabe
    NEW_LOG=$(cat)
    
    # Prüfe, ob Eingabe vorhanden ist
    if [ -n "$NEW_LOG" ]; then
        add_entry "$NEW_LOG"
    else
        echo ""
        echo "Kein Eintrag angegeben. Abbruch."
        exit 1
    fi
}

# Starte das Programm
main
