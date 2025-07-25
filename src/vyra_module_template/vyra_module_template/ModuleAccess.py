import asyncio
import rclpy

from rclpy.executors import ExternalShutdownException

from . import _Base_
from .application import application
from vyra_base.helper.logger import Logger


async def runner():   
    try:
        rclpy.init()

        entity = await _Base_.build_base()

        await application.main(entity)

        if entity.node is None:
            Logger.log('No ROS 2 node created, exiting...')
            return

        rclpy.spin(entity.node)

    except (KeyboardInterrupt, ExternalShutdownException):
        pass

    finally:
        if hasattr(locals, 'entity'):
            Logger.log('Shutting down ROS 2 node...')
            if hasattr(entity, 'node') and entity.node is not None:
                # Ensure the node is destroyed properly
                entity.node.destroy_node()
            else:
                Logger.log('No ROS 2 node to destroy.')

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