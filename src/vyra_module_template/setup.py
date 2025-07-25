import os
import sys
import subprocess
import glob

from setuptools import find_packages, setup

package_name = 'vyra_module_template'

resource_files = glob.glob('resource/*')

setup(
    version='0.1.0',
    name=package_name,
    # packages=find_packages(exclude=['test']),
    packages=[
        package_name, 
        f"{package_name}.application",
        f"{package_name}.domain",
        f"{package_name}.plugin"],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/resource', resource_files),
    ],
    install_requires=[
        'setuptools>=65',
        'vyra_base>=0.1.0',
        'vyra_module_interfaces>=0.1.0'],
    zip_safe=True,
    maintainer='H. Schernewski',
    maintainer_email='vyra.0a1@gmail.com',
    description='TODO: Package description',
    license='../../LICENSE.txt',
    extras_require={"test": ["pytest"]},
    entry_points={
        'console_scripts': [
                'core = vyra_module_template.ModuleAccess:main',
                'template = vyra_module_template.Template:main',
        ],
    },
)
