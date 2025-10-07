#!/usr/bin/env python3
"""
ASGI entry point for VYRA modules
This file dynamically loads the application based on MODULE_NAME from .env
Supports FastAPI and other native ASGI frameworks (Starlette, Quart, etc.)
"""

import sys
import os
import importlib
from typing import Optional

# Add the src directory to Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

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
    print("Error: MODULE_NAME not found in .env file")
    application = create_error_app("MODULE_NAME not found in .env file")
else:
    try:
        # Try to import the REST API module
        module_path = f"src.{module_name}.{module_name}.application.rest_api.minimal_rest"
        print(f"Attempting to import: {module_path}")
        
        module = importlib.import_module(module_path)
        
        # Check if module has an ASGI app
        if hasattr(module, 'app'):
            app_obj = getattr(module, 'app')
            
            # Validate it's an ASGI app
            if is_asgi_app(app_obj):
                application = app_obj
                print(f"✅ Successfully loaded {module_name} ASGI application (FastAPI/Starlette)")
            else:
                raise AttributeError(f"'app' object is not a valid ASGI application")
        
        # Legacy support: explicit asgi_app export
        elif hasattr(module, 'asgi_app'):
            application = getattr(module, 'asgi_app')
            print(f"✅ Successfully loaded {module_name} ASGI application")
        
        else:
            raise AttributeError("No 'app' or 'asgi_app' found in module")
        
    except (ImportError, AttributeError) as e:
        print(f"❌ Error importing {module_name} application: {e}")
        
        # Try alternative path without rest_api
        try:
            alt_module_path = f"src.{module_name}.{module_name}.application.minimal_rest"
            print(f"Trying alternative import: {alt_module_path}")
            
            module = importlib.import_module(alt_module_path)
            
            # Check for ASGI app
            if hasattr(module, 'app'):
                app_obj = getattr(module, 'app')
                
                if is_asgi_app(app_obj):
                    application = app_obj
                    print(f"✅ Successfully loaded {module_name} ASGI application (alternative path)")
                else:
                    raise AttributeError(f"'app' object is not a valid ASGI application")
            
            elif hasattr(module, 'asgi_app'):
                application = getattr(module, 'asgi_app')
                print(f"✅ Successfully loaded {module_name} ASGI application (alternative path)")
            
            else:
                raise AttributeError("No 'app' or 'asgi_app' found in module")
            
        except (ImportError, AttributeError) as e2:
            print(f"❌ Error with alternative import: {e2}")
            application = create_error_app(f"Could not import {module_name}: {e} | Alternative: {e2}")

if __name__ == "__main__":
    # Direct development testing with Uvicorn
    import uvicorn
    
    cert_path = "/workspace/storage/certificates/webserver.crt"
    key_path = "/workspace/storage/certificates/webserver.key"
    
    ssl_config = {}
    if os.path.exists(cert_path) and os.path.exists(key_path):
        print("🔒 Starting with SSL/TLS encryption")
        ssl_config = {
            "ssl_certfile": cert_path,
            "ssl_keyfile": key_path,
        }
    else:
        print("⚠️ SSL certificates not found, starting without encryption")
        print(f"   Expected: {cert_path} and {key_path}")
    
    uvicorn.run(
        "asgi:application",
        host="0.0.0.0",
        port=8443 if ssl_config else 8000,
        reload=True,
        log_level="info",
        **ssl_config
    )

