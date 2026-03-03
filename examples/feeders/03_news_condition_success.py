"""Use-Case 03: News-Condition mit Success-Message."""


def condition_a_gt_0_and_b_eq_1(context: dict) -> bool:
    return context.get("a", 0) > 0 and context.get("b", 0) == 1


async def register(entity) -> None:
    entity.news_feeder.register_news_condition(
        condition_a_gt_0_and_b_eq_1,
        name="runtime_condition_news",
        execution_point="AFTER",
        success_message="Runtime condition met (a>0 && b==1)",
        failure_message=None,
        tag="news",
    )

    await entity.news_feeder.evaluate_tracked_conditions(
        {"a": 1, "b": 1, "entity": entity, "execution_point": "AFTER"}
    )
