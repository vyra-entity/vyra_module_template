
from ..registry import PluginBase

class MyPlugin(PluginBase):
    def name(self) -> str:
        return "MyPlugin"

    def run(self, *args, **kwargs):
        print("Running MyPlugin with args:", args, "and kwargs:", kwargs)