#!/bin/bash
# wait-for-redis.sh - Wait for Redis to be ready before starting module
# Compatible with Docker Swarm deployments

set -e

# Configuration from environment variables
REDIS_HOST="${REDIS_HOST:-redis}"
REDIS_PORT="${REDIS_PORT:-6379}"
REDIS_USERNAME="${REDIS_USERNAME:-default}"
REDIS_PASSWORD="${REDIS_PASSWORD:-}"
REDIS_TLS_ENABLED="${REDIS_TLS_ENABLED:-false}"
REDIS_TLS_CA_CERT="${REDIS_TLS_CA_CERT:-}"
REDIS_TLS_CLIENT_CERT="${REDIS_TLS_CLIENT_CERT:-}"
REDIS_TLS_CLIENT_KEY="${REDIS_TLS_CLIENT_KEY:-}"

# Retry configuration
MAX_RETRIES="${REDIS_WAIT_MAX_RETRIES:-30}"
RETRY_INTERVAL="${REDIS_WAIT_RETRY_INTERVAL:-2}"

echo "⏳ Waiting for Redis at ${REDIS_HOST}:${REDIS_PORT}..."
echo "   Max retries: $MAX_RETRIES, Interval: ${RETRY_INTERVAL}s"
echo "   TLS enabled: $REDIS_TLS_ENABLED"

retry_count=0

while [ $retry_count -lt $MAX_RETRIES ]; do
    retry_count=$((retry_count + 1))
    
    # Build redis-cli command based on TLS configuration
    if [ "$REDIS_TLS_ENABLED" = "true" ]; then
        # TLS connection with certificates
        if [ -z "$REDIS_TLS_CA_CERT" ] || [ -z "$REDIS_TLS_CLIENT_CERT" ] || [ -z "$REDIS_TLS_CLIENT_KEY" ]; then
            echo "❌ Error: TLS enabled but certificates not configured"
            echo "   Required: REDIS_TLS_CA_CERT, REDIS_TLS_CLIENT_CERT, REDIS_TLS_CLIENT_KEY"
            exit 1
        fi
        
        # Check if certificate files exist
        if [ ! -f "$REDIS_TLS_CA_CERT" ]; then
            echo "❌ Error: CA certificate not found: $REDIS_TLS_CA_CERT"
            exit 1
        fi
        if [ ! -f "$REDIS_TLS_CLIENT_CERT" ]; then
            echo "❌ Error: Client certificate not found: $REDIS_TLS_CLIENT_CERT"
            exit 1
        fi
        if [ ! -f "$REDIS_TLS_CLIENT_KEY" ]; then
            echo "❌ Error: Client key not found: $REDIS_TLS_CLIENT_KEY"
            exit 1
        fi
        
        # Try TLS connection
        if redis-cli \
            -h "$REDIS_HOST" \
            -p "$REDIS_PORT" \
            --tls \
            --cert "$REDIS_TLS_CLIENT_CERT" \
            --key "$REDIS_TLS_CLIENT_KEY" \
            --cacert "$REDIS_TLS_CA_CERT" \
            --user "$REDIS_USERNAME" \
            --pass "$REDIS_PASSWORD" \
            ping > /dev/null 2>&1; then
            echo "✅ Redis is ready! (TLS connection successful)"
            exit 0
        fi
    else
        # Non-TLS connection
        if redis-cli \
            -h "$REDIS_HOST" \
            -p "$REDIS_PORT" \
            --user "$REDIS_USERNAME" \
            --pass "$REDIS_PASSWORD" \
            ping > /dev/null 2>&1; then
            echo "✅ Redis is ready! (Connection successful)"
            exit 0
        fi
    fi
    
    # Show progress
    echo "   Attempt $retry_count/$MAX_RETRIES failed, retrying in ${RETRY_INTERVAL}s..."
    sleep "$RETRY_INTERVAL"
done

echo "❌ Error: Redis not available after $MAX_RETRIES attempts"
echo "   Check if Redis is running and network connectivity is working"
exit 1
