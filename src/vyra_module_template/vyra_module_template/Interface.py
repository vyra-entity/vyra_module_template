from pathlib import Path
import json

from ament_index_python.packages import get_package_share_directory

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import FunctionConfigEntry
from vyra_base.defaults.entries import FunctionConfigBaseTypes

from vyra_base.helper.logger import Logger
from typing import Callable
from ._Base_ import load_resource

def _load_metadata(package_name: str, resource_folder: Path) -> list[dict]:
    """Loads metadata from a specified package and resource."""
    package_path = get_package_share_directory(package_name)
    resource_path = Path(package_path) / resource_folder
    meta_paths: list[Path] = list(resource_path.rglob("*.json"))

    metadata: list[dict] = []

    for meta_path in meta_paths:
        Logger.log(f"Loading resource from {meta_path}")

        with open(meta_path, 'r', encoding='utf-8') as f:
            metadata.extend(json.load(f))
    return metadata

async def auto_register_interfaces(entity: VyraEntity, callback_list: list[Callable]) -> None:
    """Automatically registers interfaces for the entity. The list of callbacks must
    contain all functions that are defined in the interface metadata.
    Args:
        entity (VyraEntity): The entity to register interfaces for.
        callback_list (list[Callable]): List of callbacks to register.
    """

    interface_metadata = _load_metadata('vyra_module_interfaces', Path('config'))

    interface_functions: list[FunctionConfigEntry] = []

    for metadata in interface_metadata:
        match metadata['type']:
            case FunctionConfigBaseTypes.callable.value:
                callback = next(
                    (c for c in callback_list if c.__name__ == metadata['functionname']), None
                )
                if callback is None:
                    Logger.error(
                        f"Callback for function {metadata['functionname']} not found. "
                        "Interface will not be created. Please check the configuration files" \
                        "in vyra_module_interfaces/config."
                    )
                    continue

                interface_functions.append(_register_callable_interface(
                    callback=callback,
                    metadata=metadata
                ))

            case FunctionConfigBaseTypes.speaker.value:
                interface_functions.append(_register_speaker_interface(
                    metadata=metadata
                ))

            case FunctionConfigBaseTypes.job.value:
                interface_functions.append(_register_job_interface(
                    metadata=metadata,
                    callbacks={}
                ))

    await entity.set_interfaces(interface_functions)
    return 

def _register_speaker_interface(
        metadata: dict) -> FunctionConfigEntry:
    return FunctionConfigEntry(
        tags=metadata['tags'],
        type=metadata['type'],
        ros2type=metadata['ros2type'],
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=metadata['displaystyle'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10),
        periodic=metadata.get('periodic', None)
    )


def _register_callable_interface( 
        callback: Callable, 
        metadata: dict) -> FunctionConfigEntry:
    """Registers a callable interface for the entity."""
    return FunctionConfigEntry(
        tags=metadata['tags'],
        type=metadata['type'],
        ros2type=metadata['ros2type'],
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=metadata['displaystyle'],
        params=metadata['params'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10),
        callback=callback
    )

def _register_job_interface(
        metadata: dict,
        callbacks: dict[str, Callable]) -> FunctionConfigEntry:
    """Registers a job interface for the entity."""
    return FunctionConfigEntry(
        tags=metadata['tags'],
        type=metadata['type'],
        ros2type=metadata['ros2type'],
        functionname=metadata['functionname'],
        displayname=metadata['displayname'],
        description=metadata['description'],
        displaystyle=metadata['displaystyle'],
        params=metadata['params'],
        returns=metadata['returns'],
        qosprofile=metadata.get('qosprofile', 10)
    )