"""
Backend Webserver Configuration

Application settings and configuration management.
"""

import os
from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    """Application settings"""
    
    # Module Info
    module_name: str = os.getenv('MODULE_NAME', 'vyra_module_template')
    module_version: str = "0.1.0"
    
    # API Settings
    api_prefix: str = f"/api/{os.getenv('MODULE_NAME', 'vyra_module_template')}"
    
    # Development
    debug: bool = os.getenv('VYRA_DEV_MODE', 'false').lower() == 'true'
    
    # Logging
    log_level: str = os.getenv('LOG_LEVEL', 'INFO')
    
    class Config:
        env_file = "/workspace/.env"
        case_sensitive = False


# Global settings instance
settings = Settings()
