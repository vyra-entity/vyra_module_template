"""Use-Case 05: ErrorFeeder-Condition zusätzlich zum Exception-Push."""

from vyra_base.com.feeder import feed_tracker


def error_has_message(context: dict) -> bool:
    exception = context.get("exception", {})
    return bool(exception.get("message"))


async def register(entity) -> None:
    entity.error_feeder.register_condition(
        error_has_message,
        name="error_condition_news",
        execution_point="AFTER",
        tag="news",
        success_message="Error condition triggered",
        failure_message=None,
    )


class Component:
    def __init__(self, entity):
        self.entity = entity

    @feed_tracker.monitor(tag="error", label="Template Test", severity="WARNING")
    async def run(self):
        raise ValueError("Fehler im Ablauf")
