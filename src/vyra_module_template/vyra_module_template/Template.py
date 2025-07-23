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
        super().__init__('template')
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

def main():
    try:
        entity = Template()
        rclpy.spin(entity)

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