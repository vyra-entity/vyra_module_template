"""Use-Case 08: CustomFeeder-Monitor mit Custom-Tag Dispatch."""

from vyra_base.com.feeder import feed_tracker


class Component:
    def __init__(self, entity):
        self.entity = entity

    async def setup(self) -> None:
        self.entity.news_feeder.register_news_condition(
            lambda ctx: ctx.get("kwargs", {}).get("mode") == "custom",
            name="route_to_custom_feeder",
            execution_point="BEFORE",
            success_message="Custom route aktiv",
            tag="custom",  # erwartet entity.custom_feeder
        )

    @feed_tracker.monitor(
        tag="news",
        label="Custom Dispatch",
        severity="INFO",
    )
    async def monitored(self, *, mode: str = "default"):
        return mode
