"""
Template Security Access Pattern
================================

Shows a minimal access-level policy check pattern that can be applied
in service callbacks.
"""

from vyra_base.security.security_levels import SecurityLevel


def has_required_level(granted_level: int, required_level: SecurityLevel) -> bool:
    return granted_level >= required_level.value


def run_demo() -> None:
    required = SecurityLevel.EXTENDED_AUTH
    callers = {
        "dashboard": SecurityLevel.BASIC_AUTH.value,
        "operator": SecurityLevel.EXTENDED_AUTH.value,
        "automation": SecurityLevel.HMAC.value,
    }

    for caller, granted in callers.items():
        allowed = has_required_level(granted, required)
        print(f"{caller}: granted={granted} required={required.value} allowed={allowed}")


if __name__ == "__main__":
    run_demo()
