"""
WebSocket router for real-time status updates and plugin communication.

Endpoints:
  /status/{client_id}           — general status / operation subscriptions
  /operations/{operation_id}    — specific operation status updates
  /module_feed                  — live feed from FeedStreamer (Logic → UI)
  /plugin/{plugin_id}/{channel} — bidirectional plugin event channel (PluginBridge)
"""
from __future__ import annotations

import asyncio
import json
import logging
from datetime import datetime

from fastapi import APIRouter, WebSocket, WebSocketDisconnect

from ..core.dependencies import module_operations
from ..services.feed_streamer import FeedStreamer, FeedMessage
from ..services.plugin_bridge import PluginBridge
from .service import (
    connection_manager,
    notify_operation_update,
    operation_monitor,
)
from ...container_injection import container

logger = logging.getLogger(__name__)

router = APIRouter()


# ---------------------------------------------------------------------------
# /status/{client_id}
# ---------------------------------------------------------------------------

@router.websocket("/status/{client_id}")
async def websocket_status_endpoint(websocket: WebSocket, client_id: str):
    """WebSocket endpoint for real-time status updates."""
    await connection_manager.connect(websocket, client_id)

    try:
        while True:
            data = await websocket.receive_text()
            message_data = json.loads(data)
            message_type = message_data.get("type")

            if message_type == "subscribe_operation":
                operation_id = message_data.get("operation_id")
                if operation_id:
                    connection_manager.subscribe_to_operation(websocket, operation_id)
                    if operation_id in module_operations:
                        current_status = module_operations[operation_id]
                        await connection_manager.send_personal_message(
                            json.dumps({
                                "type": "operation_update",
                                "operation_id": operation_id,
                                "data": current_status,
                            }),
                            websocket,
                        )

            elif message_type == "get_all_operations":
                await connection_manager.send_personal_message(
                    json.dumps({
                        "type": "all_operations",
                        "operations": dict(module_operations),
                    }),
                    websocket,
                )

            elif message_type == "ping":
                await connection_manager.send_personal_message(
                    json.dumps({"type": "pong"}),
                    websocket,
                )

    except WebSocketDisconnect:
        connection_manager.disconnect(websocket, client_id)
    except Exception as exc:
        logger.error("WebSocket error for client %s: %s", client_id, exc)
        connection_manager.disconnect(websocket, client_id)


# ---------------------------------------------------------------------------
# /operations/{operation_id}
# ---------------------------------------------------------------------------

@router.websocket("/operations/{operation_id}")
async def websocket_operation_endpoint(websocket: WebSocket, operation_id: str):
    """WebSocket endpoint for specific operation status."""
    await websocket.accept()

    try:
        if operation_id in module_operations:
            current_status = module_operations[operation_id]
            await websocket.send_text(json.dumps({
                "type": "operation_status",
                "operation_id": operation_id,
                "data": current_status,
            }))

        connection_manager.subscribe_to_operation(websocket, operation_id)

        while True:
            data = await websocket.receive_text()
            message_data = json.loads(data)
            if message_data.get("type") == "ping":
                await websocket.send_text(json.dumps({"type": "pong"}))

    except WebSocketDisconnect:
        if operation_id in connection_manager.operation_subscriptions:
            connection_manager.operation_subscriptions[operation_id].discard(websocket)
    except Exception as exc:
        logger.error("WebSocket error for operation %s: %s", operation_id, exc)


# ---------------------------------------------------------------------------
# /module_feed — FeedStreamer live stream
# ---------------------------------------------------------------------------

@router.websocket("/module_feed")
async def websocket_module_feed_endpoint(websocket: WebSocket):
    """
    WebSocket endpoint for real-time module feed updates.

    Uses the in-process FeedStreamer singleton (no Redis).
    - Replays history ring-buffer to the new client immediately.
    - Then streams live FeedMessage objects as they arrive.
    - Simultaneously handles client-side ping/pong messages.
    """
    await websocket.accept()
    fm = FeedStreamer.get_instance()
    queue = fm.subscribe()
    logger.info("Client connected to module_feed WebSocket")

    async def _send_feeds() -> None:
        """Relay FeedStreamer queue → WebSocket (sender side)."""
        history = fm.get_history()
        if history:
            await websocket.send_text(json.dumps({
                "type": "history_batch",
                "items": history,
                "timestamp": datetime.now().isoformat(),
            }))
            logger.debug("📤 Sent history_batch with %d items to new client", len(history))

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
                    logger.debug("📤 Sent state_snapshot for %d modules", len(last_states))
        except Exception as exc:
            logger.warning("Could not send state_snapshot: %s", exc)

        while True:
            payload: dict = await queue.get()
            await websocket.send_text(json.dumps({"type": "module_feed", "data": payload}))

    async def _recv_client() -> None:
        """Handle client → server messages (ping/pong)."""
        while True:
            try:
                raw = await websocket.receive_text()
                msg = json.loads(raw)
                if msg.get("type") == "ping":
                    await websocket.send_text(json.dumps({"type": "pong"}))
            except WebSocketDisconnect:
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
    except Exception as exc:
        logger.error("WebSocket error in module_feed: %s", exc)
    finally:
        fm.unsubscribe("", queue)


# ---------------------------------------------------------------------------
# /plugin/{plugin_id}/{channel} — bidirectional plugin event channel
# ---------------------------------------------------------------------------

@router.websocket("/plugin/{plugin_id}/{channel}")
async def websocket_plugin_endpoint(
    websocket: WebSocket,
    plugin_id: str,
    channel: str,
):
    """
    Bidirectional WebSocket channel for plugin UI ↔ backend communication.

    Logic → UI: PluginBridge publishes to *channel*; forwarded to frontend.
    UI → Logic: Frames with ``"type": "client_to_server"`` delivered to handlers.
    """
    await websocket.accept()
    bridge = PluginBridge.get_instance()
    queue = bridge.subscribe(channel)

    for msg in bridge.get_history(channel):
        try:
            await websocket.send_json({"type": "plugin_event", "channel": channel, "data": msg})
        except Exception:
            break

    async def _sender() -> None:
        while True:
            payload = await queue.get()
            try:
                await websocket.send_json({
                    "type": "plugin_event",
                    "plugin_id": plugin_id,
                    "channel": channel,
                    "data": payload,
                })
            except Exception:
                break

    sender_task = asyncio.ensure_future(_sender())

    try:
        while True:
            raw = await websocket.receive_text()
            frame = json.loads(raw)
            ftype = frame.get("type")
            if ftype == "client_to_server":
                await bridge.receive(channel, frame.get("data", {}))
            elif ftype == "ping":
                await websocket.send_json({"type": "pong"})
    except WebSocketDisconnect:
        pass
    except Exception as exc:
        logger.error("PluginBridge WS error [%s/%s]: %s", plugin_id, channel, exc)
    finally:
        sender_task.cancel()
        bridge.unsubscribe(channel, queue)
        logger.info("PluginBridge WS closed [%s/%s]", plugin_id, channel)
        logger.info("Client disconnected from module_feed WebSocket")