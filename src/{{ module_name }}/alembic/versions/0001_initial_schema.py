"""Initial schema for {{ module_name }}.

This is the base migration generated from the VYRA module template.
Replace the body of ``upgrade()`` and ``downgrade()`` with your module's
actual table definitions, or delete this file and generate a fresh migration
with ``alembic revision --autogenerate -m "initial schema"``.

Autogenerate quick-start::

    cd src/{{ module_name }}
    # Ensure all model imports are added to alembic/env.py first, then:
    DATABASE_URL=sqlite:////workspace/storage/{{ module_name }}.sqlite \\
        alembic revision --autogenerate -m "initial schema"
    alembic upgrade head

Revision ID: 0001
Revises: –
Create Date: 2026-03-05
"""

from __future__ import annotations

from typing import Sequence, Union

import sqlalchemy as sa
from alembic import op

revision: str = "0001"
down_revision: Union[str, None] = None
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    """
    Create initial tables for {{ module_name }}.

    Replace this placeholder with actual table definitions.
    Example::

        op.create_table(
            "example",
            sa.Column("id", sa.Integer, primary_key=True, autoincrement=True),
            sa.Column("name", sa.String(255), nullable=False),
            sa.Column(
                "created_at",
                sa.DateTime(timezone=True),
                server_default=sa.text("(CURRENT_TIMESTAMP)"),
            ),
        )
    """
    pass  # Replace with your table definitions


def downgrade() -> None:
    """Drop initial tables for {{ module_name }}."""
    pass  # Replace with corresponding drop statements
