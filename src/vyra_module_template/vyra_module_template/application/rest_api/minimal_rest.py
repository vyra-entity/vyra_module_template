from flask import Flask, request, jsonify, send_from_directory
import base64
import os
from pathlib import Path

# Flask-App als reine API (ohne Templates)
app = Flask(__name__, static_folder='static')

# Pfad zum Vue.js Build-Output (nur für Fallback in Development)
FRONTEND_DIST_PATH = Path(__file__).parent.parent.parent.parent.parent.parent / "frontend" / "dist"

@app.route("/", methods=["GET"])
def root():
    """API Root - zeigt verfügbare Endpoints"""
    return jsonify({
        "service": "VYRA Module Dashboard API",
        "version": "0.1.0",
        "endpoints": {
            "status": "/api/status",
            "modules": "/api/modules",
            "frontend": "Managed by Nginx (Production) or Vue Dev Server (Development)"
        }
    })

if __name__ == "__main__":
    # HTTPS aktivieren (selbst-signiertes Zertifikat oder echtes TLS)
    # Um ein selbst-signiertes Zertifikat und einen privaten Schlüssel zu erstellen, führe folgenden Befehl im Terminal aus:
    # openssl req -x509 -newkey rsa:4096 -keyout webserver.key -out webserver.crt -days 365 -nodes -subj "/CN=localhost"
    # Dadurch werden die Dateien webserver.crt (Zertifikat) und webserver.key (privater Schlüssel) im aktuellen Verzeichnis erstellt.
    app.run(host="0.0.0.0", port=8443, ssl_context=("webserver.crt", "webserver.key"))
