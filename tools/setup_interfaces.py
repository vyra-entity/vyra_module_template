#!/usr/bin/env python3
from __future__ import annotations

import argparse
import sys
import os
import re
import subprocess
import shutil
from pathlib import Path
import xml.etree.ElementTree as ET
import yaml
    
def get_module_name():
    """Auto-detect module name from .module/module_data.yaml or directory name."""
    script_dir = Path(__file__).parent.parent
    
    # Try to read from .module/module_data.yaml
    module_data_file = script_dir / ".module" / "module_data.yaml"
    if module_data_file.exists():
        try:
            import yaml
            with open(module_data_file, 'r') as f:
                data = yaml.safe_load(f)
                if 'name' in data:
                    return data['name']
        except Exception as e:
            print(f"⚠️ Could not read module name from {module_data_file}: {e}")
    
    # Fallback: use directory name (strip hash suffix if present)
    dir_name = script_dir.name
    # Remove hash suffix like _733256b82d6b48a48bc52b5ec73ebfff
    if '_' in dir_name:
        parts = dir_name.split('_')
        # Check if last part looks like a hash (32+ hex chars)
        if len(parts[-1]) >= 32 and all(c in '0123456789abcdef' for c in parts[-1]):
            dir_name = '_'.join(parts[:-1])
    
    return dir_name


def parse_args():
    module_name = get_module_name()
    default_interface_pkg = f"{module_name}_interfaces"
    
    parser = argparse.ArgumentParser(
        description="Script to set up ROS2 interfaces for V.Y.R.A. modules."
    )

    parser.add_argument(
        "--interface_pkg",
        type=str,
        default=default_interface_pkg,
        help=(
            f"Name of the interface package to create or update "
            f"(default: {default_interface_pkg})"
        )
    )
    parser.add_argument(
        "--dynamic_src_path",
        type=Path,
        help=(
            "Path to the temporary source directory for dynamic interface packages."
        )
    )

    return parser.parse_args()

def update_package_xml(package_path: Path):
    """Fügt nötige Dependencies zur package.xml hinzu."""
    pkg_xml_path = package_path / "package.xml"
    
    exec_dependencies = [
        "rclpy",
        "rosidl_default_runtime"
    ]
    build_dependencies = [
        "builtin_interfaces",
        "rosidl_default_generators",
    ]

    for interface_type in ['msg', 'srv', 'action']:
        interface_dir = package_path / interface_type
        
        if interface_dir.exists():
            for file in interface_dir.glob(f'*.{interface_type}'):
                exec_dependencies.append(file.stem)
                build_dependencies.append(file.stem)

    if not pkg_xml_path.exists():
        print(f"⚠️ package.xml nicht gefunden in {pkg_xml_path}")
        return

    tree: ET.ElementTree[ET.Element[str]] = ET.parse(pkg_xml_path)
    root: ET.Element[str] = tree.getroot()

    # Helper, um Dopplungen zu vermeiden
    build_existing = {
        tag.text for tag in root.findall("./*") if tag.tag.endswith('build_depend')}
    
    exec_existing = {
        tag.text for tag in root.findall("./*") if tag.tag.endswith('exec_depend')}
    
    for dep in exec_dependencies:
        if dep not in exec_existing:
            elem = ET.Element("exec_depend")
            elem.text = dep
            root.append(elem)

    for dep in build_dependencies:
        if dep not in build_existing:
            elem = ET.Element("build_depend")
            elem.text = dep
            root.append(elem)
    

    # Save updated XML
    ET.indent(tree, space="\t")
    tree.write(pkg_xml_path, encoding="utf-8", xml_declaration=True)
    print("✓ package.xml aktualisiert.")


def replace_libname_in_file(filepath, old_word, new_word):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    if old_word in content:
        content_new = content.replace(old_word, new_word)
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content_new)
        print(f"Ersetzt in {filepath}")

def collect_interface_files(package_path):
    interface_dirs = ['msg', 'srv', 'action']
    interface_files = {}
    for dir_name in interface_dirs:
        dir_path = os.path.join(package_path, dir_name)
        collected_files = []
        if os.path.isdir(dir_path):
            # Walk through all subdirectories
            for root, _, files in os.walk(dir_path):
                for f in files:
                    if f.endswith(f".{dir_name}"):
                        # Get relative path from package_path
                        rel_path = os.path.relpath(
                            os.path.join(root, f), package_path)
                        collected_files.append(rel_path)
            if collected_files:
                interface_files[dir_name] = collected_files
    return interface_files


def update_CMakefile(interface_package_path: Path, package_name: str):
    interace_files = collect_interface_files(interface_package_path)
    msg_files = interace_files["msg"]
    srv_files = interace_files["srv"]
    action_files = interace_files["action"]

    cmake_path = os.path.join(interface_package_path, "CMakeLists.txt")
    cmake_tmp_path = os.path.join(interface_package_path, "CMakeLists.template.txt")

    # Check if CMakeLists.txt exists otherwise load from CMakeLists.template.txt
    if not os.path.isfile(cmake_path):
        if os.path.isfile(cmake_tmp_path):
            shutil.copyfile(cmake_tmp_path, cmake_path)
            print(f"✓ CMakeLists.txt erstellt aus Vorlage.")
        else:
            print("⚠️ CMakeLists.txt und Vorlage nicht gefunden.")
            return

    # 1. Alle .msg .srv .action Dateien finden
    # msg_files: list[str] = [f for f in os.listdir(msg_dir) if f.endswith(".msg")]
    # srv_files: list[str] = [f for f in os.listdir(srv_dir) if f.endswith(".srv")]
    # action_files: list[str] = [f for f in os.listdir(action_dir) if f.endswith(".action")]

    if not msg_files and not srv_files and not action_files:
        print("⚠️ Keine .msg, .srv oder .action Dateien im Verzeichnis gefunden.")
        return

    # 2. CMakeLists.txt anpassen
    with open(cmake_path, "r") as f:
        cmake_content = f.read()

    # Fix project name to match package.xml
    cmake_content = re.sub(
        r'project\([^)]*\)',
        f'project({package_name})',
        cmake_content
    )
    print(f"✓ CMakeLists.txt: project() set to '{package_name}'.")

    # Ersetze oder ergänze rosidl_generate_interfaces(...)
    rosidl_line = f'rosidl_generate_interfaces(${{PROJECT_NAME}}\n'
    for msg_file in msg_files:
        rosidl_line += f'  "{msg_file}"\n'
    for srv_file in srv_files:
        rosidl_line += f'  "{srv_file}"\n'
    for action_file in action_files:
        rosidl_line += f'  "{action_file}"\n'
    rosidl_line += '\n  DEPENDENCIES std_msgs\n  # Add additional dependencies here\n)\n'

    # Regex: ersetze vorhandene rosidl_generate_interfaces oder füge neu ein
    if "rosidl_generate_interfaces" in cmake_content:
        cmake_content = re.sub(
            r'rosidl_generate_interfaces\([^)]*\)',
            rosidl_line,
            cmake_content,
            flags=re.DOTALL
        )
        print("✓ CMakeLists.txt: rosidl_generate_interfaces() aktualisiert.")
    else:
        # Einfach am Ende hinzufügen
        cmake_content += "\n" + rosidl_line + "\n"
        print("✓ CMakeLists.txt: rosidl_generate_interfaces() hinzugefügt.")

    # Remove all empty lines in cmake_content
    cmake_content = re.sub(r'\n\s*\n', '\n', cmake_content)

    with open(cmake_path, "w") as f:
        f.write(cmake_content)


def update_setup_py(package_path, package_name):
    setup_path = os.path.join(package_path, 'setup.py')
    interface_files = collect_interface_files(package_path)
    
    with open(setup_path, 'r') as f:
        content = f.read()

    data_files_pattern = re.compile(r"data_files\s*=\s*\[\n*", re.DOTALL)
    match = data_files_pattern.search(content)
    
    if not match:
        print("⚠️ Keine data_files-Struktur in setup.py gefunden.")
        raise ValueError("CMakeLists.txt and CMakeLists.template.txt not found.")
    
    data_files_str = match.group(0)

    new_data:dict = {}

    for interface_type, files in interface_files.items():
        key = f'share/{package_name}/{interface_type}'

        if key not in new_data:
            new_data[key] = []
        for f in files:
            if f not in new_data[key]:
                new_data[key].append(f)

    # Generiere den neuen data_files-String
    new_data_files_str = 'data_files=[\n'
    for k, v in new_data.items():
        files_str = ',\n            '.join(f"'{file}'" for file in sorted(v))
        new_data_files_str += f"        ('{k}', [\n            {files_str}\n        ]),\n"

    # Ersetze im Originaltext
    new_content = content.replace(data_files_str, new_data_files_str)

    # Backup erstellen
    # with open(setup_path + '.bak', 'w') as f:
    #     f.write(content)

    # Setup.py überschreiben
    with open(setup_path, 'w') as f:
        f.write(new_content)

    print("✓ setup.py wurde aktualisiert. Originalversion wurde als setup.py.bak gespeichert.")

# def run_wheel_install(wheel_dir):
#     for file in os.listdir(wheel_dir):
#         try:
#             if file.endswith('.whl'):
#                 subprocess.check_call([
#                     sys.executable, 
#                     '-m', 
#                     'pip', 
#                     'install', 
#                     '--break-system-packages', 
#                     os.path.join(wheel_dir, file)
#                 ], stdout=sys.stdout, stderr=sys.stderr)
#         except subprocess.CalledProcessError as e:
#             print(f"Error installing wheel {file}: {e}", file=sys.stderr)
#             sys.exit(1)

def load_default_interfaces(interface_package_name, interface_package_path):
    print(f"Load default interfaces: {interface_package_name}")
    try:
        import vyra_base
    except ImportError:
        raise ImportError(
            "vyra_base not found. Please set the startup environment variable " +
            " in your container (.env) [VYRA_STARTUP_ACTIVE=true] to load all wheels.")

    vyra_base.extract_ros_interfaces(interface_package_path)
    
    # Fix resource marker file: remove old vyra_module_interfaces and create correct one
    resource_dir = interface_package_path / "resource"
    if resource_dir.exists():
        old_marker = resource_dir / "vyra_module_interfaces"
        if old_marker.exists():
            old_marker.unlink()
            print(f"✓ Removed old marker file: {old_marker}")
        
        # Create correct marker file
        correct_marker = resource_dir / interface_package_name
        if not correct_marker.exists():
            correct_marker.touch()
            print(f"✓ Created marker file: {correct_marker}")

def update_dynamic_interfaces(
    interface_package_name, 
    interfaces_src_path: Path,
    interface_target_path: Path
):
    """Loading interfaces from src directory to target package."""
    print(f"Update dynamic interfaces: {interface_package_name}")
    
    source_path = interfaces_src_path
    target_path = interface_target_path
    
    # Copy interface files from source to target
    print(f"Extracting ROS2 interfaces from {source_path} to {target_path}")
    for interface_type in ['msg', 'srv', 'action']:
        source_dir: Path = source_path / interface_type
        target_dir: Path = target_path / interface_type
        
        if source_dir.exists():
            target_dir.mkdir(exist_ok=True)
            for file in source_dir.rglob(f'*.{interface_type}'):
                shutil.copy2(file, target_dir / file.name)
                print(f"Copied {file.name} to {target_dir}")

    config_path: Path = source_path / 'config'
    target_config: Path = target_path / 'config'
    
    if not target_config.exists():
        target_config.mkdir(parents=True, exist_ok=True)
    
    try:
        for type in ['json', 'yaml', 'xml']:
            for file in config_path.glob(f'*.{type}'):
                shutil.copy2(file, target_config)
                print(f"Copied {file.name} to {target_config}")

    finally:
        # Clean up the temporary source directory
        shutil.rmtree(source_path)
    
    # Fix resource marker file: remove old vyra_module_interfaces and create correct one
    resource_dir = target_path / "resource"
    if resource_dir.exists():
        old_marker = resource_dir / "vyra_module_interfaces"
        if old_marker.exists():
            old_marker.unlink()
            print(f"✓ Removed old marker file: {old_marker}")
        
        # Create correct marker file
        correct_marker = resource_dir / interface_package_name
        if not correct_marker.exists():
            correct_marker.touch()
            print(f"✓ Created marker file: {correct_marker}")

    print(f"✓ ROS2 interfaces extracted to {target_path} successfully.")
    
def main(interface_package_name, tmp_src_path=None):
    SELECT_PY_CPP = "cpp"  # oder "py", select based on your needs

    # Workspace setup - detect if we're in container or local development
    script_dir = Path(__file__).parent.parent  # Go up from tools/ to module root
    if script_dir.name.startswith("v2_") or script_dir.name == "vyra_module_template":
        # Local development - we're in the module directory
        workspace_root = script_dir
    else:
        # Container - use /workspace
        workspace_root = Path("/workspace")
    
    interface_package_path: Path = workspace_root / "src" / interface_package_name

    # Check if package already exists
    # Allow any module-specific interface package name (e.g., v2_modulemanager_interfaces, v2_dashboard_interfaces)
    if not interface_package_path.exists():
        # Check if this looks like a module-specific interface package
        if not interface_package_name.endswith("_interfaces"):
            raise FileNotFoundError(
                f"Interface package '{interface_package_name}' not "
                f"found in {workspace_root}/src. "
                "Check your spelling of the package name or create it manually."
            )
    
    interface_package_path.mkdir(exist_ok=True)

    # Load default interfaces for any new module interface package
    if not interface_package_path.exists() or not (interface_package_path / "CMakeLists.txt").exists():
        load_default_interfaces(interface_package_name, interface_package_path)
    else:
        print(f"Update existing interface package: {interface_package_name}")
        # For existing packages, check if there are dynamic interfaces to update
        if tmp_src_path and tmp_src_path.exists():
            update_dynamic_interfaces(
                interface_package_name, 
                tmp_src_path,
                interface_package_path
            )

    print(f"\nUpdate package.xml for {interface_package_name}")
    update_package_xml(interface_package_path)

    print(f"\nUpdate CMakefile for {interface_package_name}")
    update_CMakefile(interface_package_path, interface_package_name)

    interface_files = collect_interface_files(interface_package_path)
    for file_collection in interface_files.values():
        for file in file_collection:
            print(interface_package_path / file)
            replace_libname_in_file(
                interface_package_path / file,
                "vyra_base",
                interface_package_name
            )

    if SELECT_PY_CPP == "py":
        print(f"\nUpdate setup.py for {interface_package_name}")
        update_setup_py(interface_package_path, interface_package_name)
    
    print(f"✓ Package '{interface_package_name}' updated successfully!")


if __name__ == "__main__":
    args = parse_args()
    main(args.interface_pkg, args.dynamic_src_path)