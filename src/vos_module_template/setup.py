import os
import sys
import subprocess

from setuptools import find_packages, setup

package_name = 'vos_module_template'

setup(
    version='0.1.0',
    name=package_name,
    # packages=find_packages(exclude=['test']),
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=[
        'setuptools>=65',
        'vos-base>=0.1.0',
        'vos_module_interfaces>=0.1.0'],
    zip_safe=True,
    maintainer='holgder',
    maintainer_email='h.schernewski@variobotic.de',
    description='TODO: Package description',
    license='../../LICENSE.txt',
    extras_require={"test": ["pytest"]},
    entry_points={
        'console_scripts': [
                'talker = vos_module_template.PublisherNode:main',
                'listener = vos_module_template.SubscriberNode:main',
                'core = vos_module_template.Core:main',
        ],
    },
)
