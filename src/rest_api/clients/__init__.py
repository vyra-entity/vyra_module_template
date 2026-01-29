"""
HTTP and gRPC clients for external service communication.

Structure:
- clients/http/: HTTP clients for REST APIs (use BaseHttpClient)
- clients/grpc/: gRPC clients for IPC (use BaseGrpcClient[TStub])

USAGE:
1. Copy base_client.py files from v2_modulemanager to both http/ and grpc/
2. Create specialized clients inheriting from base classes
3. Use singleton pattern per endpoint/socket

EXAMPLES:

HTTP Client:
```python
from .http.base_client import BaseHttpClient

class MyServiceClient(BaseHttpClient):
    def __init__(self, base_url: str = "http://myservice:8000"):
        super().__init__(base_url=base_url)
    
    async def get_data(self) -> Dict:
        return await self.get("/data")

my_service_client = MyServiceClient()
```

gRPC Client:
```python
from .grpc.base_client import BaseGrpcClient
from storage.interfaces.grpc_generated import myservice_pb2_grpc

class MyServiceGrpcClient(BaseGrpcClient[myservice_pb2_grpc.MyServiceStub]):
    def __init__(self):
        super().__init__(socket_path=Path('/tmp/myservice.sock'))
    
    def _create_stub(self, channel):
        return myservice_pb2_grpc.MyServiceStub(channel)
    
    async def call_method(self, request):
        stub = await self.get_stub()
        return await stub.MyMethod(request, timeout=self.timeout)

my_service_client = MyServiceGrpcClient()
```
"""
