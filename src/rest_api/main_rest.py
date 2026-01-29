"""
Main REST API Application Template

Runnable FastAPI application template for VYRA modules.

CUSTOMIZATION POINTS:
1. Update app title, description, and version
2. Update URL prefix (/your_module_name/api)
3. Add your routers in the "Include routers" section
4. Add initialization/cleanup in lifespan context manager
"""
import logging
from contextlib import asynccontextmanager
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from .core.config import settings

logger = logging.getLogger(__name__)


@asynccontextmanager
async def lifespan(app: FastAPI):
    """
    Application lifespan context manager.
    
    CUSTOMIZE: Add your initialization and cleanup code here.
    """
    logger.info("🚀 Module REST API starting...")
    
    # TODO: Initialize services, clients, background tasks here
    # Example:
    # from .clients.http.hardware import hardware_registry_client
    # await hardware_registry_client.start()
    
    # from .clients.grpc.user_ipc import user_manager_grpc_client
    # await user_manager_grpc_client.ensure_connected()
    
    yield
    
    # Cleanup
    logger.info("🛑 Module REST API shutting down...")
    
    # TODO: Cleanup services, clients here
    # Example:
    # await hardware_registry_client.stop()


# Create FastAPI application
# CUSTOMIZE: Update title, description, version, and URL paths
app = FastAPI(
    title="Your Module REST API",  # CHANGE THIS
    description="Module-specific REST API",  # CHANGE THIS
    version="1.0.0",
    docs_url="/your_module/api/docs",  # CHANGE THIS
    redoc_url="/your_module/api/redoc",  # CHANGE THIS
    openapi_url="/your_module/api/openapi.json",  # CHANGE THIS
    lifespan=lifespan
)

# CORS middleware
app.add_middleware(
    CORSMiddleware,
    allow_origins=settings.cors_origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


# =============================================================================
# BASIC ENDPOINTS
# =============================================================================

@app.get("/")
@app.get("/your_module/api")  # CHANGE THIS
async def root():
    """API Root - available endpoints"""
    return {
        "service": "Your Module REST API",  # CHANGE THIS
        "version": "1.0.0",
        "endpoints": {
            "health": "/your_module/api/health",  # CHANGE THIS
            "docs": "/your_module/api/docs",  # CHANGE THIS
            "redoc": "/your_module/api/redoc",  # CHANGE THIS
        }
    }


@app.get("/health")
@app.get("/your_module/api/health")  # CHANGE THIS
async def health_check():
    """Health check endpoint"""
    return {
        "status": "healthy",
        "service": "your_module",  # CHANGE THIS
        "version": "1.0.0"
    }


# =============================================================================
# EXAMPLE ENDPOINT (Remove or replace with your own)
# =============================================================================

@app.get("/your_module/api/example")  # CHANGE THIS
async def example_endpoint():
    """Example endpoint demonstrating basic structure"""
    from .services.example_service import example_service
    
    items = await example_service.get_items(include_inactive=False)
    
    return {
        "message": "This is an example endpoint",
        "data": {
            "items": items
        }
    }


# =============================================================================
# INCLUDE YOUR ROUTERS HERE
# =============================================================================

# TODO: Import and include your module's routers
# CUSTOMIZE: Uncomment and modify for your module
# 
# from .example import router as example_router
# app.include_router(
#     example_router,
#     prefix="/your_module/api",  # CHANGE THIS
#     tags=["example"]
# )

# WebSocket example (optional)
# from .websocket.router import router as websocket_router
# app.include_router(
#     websocket_router,
#     prefix="/your_module/ws",  # CHANGE THIS
#     tags=["websocket"]
# )


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(
        "main_rest:app",
        host="0.0.0.0",
        port=8443,
        reload=True,
        ssl_certfile="/workspace/storage/certificates/server-cert.pem",
        ssl_keyfile="/workspace/storage/certificates/server-key.pem"
    )
