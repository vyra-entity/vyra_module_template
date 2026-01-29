# REST API Client Architecture

## Overview

The v2_modulemanager REST API uses a modern, industrial-grade client architecture with the following principles:

1. **Singleton Pattern**: One client instance per endpoint (HTTP) or socket (gRPC)
2. **Base Classes**: Shared functionality in `BaseHttpClient` and `BaseGrpcClient`
3. **Type Safety**: Generic typing for gRPC stubs
4. **Industrial Standards**: Connection pooling, retry logic, comprehensive logging
5. **Clear Separation**: HTTP for external REST APIs, gRPC for internal IPC

## Directory Structure

```
src/rest_api/
├── clients/              # NEW: Modern client architecture
│   ├── __init__.py
│   ├── http/             # HTTP clients for REST APIs
│   │   ├── __init__.py
│   │   ├── base_client.py      # Singleton HTTP base class
│   │   ├── hardware.py         # Hardware registry operations
│   │   └── module_http.py      # Module/container operations
│   └── grpc/             # gRPC clients for IPC
│       ├── __init__.py
│       ├── base_client.py      # Singleton gRPC base class
│       ├── user_ipc.py         # User authentication
│       └── module_ipc.py       # Module registry IPC
├── core/                 # Configuration and utilities
├── hardware/             # Hardware management endpoints
├── module/               # Module management endpoints
├── services/             # Business logic services
└── websocket/            # WebSocket endpoints
```

## HTTP Client Architecture

### BaseHttpClient

**File**: `src/rest_api/clients/http/base_client.py`

**Features**:
- **Singleton per base_url**: One instance per endpoint prevents connection proliferation
- **Connection Pooling**: 100 max connections, 30 per host, TCP keep-alive enabled
- **Exponential Backoff**: 3 retry attempts with 2^n second delays
- **Request Logging**: Comprehensive logging of all HTTP operations
- **Health Checks**: Built-in `/health` endpoint checking

**Usage**:
```python
from .base_client import BaseHttpClient

class MyServiceClient(BaseHttpClient):
    def __init__(self, base_url: str = "http://myservice:8000"):
        super().__init__(base_url=base_url)
    
    async def get_data(self) -> Dict:
        return await self.get("/data")
    
    async def create_item(self, item: Dict) -> Dict:
        return await self.post("/items", json=item)

# Singleton instance - automatically shared
my_service_client = MyServiceClient()
```

**Key Methods**:
- `get(endpoint, params, timeout)`: GET request
- `post(endpoint, json, params, timeout)`: POST request
- `put(endpoint, json, timeout)`: PUT request
- `delete(endpoint, params, timeout)`: DELETE request
- `health_check()`: Check service availability

### ModuleHttpClient

**File**: `src/rest_api/clients/http/module_http.py`

**Purpose**: Container Manager HTTP operations (module lifecycle, stats, backups)

**Methods**:
- `install_module()`: Install new module instance
- `remove_module()`: Remove module instance
- `update_module()`: Update module version
- `restart_module()`, `start_module()`, `stop_module()`: Container control
- `get_module_stats()`, `get_all_module_stats()`: Performance metrics
- `create_backup()`, `rollback_instance()`, `cleanup_backup()`: Backup operations
- `update_nfs_interfaces()`: Sync ROS2 interfaces to NFS
- `list_installed_modules()`, `list_available_modules()`: Module queries

**Usage**:
```python
from ..clients.http.module_http import module_http_client

# Install module
result = await module_http_client.install_module(
    module_name="v2_sensor",
    instance_id="abc123",
    version="1.0.0",
    repository_info={...}
)

# Get stats
stats = await module_http_client.get_module_stats("v2_sensor", "abc123")
```

### HardwareRegistryClient

**File**: `src/rest_api/clients/http/hardware.py`

**Purpose**: Hardware node management and load balancing

**Features**:
- Node registration with capabilities (CPU, memory, GPUs, sensors)
- Load-based node selection for module placement
- Background health monitoring loop
- Module placement tracking

**Methods**:
- `register_node()`, `unregister_node()`: Node lifecycle
- `find_suitable_nodes()`: Load-based node selection with scoring
- `place_module()`, `remove_module()`: Module placement tracking
- `get_node_stats()`, `get_module_stats()`: Node/module metrics
- `start()`, `stop()`: Background task management

**Usage**:
```python
from ..clients.http.hardware import hardware_registry_client

# Start background health checks
await hardware_registry_client.start()

# Find best node for module
nodes = await hardware_registry_client.find_suitable_nodes(
    module_name="v2_vision",
    required_capabilities={"gpu": True, "min_memory_gb": 8}
)

# Register module placement
await hardware_registry_client.place_module(
    node_id="node1",
    instance_id="abc123",
    module_name="v2_vision"
)
```

## gRPC Client Architecture

### BaseGrpcClient

**File**: `src/rest_api/clients/grpc/base_client.py`

**Features**:
- **Singleton per socket_path**: One instance per Unix Domain Socket
- **Generic Typing**: `BaseGrpcClient[TStub]` provides compile-time type safety
- **Auto-Reconnection**: Transparent reconnection on connection loss
- **Unix Domain Sockets**: Fast, secure IPC within container
- **Abstract Stub Creation**: Subclasses implement `_create_stub()`

**Usage**:
```python
from .base_client import BaseGrpcClient
from storage.interfaces.grpc_generated import myservice_pb2_grpc

class MyServiceGrpcClient(BaseGrpcClient[myservice_pb2_grpc.MyServiceStub]):
    def __init__(self):
        super().__init__(
            socket_path=Path('/tmp/myservice.sock'),
            timeout=10.0
        )
    
    def _create_stub(self, channel):
        return myservice_pb2_grpc.MyServiceStub(channel)
    
    async def call_method(self, request):
        stub = await self.get_stub()
        return await stub.MyMethod(request, timeout=self.timeout)

my_service_client = MyServiceGrpcClient()
```

**Key Methods**:
- `get_stub()`: Get typed stub instance (auto-reconnects if needed)
- `ensure_connected()`: Manually verify connection
- `close()`: Close connection

### UserManagerGrpcClient

**File**: `src/rest_api/clients/grpc/user_ipc.py`

**Purpose**: User authentication and management via gRPC

**Socket**: `/tmp/vyra_sockets/vyra_usermanager_service.sock`

**Methods**:
- `authenticate_user()`: Verify username/password
- `create_user()`, `list_users()`: User management
- `change_password()`: Password updates
- `initialize_default_admin()`: Bootstrap admin account

**Usage**:
```python
from ..clients.grpc.user_ipc import user_manager_grpc_client

# Authenticate
response = await user_manager_grpc_client.authenticate_user(
    username="admin",
    password="password123"
)

if response.success:
    print(f"User authenticated: {response.user.username}")
```

### ModuleRegistryGrpcClient

**File**: `src/rest_api/clients/grpc/module_ipc.py`

**Purpose**: Module registry IPC for permissions and metadata

**Socket**: `/workspace/storage/module_registry_service.sock`

**Methods**:
- `register_module_permission()`, `deregister_module_permission()`: SROS2 permissions
- `register_module()`, `deregister_module()`: Module lifecycle
- `get_registered_modules()`: Query registered modules
- `update_module_health()`: Report module health status

**Usage**:
```python
from ..clients.grpc.module_ipc import ModuleRegistryGrpcClient

ipc_client = ModuleRegistryGrpcClient()

# Register module permissions
await ipc_client.register_module_permission(
    module_id="v2_sensor_abc123",
    module_name="v2_sensor",
    base_node_name="sensor_node",
    domain_id=0,
    function_scope=[{"service": "get_data"}]
)
```

## Migration Guide

### Replacing Old `api/` Imports

**Old structure** (deprecated):
```python
from ..api.container_manager_client import ContainerManagerClient
from ..api.hardware_registry import hardware_registry
from ..api.ipc_service import ipc_service
from ..api.module_registry_client import ModuleRegistryGrpcClient
```

**New structure** (current):
```python
# HTTP clients
from ..clients.http.module_http import ModuleHttpClient, module_http_client
from ..clients.http.hardware import HardwareRegistryClient, hardware_registry_client

# gRPC clients
from ..clients.grpc.user_ipc import UserManagerGrpcClient, user_manager_grpc_client
from ..clients.grpc.module_ipc import ModuleRegistryGrpcClient
```

### Example Migration

**Before**:
```python
class ModuleService:
    def __init__(self):
        self.container_client = ContainerManagerClient(
            base_url="http://container-manager:8080",
            auth_token=""
        )
        self.ipc_service = ipc_service
```

**After**:
```python
class ModuleService:
    def __init__(self):
        # Singleton HTTP client
        self.container_client = ModuleHttpClient(
            base_url="http://container-manager:8080",
            auth_token=""
        )
        # Singleton gRPC client
        self.ipc_service = ModuleRegistryGrpcClient()
```

## Performance Characteristics

### HTTP Clients

- **Connection Pooling**: Reuses TCP connections → ~10ms saved per request
- **DNS Caching**: 300s TTL → eliminates repeated DNS lookups
- **Keep-Alive**: Long-lived connections → ~20ms saved on TLS handshake
- **Retry Logic**: Exponential backoff → resilient to transient failures

**Expected Latency**:
- First request to new endpoint: ~50-100ms (DNS + TCP + TLS)
- Subsequent requests (pooled): ~5-20ms (application logic only)

### gRPC Clients

- **Unix Domain Sockets**: No network stack overhead → ~0.1-1ms latency
- **Protobuf Serialization**: Binary format → ~50% smaller than JSON
- **Connection Reuse**: Single connection per socket → minimal overhead

**Expected Latency**:
- UDS gRPC call: ~1-5ms (including serialization)
- Network gRPC call: ~10-30ms (for comparison)

## Best Practices

1. **Always use singleton instances**: Prevents connection proliferation
   ```python
   # ✅ Correct
   from ..clients.http.module_http import module_http_client
   result = await module_http_client.install_module(...)
   
   # ❌ Incorrect (creates new connection each time)
   client = ModuleHttpClient(...)
   ```

2. **Use type hints with gRPC clients**: Leverage Generic[TStub]
   ```python
   class MyClient(BaseGrpcClient[myservice_pb2_grpc.MyServiceStub]):
       async def call(self):
           stub = await self.get_stub()  # Type: MyServiceStub
           return await stub.Method(...)  # IDE autocomplete works!
   ```

3. **Handle errors appropriately**:
   ```python
   try:
       result = await client.get_data()
   except aiohttp.ClientError as e:
       logger.error(f"HTTP request failed: {e}")
   except grpc.aio.AioRpcError as e:
       logger.error(f"gRPC call failed: {e.code()}: {e.details()}")
   ```

4. **Use background tasks for health checks**:
   ```python
   @asynccontextmanager
   async def lifespan(app: FastAPI):
       await hardware_registry_client.start()  # Starts health loop
       yield
       await hardware_registry_client.stop()
   ```

5. **Set appropriate timeouts**:
   ```python
   # Short timeout for quick operations
   result = await client.get("/health", timeout=5)
   
   # Long timeout for heavy operations
   result = await client.post("/install", json=data, timeout=300)
   ```

## Troubleshooting

### HTTP Connection Issues

**Problem**: "Max retries exceeded"
**Solution**: Check service availability with `curl http://service:port/health`

**Problem**: "Connection pool is full"
**Solution**: Increase `TCPConnector` limits in `BaseHttpClient.__init__()`

**Problem**: "SSL certificate verification failed"
**Solution**: Set `ssl=False` in connector or configure proper certs

### gRPC Connection Issues

**Problem**: "Failed to connect to UDS"
**Solution**: Verify socket file exists and has correct permissions
```bash
ls -la /workspace/storage/*.sock
```

**Problem**: "Stub not initialized"
**Solution**: Call `await client.ensure_connected()` before use

**Problem**: "Connection lost during call"
**Solution**: BaseGrpcClient auto-reconnects; retry the operation

## See Also

- [API Documentation Template](./API_DOCUMENTATION_TEMPLATE.md)
- [ROS2 Security Guide](./ROS2_SECURITY_GUIDE.md)
- [Deployment Guide](./DEPLOYMENT.md)
