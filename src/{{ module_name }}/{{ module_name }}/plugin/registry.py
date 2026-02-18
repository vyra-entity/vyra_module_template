from __future__ import annotations

import importlib
import inspect
import logging

from pathlib import Path

from abc import ABC, abstractmethod
from types import ModuleType
from attr import dataclass
from flask import config
from vyra_base.helper.file_reader import FileReader
from typing import Optional

logger = logging.getLogger(__name__)


class PluginBase(ABC):
    @abstractmethod
    def name(self) -> str:
        pass

    @abstractmethod
    def run(self, *args, **kwargs):
        pass


@dataclass
class PLUGIN_CONFIG:
    name: str
    version: str
    description: str
    author: str
    license: str
    path: Path
    module: Optional[ModuleType] = None
    dependencies: list[str] = []
    enabled: bool = True


class PluginRegistry:
    """Registry for managing plugins in the Vyra module template.
    This class allows for registering, retrieving, and unregistering plugins.
    It also provides functionality to load plugins from a specified directory.
    """
    def __init__(self, module_name: str):
        """
        Initializes the PluginRegistry with an optional plugin path.
        :param plugin_path: Path to the directory containing plugins.
        """
        self._plugins: dict[str, PLUGIN_CONFIG] = {}
        self._package_name: str = module_name

        self.plugin_dir: Path = Path(__file__).parent / "plugin"

    def register_plugin(self, config: dict, plugin_path) -> None:
        if config["name"] in self._plugins:
            logger.warning(f"[PluginRegistry] Plugin '{config['name']}' is already registered, skipping.")
            return

        try:
            plugin = PLUGIN_CONFIG(
                name=config["name"],
                version=config["version"],
                description=config["description"],
                author=config["author"],
                license=config["license"],
                path=plugin_path,
                dependencies=config["dependencies"],
                enabled=config["enabled"]

            )
        except Exception as e:
            logger.error(f"[PluginRegistry] Error creating plugin config for '{config['name']}': {e}")
            return
        
        self.import_plugin(plugin)
        self._plugins[plugin.name] = plugin

    def import_plugin(self, plugin: PLUGIN_CONFIG):
        """Imports the plugin module based on the plugin configuration."""
        try:
            module_name = f"{self._package_name}.plugin.{plugin.name}"
            module = importlib.import_module(module_name)
            plugin.module = module
            logger.info(f"[PluginRegistry] Plugin '{plugin.name}' imported successfully.")
        except ImportError as e:
            logger.error(f"[PluginRegistry] Error importing plugin '{plugin.name}': {e}")
            raise e

    def get(self, name):
        return self._plugins.get(name)

    def unregister(self, plugin: PLUGIN_CONFIG):
        plugin.module = None  # Clear the module reference
        logger.info(f"[PluginRegistry] Unregistering plugin '{plugin.name}'")
        self._plugins.pop(plugin.name, None)

    async def load_plugins(self):

        if not self.plugin_dir.exists() or not self.plugin_dir.is_dir():
            raise ValueError(f"Plugin-Directory '{self.plugin_dir}' does not exist or is not a directory.")

        for subdir in self.plugin_dir.iterdir():
            if subdir.name.startswith('_'):
                logger.info(f"[PluginRegistry] Skipping hidden plugin-directory: {subdir.name}")
            
            if subdir.is_dir():
                plugin_yaml = subdir / "plugin.yaml"
                if plugin_yaml.exists():
                    try:
                        config: dict = await FileReader.open_yaml_file(plugin_yaml)
                        self.register_plugin(config, plugin_path=subdir)
                        logger.info(f"[PluginRegistry] Plugin '{config['name']}' successfully loaded.")
                    except Exception as e:
                        logger.error(f"[PluginRegistry] Error loading '{plugin_yaml}': {e}")
                else:
                    logger.warning(f"[PluginRegistry] '{plugin_yaml}' not found – Plugin '{subdir.name}' will be skipped.")
            else:
                logger.warning(f"[PluginRegistry] '{subdir.name}' is not a directory, skipping.")