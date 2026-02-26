import asyncio
import functools
import os
import uvicorn
from pathlib import Path
import signal
import sys

# Add /workspace to Python path for storage.interfaces.grpc_generated imports
if '/workspace' not in sys.path:
    sys.path.insert(0, '/workspace')

# Initialize structured logging FIRST
from .logging_config import configure_logging, get_logger, log_exception, log_call

# Configure logging before any other imports
configure_logging()
logger = get_logger(__name__)

# Now import ROS2 conditionally
VYRA_SLIM = os.getenv('VYRA_SLIM', 'false').lower() == 'true'
if not VYRA_SLIM:
    try:
        import rclpy  # pyright: ignore[reportMissingImports]
        logger.info("ros2_imported", slim_mode=False)
    except ImportError as e:
        logger.error("ros2_import_failed", error=str(e), slim_mode=False)
        raise
else:
    rclpy = None  # type: ignore
    logger.info("ros2_skipped", slim_mode=True, reason="VYRA_SLIM mode enabled")

from . import _base_
from .application import application
from .application.application import Component
from .taskmanager import TaskManager, task_supervisor_looper
from .status.status_manager import StatusManager
from . import container_injection

from vyra_base.core.entity import VyraEntity
from vyra_base.helper.error_handler import ErrorTraceback 

logger.info(
    "module_mode_configured",
    slim_mode=VYRA_SLIM,
    mode="python_only" if VYRA_SLIM else "full_ros2",
    ros2_available=rclpy is not None
)

def handle_sigterm(signum, frame):
    """Handle SIGTERM signal for graceful shutdown."""
    logger.warning(
        "signal_received",
        signal_number=signum,
        signal_name="SIGTERM" if signum == signal.SIGTERM else "SIGINT",
        slim_mode=VYRA_SLIM
    )
    
    # Only shutdown ROS2 if running in normal mode
    if not VYRA_SLIM and rclpy and rclpy.ok():
        logger.info("shutting_down_ros2", reason="signal_received")
        try:
            rclpy.shutdown()
            logger.info("ros2_shutdown_complete")
        except Exception as e:
            log_exception(logger, e, context={"operation": "ros2_shutdown"})
    
    # Exit with SIGTERM code (143 = 128+15) so Docker Swarm knows this was forced shutdown
    exit_code = 143
    logger.info(
        "process_exiting",
        exit_code=exit_code,
        reason="forced_shutdown"
    )
    sys.exit(exit_code)

signal.signal(signal.SIGTERM, handle_sigterm)
signal.signal(signal.SIGINT, handle_sigterm)

@log_call
async def application_runner(
        taskmanager: TaskManager,
        statusmanager: StatusManager,
        component) -> None:
    """
    Main application logic runner.
    
    Starts the Component and keeps it running. Managed as an asyncio task by TaskManager.
    
    Args:
        taskmanager: TaskManager instance to manage application tasks
        statusmanager: StatusManager for monitoring application status
        component: Component instance to reuse across recoveries
    """
    await application.main(taskmanager, statusmanager, component)
    ErrorTraceback.check_error_exist()

@log_call
async def setup_statusmanager(entity: VyraEntity) -> StatusManager:
    """
    Initialize and configure the Status Manager.
    
    Args:
        entity: VyraEntity instance from core application
        
    Returns:
        Configured StatusManager instance
        
    Raises:
        Exception: If status manager initialization fails
    """
    logger.info("status_manager_initializing")
    
    # Initialize status manager
    status_manager = StatusManager(entity)
    logger.debug("status_manager_created", status_manager_type=type(status_manager).__name__)
    
    await status_manager.setup_interfaces()
    logger.info("status_manager_interfaces_setup_complete")

    return status_manager


@log_call
async def ros_spinner_runner(entity: VyraEntity) -> None:
    """
    Main ROS2 communication spinner.
    
    Handles the rclpy.spin_once loop for ROS2 message processing.
    Only runs in normal (non-SLIM) mode.
    
    Args:
        entity: VyraEntity containing the ROS2 node
    """
    logger.info("ros_spinner_starting", node_name=entity.node.get_name())
    spin_count = 0
    error_count = 0
    
    if rclpy is None:
        logger.error("ros_spinner_called_without_rclpy", slim_mode=VYRA_SLIM)
        return
    
    loop = asyncio.get_running_loop()
    spin_fn = functools.partial(rclpy.spin_once, entity.node, timeout_sec=0.001)

    while rclpy.ok():
        try:
            # Run spin_once in a thread-pool executor so it never blocks the
            # asyncio event loop.  Without this, the 10 ms timeout_sec call
            # prevented uvicorn from accepting TCP connections fast enough,
            # filling the TCP backlog and causing Traefik 504s.
            await loop.run_in_executor(None, spin_fn)
            spin_count += 1
            
            # Log periodic heartbeat (every 1000 spins)
            if spin_count % 1000 == 0:
                logger.debug(
                    "ros_spinner_heartbeat",
                    spin_count=spin_count,
                    error_count=error_count
                )
            
            # Yield to other coroutines (uvicorn, etc.) between spins
            await asyncio.sleep(0)
            
        except Exception as spin_error:
            error_count += 1
            logger.error(
                "ros_spin_error",
                error=str(spin_error),
                error_count=error_count,
                spin_count=spin_count
            )
            if error_count > 10:
                logger.critical(
                    "ros_spinner_error_threshold_exceeded",
                    error_count=error_count,
                    threshold=10
                )
                raise
    
    logger.info("ros_spinner_finished", total_spins=spin_count, total_errors=error_count)
    ErrorTraceback.check_error_exist()

@log_call
async def web_backend_runner() -> None:
    """
    Start the Uvicorn server for the REST API.
    
    This task is only started if ENABLE_BACKEND_WEBSERVER=true in .env
    Waits for container initialization before starting the server.
    """
    logger.info("web_backend_initializing")
    
    # Wait for container to be initialized
    wait_count = 0
    while not container_injection.is_initialized():
        wait_count += 1
        logger.debug(
            "waiting_for_container_init",
            wait_count=wait_count,
            wait_time_seconds=wait_count * 0.5
        )
        await asyncio.sleep(0.5)
        
        if wait_count > 60:  # 30 seconds timeout
            logger.error(
                "container_init_timeout",
                wait_count=wait_count,
                timeout_seconds=30
            )
            raise TimeoutError("Container initialization timeout after 30 seconds")
    
    logger.info("container_initialized", wait_count=wait_count)
    
    # Get module name dynamically from entity
    entity = container_injection.get_entity()
    module_name = entity.module_entry.name
    app_path = f"{module_name}.{module_name}.backend_webserver.asgi:application"
    
    logger.info(
        "web_backend_config",
        module_name=module_name,
        app_path=app_path
    )
    
    cert_path = "/workspace/storage/certificates/webserver.crt"
    key_path = "/workspace/storage/certificates/webserver.key"
    
    # Check for SSL certificates
    ssl_enabled = os.path.exists(cert_path) and os.path.exists(key_path)
    
    if ssl_enabled:
        logger.info(
            "uvicorn_ssl_enabled",
            cert_path=cert_path,
            key_path=key_path
        )
        config = uvicorn.Config(
            app=app_path,
            host="0.0.0.0",
            port=8443,
            log_level="info",
            ssl_certfile=cert_path,
            ssl_keyfile=key_path,
            reload=False
        )
    else:
        logger.warning(
            "uvicorn_ssl_disabled",
            reason="certificates_not_found",
            expected_cert=cert_path,
            expected_key=key_path
        )
        config = uvicorn.Config(
            app=app_path,
            host="0.0.0.0",
            port=8443,
            log_level="info",
            reload=False
        )
    
    logger.info(
        "uvicorn_starting",
        host=config.host,
        port=config.port,
        ssl_enabled=ssl_enabled
    )
    
    server = uvicorn.Server(config)
    await server.serve()

@log_call
async def initialize_module(taskmanager: TaskManager) -> tuple[VyraEntity, StatusManager]:
    """
    Initialize VYRA entity and configure base settings.
    
    Sets up the module infrastructure including:
    - VyraEntity creation
    - StatusManager initialization
    - Component creation and interface registration
    - Container dependency injection
    - Task scheduling (application, ROS2 spinner, web backend)
    
    Args:
        taskmanager: TaskManager instance to manage application tasks
        
    Returns:
        Tuple of (VyraEntity, StatusManager)
        
    Raises:
        RuntimeError: If ROS2 node creation fails in non-SLIM mode
    """
    # Build base entity
    logger.debug("building_base_entity")
    entity: VyraEntity = await _base_.build_base()
    logger.info(
        "entity_created",
        module_name=entity.module_entry.name,
        node_name=entity.node.get_name() if entity.node else "None"
    )
    
    # Setup status manager
    logger.debug("setting_up_status_manager")
    statusmanager: StatusManager = await setup_statusmanager(entity)
    logger.info("status_manager_ready")

    # Create Component (reused across task recoveries)
    logger.debug("creating_component")
    unified_state_machine = statusmanager.state_machine
    component = Component(unified_state_machine, entity, taskmanager)
    logger.info(
        "component_created",
        component_type=type(component).__name__,
        state_machine=type(unified_state_machine).__name__
    )
    
    # Register remote callable interfaces
    logger.debug("registering_component_interfaces")
    await component.set_interfaces()
    logger.info("component_interfaces_registered")
    
    # Set instances in container_injection for web_backend access
    logger.debug("injecting_container_dependencies")
    container_injection.set_entity(entity)
    container_injection.set_component(component)
    container_injection.set_task_manager(taskmanager)
    container_injection.set_status_manager(statusmanager)
    logger.info("container_dependencies_injected")

    # Schedule application runner task
    logger.info("scheduling_application_runner_task")
    taskmanager.add_task(application_runner, taskmanager, statusmanager, component)
    logger.debug("application_runner_task_scheduled")
    
    # ROS2-dependent tasks: only start if NOT in SLIM mode
    if not VYRA_SLIM:
        logger.info("scheduling_ros2_tasks", reason="non_slim_mode")
        
        # Validate ROS2 node was created
        if entity.node is None:
            logger.critical(
                "ros2_node_missing",
                entity_module=entity.module_entry.name,
                slim_mode=VYRA_SLIM
            )
            raise RuntimeError("No ROS 2 node created in non-SLIM mode")
        
        taskmanager.add_task(ros_spinner_runner, entity)
        logger.info(
            "ros2_spinner_task_scheduled",
            node_name=entity.node.get_name()
        )
    else:
        logger.info("skipping_ros2_tasks", reason="slim_mode_enabled")
    
    # Conditionally start web backend if ENABLE_BACKEND_WEBSERVER=true (works in both modes)
    enable_webserver = os.getenv('ENABLE_BACKEND_WEBSERVER', 'false').lower() == 'true'
    if enable_webserver:
        logger.info("scheduling_web_backend_task", reason="webserver_enabled")
        taskmanager.add_task(web_backend_runner)
        logger.debug("web_backend_task_scheduled")
    else:
        logger.info("skipping_web_backend_task", reason="webserver_disabled")
    
    task_count = len(taskmanager.tasks)
    task_names = list(taskmanager.tasks.keys())
    
    logger.info(
        "module_initialization_complete",
        task_count=task_count,
        task_names=task_names,
        slim_mode=VYRA_SLIM,
        webserver_enabled=enable_webserver
    )
    
    return entity, statusmanager

@ErrorTraceback.w_check_error_exist
async def runner() -> None:
    """
    Main async runner function.
    
    Orchestrates the entire module lifecycle:
    1. TaskManager creation
    2. ROS2 initialization (if not SLIM mode)
    3. Module initialization
    4. Task supervision loop
    5. Graceful cleanup on shutdown
    """
    logger.info(
        "runner_started",
        slim_mode=VYRA_SLIM,
        pid=os.getpid()
    )
    
    taskmanager = None
    entity = None
    
    try:
        # Create TaskManager
        logger.debug("creating_task_manager")
        taskmanager = TaskManager()
        logger.info("task_manager_created", taskmanager_id=id(taskmanager))
        
        # Only initialize ROS2 if NOT in SLIM mode
        if not VYRA_SLIM:
            if rclpy is None:
                logger.critical("rclpy_not_imported", mode="full")
                raise RuntimeError("ROS2 not available in non-SLIM mode")
            
            logger.info("initializing_rclpy", mode="full")
            try:
                rclpy.init()
                logger.info("rclpy_initialized")
            except Exception as e:
                log_exception(logger, e, context={"operation": "rclpy_init"})
                raise
        else:
            logger.info("skipping_rclpy_init", mode="slim")

        # Initialize module
        logger.info("initializing_module")
        entity, statusmanager = await initialize_module(taskmanager)
        
        task_count = len(taskmanager.tasks)
        task_names = list(taskmanager.tasks.keys())
        logger.info(
            "module_initialized",
            task_count=task_count,
            task_names=task_names,
            module_name=entity.module_entry.name if entity else "unknown"
        )

        # Start task supervision loop
        logger.info("starting_task_supervisor")
        await task_supervisor_looper(taskmanager, statusmanager)
        logger.info("task_supervisor_completed")

    except SystemExit as e:
        logger.info(
            "system_exit_received",
            exit_code=e.code,
            slim_mode=VYRA_SLIM
        )
        if taskmanager:
            logger.debug("cancelling_all_tasks", reason="system_exit")
            await taskmanager.cancel_all()
            
    except KeyboardInterrupt:
        logger.warning(
            "keyboard_interrupt_received",
            pid=os.getpid()
        )
        if taskmanager:
            logger.debug("cancelling_all_tasks", reason="keyboard_interrupt")
            await taskmanager.cancel_all()
            
    except Exception as e:
        log_exception(
            logger,
            e,
            context={
                "function": "runner",
                "slim_mode": VYRA_SLIM,
                "has_entity": entity is not None,
                "has_taskmanager": taskmanager is not None
            }
        )
        if taskmanager:
            logger.debug("cancelling_all_tasks", reason="exception")
            await taskmanager.cancel_all()
            
    finally:
        # Cleanup ROS2 resources if in normal mode
        logger.info("cleanup_started", slim_mode=VYRA_SLIM)
        
        if not VYRA_SLIM:
            if entity and hasattr(entity, 'node') and entity.node is not None:
                try:
                    logger.debug(
                        "destroying_ros2_node",
                        node_name=entity.node.get_name()
                    )
                    entity.node.destroy_node()
                    logger.info("ros2_node_destroyed")
                except Exception as e:
                    log_exception(logger, e, context={"operation": "destroy_ros2_node"})
            else:
                logger.debug("no_ros2_node_to_destroy")

            if rclpy and rclpy.ok():
                try:
                    logger.debug("shutting_down_rclpy")
                    rclpy.shutdown()
                    logger.info("rclpy_shutdown_complete")
                except Exception as e:
                    log_exception(logger, e, context={"operation": "rclpy_shutdown"})
            else:
                logger.debug("rclpy_not_running")
        else:
            logger.debug("skipping_ros2_cleanup", reason="slim_mode")
            
        if taskmanager:
            logger.debug("final_task_cancellation")
            await taskmanager.cancel_all()
            logger.info("all_tasks_cancelled")
        
        logger.info("cleanup_complete")


def main() -> None:
    """
    Main entry point for the module.
    
    Configures the async event loop and starts the runner.
    Handles top-level exceptions and ensures proper cleanup.
    """
    logger.info(
        "main_entry_point",
        pid=os.getpid(),
        python_version=sys.version.split()[0],
        slim_mode=VYRA_SLIM
    )
    
    try:
        logger.debug("starting_asyncio_runner")
        asyncio.run(runner())
        logger.info("module_exited_normally")
        
    except KeyboardInterrupt:
        logger.warning("main_keyboard_interrupt")
        
    except RuntimeError as e:
        logger.error(
            "main_runtime_error",
            error=str(e),
            error_type=type(e).__name__
        )
        
    except Exception as e:
        log_exception(
            logger,
            e,
            context={"function": "main"}
        )
        
    finally:
        logger.info("main_exit_complete")


if __name__ == '__main__':
    logger.info(
        "module_direct_execution",
        file=__file__,
        pid=os.getpid()
    )
    main()