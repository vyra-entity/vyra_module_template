#!/usr/bin/env python3
"""
WSGI entry point for VYRA modules
This file dynamically loads the Flask application based on MODULE_NAME from .env
"""

import sys
import os
import importlib

# Add the src directory to Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

def load_env_file():
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

def create_error_app(error_message):
    """Create a minimal Flask app for error display"""
    from flask import Flask
    app = Flask(__name__)
    
    @app.route('/')
    def error():
        return f"Error: {error_message}", 500
    
    return app

# Load module name from .env
module_name = load_env_file()

if not module_name:
    print("Error: MODULE_NAME not found in .env file")
    application = create_error_app("MODULE_NAME not found in .env file")
else:
    try:
        # Dynamic import: src.{module_name}.{module_name}.application.rest_api.minimal_rest:app
        module_path = f"src.{module_name}.{module_name}.application.rest_api.minimal_rest"
        print(f"Attempting to import: {module_path}")
        
        module = importlib.import_module(module_path)
        application = getattr(module, 'app')
        
        print(f"✅ Successfully loaded {module_name} application")
        
    except (ImportError, AttributeError) as e:
        print(f"❌ Error importing {module_name} application: {e}")
        
        # Try alternative path without rest_api
        try:
            alt_module_path = f"src.{module_name}.{module_name}.application.minimal_rest"
            print(f"Trying alternative import: {alt_module_path}")
            
            module = importlib.import_module(alt_module_path)
            application = getattr(module, 'app')
            
            print(f"✅ Successfully loaded {module_name} application (alternative path)")
            
        except (ImportError, AttributeError) as e2:
            print(f"❌ Error with alternative import: {e2}")
            application = create_error_app(f"Could not import {module_name}: {e} | Alternative: {e2}")

if __name__ == "__main__":
    application.run(host='0.0.0.0', port=8443, debug=True)
