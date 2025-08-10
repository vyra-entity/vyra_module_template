import asyncio
from typing import Any, Callable, Coroutine
import rclpy
import signal
import sys

from . import _Base_
from .application import application
from vyra_base.helper.logger import Logger
from vyra_base.core.entity import VyraEntity
from vyra_base.helper.error_handler import ErrorTraceback 

def handle_sigterm(signum, frame):
    Logger.warn("SIGTERM empfangen, ROS2 wird heruntergefahren...")
    rclpy.shutdown()
    sys.exit(0)

signal.signal(signal.SIGTERM, handle_sigterm)
signal.signal(signal.SIGINT, handle_sigterm)


class TaskManager:
    def __init__(self) -> None:
        self.tasks: dict[str, tuple[Callable, asyncio.Task, list[Any], dict[str, Any]]] = {}

    def add_task(self, coro: Callable, *args, **kwargs):
        self.create_task(coro, *args, **kwargs)
        Logger.info(f"Task {coro.__name__} has been added.")

    def restart_task(self, coro: Callable):
        if coro.__name__ in self.tasks:
            if not self.tasks[coro.__name__][0].done():
                self.cancel_task(coro)
                Logger.info(f"Task {coro.__name__} has been cancelled.")
            
            self.create_task(coro, *self.tasks[coro.__name__][2], **self.tasks[coro.__name__][3])
            Logger.info(f"Task {coro.__name__} has been restarted.")
                
        else:
            Logger.error(f"Task {coro.__name__} does not exist.")

    def create_task(self, coro: Callable, *args, **kwargs) -> None:
        self.tasks[coro.__name__] = (
            coro, 
            asyncio.create_task(coro(*args, **kwargs)), 
            list(args), 
            dict(kwargs)
        )

    def cancel_task(self, coro: Callable) -> None:
        if coro.__name__ in self.tasks:
            _, task, _, _ = self.tasks[coro.__name__]
            task.cancel()
            Logger.info(f"Task {coro.__name__} has been cancelled.")
        else:
            Logger.error(f"Task {coro.__name__} does not exist thus cannot be cancelled.")

    def cancel_all(self) -> None:
        for _, task, _, _ in self.tasks.values():
            task.cancel()
        self.tasks.clear()

async def application_runner(entity):
    Logger.log('Starting application runner...')
    await application.main(entity)

async def main_communication_spinner(entity):
    while rclpy.ok():
        rclpy.spin_once(entity.node, timeout_sec=0.01)

@ErrorTraceback.w_check_error_exist
async def runner():   
    try:
        tm = TaskManager()
        
        rclpy.init()

        entity: VyraEntity = await _Base_.build_base()

        Logger.log('Starting application runner...')
        tm.add_task(application_runner, entity)
        await asyncio.sleep(0.1)  # Ensure the node is initialized before starting tasks
        
        Logger.log('Starting node spinner...')
        tm.add_task(main_communication_spinner, entity)
        
        if entity.node is None:
            Logger.log('No ROS 2 node created, exiting...')
            return

        while tm.tasks:
            done, pending = await asyncio.wait(
                [task_tuple[1] for task_tuple in tm.tasks.values()],
                return_when=asyncio.FIRST_COMPLETED
            )
            for task in done:
                if task.exception():
                    Logger.error(f"Task {task.get_name()} raised an exception: {task.exception()}")
                else:
                    Logger.info(f"Task {task.get_name()} completed successfully.")
            for task in pending:
                Logger.info(f"Task {task.get_name()} is still running.")
                task.add_done_callback(lambda t: tm.tasks.pop(t.get_name(), None))

    except SystemExit as e:
        Logger.log(f'SystemExit: {e}. Exiting gracefully...')
        tm.cancel_all()
    except KeyboardInterrupt:
        Logger.warn('KeyboardInterrupt received, closing event loop')
    finally:
        if hasattr(locals, 'entity'):
            Logger.log('Shutting down ROS 2 node...')
            if hasattr(entity, 'node') and entity.node is not None:
                # Ensure the node is destroyed properly
                Logger.log('Destroying ROS 2 node...')
                entity.node.destroy_node()
            else:
                Logger.log('No ROS 2 node to destroy.')

        if rclpy.ok():
            Logger.log('ROS 2 node destroyed.')
            rclpy.shutdown()
        else:
            Logger.log('ROS 2 node was not running, nothing to destroy.')
            
        tm.cancel_all()

def main():
    try:
        asyncio.run(runner())
        Logger.log('Exit module runner')
    except KeyboardInterrupt:
        Logger.warn('KeyboardInterrupt received, closing event loop')
    except RuntimeError as e:
        Logger.log(f'RuntimeError: {e}. Closing event loop')
    finally:
        Logger.log('Finally exit entry point')

if __name__ == '__main__':
    main()