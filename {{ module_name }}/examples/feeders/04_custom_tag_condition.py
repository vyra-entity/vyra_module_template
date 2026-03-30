"""Use-Case 04: Condition mit Custom-Tag."""


def condition_custom(context: dict) -> bool:
    return bool(context.get("ready", False))


async def register(entity) -> None:
    entity.news_feeder.register_news_condition(
        condition_custom,
        name="custom_condition",
        execution_point="BEFORE",
        success_message="Custom condition met",
        failure_message=None,
        tag="custom",  # Erwartet optional entity.custom_feeder
    )

    outputs = entity.news_feeder.evaluate_conditions(
        {"ready": True, "entity": entity, "execution_point": "BEFORE"},
        rule_names=["custom_condition"],
        tags=["custom"],
        execution_point="BEFORE",
    )

    for tag, message in outputs:
        feeder = getattr(entity, f"{tag}_feeder", None)
        if feeder is not None:
            await feeder.feed(message)
