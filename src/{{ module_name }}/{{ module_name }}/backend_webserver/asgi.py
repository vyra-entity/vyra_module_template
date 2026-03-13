#!/usr/bin/env python3
"""
ASGI entry point for Backend Webserver

This module loads the FastAPI application from the backend_webserver package.
The backend communicates with core application components via dependency injection
(container_injection) instead of gRPC.
"""

import sys
import os
from ..logging_config import get_logger, log_exception, log_function_call, log_function_result
import logging.config
import json

# Configure logging for the application
def setup_logging():
    """Setup logging configuration with ENV variable support"""
    log_config_path = "/workspace/config/backend_webserver_logging.json"
    
    # Get logging format from ENV variable
    logging_format = os.getenv('LOGGING_FORMAT', '%(asctime)s - %(levelname)-8s - %(name)s - %(message)s')
    log_level = os.getenv("LOG_LEVEL", "INFO").upper()


    if os.path.exists(log_config_path):
        try:
            with open(log_config_path, 'r') as f:
                config = json.load(f)
            
            # Override format strings with ENV variable
            for formatter_name, formatter_config in config.get('formatters', {}).items():
                if 'format' in formatter_config:
                    formatter_config['format'] = logging_format
            
            logging.config.dictConfig(config)
            logging.getLogger().setLevel(log_level)
            print(f"✅ Logging configured from {log_config_path} with ENV format")
        except Exception as e:
            print(f"⚠️ Failed to load logging config: {e}")
            logging.basicConfig(
                level=logging.INFO,
                format=logging_format
            )
    else:
        print(f"ℹ️ Webserver backend logging config not found at {log_config_path}, "
              f"using basic config, and log webserver logs in core logs")
        logging.basicConfig(
            level=logging.INFO,
            format=logging_format,
            handlers=[
                logging.StreamHandler(),
            ]
        )

# Setup logging as early as possible
setup_logging()
logger = get_logger(__name__)

# Import FastAPI application from main_rest module
try:
    from .main_rest import app as application
    logger.info("✅ Successfully loaded FastAPI application from backend_webserver")
except ImportError as e:
    log_exception(logger, e, context={"message": "❌ Error importing FastAPI application: {e}"})
    
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
            reload_dirs=["/workspace/src/{{ module_name }}/{{ module_name }}/backend_webserver"],
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
            reload_dirs=["/workspace/src/{{ module_name }}/{{ module_name }}/backend_webserver"],
            log_level="debug"
        )
