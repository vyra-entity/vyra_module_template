"""Use-Case 02: Monitoring auf freier Funktion mit expliziter Entity."""

from vyra_base.com.feeder import feed_tracker


@feed_tracker.monitor(tag="error", label="Freie Funktion", severity="ERROR", entity=None)
def unsafe_calculation(a: int, b: int) -> int:
    return a // b

# Für reale Nutzung: entity beim Decorator übergeben oder als kwargs `entity=...` setzen.
# result = unsafe_calculation(10, 0, entity=my_module_instance)

