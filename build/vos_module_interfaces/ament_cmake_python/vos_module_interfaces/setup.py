from setuptools import find_packages
from setuptools import setup

setup(
    name='vos_module_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('vos_module_interfaces', 'vos_module_interfaces.*')),
)
