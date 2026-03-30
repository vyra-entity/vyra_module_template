#!/usr/bin/env python3
"""
SROS2 Policy Generator
Merges static and dynamic policy XML files into a single policy.xml
"""
import argparse
import xml.etree.ElementTree as ET
from pathlib import Path


def merge_policies(static_path: Path, dynamic_path: Path, output_path: Path):
    """
    Merge static and dynamic SROS2 policy files.
    
    Args:
        static_path: Path to static policy (module's own publish/reply/execute)
        dynamic_path: Path to dynamic policy (wildcards for subscribe/request/call)
        output_path: Output directory for merged policy.xml
    """
    # Parse both XML files
    static_tree = ET.parse(static_path)
    dynamic_tree = ET.parse(dynamic_path)
    
    static_root = static_tree.getroot()
    dynamic_root = dynamic_tree.getroot()
    
    # Create merged policy
    merged_root = ET.Element('policy', attrib={'version': '0.2.0'})
    merged_enclaves = ET.SubElement(merged_root, 'enclaves')
    
    # Get enclave from static policy (should be the same in both)
    static_enclave = static_root.find('.//enclave')
    dynamic_enclave = dynamic_root.find('.//enclave')
    
    if static_enclave is None or dynamic_enclave is None:
        raise ValueError("Both policies must contain an enclave element")
    
    enclave_path = static_enclave.get('path')
    merged_enclave = ET.SubElement(merged_enclaves, 'enclave', attrib={'path': enclave_path})
    merged_profiles = ET.SubElement(merged_enclave, 'profiles')
    
    # Merge profiles
    # 1. Add static profile (specific namespace)
    static_profile = static_enclave.find('.//profile')
    if static_profile is not None:
        merged_profiles.append(static_profile)
    
    # 2. Add dynamic profile (wildcard namespace)
    dynamic_profile = dynamic_enclave.find('.//profile')
    if dynamic_profile is not None:
        merged_profiles.append(dynamic_profile)
    
    # Pretty print with indentation
    indent(merged_root)
    
    # Write to output
    output_path.mkdir(parents=True, exist_ok=True)
    output_file = output_path / 'policy.xml'
    
    tree = ET.ElementTree(merged_root)
    tree.write(output_file, encoding='utf-8', xml_declaration=True)
    
    print(f"✅ Generated SROS2 policy: {output_file}")
    print(f"   - Static rules from: {static_path}")
    print(f"   - Dynamic rules from: {dynamic_path}")


def indent(elem, level=0):
    """Add pretty-printing indentation to XML tree."""
    i = "\n" + level * "  "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "  "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for child in elem:
            indent(child, level + 1)
        if not child.tail or not child.tail.strip():
            child.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i


def main():
    parser = argparse.ArgumentParser(description='Generate SROS2 policy from static and dynamic templates')
    parser.add_argument('--static', type=Path, required=True, help='Path to static policy XML')
    parser.add_argument('--dynamic', type=Path, required=True, help='Path to dynamic policy XML')
    parser.add_argument('--output', type=Path, required=True, help='Output directory for policy.xml')
    
    args = parser.parse_args()
    
    if not args.static.exists():
        print(f"❌ Static policy not found: {args.static}")
        return 1
    
    if not args.dynamic.exists():
        print(f"❌ Dynamic policy not found: {args.dynamic}")
        return 1
    
    try:
        merge_policies(args.static, args.dynamic, args.output)
        return 0
    except Exception as e:
        print(f"❌ Error generating policy: {e}")
        return 1


if __name__ == '__main__':
    exit(main())
