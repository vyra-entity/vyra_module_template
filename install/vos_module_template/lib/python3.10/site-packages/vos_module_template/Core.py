import asyncio
from email.mime import base
import time
import sys
import rclpy
import uuid
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

import json

from typing import Any

from datetime import datetime

from pathlib import Path

# msg
from vos_module_interfaces.msg import ErrorFeed
from vos_module_interfaces.msg import LoggerStream
from vos_module_interfaces.msg import NewsFeed
from vos_module_interfaces.msg import StateFeed

#srv
from vos_module_interfaces.srv import GetCapabilities
from vos_module_interfaces.srv import GetLogs
from vos_module_interfaces.srv import HealthCheck
from vos_module_interfaces.srv import TriggerTransition

#action
from vos_module_interfaces.action import InitiateUpdate

from std_msgs.msg import String

from vos_base.core.vos_entity import VOSEntity
from vos_base.defaults.entries import FunctionConfigEntry
from vos_base.defaults.entries import FunctionConfigBaseTypes


from vos_base.defaults.entries import ModuleEntry
from vos_base.defaults.entries import StateEntry

from vos_base.helper.file_reader import FileReader

from ament_index_python.packages import get_package_share_directory


def load_resource(package_name: str, resource_name: Path) -> list[dict[str, Any]]:
    package_path = get_package_share_directory(package_name)
    resource_path = Path(package_path) / resource_name

    if not resource_path.exists():
        raise FileNotFoundError(f"Resource {resource_name} not found in package {package_name}")
    
    with open(resource_path, 'r', encoding='utf-8') as f:
        config = json.load(f)

    return config


async def runner():   
    try:
        rclpy.init()

        base_metadata: list = load_resource(
            'vos_module_interfaces',
            Path('config', 'base_metadata.config'))

        pkg_dir = Path(get_package_share_directory('vos_module_template'))
        pyproject_path: Path = pkg_dir.parents[3] / "pyproject.toml"
        module_settings: dict[str, Any] = await FileReader.open_toml_file(pyproject_path)

        project_settings = module_settings['tool']['vos']
        project_settings['version'] = module_settings['tool']['poetry']['version']

        if not project_settings:
            raise ValueError("Project settings not found in pyproject.toml")

        me = ModuleEntry(
            uuid= uuid.uuid4(),
            name=project_settings['module_name'],
            template=project_settings['module_template'],
            description=project_settings['module_description'],
            version=project_settings['version'],
        )

        se = StateEntry(
            previous='initial',
            current='running',
            module_uuid=me.uuid,
            module_name=me.name,
            timestamp=datetime.now(),
            type=StateFeed
        )

        print("Creating VOSEntity with state entry and module config...")

        entity = VOSEntity(
            state_entry=se,
            module_config=me
        )

        base_functions = []

        for metadata in base_metadata:
            if metadata['type'] == FunctionConfigBaseTypes.callable.value:
                ros2_type: str = metadata['filetype'].split('/')[-1]
                ros2_type = ros2_type.split('.')[0]

                metadata['ros2type'] = getattr(
                    sys.modules['vos_module_interfaces.srv'], ros2_type)

                base_functions.append(
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

        await entity.add_interface(base_functions)

        rclpy.spin(entity.ros2_node)
        print("Node is running...")

    except (KeyboardInterrupt, ExternalShutdownException):
        pass

    finally:
        rclpy.shutdown()
        print("Node has been shutdown successfully.")


def main():
    try:
        asyncio.run(runner())
        asyncio.get_event_loop().close()
        print('Exit')
    except KeyboardInterrupt:
        pass
    except RuntimeError:
        print('Closing event loop')
    finally:
        print('Finally exit')
        time.sleep(1)

if __name__ == '__main__':
    main()