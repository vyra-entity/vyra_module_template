import asyncio
from typing import Callable, Any

from vyra_base.helper.logger import Logger


class TaskManager:
    """Helper class to manage asyncio tasks within the application.
    It allows adding, removing, restarting, and cancelling tasks by their coroutine function.
    Each task is identified by the name of its coroutine function.
    
    API:
        - add_task(coro: Callable, *args, **kwargs) -> str
        - remove_task(coro: Callable) -> None
        - restart_task(coro: Callable) -> None
        - cancel_task(coro: Callable) -> None
        - cancel_all() -> None
    Example:
        task_manager.add_task(some_coroutine, arg1, arg2)
        task_manager.restart_task(some_coroutine)
        task_manager.cancel_task(some_coroutine)
        task_manager.remove_task(some_coroutine)
        task_manager.cancel_all()
    """
    def __init__(self) -> None:
        """Initialize the TaskManager with an empty task dictionary."""
        self.tasks: dict[str, tuple[Callable, asyncio.Task, list[Any], dict[str, Any]]] = {}

    def add_task(self, coro: Callable, *args, **kwargs) -> str:
        """Add a task to the manager and start it immediately.
        If the task already exists, it will not be added again.
        Use restart_task to restart an existing task.
        :param coro: The coroutine function to be added as a task.
        :type coro: Callable
        :param args: Positional arguments to be passed to the coroutine.
        :type args: list[Any]
        :param kwargs: Keyword arguments to be passed to the coroutine.
        :type kwargs: dict[str, Any]
        :return: The name of the added task.
        :rtype: str
        """
        if coro.__name__ in self.tasks:
            Logger.error(f"Task <{coro.__name__}> already exists. Use restart_task to restart it.")
            return coro.__name__
        
        self._create_task(coro, *args, **kwargs)
        Logger.info(f"Task <{coro.__name__}> has been added.")
        return coro.__name__

    def remove_task(self, coro: Callable):
        """Remove a task from the manager. The task will be cancelled if it is running.
        :param coro: The coroutine function to be removed.
        :type coro: Callable
        """
        if coro.__name__ in self.tasks:
            self.cancel_task(coro)
            del self.tasks[coro.__name__]
            Logger.info(f"Task <{coro.__name__}> has been removed.")
        else:
            Logger.error(f"Task <{coro.__name__}> does not exist thus cannot be removed.")

    def restart_task(self, coro: Callable):
        """Restart an existing task. If the task is running, it will be cancelled first.
        :param coro: The coroutine function to be restarted.
        :type coro: Callable
        """
        if coro.__name__ in self.tasks:
            if not self.tasks[coro.__name__][0].done():
                self.cancel_task(coro)
                Logger.info(f"Task <{coro.__name__}> has been cancelled.")

            self._create_task(coro, *self.tasks[coro.__name__][2], **self.tasks[coro.__name__][3])
            Logger.info(f"Task <{coro.__name__}> has been restarted.")
                
        else:
            Logger.error(f"Task <{coro.__name__}> does not exist.")

    def cancel_task(self, coro: Callable) -> None:
        """Cancel a running task. The task will not be removed from the manager
        and could thus be restarted later.
        :param coro: The coroutine function to be cancelled.
        :type coro: Callable
        """
        if coro.__name__ in self.tasks:
            _, task, _, _ = self.tasks[coro.__name__]
            task.cancel()
            Logger.info(f"Task <{coro.__name__}> has been cancelled.")
        else:
            Logger.error(f"Task <{coro.__name__}> does not exist thus cannot be cancelled.")

    def cancel_all(self) -> None:
        """Cancel all running tasks and clear the task manager."""
        Logger.info("Cancelling all tasks...")
        for coro, task, _, _ in self.tasks.values():
            self.cancel_task(coro)
        self.tasks.clear()

    def _create_task(self, coro: Callable, *args, **kwargs) -> None:
        """Helper method to create and store a new asyncio task.
        :param coro: The coroutine function to be added as a task.
        :type coro: Callable
        :param args: Positional arguments to be passed to the coroutine.
        :type args: list[Any]
        :param kwargs: Keyword arguments to be passed to the coroutine.
        :type kwargs: dict[str, Any]
        """
        # Cancel old task if it exists and is still running
        if coro.__name__ in self.tasks:
            _, old_task, _, _ = self.tasks[coro.__name__]
            if not old_task.done():
                Logger.info(f"Cancelling old task <{coro.__name__}> before creating new one")
                old_task.cancel()
        
        self.tasks[coro.__name__] = (
            coro, 
            asyncio.create_task(coro(*args, **kwargs), name=coro.__name__), 
            list(args), 
            dict(kwargs)
        )