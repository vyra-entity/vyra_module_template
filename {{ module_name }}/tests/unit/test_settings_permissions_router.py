"""Unit tests for settings permissions endpoints."""

from __future__ import annotations

from pathlib import Path

import pytest
import yaml
from fastapi import FastAPI
from httpx import ASGITransport, AsyncClient


@pytest.mark.asyncio
async def test_get_permissions(monkeypatch, tmp_path: Path) -> None:
    params_path = tmp_path / "module_params.yaml"
    params_path.write_text(
        yaml.safe_dump({"permissions": {"visible": True, "protected": False}}, sort_keys=False),
        encoding="utf-8",
    )

    from {{ module_name }}.backend_webserver.settings import router as settings_router_module

    monkeypatch.setattr(settings_router_module, "_resolve_module_params_path", lambda: params_path)

    app = FastAPI()
    app.include_router(settings_router_module.router)
    app.dependency_overrides[settings_router_module.get_current_user] = lambda: {"username": "viewer", "role": "viewer"}

    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as client:
        response = await client.get("/settings/permissions")

    assert response.status_code == 200
    assert response.json()["permissions"]["visible"] is True


@pytest.mark.asyncio
async def test_put_permissions_requires_admin(monkeypatch, tmp_path: Path) -> None:
    params_path = tmp_path / "module_params.yaml"
    params_path.write_text(
        yaml.safe_dump({"permissions": {"visible": True}}, sort_keys=False),
        encoding="utf-8",
    )

    from {{ module_name }}.backend_webserver.settings import router as settings_router_module

    monkeypatch.setattr(settings_router_module, "_resolve_module_params_path", lambda: params_path)

    app = FastAPI()
    app.include_router(settings_router_module.router)
    app.dependency_overrides[settings_router_module.get_current_user] = lambda: {"username": "admin", "role": "admin"}

    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as client:
        response = await client.put("/settings/permissions", json={"permissions": {"visible": False}})

    assert response.status_code == 200
    payload = yaml.safe_load(params_path.read_text(encoding="utf-8"))
    assert payload["permissions"]["visible"] is False
