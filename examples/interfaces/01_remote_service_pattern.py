"""
Template Interface Pattern Example
=================================

Service callback pattern for module-local business logic.
"""

from vyra_base.com import remote_service


class ServiceComponent:
    def __init__(self) -> None:
        self._status = "ready"

    @remote_service()
    async def get_status(self, request: dict | None = None, _meta: dict | None = None) -> dict:
        request = request or {}
        include_debug = bool(request.get("debug", False))
        response = {
            "success": True,
            "status": self._status,
        }
        if include_debug:
            response["debug"] = {"source": "ServiceComponent.get_status"}
        return response
