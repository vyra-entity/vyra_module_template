#!/bin/bash
# Pre-Install Script für spezielle Repositories
# Wird vor system-packages.txt ausgeführt

echo "🔧 Setting up additional repositories..."

# Node.js ist bereits im Base Image installiert
if command -v node &> /dev/null; then
    echo "✅ Node.js already available: $(node --version)"
    echo "✅ NPM already available: $(npm --version)"
else
    echo "⚠️ Node.js not found in Base Image - may need manual installation"
fi

# Weitere Repository-Setups hier hinzufügen...
