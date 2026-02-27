#!/usr/bin/env python3
"""
ASGI entry point for Backend Webserver

This module loads the FastAPI application from the backend_webserver package.
The backend communicates with core application components via dependency injection
(container_injection) instead of gRPC.
"""

import sys
import os
from ..logging_config import get_logger

# Setup logging via the shared VYRA logging_config (same as v2_modulemanager)
# logging_config reads core_logging.json and configures the root logger on import
logger = get_logger(__name__)

# Import FastAPI application from main_rest module
try:
    from .main_rest import app as application
    logger.info("✅ Successfully loaded FastAPI application from backend_webserver")
except ImportError as e:
    logger.exception(f"❌ Error importing FastAPI application: {e}")
    
    # Create minimal error ASGI app
    async def application(scope, receive, send):
        if scope['type'] == 'http':
            await send({
                'type': 'http.response.start',
                'status': 500,
                'headers': [[b'content-type', b'application/json']],
            })
            await send({
                'type': 'http.response.body',
                'body': f'{{"error": "Could not import backend_webserver: {e}"}}'.encode('utf-8'),
            })
    
    logger.error("Using fallback error application")

if __name__ == "__main__":
    # Direct development testing with Uvicorn
    import uvicorn
    
    cert_path = "/workspace/storage/certificates/webserver.crt"
    key_path = "/workspace/storage/certificates/webserver.key"
    
    # Get module name dynamically
    module_name = os.getenv('MODULE_NAME', '{{ module_name }}')
    app_path = f"{module_name}.{module_name}.backend_webserver.asgi:application"
    
    # Check for SSL certificates
    if os.path.exists(cert_path) and os.path.exists(key_path):
        logger.info("🔒 Starting with SSL/TLS encryption")
        uvicorn.run(
            app_path,
            host="0.0.0.0",
            port=8443,
            reload=True,
            reload_dirs=[f"/workspace/src/{module_name}/{module_name}/backend_webserver"],
            log_level="debug",
            ssl_certfile=cert_path,
            ssl_keyfile=key_path
        )
    else:
        logger.warning("⚠️ SSL certificates not found, starting without encryption")
        logger.info(f"   Expected: {cert_path} and {key_path}")
        uvicorn.run(
            app_path,
            host="0.0.0.0",
            port=8000,
            reload=True,
            reload_dirs=[f"/workspace/src/{module_name}/{module_name}/backend_webserver"],
            log_level="debug"
        )
