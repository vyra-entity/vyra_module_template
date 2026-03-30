"""
Hardware Registry Client

Manages hardware nodes and module placements for container orchestration.
Provides modernized version of hardware_registry.py with clean architecture.
"""
import asyncio
from {{ module_name }}.logging_config import get_logger, log_exception, log_function_call, log_function_result
import os
import socket
from dataclasses import dataclass, field
from datetime import datetime
from typing import Dict, List, Optional, Set
from enum import Enum

from .base_client import BaseHttpClient

logger = get_logger(__name__)


class NodeRole(Enum):
    """Docker Swarm Node Role"""
    MANAGER = "manager"
    WORKER = "worker"
    STANDALONE = "standalone"


@dataclass
class HardwareCapabilities:
    """Hardware capabilities of a node"""
    gpu: bool = False
    high_memory: bool = False  # > 16GB
    high_cpu: bool = False     # > 8 cores
    ssd: bool = False
    custom_tags: Set[str] = field(default_factory=set)
    
    def matches_requirements(self, requirements: Dict) -> bool:
        """Check if node meets requirements"""
        if requirements.get('gpu') and not self.gpu:
            return False
        if requirements.get('high_memory') and not self.high_memory:
            return False
        if requirements.get('high_cpu') and not self.high_cpu:
            return False
        if requirements.get('ssd') and not self.ssd:
            return False
        
        required_tags = set(requirements.get('tags', []))
        if required_tags and not required_tags.issubset(self.custom_tags):
            return False
        
        return True


@dataclass
class HardwareNode:
    """Represents a hardware node with Container Manager"""
    node_id: str
    hostname: str
    container_manager_url: str
    auth_token: str
    
    # Hardware info
    role: NodeRole
    cpu_cores: int
    memory_total_gb: float
    memory_available_gb: float
    disk_total_gb: float
    disk_available_gb: float
    capabilities: HardwareCapabilities
    
    # Status
    is_healthy: bool = True
    last_health_check: datetime = field(default_factory=datetime.now)
    last_error: Optional[str] = None
    
    # Deployed modules
    deployed_modules: Dict[str, str] = field(default_factory=dict)  # instance_id -> module_name
    
    def get_load_score(self) -> float:
        """
        Calculate load score (lower = better).
        
        Based on:
        - Memory usage
        - Number of deployed modules
        """
        if self.memory_total_gb == 0:
            memory_usage_percent = 0
        else:
            memory_usage_percent = (
                (self.memory_total_gb - self.memory_available_gb) / 
                self.memory_total_gb * 100
            )
        
        score = (
            memory_usage_percent * 0.5 +  # 50% weight for memory
            len(self.deployed_modules) * 10  # 10 points per module
        )
        
        return score
    
    def can_deploy(self, requirements: Dict) -> bool:
        """Check if node can deploy module with given requirements"""
        if not self.is_healthy:
            return False
        
        if self.memory_available_gb < requirements.get('min_memory_gb', 0):
            return False
        if self.cpu_cores < requirements.get('min_cpu_cores', 0):
            return False
        if self.disk_available_gb < requirements.get('min_disk_gb', 0):
            return False
        if not self.capabilities.matches_requirements(requirements):
            return False
        
        return True


class HardwareRegistryClient:
    """
    Hardware Registry for multi-node orchestration.
    
    Manages hardware nodes and their module placements with automatic
    health checking and load balancing support.
    
    Features:
    - Multi-node registration and discovery
    - Automatic health monitoring
    - Load-based node selection
    - Module placement tracking
    """
    
    # Singleton instance
    _instance: Optional['HardwareRegistryClient'] = None
    _lock = asyncio.Lock()
    
    def __new__(cls):
        """Singleton pattern"""
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance
    
    def __init__(self, health_check_interval: int = 60):
        """
        Initialize Hardware Registry.
        
        Args:
            health_check_interval: Seconds between health checks
        """
        if hasattr(self, '_initialized'):
            return
        
        self.nodes: Dict[str, HardwareNode] = {}
        self.health_check_interval = health_check_interval
        self._health_check_task: Optional[asyncio.Task] = None
        self._http_clients: Dict[str, BaseHttpClient] = {}
        self._initialized = True
        
        logger.info("🔧 Hardware Registry initialized")
    
    async def start(self):
        """Start background tasks and register local node"""
        if not self._health_check_task:
            self._health_check_task = asyncio.create_task(
                self._health_check_loop()
            )
            logger.info("✅ Hardware Registry started")
            
            # Auto-register local node with retry
            asyncio.create_task(self._auto_register_local_node())
    
    async def stop(self):
        """Stop background tasks and cleanup"""
        if self._health_check_task:
            self._health_check_task.cancel()
            try:
                await self._health_check_task
            except asyncio.CancelledError:
                pass
        
        # Close all HTTP clients
        for client in self._http_clients.values():
            await client.close()
        
        logger.info("✅ Hardware Registry stopped")
    
    async def _auto_register_local_node(self):
        """Auto-register local node with retry logic"""
        hostname = socket.gethostname()
        container_manager_url = os.getenv(
            "CONTAINER_MANAGER_URL",
            "http://container-manager:8080"
        )
        
        # Load token
        token = ""
        token_file = os.getenv("MANAGER_TOKEN_FILE", "/run/secrets/manager_token")
        if os.path.exists(token_file):
            with open(token_file, 'r') as f:
                token = f.read().strip()
        
        # Retry with exponential backoff
        max_retries = 5
        for attempt in range(max_retries):
            try:
                await self.register_node(
                    node_id="local",
                    hostname=hostname,
                    container_manager_url=container_manager_url,
                    auth_token=token,
                    auto_fetch_info=True
                )
                logger.info(f"✅ Local node registered: {hostname}")
                return
            except Exception as e:
                delay = 2 ** attempt
                if attempt < max_retries - 1:
                    logger.warning(
                        f"Failed to register local node (attempt {attempt + 1}): {e}. "
                        f"Retrying in {delay}s..."
                    )
                    await asyncio.sleep(delay)
                else:
                    logger.error(
                        f"❌ Failed to register local node after {max_retries} attempts. "
                        f"Container Manager may be unreachable."
                    )
    
    def _get_client(self, node: HardwareNode) -> BaseHttpClient:
        """Get or create HTTP client for node"""
        if node.node_id not in self._http_clients:
            self._http_clients[node.node_id] = BaseHttpClient(
                base_url=node.container_manager_url,
                auth_token=node.auth_token,
                timeout=10,
                verify_ssl=False
            )
        return self._http_clients[node.node_id]
    
    async def register_node(
        self,
        node_id: str,
        hostname: str,
        container_manager_url: str,
        auth_token: str,
        auto_fetch_info: bool = True
    ) -> HardwareNode:
        """
        Register new hardware node.
        
        Args:
            node_id: Unique node identifier
            hostname: Node hostname
            container_manager_url: Container Manager URL
            auth_token: Auth token for Container Manager API
            auto_fetch_info: Automatically fetch hardware info
            
        Returns:
            HardwareNode instance
        """
        if node_id in self.nodes:
            logger.warning(f"Node {node_id} already registered, updating")
        
        node = HardwareNode(
            node_id=node_id,
            hostname=hostname,
            container_manager_url=container_manager_url,
            auth_token=auth_token,
            role=NodeRole.STANDALONE,
            cpu_cores=0,
            memory_total_gb=0,
            memory_available_gb=0,
            disk_total_gb=0,
            disk_available_gb=0,
            capabilities=HardwareCapabilities()
        )
        
        if auto_fetch_info:
            try:
                await self._fetch_node_info(node)
            except Exception as e:
                logger.error(f"Failed to fetch info for node {node_id}: {e}")
                node.is_healthy = False
                node.last_error = str(e)
        
        self.nodes[node_id] = node
        logger.info(f"✅ Registered node: {node_id} ({hostname})")
        
        return node
    
    async def unregister_node(self, node_id: str):
        """Remove node from registry"""
        if node_id in self.nodes:
            del self.nodes[node_id]
            if node_id in self._http_clients:
                await self._http_clients[node_id].close()
                del self._http_clients[node_id]
            logger.info(f"Unregistered node: {node_id}")
    
    def get_node(self, node_id: str) -> Optional[HardwareNode]:
        """Get node by ID"""
        return self.nodes.get(node_id)
    
    def get_all_nodes(self) -> List[HardwareNode]:
        """Get all nodes"""
        return list(self.nodes.values())
    
    def get_healthy_nodes(self) -> List[HardwareNode]:
        """Get only healthy nodes"""
        return [node for node in self.nodes.values() if node.is_healthy]
    
    async def find_suitable_nodes(
        self,
        requirements: Dict,
        count: int = 1
    ) -> List[HardwareNode]:
        """
        Find suitable nodes for deployment.
        
        Args:
            requirements: Hardware requirements dict
            count: Number of nodes needed
            
        Returns:
            List of suitable nodes, sorted by load score
        """
        suitable = [
            node for node in self.get_healthy_nodes()
            if node.can_deploy(requirements)
        ]
        
        # Sort by load score (ascending = less loaded first)
        suitable.sort(key=lambda n: n.get_load_score())
        
        return suitable[:count]
    
    async def place_module(
        self,
        module_name: str,
        instance_id: str,
        node_id: str
    ):
        """Register module placement on node"""
        node = self.nodes.get(node_id)
        if not node:
            raise ValueError(f"Node {node_id} not found")
        
        node.deployed_modules[instance_id] = module_name
        logger.info(f"Module placed: {module_name}/{instance_id} on {node_id}")
    
    async def remove_module(
        self,
        instance_id: str,
        node_id: Optional[str] = None
    ):
        """Remove module placement"""
        if node_id:
            node = self.nodes.get(node_id)
            if node and instance_id in node.deployed_modules:
                del node.deployed_modules[instance_id]
                logger.info(f"Module removed: {instance_id} from {node_id}")
        else:
            # Search all nodes
            for node in self.nodes.values():
                if instance_id in node.deployed_modules:
                    del node.deployed_modules[instance_id]
                    logger.info(f"Module removed: {instance_id} from {node.node_id}")
                    break
    
    async def find_module_node(self, instance_id: str) -> Optional[HardwareNode]:
        """Find node where module is deployed"""
        for node in self.nodes.values():
            if instance_id in node.deployed_modules:
                return node
        return None
    
    async def get_node_stats(self, node_id: str) -> Dict:
        """Get current stats from a node"""
        node = self.nodes.get(node_id)
        if not node:
            raise ValueError(f"Node {node_id} not found")
        
        client = self._get_client(node)
        
        try:
            result = await client.get("/hardware/stats")
            return result.get("data", {})
        except Exception as e:
            logger.warning(f"Failed to get stats from {node_id}: {e}")
            return {
                "cpu_percent": 0,
                "memory_percent": 0,
                "disk_percent": 0,
                "error": str(e)
            }
    
    async def get_module_stats(
        self,
        module_name: str,
        instance_id: str,
        node_id: Optional[str] = None
    ) -> Dict:
        """Get module statistics (CPU, RAM, disk, etc.)"""
        if not node_id:
            node = await self.find_module_node(instance_id)
            if not node:
                raise ValueError(
                    f"Module {module_name}/{instance_id} not found on any node"
                )
        else:
            node = self.nodes.get(node_id)
            if not node:
                raise ValueError(f"Node {node_id} not found")
        
        client = self._get_client(node)
        result = await client.get(
            f"/modules/{module_name}/{instance_id}/stats"
        )
        return result.get("data", {})
    
    async def get_all_module_stats(self) -> List[Dict]:
        """Get statistics for all modules on all nodes"""
        all_stats = []
        
        tasks = [
            self._get_node_all_stats(node)
            for node in self.nodes.values()
        ]
        
        results = await asyncio.gather(*tasks, return_exceptions=True)
        
        for result in results:
            if isinstance(result, list):
                all_stats.extend(result)
            elif isinstance(result, Exception):
                logger.error(f"Failed to get stats: {result}")
        
        return all_stats
    
    async def _get_node_all_stats(self, node: HardwareNode) -> List[Dict]:
        """Get all module stats from a node"""
        try:
            client = self._get_client(node)
            result = await client.get("/modules/stats/all")
            data = result.get("data", {})
            return data.get('modules', [])
        except Exception as e:
            logger.debug(f"Stats unavailable for {node.node_id}: {e}")
            return []
    
    async def _fetch_node_info(self, node: HardwareNode):
        """Fetch hardware info from Container Manager"""
        client = self._get_client(node)
        result = await client.get("/hardware/info")
        
        if not result.get("success"):
            raise Exception("API returned success=false")
        
        data = result.get("data", {})
        hw = data.get('hardware', {})
        
        # Update node info
        node.role = NodeRole(hw['role'])
        node.cpu_cores = hw['cpu_cores']
        node.memory_total_gb = hw['memory_total_gb']
        node.memory_available_gb = hw['memory_available_gb']
        node.disk_total_gb = hw['disk_total_gb']
        node.disk_available_gb = hw['disk_available_gb']
        
        # Parse capabilities
        caps = hw.get('capabilities', [])
        node.capabilities = HardwareCapabilities(
            gpu='gpu' in caps,
            high_memory='high_memory' in caps or node.memory_total_gb > 16,
            high_cpu='high_cpu' in caps or node.cpu_cores > 8,
            ssd='ssd' in caps,
            custom_tags=set(caps)
        )
        
        node.is_healthy = hw.get('is_healthy', True)
        node.last_health_check = datetime.now()
        node.last_error = None
    
    async def _health_check_loop(self):
        """Background task: periodic health checks"""
        logger.info(
            f"Health check loop started (interval: {self.health_check_interval}s)"
        )
        
        while True:
            try:
                await asyncio.sleep(self.health_check_interval)
                
                if not self.nodes:
                    continue
                
                tasks = [
                    self._health_check_node(node)
                    for node in self.nodes.values()
                ]
                
                await asyncio.gather(*tasks, return_exceptions=True)
                
            except asyncio.CancelledError:
                logger.info("Health check loop cancelled")
                break
            except Exception as e:
                logger.error(f"Error in health check loop: {e}")
    
    async def _health_check_node(self, node: HardwareNode):
        """Health check for a single node"""
        try:
            await self._fetch_node_info(node)
        except Exception as e:
            logger.warning(f"Health check failed for {node.node_id}: {e}")
            node.is_healthy = False
            node.last_error = str(e)


# Global singleton instance
hardware_registry_client = HardwareRegistryClient()
