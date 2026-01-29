"""
Example Service - Business logic template

Template for encapsulating business logic separate from API endpoints.

CUSTOMIZATION:
- Replace ExampleService with your service name
- Add domain-specific methods
- Integrate with clients (HTTP/gRPC)
- Add error handling and validation
"""
import logging
from typing import List, Dict, Any, Optional

logger = logging.getLogger(__name__)


class ExampleService:
    """
    Example service demonstrating business logic patterns.
    
    Best practices:
    - Keep services stateless or use dependency injection
    - Separate business logic from API endpoints
    - Use clients for external communication
    - Handle errors gracefully
    """
    
    def __init__(self):
        """Initialize service with dependencies"""
        # TODO: Initialize clients, database connections, etc.
        # Example:
        # from ..clients.http.sensor import sensor_client
        # self.sensor_client = sensor_client
        logger.info("✅ ExampleService initialized")
    
    async def get_items(self, include_inactive: bool = False) -> List[Dict[str, Any]]:
        """
        Get list of items.
        
        Args:
            include_inactive: Include inactive items
            
        Returns:
            List of item dictionaries
        """
        try:
            # TODO: Implement actual logic
            # Example:
            # items = await self.sensor_client.get_all()
            # if not include_inactive:
            #     items = [i for i in items if i.get("active")]
            # return items
            
            logger.info(f"📋 Getting items (include_inactive={include_inactive})")
            return [
                {"id": "1", "name": "Example Item 1", "active": True},
                {"id": "2", "name": "Example Item 2", "active": False}
            ]
            
        except Exception as e:
            logger.error(f"❌ Failed to get items: {e}")
            raise
    
    async def get_item(self, item_id: str) -> Optional[Dict[str, Any]]:
        """
        Get specific item by ID.
        
        Args:
            item_id: Item identifier
            
        Returns:
            Item dictionary or None if not found
        """
        try:
            logger.info(f"🔍 Getting item: {item_id}")
            
            # TODO: Implement actual logic
            # Example:
            # return await self.sensor_client.get_by_id(item_id)
            
            if item_id == "1":
                return {"id": "1", "name": "Example Item 1", "active": True}
            return None
            
        except Exception as e:
            logger.error(f"❌ Failed to get item {item_id}: {e}")
            raise
    
    async def create_item(self, item_data: Dict[str, Any]) -> Dict[str, Any]:
        """
        Create new item.
        
        Args:
            item_data: Item data to create
            
        Returns:
            Created item with ID
        """
        try:
            logger.info(f"➕ Creating item: {item_data.get('name')}")
            
            # TODO: Implement actual logic
            # Validate data
            # Call external services
            # Store in database
            
            return {
                "id": "new_id",
                **item_data,
                "created_at": "2026-01-29T12:00:00Z"
            }
            
        except Exception as e:
            logger.error(f"❌ Failed to create item: {e}")
            raise
    
    async def update_item(
        self, 
        item_id: str, 
        item_data: Dict[str, Any]
    ) -> Optional[Dict[str, Any]]:
        """
        Update existing item.
        
        Args:
            item_id: Item identifier
            item_data: Updated item data
            
        Returns:
            Updated item or None if not found
        """
        try:
            logger.info(f"✏️ Updating item: {item_id}")
            
            # TODO: Implement actual logic
            # Check if exists
            # Validate update data
            # Apply updates
            # Return updated item
            
            return {
                "id": item_id,
                **item_data,
                "updated_at": "2026-01-29T12:00:00Z"
            }
            
        except Exception as e:
            logger.error(f"❌ Failed to update item {item_id}: {e}")
            raise
    
    async def delete_item(self, item_id: str) -> bool:
        """
        Delete item.
        
        Args:
            item_id: Item identifier
            
        Returns:
            True if deleted successfully
        """
        try:
            logger.info(f"🗑️ Deleting item: {item_id}")
            
            # TODO: Implement actual logic
            # Check if exists
            # Perform cleanup
            # Delete item
            
            return True
            
        except Exception as e:
            logger.error(f"❌ Failed to delete item {item_id}: {e}")
            raise


# Global service instance (singleton)
example_service = ExampleService()


# TODO: Add more services as needed
# Example:
# class SensorService:
#     """Sensor-specific business logic"""
#     pass
# 
# sensor_service = SensorService()
