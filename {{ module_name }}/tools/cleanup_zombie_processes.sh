#!/bin/bash
# cleanup_zombie_processes.sh - Kill all remaining v2_modulemanager/core processes
# Usage: docker exec <container> bash /workspace/tools/cleanup_zombie_processes.sh

echo "🔍 Checking for zombie processes..."

# Find all v2_modulemanager/core processes
PIDS=$(pgrep -f "v2_modulemanager/core" | grep -v "$$")

if [ -z "$PIDS" ]; then
    echo "✅ No zombie processes found"
    exit 0
fi

COUNT=$(echo "$PIDS" | wc -l)
echo "⚠️ Found $COUNT processes to clean up"

# Show process info
echo ""
echo "Process list:"
ps aux | grep "v2_modulemanager/core" | grep -v "grep"
echo ""

# Ask for confirmation (skip in non-interactive mode)
if [ -t 0 ]; then
    read -p "Kill all these processes? (y/N) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "❌ Cancelled by user"
        exit 1
    fi
fi

echo "🔨 Sending SIGTERM (graceful shutdown)..."
echo "$PIDS" | xargs kill -TERM 2>/dev/null || true

sleep 2

# Check if any are still alive
REMAINING=$(pgrep -f "v2_modulemanager/core" | grep -v "$$")

if [ -n "$REMAINING" ]; then
    REMAINING_COUNT=$(echo "$REMAINING" | wc -l)
    echo "⚠️ $REMAINING_COUNT processes still alive, force killing..."
    echo "$REMAINING" | xargs kill -KILL 2>/dev/null || true
    sleep 1
fi

# Final check
FINAL=$(pgrep -f "v2_modulemanager/core" | grep -v "$$")

if [ -z "$FINAL" ]; then
    echo "✅ All zombie processes cleaned up successfully"
    exit 0
else
    FINAL_COUNT=$(echo "$FINAL" | wc -l)
    echo "❌ Failed to kill $FINAL_COUNT processes"
    echo "$FINAL"
    exit 1
fi
