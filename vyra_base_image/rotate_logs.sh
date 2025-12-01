#!/bin/bash
# Log rotation script for ROS2 runtime logs
# Usage: rotate_logs.sh <logfile> <max_size_mb> <max_backups>

LOGFILE="$1"
MAX_SIZE_MB="${2:-50}"  # Default: 50MB
MAX_BACKUPS="${3:-5}"   # Default: 5 backups

if [ ! -f "$LOGFILE" ]; then
    exit 0
fi

# Get file size in MB
SIZE_MB=$(du -m "$LOGFILE" | cut -f1)

if [ "$SIZE_MB" -ge "$MAX_SIZE_MB" ]; then
    echo "🔄 Rotating log: $LOGFILE (${SIZE_MB}MB >= ${MAX_SIZE_MB}MB)"
    
    # Rotate existing backups
    for i in $(seq $((MAX_BACKUPS - 1)) -1 1); do
        if [ -f "${LOGFILE}.$i" ]; then
            mv "${LOGFILE}.$i" "${LOGFILE}.$((i + 1))"
        fi
    done
    
    # Create new backup
    mv "$LOGFILE" "${LOGFILE}.1"
    
    # Delete old backups
    if [ -f "${LOGFILE}.$((MAX_BACKUPS + 1))" ]; then
        rm -f "${LOGFILE}.$((MAX_BACKUPS + 1))"
    fi
    
    echo "✅ Log rotated: $LOGFILE"
fi
