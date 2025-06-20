from setuptools import find_packages, setup

package_name = 'vyra_module_template'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='holgder',
    maintainer_email='h.schernewski@variobotic.de',
    description='TODO: Package description',
    license='../../LICENSE.txt',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
