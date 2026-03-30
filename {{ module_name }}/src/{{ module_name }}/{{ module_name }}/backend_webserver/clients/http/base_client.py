"""
Base HTTP Client with Singleton Pattern

Provides thread-safe HTTP client with connection pooling and retry logic
for industrial automation applications.
"""
import asyncio
from {{ module_name }}.logging_config import get_logger, log_exception, log_function_call, log_function_result
from typing import Dict, Optional, Any
from contextlib import asynccontextmanager
import aiohttp
from abc import ABC

from click import Option

logger = get_logger(__name__)


class BaseHttpClient(ABC):
    """
    Base HTTP client with singleton pattern and connection pooling.
    
    Features:
    - Thread-safe singleton per endpoint
    - Connection pooling for performance
    - Automatic retry with exponential backoff
    - Timeout management
    - Request/Response logging
    - SSL verification support
    
    Industrial automation standards:
    - Predictable timeout behavior
    - Detailed error logging for diagnostics
    - Connection health monitoring
    """
    
    _instances: Dict[tuple, Any] = {}
    _lock = asyncio.Lock()
    
    def __new__(cls, base_url: str, *args, **kwargs):
        """Singleton pattern: One instance per (class, base_url) combination."""
        # Create unique key from class and base_url
        instance_key = (cls.__name__, base_url)
        
        if instance_key not in cls._instances:
            instance = super().__new__(cls)
            cls._instances[instance_key] = instance
        return cls._instances[instance_key]
    
    def __init__(
        self,
        base_url: str,
        auth_token: Optional[str] = None,
        timeout: int = 30,
        max_retries: int = 3,
        verify_ssl: bool = True
    ):
        """
        Initialize HTTP client (only once per base_url).
        
        Args:
            base_url: Base URL for API endpoints
            auth_token: Bearer token for authentication
            timeout: Request timeout in seconds
            max_retries: Maximum number of retry attempts
            verify_ssl: Enable SSL certificate verification
        """
        # Prevent re-initialization
        if hasattr(self, '_initialized'):
            return
            
        self.base_url = base_url.rstrip("/")
        self.auth_token = auth_token
        self.timeout = aiohttp.ClientTimeout(total=timeout)
        self.max_retries = max_retries
        self.verify_ssl = verify_ssl
        
        self._session: Optional[aiohttp.ClientSession] = None
        self._initialized = True
        
        logger.info(
            f"🔧 {self.__class__.__name__} initialized "
            f"(endpoint: {self.base_url}, timeout: {timeout}s)"
        )
    
    @property
    def headers(self) -> Dict[str, str]:
        """Get default headers with authentication."""
        headers = {
            "Content-Type": "application/json",
            "Accept": "application/json"
        }
        if self.auth_token:
            headers["Authorization"] = f"Bearer {self.auth_token}"
        return headers
    
    @asynccontextmanager
    async def get_session(self):
        """
        Get or create aiohttp session with connection pooling.
        
        Yields:
            aiohttp.ClientSession: HTTP session
        """
        if self._session is None or self._session.closed:
            connector = aiohttp.TCPConnector(
                limit=100,  # Max connections
                limit_per_host=30,
                ttl_dns_cache=300,
                ssl=self.verify_ssl
            )
            self._session = aiohttp.ClientSession(
                connector=connector,
                timeout=self.timeout,
                headers=self.headers
            )
        
        try:
            yield self._session
        except Exception as e:
            logger.error(f"Session error: {e}")
            raise
    
    async def close(self):
        """Close HTTP session and cleanup resources."""
        if self._session and not self._session.closed:
            await self._session.close()
            logger.info(f"✅ {self.__class__.__name__} session closed")
    
    async def _request_with_retry(
        self,
        method: str,
        endpoint: str,
        retry_count: int = 0,
        **kwargs
    ) -> Dict[str, Any]:
        """
        Execute HTTP request with exponential backoff retry.
        
        Args:
            method: HTTP method (GET, POST, PUT, DELETE)
            endpoint: API endpoint path
            retry_count: Current retry attempt
            **kwargs: Additional request parameters
            
        Returns:
            Dict: JSON response data
            
        Raises:
            aiohttp.ClientError: On final retry failure
        """
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        
        # Merge default headers with any custom headers from kwargs
        request_headers = self.headers.copy()
        if 'headers' in kwargs:
            request_headers.update(kwargs.pop('headers'))
        kwargs['headers'] = request_headers
        
        try:
            async with self.get_session() as session:
                async with session.request(method, url, **kwargs) as response:
                    data = await response.json()
                    
                    # Log request for diagnostics
                    logger.debug(
                        f"{method} {endpoint} → {response.status} "
                        f"(attempt {retry_count + 1}/{self.max_retries})"
                    )
                    
                    if response.status >= 500 and retry_count < self.max_retries - 1:
                        # Server error - retry with backoff
                        wait_time = 2 ** retry_count
                        logger.warning(
                            f"⚠️ Server error {response.status}, "
                            f"retrying in {wait_time}s..."
                        )
                        await asyncio.sleep(wait_time)
                        return await self._request_with_retry(
                            method, endpoint, retry_count + 1, **kwargs
                        )
                    
                    if response.status >= 400:
                        logger.error(
                            f"❌ HTTP {response.status} {method} {endpoint}: {data}"
                        )
                    
                    return {
                        "status": response.status,
                        "data": data,
                        "success": 200 <= response.status < 300
                    }
                    
        except asyncio.TimeoutError:
            logger.error(f"❌ Timeout: {method} {endpoint}")
            if retry_count < self.max_retries - 1:
                wait_time = 2 ** retry_count
                await asyncio.sleep(wait_time)
                return await self._request_with_retry(
                    method, endpoint, retry_count + 1, **kwargs
                )
            raise
            
        except aiohttp.ClientError as e:
            logger.error(f"❌ Client error: {method} {endpoint}: {e}")
            raise
    
    async def get(self, endpoint: str, params: Optional[Dict] = None) -> Dict:
        """GET request."""
        return await self._request_with_retry("GET", endpoint, params=params)
    
    async def post(self, endpoint: str, **kwargs: Optional[Dict[str, Any]]) -> Dict:
        """POST request."""
        retry_count: int = kwargs.pop('retry_count', 0)
        return await self._request_with_retry("POST", endpoint, retry_count=retry_count, **kwargs)
    
    async def put(self, endpoint: str, data: Optional[Dict] = None) -> Dict:
        """PUT request."""
        return await self._request_with_retry("PUT", endpoint, json=data)
    
    async def delete(self, endpoint: str, **kwargs: Optional[Dict]) -> Dict:
        """DELETE request."""
        retry_count: int = kwargs.pop('retry_count', 0)
        return await self._request_with_retry("DELETE", endpoint, retry_count=retry_count, **kwargs)
    
    async def health_check(self) -> bool:
        """
        Check if service is healthy.
        
        Returns:
            bool: True if service responds within timeout
        """
        try:
            result = await self.get("/health")
            return result.get("success", False)
        except Exception as e:
            logger.warning(f"⚠️ Health check failed: {e}")
            return False
