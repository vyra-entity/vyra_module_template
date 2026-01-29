"""
HTTP clients for REST API communication.

All HTTP clients should:
1. Inherit from BaseHttpClient
2. Use singleton pattern (one instance per base_url)
3. Implement domain-specific methods using self.get(), self.post(), etc.

SETUP:
1. Copy base_client.py from v2_modulemanager/src/rest_api/clients/http/
2. Create specialized clients (see __init__.py in clients/ for examples)
"""
