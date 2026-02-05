#!/usr/bin/env python3
"""
Proto Interface Setup for V.Y.R.A. Modules

Sets up Protocol Buffer interfaces (.proto files) for cross-module communication.
Generates Python/gRPC code from .proto files for use with Redis and other transports.

Usage:
    python setup_proto_interfaces.py [--interface-pkg MODULE_proto_interfaces]

Features:
    - Auto-detects module name from .module/module_data.yaml
    - Finds .proto files in storage/interfaces/proto/
    - Generates Python code using grpc_tools.protoc
    - Creates install/{module}_proto_interfaces/ structure
    - Prepares for NFS deployment

Example Directory Structure:
    storage/interfaces/proto/
        ├── sensor_service.proto
        ├── actuator_service.proto
        └── config/
            └── proto_callables_meta.json
    
    → Generates:
    install/{module}_proto_interfaces/
        ├── sensor_service_pb2.py
        ├── sensor_service_pb2_grpc.py
        ├── actuator_service_pb2.py
        ├── actuator_service_pb2_grpc.py
        └── config/
            └── proto_callables_meta.json
"""

from __future__ import annotations

import argparse
import sys
import os
import subprocess
import shutil
import json
import logging
from pathlib import Path
import yaml

# Setup logging
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')
logger = logging.getLogger(__name__)

def get_module_name():
    """Auto-detect module name from .module/module_data.yaml or directory name."""
    script_dir = Path(__file__).parent.parent
    
    # Try to read from .module/module_data.yaml
    module_data_file = script_dir / ".module" / "module_data.yaml"
    if module_data_file.exists():
        try:
            with open(module_data_file, 'r') as f:
                data = yaml.safe_load(f)
                if 'name' in data:
                    return data['name']
        except Exception as e:
            logger.warning(f"Could not read module name from {module_data_file}: {e}")
    
    # Fallback: use directory name (strip hash suffix if present)
    dir_name = script_dir.name
    if '_' in dir_name:
        parts = dir_name.split('_')
        # Check if last part looks like a hash (32+ hex chars)
        if len(parts[-1]) >= 32 and all(c in '0123456789abcdef' for c in parts[-1]):
            dir_name = '_'.join(parts[:-1])
    
    return dir_name


def parse_args():
    module_name = get_module_name()
    default_interface_pkg = f"{module_name}_proto_interfaces"
    
    parser = argparse.ArgumentParser(
        description="Script to set up Protocol Buffer interfaces for V.Y.R.A. modules."
    )

    parser.add_argument(
        "--interface-pkg",
        type=str,
        default=default_interface_pkg,
        help=f"Name of the proto interface package to create (default: {default_interface_pkg})"
    )
    
    parser.add_argument(
        "--proto-interface-dir",
        type=Path,
        default=Path("/workspace/storage/interfaces/proto"),
        help="Directory containing .proto files (default: /workspace/storage/interfaces/proto)"
    )
    
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=Path("/workspace/install"),
        help="Output directory for generated interfaces (default: /workspace/install)"
    )

    return parser.parse_args()


def find_proto_files(proto_interface_dir: Path) -> list[Path]:
    """Find all .proto files in the proto interfaces directory."""
    if not proto_interface_dir.exists():
        logger.warning(f"Proto interface directory not found: {proto_interface_dir}")
        return []
    
    proto_files = list(proto_interface_dir.glob("*.proto"))
    logger.info(f"Found {len(proto_files)} .proto file(s)")
    for proto_file in proto_files:
        logger.info(f"   📄 {proto_file.name}")
    
    return proto_files


def generate_python_from_proto(
    proto_file: Path,
    proto_dir: Path,
    output_dir: Path
) -> bool:
    """
    Generate Python code from a .proto file using grpc_tools.protoc.
    
    Args:
        proto_file: Path to .proto file
        proto_dir: Directory containing .proto files (for imports)
        output_dir: Directory for generated Python code
        
    Returns:
        True if successful, False otherwise
    """
    logger.info(f"🔧 Generating Python code for: {proto_file.name}")
    
    try:
        # Build protoc command
        cmd = [
            "python3", "-m", "grpc_tools.protoc",
            f"--proto_path={proto_dir}",
            f"--python_out={output_dir}",
            f"--grpc_python_out={output_dir}",
            f"--pyi_out={output_dir}",  # Type hints
            str(proto_file)
        ]
        
        logger.debug(f"Command: {' '.join(cmd)}")
        
        # Execute protoc
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            check=True
        )
        
        if result.stderr:
            logger.debug(f"stderr: {result.stderr}")
            
        # Verify generated files
        base_name = proto_file.stem
        pb2_file = output_dir / f"{base_name}_pb2.py"
        grpc_file = output_dir / f"{base_name}_pb2_grpc.py"
        
        if pb2_file.exists() and grpc_file.exists():
            # Fix imports in generated grpc file
            fix_grpc_imports(grpc_file, base_name)
            
            logger.info(f"✅ Generated Python:")
            logger.info(f"   • {pb2_file.name}")
            logger.info(f"   • {grpc_file.name}")
            return True
        else:
            logger.error("❌ Expected Python files not generated")
            return False
            
    except subprocess.CalledProcessError as e:
        logger.error(f"❌ Protoc (Python) failed: {e}")
        logger.error(f"   stdout: {e.stdout}")
        logger.error(f"   stderr: {e.stderr}")
        return False
    except Exception as e:
        logger.error(f"❌ Error generating Python proto: {e}")
        return False


def generate_cpp_from_proto(
    proto_file: Path,
    proto_dir: Path,
    output_dir: Path
) -> bool:
    """
    Generate C++ code from a .proto file using protoc.
    
    Args:
        proto_file: Path to .proto file
        proto_dir: Directory containing .proto files (for imports)
        output_dir: Directory for generated C++ code
        
    Returns:
        True if successful, False otherwise
    """
    logger.info(f"🔧 Generating C++ code for: {proto_file.name}")
    
    try:
        # Check if protoc is available
        protoc_check = subprocess.run(
            ["which", "protoc"],
            capture_output=True,
            text=True
        )
        
        if protoc_check.returncode != 0:
            logger.warning("⚠️  protoc not found - skipping C++ generation")
            logger.warning("   Install with: apt-get install protobuf-compiler")
            return False
        
        # Create C++ output directory
        cpp_dir = output_dir / "cpp"
        cpp_dir.mkdir(parents=True, exist_ok=True)
        
        # Build protoc command for C++
        cmd = [
            "protoc",
            f"--proto_path={proto_dir}",
            f"--cpp_out={cpp_dir}",
            f"--grpc_out={cpp_dir}",
            f"--plugin=protoc-gen-grpc=$(which grpc_cpp_plugin)",
            str(proto_file)
        ]
        
        logger.debug(f"Command: {' '.join(cmd)}")
        
        # Execute protoc
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            check=False  # Don't fail if grpc plugin not found
        )
        
        if result.returncode != 0:
            # Try without gRPC plugin
            logger.debug("gRPC C++ plugin not found, generating only messages")
            cmd_minimal = [
                "protoc",
                f"--proto_path={proto_dir}",
                f"--cpp_out={cpp_dir}",
                str(proto_file)
            ]
            
            result = subprocess.run(
                cmd_minimal,
                capture_output=True,
                text=True,
                check=True
            )
        
        if result.stderr:
            logger.debug(f"stderr: {result.stderr}")
            
        # Verify generated files
        base_name = proto_file.stem
        pb_h = cpp_dir / f"{base_name}.pb.h"
        pb_cc = cpp_dir / f"{base_name}.pb.cc"
        
        if pb_h.exists() and pb_cc.exists():
            logger.info(f"✅ Generated C++:")
            logger.info(f"   • {pb_h.name}")
            logger.info(f"   • {pb_cc.name}")
            
            # Check for gRPC files
            grpc_pb_h = cpp_dir / f"{base_name}.grpc.pb.h"
            grpc_pb_cc = cpp_dir / f"{base_name}.grpc.pb.cc"
            if grpc_pb_h.exists() and grpc_pb_cc.exists():
                logger.info(f"   • {grpc_pb_h.name}")
                logger.info(f"   • {grpc_pb_cc.name}")
            
            return True
        else:
            logger.warning("⚠️  C++ files not generated (optional)")
            return False
            
    except subprocess.CalledProcessError as e:
        logger.error(f"❌ Protoc (C++) failed: {e}")
        logger.error(f"   stdout: {e.stdout}")
        logger.error(f"   stderr: {e.stderr}")
        return False
    except Exception as e:
        logger.error(f"❌ Error generating C++ proto: {e}")
        return False


def fix_grpc_imports(grpc_file: Path, base_name: str):
    """Fix imports in generated *_pb2_grpc.py to use relative imports."""
    try:
        content = grpc_file.read_text()
        
        # Replace: import sensor_service_pb2 as sensor__service__pb2
        # With:    from . import sensor_service_pb2 as sensor__service__pb2
        old_import = f"import {base_name}_pb2 as {base_name.replace('.', '_')}__pb2"
        new_import = f"from . import {base_name}_pb2 as {base_name.replace('.', '_')}__pb2"
        
        if old_import in content:
            content = content.replace(old_import, new_import)
            grpc_file.write_text(content)
            logger.debug(f"   ✓ Fixed imports in {grpc_file.name}")
        
    except Exception as e:
        logger.warning(f"Could not fix imports in {grpc_file.name}: {e}")


def copy_config_files(
    proto_interface_dir: Path,
    output_package_dir: Path
):
    """Copy config files (metadata) to output package."""
    config_source = proto_interface_dir / "config"
    config_dest = output_package_dir / "config"
    
    if not config_source.exists():
        logger.info("ℹ️  No config directory found (optional)")
        return
    
    logger.info(f"📋 Copying config files...")
    config_dest.mkdir(parents=True, exist_ok=True)
    
    for config_file in config_source.glob("*.json"):
        shutil.copy2(config_file, config_dest / config_file.name)
        logger.info(f"   • {config_file.name}")


def create_package_init(output_package_dir: Path, interface_pkg_name: str):
    """Create __init__.py for the proto interface package."""
    init_file = output_package_dir / "__init__.py"
    
    init_content = f'''"""
{interface_pkg_name}

Auto-generated Protocol Buffer interfaces for VYRA module communication.
Generated from .proto files using grpc_tools.protoc.
Can be used with Redis, gRPC, or other transports.

Usage:
    from {interface_pkg_name}.sensor_service_pb2 import (
        GetSensorDataRequest,
        GetSensorDataResponse
    )
"""

__all__ = []
'''
    
    init_file.write_text(init_content)
    logger.info(f"✅ Created {init_file.name}")


def main():
    args = parse_args()
    
    logger.info("=== Proto Interface Setup ===")
    logger.info(f"Interface Package: {args.interface_pkg}")
    logger.info(f"Proto Interface Dir: {args.proto_interface_dir}")
    logger.info(f"Output Dir: {args.output_dir}")
    
    # Find .proto files
    proto_files = find_proto_files(args.proto_interface_dir)
    
    if not proto_files:
        logger.info("ℹ️  No .proto files found - Proto interfaces not used by this module")
        sys.exit(0)
    
    # Create output directory
    output_package_dir = args.output_dir / args.interface_pkg
    output_package_dir.mkdir(parents=True, exist_ok=True)
    logger.info(f"📁 Output package: {output_package_dir}")
    
    # Generate Python code from each .proto file
    python_success_count = 0
    cpp_success_count = 0
    
    for proto_file in proto_files:
        logger.info(f"\n🔨 Processing: {proto_file.name}")
        
        # Generate Python
        if generate_python_from_proto(
            proto_file,
            args.proto_interface_dir,
            output_package_dir
        ):
            python_success_count += 1
        
        # Generate C++
        if generate_cpp_from_proto(
            proto_file,
            args.proto_interface_dir,
            output_package_dir
        ):
            cpp_success_count += 1
    
    if python_success_count == 0:
        logger.error("❌ No Python proto files were successfully generated")
        sys.exit(1)
    
    # Copy config files
    copy_config_files(args.proto_interface_dir, output_package_dir)
    
    # Create __init__.py
    create_package_init(output_package_dir, args.interface_pkg)
    
    logger.info(f"\n✅ Proto interface setup complete!")
    logger.info(f"   Python: {python_success_count}/{len(proto_files)} interface(s) generated")
    if cpp_success_count > 0:
        logger.info(f"   C++:    {cpp_success_count}/{len(proto_files)} interface(s) generated")
    else:
        logger.info(f"   C++:    Skipped (protoc not available or failed)")
    logger.info(f"   Package: {output_package_dir}")
    logger.info(f"\nNext steps:")
    logger.info(f"   1. Interfaces will be deployed to NFS at runtime")
    logger.info(f"   2. Python: from {args.interface_pkg} import *")
    logger.info(f"   3. C++: #include \"{args.interface_pkg}/cpp/file.pb.h\"")
    
    sys.exit(0)


if __name__ == "__main__":
    main()
