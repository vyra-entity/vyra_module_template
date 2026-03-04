### Update permission file on change

```bash
#!/usr/bin/env bash
#
# Signiere eine ROS2 Permissions-Datei mit OpenSSL SMIME.
# Nutzung: ./sign_permissions.sh --dir /pfad/zum/verzeichnis
#

set -euo pipefail

# === Parameter einlesen ===
DIR=""
while [[ $# -gt 0 ]]; do
    case "$1" in
        --dir)
            DIR="$2"
            shift 2
            ;;
        *)
            echo "Unbekannter Parameter: $1" >&2
            exit 1
            ;;
    esac
done

# === Validierung ===
if [[ -z "$DIR" ]]; then
    echo "Fehler: --dir Parameter fehlt." >&2
    exit 1
fi

# Absoluten Pfad erzeugen
DIR="$(realpath "$DIR")"

XML_FILE="$DIR/permissions.xml"
OUT_FILE="$DIR/permissions.p7s"
CERT_FILE="permissions_ca.cert.pem"
KEY_FILE="$HOME/VOS2_WORKSPACE/sros2_tests/sros2_ca/keystore/private/permissions_ca.key.pem"

if [[ ! -f "$XML_FILE" ]]; then
    echo "Fehler: $XML_FILE existiert nicht." >&2
    exit 1
fi

if [[ ! -f "$CERT_FILE" ]]; then
    echo "Fehler: Zertifikat $CERT_FILE nicht gefunden." >&2
    exit 1
fi

if [[ ! -f "$KEY_FILE" ]]; then
    echo "Fehler: Key $KEY_FILE nicht gefunden." >&2
    exit 1
fi

# === Signieren ===
echo "Signiere $XML_FILE ..."
openssl smime -sign -text \
    -in "$XML_FILE" \
    -out "$OUT_FILE" \
    --signer "$CERT_FILE" \
    -inkey "$KEY_FILE"

echo "Fertig: Signatur gespeichert in $OUT_FILE"
```



