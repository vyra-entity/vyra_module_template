import asyncio
import json
import logging
import logging.config
import os
from pathlib import Path
import rclpy
import signal
import sys

from . import _base_
from .application import application
from .taskmanager import TaskManager

from vyra_base.core.entity import VyraEntity
from vyra_base.helper.error_handler import ErrorTraceback 

# Load logging configuration from config file
def setup_module_logging():
    """Setup logging from configuration file with ENV variable support."""
    config_path = Path('/workspace/config/ros2_logging.json')
    logging_format = os.getenv('LOGGING_FORMAT', '%(asctime)s - %(levelname)-8s - %(name)s - %(message)s')
    log_level = os.getenv("LOG_LEVEL", "INFO").upper()

    if config_path.exists():
        with open(config_path, 'r') as f:
            config = json.load(f)
        
        # Update all formatters to use ENV-based format
        for formatter_name, formatter_config in config.get('formatters', {}).items():
            formatter_config['format'] = logging_format
        
        # Apply configuration
        logging.config.dictConfig(config)
        logging.getLogger().setLevel(log_level)
    else:
        # Fallback to basic configuration if config file not found
        logging.basicConfig(
            level=getattr(logging, log_level, logging.INFO),
            format=logging_format,
            handlers=[logging.StreamHandler(sys.stdout)]
        )

# Initialize logging
setup_module_logging()

# Configure main logger
logger = logging.getLogger(__name__)

def handle_sigterm(signum, frame):
    logger.warning("SIGTERM empfangen, ROS2 wird heruntergefahren...")
    rclpy.shutdown()
    sys.exit(0)

signal.signal(signal.SIGTERM, handle_sigterm)
signal.signal(signal.SIGINT, handle_sigterm)

async def application_runner(
        entity: VyraEntity, 
        taskmanager: TaskManager) -> None:
    """The application runner starts the main application logic.
    It is managed as an asyncio task by the TaskManager.
    :param entity: The VyraEntity containing the ROS 2 node.
    :type entity: VyraEntity
    :param taskmanager: The TaskManager instance to manage application tasks.
    :type taskmanager: TaskManager
    """
    logger.info('Starting application runner...')
    try:
        await application.main(entity, taskmanager)
    finally:
        logger.info('Application runner finished.')
        ErrorTraceback.check_error_exist()

async def main_communication_spinner(entity: VyraEntity) -> None:
    """The main communication spinner handle the rclpy.spin_once loop
    from ros2
    :param entity: The VyraEntity containing the ROS 2 node.
    :type entity: VyraEntity
    """
    logger.info('Starting node spinner...')
    try:
        while rclpy.ok():
            rclpy.spin_once(entity.node, timeout_sec=0.01)
            await asyncio.sleep(0.1)
    except SystemExit as se:
        logger.info(f'SystemExit in spinner: {se}. Exiting gracefully...')
    except Exception as e:
        logger.exception(f'Exception in spinner: {e}')
    finally:
        logger.info('Node spinner finished.')
        ErrorTraceback.check_error_exist()

async def configure_settings(tm: TaskManager) -> VyraEntity:
    """Initializing vyra entity and configure base settings. Afterwards start 
    the application runner and the communication spinner.
    :param tm: The TaskManager instance to manage application tasks.
    :type tm: TaskManager
    :return: The configured VyraEntity instance.
    :rtype: VyraEntity
    """
    logger.info('Configuring settings...')
    # Hier können spezifische Einstellungen für die Anwendung gesetzt werden
    # Zum Beispiel:
    # entity.set_parameter('parameter_name', 'value')
    entity: VyraEntity = await _base_.build_base()

    tm.add_task(application_runner, entity, tm)
    tm.add_task(main_communication_spinner, entity)
    if entity.node is None:
        logger.info('No ROS 2 node created, exiting...')
        raise RuntimeError("No ROS 2 node created, exiting...")
    return entity

@ErrorTraceback.w_check_error_exist
async def runner() -> None:   
    try:
        tm = TaskManager()
        
        rclpy.init()

        entity: VyraEntity = await configure_settings(tm)

        while tm.tasks:
            try:
                done, pending = await asyncio.wait(
                    [task_tuple[1] for task_tuple in tm.tasks.values()],
                    return_when=asyncio.FIRST_COMPLETED
                )
                logger.debug("Tasks completed")
                for task in done:
                    if task.exception():
                        logger.error(
                            f"Task {task.get_name()} raised an exception: {task.exception()}")
                        
                        await asyncio.sleep(0.5)
                    else:
                        logger.info(f"Task {task.get_name()} completed successfully.")
                    tm.tasks.pop(task.get_name())

                for task in pending:
                    logger.info(f"Task {task.get_name()} is still running.")

                await asyncio.sleep(0.01)
            except asyncio.TimeoutError:
                if entity.node and entity.node.reload_event.is_set():
                    entity.node.reload_event.clear()  # Event zurücksetzen
                    logger.info("Node reload event received")
                    tm.cancel_all()
                    entity = await configure_settings(tm)
                elif entity.node == None:
                    raise RuntimeError("Node is None, cannot proceed with tasks.")

    except SystemExit as e:
        logger.info(f'SystemExit: {e}. Exiting gracefully...')
        tm.cancel_all()
    except KeyboardInterrupt:
        logger.warning('KeyboardInterrupt received, closing event loop')
    except Exception as e:
        logger.exception(f'Exception: {e}. Closing event loop')
    finally:
        if hasattr(locals, 'entity'):
            logger.info('Shutting down ROS 2 node...')
            if hasattr(entity, 'node') and entity.node is not None:
                # Ensure the node is destroyed properly
                logger.info('Destroying ROS 2 node...')
                entity.node.destroy_node()
            else:
                logger.info('No ROS 2 node to destroy.')

        if rclpy.ok():
            logger.info('ROS 2 node destroyed.')
            rclpy.shutdown()
        else:
            logger.info('ROS 2 node was not running, nothing to destroy.')
            
        tm.cancel_all()

def main() -> None:
    try:
        asyncio.run(runner())
        logger.info('Exit module runner')
    except KeyboardInterrupt:
        logger.warning('KeyboardInterrupt received, closing event loop')
    except RuntimeError as e:
        logger.info(f'RuntimeError: {e}. Closing event loop')
    finally:
        logger.info('Finally exit entry point')

if __name__ == '__main__':
    main()