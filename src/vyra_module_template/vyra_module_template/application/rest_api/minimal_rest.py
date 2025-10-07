from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse, FileResponse
from fastapi.staticfiles import StaticFiles
import os
from pathlib import Path
from typing import Optional

# FastAPI-App als reine API (ohne Templates)
app = FastAPI(
    title="VYRA Module Manager API",
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
        "service": "VYRA Module Manager API",
        "version": "0.1.0",
        "endpoints": {
            "status": "/api/status",
            "modules": "/api/modules",
            "docs": "/api/docs",
            "redoc": "/api/redoc",
            "frontend": "Managed by Nginx (Production) or Vue Dev Server (Development)"
        }
    }


@app.get("/health")
async def health_check():
    """Health check endpoint for monitoring"""
    return {"status": "healthy", "service": "v2_dashboard"}


# Note: App is now served via asgi.py + uvicorn + supervisord (FastAPI native ASGI)
