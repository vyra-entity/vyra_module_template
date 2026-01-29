"""
WebSocket Router - Real-time communication example

Template for WebSocket-based status updates and notifications.

CUSTOMIZATION:
- Modify ConnectionManager for module-specific subscriptions
- Add custom message types
- Integrate with module business logic
"""
from fastapi import APIRouter, WebSocket, WebSocketDisconnect
from typing import Dict, Set
import json
import logging

logger = logging.getLogger(__name__)

router = APIRouter()


class ConnectionManager:
    """
    Manages WebSocket connections and message broadcasting.
    
    Features:
    - Client tracking by ID
    - Topic-based subscriptions
    - Broadcast and targeted messaging
    """
    
    def __init__(self):
        self.active_connections: Dict[str, Set[WebSocket]] = {}
        self.topic_subscriptions: Dict[str, Set[WebSocket]] = {}
    
    async def connect(self, websocket: WebSocket, client_id: str):
        """Accept and register new WebSocket connection"""
        await websocket.accept()
        if client_id not in self.active_connections:
            self.active_connections[client_id] = set()
        self.active_connections[client_id].add(websocket)
        logger.info(f"✅ Client {client_id} connected via WebSocket")
    
    def disconnect(self, websocket: WebSocket, client_id: str):
        """Unregister WebSocket connection"""
        if client_id in self.active_connections:
            self.active_connections[client_id].discard(websocket)
            if not self.active_connections[client_id]:
                del self.active_connections[client_id]
        
        # Remove from all topic subscriptions
        for topic in list(self.topic_subscriptions.keys()):
            self.topic_subscriptions[topic].discard(websocket)
            if not self.topic_subscriptions[topic]:
                del self.topic_subscriptions[topic]
        
        logger.info(f"🔌 Client {client_id} disconnected from WebSocket")
    
    async def send_personal_message(self, message: str, websocket: WebSocket):
        """Send message to specific WebSocket"""
        try:
            await websocket.send_text(message)
        except Exception as e:
            logger.warning(f"❌ Failed to send message: {e}")
    
    async def send_to_client(self, message: str, client_id: str):
        """Send message to all connections of a client"""
        if client_id in self.active_connections:
            for websocket in self.active_connections[client_id].copy():
                try:
                    await websocket.send_text(message)
                except Exception as e:
                    logger.warning(f"❌ Failed to send to client {client_id}: {e}")
                    self.active_connections[client_id].discard(websocket)
    
    async def broadcast(self, message: str):
        """Broadcast message to all connected clients"""
        for client_connections in self.active_connections.values():
            for websocket in client_connections.copy():
                try:
                    await websocket.send_text(message)
                except Exception as e:
                    logger.warning(f"❌ Failed to broadcast: {e}")
    
    def subscribe_to_topic(self, websocket: WebSocket, topic: str):
        """Subscribe WebSocket to a topic"""
        if topic not in self.topic_subscriptions:
            self.topic_subscriptions[topic] = set()
        self.topic_subscriptions[topic].add(websocket)
        logger.info(f"📢 WebSocket subscribed to topic: {topic}")
    
    async def notify_topic(self, topic: str, data: dict):
        """Send notification to all subscribers of a topic"""
        if topic in self.topic_subscriptions:
            message = json.dumps({
                "type": "topic_update",
                "topic": topic,
                "data": data
            })
            
            for websocket in self.topic_subscriptions[topic].copy():
                try:
                    await websocket.send_text(message)
                except Exception as e:
                    logger.warning(f"❌ Failed to notify topic {topic}: {e}")
                    self.topic_subscriptions[topic].discard(websocket)


# Global connection manager
connection_manager = ConnectionManager()


@router.websocket("/status/{client_id}")
async def websocket_status_endpoint(websocket: WebSocket, client_id: str):
    """
    WebSocket endpoint for real-time status updates.
    
    Message types:
    - subscribe: {"type": "subscribe", "topic": "status"}
    - ping: {"type": "ping"}
    
    CUSTOMIZE: Add your module-specific message handling here.
    """
    await connection_manager.connect(websocket, client_id)
    
    try:
        while True:
            # Receive messages from client
            data = await websocket.receive_text()
            message_data = json.loads(data)
            
            message_type = message_data.get("type")
            
            if message_type == "subscribe":
                # Subscribe to a topic
                topic = message_data.get("topic")
                if topic:
                    connection_manager.subscribe_to_topic(websocket, topic)
                    await connection_manager.send_personal_message(
                        json.dumps({
                            "type": "subscribed",
                            "topic": topic
                        }),
                        websocket
                    )
            
            elif message_type == "ping":
                # Respond to ping with pong
                await connection_manager.send_personal_message(
                    json.dumps({"type": "pong"}),
                    websocket
                )
            
            # TODO: Add custom message types here
            # elif message_type == "your_custom_type":
            #     # Handle custom message
            #     pass
    
    except WebSocketDisconnect:
        connection_manager.disconnect(websocket, client_id)
    except Exception as e:
        logger.error(f"❌ WebSocket error for client {client_id}: {e}")
        connection_manager.disconnect(websocket, client_id)


# TODO: Add more WebSocket endpoints as needed
# Example:
# @router.websocket("/notifications/{user_id}")
# async def websocket_notifications(websocket: WebSocket, user_id: str):
#     await connection_manager.connect(websocket, user_id)
#     try:
#         while True:
#             data = await websocket.receive_text()
#             # Handle notifications
#     except WebSocketDisconnect:
#         connection_manager.disconnect(websocket, user_id)
