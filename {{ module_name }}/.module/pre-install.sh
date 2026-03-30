#!/bin/bash
# =============================================================================
# pre-install.sh — VYRA Module Pre-Installation Hook
# =============================================================================
#
# PURPOSE
#   This script runs as STEP 1 of the VYRA module installation pipeline,
#   before apt, pip, or npm install anything. Use it to:
#     - Add GPG keys and third-party APT repositories (PPAs)
#     - Download and install binaries not available via package managers
#     - Verify that base-image dependencies are present
#     - Set up environment variables or config files required by later steps
#
# EXECUTION CONTEXT
#   - Runs inside the container as root
#   - Working directory: /workspace
#   - Called by: Module Manager during deploy / update
#   - Runs before: system-packages.txt, requirements.txt, npm-packages.txt
#
# SAFETY
#   - The script exits immediately on any error (set -e)
#   - Use existence checks before installing to keep the script idempotent
#
# =============================================================================
set -euo pipefail

echo "------------------------------------------------------------"
echo " VYRA Module Pre-Install — {{ module_name }}"
echo "------------------------------------------------------------"

# ── Base Image Dependency Verification ───────────────────────────────────────
# Node.js and npm are pre-installed in the VYRA base image.
# This block verifies their presence and prints the versions for the logs.

echo "[check] Verifying base-image dependencies..."

if command -v node &> /dev/null; then
    echo "[ok]    Node.js available: $(node --version)"
else
    echo "[warn]  Node.js not found in base image — frontend builds will fail"
fi

if command -v npm &> /dev/null; then
    echo "[ok]    npm available: $(npm --version)"
else
    echo "[warn]  npm not found in base image"
fi

if command -v python3 &> /dev/null; then
    echo "[ok]    Python available: $(python3 --version)"
else
    echo "[error] Python3 not found — this module cannot run without Python"
    exit 1
fi

# ── Example: Add a Third-Party APT Repository ────────────────────────────────
# Uncomment and adapt the block below to add a custom APT source.
# Always pin the GPG key to avoid "apt-key deprecated" warnings.
#
# REPO_NAME="my-vendor"
# REPO_URL="https://packages.my-vendor.com/debian"
# KEYRING_PATH="/usr/share/keyrings/${REPO_NAME}-archive-keyring.gpg"
#
# if [ ! -f "$KEYRING_PATH" ]; then
#     echo "[setup] Adding ${REPO_NAME} GPG key..."
#     curl -fsSL "https://packages.my-vendor.com/gpgkey" \
#         | gpg --dearmor -o "$KEYRING_PATH"
#     echo "deb [signed-by=${KEYRING_PATH}] ${REPO_URL} stable main" \
#         > /etc/apt/sources.list.d/${REPO_NAME}.list
#     apt-get update -qq
#     echo "[ok]    ${REPO_NAME} repository added"
# else
#     echo "[skip]  ${REPO_NAME} repository already configured"
# fi

# ── Example: Download a Binary from a Release URL ────────────────────────────
# Use this pattern for tools that have no APT or pip package.
#
# TOOL_VERSION="1.2.3"
# TOOL_BIN="/usr/local/bin/my-tool"
#
# if [ ! -f "$TOOL_BIN" ]; then
#     echo "[setup] Installing my-tool v${TOOL_VERSION}..."
#     curl -fsSL "https://github.com/vendor/my-tool/releases/download/v${TOOL_VERSION}/my-tool-linux-amd64" \
#         -o "$TOOL_BIN"
#     chmod +x "$TOOL_BIN"
#     echo "[ok]    my-tool installed: $(${TOOL_BIN} --version)"
# else
#     echo "[skip]  my-tool already present"
# fi

# ── Module-Specific Setup ─────────────────────────────────────────────────────
# Add any module-specific pre-installation steps below this line.
# Keep each block clearly commented and idempotent.

echo "------------------------------------------------------------"
echo " Pre-install complete"
echo "------------------------------------------------------------"
