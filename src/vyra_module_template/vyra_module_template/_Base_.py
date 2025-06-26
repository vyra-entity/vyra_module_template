import asyncio
import json
import sys
import time
import uuid
from datetime import datetime
from pathlib import Path
from typing import Any

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from ament_index_python.packages import get_package_share_directory

from std_msgs.msg import String

# msg
from vyra_module_interfaces.msg import ErrorFeed
from vyra_module_interfaces.msg import NewsFeed
from vyra_module_interfaces.msg import StateFeed

# srv
from vyra_module_interfaces.srv import GetCapabilities
from vyra_module_interfaces.srv import GetLogs
from vyra_module_interfaces.srv import HealthCheck
from vyra_module_interfaces.srv import TriggerTransition

# action
from vyra_module_interfaces.action import InitiateUpdate

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


def _load_resource(package_name: str, resource_name: Path) -> Any:
    package_path = get_package_share_directory(package_name)
    resource_path = Path(package_path) / resource_name

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

async def _load_project_settings() -> dict[str, Any]:
    pkg_dir = Path(get_package_share_directory('vyra_module_template'))
    pyproject_path: Path = pkg_dir.parents[3] / "pyproject.toml"
    module_settings: dict[str, Any] = await FileReader.open_toml_file(pyproject_path)

    project_settings = module_settings['tool']['vyra']
    project_settings['version'] = module_settings['tool']['poetry']['version']

    if not project_settings:
        raise ValueError("Project settings not found in pyproject.toml")
    
    return project_settings

def build_entity(project_settings):
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

    return VyraEntity(
        state_entry=se,
        module_config=me,
        news_entry=ne,
        error_entry=ee
    )

async def create_db_storage(entity: VyraEntity) -> None:
    """Create database storage for the entity. The configuration is loaded from the
    ros2 vyra_module_interfaces package. Check for adoptions in the
    vyra_module_interfaces/config/db_config.ini file.
    Arguments:
        entity (VyraEntity): The entity for which the database storage should be created.
    Raises:
        FileNotFoundError: If the db_config.ini file is not found in the vyra_module_interfaces package.
        ValueError: If the db_config.ini file is not valid or does not contain the required sections.
    Returns:
        None: The function does not return anything, but sets the storage in the entity.
    """

    from vyra_base.storage.db_access import DbAccess
    from vyra_base.storage.tb_base import Base as DbBase

    db_config: dict = _load_resource(
            'vyra_module_interfaces',
            Path('config', 'db_config.ini'))

    db_access = DbAccess(
        module_name=entity.module_config.name,
        db_config= db_config
    )

    await db_access.create_all_tables()

    entity.register_storage(db_access)
    Logger.log("Storage access created and set in entity")

async def build_base():
    project_settings: dict[str, Any] = await _load_project_settings()
    entity = build_entity(project_settings)
    await entity.add_interface(_create_interfaces())
    
    await create_db_storage(entity)

    Logger.log("Created V.Y.R.A. Entity with state entry and module config")

    return entity