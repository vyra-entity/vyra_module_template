import asyncio
from typing import Callable, Any

from vyra_base.helper.logger import Logger


class TaskManager:
    def __init__(self) -> None:
        self.tasks: dict[str, tuple[Callable, asyncio.Task, list[Any], dict[str, Any]]] = {}

    def add_task(self, coro: Callable, *args, **kwargs):
        self.create_task(coro, *args, **kwargs)
        Logger.info(f"Task <{coro.__name__}> has been added.")

    def remove_task(self, coro: Callable):
        if coro.__name__ in self.tasks:
            self.cancel_task(coro)
            del self.tasks[coro.__name__]
            Logger.info(f"Task <{coro.__name__}> has been removed.")
        else:
            Logger.error(f"Task <{coro.__name__}> does not exist thus cannot be removed.")

    def restart_task(self, coro: Callable):
        if coro.__name__ in self.tasks:
            if not self.tasks[coro.__name__][0].done():
                self.cancel_task(coro)
                Logger.info(f"Task <{coro.__name__}> has been cancelled.")

            self.create_task(coro, *self.tasks[coro.__name__][2], **self.tasks[coro.__name__][3])
            Logger.info(f"Task <{coro.__name__}> has been restarted.")
                
        else:
            Logger.error(f"Task <{coro.__name__}> does not exist.")

    def create_task(self, coro: Callable, *args, **kwargs) -> None:
        self.tasks[coro.__name__] = (
            coro, 
            asyncio.create_task(coro(*args, **kwargs), name=coro.__name__), 
            list(args), 
            dict(kwargs)
        )

    def cancel_task(self, coro: Callable) -> None:
        if coro.__name__ in self.tasks:
            _, task, _, _ = self.tasks[coro.__name__]
            task.cancel()
            Logger.info(f"Task <{coro.__name__}> has been cancelled.")
        else:
            Logger.error(f"Task <{coro.__name__}> does not exist thus cannot be cancelled.")

    def cancel_all(self) -> None:
        for _, task, _, _ in self.tasks.values():
            task.cancel()
        self.tasks.clear()