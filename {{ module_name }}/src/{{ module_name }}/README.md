# {{ module_name }}

Python source package for the `{{ module_name }}` VYRA module.

## Structure

```
{{ module_name }}/                       ← This Python package
├── alembic/                             ← Database schema migrations
│   └── versions/                        ← Migration scripts (auto-generated and manual)
├── alembic.ini                          ← Alembic configuration (DB URL, log config, paths)
├── resource/                            ← ROS2 resource marker and runtime config files
│   └── {{ module_name }}/
├── package.xml                          ← ROS2 package metadata (name, version, dependencies)
├── setup.cfg                            ← Python package metadata, console entry points
├── setup.py                             ← pip / colcon editable install hook
└── {{ module_name }}/                   ← Main Python module — see README therein
    └── README.md
```

## Database Migrations (Alembic)

`alembic/` manages SQLite schema changes for any data the module persists across restarts.
Migration scripts live under `alembic/versions/`.

Database files are stored in the persistent volume:

```
storage/    ← module root (mounted as a Docker volume, survives container restarts)
```

To create a new migration (run inside the container after changing SQLAlchemy models):

```bash
alembic revision --autogenerate -m "add my_table"
alembic upgrade head
```

## Main Module

The core application code lives in `{{ module_name }}/{{ module_name }}/`.
See [{{ module_name }}/README.md]({{ module_name }}/README.md) for a full description of every subsystem.
