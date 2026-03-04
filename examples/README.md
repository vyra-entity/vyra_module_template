# Examples

Dieser Ordner enthält **kleine, isolierte Beispiele** für einzelne Feeder-Fälle.
Jede Datei behandelt genau einen Use-Case.

Zusätzlich enthält der Ordner jetzt Basisbeispiele für State, Interfaces,
Helper und Security, damit neue Module schneller aus dem Template heraus
entwickelt werden können.

## Struktur

- `feeders/01_error_monitor_method.py` – Exception-Monitoring auf Klassenmethode via `@feed_tracker.monitor(...)`
- `feeders/02_error_monitor_function.py` – Monitoring auf freier Funktion mit expliziter `entity`
- `feeders/03_news_condition_success.py` – News-Condition (bool-only) mit `execution_point`
- `feeders/04_custom_tag_condition.py` – Condition mit Custom-Tag, Rule-/Tag-Filter und `execution_point`
- `feeders/05_error_condition_traceback.py` – ErrorFeeder-Condition zusätzlich zum Exception-Push
- `feeders/06_state_feeder_no_wrapper.py` – StateFeeder bewusst ohne Wrapper (direktes Feed)
- `feeders/07_news_monitor_wrapper.py` – News-Monitor-Wrapper auf Methode
- `feeders/08_custom_monitor_wrapper.py` – CustomFeeder-Monitor-Wrapper
- `feeders/09_execution_points_during.py` – BEFORE/DURING/AFTER/ALWAYS in einem isolierten Ablauf
- `state/01_state_transition_flow.py` – Minimaler Lifecycle-/Operational-Flow für `StateManager`
- `interfaces/01_remote_service_pattern.py` – Service-Pattern mit `@remote_service`
- `helper/01_file_io_config_pattern.py` – Async/sync Config-I/O via FileReader/FileWriter
- `security/01_access_policy_pattern.py` – Rollen-/Access-Level-Pattern für geschützte Services

## Hinweise

- Condition-Funktionen müssen synchron sein und `bool` zurückgeben.
- `None` oder leere Messages werden nicht gepublished.
- Error-Monitor scannt Traceback und pusht Fehler immer an den ErrorFeeder, sofern ein `entity.error_feeder` gefunden wird.
- Für identische Meldungen greift Debouncing (5s-Fenster).
- Runtime-Context enthält u. a. `function`, `args`, `kwargs`, `result`, `exception`, `execution_point`.
- Condition-Auswertung kann über `rule_names=[...]`, `tags=[...]` und `execution_point=...` gezielt gefiltert werden.
- Die neuen Unterordner sind bewusst template-nah und enthalten keine hardcodierten produktiven IDs.
