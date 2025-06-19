import rclpy
import uuid
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from datetime import datetime

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
from vos_base.defaults.entries import ModuleEntry
from vos_base.defaults.entries import StateEntry

class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
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
        rclpy.init()
        me = ModuleEntry(
            uuid= uuid.uuid4(),
            name='vos_module_template',
            template="Template",
            description='A template module for VOS',
            version='0.1.0',
        )

        se = StateEntry(
            previous='initial',
            current='running',
            module_uuid=me.uuid,
            module_name=me.name,
            timestamp=datetime.now(),
            type=StateFeed
        )

        entity = VOSEntity(
            state_entry=se,
            module_config=me
        )
    
        minimal_publisher = MinimalPublisher()

        rclpy.spin(minimal_publisher)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()