"""
Professional structured logging configuration using structlog.

This module provides a centralized logging configuration that:
- Uses structlog for structured logging with context
- Supports JSON and colored console output
- Integrates with standard Python logging
- Provides log rotation for production use
- Supports both ROS2 and Python-only (SLIM) modes
"""

import asyncio
import functools
import inspect
import json
import logging
import logging.config
import os
import sys
import time
from pathlib import Path
from typing import Any, Callable, Coroutine, Dict, Optional, TypeVar, Union, cast, overload

from vyra_base.helper.env_handler import get_env_required

import structlog
from structlog.typing import EventDict, WrappedLogger

# Type variables for generic decorator (separate for sync and async)
F = TypeVar('F', bound=Callable[..., Any])
AsyncF = TypeVar('AsyncF', bound=Callable[..., Coroutine[Any, Any, Any]])


# Environment variables for configuration
LOG_LEVEL = os.getenv("LOG_LEVEL", "INFO").upper()
LOG_FORMAT = os.getenv("LOG_FORMAT", "colored")  # 'json' or 'colored'
VYRA_SLIM = os.getenv("VYRA_SLIM", "false").lower() == "true"
MODULE_NAME = get_env_required("MODULE_NAME")  # Must be set in .env for proper logging context


def add_module_context(
    logger: WrappedLogger, method_name: str, event_dict: EventDict
) -> EventDict:
    """Add module-specific context to all log entries."""
    event_dict["module"] = MODULE_NAME
    event_dict["mode"] = "slim" if VYRA_SLIM else "full"
    return event_dict


def add_caller_info(
    logger: WrappedLogger, method_name: str, event_dict: EventDict
) -> EventDict:
    """Add caller information (file, function, line) to log entries."""
    # Get frame info from structlog's internal frames
    frame = sys._getframe()
    
    # Walk up the stack to find the actual caller (skip structlog frames)
    while frame:
        code = frame.f_code
        filename = code.co_filename
        
        # Skip structlog and logging framework frames
        if 'structlog' not in filename and 'logging' not in filename:
            event_dict["caller_file"] = Path(filename).name
            event_dict["caller_function"] = code.co_name
            event_dict["caller_line"] = frame.f_lineno
            break
            
        frame = frame.f_back
    
    return event_dict


def censor_sensitive_data(
    logger: WrappedLogger, method_name: str, event_dict: EventDict
) -> EventDict:
    """Censor sensitive data in log entries."""
    sensitive_keys = ["password", "token", "secret", "api_key", "authorization"]
    
    for key in event_dict.keys():
        if any(sensitive in key.lower() for sensitive in sensitive_keys):
            event_dict[key] = "***CENSORED***"
    
    return event_dict


def setup_structlog() -> None:
    """
    Configure structlog with professional settings.
    
    This function sets up:
    - JSON or colored console output based on environment
    - Timestamps in ISO format
    - Log levels
    - Context processors for debugging
    - Integration with standard logging
    """
    # Determine if we're in development (for colored output) or production (JSON)
    is_development = LOG_FORMAT == "colored" or os.getenv("VYRA_DEV_MODE", "false").lower() == "true"
    
    # Configure shared processors
    shared_processors = [
        structlog.stdlib.add_log_level,
        structlog.stdlib.add_logger_name,
        add_module_context,
        structlog.processors.TimeStamper(fmt="iso", utc=True),
        structlog.stdlib.PositionalArgumentsFormatter(),
        structlog.processors.StackInfoRenderer(),
        structlog.processors.format_exc_info,
        censor_sensitive_data,
        structlog.processors.UnicodeDecoder(),
    ]
    
    # Add caller info only in development (performance overhead)
    if is_development:
        shared_processors.insert(3, add_caller_info)
    
    # Configure structlog
    structlog.configure(
        processors=shared_processors + [
            structlog.stdlib.ProcessorFormatter.wrap_for_formatter,
        ],
        context_class=dict,
        logger_factory=structlog.stdlib.LoggerFactory(),
        wrapper_class=structlog.stdlib.BoundLogger,
        cache_logger_on_first_use=True,
    )


def load_logging_config(config_path: Path = None) -> Dict[str, Any]:
    """
    Load logging configuration from JSON file.
    
    Returns:
        Dict containing logging configuration
        
    Raises:
        FileNotFoundError: If config file doesn't exist
        json.JSONDecodeError: If config file is invalid
    """
    if config_path is None:
        config_path = Path("/workspace/config/core_logging.json")
    
    if not config_path.exists():
        raise FileNotFoundError(
            f"Logging configuration not found: {config_path}\n"
            "Please ensure core_logging.json exists in the config directory."
        )
    
    try:
        with open(config_path, 'r') as f:
            config = json.load(f)
        return config
    except json.JSONDecodeError as e:
        raise json.JSONDecodeError(
            f"Invalid JSON in logging configuration: {e.msg}",
            e.doc,
            e.pos
        )


def setup_standard_logging(log_dir: Path = None) -> None:
    """
    Configure standard Python logging from JSON config file.
    
    This integrates with structlog and provides:
    - File rotation
    - Multiple handlers (console, file, error file)
    - Proper log levels
    """
    try:
        config = load_logging_config()
        
        # Ensure log directories exist
        if log_dir is None:
            log_dir = Path("/workspace/log/core")
        
        log_dir.mkdir(parents=True, exist_ok=True)
        
        # Apply configuration
        logging.config.dictConfig(config)
        
        # Set root log level from environment
        logging.getLogger().setLevel(getattr(logging, LOG_LEVEL, logging.INFO))
        
    except (FileNotFoundError, json.JSONDecodeError) as e:
        # Fallback to basic configuration
        print(f"⚠️  Warning: Could not load logging config: {e}", file=sys.stderr)
        print("⚠️  Falling back to basic logging configuration", file=sys.stderr)
        
        logging.basicConfig(
            level=getattr(logging, LOG_LEVEL, logging.INFO),
            format="%(asctime)s - %(levelname)-8s - %(name)s - %(message)s",
            handlers=[
                logging.StreamHandler(sys.stdout),
                logging.StreamHandler(sys.stderr)
            ]
        )


def configure_logging() -> structlog.stdlib.BoundLogger:
    """
    Main entry point for logging configuration.
    
    Sets up both structlog and standard logging, and returns a configured logger.
    
    Returns:
        A structlog logger instance ready for use
        
    Example:
        >>> from v2_modulemanager.logging_config import configure_logging
        >>> logger = configure_logging()
        >>> logger.info("application_started", version="1.0.0", mode="production")
    """
    # Setup standard logging first (file handlers, etc.)
    setup_standard_logging()
    
    # Setup structlog on top
    setup_structlog()
    
    # Create and return a logger
    logger = structlog.get_logger(__name__)
    
    logger.info(
        "logging_configured",
        log_level=LOG_LEVEL,
        log_format=LOG_FORMAT,
        slim_mode=VYRA_SLIM,
        module=MODULE_NAME
    )
    
    return logger


def get_logger(name: Optional[str] = None) -> structlog.stdlib.BoundLogger:
    """
    Get a structlog logger with the given name.
    
    Args:
        name: Logger name (typically __name__ from the calling module)
              If None, returns a logger with the caller's module name
    
    Returns:
        A bound structlog logger instance
        
    Example:
        >>> from v2_modulemanager.logging_config import get_logger
        >>> logger = get_logger(__name__)
        >>> logger.info("processing_started", task_id="12345", user="admin")
    """
    return structlog.get_logger(name)


# Utility functions for common logging patterns
def log_function_call(logger: structlog.stdlib.BoundLogger, **kwargs) -> None:
    """
    Log a function call with structured context.
    
    Args:
        logger: The structlog logger instance
        **kwargs: Additional context to log
        
    Example:
        >>> log_function_call(logger, function="process_data", input_size=1000)
    """
    logger.debug("function_called", **kwargs)


def log_function_result(
    logger: structlog.stdlib.BoundLogger,
    success: bool = True,
    **kwargs
) -> None:
    """
    Log a function result with structured context.
    
    Args:
        logger: The structlog logger instance
        success: Whether the function succeeded
        **kwargs: Additional context to log
        
    Example:
        >>> log_function_result(logger, success=True, records_processed=500, duration_ms=1234)
    """
    level = "info" if success else "error"
    getattr(logger, level)("function_completed", success=success, **kwargs)


def log_exception(
    logger: structlog.stdlib.BoundLogger,
    exception: Exception,
    context: Optional[Dict[str, Any]] = None,
    **kwargs
) -> None:
    """
    Log an exception with full context and traceback.
    
    Args:
        logger: The structlog logger instance
        exception: The exception to log
        context: Additional context dictionary
        **kwargs: Additional context to log
        
    Example:
        >>> try:
        ...     dangerous_operation()
        ... except Exception as e:
        ...     log_exception(logger, e, context={"user_id": 123}, operation="dangerous_operation")
    """
    log_context = {
        "exception_type": type(exception).__name__,
        "exception_message": str(exception),
        **(context or {}),
        **kwargs
    }
    logger.exception("exception_occurred", **log_context)


@overload
def log_call(func: AsyncF) -> AsyncF:
    ...

@overload
def log_call(func: F) -> F:
    ...

@overload
def log_call(func: None = None, *, logger: Optional[structlog.stdlib.BoundLogger] = None) -> Callable[[Union[F, AsyncF]], Union[F, AsyncF]]:
    ...

def log_call(
    func: Optional[Union[F, AsyncF]] = None, 
    *, 
    logger: Optional[structlog.stdlib.BoundLogger] = None
) -> Union[F, AsyncF, Callable[[Union[F, AsyncF]], Union[F, AsyncF]]]:
    """
    Decorator to automatically log function calls, results, and exceptions.
    
    Logs:
    - Function entry with arguments (at DEBUG level)
    - Function exit with result/duration (at INFO level)
    - Exceptions with full context (at ERROR level)
    
    Works with both sync and async functions.
    
    Args:
        func: The function to decorate (automatically passed when used as @log_call)
        logger: Optional logger instance. If None, creates one from function's module.
    
    Example:
        >>> @log_call
        ... async def process_module(module_name: str, config: dict):
        ...     return await do_something()
        
        >>> @log_call(logger=custom_logger)
        ... def synchronous_function(x: int):
        ...     return x * 2
    """
    def decorator(f: Union[F, AsyncF]) -> Union[F, AsyncF]:
        # Get logger for this function's module
        func_logger = logger or get_logger(f.__module__)
        
        # Determine if function is async
        is_async = asyncio.iscoroutinefunction(f)
        
        if is_async:
            @functools.wraps(f)
            async def async_wrapper(*args, **kwargs):
                # Get function signature for better argument logging
                sig = inspect.signature(f)
                bound_args = sig.bind_partial(*args, **kwargs)
                bound_args.apply_defaults()
                
                # Prepare context (filter out large objects)
                call_context = {}
                for arg_name, arg_value in bound_args.arguments.items():
                    # Skip 'self' and large objects
                    if arg_name == 'self':
                        continue
                    # Log simple types directly, others by type
                    if isinstance(arg_value, (str, int, float, bool, type(None))):
                        call_context[arg_name] = arg_value
                    else:
                        call_context[f"{arg_name}_type"] = type(arg_value).__name__
                
                # Log function call
                func_logger.debug(
                    "function_called",
                    function=f.__name__,
                    module=f.__module__,
                    **call_context
                )
                
                start_time = time.time()
                try:
                    result = await f(*args, **kwargs)
                    duration_ms = (time.time() - start_time) * 1000
                    
                    # Log successful completion
                    func_logger.info(
                        "function_completed",
                        function=f.__name__,
                        module=f.__module__,
                        duration_ms=round(duration_ms, 2),
                        success=True
                    )
                    
                    return result
                    
                except Exception as e:
                    duration_ms = (time.time() - start_time) * 1000
                    
                    # Log exception
                    log_exception(
                        func_logger,
                        e,
                        context={
                            "function": f.__name__,
                            "module": f.__module__,
                            "duration_ms": round(duration_ms, 2),
                            **call_context
                        }
                    )
                    raise
            
            return cast(Union[F, AsyncF], async_wrapper)  # type: ignore[return-value]
        else:
            @functools.wraps(f)
            def sync_wrapper(*args, **kwargs):
                # Get function signature for better argument logging
                sig = inspect.signature(f)
                bound_args = sig.bind_partial(*args, **kwargs)
                bound_args.apply_defaults()
                
                # Prepare context (filter out large objects)
                call_context = {}
                for arg_name, arg_value in bound_args.arguments.items():
                    # Skip 'self' and large objects
                    if arg_name == 'self':
                        continue
                    # Log simple types directly, others by type
                    if isinstance(arg_value, (str, int, float, bool, type(None))):
                        call_context[arg_name] = arg_value
                    else:
                        call_context[f"{arg_name}_type"] = type(arg_value).__name__
                
                # Log function call
                func_logger.debug(
                    "function_called",
                    function=f.__name__,
                    module=f.__module__,
                    **call_context
                )
                
                start_time = time.time()
                try:
                    result = f(*args, **kwargs)
                    duration_ms = (time.time() - start_time) * 1000
                    
                    # Log successful completion
                    func_logger.info(
                        "function_completed",
                        function=f.__name__,
                        module=f.__module__,
                        duration_ms=round(duration_ms, 2),
                        success=True
                    )
                    
                    return result
                    
                except Exception as e:
                    duration_ms = (time.time() - start_time) * 1000
                    
                    # Log exception
                    log_exception(
                        func_logger,
                        e,
                        context={
                            "function": f.__name__,
                            "module": f.__module__,
                            "duration_ms": round(duration_ms, 2),
                            **call_context
                        }
                    )
                    raise
            
            return cast(Union[F, AsyncF], sync_wrapper)  # type: ignore[return-value]
    
    # Support both @log_call and @log_call()
    if func is None:
        return decorator
    else:
        return decorator(func)


# Module initialization - configure logging when imported
if __name__ != "__main__":
    # Only auto-configure if not run as main script
    pass  # Configuration happens in main.py
