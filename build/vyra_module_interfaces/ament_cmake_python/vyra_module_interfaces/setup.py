from setuptools import find_packages
from setuptools import setup

setup(
    name='vyra_module_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('vyra_module_interfaces', 'vyra_module_interfaces.*')),
)
