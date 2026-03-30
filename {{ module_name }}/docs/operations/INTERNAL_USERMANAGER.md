# Internal User Manager Documentation

## Overview

The Internal User Manager is a built-in user authentication and authorization system for the VYRA Module Manager. It runs as a separate task within the `{{ module_name }}` module and provides local user management when no external usermanager module is available.

## Architecture

### Directory Structure

```
{{ module_name }}/
├── user/
│   ├── __init__.py
│   ├── usermanager.py                 # Main runner and orchestrator
│   ├── internal_usermanager.py        # Core user management logic
│   ├── usermanager_grpc_server.py     # gRPC server for REST API communication
│   └── tb_users.py                    # Database model for users
```

### Components

1. **UserManager (usermanager.py)**
   - Orchestrates initialization and lifecycle
   - Runs as async task in TaskManager
   - Initializes internal user manager and gRPC server

2. **InternalUserManager (internal_usermanager.py)**
   - Core authentication and authorization logic
   - Database operations (CRUD for users)
   - Password hashing and verification
   - Account lockout on failed login attempts

3. **UserManagerGrpcServer (usermanager_grpc_server.py)**
   - Provides gRPC service for REST API
   - Bridges HTTP requests to internal user manager
   - Unix domain socket communication

4. **User Model (tb_users.py)**
   - SQLAlchemy database model
   - User roles: ADMIN, OPERATOR, VIEWER, CUSTOM
   - Access levels: 0-4 (lower = more privileged)

## Features

### 1. Initial Admin User from Environment

On first startup, if no users exist in the database:

- Reads `INITIAL_ADMIN_USER` and `INITIAL_ADMIN_PASSWORD` from `.env`
- Creates admin user with full system access
- Sets `password_change_required` flag in user metadata
- Forces password change on first login

**Environment Variables:**

```bash
INITIAL_ADMIN_USER=admin          # Default: 'admin'
INITIAL_ADMIN_PASSWORD=admin      # Default: 'admin'
```

### 2. Password Change Enforcement

When `password_change_required` is set in user metadata:

- User can login but receives flag in response
- Frontend should redirect to password change page
- After password change, flag is cleared
- New password is securely hashed and stored

### 3. Account Security

**Password Requirements:**
- Minimum length: 4 characters (configurable)
- SHA-256 hashed storage
- No plain-text passwords in database

**Failed Login Protection:**
- Max login attempts: 5 (configurable)
- Account lockout: 15 minutes (configurable)
- Automatic unlock after timeout
- Counter reset on successful login

**Account States:**
- Enabled/Disabled flag
- Locked until timestamp
- Last login tracking
- Last password change tracking

### 4. User Roles and Permissions

**Predefined Roles:**

| Role     | Level | Description                    |
|----------|-------|--------------------------------|
| ADMIN    | 0     | Full system access             |
| OPERATOR | 1     | Module management & operations |
| VIEWER   | 3     | Read-only access               |
| CUSTOM   | -     | Custom permission set          |

**Access Levels:**
- LEVEL_0: Full system access (admin)
- LEVEL_1: Module management
- LEVEL_2: Module operations
- LEVEL_3: Read-only
- LEVEL_4: Limited read-only

**Custom Permissions (JSON):**

```json
{
  "modules": ["*"],           // Access to all modules, or specific list
  "operations": ["*"],        // All operations, or specific list
  "custom_settings": {}       // Module-specific permissions
}
```

### 5. External Usermanager Detection

The system can detect external usermanager modules via the module registry:

**Detection Process:**
1. Query module registry via gRPC
2. Filter by `template: 'usermanager'`
3. Return list of available external usermanagers
4. Frontend shows dropdown if multiple options exist

**REST API Endpoint:**

```
GET /api/auth/check-usermanager

Response:
{
  "available": true,
  "message": "Found 1 usermanager module(s)",
  "modules": [
    {
      "module_id": "...",
      "module_name": "external_usermanager",
      "template": "usermanager"
    }
  ]
}
```

## REST API Integration

### Authentication Flow

```
Browser → REST API → gRPC Client → gRPC Server → InternalUserManager → Database
```

**gRPC Communication:**
- Unix domain socket: `/workspace/storage/usermanager_service.sock`
- Async/await pattern
- Request/response with correlation IDs

### Available Endpoints

```
POST   /api/auth/login              # Authenticate user
POST   /api/auth/logout             # Revoke session
GET    /api/auth/verify             # Verify token
POST   /api/auth/change-password    # Change user password
GET    /api/auth/check-usermanager  # Check external usermanager
GET    /api/auth/users              # List users (admin only)
POST   /api/auth/users              # Create user (admin only)
```

## Task Management

### Initialization in main.py

```python
from .user.usermanager import usermanager_runner

async def initialize_module(taskmanager: TaskManager):
    entity = await _base_.build_base()
    statusmanager = await setup_statusmanager(entity)
    component = Component(...)
    
    # Add tasks
    taskmanager.add_task(application_runner, ...)
    taskmanager.add_task(ros_spinner_runner, entity)
    taskmanager.add_task(usermanager_runner, entity)  # ← User Manager Task
    
    return entity, statusmanager
```

### Task Lifecycle

1. **Startup:**
   - TaskManager calls `usermanager_runner(entity)`
   - UserManager initializes InternalUserManager
   - Checks for existing users, creates admin if needed
   - Starts gRPC server on Unix domain socket
   - Runs indefinitely until task is cancelled

2. **Running:**
   - gRPC server handles incoming requests
   - InternalUserManager processes authentication
   - Database operations via DbManipulator

3. **Shutdown:**
   - TaskManager cancels task
   - gRPC server stops gracefully
   - Connections cleaned up

## Database Schema

**Table: users**

| Column                | Type     | Description                           |
|-----------------------|----------|---------------------------------------|
| id                    | Integer  | Primary key (auto-increment)          |
| username              | String   | Unique username (indexed)             |
| password_hash         | String   | SHA-256 hashed password               |
| email                 | String   | Optional email address                |
| role                  | Enum     | ADMIN, OPERATOR, VIEWER, CUSTOM       |
| level                 | Enum     | 0-4 access level                      |
| enabled               | Boolean  | Account enabled flag                  |
| permissions           | JSON     | Custom permissions object             |
| created_at            | DateTime | Account creation timestamp            |
| last_login            | DateTime | Last successful login                 |
| last_password_change  | DateTime | Last password change                  |
| login_attempts        | Integer  | Failed login counter                  |
| locked_until          | DateTime | Account lock expiry                   |
| metadata              | JSON     | Additional metadata (e.g., password_change_required) |

## Configuration

### Environment Variables

```bash
# Initial Admin User (created if no users exist)
INITIAL_ADMIN_USER=admin
INITIAL_ADMIN_PASSWORD=admin

# Security Settings (optional, defaults shown)
USER_PASSWORD_MIN_LENGTH=4
USER_MAX_LOGIN_ATTEMPTS=5
USER_LOCKOUT_DURATION_MINUTES=15
```

### Database Configuration

Uses vyra_base SQLite database:
- Location: `/workspace/storage/databases/{{ module_name }}.db`
- ORM: SQLAlchemy via vyra_base DbManipulator
- Auto-creates tables on first run

## Usage Examples

### Creating a New User (Python)

```python
from {{ module_name }}.user import InternalUserManager

usermanager = InternalUserManager(entity)

result = await usermanager.create_user_impl(
    username="operator1",
    password="secure_password",
    role="operator",
    level=1,
    permissions='{"modules": ["{{ module_name }}"], "operations": ["start", "stop"]}'
)
```

### Authenticating a User

```python
user_info = await usermanager.authenticate("admin", "password")

if user_info:
    print(f"Welcome {user_info['username']}")
    if user_info.get('password_change_required'):
        print("Please change your password")
```

### Changing Password

```python
result = await usermanager.change_password_impl(
    username="admin",
    old_password="admin",
    new_password="new_secure_password"
)
```

## Frontend Integration

### Login with Password Change Detection

```typescript
const result = await authApi.login({ username, password, auth_mode: 'local' })

if (result.success) {
  const userInfo = await authApi.verifyToken()
  
  if (userInfo.password_change_required) {
    // Redirect to password change page
    router.push('/change-password')
  } else {
    router.push('/home')
  }
}
```

### Checking for External Usermanagers

```typescript
const status = await authApi.checkUserManagerAvailable()

if (status.available && status.modules.length > 0) {
  // Show dropdown with multiple options
  authModeOptions.value = [
    { label: 'Local', value: 'local' },
    ...status.modules.map(m => ({
      label: m.module_name,
      value: m.module_id
    }))
  ]
} else {
  // Only local authentication
  authModeOptions.value = [{ label: 'Local', value: 'local' }]
}
```

## Security Best Practices

1. **Always use HTTPS** for production deployments
2. **Change default admin password** immediately after first login
3. **Use strong passwords** (minimum 12 characters recommended)
4. **Enable SROS2** for ROS2 service communication security
5. **Regularly review user accounts** and disable unused accounts
6. **Monitor failed login attempts** for potential attacks
7. **Backup user database** regularly

## Troubleshooting

### User Manager Not Starting

**Check logs:**
```bash
docker service logs vos2_ws_{{ module_name }} | grep "User Manager"
```

**Common issues:**
- Database connection failure
- Socket path permission issues
- gRPC server port already in use

### Cannot Login with Default Admin

**Verify admin user exists:**
```bash
# Inside container
sqlite3 /workspace/storage/databases/{{ module_name }}.db "SELECT * FROM users WHERE username='admin';"
```

**Reset admin password:**
```python
# Inside Python console
from {{ module_name }}.user import InternalUserManager
usermanager = InternalUserManager(entity)
await usermanager.create_user_impl("admin", "newpassword", role="admin", level=0)
```

### External Usermanager Not Detected

**Check module registry:**
```bash
curl -k https://localhost/{{ module_name }}/api/modules/instances
```

**Verify usermanager template:**
- External usermanager must have `template: 'usermanager'` in module metadata
- Module must be registered and enabled

## Migration Guide

### From Old auth_service.py to New System

**Old System:**
- Redis-only user storage
- Simple hash-based authentication
- No user management features

**New System:**
- Database-backed persistence
- Full CRUD operations
- Role-based access control
- Account security features

**Migration Steps:**

1. Backup existing Redis user data (if any)
2. Start new system with .env admin credentials
3. Recreate users via REST API or gRPC
4. Test authentication flow
5. Update frontend to handle `password_change_required`

## Future Enhancements

- [ ] LDAP/Active Directory integration
- [ ] Two-factor authentication (2FA)
- [ ] Password complexity requirements
- [ ] Session management improvements
- [ ] Audit logging for user actions
- [ ] User profile management
- [ ] Email verification
- [ ] Password recovery via email

## See Also

- [REST API Documentation](./API_DOCUMENTATION_TEMPLATE.md)
- [VYRA Base Python - Database Access](../../../vyra_base_python/docs/database/)
- [gRPC Service Architecture](./GRPC_ARCHITECTURE.md)
- [Security Guide](./SECURITY_GUIDE.md)
