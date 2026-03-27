import json
from .logging_config import get_logger
import os
import sys
from pathlib import Path

from lark import logger

from typing import Any, TYPE_CHECKING
from typing import Callable


VYRA_SLIM = os.getenv('VYRA_SLIM', 'false').lower() == 'true'
if not VYRA_SLIM:
    from ament_index_python.packages import get_package_share_directory  # pyright: ignore[reportMissingImports]

from vyra_base.defaults.entries import FunctionConfigEntry
from vyra_base.defaults.entries import FunctionConfigDisplaystyle
from vyra_base.defaults.entries import FunctionConfigBaseTypes
from vyra_base.helper.error_handler import ErrorTraceback

if TYPE_CHECKING:
    from vyra_base.core.entity import VyraEntity
else:
    VyraEntity = Any


logger = get_logger(__name__)


@ErrorTraceback.w_check_error_exist
async def auto_register_interfaces(
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
        callback_list = _autoload_all_remote_service_from_parent(callback_parent)
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
            metadata: dict = config_list[0]
        else:
            metadata: dict = config_list[0]

        # Handle filetype as either a string or a list
        filetype_raw = metadata['filetype']
        if isinstance(filetype_raw, list):
            # New format: list of filetypes, e.g. ["VBASEGetInterfaceList.proto"]
            # Use _base_.py style: load ROS2 types for .srv / .msg / .action, pass through others
            ifaces = []
            for iface_type in filetype_raw:
                filename, ext = iface_type.split('.') if '.' in iface_type else (iface_type, '')
                if ext in ['msg', 'srv', 'action']:
                    try:
                        iface_module = sys.modules[f'{module_name}_interfaces.{ext}']
                        iface_class = getattr(iface_module, filename)
                        ifaces.append(iface_class)
                    except (KeyError, AttributeError) as e:
                        logger.warning(f"Could not load ROS2 type {iface_type}: {e}")
                        ifaces.append(iface_type)  # keep as string
                else:
                    ifaces.append(iface_type)  # proto / custom type, keep as string
            metadata['interfacetypes'] = ifaces
        else:
            # Old format: single string, e.g. "{{ module_name }}_interfaces/srv/Foo.srv"
            logger.warning(f"Old format not supported for filetype: {filetype_raw}. Please update to list format in your config.")
            raise ValueError(f"Old format not supported for filetype: {filetype_raw}. Please update to list format in your config.")

        match metadata['type']:
            case FunctionConfigBaseTypes.service.value:
                interface_functions.append(_register_service_interface(
                    callback=callback,
                    metadata=metadata
                )) 

            case FunctionConfigBaseTypes.action.value:
                interface_functions.append(_register_action_interface(
                    metadata=metadata,
                    callbacks={}
                ))

    logger.info(f"Registering {len(interface_functions)} interfaces for entity")
    
    # NEW: Bind decorated callbacks from callback_parent (for multi-callback ActionServers)
    if callback_parent:
        logger.debug("Binding decorated callbacks from component...")
        binding_results = entity.bind_interface_callbacks(
            component=callback_parent,
            settings=interface_functions
        )
        logger.info(
            f"Callback binding complete: "
            f"{sum(binding_results.values())}/{len(binding_results)} successful"
        )
    
    await entity.set_interfaces(interface_functions)
    return

def _autoload_all_remote_service_from_parent(callback_parent: object) -> list:
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
                logger.debug(f"    has _vyra_remote_server: {hasattr(attr, '_vyra_remote_server')}")
                logger.debug(f"    _vyra_remote_server value: {getattr(attr, '_vyra_remote_server', 'NOT FOUND')}")
                
                # Try __func__ if it's a bound method
                if hasattr(attr, "__func__"):
                    logger.debug(f"    __func__._vyra_remote_server: {getattr(attr.__func__, '_vyra_remote_server', 'NOT FOUND')}")
                
                # Try class method
                class_method = getattr(callback_parent.__class__, "get_interface_list", None)
                if class_method:
                    logger.debug(f"    class method._vyra_remote_server: {getattr(class_method, '_vyra_remote_server', 'NOT FOUND')}")
            
            # Check if it's callable and has _vyra_remote_server marker (set by @remote_service decorator)
            if callable(attr) and hasattr(attr, "_vyra_remote_server"):
                logger.debug(f"  Found remote_service on instance: {attr_name}")
                callable_list.append(attr)
                continue
            
            # If not found on instance, try the class
            # This handles cases where decorator is on class method
            if hasattr(callback_parent.__class__, attr_name):
                class_attr = getattr(callback_parent.__class__, attr_name)
                if callable(class_attr) and hasattr(class_attr, "_vyra_remote_server"):
                    logger.debug(f"  Found remote_service on class: {attr_name}")
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
    """Loads metadata from a specified package and resource.

    In SLIM mode the Python source tree is used; in FULL mode the ROS2 ament
    package share directory is queried.
    """
    if VYRA_SLIM:
        resource_path = Path(__file__).parent.parent.parent.parent / "src" / package_name / resource_folder
    else:
        resource_path = Path(get_package_share_directory(package_name)) / resource_folder
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
        interfacetypes=metadata.get('interfacetypes', None),
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=displaystyle,
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10),
        periodic=metadata.get('periodic', None)
    )


def _register_service_interface( 
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
        interfacetypes=metadata.get('interfacetypes', None),
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=displaystyle,
        params=metadata['params'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10),
        callbacks={'response': callback} if callback is not None else None
    )

def _register_action_interface(
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
        interfacetypes=metadata.get('interfacetypes', None),
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=displaystyle,
        params=metadata['params'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10)
    )