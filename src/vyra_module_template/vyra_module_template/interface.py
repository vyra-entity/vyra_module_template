import json
import logging
import os
import sys
from pathlib import Path

from lark import logger

from typing import Any
from typing import Callable


from ament_index_python.packages import get_package_share_directory  # pyright: ignore[reportMissingImports]

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import FunctionConfigEntry
from vyra_base.defaults.entries import FunctionConfigDisplaystyle
from vyra_base.defaults.entries import FunctionConfigBaseTypes
from vyra_base.helper.error_handler import ErrorTraceback


logger = logging.getLogger(__name__)


@ErrorTraceback.w_check_error_exist
async def auto_register_callable_interfaces(
    entity: VyraEntity, 
    callback_list: list[Callable]=[], 
    callback_parent: object=None,
    publisher_list: list=[]) -> None:
    """Automatically registers callable interfaces for the entity. The list of callbacks must
    contain all functions that are defined in the interface metadata.
    Args:
        entity (VyraEntity): The entity to register interfaces for.
        callback_list (list[Callable], optional): List of functions to register.
        callback_parent (Callable, optional): Parent callback for loading all remote callables. Defaults to None.

    Either a callback_list or a callback_parent must be provided.
    """
    if not callback_list and not callback_parent:
        raise ValueError("Either callback_list or callback_parent must be provided.")
    
    if not callback_list:
        logger.debug(
            "No callback_list provided, loading all remote callables from parent."
        )
        callback_list = _autoload_all_remote_callable_from_parent(callback_parent)
        logger.debug(
            f"Loaded {len(callback_list)} remote callables from parent."
        )

    module_name = os.getenv("MODULE_NAME", "")

    interface_metadata: list[dict[str, Any]] = _load_metadata(f'{module_name}_interfaces', Path('config'))

    interface_functions: list[FunctionConfigEntry] = []

    for callback in callback_list:
        config_list: list = [m for m in interface_metadata 
                    if m['functionname'] == callback.__name__]

        if not config_list:
            logger.warning(
                f"No config found for callback {callback.__name__}, skipping."
            )
            continue
        elif len(config_list) > 1:
            logger.warning(
                f"Multiple metadata entries found for callback {callback.__name__}, "
                f"using the first one from config: {config_list}. Please check your configuration!"
            )
            
        else:
            metadata: dict = config_list[0]

        ros2_type: str = metadata['filetype'].split('/')[-1]
        ros2_type = ros2_type.split('.')[0]
        
        match metadata['type']:
            case FunctionConfigBaseTypes.callable.value:
                metadata['ros2type'] = getattr(
                    sys.modules[f'{module_name}_interfaces.srv'], ros2_type)
                interface_functions.append(_register_callable_interface(
                    callback=callback,
                    metadata=metadata
                )) 

            case FunctionConfigBaseTypes.job.value:
                metadata['ros2type'] = getattr(
                    sys.modules[f'{module_name}_interfaces.action'], ros2_type)
                
                interface_functions.append(_register_job_interface(
                    metadata=metadata,
                    callbacks={}
                ))

    logger.info(f"Registering {len(interface_functions)} interfaces for entity")
    await entity.set_interfaces(interface_functions)
    return

def _autoload_all_remote_callable_from_parent(callback_parent: object) -> list:
    callable_list = []
    
    logger.debug(f"Scanning {callback_parent.__class__.__name__} for remote callables...")
    logger.debug(f"  callback_parent type: {type(callback_parent)}")
    logger.debug(f"  callback_parent class: {callback_parent.__class__}")
    
    # Check both instance and class for remote callables
    # This is necessary because decorator attributes might be on the class method
    for attr_name in dir(callback_parent):
        if attr_name.startswith("_"):
            continue
            
        try:
            # Get attribute from instance (bound method)
            attr = getattr(callback_parent, attr_name)
            
            # Debug specific method
            if attr_name == "get_interface_list":
                logger.debug(f"  Checking get_interface_list:")
                logger.debug(f"    attr: {attr}")
                logger.debug(f"    type(attr): {type(attr)}")
                logger.debug(f"    callable: {callable(attr)}")
                logger.debug(f"    has _remote_callable: {hasattr(attr, '_remote_callable')}")
                logger.debug(f"    _remote_callable value: {getattr(attr, '_remote_callable', 'NOT FOUND')}")
                
                # Try __func__ if it's a bound method
                if hasattr(attr, "__func__"):
                    logger.debug(f"    __func__._remote_callable: {getattr(attr.__func__, '_remote_callable', 'NOT FOUND')}")
                
                # Try class method
                class_method = getattr(callback_parent.__class__, "get_interface_list", None)
                if class_method:
                    logger.debug(f"    class method._remote_callable: {getattr(class_method, '_remote_callable', 'NOT FOUND')}")
            
            # Check if it's callable and has _remote_callable marker
            # Note: We check for attribute existence, not value, because vyra_base 
            # sets _remote_callable=False after registering to DataSpace
            if callable(attr) and hasattr(attr, "_remote_callable"):
                logger.debug(f"  Found remote_callable on instance: {attr_name}")
                callable_list.append(attr)
                continue
            
            # If not found on instance, try the class
            # This handles cases where decorator is on class method
            if hasattr(callback_parent.__class__, attr_name):
                class_attr = getattr(callback_parent.__class__, attr_name)
                if callable(class_attr) and hasattr(class_attr, "_remote_callable"):
                    logger.debug(f"  Found remote_callable on class: {attr_name}")
                    # Get the bound method from instance
                    callable_list.append(attr)
        except AttributeError as e:
            if attr_name == "get_interface_list":
                logger.debug(f"  AttributeError for get_interface_list: {e}")
            continue
        except Exception as e:
            logger.debug(f"  Unexpected error for {attr_name}: {e}")
            continue
    
    logger.debug(f"Total remote callables found: {len(callable_list)}")
    return callable_list

def _load_metadata(package_name: str, resource_folder: Path) -> list[dict[str, Any]]:
    """Loads metadata from a specified package and resource."""
    package_path = get_package_share_directory(package_name)
    resource_path = Path(package_path) / resource_folder
    meta_paths: list[Path] = list(resource_path.rglob("*.json"))

    metadata: list[dict] = []

    logger.debug(f"Meta paths: {meta_paths}")

    for meta_path in meta_paths:
        logger.debug(f"Loading custom interface resource from {meta_path}")

        with open(meta_path, 'r', encoding='utf-8') as f:
            metadata.extend(json.load(f))
    return metadata

def _register_publisher_interface(
        metadata: dict) -> FunctionConfigEntry:
    displaystyle = FunctionConfigDisplaystyle(
        visible=metadata.get('displaystyle', {}).get('visible', False),
        published=metadata.get('displaystyle', {}).get('published', False)
    )
    return FunctionConfigEntry(
        tags=metadata['tags'],
        type=metadata['type'],
        ros2type=metadata['ros2type'],
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=displaystyle,
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10),
        periodic=metadata.get('periodic', None)
    )


def _register_callable_interface( 
        callback: Callable, 
        metadata: dict) -> FunctionConfigEntry:
    """Registers a callable interface for the entity."""
    displaystyle = FunctionConfigDisplaystyle(
        visible=metadata.get('displaystyle', {}).get('visible', False),
        published=metadata.get('displaystyle', {}).get('published', False)
    )
    return FunctionConfigEntry(
        tags=metadata['tags'],
        type=metadata['type'],
        ros2type=metadata['ros2type'],
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=displaystyle,
        params=metadata['params'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10),
        callback=callback
    )

def _register_job_interface(
        metadata: dict,
        callbacks: dict[str, Callable]) -> FunctionConfigEntry:
    """Registers a job interface for the entity."""
    displaystyle = FunctionConfigDisplaystyle(
        visible=metadata.get('displaystyle', {}).get('visible', False),
        published=metadata.get('displaystyle', {}).get('published', False)
    )
    return FunctionConfigEntry(
        tags=metadata['tags'],
        type=metadata['type'],
        ros2type=metadata['ros2type'],
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=displaystyle,
        params=metadata['params'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10)
    )