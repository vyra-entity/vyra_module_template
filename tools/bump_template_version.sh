#!/usr/bin/env bash
# bump_template_version.sh
# Increments the patch version for the vyra_module_template, commits and tags.
#
# Usage (from any directory):
#   bash /path/to/vyra_module_template/tools/bump_template_version.sh

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEMPLATE_DIR="$(dirname "$SCRIPT_DIR")"
COPIER_YML="$TEMPLATE_DIR/copier.yml"

# ---------------------------------------------------------------------------
# Read current version from copier.yml  (line: _version: "X.Y.Z")
# ---------------------------------------------------------------------------
if ! grep -q '_template_version:' "$COPIER_YML"; then
  echo "❌ No _template_version field found in copier.yml"
  echo "   Add:  _template_version: \"0.0.0\"  to copier.yml first."
  exit 1
fi

CURRENT=$(grep '_template_version:' "$COPIER_YML" | head -1 | sed 's/.*"\(.*\)".*/\1/')
IFS='.' read -r MAJOR MINOR PATCH <<< "$CURRENT"
PATCH=$(( PATCH + 1 ))
NEW_VERSION="${MAJOR}.${MINOR}.${PATCH}"

echo "📦 Bumping template version: $CURRENT → $NEW_VERSION"

# ---------------------------------------------------------------------------
# Write new version back
# ---------------------------------------------------------------------------
sed -i "s/_template_version: \"${CURRENT}\"/_template_version: \"${NEW_VERSION}\"/" "$COPIER_YML"

# ---------------------------------------------------------------------------
# Commit and tag
# ---------------------------------------------------------------------------
cd "$TEMPLATE_DIR"
git add -A
git commit -m "chore: bump template version to v${NEW_VERSION}"
git tag "v${NEW_VERSION}"

echo "✅ Committed and tagged v${NEW_VERSION}"
echo "   Run: git push && git push --tags"
