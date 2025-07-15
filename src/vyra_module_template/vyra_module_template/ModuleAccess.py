import asyncio
import rclpy

from rclpy.executors import ExternalShutdownException

from vyra_module_template import _Base_
from vyra_base.helper.logger import Logger

async def runner():   
    try:
        rclpy.init()

        entity = await _Base_.build_base()

        rclpy.spin(entity.node)

    except (KeyboardInterrupt, ExternalShutdownException):
        pass

    finally:
        if hasattr(locals, 'entity'):
            Logger.log('Shutting down ROS 2 node...')
            entity.ros2_node.destroy_node()

        if rclpy.ok():
            Logger.log('ROS 2 node destroyed.')
            rclpy.shutdown()
        else:
            Logger.log('ROS 2 node was not running, nothing to destroy.')


def main():
    try:
        asyncio.run(runner())
        Logger.log('Exit module')
    except KeyboardInterrupt:
        pass
    except RuntimeError as e:
        Logger.log(f'RuntimeError: {e}. Closing event loop')
    finally:
        Logger.log('Finally exit module')

if __name__ == '__main__':
    main()