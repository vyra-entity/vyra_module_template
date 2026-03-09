"""
WebSocket router for real-time status updates
"""
from fastapi import APIRouter, WebSocket, WebSocketDisconnect
from typing import Dict, Set
import json
import asyncio
from datetime import datetime
from v2_modulemanager.logging_config import get_logger

from ..core.dependencies import module_operations
from ..services.feed_manager import FeedManager, FeedMessage
from ...container_injection import container

logger = get_logger(__name__)

router = APIRouter()

# Connection manager for WebSocket connections
class ConnectionManager:
    def __init__(self):
        self.active_connections: Dict[str, Set[WebSocket]] = {}
        self.operation_subscriptions: Dict[str, Set[WebSocket]] = {}
    
    async def connect(self, websocket: WebSocket, client_id: str):
        await websocket.accept()
        if client_id not in self.active_connections:
            self.active_connections[client_id] = set()
        self.active_connections[client_id].add(websocket)
        logger.info(f"Client {client_id} connected via WebSocket")
    
    def disconnect(self, websocket: WebSocket, client_id: str):
        if client_id in self.active_connections:
            self.active_connections[client_id].discard(websocket)
            if not self.active_connections[client_id]:
                del self.active_connections[client_id]
        
        # Remove from operation subscriptions
        for operation_id in list(self.operation_subscriptions.keys()):
            self.operation_subscriptions[operation_id].discard(websocket)
            if not self.operation_subscriptions[operation_id]:
                del self.operation_subscriptions[operation_id]
        
        logger.info(f"Client {client_id} disconnected from WebSocket")
    
    async def send_personal_message(self, message: str, websocket: WebSocket):
        try:
            await websocket.send_text(message)
        except Exception as e:
            logger.warning(f"Failed to send message to WebSocket: {e}")
    
    async def send_to_client(self, message: str, client_id: str):
        if client_id in self.active_connections:
            for websocket in self.active_connections[client_id].copy():
                try:
                    await websocket.send_text(message)
                except Exception as e:
                    logger.warning(f"Failed to send message to client {client_id}: {e}")
                    self.active_connections[client_id].discard(websocket)
    
    async def broadcast(self, message: str):
        for client_connections in self.active_connections.values():
            for websocket in client_connections.copy():
                try:
                    await websocket.send_text(message)
                except Exception as e:
                    logger.warning(f"Failed to broadcast message: {e}")
    
    def subscribe_to_operation(self, websocket: WebSocket, operation_id: str):
        if operation_id not in self.operation_subscriptions:
            self.operation_subscriptions[operation_id] = set()
        self.operation_subscriptions[operation_id].add(websocket)
        logger.info(f"WebSocket subscribed to operation {operation_id}")
    
    async def notify_operation_update(self, operation_id: str, operation_data: dict):
        if operation_id in self.operation_subscriptions:
            message = json.dumps({
                "type": "operation_update",
                "operation_id": operation_id,
                "data": operation_data
            })
            
            for websocket in self.operation_subscriptions[operation_id].copy():
                try:
                    await websocket.send_text(message)
                except Exception as e:
                    logger.warning(f"Failed to send operation update: {e}")
                    self.operation_subscriptions[operation_id].discard(websocket)

# Global connection manager
connection_manager = ConnectionManager()

@router.websocket("/status/{client_id}")
async def websocket_status_endpoint(websocket: WebSocket, client_id: str):
    """WebSocket endpoint for real-time status updates"""
    await connection_manager.connect(websocket, client_id)
    
    try:
        while True:
            # Receive messages from client
            data = await websocket.receive_text()
            message_data = json.loads(data)
            
            message_type = message_data.get("type")
            
            if message_type == "subscribe_operation":
                operation_id = message_data.get("operation_id")
                if operation_id:
                    connection_manager.subscribe_to_operation(websocket, operation_id)
                    
                    # Send current status if available
                    if operation_id in module_operations:
                        current_status = module_operations[operation_id]
                        await connection_manager.send_personal_message(
                            json.dumps({
                                "type": "operation_update",
                                "operation_id": operation_id,
                                "data": current_status
                            }),
                            websocket
                        )
            
            elif message_type == "get_all_operations":
                # Send all current operations
                operations_data = {
                    "type": "all_operations",
                    "operations": dict(module_operations)
                }
                await connection_manager.send_personal_message(
                    json.dumps(operations_data),
                    websocket
                )
            
            elif message_type == "ping":
                # Respond to ping with pong
                await connection_manager.send_personal_message(
                    json.dumps({"type": "pong"}),
                    websocket
                )
    
    except WebSocketDisconnect:
        connection_manager.disconnect(websocket, client_id)
    except Exception as e:
        logger.error(f"WebSocket error for client {client_id}: {e}")
        connection_manager.disconnect(websocket, client_id)

@router.websocket("/operations/{operation_id}")
async def websocket_operation_endpoint(websocket: WebSocket, operation_id: str):
    """WebSocket endpoint for specific operation status"""
    await websocket.accept()
    
    try:
        # Send current status immediately if available
        if operation_id in module_operations:
            current_status = module_operations[operation_id]
            await websocket.send_text(json.dumps({
                "type": "operation_status",
                "operation_id": operation_id,
                "data": current_status
            }))
        
        # Subscribe to updates
        connection_manager.subscribe_to_operation(websocket, operation_id)
        
        # Keep connection alive and handle client messages
        while True:
            data = await websocket.receive_text()
            message_data = json.loads(data)
            
            if message_data.get("type") == "ping":
                await websocket.send_text(json.dumps({"type": "pong"}))
    
    except WebSocketDisconnect:
        if operation_id in connection_manager.operation_subscriptions:
            connection_manager.operation_subscriptions[operation_id].discard(websocket)
    except Exception as e:
        logger.error(f"WebSocket error for operation {operation_id}: {e}")

# Function to notify operation updates (call from services)
async def notify_operation_update(operation_id: str, operation_data: dict):
    """Notify all subscribed WebSocket connections about operation updates"""
    await connection_manager.notify_operation_update(operation_id, operation_data)

# Background task to monitor operation changes
async def operation_monitor():
    """Background task that monitors operation changes and sends updates"""
    last_operations_state = {}
    
    while True:
        try:
            current_operations = dict(module_operations)
            
            # Check for changes
            for operation_id, operation_data in current_operations.items():
                if (operation_id not in last_operations_state or 
                    last_operations_state[operation_id] != operation_data):
                    
                    # Operation changed, notify subscribers
                    await notify_operation_update(operation_id, operation_data)
            
            # Update last state
            last_operations_state = current_operations.copy()
            
            # Wait before next check
            await asyncio.sleep(1)
            
        except Exception as e:
            logger.error(f"Error in operation monitor: {e}")
            await asyncio.sleep(5)


@router.websocket("/module_feed")
async def websocket_module_feed_endpoint(websocket: WebSocket):
    """
    WebSocket endpoint for real-time module feed updates.

    Uses the in-process FeedManager singleton (no Redis).
    - Replays history ring-buffer to the new client immediately.
    - Then streams live FeedMessage objects as they arrive.
    - Simultaneously handles client-side ping/pong messages.
    """
    await websocket.accept()
    fm = FeedManager.get_instance()
    queue = fm.subscribe()
    logger.info("Client connected to module_feed WebSocket")

    async def _send_feeds() -> None:
        """Relay FeedManager queue → WebSocket (sender side)."""
        # 1. Send history ring-buffer as a SINGLE bulk message (no per-item WS frame flood)
        history = fm.get_history()
        if history:
            await websocket.send_text(json.dumps({
                "type": "history_batch",
                "items": history,
                "timestamp": datetime.now().isoformat(),
            }))
            logger.debug(f"📤 Sent history_batch with {len(history)} items to new client")

        # 2. Send current module state snapshot so the client immediately sees
        #    the last known state of every installed module (not just what's in history)
        try:
            comp = container.component()
            if comp and getattr(comp, "module_info_reader", None):
                last_states = comp.module_info_reader.get_all_last_statuses()
                if last_states:
                    await websocket.send_text(json.dumps({
                        "type": "state_snapshot",
                        "states": last_states,
                        "timestamp": datetime.now().isoformat(),
                    }))
                    logger.debug(f"📤 Sent state_snapshot for {len(last_states)} modules")
        except Exception as exc:
            logger.warning(f"Could not send state_snapshot: {exc}")

        # 3. Stream live messages from the queue
        while True:
            # queue.get() returns already-serialised dict (FeedManager.publish stores to_dict())
            payload: dict = await queue.get()
            await websocket.send_text(json.dumps({"type": "module_feed", "data": payload}))

    async def _recv_client() -> None:
        """Handle client → server messages (ping/pong, receiver side)."""
        while True:
            try:
                raw = await websocket.receive_text()
                msg = json.loads(raw)
                if msg.get("type") == "ping":
                    await websocket.send_text(json.dumps({"type": "pong"}))
            except WebSocketDisconnect:
                # Client closed the connection — stop the receiver loop cleanly
                break
            except Exception:
                pass

    send_task = asyncio.create_task(_send_feeds())
    recv_task = asyncio.create_task(_recv_client())

    try:
        _done, pending = await asyncio.wait(
            {send_task, recv_task},
            return_when=asyncio.FIRST_COMPLETED,
        )
        for task in pending:
            task.cancel()
            try:
                await task
            except (asyncio.CancelledError, WebSocketDisconnect):
                pass
    except WebSocketDisconnect:
        pass
    except Exception as e:
        logger.error(f"WebSocket error in module_feed: {e}")
    finally:
        fm.unsubscribe(queue)
        logger.info("Client disconnected from module_feed WebSocket")