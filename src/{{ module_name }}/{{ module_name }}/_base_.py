import os
import sys
from datetime import datetime
from pathlib import Path
from typing import Any, Optional

from ament_index_python.packages import get_package_share_directory  # pyright: ignore[reportMissingImports]

from std_msgs.msg import String # pyright: ignore[reportMissingImports]

# msg
from {{ module_name }}_interfaces.msg import VBASEErrorFeed # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASEVolatileList # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASEStateFeed # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASENewsFeed # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASEUpdateParamEvent # pyright: ignore[reportAttributeAccessIssue]

from {{ module_name }}_interfaces.msg import VBASEVolatileList # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASEVolatileSet # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASEVolatileHash # pyright: ignore[reportAttributeAccessIssue]
from {{ module_name }}_interfaces.msg import VBASEVolatileString # pyright: ignore[reportAttributeAccessIssue]
# srv
# add base services here
# action
# add base actions here 

from vyra_base.core.entity import VyraEntity
from vyra_base.defaults.entries import (
    FunctionConfigEntry,
    FunctionConfigDisplaystyle,
    FunctionConfigBaseTypes,
    FunctionConfigTags,
    ModuleEntry,
    StateEntry,
    NewsEntry,
    ErrorEntry,
)
from vyra_base.helper.file_reader import FileReader
from vyra_base.helper.file_writer import FileWriter

# Import logger
from .logging_config import get_logger, log_exception, log_function_call, log_function_result

if __package__:
    PACKAGE_NAME = __package__.split('.')[0]
else:
    sys.exit("Package name not found. Please run this script as part of a package.")


logger = get_logger(__name__)

async def load_resource(package_name: str, resource_name: Path) -> Any:
    """
    Load a resource file from a ROS2 package.
    
    Supports .ini, .json, .yaml, and .yml files.
    
    Args:
        package_name: Name of the ROS2 package
        resource_name: Path to the resource relative to package share directory
        
    Returns:
        Parsed resource content
        
    Raises:
        FileNotFoundError: If resource file doesn't exist
        ValueError: If file type is not supported
    """
    log_function_call(
        logger,
        function="load_resource",
        package=package_name,
        resource=str(resource_name),
        file_type=resource_name.suffix
    )
    
    try:
        package_path = get_package_share_directory(package_name)
        resource_path: Path = Path(package_path) / resource_name

        if not resource_path.exists():
            logger.error(
                "resource_not_found",
                package=package_name,
                resource=str(resource_name),
                full_path=str(resource_path)
            )
            raise FileNotFoundError(
                f"Resource {resource_name} not found in package {package_name}"
            )
        
        logger.debug(
            "loading_resource",
            package=package_name,
            path=str(resource_path),
            file_type=resource_name.suffix
        )

        result = None
        match resource_name.suffix:
            case '.ini':
                result = await FileReader.open_ini_file(resource_path)
            case '.json':
                result = await FileReader.open_json_file(resource_path)
            case '.yaml' | '.yml':
                result = await FileReader.open_yaml_file(resource_path)
            case _:
                logger.error(
                    "unsupported_file_type",
                    file_type=resource_name.suffix,
                    supported_types=['.ini', '.json', '.yaml', '.yml']
                )
                raise ValueError(
                    f"Unsupported file type: {resource_name.suffix}. "
                    "Supported types are .ini, .json, .yaml/.yml"
                )
        
        log_function_result(
            logger,
            success=True,
            function="load_resource",
            package=package_name,
            resource=str(resource_name),
            data_size=len(str(result)) if result else 0
        )
        
        return result
        
    except Exception as e:
        log_exception(
            logger,
            e,
            context={
                "function": "load_resource",
                "package": package_name,
                "resource": str(resource_name)
            }
        )
        raise

async def _create_base_interfaces() -> list[FunctionConfigEntry]:
    """
    Create base interface configurations from metadata files.
    
    Loads interface metadata from JSON files and creates FunctionConfigEntry objects
    for ROS2 services, topics, and actions.
    
    Returns:
        List of configured interface entries
        
    Raises:
        KeyError: If required field is missing in interface metadata
        TypeError: If interface data has type errors
    """
    log_function_call(logger, function="_create_base_interfaces")
    
    interface_metadata: list = []

    base_interfaces: list[str] = [
        'vyra_core.meta.json',
        'vyra_com.meta.json',
        'vyra_security.meta.json'
    ]

    module_name = os.getenv("MODULE_NAME", "")
    logger.debug(
        "loading_base_interfaces",
        module_name=module_name,
        interface_files=base_interfaces
    )

    for interface_file in base_interfaces:
        if isinstance(interface_file, str):
            try:
                logger.debug(
                    "loading_interface_metadata",
                    module=module_name,
                    file=interface_file
                )
                metadata = await load_resource(
                    f'{module_name}_interfaces',
                    Path('config', interface_file)
                )
                interface_metadata.extend(metadata)
                logger.debug(
                    "interface_metadata_loaded",
                    file=interface_file,
                    entries_count=len(metadata)
                )
            except Exception as e:
                log_exception(
                    logger,
                    e,
                    context={
                        "operation": "load_interface_metadata",
                        "file": interface_file
                    }
                )
                raise

    interface_functions: list[FunctionConfigEntry] = []
    
    logger.debug(
        "processing_interface_metadata",
        total_entries=len(interface_metadata)
    )

    for idx, metadata in enumerate(interface_metadata):
        try:
            if metadata['type'] == FunctionConfigBaseTypes.service.value:
                ifaces = []
                logger.debug(
                    "processing_callable_interface",
                    index=idx,
                    function_name=metadata.get('functionname', 'unknown'),
                    filetypes=metadata.get('filetype', [])
                )
                
                for iface_type in metadata['filetype']:
                    filename, filetype = iface_type.split('.')
                
                    if filetype in ['msg', 'srv', 'action']:
                        try:
                            iface_module = sys.modules[f'{module_name}_interfaces.{filetype}']
                            iface_class = getattr(iface_module, filename)
                            ifaces.append(iface_class)
                            logger.debug(
                                "interface_type_loaded",
                                filename=filename,
                                filetype=filetype,
                                class_name=iface_class.__name__
                            )
                        except (KeyError, AttributeError) as e:
                            logger.error(
                                "interface_type_load_failed",
                                filename=filename,
                                filetype=filetype,
                                module=f'{module_name}_interfaces.{filetype}',
                                error=str(e)
                            )
                            raise
                    else:
                        ifaces.append(iface_type)
                        logger.debug(
                            "custom_interface_type",
                            iface_type=iface_type
                        )

                metadata['interfacetypes'] = ifaces
                
                displaystyle = FunctionConfigDisplaystyle(
                    visible=metadata.get('displaystyle', {}).get('visible', False),
                    published=metadata.get('displaystyle', {}).get('published', False)
                )

                interface_entry = FunctionConfigEntry(
                    tags=[
                        FunctionConfigTags(t)
                        for t in metadata.get('tags', [])
                        if t in FunctionConfigTags._value2member_map_
                    ],
                    type=metadata['type'],
                    interfacetypes=metadata['interfacetypes'],
                    functionname=metadata['functionname'],
                    displayname=metadata['displayname'],
                    description=metadata['description'],
                    displaystyle=displaystyle,
                    params=metadata['params'],
                    returns=metadata['returns'],
                    qosprofile=metadata.get('qosprofile', 10),
                    callbacks=None,
                    periodic=None
                )
                interface_functions.append(interface_entry)
                
                logger.debug(
                    "interface_entry_created",
                    function_name=metadata['functionname'],
                    interface_types_count=len(ifaces)
                )

            elif metadata['type'] in (
                FunctionConfigBaseTypes.message.value,
                FunctionConfigBaseTypes.action.value,
            ):
                # Publisher (message) and Action types — no service callbacks,
                # registered as-is so the entity can bind them when ready.
                logger.debug(
                    "processing_non_service_interface",
                    index=idx,
                    type=metadata['type'],
                    function_name=metadata.get('functionname', 'unknown'),
                )
                displaystyle = FunctionConfigDisplaystyle(
                    visible=metadata.get('displaystyle', {}).get('visible', False),
                    published=metadata.get('displaystyle', {}).get('published', False)
                )
                interface_entry = FunctionConfigEntry(
                    tags=[
                        FunctionConfigTags(t)
                        for t in metadata.get('tags', [])
                        if t in FunctionConfigTags._value2member_map_
                    ],
                    type=metadata['type'],
                    interfacetypes=metadata.get('interfacetypes', None),
                    functionname=metadata['functionname'],
                    displayname=metadata['displayname'],
                    description=metadata['description'],
                    displaystyle=displaystyle,
                    params=metadata.get('params', []),
                    returns=metadata.get('returns', []),
                    qosprofile=metadata.get('qosprofile', 10),
                    callbacks=None,
                    periodic=None
                )
                interface_functions.append(interface_entry)
                logger.debug(
                    "interface_entry_created",
                    function_name=metadata['functionname'],
                    type=metadata['type'],
                )

            else:
                logger.warning(
                    "unknown_interface_type_skipped",
                    index=idx,
                    type=metadata.get('type'),
                    function_name=metadata.get('functionname', 'unknown'),
                )
                
        except KeyError as e:
            logger.error(
                "missing_interface_field",
                missing_key=str(e),
                metadata_snippet=str(metadata)[:200],
                index=idx
            )
            log_exception(
                logger,
                e,
                context={
                    "operation": "create_interface_entry",
                    "index": idx,
                    "metadata": metadata
                }
            )
            raise
        except TypeError as e:
            logger.error(
                "interface_type_error",
                error=str(e),
                metadata_snippet=str(metadata)[:200],
                index=idx
            )
            log_exception(
                logger,
                e,
                context={
                    "operation": "create_interface_entry",
                    "index": idx,
                    "metadata": metadata
                }
            )
            raise

    log_function_result(
        logger,
        success=True,
        function="_create_base_interfaces",
        interface_count=len(interface_functions),
        interface_names=[f.functionname for f in interface_functions]
    )
    
    return interface_functions

async def _load_storage_config() -> dict[str, Any]:
    """
    Load the storage configuration from resource/storage_config.ini file.
    
    Returns:
        Storage configuration dictionary
        
    Raises:
        FileNotFoundError: If storage_config.ini file is not found
        ValueError: If file is not valid or missing required sections
    """
    log_function_call(logger, function="_load_storage_config", package=PACKAGE_NAME)
    
    try:
        config = await load_resource(
            PACKAGE_NAME,
            Path('resource', 'storage_config.ini')
        )
        log_function_result(
            logger,
            success=True,
            function="_load_storage_config",
            config_keys=list(config.keys()) if isinstance(config, dict) else "not_dict"
        )
        return config
    except Exception as e:
        log_exception(logger, e, context={"function": "_load_storage_config"})
        raise

async def _load_module_config() -> dict[str, Any]:
    """
    Load the module configuration from pyproject.toml file.
    
    Returns:
        Module configuration dictionary
        
    Raises:
        FileNotFoundError: If pyproject.toml file is not found
        ValueError: If file is not valid or missing required sections
    """
    log_function_call(logger, function="_load_module_config", package=PACKAGE_NAME)
    
    try:
        config = await load_resource(
            PACKAGE_NAME,
            Path('resource', 'module_config.yaml')
        )
        log_function_result(
            logger,
            success=True,
            function="_load_module_config",
            config_keys=list(config.keys()) if isinstance(config, dict) else "not_dict"
        )
        return config
    except Exception as e:
        log_exception(logger, e, context={"function": "_load_module_config"})
        raise

async def _load_module_data() -> Optional[dict[str, Any]]:
    """
    Load the module data from .module/module_data.yaml file.
    
    Returns:
        Module data dictionary or None if not found
        
    Raises:
        ValueError: If file is not valid or missing required sections
    """
    log_function_call(logger, function="_load_module_data", package=PACKAGE_NAME)
    
    pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))
    data_path: Path = pkg_dir.parents[3] / ".module" / "module_data.yaml"

    logger.debug("checking_module_data_file", path=str(data_path))

    try:
        module_data: Optional[dict[str, Any]] = await FileReader.open_yaml_file(data_path)
        logger.info(
            "module_data_loaded",
            path=str(data_path),
            data_keys=list(module_data.keys()) if module_data else []
        )
        log_function_result(logger, success=True, function="_load_module_data")
        return module_data
        
    except FileNotFoundError as e:
        logger.warning(
            "module_data_not_found",
            path=str(data_path),
            will_create=True
        )
        # Create .module directory if it does not exist
        if not data_path.parent.exists():
            logger.debug("creating_module_directory", path=str(data_path.parent))
            data_path.parent.mkdir(parents=True)
        return None
    except Exception as e:
        log_exception(logger, e, context={"function": "_load_module_data", "path": str(data_path)})
        raise

async def _write_module_data(data: dict[str, Any]) -> None:
    """
    Write module data to .module/module_data.yaml file.
    
    Args:
        data: Module data dictionary to write
        
    Raises:
        FileNotFoundError: If resource directory does not exist
        ValueError: If data is not valid or missing required sections
    """
    log_function_call(logger, function="_write_module_data", data_keys=list(data.keys()))
    
    try:
        pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))
        data_path: Path = pkg_dir.parents[3] / ".module" / "module_data.yaml"

        logger.debug("writing_module_data", path=str(data_path))
        await FileWriter.write_yaml_file(data_path, data)
        
        logger.info("module_data_written", path=str(data_path), data_keys=list(data.keys()))
        log_function_result(logger, success=True, function="_write_module_data")
        
    except Exception as e:
        log_exception(logger, e, context={"function": "_write_module_data", "path": str(data_path)})
        raise

async def _load_project_settings() -> dict[str, Any]:
    """
    Load project settings from pyproject.toml file.
    
    Returns:
        Project settings dictionary with version information
        
    Raises:
        FileNotFoundError: If pyproject.toml not found
        ValueError: If settings are missing or invalid
    """
    log_function_call(logger, function="_load_project_settings", package=PACKAGE_NAME)
    
    try:
        pkg_dir = Path(get_package_share_directory(PACKAGE_NAME))
        pyproject_path: Path = pkg_dir.parents[3] / "pyproject.toml"
        
        logger.debug("loading_pyproject", path=str(pyproject_path))
        module_settings: Optional[dict[str, Any]] = await FileReader.open_toml_file(pyproject_path)

        if not module_settings:
            logger.error("module_settings_empty", path=str(pyproject_path))
            raise ValueError("Module settings not found in pyproject.toml")

        project_settings = module_settings['tool']['vyra']
        project_settings['version'] = module_settings['tool']['poetry']['version']

        if not project_settings:
            logger.error("project_settings_empty", path=str(pyproject_path))
            raise ValueError("Project settings not found in pyproject.toml")
        
        logger.info(
            "project_settings_loaded",
            module_name=project_settings.get('module_name', 'unknown'),
            version=project_settings.get('version', 'unknown'),
            template=project_settings.get('module_template', 'unknown')
        )
        log_function_result(logger, success=True, function="_load_project_settings")
        
        return project_settings
        
    except Exception as e:
        log_exception(logger, e, context={"function": "_load_project_settings", "path": str(pyproject_path)})
        raise

async def build_entity(project_settings) -> VyraEntity:
    """
    Build a VyraEntity from project settings and module data.
    
    Creates or recovers module entry, state entry, news entry, and error entry.
    Sets up storage and transient data types.
    
    Args:
        project_settings: Project configuration from pyproject.toml
        
    Returns:
        Configured VyraEntity instance
        
    Raises:
        ValueError: If module data is invalid or incomplete
    """
    log_function_call(
        logger,
        function="build_entity",
        module_name=project_settings.get('module_name', 'unknown')
    )
    
    try:
        logger.debug("loading_module_data")
        module_data: Optional[dict] = await _load_module_data()
        needed_fields: list[str] = ['uuid', 'name', 'template', 'description', 'version']

        if not module_data or module_data == {}:
            logger.info(
                "creating_new_module_entry",
                reason="module_data_empty",
                source="project_settings"
            )

            me = ModuleEntry(
                uuid= ModuleEntry.gen_uuid(),
                name=project_settings['module_name'],
                template=project_settings['module_template'],
                description=project_settings['module_description'],
                version=project_settings['version'],
            )
            logger.debug("new_module_entry_created", uuid=me.uuid, name=me.name)
            
        elif not all(field in module_data for field in needed_fields):
            missing_field: list[str] = [
                field for field in needed_fields if field not in module_data
            ]
            
            logger.warning(
                "module_data_incomplete",
                missing_fields=missing_field,
                will_recover=True
            )

            me = ModuleEntry(
                uuid=module_data.get('uuid', ModuleEntry.gen_uuid()),
                name=module_data.get('name', project_settings['module_name']),
                template=module_data.get('template', project_settings['module_template']),
                description=module_data.get('description', project_settings['module_description']),
                version=module_data.get('version', project_settings['version']),
            )

            logger.info(
                "module_data_recovered",
                uuid=me.uuid,
                name=me.name,
                recovered_fields=missing_field
            )
        else:
            logger.debug(
                "module_data_complete",
                uuid=module_data.get('uuid'),
                name=module_data.get('name')
            )

            if module_data['uuid'] in [None, "", "null"]:
                logger.warning(
                    "module_uuid_empty",
                    generating_new=True
                )
                module_data['uuid'] = ModuleEntry.gen_uuid()

            me = ModuleEntry(
                uuid=module_data['uuid'],
                name=module_data['name'],
                template=module_data['template'],
                description=module_data['description'],
                version=module_data['version'],
            )
            logger.debug("module_entry_loaded", uuid=me.uuid, name=me.name)
        
        # Persist module data
        logger.debug("persisting_module_data")
        await _write_module_data(me.to_dict())
        
        logger.info(
            "module_entry_ready",
            uuid=me.uuid,
            name=me.name,
            template=me.template,
            version=me.version
        )

        # Create state, news, and error entries
        logger.debug("creating_state_entries")
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
        
        logger.debug("state_entries_created")

        # Load configurations
        logger.debug("loading_configurations")
        module_config = await _load_module_config()
        storage_config = await _load_storage_config()
        logger.debug("configurations_loaded")

        # Create entity
        logger.info("creating_vyra_entity", module_name=me.name, uuid=me.uuid)
        entity = VyraEntity(
            state_entry=se,
            module_entry=me,
            news_entry=ne,
            error_entry=ee,
            module_config=module_config
        )

        # Setup transient base types
        transient_base_types: dict[str, Any] = {
            'VolatileString': VBASEVolatileString,
            'VolatileHash': VBASEVolatileHash,
            'VolatileList': VBASEVolatileList,
            'VolatileSet': VBASEVolatileSet
        }

        parameter_types: dict[str, Any] = {
            'UpdateParamEvent': VBASEUpdateParamEvent
        }

        logger.debug("starting_entity_startup")
        await entity.startup_entity()
        logger.debug("entity_startup_complete")

        logger.debug("setting_up_entity_storage")
        await entity.setup_storage(
            storage_config, 
            transient_base_types, 
            parameter_types
        )
        
        logger.info(
            "entity_built_successfully",
            module=me.name,
            uuid=me.uuid,
            version=me.version
        )
        log_function_result(logger, success=True, function="build_entity", module=me.name)

        return entity
        
    except Exception as e:
        log_exception(
            logger,
            e,
            context={
                "function": "build_entity",
                "module_name": project_settings.get('module_name', 'unknown')
            }
        )
        raise


async def create_db_storage(entity: VyraEntity) -> None:
    """
    Create database storage for the entity.
    
    Configuration is loaded from this ROS2 package's storage_config.ini file.
    
    Args:
        entity: VyraEntity for which database storage should be created
        
    Raises:
        FileNotFoundError: If storage_config.ini file is not found
        ValueError: If config is invalid or missing required sections
    """
    log_function_call(
        logger,
        function="create_db_storage",
        module_name=entity.module_entry.name
    )
    
    try:
        from vyra_base.storage.db_access import DbAccess

        logger.debug("loading_storage_config")
        storage_config: dict[str, Any] = await _load_storage_config()
        logger.debug("storage_config_loaded", config_keys=list(storage_config.keys()))

        logger.info(
            "creating_db_access",
            module=entity.module_entry.name,
            db_type=storage_config.get('type', 'unknown')
        )
        
        db_access = DbAccess(
            module_name=entity.module_entry.name,
            db_config=storage_config
        )

        logger.debug("creating_database_tables")
        await db_access.create_all_tables()
        logger.info("database_tables_created")

        logger.debug("registering_storage_in_entity")
        entity.register_storage(db_access)
        
        logger.info(
            "db_storage_ready",
            module=entity.module_entry.name
        )
        log_function_result(logger, success=True, function="create_db_storage")
        
    except Exception as e:
        log_exception(
            logger,
            e,
            context={
                "function": "create_db_storage",
                "module": entity.module_entry.name
            }
        )
        raise

async def build_base():
    """
    Build base entity configuration.
    
    Main initialization function that:
    1. Loads project settings
    2. Builds VyraEntity
    3. Creates base interfaces
    4. Sets up ROS2 services
    5. Creates database storage
    
    Returns:
        Fully configured VyraEntity
        
    Raises:
        Various exceptions from underlying functions
    """
    log_function_call(logger, function="build_base")
    
    try:
        logger.info("build_base_started")
        
        # Load project settings
        logger.debug("loading_project_settings")
        project_settings: dict[str, Any] = await _load_project_settings()
        logger.info(
            "project_settings_loaded",
            module_name=project_settings.get('module_name', 'unknown')
        )
        
        # Build entity
        logger.debug("building_entity")
        entity: VyraEntity = await build_entity(project_settings)
        logger.info(
            "entity_built",
            module=entity.module_entry.name,
            uuid=entity.module_entry.uuid
        )
        
        # VyraEntity.__init__() calls register_callables_callbacks(self) which adds 
        # entity methods to DataSpace but doesn't create ROS2 services.
        # We need to create the actual ROS2 services by loading interfaces with callbacks.

        # Register interface package paths so VyraEntity / InterfaceFactory can locate
        # ROS2 message types and Protobuf schemas at runtime.
        # The installed ament package lives under install/{MODULE_NAME}_interfaces/
        interfaces_install_path = Path(f"/workspace/src/{entity.module_entry.name}_interfaces")
        if interfaces_install_path.exists():
            entity.set_interface_paths([interfaces_install_path])
            logger.info(
                "interface_paths_set",
                paths=[str(interfaces_install_path)]
            )
        else:
            logger.warning(
                "interface_paths_not_found",
                path=str(interfaces_install_path)
            )

        # Load base interface metadata
        logger.debug("creating_base_interfaces")
        base_interfaces: list[Any] = await _create_base_interfaces()
        interface_names = [i.functionname for i in base_interfaces]
        logger.info(
            "base_interfaces_created",
            count=len(base_interfaces),
            interfaces=interface_names
        )

        # BLUEPRINT STRATEGY — Phase 2: bind callbacks before registering interfaces
        # Interface definitions (JSON metadata) are separated from implementations
        # (entity methods). We bind here so set_interfaces creates real queryables.
        _callback_sources: list[Any] = [entity]
        if hasattr(entity, 'param_manager') and entity.param_manager is not None:
            _callback_sources.append(entity.param_manager)
        if hasattr(entity, 'security_manager') and entity.security_manager is not None:
            _callback_sources.append(entity.security_manager)
        if hasattr(entity, 'volatile') and entity.volatile is not None:
            _callback_sources.append(entity.volatile)

        for component in _callback_sources:
            bound = entity.bind_interface_callbacks(component, base_interfaces)
            bound_count = sum(1 for v in bound.values() if v)
            if bound_count:
                logger.info(
                    "blueprint_callbacks_bound",
                    component=type(component).__name__,
                    bound=bound_count,
                    total=len(bound),
                )

        # Phase 3: register with transport (callbacks now bound → creates real queryables)
        logger.debug("setting_entity_interfaces")
        await entity.set_interfaces(base_interfaces)
        logger.info("entity_interfaces_set", count=len(base_interfaces))
        
        # Create database storage
        logger.debug("creating_db_storage")
        await create_db_storage(entity)
        logger.info("db_storage_created")

        logger.info(
            "build_base_complete",
            module=entity.module_entry.name,
            uuid=entity.module_entry.uuid,
            interface_count=len(base_interfaces)
        )
        log_function_result(
            logger,
            success=True,
            function="build_base",
            module=entity.module_entry.name
        )

        return entity
        
    except Exception as e:
        log_exception(logger, e, context={"function": "build_base"})
        raise