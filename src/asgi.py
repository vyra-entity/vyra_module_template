#!/usr/bin/env python3
"""
ASGI entry point for VYRA modules
This file dynamically loads the application based on MODULE_NAME from .env
Supports FastAPI and other native ASGI frameworks (Starlette, Quart, etc.)
"""

import sys
import os
import importlib
import logging
import logging.config
import json
from typing import Optional

# Add the src directory to Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

# Configure logging for the application
def setup_logging():
    """Setup logging configuration with ENV variable support"""
    log_config_path = "/workspace/config/uvicorn_logging.json"
    
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
        print(f"⚠️ Logging config not found at {log_config_path}, using basic config")
        logging.basicConfig(
            level=logging.INFO,
            format=logging_format,
            handlers=[
                logging.StreamHandler(),
                logging.FileHandler('/workspace/log/uvicorn/application.log')
            ]
        )

# Setup logging as early as possible
setup_logging()
logger = logging.getLogger(__name__)

def load_env_file() -> Optional[str]:
    """Load MODULE_NAME from .env file"""
    env_file = "/workspace/.env"
    module_name = None
    
    try:
        with open(env_file, 'r') as f:
            for line in f:
                line = line.strip()
                if line.startswith('MODULE_NAME='):
                    module_name = line.split('=', 1)[1]
                    break
    except FileNotFoundError:
        print(f"Warning: {env_file} not found")
    
    return module_name

def create_error_app(error_message: str):
    """Create a minimal ASGI app for error display"""
    async def app(scope, receive, send):
        if scope['type'] == 'http':
            await send({
                'type': 'http.response.start',
                'status': 500,
                'headers': [
                    [b'content-type', b'application/json'],
                ],
            })
            await send({
                'type': 'http.response.body',
                'body': f'{{"error": "{error_message}"}}'.encode('utf-8'),
            })
    return app

def is_asgi_app(app) -> bool:
    """Check if the app is an ASGI application (FastAPI, Starlette, etc.)"""
    # FastAPI and Starlette apps have these attributes
    return (
        hasattr(app, 'routes') or 
        hasattr(app, '__call__') and 
        app.__code__.co_argcount >= 3  # ASGI apps have (scope, receive, send)
    )

# Load module name from .env
module_name = load_env_file()

if not module_name:
    logger.error("MODULE_NAME not found in .env file")
    application = create_error_app("MODULE_NAME not found in .env file")
else:
    try:
        # Try to import the REST API module (new location: src/rest_api/)
        module_path = "src.rest_api.main_rest"
        logger.info(f"Attempting to import: {module_path}")
        
        module = importlib.import_module(module_path)
        
        # Check if module has an ASGI app
        if hasattr(module, 'app'):
            app_obj = getattr(module, 'app')
            
            # Validate it's an ASGI app
            if is_asgi_app(app_obj):
                application = app_obj
                logger.info(f"✅ Successfully loaded {module_name} ASGI application (FastAPI/Starlette)")
            else:
                raise AttributeError(f"'app' object is not a valid ASGI application")
        
        # Legacy support: explicit asgi_app export
        elif hasattr(module, 'asgi_app'):
            application = getattr(module, 'asgi_app')
            logger.info(f"✅ Successfully loaded {module_name} ASGI application")
        
        else:
            raise AttributeError("No 'app' or 'asgi_app' found in module")
        
    except (ImportError, AttributeError) as e:
        logger.exception(f"❌ Error importing {module_name} application: {e}")
        
        # Try legacy path (old location inside v2_modulemanager)
        try:
            alt_module_path = f"src.{module_name}.{module_name}.application.rest_api.main_rest"
            logger.info(f"Trying legacy import: {alt_module_path}")
            
            module = importlib.import_module(alt_module_path)
            
            # Check for ASGI app
            if hasattr(module, 'app'):
                app_obj = getattr(module, 'app')
                
                if is_asgi_app(app_obj):
                    application = app_obj
                    logger.info(f"✅ Successfully loaded {module_name} ASGI application (alternative path)")
                else:
                    raise AttributeError(f"'app' object is not a valid ASGI application")
            
            elif hasattr(module, 'asgi_app'):
                application = getattr(module, 'asgi_app')
                logger.info(f"✅ Successfully loaded {module_name} ASGI application (alternative path)")
            
            else:
                raise AttributeError("No 'app' or 'asgi_app' found in module")
            
        except (ImportError, AttributeError) as e2:
            logger.exception(f"❌ Error with alternative import: {e2}")
            application = create_error_app(f"Could not import {module_name}: {e} | Alternative: {e2}")

if __name__ == "__main__":
    # Direct development testing with Uvicorn
    import uvicorn
    
    cert_path = "/workspace/storage/certificates/webserver.crt"
    key_path = "/workspace/storage/certificates/webserver.key"
    
    # Check for SSL certificates
    if os.path.exists(cert_path) and os.path.exists(key_path):
        logger.info("🔒 Starting with SSL/TLS encryption")
        uvicorn.run(
            "asgi:application",
            host="0.0.0.0",
            port=8443,
            reload=True,
            reload_dirs=["/workspace/src"],
            log_level="debug",
            ssl_certfile=cert_path,
            ssl_keyfile=key_path
        )
    else:
        logger.warning("⚠️ SSL certificates not found, starting without encryption")
        logger.info(f"   Expected: {cert_path} and {key_path}")
        uvicorn.run(
            "asgi:application",
            host="0.0.0.0",
            port=8000,
            reload=True,
            reload_dirs=["/workspace/src"],
            log_level="debug"
        )

