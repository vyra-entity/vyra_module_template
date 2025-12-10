import logging
import sys
from datetime import datetime
from pathlib import Path
from typing import Any, Optional

from ament_index_python.packages import get_package_share_directory

from std_msgs.msg import String # pyright: ignore[reportMissingImports]

# msg
from vyra_module_interfaces.msg import VBASEErrorFeed # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASEVolatileList # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASEStateFeed # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASENewsFeed # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASEUpdateParamEvent # pyright: ignore[reportAttributeAccessIssue]

from vyra_module_interfaces.msg import VBASEVolatileList # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASEVolatileSet # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASEVolatileHash # pyright: ignore[reportAttributeAccessIssue]
from vyra_module_interfaces.msg import VBASEVolatileString # pyright: ignore[reportAttributeAccessIssue]
# srv
# add base services here
# action
# add base actions here

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import (
    FunctionConfigEntry,
    FunctionConfigDisplaystyle,
    FunctionConfigBaseTypes,
    ModuleEntry,
    StateEntry,
    NewsEntry,
    ErrorEntry,
)
from vyra_base.helper.file_reader import FileReader
from vyra_base.helper.file_writer import FileWriter

if __package__:
    PACKAGE_NAME = __package__.split('.')[0]
else:
    sys.exit("Package name not found. Please run this script as part of a package.")


logger = logging.getLogger(__name__)

async def load_resource(package_name: str, resource_name: Path) -> Any:
    package_path = get_package_share_directory(package_name)
    resource_path: Path = Path(package_path) / resource_name

    if not resource_path.exists():
        raise FileNotFoundError(
            f"Resource {resource_name} not found in package {package_name}")
    
    logger.debug(f"Loading resource from {resource_path}")


    match resource_name.suffix:
        case '.ini':
            return await FileReader.open_ini_file(resource_path)
        case '.json':
            return await FileReader.open_json_file(resource_path)
        case '.yaml' | '.yml':
            return await FileReader.open_yaml_file(resource_path)
        case _:
            fail_msg = (
                f"Unsupported file type: {resource_name.suffix}. "
                "Supported types are .ini, .json, .yaml/.yml"
            )
            logger.error(fail_msg)
            raise ValueError(fail_msg)

async def _create_base_interfaces() -> list[FunctionConfigEntry]:
    interface_metadata: list = []

    base_interfaces: list[str] = [
        'vyra_core_meta.json',
        'vyra_com_meta.json',
        'vyra_security_meta.json'
    ]

    for interface_file in base_interfaces:
        if isinstance(interface_file, str):
            interface_metadata.extend(await load_resource(
                'vyra_module_interfaces',
                Path('config', interface_file))
            )

    interface_functions: list[FunctionConfigEntry] = []

    for metadata in interface_metadata:
        try:
            if metadata['type'] == FunctionConfigBaseTypes.callable.value:
                ros2_type: str = metadata['filetype'].split('/')[-1]
                ros2_type = ros2_type.split('.')[0]

                metadata['ros2type'] = getattr(
                    sys.modules['vyra_module_interfaces.srv'], ros2_type)

                displaystyle = FunctionConfigDisplaystyle(
                    visible=metadata.get('displaystyle', {}).get('visible', False),
                    published=metadata.get('displaystyle', {}).get('published', False)
                )

                interface_functions.append(
                    FunctionConfigEntry(
                        tags=metadata['tags'],
                        type=metadata['type'],
                        ros2type=metadata['ros2type'],
                        functionname=metadata['functionname'],
                        displayname=metadata['displayname'],
                        description=metadata['description'],
                        displaystyle=displaystyle,
                        params=metadata['params'],
                        returns=metadata['returns'],
                        qosprofile=metadata.get('qosprofile', 10),
                        callback=None,
                        periodic=None
                    )
                )
        except KeyError as e:
            logger.error(
                f"Missing key <{e}> in interface data <{metadata}>."
                "Interface will not be created.")
            raise
        except TypeError as e:
            logger.error(
                f"Type error in interface data <{metadata}>: {e}."
                "Interface will not be created.")
            raise

    return interface_functions

async def _load_storage_config() -> dict[str, Any]:
    """
    Load the storage configuration from the resource/storage_config.ini file.
    Returns:
        dict: The storage configuration.
    Raises:
        FileNotFoundError: If the storage_config.ini file is not found.
        ValueError: If the storage_config.ini file is not valid or does not 
        contain the required sections.
    """
    return await load_resource(
        PACKAGE_NAME,
        Path('resource', 'storage_config.ini')
    )

async def _load_module_config() -> dict[str, Any]:
    """
    Load the module configuration from the pyproject.toml file.
    Returns:
        dict: The module configuration.
    Raises:
        FileNotFoundError: If the pyproject.toml file is not found.
        ValueError: If the pyproject.toml file is not valid or does not contain 
        the required sections.
    """
    return await load_resource(
        PACKAGE_NAME,
        Path('resource', 'module_config.yaml')
    )

async def _load_module_data() -> Optional[dict[str, Any]]:
    """
    Load the module data from the resource/module_data.yaml file.
    Returns:
        dict: The module data.
    Raises:
        FileNotFoundError: If the module_data.yaml file is not found.
        ValueError: If the module_data.yaml file is not valid or does not contain
        the required sections.
    """
    pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))
    data_path: Path = pkg_dir.parents[3] / ".module" / "module_data.yaml"

    try:
        module_data: Optional[dict[str, Any]] = await FileReader.open_yaml_file(data_path)
    except (FileNotFoundError) as e:
        # Create .module directory if it does not exist
        logger.error(f"Module data file not found: {e}. Creating new module_data.yaml.")
        if not data_path.parent.exists():
            data_path.parent.mkdir(parents=True)
        return None
    
    return module_data

async def _write_module_data(data: dict[str, Any]) -> None:
    """
    Write the module data to the resource/module_data.yaml file.
    Args:
        data (dict): The module data to write.
    Raises:
        FileNotFoundError: If the resource directory does not exist.
        ValueError: If the data is not valid or does not contain the required sections.
    """
    pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))

    data_path: Path = pkg_dir.parents[3] / ".module" / "module_data.yaml"

    await FileWriter.write_yaml_file(data_path, data)

async def _load_project_settings() -> dict[str, Any]:
    pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))
    pyproject_path: Path = pkg_dir.parents[3] / "pyproject.toml"
    module_settings: Optional[dict[str, Any]] = await FileReader.open_toml_file(pyproject_path)

    if not module_settings:
        raise ValueError("Module settings not found in pyproject.toml")

    project_settings = module_settings['tool']['vyra']
    project_settings['version'] = module_settings['tool']['poetry']['version']

    if not project_settings:
        raise ValueError("Project settings not found in pyproject.toml")
    
    return project_settings

async def build_entity(project_settings):
    module_data: Optional[dict] = await _load_module_data()
    needed_fields: list[str] = ['uuid', 'name', 'template', 'description', 'version']

    if not module_data or module_data == {}:
        logger.info(
            "Creating new module entry from project settings. "
            "Module data is empty."
        )

        me = ModuleEntry(
            uuid= ModuleEntry.gen_uuid(),
            name=project_settings['module_name'],
            template=project_settings['module_template'],
            description=project_settings['module_description'],
            version=project_settings['version'],
        )
    elif not all(field in module_data for field in needed_fields):
        missing_field: list[str] = [
            field for field in needed_fields if field not in module_data]
        
        logger.info(
            "Module data is incomplete. "
            f"Missing fields: {missing_field}. Will be recovered "
            f"from project settings."
        )

        me = ModuleEntry(
            uuid=module_data.get('uuid', ModuleEntry.gen_uuid()),
            name=module_data.get('name', project_settings['name']),
            template=module_data.get('template', project_settings['template']),
            description=module_data.get('description', project_settings['description']),
            version=module_data.get('version', project_settings['version']),
        )

        logger.info(
            "Module data recovered from project settings."
        )
    else:
        logger.info(
            "Module data complete. "
            "Using project settings to create a new module entry."
        )

        if module_data['uuid'] in [None, "", "null"]:
            logger.info(
                "Module UUID is empty. Generating new UUID."
            )

            module_data['uuid'] = ModuleEntry.gen_uuid()

        me = ModuleEntry(
            uuid=module_data['uuid'],
            name=module_data['name'],
            template=module_data['template'],
            description=module_data['description'],
            version=module_data['version'],
        )
    
    await _write_module_data(me.to_dict())
    
    logger.info(f"Module_data: {me.to_dict()}")

    se = StateEntry(
        previous='initial',
        trigger='',
        current='running',
        module_id=me.uuid,
        module_name=me.name,
        timestamp=datetime.now(),
        _type=VBASEStateFeed
    )

    ne = NewsEntry(
        module_id=me.uuid,
        module_name=me.name,
        _type=VBASENewsFeed
    )

    ee = ErrorEntry(
        module_id=me.uuid,
        module_name=me.name,
        _type=VBASEErrorFeed
    )

    module_config = await _load_module_config()
    storage_config = await _load_storage_config()

    entity = VyraEntity(
        state_entry=se,
        module_entry=me,
        news_entry=ne,
        error_entry=ee,
        module_config=module_config
    )

    transient_base_types: dict[str, Any] = {
        'VolatileString': VBASEVolatileString,
        'VolatileHash': VBASEVolatileHash,
        'VolatileList': VBASEVolatileList,
        'VolatileSet': VBASEVolatileSet
    }

    parameter_types: dict[str, Any] = {
        'UpdateParamEvent': VBASEUpdateParamEvent
    }

    await entity.setup_storage(
        storage_config, 
        transient_base_types, 
        parameter_types)

    return entity


async def create_db_storage(entity: VyraEntity) -> None:
    """Create database storage for the entity. The configuration is loaded from this
    ros2 package. Check for adoptions in the
    <your_package>/config/storage_config.ini file.
    Arguments:
        entity (VyraEntity): The entity for which the database storage should be created.
    Raises:
        FileNotFoundError: If the storage_config.ini file is not found in this package.
        ValueError: If the storage_config.ini file is not valid or does not contain the required sections.
    Returns:
        None: The function does not return anything, but sets the storage in the entity.
    """

    from vyra_base.storage.db_access import DbAccess

    storage_config: dict[str, Any] = await _load_storage_config()

    db_access = DbAccess(
        module_name=entity.module_entry.name,
        db_config=storage_config
    )

    await db_access.create_all_tables()

    entity.register_storage(db_access)
    logger.debug("Storage access created and set in entity")

async def build_base():
    project_settings: dict[str, Any] = await _load_project_settings()
    entity = await build_entity(project_settings)
    await entity.set_interfaces(await _create_base_interfaces())
    
    await create_db_storage(entity)

    logger.debug("Created V.Y.R.A. Entity with state entry and module config")

    return entity