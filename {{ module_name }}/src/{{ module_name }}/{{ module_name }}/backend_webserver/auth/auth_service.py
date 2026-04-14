"""
Authentication Service for {{ module_name }} - Direct DI Version

Integrates with Internal User Manager via direct dependency injection
(no gRPC needed since backend and core run in same process).
"""

from {{ module_name }}.logging_config import get_logger, log_exception, log_function_call, log_function_result
import os
import secrets
import ssl
from datetime import datetime, timedelta
from typing import Optional, Dict, Any
from pydantic import BaseModel, json
import aiohttp

from vyra_base.com.transport.t_redis.communication import RedisClient
from ...container_injection import get_user_manager

logger = get_logger(__name__)


class AuthToken(BaseModel):
    """Authentication token model"""
    token: str
    username: str
    user_id: int
    role: str
    level: int
    created_at: str
    expires_at: str
    module_id: str


class AuthenticationService:
    """
    Authentication service with direct dependency injection
    
    Authentication Flow:
    1. Check auth_mode: 'local' or 'usermanager'
    2. If local: Validate via InternalUserManager (direct access via DI)
    3. If usermanager: Delegate to external usermanager (ROS2)
    4. Store session tokens in Redis for fast access
    
    Architecture:
    Backend Webserver → container_injection.get_component() → Component.internal_usermanager → Database
    """
    
    def __init__(
        self,
        redis_client: RedisClient,
        module_id: str
    ):
        """
        Initialize authentication service
        
        Args:
            redis_client: Redis client for session storage
            module_id: Module identifier (e.g., '{{ module_name }}')
        """
        self.redis = redis_client
        self.module_id = module_id
        
        self._token_prefix = f"{module_id}:auth:tokens"
        self._token_ttl = 3600 * 8  # 8 hours
        
        logger.info(f"✅ Authentication service initialized for {module_id} (direct DI)")
    
    async def validate_credentials(
        self, 
        username: str, 
        password: str,
        auth_mode: str = "local"
    ) -> Optional[Dict[str, Any]]:
        """
        Validate user credentials
        
        Args:
            username: Username
            password: Plain text password
            auth_mode: 'local' or 'usermanager'
            
        Returns:
            User info dict if valid, None otherwise
        """
        if auth_mode == "local":
            return await self._validate_local_credentials(username, password)
        elif auth_mode == "usermanager":
            return await self._validate_usermanager_credentials(username, password)
        else:
            logger.error(f"Unknown auth_mode: {auth_mode}")
            return None
    
    async def _validate_local_credentials(
        self, 
        username: str, 
        password: str
    ) -> Optional[Dict[str, Any]]:
        """Validate credentials via InternalUserManager (direct DI)"""
        try:
            user_manager = get_user_manager()
            if not user_manager or not user_manager.internal_usermanager:
                logger.error("InternalUserManager not available via UserManager")
                raise Exception("InternalUserManager not available")
            
            user_info = await user_manager.internal_usermanager.authenticate(
                username, password
            )
            
            if user_info:
                logger.info(f"✅ User authenticated via direct DI: {username}")
                return {
                    **user_info,
                    "auth_mode": "local"
                }
            else:
                logger.warning(f"❌ Authentication failed for: {username}")
                raise Exception("Invalid username or password")
                
        except Exception as e:
            logger.error(f"❌ Authentication error: {e}", exc_info=True)
            raise Exception("General authentication error") from e
    
    async def _validate_usermanager_credentials(
        self, 
        username: str, 
        password: str
    ) -> Optional[Dict[str, Any]]:
        """
        Validate credentials via external usermanager service
        
        TODO: Implement ROS2 service call to external usermanager
        """
        logger.warning("External usermanager authentication not yet implemented")
        return None
    
    async def create_session(
        self, 
        username: str,
        user_info: Dict[str, Any]
    ) -> str:
        """
        Create authentication session and return token
        
        Args:
            username: Username
            user_info: User information from authentication
            
        Returns:
            Session token
        """
        # Generate secure token
        token = secrets.token_urlsafe(32)
        
        # Create token record
        auth_token = AuthToken(
            token=token,
            username=username,
            user_id=user_info.get("user_id", 0),
            role=user_info.get("role", "viewer"),
            level=user_info.get("level", 3),
            created_at=datetime.utcnow().isoformat(),
            expires_at=(datetime.utcnow() + timedelta(seconds=self._token_ttl)).isoformat(),
            module_id=self.module_id
        )
        
        token_key = f"{self._token_prefix}:{token}"
        await self.redis.set(
            token_key, 
            auth_token.model_dump_json()
        )
        # ex=self._token_ttl        # Set expiry using raw client
        client = await self.redis._ensure_connected()
        await client.expire(token_key, self._token_ttl)
        
        logger.info(f"✅ Created session for user: {username}")
        return token
    
    async def validate_token(self, token: str) -> Optional[Dict[str, Any]]:
        """
        Validate authentication token
        
        Args:
            token: Session token
            
        Returns:
            User info dict if valid, None otherwise
        """
        token_key = f"{self._token_prefix}:{token}"
        
        token_json = await self.redis.get(token_key)
        if not token_json:
            logger.debug("Invalid or expired token")
            return None
        
        try:
            auth_token = AuthToken.model_validate_json(token_json)
            
            # Check expiration
            expires_at = datetime.fromisoformat(auth_token.expires_at)
            if datetime.utcnow() > expires_at:
                logger.debug("Token expired")
                await self.redis.delete(token_key)
                return None
            
            return {
                "user_id": auth_token.user_id,
                "username": auth_token.username,
                "role": auth_token.role,
                "level": auth_token.level,
                "token": auth_token.token,
                "module_id": auth_token.module_id
            }
        except Exception as e:
            logger.error(f"Error validating token: {e}")
            return None
    
    async def revoke_token(self, token: str) -> bool:
        """
        Revoke authentication token (logout)
        
        Args:
            token: Session token
            
        Returns:
            True if token was revoked
        """
        token_key = f"{self._token_prefix}:{token}"
        result = await self.redis.delete(token_key)
        return result > 0
    
    async def change_password(
        self, 
        username: str, 
        old_password: str, 
        new_password: str
    ) -> bool:
        """
        Change user password via internal user manager (direct DI)
        
        Args:
            username: Username
            old_password: Current password
            new_password: New password
            
        Returns:
            True if password was changed
        """
        try:
            user_manager = get_user_manager()
            if not user_manager or not user_manager.internal_usermanager:
                logger.error("InternalUserManager not available via UserManager")
                raise Exception("InternalUserManager not available")
            
            result = await user_manager.internal_usermanager.change_password_impl(
                username, old_password, new_password
            )
            return result.get("success", False) if result else False
        except Exception as e:
            logger.error(f"Error changing password: {e}", exc_info=True)
            return False
    
    async def check_usermanager_available(self) -> Dict[str, Any]:
        """
        Check if external usermanager service is available.

        Delegates the check to the modulemanager via HTTP, since the module
        registry lives in the modulemanager, not in individual modules.

        Returns:
            Dict with available status and details
        """
        gateway = os.environ.get("GATEWAY_URL", "https://traefik:443")
        url = f"{gateway}/v2_modulemanager/api/auth/check-usermanager"
        ssl_ctx = ssl.create_default_context()
        ssl_ctx.check_hostname = False
        ssl_ctx.verify_mode = ssl.CERT_NONE
        try:
            async with aiohttp.ClientSession() as session:
                async with session.get(url, ssl=ssl_ctx, timeout=aiohttp.ClientTimeout(total=5)) as resp:
                    if resp.status == 200:
                        data = await resp.json()
                        return data
                    else:
                        logger.warning(f"Module manager returned {resp.status} for usermanager check")
                        return {
                            "available": False,
                            "message": f"Module manager returned status {resp.status}"
                        }
        except Exception as e:
            logger.error(f"❌ Error checking usermanager availability via gateway: {e}", exc_info=True)
            return {
                "available": False,
                "message": f"Error reaching module manager: {str(e)}"
            }
    
    async def list_local_users(self) -> list:
        """List all local users via InternalUserManager (direct DI)"""
        try:
            user_manager = get_user_manager()
            if not user_manager or not user_manager.internal_usermanager:
                logger.error("InternalUserManager not available via UserManager")
                raise Exception("InternalUserManager not available")
            
            result = await user_manager.internal_usermanager.list_users_impl()
            return result.get("users", []) if result else []
        except Exception as e:
            logger.error(f"Error listing users: {e}", exc_info=True)
            return []
    
    async def create_local_user(
        self,
        username: str,
        password: str,
        role: str = "viewer",
        level: int = 0,
        permissions: str | dict = "{}"
    ) -> Dict[str, Any]:
        """Create new local user via InternalUserManager (direct DI)"""
        try:
            user_manager = get_user_manager()
            if not user_manager or not user_manager.internal_usermanager:
                logger.error("InternalUserManager not available via UserManager")
                raise Exception("InternalUserManager not available")
            
            if isinstance(permissions, str):
                try:
                    permissions_parsed: dict = json.loads(permissions)
                except json.JSONDecodeError:
                    logger.error("Invalid permissions JSON string")
                    return {
                        "success": False,
                        "message": "Invalid permissions format"
                    }

            result = await user_manager.internal_usermanager.create_user_impl(
                username=username,
                password=password,
                role=role,
                level=level,
                permissions=permissions_parsed
            )
            
            if result and result.get("success"):
                return {
                    "success": True,
                    "message": "User created successfully",
                    "user": result.get("user")
                }
            else:
                return {
                    "success": False,
                    "message": result.get("message", "Failed to create user") if result else "Failed to create user"
                }
        except Exception as e:
            logger.error(f"Error creating user: {e}", exc_info=True)
            return {
                "success": False,
                "message": f"Error: {str(e)}"
            }
