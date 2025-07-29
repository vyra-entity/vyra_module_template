import asyncio
import rclpy
import signal
import sys

from . import _Base_
from .application import application
from vyra_base.helper.logger import Logger

def handle_sigterm(signum, frame):
    Logger.warn("SIGTERM empfangen, ROS2 wird heruntergefahren...")
    rclpy.shutdown()
    sys.exit(0)

signal.signal(signal.SIGTERM, handle_sigterm)
signal.signal(signal.SIGINT, handle_sigterm)


async def runner():   
    try:
        rclpy.init()

        entity = await _Base_.build_base()

        await application.main(entity)

        if entity.node is None:
            Logger.log('No ROS 2 node created, exiting...')
            return

        while rclpy.ok():
            rclpy.spin_once(entity.node, timeout_sec=0.01)

    except Exception as e:
        Logger.warn(
            f'Exception received: {e}, ' \
            'shutting down ROS 2 node...')

    finally:
        if hasattr(locals, 'entity'):
            Logger.log('Shutting down ROS 2 node...')
            if hasattr(entity, 'node') and entity.node is not None:
                # Ensure the node is destroyed properly
                Logger.log('Destroying ROS 2 node...')
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
        Logger.warn('KeyboardInterrupt received, closing event loop')
    except RuntimeError as e:
        Logger.log(f'RuntimeError: {e}. Closing event loop')
    finally:
        Logger.log('Finally exit module')

if __name__ == '__main__':
    main()