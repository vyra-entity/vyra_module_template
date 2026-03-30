# Plugin-Bridge & Event-Bridge Architecture

## Overview

This module implements a three-tier event-bridge architecture:

```
Application ──► FeedStreamer ──► WebSocket (Frontend updates)
                    │
              BaseEventBridge (ABC)
                    │
             PluginBridge ──► WebSocket /ws/plugin/{id}/{channel}
                    │
               PluginGateway (Zenoh proxy → v2_modulemanager)
```

---

## Classes

### BaseEventBridge

**File**: `backend_webserver/services/base_event_bridge.py`

Abstract base class. All concrete bridges inherit from here.

| Method | Abstract | Description |
|--------|----------|-------------|
| `publish(topic, payload)` | ✅ | Publish a message |
| `subscribe(topic, maxsize)` | ✅ | Subscribe a queue for a topic |
| `unsubscribe(topic, q)` | ✅ | Remove a queue subscription |
| `get_history(topic)` | ✅ | Retrieve last messages |
| `clear_history(topic)` | ✅ | Clear history |
| `setThrottle(ms)` | ❌ | Configure rate limiting |
| `intercept(fn)` | ❌ | Register middleware hook |
| `checkHealth()` | ❌ | Check subscriber count + queue fill level |

Constant: `QUEUE_WARN_THRESHOLD = 0.80` (80% queue fill = warning).

---

### FeedStreamer

**File**: `backend_webserver/services/feed_streamer.py`

Broadcast bridge: sends all `FeedMessage` events to all subscribers.

```python
from backend_webserver.services.feed_streamer import FeedStreamer, FeedMessage

feed = FeedStreamer.get_instance()

# Sync (from non-async context):
feed.publish_feed(FeedMessage(type="status", data={"value": 42}))

# Async (ABC implementation):
await feed.publish("", {"type": "status", "data": {"value": 42}})

# Subscribe (topic is ignored — always broadcast):
queue = await feed.subscribe("")
await feed.unsubscribe("", queue)
```

**Breaking change vs FeedManager**: `unsubscribe` requires 2 arguments `(topic, queue)`.

---

### PluginBridge

**File**: `backend_webserver/services/plugin_bridge.py`

Bidirectional singleton bridge. Each Zenoh channel has its own asyncio queue list
and ring-buffer history (50 entries).

```python
from backend_webserver.services.plugin_bridge import PluginBridge

bridge = PluginBridge.get_instance()

# Send plugin event (e.g. from PluginGateway):
await bridge.publish("counter-widget/events", {"value": 5})
bridge.publish_sync("counter-widget/events", {"value": 5})

# Handle incoming message from frontend:
await bridge.receive("counter-widget/ui", {"action": "reset"})

# Register handler (e.g. for plugin logic):
bridge.register_handler("counter-widget/ui", my_async_handler)

# Subscribe (for WebSocket fan-out):
queue = await bridge.subscribe("counter-widget/events")
await bridge.unsubscribe("counter-widget/events", queue)

# Get history:
history = bridge.get_history("counter-widget/events")
```

---

### ConnectionManager

**File**: `backend_webserver/websocket/service.py`

Manages all active WebSocket connections.

```python
from backend_webserver.websocket.service import connection_manager, operation_monitor

# In lifespan:
asyncio.create_task(operation_monitor())

# Connect:
await connection_manager.connect(client_id, websocket)
await connection_manager.disconnect(client_id, websocket)
```

---

## WebSocket Endpoints

### `/ws/status/{client_id}`
General status stream (FeedStreamer). Sends all `FeedMessage` events.

### `/ws/plugin/{plugin_id}/{channel}`
Bidirectional plugin channel (PluginBridge).

- **Connect**: Sends last 50 messages from history
- **Server → Client**: `{"type": "server_to_client", "payload": {...}}`
- **Client → Server**: `{"type": "client_to_server", "payload": {...}}` → `bridge.receive(channel, payload)`

---

## Dependency Injection

```python
# container_injection.py
from container_injection import provide_plugin_bridge, get_plugin_bridge

# In FastAPI route:
@router.post("/{id}/call")
async def call(bridge = Depends(provide_plugin_bridge)):
    await bridge.publish("channel", data)
```

---

## Further Documentation

- [WEBSOCKET_API.md](../api/WEBSOCKET_API.md) — WebSocket protocol details
- [PLUGIN_INTEGRATION.md](../plugin/PLUGIN_INTEGRATION.md) — Plugin integration guide
