
import asyncio
import logging
from collections import deque
from typing import Callable, Any, Coroutine

from .status.status_manager import StatusManager
from vyra_base.state import UnifiedStateMachine
from vyra_base.state.state_types import LifecycleState

logger = logging.getLogger(__name__)


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
    TIMEOUT_CANCEL_TASK = 30  # seconds

    def __init__(self) -> None:
        """Initialize the TaskManager with an empty task dictionary."""
        self.tasks: dict[str, tuple[Callable, asyncio.Task, list[Any], dict[str, Any]]] = {}
        self.history: deque[dict] = deque(maxlen=100)
        self.metadata: dict[str, dict[str, Any]] = {}  # Task metadata including recovery counters

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
            logger.error(f"Task <{coro.__name__}> already exists. Use restart_task to restart it.")
            return coro.__name__
        
        self._create_task(coro, *args, **kwargs)
        logger.info(f"Task <{coro.__name__}> has been added.")
        return coro.__name__

    async def remove_task(self, coro: Callable, force: bool = True) -> None:
        """Remove a task from the manager. The task will be cancelled if it is running.
        :param coro: The coroutine function to be removed.
        :type coro: Callable
        :param force: Whether to force cancellation if the task is running.
        :type force: bool
        """
        if coro.__name__ in self.tasks:
            await self.cancel_task(coro, force=True)
            del self.tasks[coro.__name__]

            self.history.append({
                "task_name": coro.__name__,
                "removed_at": asyncio.get_event_loop().time()
            })

            logger.info(f"Task <{coro.__name__}> has been removed.")
        else:
            logger.error(f"Task <{coro.__name__}> does not exist thus cannot be removed.")

    async def restart_task(self, coro: Callable, force_restart: bool = False, force_time: float = 5) -> None:
        """Restart an existing task. If the task is running, it will be cancelled first.
        :param coro: The coroutine function to be restarted.
        :type coro: Callable
        :param force_restart: Whether to force a restart even if the task will not be cancelled.
        :type force_restart: bool
        :param force_time: Time in seconds to wait for the task to cancel otherwise force a restart.
        :type force_time: float (default: 5)
        """
        if coro.__name__ in self.tasks:
            if not self.tasks[coro.__name__][0].done():
                await self.cancel_task(coro, False)
                
                if force_restart:
                    await asyncio.sleep(force_time)
                    await self.cancel_task(coro, True)

                logger.info(f"Task <{coro.__name__}> has been cancelled.")

            self._create_task(coro, *self.tasks[coro.__name__][2], **self.tasks[coro.__name__][3])
            logger.info(f"Task <{coro.__name__}> has been restarted.")
                
        else:
            logger.error(f"Task <{coro.__name__}> does not exist.")

    async def cancel_task(self, coro: Callable, force: bool) -> None:
        """Cancel a running task. The task will not be removed from the manager
        and could thus be restarted later.
        :param coro: The coroutine function to be cancelled.
        :type coro: Callable
        :param force: Whether to force cancellation.
        :type force: bool
        """
        if coro.__name__ in self.tasks:
            _, task, _, _ = self.tasks[coro.__name__]
            task.cancel()
            
            start_time: float = asyncio.get_event_loop().time()
            waited_time: float = 0.0

            while not task.done() and force and waited_time < self.TIMEOUT_CANCEL_TASK:
                await asyncio.sleep(0.1)
                task.cancel()
                waited_time = asyncio.get_event_loop().time() - start_time
            
            self.add_history_entry("cancelled", coro.__name__)

            logger.info(f"Task <{coro.__name__}> has been cancelled.")
        else:
            logger.error(f"Task <{coro.__name__}> does not exist thus cannot be cancelled.")

    async def cancel_all(self) -> None:
        """Cancel all running tasks and clear the task manager."""
        logger.info("Cancelling all tasks...")

        async with asyncio.TaskGroup() as tg:
            for coro, task, _, _ in self.tasks.values():
                tg.create_task(self.cancel_task(coro, force=True))

        logger.info("All tasks have been cancelled.")
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
                logger.info(f"Cancelling old task <{coro.__name__}> before creating new one")
                old_task.cancel()
        
        task = asyncio.create_task(coro(*args, **kwargs), name=coro.__name__)
        self.tasks[coro.__name__] = (coro, task, list(args), dict(kwargs))
        
        # Initialize metadata for new task
        if coro.__name__ not in self.metadata:
            self.metadata[coro.__name__] = {
                "recovery_counter": 0,
                "last_start_time": asyncio.get_event_loop().time(),
                "successful_run": False
            }
        else:
            # Update start time for restarted task
            self.metadata[coro.__name__]["last_start_time"] = asyncio.get_event_loop().time()
        
        self.add_history_entry("created", coro.__name__)
    
    def add_history_entry(self, action: str, task_name: str) -> None:
        """Add an entry to the task history.
        :param action: The action performed on the task (e.g., "created", "cancelled").
        :type action: str
        :param task_name: The name of the task.
        :type task_name: str
        """
        if len(self.history) > 0 and action == self.history[-1]["action"] and task_name == self.history[-1]["task_name"]:
            self.history[-1]["timestamp"] = asyncio.get_event_loop().time()
            self.history[-1]["duplicate_count"] += 1
            return  # Avoid duplicate consecutive entries
        
        self.history.append({
            "task_name": task_name,
            "action": action,
            "timestamp": asyncio.get_event_loop().time(),
            "duplicate_count": 1
        })

    def get_status(self) -> dict[str, Any]:
        """Get the status of all managed tasks.
        :return: A dictionary with task names as keys and their status ('running' or 'cancelled') as values.
        :rtype: dict[str, str]
        """
        status = {}
        for coro_name, (coro, task, _, _) in self.tasks.items():
            task_status = "running" if not task.done() else "cancelled"
            metadata = self.metadata.get(coro_name, {})
            status[coro_name] = {
                "status": task_status,
                "recovery_counter": metadata.get("recovery_counter", 0),
                "last_start_time": metadata.get("last_start_time", 0),
                "successful_run": metadata.get("successful_run", False)
            }
        return status
    
async def task_supervisor_looper(
        taskmanager: TaskManager, 
        statusmanager: StatusManager, 
        check_interval: float = 5.0) -> None:
    """A coroutine that supervises tasks in the TaskManager.
    It monitors the application_runner task and implements recovery logic:
    - Checks if application_runner has been running for at least 5 seconds (health check)
    - If lifecycle is in 'recovering' state, increments recovery_counter and restarts application_runner
    - Resets recovery_counter to 0 after successful 5-second run
    - Triggers shutdown if recovery_counter reaches 3
    
    :param tm: The TaskManager instance to supervise.
    :type tm: TaskManager
    :param sm: The StatusManager instance to check lifecycle state.
    :type sm: StatusManager
    :param check_interval: Time in seconds between status checks.
    :type check_interval: float
    """
    HEALTH_CHECK_DURATION = 5.0  # seconds
    MAX_RECOVERY_ATTEMPTS = 3
    APPLICATION_RUNNER_NAME = "application_runner"
    
    state_machine: UnifiedStateMachine = statusmanager.state_machine

    async def supervisor_loop():
        logger.info("Task supervisor started")
        
        while True:
            await asyncio.sleep(check_interval)
            
            # Check if application_runner exists in tasks
            if APPLICATION_RUNNER_NAME not in taskmanager.tasks:
                logger.warning(f"Task <{APPLICATION_RUNNER_NAME}> not found in TaskManager")
                continue
            
            coro, task, args, kwargs = taskmanager.tasks[APPLICATION_RUNNER_NAME]
            metadata = taskmanager.metadata.get(APPLICATION_RUNNER_NAME, {})
            
            current_time = asyncio.get_event_loop().time()
            time_running = current_time - metadata.get("last_start_time", current_time)
            recovery_counter = metadata.get("recovery_counter", 0)
            
            # Check if task has been running successfully for 5 seconds
            if not task.done() and time_running >= HEALTH_CHECK_DURATION:
                if not metadata.get("successful_run", False):
                    logger.info(f"Task <{APPLICATION_RUNNER_NAME}> health check passed (running for {time_running:.1f}s)")
                    metadata["successful_run"] = True
                    
                    # Reset recovery counter after successful run
                    if recovery_counter > 0:
                        logger.info(
                            f"Task <{APPLICATION_RUNNER_NAME}> recovered successfully. "
                            f"Resetting recovery_counter from {recovery_counter} to 0")
                        metadata["recovery_counter"] = 0
            
            # Check if task has stopped unexpectedly
            if not task.done():
                # Task is still running, skip recovery logic
                continue
            
            # Task has stopped - log and handle recovery
            logger.info(f"Task <{APPLICATION_RUNNER_NAME}> has stopped unexpectedly.")

            # Get lifecycle state from StatusManager
            lifecycle_state = state_machine.get_lifecycle_state()
            
            if lifecycle_state == LifecycleState.RECOVERING:
                # Increment recovery counter
                metadata["recovery_counter"] = recovery_counter + 1
                new_counter = metadata["recovery_counter"]
                
                logger.warning(
                    f"Task <{APPLICATION_RUNNER_NAME}> failed during recovery. "
                    f"Recovery attempt {new_counter}/{MAX_RECOVERY_ATTEMPTS}"
                )
                
                # Check if max recovery attempts reached
                if new_counter >= MAX_RECOVERY_ATTEMPTS:
                    logger.error(
                        f"Task <{APPLICATION_RUNNER_NAME}> failed {new_counter} times. "
                        f"Max recovery attempts ({MAX_RECOVERY_ATTEMPTS}) reached. "
                        "Initiating shutdown."
                    )
                    
                    # Set lifecycle to shutting_down
                    state_machine.shutdown(reason="Max recovery attempts reached")
                    
                    # Exit supervisor loop
                    logger.info("Task supervisor shutting down")
                    break
                
                # Restart the task
                logger.info(
                    f"Restarting task <{APPLICATION_RUNNER_NAME}> (attempt "
                    f"{new_counter}/{MAX_RECOVERY_ATTEMPTS})")
                metadata["successful_run"] = False
                taskmanager._create_task(coro, *args, **kwargs)
                
            elif lifecycle_state == LifecycleState.SHUTTING_DOWN:
                logger.info(f"Lifecycle in shutting_down state. Task supervisor will exit.")
                break
                
            else:
                # Normal unexpected stop (not in recovering state)
                logger.warning(
                    f"Task <{APPLICATION_RUNNER_NAME}> stopped unexpectedly in "
                    f"lifecycle state '{lifecycle_state}'. "
                    f"Recovery counter: {recovery_counter}"
                )
                
                # Increment recovery counter
                metadata["recovery_counter"] = recovery_counter + 1
                new_counter = metadata["recovery_counter"]
                
                if new_counter >= MAX_RECOVERY_ATTEMPTS:
                    logger.error(
                        f"Task <{APPLICATION_RUNNER_NAME}> failed {new_counter} times. "
                        f"Initiating shutdown."
                    )
                    state_machine.shutdown(reason="Max recovery attempts reached")
                    break
                
                # Restart the task
                logger.info(f"Restarting task <{APPLICATION_RUNNER_NAME}> (attempt "
                            f"{new_counter}/{MAX_RECOVERY_ATTEMPTS})")
                metadata["successful_run"] = False
                taskmanager._create_task(coro, *args, **kwargs)
        
        logger.info("Task supervisor loop ended")
    
    await supervisor_loop()