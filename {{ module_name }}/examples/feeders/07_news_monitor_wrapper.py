"""Use-Case 07: NewsFeeder-Monitor als Wrapper auf Methode."""

from vyra_base.com.feeder import feed_tracker


class Component:
    def __init__(self, entity):
        self.entity = entity

    async def setup(self) -> None:
        self.entity.news_feeder.register_news_condition(
            lambda ctx: bool(ctx.get("result", 0) > 10),
            name="news_after_threshold",
            execution_point="AFTER",
            success_message="Messwert über Schwellwert",
            tag="news",
        )

    @feed_tracker.monitor(
        tag="news",
        label="News Monitor Wrapper",
        severity="INFO",
        during_interval_seconds=0.1,
    )
    async def monitored_method(self, value: int) -> int:
        return value
