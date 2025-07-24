import asyncio
import rclpy

from rclpy.executors import ExternalShutdownException

from vyra_module_template import _Base_
from vyra_module_template.application import application
from vyra_base.helper.logger import Logger


async def runner():   
    try:
        rclpy.init()

        entity = await _Base_.build_base()

        async_loop = asyncio.get_event_loop()

        application.main(async_loop, entity)

        rclpy.spin(entity.node)

    except (KeyboardInterrupt, ExternalShutdownException):
        pass

    finally:
        if hasattr(locals, 'entity'):
            Logger.log('Shutting down ROS 2 node...')
            if hasattr(entity, 'node') and entity.node is not None:
                # Ensure the node is destroyed properly
                await entity.node.destroy_async()
            else:
                Logger.log('No ROS 2 node to destroy.')

        if rclpy.ok():
            Logger.log('ROS 2 node destroyed.')
            rclpy.shutdown()
        else:
            Logger.log('ROS 2 node was not running, nothing to destroy.')


def vyra_startup():
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
    vyra_startup()