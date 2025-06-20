#!/usr/bin/env python3
import sys
import os
import re
import shutil
import subprocess
from pathlib import Path
from turtle import update
import xml.etree.ElementTree as ET

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
        if os.path.isdir(dir_path):
            files = [f"{dir_name}/{f}" for f in os.listdir(dir_path) if f.endswith(f".{dir_name}")]
            if files:
                interface_files[dir_name] = files
    return interface_files


def update_CMakefile(package_path: Path):
    interace_files = collect_interface_files(package_path)
    msg_files = interace_files["msg"]
    srv_files = interace_files["srv"]
    action_files = interace_files["action"]

    cmake_path = os.path.join(package_path, "CMakeLists.txt")

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
        return
    
    data_files_str = match.group(0)

    new_data:dict = {}

    for interface_type, files in interface_files.items():
        key = f'share/{package_name}/{interface_type}'
        if key in content:
            print(
                f"⚠️ Info: {key} already exists in file, "
                "do not overwrite. Please remove manually "
                "if you want to update.")
            continue
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
    with open(setup_path + '.bak', 'w') as f:
        f.write(content)

    # Setup.py überschreiben
    with open(setup_path, 'w') as f:
        f.write(new_content)

    print("✓ setup.py wurde aktualisiert. Originalversion wurde als setup.py.bak gespeichert.")

def run_wheel_install(wheel_dir):
    for file in os.listdir(wheel_dir):
        try:
            if file.endswith('.whl'):
                subprocess.check_call([
                    sys.executable, 
                    '-m', 
                    'pip', 
                    'install', 
                    '--break-system-packages', 
                    os.path.join(wheel_dir, file)
                ], stdout=sys.stdout, stderr=sys.stderr)
        except subprocess.CalledProcessError as e:
            print(f"Error installing wheel {file}: {e}", file=sys.stderr)
            sys.exit(1)

def derive_package_name_from_pip(pip_package_name):
    """Leitet ROS2 Package-Namen vom pip Package-Namen ab"""
    # Konventionen für die Umwandlung
    ros_name = pip_package_name.replace('-', '_').replace('_', '_')
    
    # # Füge _interfaces suffix hinzu falls nicht vorhanden
    # if not ros_name.endswith('_interfaces'):
    #     ros_name += '_interfaces'
    
    return ros_name

def main():
    SELECT_PY_CPP = "py"

    try:
        import vyra_base
    except ImportError:
        print("vyra_base not found. Will be installed from wheel.")

        run_wheel_install(Path(__file__).parent.parent / "wheels")
        import vyra_base
        
    # User kann überschreiben
    # package_name = input(f"V.Y.R.A. module name: ").strip()
    interface_package_name = "vyra_module_interfaces"
    # Workspace setup
    workspace_root = Path(__file__).parent.parent
    interface_package_path: Path = workspace_root / "src" / interface_package_name
    interface_package_path.mkdir(exist_ok=True)

    print(f"\nAdd default interfaces: {interface_package_name}")
    vyra_base.extract_ros_interfaces(interface_package_path)

    if SELECT_PY_CPP == "py":
        print(f"\nUpdate package.xml for {interface_package_name}")
        update_package_xml(interface_package_path)
    elif SELECT_PY_CPP == "cpp":
        pass
        # here cpp specific setup code
    else:
        print("Invalid selection. Please choose 'py' or 'cpp'.")
        sys.exit(1)

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

    print(f"\nUpdate setup.py for {interface_package_name}")
    update_setup_py(interface_package_path, interface_package_name)
    
    print(f"✓ Package '{interface_package_name}' updated successfully!")

    package_name = "vyra_module_template"
    # Workspace setup    
    


if __name__ == "__main__":
    main()