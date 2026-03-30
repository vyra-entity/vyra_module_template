"""Use-Case 01: Error-Monitoring auf einer Klassenmethode."""

from vyra_base.com.feeder import feed_tracker


class Component:
    def __init__(self, entity):
        self.entity = entity

    @feed_tracker.monitor(tag="error", label="Greifer-Check", severity="WARNING")
    async def check_gripper(self) -> None:
        raise RuntimeError("Greifer blockiert")

