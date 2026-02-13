"""
FastAPI Main Application - Backend Webserver

This is the main FastAPI application for the VYRA module.
Customize this file to add your module-specific endpoints and functionality.
"""

import logging
import os
from contextlib import asynccontextmanager

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

logger = logging.getLogger(__name__)

# Get module name from environment
MODULE_NAME = os.getenv('MODULE_NAME', 'vyra_module_template')


@asynccontextmanager
async def lifespan(app: FastAPI):
    """
    Application lifespan manager
    
    Startup: Initialize connections, start background tasks
    Shutdown: Clean up resources, close connections
    """
    # Startup
    logger.info(f"🚀 {MODULE_NAME} Backend Webserver starting up...")
    
    # TODO: Add your startup logic here
    # Examples:
    # - Initialize database connections
    # - Start background tasks
    # - Load configuration
    
    yield
    
    # Shutdown
    logger.info(f"🛑 {MODULE_NAME} Backend Webserver shutting down...")
    
    # TODO: Add your shutdown logic here
    # Examples:
    # - Close database connections
    # - Stop background tasks
    # - Save state


# Create FastAPI application
app = FastAPI(
    title=f"{MODULE_NAME} API",
    description=f"REST API for {MODULE_NAME} module",
    version="0.1.0",
    docs_url=f"/api/{MODULE_NAME}/docs",
    redoc_url=f"/api/{MODULE_NAME}/redoc",
    openapi_url=f"/api/{MODULE_NAME}/openapi.json",
    lifespan=lifespan
)

# CORS Middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # TODO: Configure for production
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/")
async def root():
    """Root endpoint"""
    return {
        "service": f"{MODULE_NAME} Backend Webserver",
        "version": "0.1.0",
        "status": "running"
    }


@app.get("/health")
async def health():
    """Health check endpoint"""
    return {
        "status": "healthy",
        "service": MODULE_NAME
    }


# TODO: Add your routers here
# Example:
# from .routes import my_router
# app.include_router(my_router, prefix=f"/api/{MODULE_NAME}/my_endpoint", tags=["My Endpoint"])


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
