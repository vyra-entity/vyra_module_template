import asyncio
import json
import sys
import time
import uuid
from datetime import datetime
from pathlib import Path
from typing import Any

import rclpy
from ament_index_python.packages import get_package_share_directory
from std_msgs.msg import String # pyright: ignore[reportAttributeAccessIssue]

# msg
from vyra_base import storage
from vyra_module_interfaces.msg import ErrorFeed # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import NewsFeed # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import StateFeed # pyright: ignore[reportAttributeAccessIssue]

from vyra_module_interfaces.msg import VolatileList # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VolatileSet # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VolatileHash # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VolatileString # pyright: ignore[reportAttributeAccessIssue]
# srv
from vyra_module_interfaces.srv import GetCapabilities # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.srv import GetLogs # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.srv import HealthCheck # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.srv import TriggerTransition # pyright: ignore[reportAttributeAccessIssue]

# action
from vyra_module_interfaces.action import InitiateUpdate # pyright: ignore[reportAttributeAccessIssue]

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import (
    FunctionConfigEntry,
    FunctionConfigBaseTypes,
    ModuleEntry,
    StateEntry,
    NewsEntry,
    ErrorEntry,
)
from vyra_base.helper.file_reader import FileReader
from vyra_base.helper.logger import Logger

if __package__:
    PACKAGE_NAME = __package__.split('.')[0]
else:
    sys.exit("Package name not found. Please run this script as part of a package.")


def _load_resource(package_name: str, resource_name: Path) -> Any:
    package_path = get_package_share_directory(package_name)
    resource_path = Path(package_path) / resource_name

    print(PACKAGE_NAME, package_path, resource_name, resource_path)

    if not resource_path.exists():
        raise FileNotFoundError(
            f"Resource {resource_name} not found in package {package_name}")
    
    Logger.log(f"Loading resource from {resource_path}")

    with open(resource_path, 'r', encoding='utf-8') as f:
        match resource_name.suffix:
            case '.ini':
                from configparser import ConfigParser
                parser = ConfigParser()
                parser.read_file(f)
                # Convert ConfigParser object to a dictionary
                config = {
                    section: dict(parser.items(section)) for section in parser.sections()}
            case '.json':
                import json
                config = json.load(f)
            case '.yaml' | '.yml':
                import yaml
                config = yaml.safe_load(f)
            case _:
                fail_msg = (
                    f"Unsupported file type: {resource_name.suffix}. "
                    "Supported types are .ini, .json, .yaml/.yml"
                )
                Logger.error(fail_msg)
                raise ValueError(fail_msg)
    return config

def _create_interfaces(interface_files: list[str]=[]) -> list[FunctionConfigEntry]:
    interface_metadata: list = _load_resource(
            'vyra_module_interfaces',
            Path('config', 'base_metadata.json'))
    
    for custom_interface in interface_files:
        if isinstance(custom_interface, str):
            interface_metadata.append(_load_resource(
                'vyra_module_interfaces',
                Path('config', custom_interface))
            )

    interface_functions = []

    for metadata in interface_metadata:
        try:
            if metadata['type'] == FunctionConfigBaseTypes.callable.value:
                ros2_type: str = metadata['filetype'].split('/')[-1]
                ros2_type = ros2_type.split('.')[0]

                metadata['ros2type'] = getattr(
                    sys.modules['vyra_module_interfaces.srv'], ros2_type)

                interface_functions.append(
                    FunctionConfigEntry(
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
                        callback=None,
                        periodic=None
                    )
                )
        except KeyError as e:
            Logger.error(
                f"Missing key <{e}> in interface data <{metadata}>."
                "Interface will not be created.")
            continue

    return interface_functions

def _load_storage_config() -> dict[str, Any]:
    """
    Load the storage configuration from the resource/storage_config.ini file.
    Returns:
        dict: The storage configuration.
    Raises:
        FileNotFoundError: If the storage_config.ini file is not found.
        ValueError: If the storage_config.ini file is not valid or does not contain the required sections.
    """
    return _load_resource(
        PACKAGE_NAME,
        Path('resource', 'storage_config.ini')
    )

def _load_module_config() -> dict[str, Any]:
    """
    Load the module configuration from the pyproject.toml file.
    Returns:
        dict: The module configuration.
    Raises:
        FileNotFoundError: If the pyproject.toml file is not found.
        ValueError: If the pyproject.toml file is not valid or does not contain the required sections.
    """
    return _load_resource(
        PACKAGE_NAME,
        Path('resource', 'module_config.yaml')
    )


async def _load_project_settings() -> dict[str, Any]:
    pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))
    pyproject_path: Path = pkg_dir.parents[3] / "pyproject.toml"
    module_settings: dict[str, Any] = await FileReader.open_toml_file(pyproject_path)

    project_settings = module_settings['tool']['vyra']
    project_settings['version'] = module_settings['tool']['poetry']['version']

    if not project_settings:
        raise ValueError("Project settings not found in pyproject.toml")
    
    return project_settings

async def build_entity(project_settings):
    me = ModuleEntry(
        uuid= uuid.uuid4(),
        name=project_settings['module_name'],
        template=project_settings['module_template'],
        description=project_settings['module_description'],
        version=project_settings['version'],
    )

    se = StateEntry(
        previous='initial',
        trigger='',
        current='running',
        module_id=me.uuid,
        module_name=me.name,
        timestamp=datetime.now(),
        _type=StateFeed
    )

    ne = NewsEntry(
        module_id=me.uuid,
        module_name=me.name,
        _type=NewsFeed
    )

    ee = ErrorEntry(
        module_id=me.uuid,
        module_name=me.name,
        _type=ErrorFeed
    )

    module_config = _load_module_config()
    storage_config = _load_storage_config()

    entity = VyraEntity(
        state_entry=se,
        module_entry=me,
        news_entry=ne,
        error_entry=ee,
        module_config=module_config
    )

    transient_base_types: dict[str, Any] = {
        'VolatileString': VolatileString,
        'VolatileHash': VolatileHash,
        'VolatileList': VolatileList,
        'VolatileSet': VolatileSet
    }

    await entity.setup_storage(storage_config, transient_base_types)

    return entity


async def create_db_storage(entity: VyraEntity) -> None:
    """Create database storage for the entity. The configuration is loaded from this
    ros2 package. Check for adoptions in the
    <your_package>/config/storage_config.ini file.
    Arguments:
        entity (VyraEntity): The entity for which the database storage should be created.
    Raises:
        FileNotFoundError: If the storage_config.ini file is not found in this package.
        ValueError: If the storage_config.ini file is not valid or does not contain the required sections.
    Returns:
        None: The function does not return anything, but sets the storage in the entity.
    """

    from vyra_base.storage.db_access import DbAccess
    from vyra_base.storage.tb_base import Base as DbBase

    storage_config: dict[str, Any] = _load_storage_config()

    db_access = DbAccess(
        module_name=entity.module_entry.name,
        db_config=storage_config
    )

    await db_access.create_all_tables()

    entity.register_storage(db_access)
    Logger.log("Storage access created and set in entity")

async def build_base():
    project_settings: dict[str, Any] = await _load_project_settings()
    entity = await build_entity(project_settings)
    await entity.add_interface(_create_interfaces())
    
    await create_db_storage(entity)

    Logger.log("Created V.Y.R.A. Entity with state entry and module config")

    return entity