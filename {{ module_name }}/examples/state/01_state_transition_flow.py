"""
Template State Flow Example
===========================

Shows a minimal state-transition flow that can be adapted inside
`application/main.py` of a generated module.
"""

from dataclasses import dataclass


@dataclass
class LocalState:
    lifecycle: str = "Offline"
    operational: str = "Idle"
    health: str = "Healthy"


def initialization_start(state: LocalState) -> None:
    state.lifecycle = "Initializing"


def initialization_complete(state: LocalState) -> None:
    state.lifecycle = "Active"
    state.operational = "Ready"


def shutdown_to_offline(state: LocalState) -> None:
    state.lifecycle = "ShuttingDown"
    state.operational = "Stopping"
    state.lifecycle = "Offline"
    state.operational = "Idle"


def main() -> None:
    state = LocalState()
    print("Initial:", state)
    initialization_start(state)
    print("After start:", state)
    initialization_complete(state)
    print("After complete:", state)
    shutdown_to_offline(state)
    print("After shutdown:", state)


if __name__ == "__main__":
    main()
