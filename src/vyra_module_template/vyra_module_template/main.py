import asyncio
import json
import logging
import logging.config
import os
from pathlib import Path
import rclpy  # pyright: ignore[reportMissingImports]
import signal
import sys

# Add /workspace to Python path for storage.interfaces.grpc_generated imports
if '/workspace' not in sys.path:
    sys.path.insert(0, '/workspace')

from . import _base_
from .application import application
from .application.application import Component
from .taskmanager import TaskManager, task_supervisor_looper
from .status.status_manager import StatusManager
from .user.usermanager import usermanager_runner

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
    # Exit with SIGTERM code (143 = 128+15) so Docker Swarm knows this was forced shutdown
    sys.exit(143)

signal.signal(signal.SIGTERM, handle_sigterm)
signal.signal(signal.SIGINT, handle_sigterm)

async def application_runner(
        taskmanager: TaskManager,
        statusmanager: StatusManager,
        component) -> None:
    """The application runner starts the main application logic.
    It is managed as an asyncio task by the TaskManager.
    :param entity: The VyraEntity containing the ROS 2 node.
    :type entity: VyraEntity
    :param taskmanager: The TaskManager instance to manage application tasks.
    :type taskmanager: TaskManager
    :param component: The Component instance to reuse across recoveries.
    """
    logger.info('Starting application runner...')
    try:
        await application.main(taskmanager, statusmanager, component)
    finally:
        logger.info('Application runner finished.')
        ErrorTraceback.check_error_exist()

async def setup_statusmanager(entity: VyraEntity) -> StatusManager:
    """
    Status manager runner as async task.
    
    Initializes StatusManager and runs periodic status broadcasting.
    
    Args:
        entity: VyraEntity instance from core application
    """
    logger.info('Starting status manager...')
    try:
        # Initialize status manager
        status_manager = StatusManager(entity)
        
        await status_manager.setup_interfaces()

        return status_manager
            
    except asyncio.CancelledError:
        logger.info('Status manager task cancelled.')
        raise
    except Exception as e:
        logger.exception(f'Status manager error: {e}')
        raise
    finally:
        logger.info('Status manager finished.')


async def ros_spinner_runner(entity: VyraEntity) -> None:
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

async def initialize_module(taskmanager: TaskManager) -> tuple[VyraEntity, StatusManager]:
    """Initializing vyra entity and configure base settings. Afterwards start 
    the application runner, communication spinner, and status manager.
    :param taskmanager: The TaskManager instance to manage application tasks.
    :type taskmanager: TaskManager
    :return: The configured VyraEntity instance and StatusManager.
    :rtype: tuple[VyraEntity, StatusManager]
    """
    logger.info('Configuring settings...')
    # Hier können spezifische Einstellungen für die Anwendung gesetzt werden
    # Zum Beispiel:
    # entity.set_parameter('parameter_name', 'value')
    entity: VyraEntity = await _base_.build_base()
    statusmanager: StatusManager = await setup_statusmanager(entity)

    # Create Component ONCE here, outside of application_runner
    # This ensures the same Component instance is reused across task recoveries
    unified_state_machine = statusmanager.state_machine
    component = Component(unified_state_machine, entity, taskmanager)
    
    # Register remote callable interfaces
    await component.set_interfaces()
    logger.info("✅ Component created and interfaces registered")

    logger.info('Starting application runner and ROS spinner...')
    # Pass component to application_runner so it can be reused across recoveries
    taskmanager.add_task(application_runner, taskmanager, statusmanager, component)
    taskmanager.add_task(ros_spinner_runner, entity)
    taskmanager.add_task(usermanager_runner, entity)
    
    if entity.node is None:
        logger.info('No ROS 2 node created, exiting...')
        raise RuntimeError("No ROS 2 node created, exiting...")
    
    return entity, statusmanager

@ErrorTraceback.w_check_error_exist
async def runner() -> None:   
    logger.info('🏁 Runner function started!')
    try:
        logger.info('📦 Creating TaskManager...')
        taskmanager = TaskManager()
        logger.info('✅ TaskManager created')
        
        logger.info('🔧 Initializing rclpy...')
        rclpy.init()
        logger.info('✅ rclpy initialized')

        logger.info('⚙️  Initializing module')
        entity, statusmanager = await initialize_module(taskmanager)
        logger.info(f'📊 Number of tasks: {len(taskmanager.tasks)}')
        logger.info(f'📋 Tasks: {list(taskmanager.tasks.keys())}')

        await task_supervisor_looper(taskmanager, statusmanager)

        # while tm.tasks:
        #     logger.info(f'🔄 Loop iteration - {len(tm.tasks)} tasks running')
        #     try:
        #         done, pending = await asyncio.wait(
        #             [task_tuple[1] for task_tuple in tm.tasks.values()],
        #             return_when=asyncio.FIRST_COMPLETED
        #         )
        #         logger.debug("Tasks completed")
        #         for task in done:
        #             if task.exception():
        #                 logger.error(
        #                     f"Task {task.get_name()} raised an exception: {task.exception()}")
                        
        #                 await asyncio.sleep(0.5)
        #             else:
        #                 logger.info(f"Task {task.get_name()} completed successfully.")
        #             tm.tasks.pop(task.get_name())

        #         for task in pending:
        #             logger.info(f"Task {task.get_name()} is still running.")

        #         await asyncio.sleep(0.01)
        #     except asyncio.TimeoutError:
        #         if entity.node and entity.node.reload_event.is_set():
        #             entity.node.reload_event.clear()  # Event zurücksetzen
        #             logger.info("Node reload event received")
        #             await taskmanager.cancel_all()
        #             entity = await initialize_module(taskmanager)
        #         elif entity.node == None:
        #             raise RuntimeError("Node is None, cannot proceed with tasks.")

    except SystemExit as e:
        logger.info(f'SystemExit: {e}. Exiting gracefully...')
        await taskmanager.cancel_all()
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
            
        await taskmanager.cancel_all()

def main() -> None:
    logger.info('🎬 Main function called!')
    try:
        logger.info('🚀 Starting asyncio.run(runner())...')
        asyncio.run(runner())
        logger.info('Exit module runner')
    except KeyboardInterrupt:
        logger.warning('KeyboardInterrupt received, closing event loop')
    except RuntimeError as e:
        logger.info(f'RuntimeError: {e}. Closing event loop')
    finally:
        logger.info('Finally exit entry point')

if __name__ == '__main__':
    logger.info('🔴 __main__ block - calling main()')
    main()