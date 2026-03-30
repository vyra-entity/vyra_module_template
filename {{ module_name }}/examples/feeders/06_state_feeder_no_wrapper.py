"""Use-Case 06: StateFeeder ohne Wrapper (bewusst direktes Feed)."""

from datetime import datetime
from vyra_base.defaults.entries import StateEntry


async def publish_state(entity) -> None:
    """StateFeeder wird absichtlich nicht per monitor/decorator gewrappt."""
    entry = StateEntry(
        previous="Idle",
        trigger="manual_test",
        current="Running",
        module_id=entity.module_entry.uuid,
        module_name=entity.module_entry.name,
        timestamp=datetime.now(),
        _type="operational",
    )
    await entity.state_feeder.feed(entry)
