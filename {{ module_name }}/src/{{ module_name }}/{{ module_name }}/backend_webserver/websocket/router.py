"""
WebSocket router for real-time status updates
"""
from fastapi import APIRouter, WebSocket, WebSocketDisconnect
from typing import Dict, Set
import json
import asyncio
from datetime import datetime
from {{ module_name }}.logging_config import get_logger

from ..core.dependencies import module_operations
from ..services.feed_streamer import FeedStreamer, FeedMessage
from ..services.plugin_bridge import PluginBridge
from ...container_injection import container
from .service import (
    ConnectionManager,
    connection_manager,
    notify_operation_update,
    operation_monitor,
)

logger = get_logger(__name__)

router = APIRouter()

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
    fm = FeedStreamer.get_instance()
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
        fm.unsubscribe("", queue)
        logger.info("Client disconnected from module_feed WebSocket")


@router.websocket("/plugin/{plugin_id}/{channel}")
async def websocket_plugin_endpoint(websocket: WebSocket, plugin_id: str, channel: str):
    """
    Bidirectional WebSocket endpoint for plugin UI ↔ Logic communication.

    URL parameters
    --------------
    plugin_id : str
        The plugin identifier (e.g. ``"counter-widget"``).  Used for logging.
    channel : str
        The event channel within that plugin (e.g. ``"state"``, ``"command"``).

    Protocol (JSON frames)
    ----------------------
    Server → Client:
        ``{"type": "plugin_event", "plugin_id": ..., "channel": ..., "data": {...}}``
        ``{"type": "history_batch", "items": [...]}``
        ``{"type": "pong"}``

    Client → Server:
        ``{"type": "client_to_server", "data": {...}}``   — forwarded to backend handlers
        ``{"type": "ping"}``                              — server responds with pong
    """
    await websocket.accept()
    bridge = PluginBridge.get_instance()
    queue = bridge.subscribe(channel)
    logger.info("Plugin WS connected: plugin_id=%s channel=%s", plugin_id, channel)

    # Replay history to new client
    history = bridge.get_history(channel)
    if history:
        try:
            await websocket.send_text(json.dumps({
                "type": "history_batch",
                "plugin_id": plugin_id,
                "channel": channel,
                "items": history,
            }))
        except Exception:
            pass

    async def _send_events() -> None:
        while True:
            payload = await queue.get()
            await websocket.send_text(json.dumps({
                "type": "plugin_event",
                "plugin_id": plugin_id,
                "channel": channel,
                "data": payload,
            }))

    async def _recv_messages() -> None:
        while True:
            try:
                raw = await websocket.receive_text()
                msg = json.loads(raw)
                if msg.get("type") == "ping":
                    await websocket.send_text(json.dumps({"type": "pong"}))
                elif msg.get("type") == "client_to_server":
                    await bridge.receive(channel, msg.get("data", {}))
            except WebSocketDisconnect:
                break
            except Exception:
                pass

    send_task = asyncio.create_task(_send_events())
    recv_task = asyncio.create_task(_recv_messages())

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
    finally:
        bridge.unsubscribe(channel, queue)
        logger.info("Plugin WS disconnected: plugin_id=%s channel=%s", plugin_id, channel)