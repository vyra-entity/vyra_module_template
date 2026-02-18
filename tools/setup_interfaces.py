#!/usr/bin/env python3

# Short description:
# This script sets up or updates ROS2 interface packages for V.Y.R.A. modules.
# It auto-detects the module name, manages interface files, updates CMakeLists.txt
# and package.xml, and checks for naming conflicts with reserved interface names

from __future__ import annotations

import argparse
import sys
import os
import re
import subprocess
import shutil
import json
import logging
from pathlib import Path
import xml.etree.ElementTree as ET
import yaml

# Setup logging
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')
    
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
        description="Script to set up ROS2 and Proto interfaces for V.Y.R.A. modules.",
        epilog="""
Examples:
  # Build all interfaces (ROS2 + Proto with Python + C++)
  python setup_interfaces.py --all
  
  # Build only ROS2 interfaces
  python setup_interfaces.py --ros2-only
  
  # Build only Proto interfaces (Python + C++)
  python setup_interfaces.py --proto-only
  
  # Build specific interface package
  python setup_interfaces.py --interface_pkg my_custom_interfaces
        """,
        formatter_class=argparse.RawDescriptionHelpFormatter
    )

    parser.add_argument(
        "--interface_pkg",
        type=str,
        default=default_interface_pkg,
        help=(
            f"Name of the ROS2 interface package to create or update "
            f"(default: {default_interface_pkg})"
        )
    )
    
    # Build mode arguments
    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument(
        "--all",
        action="store_true",
        default=False,
        help="Build both ROS2 and Proto interfaces (default if no mode specified)"
    )
    mode_group.add_argument(
        "--ros2-only",
        action="store_true",
        help="Build only ROS2 interfaces (.msg, .srv, .action)"
    )
    mode_group.add_argument(
        "--proto-only",
        action="store_true",
        help="Build only Proto interfaces (.proto) - Python and C++"
    )

    return parser.parse_args()

def update_package_xml(package_path: Path, package_name: str = None):
    """Fügt nötige Dependencies zur package.xml hinzu und updated den package name."""
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

    # Update package name if provided
    if package_name:
        name_elem = root.find("name")
        if name_elem is not None and name_elem.text != package_name:
            print(f"📝 Updating package name from '{name_elem.text}' to '{package_name}'")
            name_elem.text = package_name

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

    # 1. Sammle alle Interface-Dateien
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

    # Setup.py überschreiben
    with open(setup_path, 'w') as f:
        f.write(new_content)

    print("✓ setup.py wurde aktualisiert. Originalversion wurde als setup.py.bak gespeichert.")

def load_reserved_list(vyra_base_path: Path = None) -> dict:
    """
    Load reserved interface names from vyra_base RESERVED.list.
    
    Returns:
        dict: {interface_filename: {'function_name': str, 'config_file': str}}
    """
    try:
        import vyra_base
    except ImportError:
        raise ImportError(
            "vyra_base not found. Please set the startup environment variable " +
            " in your container (.env) [VYRA_STARTUP_ACTIVE=true] to load all wheels.")

    return vyra_base.get_reserved_list()


def has_vyra_base_tag(file_path: Path) -> bool:
    """Check if file has the vyra_base generated tag."""
    try:
        tags = [
            "// Generated by Vyra Copy Script",  # For .proto files
            "# Generated by Vyra Copy Script"     # For .msg, .srv, .action files
        ]
        with open(file_path, 'r') as f:
            first_lines = ''.join([next(f, '') for _ in range(5)])

            return any(tag in first_lines for tag in tags)
    except Exception:
        return False


def check_interface_conflicts(interface_package_path: Path, reserved_interfaces: dict) -> list:
    """
    Check for interface naming conflicts.
    
    Returns:
        list: List of conflict error messages
    """
    errors = []
    interface_dirs = ['msg', 'srv', 'action', 'proto']
    
    for dir_name in interface_dirs:
        dir_path = interface_package_path / dir_name
        if not dir_path.exists():
            continue
        
        # Use appropriate extension
        file_ext = 'proto' if dir_name == 'proto' else dir_name
        
        for file_path in dir_path.glob(f'*.{file_ext}'):
            filename = file_path.name
            
            # Check if file has vyra_base tag - these can always be overwritten
            if has_vyra_base_tag(file_path):
                logging.debug(f"  ✓ {filename} has vyra_base tag, will be overwritten")
                continue
            
            # Check if filename conflicts with reserved names
            if filename in reserved_interfaces:
                reserved_info = reserved_interfaces[filename]
                error_msg = (
                    f"❌ CONFLICT: Interface file '{filename}' conflicts with "
                    f"vyra_base reserved name (function: {reserved_info['function_name']}, "
                    f"source: {reserved_info['config_file']}). "
                    f"Please add '# Generated by Vyra Copy Script' (for .msg/.srv/.action) "
                    f"or '// Generated by Vyra Copy Script' (for .proto) as first line, "
                    f"or rename your interface or remove it."
                )
                errors.append(error_msg)
                logging.error(error_msg)
    
    # Check function name conflicts from metadata
    config_path = interface_package_path / "config"
    if config_path.exists():
        errors.extend(check_function_name_conflicts(config_path, reserved_interfaces))
    
    return errors


def check_function_name_conflicts(config_path: Path, reserved_interfaces: dict) -> list:
    """Check for function name conflicts in metadata JSON files."""
    errors = []
    reserved_functions = {
        info['function_name']: name 
        for name, info in reserved_interfaces.items() 
        if info['function_name']
    }
    
    for json_file in config_path.glob('*_meta.json'):
        try:
            with open(json_file, 'r') as f:
                data = json.load(f)
            
            if isinstance(data, list):
                for item in data:
                    if 'functionname' in item:
                        func_name = item['functionname']
                        if func_name in reserved_functions:
                            # Get the interface filename associated with this reserved function
                            reserved_interface_filename = reserved_functions[func_name]
                            
                            # Check if the interface file exists and has vyra_base tag
                            interface_parent_path = config_path.parent
                            interface_file_found = False
                            has_tag = False
                            
                            for interface_type in ['msg', 'srv', 'action', 'proto']:
                                interface_file = interface_parent_path / interface_type / reserved_interface_filename
                                if interface_file.exists():
                                    interface_file_found = True
                                    has_tag = has_vyra_base_tag(interface_file)
                                    break
                            
                            # Only report conflict if:
                            # 1. Interface file EXISTS in module (interface_file_found = True)
                            # 2. AND it does NOT have vyra_base tag (has_tag = False)
                            # If file doesn't exist, it will be copied from vyra_base -> no conflict
                            if interface_file_found and not has_tag:
                                error_msg = (
                                    f"❌ CONFLICT: Function name '{func_name}' in {json_file.name} "
                                    f"conflicts with vyra_base reserved function "
                                    f"(interface: {reserved_functions[func_name]}). "
                                    f"The file {reserved_interface_filename} exists but is missing the vyra_base tag. "
                                    f"Please add '# Generated by Vyra Copy Script' or '// Generated by Vyra Copy Script' as first line, "
                                    f"or rename your function."
                                )
                                errors.append(error_msg)
                                logging.error(error_msg)
                            elif interface_file_found and has_tag:
                                logging.debug(f"  ✓ Function '{func_name}' is linked to vyra_base interface {reserved_interface_filename}, no conflict")
                            else:
                                # File doesn't exist yet - will be copied from vyra_base
                                logging.debug(f"  ✓ Function '{func_name}' uses vyra_base interface {reserved_interface_filename} (will be auto-copied)")
        except Exception as e:
            logging.warning(f"Could not parse {json_file.name}: {e}")
    
    return errors


def load_default_interfaces(interface_package_name, interface_package_path):
    print(f"Load default interfaces: {interface_package_name}")
    try:
        import vyra_base
    except ImportError:
        raise ImportError(
            "vyra_base not found. Please set the startup environment variable " +
            " in your container (.env) [VYRA_STARTUP_ACTIVE=true] to load all wheels.")

    vyra_base.extract_interfaces(interface_package_path)
    
    # Fix resource marker file: remove old {{ module_name }}_interfaces and create correct one
    resource_dir = interface_package_path / "resource"
    if resource_dir.exists():
        old_marker = resource_dir / "{{ module_name }}_interfaces"
        if old_marker.exists():
            old_marker.unlink()
            print(f"✓ Removed old marker file: {old_marker}")
        
        # Create correct marker file
        correct_marker = resource_dir / interface_package_name
        if not correct_marker.exists():
            correct_marker.touch()
            print(f"✓ Created marker file: {correct_marker}")

def add_header_to_proto_file(proto_file_path: Path):
    """
    Add 'Generated by Vyra Copy Script' header to .proto file if not already present.
    
    Args:
        proto_file_path: Path to the .proto file
    """
    header = "// Generated by Vyra Copy Script\n"
    
    try:
        with open(proto_file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Check if header already exists
        if "Generated by Vyra Copy Script" not in content:
            # Add header at the beginning
            with open(proto_file_path, 'w', encoding='utf-8') as f:
                f.write(header + content)
            print(f"✓ Added header to {proto_file_path.name}")
    except Exception as e:
        print(f"⚠️ Could not add header to {proto_file_path}: {e}")


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
    print(f"Extracting interfaces from {source_path} to {target_path}")
    for interface_type in ['msg', 'srv', 'action', 'proto']:
        source_dir: Path = source_path / interface_type
        target_dir: Path = target_path / interface_type
        
        if source_dir.exists():
            target_dir.mkdir(exist_ok=True)
            # Proto files use .proto extension, others use directory name
            file_ext = 'proto' if interface_type == 'proto' else interface_type
            for file in source_dir.rglob(f'*.{file_ext}'):
                shutil.copy2(file, target_dir / file.name)
                print(f"Copied {file.name} to {target_dir}")
                
                # Add header to .proto files
                if interface_type == 'proto':
                    target_file = target_dir / file.name
                    add_header_to_proto_file(target_file)

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
    
    # Fix resource marker file: remove old {{ module_name }}_interfaces and create correct one
    resource_dir = target_path / "resource"
    if resource_dir.exists():
        old_marker = resource_dir / "{{ module_name }}_interfaces"
        if old_marker.exists():
            old_marker.unlink()
            print(f"✓ Removed old marker file: {old_marker}")
        
        # Create correct marker file
        correct_marker = resource_dir / interface_package_name
        if not correct_marker.exists():
            correct_marker.touch()
            print(f"✓ Created marker file: {correct_marker}")

    print(f"✓ ROS2 interfaces extracted to {target_path} successfully.")


# === Proto Interface Functions ===

def find_proto_files(proto_interface_dir: Path) -> list[Path]:
    """Find all .proto files in the proto interfaces directory."""
    if not proto_interface_dir.exists():
        logging.warning(f"Proto interface directory not found: {proto_interface_dir}")
        return []
    proto_files = list(proto_interface_dir.glob("*.proto"))
    logging.info(f"Found {len(proto_files)} .proto file(s)")
    for proto_file in proto_files:
        logging.info(f"   📄 {proto_file.name}")
    return proto_files


def generate_python_from_proto(proto_file: Path, proto_dir: Path, output_dir: Path) -> bool:
    """Generate Python code from a .proto file using grpc_tools.protoc."""
    logging.info(f"🔧 Generating Python code for: {proto_file.name}")
    try:
        cmd = [
            "python3", "-m", "grpc_tools.protoc",
            f"--proto_path={proto_dir}",
            f"--python_out={output_dir}",
            f"--grpc_python_out={output_dir}",
            f"--pyi_out={output_dir}",
            str(proto_file)
        ]
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        base_name = proto_file.stem
        pb2_file = output_dir / f"{base_name}_pb2.py"
        grpc_file = output_dir / f"{base_name}_pb2_grpc.py"
        if pb2_file.exists() and grpc_file.exists():
            logging.info(f"✅ Generated Python: {pb2_file.name}, {grpc_file.name}")
            return True
        else:
            logging.error("❌ Expected Python files not generated")
            return False
    except Exception as e:
        logging.error(f"❌ Error generating Python proto: {e}")
        return False


def generate_cpp_from_proto(proto_file: Path, proto_dir: Path, output_dir: Path) -> bool:
    """Generate C++ code from a .proto file using protoc."""
    logging.info(f"🔧 Generating C++ code for: {proto_file.name}")
    try:
        protoc_check = subprocess.run(["which", "protoc"], capture_output=True, text=True)
        if protoc_check.returncode != 0:
            logging.warning("⚠️  protoc not found - skipping C++ generation")
            return False
        cpp_dir = output_dir / "cpp"
        cpp_dir.mkdir(parents=True, exist_ok=True)
        cmd = [
            "protoc",
            f"--proto_path={proto_dir}",
            f"--cpp_out={cpp_dir}",
            f"--grpc_out={cpp_dir}",
            f"--plugin=protoc-gen-grpc=$(which grpc_cpp_plugin)",
            str(proto_file)
        ]
        result = subprocess.run(cmd, capture_output=True, text=True, check=False)
        base_name = proto_file.stem
        pb_h = cpp_dir / f"{base_name}.pb.h"
        pb_cc = cpp_dir / f"{base_name}.pb.cc"
        if pb_h.exists() and pb_cc.exists():
            logging.info(f"✅ Generated C++: {pb_h.name}, {pb_cc.name}")
            return True
        else:
            logging.warning("⚠️  C++ files not generated (optional)")
            return False
    except Exception as e:
        logging.error(f"❌ Error generating C++ proto: {e}")
        return False


def copy_proto_config_files(proto_interface_dir: Path, output_package_dir: Path):
    """Copy config files (metadata) to output package."""
    # Config files are in interfaces/config, not interfaces/proto/config
    interfaces_dir = proto_interface_dir.parent
    config_source = interfaces_dir / "config"
    config_dest = output_package_dir / "config"
    
    # Skip if source and dest are the same directory
    if config_source.resolve() == config_dest.resolve():
        logging.info("ℹ️  Config files already in place (same directory)")
        return
        
    if not config_source.exists():
        logging.info("ℹ️  No config directory found (optional)")
        return
    logging.info(f"📋 Copying config files from {config_source}...")
    config_dest.mkdir(parents=True, exist_ok=True)
    for config_file in config_source.glob("*.json"):
        dest_file = config_dest / config_file.name
        if dest_file.exists() and dest_file.samefile(config_file):
            continue  # Skip if source and dest are the same file
        shutil.copy2(config_file, dest_file)
        logging.info(f"   • {config_file.name}")


def create_proto_package_init(output_package_dir: Path, interface_pkg_name: str):
    """Create __init__.py for the proto interface package."""
    init_file = output_package_dir / "__init__.py"
    init_content = f'''"""\n{interface_pkg_name}\nAuto-generated Protocol Buffer interfaces for VYRA module communication.\nGenerated from .proto files using grpc_tools.protoc.\nCan be used with Redis, gRPC, or other transports.\n"""\n__all__ = []\n'''
    init_file.write_text(init_content)
    logging.info(f"✅ Created {init_file.name}")


def build_proto_interfaces(interface_package_path: Path, module_name: str):
    """Build proto interfaces for the module."""
    try:
        script_dir = Path(__file__).parent.parent
        proto_interface_dir = script_dir / "storage" / "interfaces" / "proto"
        output_dir = interface_package_path
        interface_pkg = f"{module_name}_proto_interfaces"

        if not proto_interface_dir.exists():
            logging.warning(f"⚠️  Proto interface directory not found: {proto_interface_dir}")
            logging.info("ℹ️  Skipping proto interface generation")
            return
        
        logging.info(f"📁 Proto source: {proto_interface_dir}")
        logging.info(f"📁 Output: {output_dir}")
        proto_files = find_proto_files(proto_interface_dir)
        
        if not proto_files:
            logging.info("ℹ️  No .proto files found - skipping proto generation")
            return
        
        python_success_count = 0
        cpp_success_count = 0
        for proto_file in proto_files:
            logging.info(f"\n🔨 Processing: {proto_file.name}")
            if generate_python_from_proto(proto_file, proto_interface_dir, output_dir):
                python_success_count += 1
            if generate_cpp_from_proto(proto_file, proto_interface_dir, output_dir):
                cpp_success_count += 1
        
        if python_success_count == 0 and len(proto_files) > 0:
            logging.error("❌ No Python proto files were successfully generated")
        
        copy_proto_config_files(proto_interface_dir, output_dir)
        create_proto_package_init(output_dir, interface_pkg)
        
        logging.info(f"\n✅ Proto interface setup complete!")
        logging.info(f"   Python: {python_success_count}/{len(proto_files)} interface(s) generated")
        if cpp_success_count > 0:
            logging.info(f"   C++:    {cpp_success_count}/{len(proto_files)} interface(s) generated")
        else:
            logging.info(f"   C++:    Skipped (protoc not available or failed)")
        logging.info(f"   Package: {output_dir}")
    except Exception as e:
        logging.error(f"❌ Failed to build proto interfaces: {e}")
        logging.info("ℹ️  Continuing without proto interfaces (non-critical)")


# === Main Function ===

def main(interface_package_name, tmp_src_path=None):
    SELECT_PY_CPP = "cpp"  # oder "py", select based on your needs

    # Workspace setup - detect if we're in container or local development
    script_dir = Path(__file__).parent.parent  # Go up from tools/ to module root
    if script_dir.name.startswith("v2_") or script_dir.name == "{{ module_name }}":
        # Local development - we're in the module directory
        workspace_root = script_dir
    else:
        # Container - use /workspace
        workspace_root = Path("/workspace")
    
    interface_package_path: Path = workspace_root / "src" / interface_package_name

    # Load reserved interface names from vyra_base
    logging.info("Checking for interface naming conflicts with vyra_base...")
    reserved_interfaces = load_reserved_list()
    
    # Check for conflicts BEFORE processing
    conflicts = check_interface_conflicts(interface_package_path, reserved_interfaces)
    if conflicts:
        logging.error("\n" + "="*70)
        logging.error("❌ INTERFACE NAMING CONFLICTS DETECTED")
        logging.error("="*70)
        for error in conflicts:
            logging.error(error)
        logging.error("="*70)
        logging.error("\nPlease resolve these conflicts before continuing.")
        logging.error("Files with '# Generated by Vyra Copy Script' tag will be automatically overwritten.")
        sys.exit(1)
    else:
        logging.info("✓ No interface naming conflicts detected")

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

    # Always load/update default interfaces from vyra_base to ensure all base interfaces are present
    # This will copy any missing interfaces and update existing ones that have the vyra_base tag
    cmake_exists = (interface_package_path / "CMakeLists.txt").exists()
    
    if cmake_exists:
        logging.info(f"📥 Updating interfaces from vyra_base (existing package)...")
    else:
        logging.info(f"📥 Loading default interfaces from vyra_base (new package)...")
    
    load_default_interfaces(interface_package_name, interface_package_path)
    
    # For existing packages, also check if there are dynamic interfaces to update
    if tmp_src_path and tmp_src_path.exists():
        update_dynamic_interfaces(
                interface_package_name, 
                tmp_src_path,
                interface_package_path
            )

    print(f"\nUpdate package.xml for {interface_package_name}")
    update_package_xml(interface_package_path, interface_package_name)

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

    # Build proto interfaces directly (integrated)
    try:
        # Import proto functions
        # --- Begin proto integration ---
        def find_proto_files(proto_interface_dir: Path) -> list[Path]:
            if not proto_interface_dir.exists():
                logging.warning(f"Proto interface directory not found: {proto_interface_dir}")
                return []
            proto_files = list(proto_interface_dir.glob("*.proto"))
            logging.info(f"Found {len(proto_files)} .proto file(s)")
            for proto_file in proto_files:
                logging.info(f"   📄 {proto_file.name}")
            return proto_files

        def generate_python_from_proto(proto_file: Path, proto_dir: Path, output_dir: Path) -> bool:
            logging.info(f"🔧 Generating Python code for: {proto_file.name}")
            try:
                cmd = [
                    "python3", "-m", "grpc_tools.protoc",
                    f"--proto_path={proto_dir}",
                    f"--python_out={output_dir}",
                    f"--grpc_python_out={output_dir}",
                    f"--pyi_out={output_dir}",
                    str(proto_file)
                ]
                result = subprocess.run(cmd, capture_output=True, text=True, check=True)
                base_name = proto_file.stem
                pb2_file = output_dir / f"{base_name}_pb2.py"
                grpc_file = output_dir / f"{base_name}_pb2_grpc.py"
                if pb2_file.exists() and grpc_file.exists():
                    logging.info(f"✅ Generated Python: {pb2_file.name}, {grpc_file.name}")
                    return True
                else:
                    logging.error("❌ Expected Python files not generated")
                    return False
            except Exception as e:
                logging.error(f"❌ Error generating Python proto: {e}")
                return False

        def generate_cpp_from_proto(proto_file: Path, proto_dir: Path, output_dir: Path) -> bool:
            logging.info(f"🔧 Generating C++ code for: {proto_file.name}")
            try:
                protoc_check = subprocess.run(["which", "protoc"], capture_output=True, text=True)
                if protoc_check.returncode != 0:
                    logging.debug("protoc not found - C++ generation skipped")
                    return False
                
                # Check for grpc_cpp_plugin
                grpc_plugin_check = subprocess.run(["which", "grpc_cpp_plugin"], capture_output=True, text=True)
                if grpc_plugin_check.returncode != 0:
                    logging.debug("grpc_cpp_plugin not found - C++ generation skipped")
                    return False
                    
                cpp_dir = output_dir / "cpp"
                cpp_dir.mkdir(parents=True, exist_ok=True)
                cmd = [
                    "protoc",
                    f"--proto_path={proto_dir}",
                    f"--cpp_out={cpp_dir}",
                    f"--grpc_out={cpp_dir}",
                    f"--plugin=protoc-gen-grpc={grpc_plugin_check.stdout.strip()}",
                    str(proto_file)
                ]
                result = subprocess.run(cmd, capture_output=True, text=True, check=True)
                base_name = proto_file.stem
                pb_h = cpp_dir / f"{base_name}.pb.h"
                pb_cc = cpp_dir / f"{base_name}.pb.cc"
                if pb_h.exists() and pb_cc.exists():
                    logging.info(f"✅ Generated C++: {pb_h.name}, {pb_cc.name}")
                    return True
                else:
                    logging.debug("C++ files not generated")
                    return False
            except subprocess.CalledProcessError as e:
                logging.debug(f"C++ proto generation failed: {e.stderr if e.stderr else str(e)}")
                return False
            except Exception as e:
                logging.debug(f"C++ proto generation error: {e}")
                return False

        def copy_config_files(proto_interface_dir: Path, output_package_dir: Path):
            # Config files are in interfaces/config, not interfaces/proto/config
            interfaces_dir = proto_interface_dir.parent
            config_source = interfaces_dir / "config"
            config_dest = output_package_dir / "config"
            
            # Skip if source and dest are the same directory
            if config_source.resolve() == config_dest.resolve():
                logging.info("ℹ️  Config files already in place (same directory)")
                return
                
            if not config_source.exists():
                logging.info("ℹ️  No config directory found (optional)")
                return
            logging.info(f"📋 Copying config files from {config_source}...")
            config_dest.mkdir(parents=True, exist_ok=True)
            for config_file in config_source.glob("*.json"):
                dest_file = config_dest / config_file.name
                if dest_file.exists() and dest_file.samefile(config_file):
                    continue  # Skip if source and dest are the same file
                shutil.copy2(config_file, dest_file)
                logging.info(f"   • {config_file.name}")

        def create_package_init(output_package_dir: Path, interface_pkg_name: str):
            init_file = output_package_dir / "__init__.py"
            
            # Skip if file already exists (might be read-only)
            if init_file.exists():
                logging.info(f"ℹ️  {init_file.name} already exists, skipping")
                return
                
            init_content = f'''"""
{interface_pkg_name}
Auto-generated Protocol Buffer interfaces for VYRA module communication.
Generated from .proto files using grpc_tools.protoc.
Can be used with Redis, gRPC, or other transports.
"""
__all__ = []
'''
            try:
                init_file.write_text(init_content)
                logging.info(f"✅ Created {init_file.name}")
            except PermissionError as e:
                logging.warning(f"⚠️  Could not create {init_file.name}: {e}")
        # --- End proto integration ---

        # Proto files are extracted by vyra_base.extract_interfaces() to interface_package_path/proto
        # Config files are extracted to interface_package_path/config
        proto_interface_dir = interface_package_path / "proto"
        # Generated proto files go to generated_proto/py and generated_proto/cpp subdirectories
        python_output_dir = interface_package_path / "generated_proto" / "py"
        cpp_output_dir = interface_package_path / "generated_proto" / "cpp"
        python_output_dir.mkdir(parents=True, exist_ok=True)
        cpp_output_dir.mkdir(parents=True, exist_ok=True)
        interface_pkg = f"{module_name}_proto_interfaces"

        if not proto_interface_dir.exists():
            logging.warning(f"⚠️  Proto interface directory not found: {proto_interface_dir}")
            logging.info("ℹ️  Skipping proto interface generation (no proto files in vyra_base)")
        else:
            logging.info(f"📁 Proto source: {proto_interface_dir}")
            logging.info(f"📁 Python output: {python_output_dir}")
            logging.info(f"📁 C++ output: {cpp_output_dir}")
            proto_files = find_proto_files(proto_interface_dir)
            
            if len(proto_files) == 0:
                logging.info("ℹ️  No .proto files found, skipping proto generation")
            else:
                python_success_count = 0
                cpp_success_count = 0
                for proto_file in proto_files:
                    logging.info(f"\n🔨 Processing: {proto_file.name}")
                    if generate_python_from_proto(proto_file, proto_interface_dir, python_output_dir):
                        python_success_count += 1
                    if generate_cpp_from_proto(proto_file, proto_interface_dir, cpp_output_dir):
                        cpp_success_count += 1
                if python_success_count == 0:
                    logging.error("❌ No Python proto files were successfully generated")
                else:
                    logging.info(f"\n✅ Proto interface setup complete!")
                    logging.info(f"   Python: {python_success_count}/{len(proto_files)} interface(s) generated")
                    if cpp_success_count > 0:
                        logging.info(f"   C++:    {cpp_success_count}/{len(proto_files)} interface(s) generated")
                    else:
                        logging.info(f"   C++:    Skipped (protoc not available or failed)")
                    logging.info(f"   Package: {python_output_dir}")
            
            # Config files go to interface_package_path/config (one level above generated_proto)
            copy_config_files(proto_interface_dir, interface_package_path)
            create_package_init(python_output_dir, interface_pkg)
    except Exception as e:
        logging.error(f"❌ Failed to build proto interfaces: {e}")
        logging.info("ℹ️  Continuing without proto interfaces (non-critical)")

if __name__ == "__main__":
    args = parse_args()
    
    # Determine build mode
    build_ros2 = True
    build_proto = True
    
    if args.ros2_only:
        build_ros2 = True
        build_proto = False
        logging.info("🔧 Mode: ROS2 interfaces only")
    elif args.proto_only:
        build_ros2 = False
        build_proto = True
        logging.info("🔧 Mode: Proto interfaces only")
    elif args.all:
        build_ros2 = True
        build_proto = True
        logging.info("🔧 Mode: All interfaces (ROS2 + Proto)")
    else:
        # Default: build all
        build_ros2 = True
        build_proto = True
        logging.info("🔧 Mode: All interfaces (ROS2 + Proto) [default]")
    
    # Build ROS2 interfaces
    if build_ros2:
        logging.info("\n" + "="*70)
        logging.info("📦 Building ROS2 Interfaces")
        logging.info("="*70)
        main(args.interface_pkg)
        logging.info("✅ ROS2 interfaces built successfully")
    
    # Proto interfaces are now built as part of main() when build_ros2 is True
    # or when build_proto is True (proto-only mode)
    if build_proto and not build_ros2:
        logging.info("\n" + "="*70)
        logging.info("📦 Building Proto Interfaces Only")
        logging.info("="*70)
        # Run main() which will now only process proto files
        main(args.interface_pkg)
        logging.info("✅ Proto interfaces built successfully")
    
    logging.info("\n" + "="*70)
    logging.info("✅ Interface setup complete!")
    logging.info("="*70)
    if build_ros2:
        logging.info(f"   ROS2: {args.interface_pkg}")
    if build_proto:
        module_name = get_module_name()
        logging.info(f"   Proto: {module_name}_proto_interfaces (Python + C++)")
    logging.info("="*70)