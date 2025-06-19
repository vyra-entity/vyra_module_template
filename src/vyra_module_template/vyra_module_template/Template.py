import asyncio
import time
import rclpy
import uuid
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node



from typing import Any

from datetime import datetime

from pathlib import Path

from ament_index_python.packages import get_package_share_directory


# msg

#srv

#action


from std_msgs.msg import String

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import ModuleEntry
from vyra_base.defaults.entries import StateEntry

from vyra_base.helper.file_reader import FileReader

def load_resource(package_name: str, resource_name: str) -> Path:
    package_path = get_package_share_directory(package_name)
    resource_path = Path(package_path) / resource_name
    if not resource_path.exists():
        raise FileNotFoundError(f"Resource {resource_name} not found in package {package_name}")
    return resource_path


class Template(Node):

    def __init__(self):
        super().__init__('core')
        self.publisher_ = self.create_publisher(String, 'topic', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1


async def runner():   
    try:
        rclpy.init()

        pyproject_path: Path = Path(__file__).parent.parent.parent / "pyproject.toml"
        module_settings: dict[str, Any] = await FileReader.open_toml_file(pyproject_path)

        project_settings = module_settings['tool'].get('vyra', {})
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

        entity = VyraEntity(
            state_entry=se,
            module_config=me
        )
        
        rclpy.spin(minimal_publisher)
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