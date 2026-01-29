"""
gRPC clients for IPC via Unix Domain Sockets.

All gRPC clients should:
1. Inherit from BaseGrpcClient[TStub] with proper stub type
2. Use singleton pattern (one instance per socket_path)
3. Implement _create_stub() method
4. Use await self.get_stub() to access stub

SETUP:
1. Copy base_client.py from v2_modulemanager/src/rest_api/clients/grpc/
2. Create specialized clients (see __init__.py in clients/ for examples)
"""
