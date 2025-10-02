# Gunicorn Configuration File
# Python configuration format
# This file is loaded by gunicorn via --config parameter

# Server socket
bind = "0.0.0.0:8443"

# Worker processes
workers = 2
worker_class = "sync"
timeout = 30

# Logging
accesslog = "/workspace/log/gunicorn/gunicorn_access.log"
errorlog = "/workspace/log/gunicorn/gunicorn_error.log"
loglevel = "info"

# Performance
preload_app = True

# SSL Configuration
# SSL certificates are handled by the vyra_entrypoint.sh script
# If certificates exist in /workspace/storage/certificates/, they will be used
# This would require modifying the supervisord command to include SSL parameters
