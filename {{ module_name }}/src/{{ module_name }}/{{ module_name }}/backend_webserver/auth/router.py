"""
Authentication router for {{ module_name }} REST API
"""

from typing import Optional

from fastapi import APIRouter, Cookie, Depends, HTTPException, Response
from fastapi.security import HTTPAuthorizationCredentials

from {{ module_name }}.logging_config import get_logger

from vyra_base.auth import (
    TOKEN_COOKIE_MAX_AGE,
    ChangePasswordRequest,
    CreateUserRequest,
    LoginRequest,
    LoginResponse,
    UsermanagerUnavailableError,
    _extract_token,
    make_auth_service_di,
    security,
)

from .auth_service import AuthenticationService

logger = get_logger(__name__)

router = APIRouter(prefix="/auth", tags=["authentication"])

set_auth_service, get_auth_service = make_auth_service_di()


async def get_current_user(
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service),
) -> dict:
    """FastAPI dependency — validates session token and returns user info."""
    token = _extract_token(auth_token, credentials)
    user_info = await auth_service.validate_token(token)
    if user_info is None:
        raise HTTPException(status_code=401, detail="Invalid or expired token")
    return user_info


@router.post("/login", response_model=LoginResponse)
async def login(
    request: LoginRequest,
    response: Response,
    auth_service: AuthenticationService = Depends(get_auth_service)
):
    """
    Authenticate user and create session.

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
        user_info = await auth_service.validate_credentials(
            request.username,
            request.password,
            request.auth_mode,
        )
    except UsermanagerUnavailableError as exc:
        logger.warning(f"UserManager not reachable during login by '{request.username}': {exc}")
        raise HTTPException(
            status_code=503,
            detail="Usermanager ist nicht erreichbar. Nur lokaler Login möglich.",
        ) from exc
    except Exception as exc:
        if "access_denied" in str(exc):
            raise HTTPException(
                status_code=403,
                detail="Access to this module is not permitted for your account",
            ) from exc
        raise HTTPException(status_code=401, detail="Authentication failed") from exc

    if not user_info:
        logger.warning(f"Login failed for: {request.username}")
        raise HTTPException(status_code=401, detail="Invalid credentials")

    token = await auth_service.create_session(request.username, user_info)

    response.set_cookie(
        key="auth_token",
        value=token,
        httponly=True,
        secure=True,
        max_age=TOKEN_COOKIE_MAX_AGE,
        samesite="lax",
    )

    return LoginResponse(
        success=True,
        token=token,
        username=request.username,
        auth_mode=request.auth_mode,
        message="Login successful",
    )


@router.post("/logout")
async def logout(
    response: Response,
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """
    Logout user and revoke session.

    Token can be provided via:
    - Cookie: auth_token
    - Authorization header: Bearer <token>
    """
    try:
        token = _extract_token(auth_token, credentials)
    except HTTPException:
        token = None

    if token:
        await auth_service.revoke_token(token)
        response.delete_cookie("auth_token")
        logger.info("User logged out")

    return {"success": True, "message": "Logged out successfully"}


@router.get("/verify")
async def verify_token(
    auth_token: Optional[str] = Cookie(None),
    credentials: Optional[HTTPAuthorizationCredentials] = Depends(security),
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """
    Verify authentication token.

    Returns user info if token is valid.
    """
    token = _extract_token(auth_token, credentials)
    user_info = await auth_service.validate_token(token)

    if not user_info:
        raise HTTPException(status_code=401, detail="Invalid or expired token")

    return {"success": True, "user": user_info}


@router.post("/change-password")
async def change_password(
    request: ChangePasswordRequest,
    user: dict = Depends(get_current_user),
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """
    Change the current user's password.

    Authentication is validated via the session token (cookie or Bearer header).
    """
    success = await auth_service.change_password(
        user["username"],
        request.old_password,
        request.new_password,
    )

    if not success:
        raise HTTPException(status_code=400, detail="Failed to change password")

    return {"success": True, "message": "Password changed successfully"}


@router.get("/check-usermanager")
async def check_usermanager(
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """Check if the external usermanager service is available."""
    result = await auth_service.check_usermanager_available()
    return {
        "available": result.get("available", False),
        "message": result.get("message", "Unknown status"),
    }


@router.get("/users")
async def list_users(
    user: dict = Depends(get_current_user),
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """List all local users (admin only)."""
    if user["username"] != "admin":
        raise HTTPException(status_code=403, detail="Admin access required")

    users = await auth_service.list_local_users()
    return {"success": True, "users": users}


@router.post("/users")
async def create_user(
    request: CreateUserRequest,
    user: dict = Depends(get_current_user),
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """Create new user (admin only)."""
    if user["username"] != "admin":
        raise HTTPException(status_code=403, detail="Admin access required")

    result = await auth_service.create_local_user(
        request.username, request.password, role=request.role
    )

    if not result.get("success"):
        raise HTTPException(status_code=400, detail=result.get("message", "Failed to create user"))

    return {"success": True, "message": f"User {request.username} created successfully"}


@router.delete("/users/{username}")
async def delete_user(
    username: str,
    user: dict = Depends(get_current_user),
    auth_service: AuthenticationService = Depends(get_auth_service),
):
    """Delete local user (admin only)."""
    if user["username"] != "admin":
        raise HTTPException(status_code=403, detail="Admin access required")

    if username == "admin":
        raise HTTPException(status_code=400, detail="Cannot delete admin user")

    result = await auth_service.delete_local_user(username)

    if not result.get("success"):
        raise HTTPException(status_code=400, detail=result.get("message", "Failed to delete user"))

    return {"success": True, "message": f"User {username} deleted successfully"}
