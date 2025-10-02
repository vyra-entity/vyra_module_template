#!/bin/bash
# =============================================================================
# SSL Certificate Creation for VYRA Dashboard
# =============================================================================
# This script creates self-signed SSL certificates for the VYRA Dashboard
# following ROS2 security best practices.
#
# Usage:
#   ./tools/create_ssl_certificates.sh [--domain localhost] [--days 365]
# =============================================================================

set -euo pipefail

# Default values
DOMAIN="localhost"
DAYS=365
CERT_DIR="/workspace/storage/certificates"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --domain)
            DOMAIN="$2"
            shift 2
            ;;
        --days)
            DAYS="$2"
            shift 2
            ;;
        -h|--help)
            echo "Usage: $0 [--domain localhost] [--days 365]"
            echo ""
            echo "Options:"
            echo "  --domain    Domain name for certificate (default: localhost)"
            echo "  --days      Certificate validity in days (default: 365)"
            echo "  -h, --help  Show this help message"
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
echo "   Domain: $DOMAIN"
echo "   Validity: $DAYS days"
echo "   Output: $CERT_DIR"

# Create the SSL certificate
openssl req -x509 -newkey rsa:4096 \
    -keyout "$CERT_DIR/webserver.key" \
    -out "$CERT_DIR/webserver.crt" \
    -days "$DAYS" \
    -nodes \
    -subj "/CN=$DOMAIN/O=VYRA Dashboard/C=DE"

# Set appropriate permissions (important for security!)
chmod 600 "$CERT_DIR/webserver.key"    # Private key - owner read/write only
chmod 644 "$CERT_DIR/webserver.crt"    # Certificate - readable by all

echo "✅ SSL certificates created successfully!"
echo ""
echo "📋 Certificate Information:"
echo "   Certificate: $CERT_DIR/webserver.crt"
echo "   Private Key: $CERT_DIR/webserver.key (protected with 600 permissions)"
echo ""
echo "🔍 Certificate Details:"
openssl x509 -in "$CERT_DIR/webserver.crt" -text -noout | grep -A 2 "Subject:"
echo ""
echo "🌐 HTTPS will be available at: https://$DOMAIN:8443"
echo "⚠️  Note: Self-signed certificates will show security warnings in browsers"
