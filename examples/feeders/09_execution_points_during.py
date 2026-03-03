"""Use-Case 09: BEFORE/DURING/AFTER/ALWAYS Regeln in einem Ablauf."""

import asyncio


def before_rule(ctx: dict) -> bool:
    return ctx.get("execution_point") == "BEFORE"


def during_rule(ctx: dict) -> bool:
    return ctx.get("execution_point") == "DURING"


def after_rule(ctx: dict) -> bool:
    return ctx.get("execution_point") == "AFTER"


def always_rule(ctx: dict) -> bool:
    return True


async def register(entity) -> None:
    entity.news_feeder.register_news_condition(
        before_rule,
        name="rule_before",
        execution_point="BEFORE",
        success_message="before hit",
    )
    entity.news_feeder.register_news_condition(
        during_rule,
        name="rule_during",
        execution_point="DURING",
        success_message="during hit",
    )
    entity.news_feeder.register_news_condition(
        after_rule,
        name="rule_after",
        execution_point="AFTER",
        success_message="after hit",
    )
    entity.news_feeder.register_news_condition(
        always_rule,
        name="rule_always",
        execution_point="ALWAYS",
        success_message="always hit",
    )


class Component:
    def __init__(self, entity):
        self.entity = entity

    @property
    def monitored(self):
        @self.entity.news_feeder.monitor(
            tag="news",
            label="Execution points",
            severity="INFO",
            during_interval_seconds=0.05,
        )
        async def _inner():
            await asyncio.sleep(0.12)
            return "done"

        return _inner
