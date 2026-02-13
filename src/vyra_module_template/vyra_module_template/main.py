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
from . import container_injection

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

# Check if operating in SLIM mode (Python-only, no ROS2)
VYRA_SLIM = os.getenv('VYRA_SLIM', 'false').lower() == 'true'
if VYRA_SLIM:
    logger.info('🎯 VYRA_SLIM=true: Python-only mode (no ROS2)')
else:
    logger.info('🎯 VYRA_SLIM=false: Full ROS2 mode with gRPC')

def handle_sigterm(signum, frame):
    logger.warning("SIGTERM empfangen...")
    
    # Only shutdown ROS2 if running in normal mode
    if not VYRA_SLIM and rclpy.ok():
        logger.warning("Shutting down ROS2...")
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


async def web_backend_runner(entity: VyraEntity, taskmanager: TaskManager, statusmanager: StatusManager, component) -> None:
    """
    Runner for the backend webserver (uvicorn).
    Starts the FastAPI application via uvicorn.Server.
    """
    import asyncio
    import uvicorn
    
    logger = logging.getLogger(__name__)
    logger.info('🌐 Starting backend webserver runner...')
    
    try:
        # Get module name dynamically
        module_name = entity.module_entry.name if hasattr(entity, 'module_entry') and entity.module_entry else os.getenv('MODULE_NAME', 'vyra_module_template')
        app_path = f"{module_name}.backend_webserver.asgi:app"
        
        logger.info(f'Loading ASGI application from: {app_path}')
        
        # Uvicorn server config
        config = uvicorn.Config(
            app=app_path,
            host="0.0.0.0",
            port=8443,
            ssl_keyfile="/workspace/storage/certificates/selfsigned/key.pem",
            ssl_certfile="/workspace/storage/certificates/selfsigned/cert.pem",
            log_level="info",
            reload=False,  # Hot reload managed by tools/hot_reload.py
            workers=1
        )
        
        server = uvicorn.Server(config)
        logger.info('✅ Uvicorn server configured')
        
        # Start server (blocking)
        logger.info('🚀 Starting uvicorn server...')
        await server.serve()
        
    except asyncio.CancelledError:
        logger.info('Backend webserver task cancelled')
        raise
    except Exception as e:
        logger.exception(f'Backend webserver error: {e}')
        raise


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
    
    # Initialize container injection with all dependencies
    logger.info('Setting up container injection...')
    container_injection.set_entity(entity)
    container_injection.set_component(component)
    container_injection.set_task_manager(taskmanager)
    container_injection.set_status_manager(statusmanager)
    logger.info('✅ Container injection configured')

    logger.info('Starting tasks...')
    # Pass component to application_runner so it can be reused across recoveries
    taskmanager.add_task(application_runner, taskmanager, statusmanager, component)
    
    # Note: UserManager is now integrated in Component class via vyra_base
    # No separate usermanager_runner task needed anymore
    
    # ROS2-dependent tasks: only start if NOT in SLIM mode
    if not VYRA_SLIM:
        logger.info('Starting ROS2-dependent tasks (ros_spinner)...')
        taskmanager.add_task(ros_spinner_runner, entity)
        
        # Validate ROS2 node was created
        if entity.node is None:
            logger.error('No ROS 2 node created, exiting...')
            raise RuntimeError("No ROS 2 node created, exiting...")
    else:
        logger.info('⏭️  SLIM mode: skipping ROS2-dependent tasks')
    
    # Backend webserver: optional via environment variable
    if os.getenv('ENABLE_BACKEND_WEBSERVER', 'false').lower() == 'true':
        logger.info('Starting backend webserver task...')
        taskmanager.add_task(web_backend_runner, entity, taskmanager, statusmanager, component)
    else:
        logger.info('⏭️  Backend webserver disabled (ENABLE_BACKEND_WEBSERVER not set)')
    
    return entity, statusmanager

@ErrorTraceback.w_check_error_exist
async def runner() -> None:   
    logger.info('🏁 Runner function started!')
    try:
        logger.info('📦 Creating TaskManager...')
        taskmanager = TaskManager()
        logger.info('✅ TaskManager created')
        
        # Only initialize ROS2 if NOT in SLIM mode
        if not VYRA_SLIM:
            logger.info('🔧 Initializing rclpy (normal mode)...')
            rclpy.init()
            logger.info('✅ rclpy initialized')
        else:
            logger.info('⏭️  Skipping rclpy init (SLIM mode)...')

        logger.info('⚙️  Initializing module')
        entity, statusmanager = await initialize_module(taskmanager)
        logger.info(f'📊 Number of tasks: {len(taskmanager.tasks)}')
        logger.info(f'📋 Tasks: {list(taskmanager.tasks.keys())}')

        await task_supervisor_looper(taskmanager, statusmanager)

    except SystemExit as e:
        logger.info(f'SystemExit: {e}. Exiting gracefully...')
        await taskmanager.cancel_all()
    except KeyboardInterrupt:
        logger.warning('KeyboardInterrupt received, closing event loop')
    except Exception as e:
        logger.exception(f'Exception: {e}. Closing event loop')
    finally:
        # Only cleanup ROS2 if it was initialized
        if not VYRA_SLIM:
            if 'entity' in locals():
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
                logger.info('ROS 2 was not running, nothing to destroy.')
        else:
            logger.info('⏭️  Skipping ROS2 cleanup (SLIM mode)')
            
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