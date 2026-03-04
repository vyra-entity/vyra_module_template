"""
Template Helper I/O Pattern
===========================

Configuration read/write pattern using vyra_base FileReader/FileWriter helpers.
"""

import asyncio
from pathlib import Path

from vyra_base.helper.file_reader import FileReader
from vyra_base.helper.file_writer import FileWriter


async def main() -> None:
    config_file = Path("/tmp/template_config.json")

    await FileWriter.write_json_file(
        config_file,
        {
            "module": "template",
            "enabled": True,
            "poll_interval": 1.0,
        },
    )

    loaded = await FileReader.open_json_file(config_file)
    print("Loaded config:", loaded)


if __name__ == "__main__":
    asyncio.run(main())
