"""
Configuration Management Template

Centralizes environment variables and application settings.

CUSTOMIZATION POINTS:
1. Update app_name and default module_id
2. Update api_prefix
3. Add module-specific settings
"""
import os
from typing import List
from pydantic import BaseModel


class Settings(BaseModel):
    """
    Application settings.
    
    CUSTOMIZE: Add your module-specific settings here.
    """
    
    # Application
    app_name: str = "your_module"  # CHANGE THIS
    module_id: str = os.getenv("MODULE_ID", "your_module_default")  # CHANGE THIS
    
    # API
    api_prefix: str = "/your_module/api"  # CHANGE THIS
    docs_enabled: bool = os.getenv("API_DOCS_ENABLED", "true").lower() == "true"
    
    # CORS
    cors_origins: List[str] = [
        "https://localhost",
        "https://localhost:3000",
        f"https://localhost/your_module",  # CHANGE THIS
    ]
    
    # Redis (if needed)
    redis_host: str = os.getenv("REDIS_HOST", "redis")
    redis_port: int = int(os.getenv("REDIS_PORT", "6379"))
    redis_ssl: bool = os.getenv("REDIS_SSL", "true").lower() == "true"
    redis_cert_path: str = "/workspace/storage/certificates/redis/ca-cert.pem"
    
    # ROS2
    ros_domain_id: int = int(os.getenv("ROS_DOMAIN_ID", "0"))
    ros_namespace: str = os.getenv("ROS_NAMESPACE", "/your_module")  # CHANGE THIS
    
    # Logging
    log_level: str = os.getenv("LOG_LEVEL", "INFO")
    
    # TODO: Add your module-specific settings here
    # Example:
    # sensor_polling_interval: float = float(os.getenv("SENSOR_POLL_INTERVAL", "1.0"))
    # max_concurrent_requests: int = int(os.getenv("MAX_CONCURRENT", "10"))


settings = Settings()
