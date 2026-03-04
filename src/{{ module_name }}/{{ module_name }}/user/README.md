# UserManager Client

Dieses Modul enthält ausschließlich den `UserManagerClient`.

## Zweck
- Keine lokale Benutzerverwaltung im Modul.
- Verbindung zu einem externen UserManager-Modul.
- Anforderung von Berechtigungstokens für Zugriffe auf Module mit erhöhtem Security-Level.

## TaskManager-Integration
- Runner: `usermanager_client_runner`
- Wird durch `main.py` als eigener Task gestartet.

