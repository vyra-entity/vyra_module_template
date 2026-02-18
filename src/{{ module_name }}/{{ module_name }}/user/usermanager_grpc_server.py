"""
User Manager gRPC Server for v2_modulemanager
Provides gRPC service for user authentication and management
"""
import logging
from pathlib import Path
from typing import Optional
from datetime import datetime

from vyra_base.com.external.grpc import GrpcServer

# Import generated protobuf files (will be generated from usermanager_service.proto)
# from storage.interfaces import usermanager_service_pb2
# from storage.interfaces import usermanager_service_pb2_grpc

logger = logging.getLogger(__name__)


class UserManagerServicer:
    """
    gRPC servicer implementation for User Manager.
    Bridges gRPC calls to InternalUserManager.
    """
    
    def __init__(self, internal_usermanager):
        """
        Initialize servicer with internal user manager.
        
        Args:
            internal_usermanager: InternalUserManager instance
        """
        self.internal_usermanager = internal_usermanager
        logger.info("🔧 UserManagerServicer initialized")
    
    async def AuthenticateUser(self, request, context):
        """
        Authenticate user with username and password.
        
        Args:
            request: AuthenticateUserRequest
            context: gRPC context
            
        Returns:
            AuthenticateUserResponse
        """
        try:
            logger.info(f"🔐 gRPC AuthenticateUser: {request.username}")
            
            # Call internal user manager
            user_info = await self.internal_usermanager.authenticate(
                request.username,
                request.password
            )
            
            if user_info:
                # Import will be available after proto compilation
                # from storage.interfaces import usermanager_service_pb2
                
                # Return success response (pseudo-code for now)
                return {
                    "correlation_id": request.correlation_id,
                    "success": True,
                    "message": "Authentication successful",
                    "user_info": {
                        "user_id": user_info["user_id"],
                        "username": user_info["username"],
                        "role": user_info["role"],
                        "level": user_info["level"],
                        "enabled": user_info["enabled"],
                        "permissions": user_info.get("permissions", "{}"),
                    }
                }
            else:
                return {
                    "correlation_id": request.correlation_id,
                    "success": False,
                    "message": "Invalid credentials",
                    "user_info": None
                }
                
        except Exception as e:
            logger.exception(f"❌ gRPC AuthenticateUser failed: {e}")
            return {
                "correlation_id": request.correlation_id,
                "success": False,
                "message": f"Authentication error: {str(e)}",
                "user_info": None
            }
    
    async def CreateUser(self, request, context):
        """Create new user."""
        try:
            logger.info(f"👤 gRPC CreateUser: {request.username}")
            
            user = await self.internal_usermanager.create_user_impl(
                username=request.username,
                password=request.password,
                role=request.role,
                level=request.level,
                permissions=request.permissions
            )
            
            if user:
                return {
                    "correlation_id": request.correlation_id,
                    "success": True,
                    "message": "User created successfully",
                    "user_info": self._user_to_proto(user)
                }
            else:
                return {
                    "correlation_id": request.correlation_id,
                    "success": False,
                    "message": "User already exists",
                    "user_info": None
                }
                
        except Exception as e:
            logger.exception(f"❌ gRPC CreateUser failed: {e}")
            return {
                "correlation_id": request.correlation_id,
                "success": False,
                "message": str(e),
                "user_info": None
            }
    
    async def ListUsers(self, request, context):
        """List all users."""
        try:
            logger.info("📋 gRPC ListUsers")
            
            users = await self.internal_usermanager.list_users_impl(
                include_disabled=request.include_disabled
            )
            
            return {
                "correlation_id": request.correlation_id,
                "success": True,
                "message": f"Found {len(users)} users",
                "users": [self._user_to_proto(user) for user in users]
            }
            
        except Exception as e:
            logger.exception(f"❌ gRPC ListUsers failed: {e}")
            return {
                "correlation_id": request.correlation_id,
                "success": False,
                "message": str(e),
                "users": []
            }
    
    async def ChangePassword(self, request, context):
        """Change user password."""
        try:
            logger.info(f"🔑 gRPC ChangePassword: {request.username}")
            
            success = await self.internal_usermanager.change_password_impl(
                username=request.username,
                old_password=request.old_password,
                new_password=request.new_password
            )
            
            return {
                "correlation_id": request.correlation_id,
                "success": success,
                "message": "Password changed" if success else "Invalid old password"
            }
            
        except Exception as e:
            logger.exception(f"❌ gRPC ChangePassword failed: {e}")
            return {
                "correlation_id": request.correlation_id,
                "success": False,
                "message": str(e)
            }
    
    async def InitializeDefaultAdmin(self, request, context):
        """Initialize default admin user."""
        try:
            logger.info("👨‍💼 gRPC InitializeDefaultAdmin")
            
            result = await self.internal_usermanager.initialize_default_admin()
            
            return {
                "correlation_id": request.correlation_id,
                "success": True,
                "message": "Admin initialized" if result else "Admin already exists",
                "admin_created": result
            }
            
        except Exception as e:
            logger.exception(f"❌ gRPC InitializeDefaultAdmin failed: {e}")
            return {
                "correlation_id": request.correlation_id,
                "success": False,
                "message": str(e),
                "admin_created": False
            }
    
    def _user_to_proto(self, user):
        """Convert User model to proto UserInfo."""
        return {
            "user_id": user.user_id,
            "username": user.username,
            "role": user.role.value if hasattr(user.role, 'value') else str(user.role),
            "level": user.level.value if hasattr(user.level, 'value') else int(user.level),
            "enabled": user.enabled,
            "permissions": user.permissions or "{}",
            "login_attempts": user.login_attempts,
            "locked_until": user.locked_until.isoformat() if user.locked_until else "",
            "created_at": user.created_at.isoformat() if user.created_at else "",
            "updated_at": user.updated_at.isoformat() if user.updated_at else ""
        }


class UserManagerGrpcServer:
    """
    gRPC server wrapper for user manager service.
    
    Manages lifecycle of gRPC server on Unix Domain Socket.
    """
    
    def __init__(
        self,
        internal_usermanager,
        socket_path: Path = Path("/tmp/vyra_sockets/vyra_usermanager.sock")
    ):
        """
        Initialize gRPC server.
        
        Args:
            internal_usermanager: InternalUserManager instance
            socket_path: Unix socket path for gRPC communication
        """
        self.internal_usermanager = internal_usermanager
        self.socket_path = socket_path
        
        self._server: Optional[GrpcServer] = None
        self._servicer: Optional[UserManagerServicer] = None
        
        logger.info(f"🔧 UserManagerGrpcServer created (socket: {socket_path})")
    
    async def start(self):
        """Start the gRPC server."""
        try:
            logger.info("🚀 Starting UserManager gRPC Server...")
            
            # Create servicer
            self._servicer = UserManagerServicer(self.internal_usermanager)
            
            # Create server
            self._server = GrpcServer(socket_path=self.socket_path)
            
            if self._server:
                # Register servicer (will be available after proto compilation)
                # from storage.interfaces import usermanager_service_pb2_grpc
                # self._server.add_service(
                #     usermanager_service_pb2_grpc.add_UserManagerServiceServicer_to_server,
                #     self._servicer
                # )
                
                # Start server
                await self._server.start()
                logger.info(f"✅ UserManager gRPC Server running on {self.socket_path}")
                
                # TODO: Remove this note after proto compilation
                logger.warning("⚠️  Proto files need compilation: python -m grpc_tools.protoc ...")
            else:
                raise RuntimeError("Failed to create gRPC UDS server")
            
        except Exception as e:
            logger.exception(f"❌ Failed to start UserManager gRPC Server: {e}")
            raise
    
    async def stop(self):
        """Stop the gRPC server."""
        if self._server:
            logger.info("🛑 Stopping UserManager gRPC Server...")
            await self._server.stop()
            logger.info("✅ UserManager gRPC Server stopped")
    
    async def wait_for_termination(self):
        """Wait for server termination."""
        if self._server:
            await self._server.wait_for_termination()
