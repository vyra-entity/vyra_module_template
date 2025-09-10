import asyncio
import datetime
import json
from vyra_base.helper.logger import Logger
from vyra_base.core.entity import VyraEntity

from .registry import ModuleRegistry
from .permission import PermissionManager
from .minimal_rest import app

from ..taskmanager import TaskManager

from vyra_base.com.datalayer.interface_factory import execute_vyra_callable

from vyra_module_interfaces.srv import VBASEGetInterfaceList # pyright: ignore[reportAttributeAccessIssue] 

def test_vyra_speaker(msg):
    Logger.info(f"Testing VyraSpeaker...: {msg}")
    return

async def main(entity: VyraEntity, task_manager: TaskManager) -> None:
    Logger.info("Starting development webserver...")
    # task_manager.add_task(
    #     app.run,
    #     {
    #         "host": "0.0.0.0", 
    #         "port": 8443, 
    #         "ssl_context": ("webserver.crt", "webserver.key")
    #     }
    # )

    permission = PermissionManager(entity)
    await permission.set_interfaces()

    registry = ModuleRegistry(entity, permission)
    await registry.set_interfaces()

    Logger.debug("Testing VyraCallableExecutor...")
    result = await execute_vyra_callable(
        VBASEGetInterfaceList,
        getattr(entity, "node"),
        {},
        ident_name="get_interface_list",
        timeout=10
        )
    
    for r in result.interface_list:
        Logger.info(f"Result from VBASEGetInterfaceList: {json.loads(r)}")