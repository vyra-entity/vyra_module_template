from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse, FileResponse
from fastapi.staticfiles import StaticFiles
import os
from pathlib import Path
from typing import Optional

# FastAPI-App als reine API (ohne Templates)
app = FastAPI(
    title="Fast API Interface",
    version="0.1.0",
    description="Modern async API for VYRA Module Management",
    docs_url="/api/docs",  # Swagger UI
    redoc_url="/api/redoc"  # ReDoc
)

# Pfad zum Vue.js Build-Output (nur für Fallback in Development)
FRONTEND_DIST_PATH = Path(__file__).parent.parent.parent.parent.parent.parent / "frontend" / "dist"

# Mount static directories if they exist
if (FRONTEND_DIST_PATH / "static").exists():
    app.mount("/static", StaticFiles(directory=str(FRONTEND_DIST_PATH / "static")), name="static")

if (FRONTEND_DIST_PATH / "assets").exists():
    app.mount("/assets", StaticFiles(directory=str(FRONTEND_DIST_PATH / "assets")), name="assets")


@app.get("/")
async def root():
    """API Root - zeigt verfügbare Endpoints"""
    return {
        "service": "VYRA Module Template API",
        "version": "0.1.0",
        "endpoints": {
            "status": "/api/status",
            "modules": "/api/modules",
            "docs": "/api/docs",
            "redoc": "/api/redoc",
            "frontend": "Managed by Nginx (Production) or Vue Dev Server (Development)"
        }
    }


@app.get("/dashboard")
@app.get("/dashboard/{path:path}")
async def dashboard(path: Optional[str] = None):
    """Frontend-Weiterleitung - sollte nur in Notfällen erreicht werden"""
    return {
        "message": "Frontend wird durch Nginx oder Vue Dev Server bereitgestellt",
        "redirect": "http://localhost:3000"
    }


# API Routes für Vue.js Frontend
@app.get("/api/status")
async def api_status():
    """Health check und Status-Information"""
    return {
        "status": "running",
        "service": "v2_dashboard",
        "version": "0.1.0",
        "frontend": "Vue.js SPA"
    }


@app.get("/api/modules")
async def api_list_modules():
    """API für Vue.js - Modulverwaltung"""
    return {
        "modules": [
            {"name": "v2_modulemanager", "status": "running", "version": "1.0.0"},
            {"name": "v2_dashboard", "status": "running", "version": "0.1.0"}
        ],
        "total": 2
    }


@app.get("/api/modules/{module_name}")
async def api_get_module(module_name: str):
    """API für Vue.js - Einzelnes Modul abrufen"""
    return {
        "name": module_name,
        "status": "running",
        "version": "1.0.0",
        "config": {},
        "logs": []
    }


@app.post("/api/modules/{module_name}")
async def api_update_module(module_name: str, request: Request):
    """API für Vue.js - Modul aktualisieren"""
    data = await request.json()
    return {
        "message": f"Module {module_name} updated",
        "data": data
    }


@app.get("/health")
async def health_check():
    """Health check endpoint for monitoring"""
    return {"status": "healthy", "service": "v2_dashboard"}


# Note: App is now served via asgi.py + uvicorn + supervisord (FastAPI native ASGI)
