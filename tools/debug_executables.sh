#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/$MODULE_NAME/tools/debug_executables.sh

pushd /workspace

export $(grep -v '^#' .env | xargs)

echo "=== 1. DIRECTORY STRUCTURE ==="
echo "Source structure:"
find src/$MODULE_NAME -name "*.py" | head -10

echo -e "\nInstall structure:"
ls -la install/$MODULE_NAME/ 2>/dev/null || echo "install/$MODULE_NAME nicht gefunden"

echo -e "\nBin directory:"
ls -la install/$MODULE_NAME/bin/ 2>/dev/null || echo "bin/ Verzeichnis nicht gefunden"

echo "=== 2. SETUP.PY CONTENT ==="
echo "Entry points in setup.py:"
grep -A 10 "entry_points" src/$MODULE_NAME/setup.py || echo "Keine entry_points gefunden"

echo "=== 3. PACKAGE.XML ==="
cat src/$MODULE_NAME/package.xml | grep -E "(name|build_type)" || echo "package.xml Problem"

echo "=== 4. PYTHON MODULE CHECK ==="
echo "Python Module importierbar?"
python3 -c "
import sys
sys.path.insert(0, '/workspace/install/$MODULE_NAME/lib/python3.11/site-packages')
try:
    import $MODULE_NAME
    print('✅ Module importiert')
    print(f'Module path: {$MODULE_NAME.__file__}')
    if hasattr($MODULE_NAME, 'main'):
        print('✅ main() Funktion gefunden')
    else:
        print('❌ main() Funktion nicht gefunden')
except Exception as e:
    print(f'❌ Import error: {e}')
"

echo "=== 5. MAIN FUNCTION CHECK ==="
echo "Checking for main functions:"
find src/$MODULE_NAME -name "*.py" -exec grep -l "def main" {} \;

echo "=== 6. ROS2 ENVIRONMENT ==="
source /opt/ros/kilted/setup.bash
source install/setup.bash

echo "AMENT_PREFIX_PATH: $AMENT_PREFIX_PATH"
echo "Available packages:"
ros2 pkg list | grep v2

echo "Package prefix:"
ros2 pkg prefix $MODULE_NAME 2>/dev/null || echo "Package nicht im ROS2 Index"

popd