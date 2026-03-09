"""
FeedManager — In-Process WebSocket Feed Bus

Decouples the application core (vyra_base) from the FastAPI WebSocket
layer via a lightweight asyncio-based pub/sub bus.

Architecture
-----------
Application core      WebSocket handler
  (sync or async)         (async)
       │                     │
       │ publish()           │ subscribe() → Queue
       ▼                     ▼
  ┌──────────────────────────────────┐
  │  FeedManager (singleton)         │
  │  • history deque (ring buffer)   │
  │  • list[asyncio.Queue]           │
  └──────────────────────────────────┘

Usage (application layer)
-------------------------
    from ..backend_webserver.services.feed_manager import FeedManager, FeedMessage

    FeedManager.get_instance().publish(FeedMessage(
        module_name="v2_modulemanager",
        module_id="...",
        feed_type="news",
        message="heartbeat",
        timestamp=datetime.now().isoformat(),
        data={}
    ))

Usage (WebSocket handler)
-------------------------
    fm = FeedManager.get_instance()
    queue = fm.subscribe()
    try:
        for msg in fm.get_history():   # replay history to new client
            await ws.send_json({"type": "feed", "data": msg})
        while True:
            data = await queue.get()
            await ws.send_json({"type": "feed", "data": data})
    finally:
        fm.unsubscribe(queue)
"""

from __future__ import annotations

import asyncio
import logging
from collections import deque
from dataclasses import asdict, dataclass, field
from typing import List, Optional

logger = logging.getLogger(__name__)


# ---------------------------------------------------------------------------
# Data model
# ---------------------------------------------------------------------------

@dataclass
class FeedMessage:
    """Canonical feed message passed through the in-process bus.

    All fields are plain JSON-serialisable types so that WebSocket handlers
    can forward them without any further transformation.
    """

    module_name: str
    module_id: str
    feed_type: str          # "news" | "state" | "error"
    message: str
    timestamp: str          # ISO-8601
    data: dict = field(default_factory=dict)

    def to_dict(self) -> dict:
        """Return as plain dict (JSON-ready)."""
        return asdict(self)


# ---------------------------------------------------------------------------
# FeedManager
# ---------------------------------------------------------------------------

class FeedManager:
    """
    Singleton in-process pub/sub bus for module feed messages.

    Thread-safety note
    ------------------
    ``publish()`` is *synchronous* and safe to call from application-layer
    code running in the same asyncio event loop as the webserver.  It uses
    ``Queue.put_nowait()`` so it never blocks the caller.

    If the caller is on a *different thread* (e.g., a VYRA executor thread),
    use ``publish_threadsafe(msg, loop)`` instead, which schedules
    ``put_nowait`` on the given event loop.

    Parameters
    ----------
    history_size : int
        Maximum number of messages kept in the ring-buffer sent to new
        WebSocket clients on connect.  Defaults to 100.
    queue_size : int
        Maximum depth of each subscriber queue.  Messages are *dropped* for
        slow consumers rather than blocking the publisher.  Defaults to 500.
    """

    _instance: Optional["FeedManager"] = None

    def __init__(self, history_size: int = 100, queue_size: int = 500) -> None:
        self._history: deque[dict] = deque(maxlen=history_size)
        self._subscribers: List[asyncio.Queue] = []
        self._queue_size = queue_size

    # ------------------------------------------------------------------
    # Singleton
    # ------------------------------------------------------------------

    @classmethod
    def get_instance(cls, *, history_size: int = 100, queue_size: int = 500) -> "FeedManager":
        """Return the process-wide FeedManager singleton."""
        if cls._instance is None:
            cls._instance = cls(history_size=history_size, queue_size=queue_size)
            logger.info("✅ FeedManager singleton created (history=%d, queue=%d)", history_size, queue_size)
        return cls._instance

    @classmethod
    def reset(cls) -> None:
        """Reset singleton — intended for tests only."""
        cls._instance = None

    # ------------------------------------------------------------------
    # Publisher API
    # ------------------------------------------------------------------

    def publish(self, msg: FeedMessage) -> None:
        """
        Non-blocking publish from any sync or async context.

        Appends *msg* to the history ring-buffer and forwards it to every
        active subscriber queue.  Slow subscribers (full queue) are silently
        skipped; their WebSocket will still receive the next message.
        """
        payload = msg.to_dict()
        self._history.append(payload)

        dropped = 0
        for q in self._subscribers:
            try:
                q.put_nowait(payload)
            except asyncio.QueueFull:
                dropped += 1

        if dropped:
            logger.debug("FeedManager: dropped %d message(s) for slow subscribers", dropped)

    def publish_threadsafe(self, msg: FeedMessage, loop: asyncio.AbstractEventLoop) -> None:
        """
        Thread-safe variant for callers on a foreign thread (e.g. ROS2 executor).

        Uses ``call_soon_threadsafe`` to schedule ``publish()`` on *loop*.
        """
        loop.call_soon_threadsafe(self.publish, msg)

    # ------------------------------------------------------------------
    # Subscriber API
    # ------------------------------------------------------------------

    def subscribe(self) -> asyncio.Queue:
        """
        Register a new subscriber.

        Returns a fresh ``asyncio.Queue`` that will receive every future feed
        message published after this call.  The caller is responsible for
        calling :meth:`unsubscribe` when the consumer (e.g. WebSocket) closes.
        """
        q: asyncio.Queue = asyncio.Queue(maxsize=self._queue_size)
        self._subscribers.append(q)
        logger.debug("FeedManager: subscriber added (total=%d)", len(self._subscribers))
        return q

    def unsubscribe(self, q: asyncio.Queue) -> None:
        """Remove a subscriber queue.  No-op if the queue is not registered."""
        try:
            self._subscribers.remove(q)
            logger.debug("FeedManager: subscriber removed (total=%d)", len(self._subscribers))
        except ValueError:
            pass

    # ------------------------------------------------------------------
    # History API
    # ------------------------------------------------------------------

    def get_history(self) -> list[dict]:
        """Return a snapshot of the history ring-buffer (oldest first)."""
        return list(self._history)

    def clear_history(self) -> None:
        """Flush the history ring-buffer — intended for tests."""
        self._history.clear()

    # ------------------------------------------------------------------
    # Diagnostics
    # ------------------------------------------------------------------

    @property
    def subscriber_count(self) -> int:
        """Number of currently registered subscribers."""
        return len(self._subscribers)

    @property
    def history_count(self) -> int:
        """Number of messages currently held in the history buffer."""
        return len(self._history)
