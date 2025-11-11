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
    
def parse_args():
    parser = argparse.ArgumentParser(
        description="Script to set up ROS2 interfaces for V.Y.R.A. modules."
    )

    parser.add_argument(
        "--interface_pkg",
        type=str,
        default="vyra_module_interfaces",
        help=(
            "Name of the interface package to create or update "
            "(default: vyra_module_interfaces)"
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


def update_CMakefile(interface_package_path: Path):
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

    print(f"✓ ROS2 interfaces extracted to {target_path} successfully.")
    
def main(interface_package_name, tmp_src_path=None):
    SELECT_PY_CPP = "cpp"  # oder "py", select based on your needs

    # Workspace setup
    workspace_root = Path("/workspace")
    interface_package_path: Path = workspace_root / "src" / interface_package_name

    # Check if package already exists
    if (
        not interface_package_path.exists() and 
        interface_package_name != "vyra_module_interfaces"
    ):
        raise FileNotFoundError(
            f"Interface package '{interface_package_name}' not "
            f"found in {workspace_root}/src. "
            "Check your spelling of the package name or create it manually."
        )
    
    interface_package_path.mkdir(exist_ok=True)

    if interface_package_name == "vyra_module_interfaces":
        load_default_interfaces(interface_package_name, interface_package_path)
    else:
        print(f"Update dynamic interface package: {interface_package_name}")
        if tmp_src_path is None or not tmp_src_path.exists():
            raise ValueError(
                "tmp_src_path must be provided for dynamic interface packages."
            )

        update_dynamic_interfaces(
            interface_package_name, 
            tmp_src_path,
            interface_package_path
        )

    print(f"\nUpdate package.xml for {interface_package_name}")
    update_package_xml(interface_package_path)

    print(f"\nUpdate CMakefile for {interface_package_name}")
    update_CMakefile(interface_package_path)

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