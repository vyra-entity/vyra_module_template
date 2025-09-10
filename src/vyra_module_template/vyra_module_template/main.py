import asyncio
from typing import Any, Callable, Coroutine
import rclpy
import signal
import sys

from . import _Base_
from .application import application
from .taskmanager import TaskManager

from vyra_base.helper.logger import Logger
from vyra_base.core.entity import VyraEntity
from vyra_base.helper.error_handler import ErrorTraceback 

def handle_sigterm(signum, frame):
    Logger.warn("SIGTERM empfangen, ROS2 wird heruntergefahren...")
    rclpy.shutdown()
    sys.exit(0)

signal.signal(signal.SIGTERM, handle_sigterm)
signal.signal(signal.SIGINT, handle_sigterm)

async def application_runner(entity, taskmanager):
    Logger.log('Starting application runner...')
    try:
        await application.main(entity, taskmanager)
    finally:
        Logger.log('Application runner finished.')
        ErrorTraceback.check_error_exist()

async def main_communication_spinner(entity):
    Logger.log('Starting node spinner...')
    try:
        while rclpy.ok():
            rclpy.spin_once(entity.node, timeout_sec=0.01)
            await asyncio.sleep(0.1)
    except SystemExit as se:
        Logger.log(f'SystemExit in spinner: {se}. Exiting gracefully...')
    finally:
        Logger.log('Node spinner finished.')
        ErrorTraceback.check_error_exist()

async def configure_settings(tm: TaskManager) -> VyraEntity:
    """Konfiguriert die Einstellungen für die Anwendung."""
    Logger.log('Configuring settings...')
    # Hier können spezifische Einstellungen für die Anwendung gesetzt werden
    # Zum Beispiel:
    # entity.set_parameter('parameter_name', 'value')
    entity: VyraEntity = await _Base_.build_base()

    tm.add_task(application_runner, entity, tm)
    tm.add_task(main_communication_spinner, entity)
    if entity.node is None:
        Logger.log('No ROS 2 node created, exiting...')
        raise RuntimeError("No ROS 2 node created, exiting...")
    return entity

@ErrorTraceback.w_check_error_exist
async def runner():   
    try:
        tm = TaskManager()
        
        rclpy.init()

        entity = await configure_settings(tm)

        while tm.tasks:
            try:
                done, pending = await asyncio.wait(
                    [task_tuple[1] for task_tuple in tm.tasks.values()],
                    return_when=asyncio.FIRST_COMPLETED
                )
                Logger.debug("Tasks completed")
                for task in done:
                    if task.exception():
                        Logger.error(f"Task {task.get_name()} raised an exception: {task.exception()}")
                        await asyncio.sleep(0.5)
                    else:
                        Logger.info(f"Task {task.get_name()} completed successfully.")
                    tm.tasks.pop(task.get_name())

                for task in pending:
                    Logger.info(f"Task {task.get_name()} is still running.")

                await asyncio.sleep(0.01)
            except asyncio.TimeoutError:
                if entity.node and entity.node.reload_event.is_set():
                    entity.node.reload_event.clear()  # Event zurücksetzen
                    Logger.info("Node reload event received")
                    tm.cancel_all()
                    entity = await configure_settings(tm)
                elif entity.node == None:
                    raise RuntimeError("Node is None, cannot proceed with tasks.")
            

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