#!/bin/bash
# =============================================================================
# SSL Certificate Creation for VYRA Dashboard
# =============================================================================
# This script creates self-signed SSL certificates for the VYRA Dashboard
# following ROS2 security best practices.
#
# Usage:
#   ./tools/create_ssl_certificates.sh [--name certificate_name] [--domain localhost] [--days 365]
#
# Examples:
#   ./tools/create_ssl_certificates.sh --name webserver          # Backend certificate
#   ./tools/create_ssl_certificates.sh --name frontend          # Frontend certificate
#   ./tools/create_ssl_certificates.sh --name api-gateway       # API Gateway certificate
# =============================================================================

set -euo pipefail

# Default values
CERT_NAME="webserver"
DOMAIN="localhost"
DAYS=365
CERT_DIR="/workspace/storage/certificates"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --name)
            CERT_NAME="$2"
            shift 2
            ;;
        --domain)
            DOMAIN="$2"
            shift 2
            ;;
        --days)
            DAYS="$2"
            shift 2
            ;;
        -h|--help)
            echo "Usage: $0 [--name certificate_name] [--domain localhost] [--days 365]"
            echo ""
            echo "Options:"
            echo "  --name      Certificate name (default: webserver)"
            echo "              Common names: webserver, frontend, api-gateway, redis-tls"
            echo "  --domain    Domain name for certificate (default: localhost)"
            echo "  --days      Certificate validity in days (default: 365)"
            echo "  -h, --help  Show this help message"
            echo ""
            echo "Examples:"
            echo "  $0 --name webserver    # Backend HTTPS certificate"
            echo "  $0 --name frontend     # Frontend HTTPS certificate"  
            echo "  $0 --name api-gateway  # API Gateway certificate"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

# Create certificate directory if it doesn't exist
mkdir -p "$CERT_DIR"

echo "🔐 Creating SSL certificates for VYRA Dashboard..."
echo "   Certificate Name: $CERT_NAME"
echo "   Domain: $DOMAIN"
echo "   Validity: $DAYS days"
echo "   Output: $CERT_DIR"

# Create the SSL certificate with custom name
openssl req -x509 -newkey rsa:4096 \
    -keyout "$CERT_DIR/${CERT_NAME}.key" \
    -out "$CERT_DIR/${CERT_NAME}.crt" \
    -days "$DAYS" \
    -nodes \
    -subj "/CN=$DOMAIN/O=VYRA Dashboard/OU=${CERT_NAME}/C=DE"

# Set appropriate permissions (important for security!)
chmod 600 "$CERT_DIR/${CERT_NAME}.key"    # Private key - owner read/write only
chmod 644 "$CERT_DIR/${CERT_NAME}.crt"    # Certificate - readable by all

echo "✅ SSL certificates created successfully!"
echo ""
echo "📋 Certificate Information:"
echo "   Certificate: $CERT_DIR/${CERT_NAME}.crt"
echo "   Private Key: $CERT_DIR/${CERT_NAME}.key (protected with 600 permissions)"
echo ""
echo "🔍 Certificate Details:"
openssl x509 -in "$CERT_DIR/${CERT_NAME}.crt" -text -noout | grep -A 2 "Subject:"
echo ""
echo "🌐 HTTPS Configuration:"
case "$CERT_NAME" in
    "webserver"|"backend")
        echo "   Backend HTTPS: https://$DOMAIN:8443"
        echo "   Nginx upstream: server 127.0.0.1:8443 (SSL enabled)"
        ;;
    "frontend"|"nginx")
        echo "   Frontend HTTPS: https://$DOMAIN:3000"
        echo "   Nginx SSL: listen 3000 ssl; (SSL enabled)"
        ;;
    "api-gateway")
        echo "   API Gateway HTTPS: https://$DOMAIN:8080"
        ;;
    *)
        echo "   Custom certificate for: $CERT_NAME"
        ;;
esac
echo ""
echo "⚠️  Note: Self-signed certificates will show security warnings in browsers"
echo "💡 Tip: Add certificate to browser trusted store or use --insecure flag for testing"
