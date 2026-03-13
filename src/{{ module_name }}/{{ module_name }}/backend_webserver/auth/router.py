"""
Authentication router for {{ module_name }} REST API
"""

from {{ module_name }}.logging_config import get_logger, log_exception, log_function_call, log_function_result
from typing import Optional
from fastapi import APIRouter, HTTPException, Depends, Header, Response, Cookie
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from pydantic import BaseModel

from .auth_service import AuthenticationService

logger = get_logger(__name__)

router = APIRouter(prefix="/auth", tags=["authentication"])

# Global auth service instance (will be set during app initialization)
_auth_service: Optional[AuthenticationService] = None

security = HTTPBearer(auto_error=False)


def set_auth_service(auth_service: AuthenticationService):
    """Set the global authentication service instance"""
    global _auth_service
    _auth_service = auth_service


def get_auth_service() -> AuthenticationService:
    """Dependency to get auth service"""
    if _auth_service is None:
        raise HTTPException(status_code=500, detail="Auth service not initialized")
    return _auth_service


class LoginRequest(BaseModel):
    """Login request model"""
    username: str
    password: str
    auth_mode: str = "local"  # 'local' or 'usermanager'


class LoginResponse(BaseModel):
    """Login response model"""
    success: bool
    token: str
    username: str
    auth_mode: str
    message: str


class ChangePasswordRequest(BaseModel):
    """Change password request"""
    username: str
    old_password: str
    new_password: str


class CreateUserRequest(BaseModel):
    """Create user request (admin only)"""
    username: str
    password: str


@router.post("/login", response_model=LoginResponse)
async def login(
    request: LoginRequest,
    response: Response,
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Authenticate user and create session
    
    Request:
        {
            "username": "admin",
            "password": "password",
            "auth_mode": "local"  // or "usermanager"
        }
    
    Response:
        {
            "success": true,
            "token": "session_token",
            "username": "admin",
            "auth_mode": "local",
            "message": "Login successful"
        }
    """
    logger.info(f"Login attempt: {request.username} (mode: {request.auth_mode})")
    
    try:
        # Validate credentials
        user_info = await auth_service.validate_credentials(
            request.username,
            request.password,
            request.auth_mode
        )
    except Exception as e:
        raise HTTPException(status_code=401, detail="Authentication failed") from e
    
    if not user_info:
        logger.warning(f"Login failed for: {request.username}")
        raise HTTPException(
            status_code=401,
            detail="Invalid credentials"
        )
    
    # Create session
    token = await auth_service.create_session(
        request.username,
        user_info
    )
    
    # Set cookie
    response.set_cookie(
        key="auth_token",
        value=token,
        httponly=True,
        max_age=3600 * 8,  # 8 hours
        samesite="lax"
    )
    
    return LoginResponse(
        success=True,
        token=token,
        username=request.username,
        auth_mode=request.auth_mode,
        message="Login successful"
    )


@router.post("/logout")
async def logout(
    response: Response,
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Logout user and revoke session
    
    Token can be provided via:
    - Cookie: auth_token
    - Authorization header: Bearer <token>
    """
    token = None
    
    # Check cookie first
    if auth_token:
        token = auth_token
    # Then check Authorization header
    elif credentials:
        token = credentials.credentials
    
    if token:
        await auth_service.revoke_token(token)
        response.delete_cookie("auth_token")
        logger.info("User logged out")
    
    return {"success": True, "message": "Logged out successfully"}


@router.get("/verify")
async def verify_token(
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Verify authentication token
    
    Returns user info if token is valid
    """
    token = None
    
    # Check cookie first
    if auth_token:
        token = auth_token
    # Then check Authorization header
    elif credentials:
        token = credentials.credentials
    
    if not token:
        raise HTTPException(status_code=401, detail="No authentication token provided")
    
    user_info = await auth_service.validate_token(token)
    
    if not user_info:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    
    return {
        "success": True,
        "user": user_info
    }


@router.post("/change-password")
async def change_password(
    request: ChangePasswordRequest,
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Change user password
    
    Requires valid authentication token
    """
    token = auth_token or (credentials.credentials if credentials else None)
    
    if not token:
        raise HTTPException(status_code=401, detail="Authentication required")
    
    # Verify token
    user_info = await auth_service.validate_token(token)
    if not user_info:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    
    # Only allow users to change their own password (or admin to change any)
    if user_info["username"] != request.username and user_info["username"] != "admin":
        raise HTTPException(status_code=403, detail="Not authorized")
    
    # Change password
    success = await auth_service.change_password(
        request.username,
        request.old_password,
        request.new_password
    )
    
    if not success:
        raise HTTPException(status_code=400, detail="Failed to change password")
    
    return {"success": True, "message": "Password changed successfully"}


@router.get("/check-usermanager")
async def check_usermanager(
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Check if usermanager service is available
    
    Returns:
        {
            "available": true/false,
            "message": "..."
        }
    """
    result = await auth_service.check_usermanager_available()
    
    return {
        "available": result.get("available", False),
        "message": result.get("message", "Unknown status")
    }


@router.get("/users")
async def list_users(
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    List all local users (admin only)
    
    Requires valid authentication token
    """
    token = auth_token or (credentials.credentials if credentials else None)
    
    if not token:
        raise HTTPException(status_code=401, detail="Authentication required")
    
    # Verify token
    user_info = await auth_service.validate_token(token)
    if not user_info:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    
    # Only admin can list users
    if user_info["username"] != "admin":
        raise HTTPException(status_code=403, detail="Admin access required")
    
    users = await auth_service.list_local_users()
    
    return {
        "success": True,
        "users": users
    }


@router.post("/users")
async def create_user(
    request: CreateUserRequest,
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Create new user (admin only)
    
    Requires valid authentication token
    """
    token = auth_token or (credentials.credentials if credentials else None)
    
    if not token:
        raise HTTPException(status_code=401, detail="Authentication required")
    
    # Verify token
    user_info = await auth_service.validate_token(token)
    if not user_info:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    
    # Only admin can create users
    if user_info["username"] != "admin":
        raise HTTPException(status_code=403, detail="Admin access required")
    
    # Create user
    result = await auth_service.create_local_user(request.username, request.password)
    
    if not result.get("success"):
        raise HTTPException(status_code=400, detail=result.get("message", "Failed to create user"))
    
    return {
        "success": True,
        "message": f"User {request.username} created successfully"
    }
