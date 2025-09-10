#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/vyra_module_template/tools/debug_executables.sh

pushd /workspace

echo "=== 1. DIRECTORY STRUCTURE ==="
echo "Source structure:"
find src/vyra_module_template -name "*.py" | head -10

echo -e "\nInstall structure:"
ls -la install/vyra_module_template/ 2>/dev/null || echo "install/vyra_module_template nicht gefunden"

echo -e "\nBin directory:"
ls -la install/vyra_module_template/bin/ 2>/dev/null || echo "bin/ Verzeichnis nicht gefunden"

echo "=== 2. SETUP.PY CONTENT ==="
echo "Entry points in setup.py:"
grep -A 10 "entry_points" src/vyra_module_template/setup.py || echo "Keine entry_points gefunden"

echo "=== 3. PACKAGE.XML ==="
cat src/vyra_module_template/package.xml | grep -E "(name|build_type)" || echo "package.xml Problem"

echo "=== 4. PYTHON MODULE CHECK ==="
echo "Python Module importierbar?"
python3 -c "
import sys
sys.path.insert(0, '/workspace/install/vyra_module_template/lib/python3.11/site-packages')
try:
    import vyra_module_template
    print('✅ Module importiert')
    print(f'Module path: {vyra_module_template.__file__}')
    if hasattr(vyra_module_template, 'main'):
        print('✅ main() Funktion gefunden')
    else:
        print('❌ main() Funktion nicht gefunden')
except Exception as e:
    print(f'❌ Import error: {e}')
"

echo "=== 5. MAIN FUNCTION CHECK ==="
echo "Checking for main functions:"
find src/vyra_module_template -name "*.py" -exec grep -l "def main" {} \;

echo "=== 6. ROS2 ENVIRONMENT ==="
source /opt/ros/kilted/setup.bash
source install/setup.bash

echo "AMENT_PREFIX_PATH: $AMENT_PREFIX_PATH"
echo "Available packages:"
ros2 pkg list | grep v2

echo "Package prefix:"
ros2 pkg prefix vyra_module_template 2>/dev/null || echo "Package nicht im ROS2 Index"

popd