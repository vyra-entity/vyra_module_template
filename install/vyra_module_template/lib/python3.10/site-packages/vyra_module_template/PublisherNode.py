import rclpy
import uuid
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from datetime import datetime

# msg
from vyra_module_interfaces.msg import ErrorFeed
from vyra_module_interfaces.msg import LoggerStream
from vyra_module_interfaces.msg import NewsFeed
from vyra_module_interfaces.msg import StateFeed


#srv
from vyra_module_interfaces.srv import GetCapabilities
from vyra_module_interfaces.srv import GetLogs
from vyra_module_interfaces.srv import HealthCheck
from vyra_module_interfaces.srv import TriggerTransition

#action
from vyra_module_interfaces.action import InitiateUpdate

from std_msgs.msg import String

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import ModuleEntry
from vyra_base.defaults.entries import StateEntry

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
            name='vyra_module_template',
            template="Template",
            description='A template module for V.Y.R.A.',
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

        entity = VyraEntity(
            state_entry=se,
            module_config=me
        )
    
        minimal_publisher = MinimalPublisher()

        rclpy.spin(minimal_publisher)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()