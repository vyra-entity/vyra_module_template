from setuptools import find_packages, setup

package_name = 'vyra_module_interfaces'

setup(
    version='0.1.0',
    name=package_name,
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/vyra_module_interfaces/msg', [
            'msg/ErrorFeed.msg',
            'msg/LoggerStream.msg',
            'msg/NewsFeed.msg',
            'msg/StateFeed.msg'
        ]),
        ('share/vyra_module_interfaces/srv', [
            'srv/GetCapabilities.srv',
            'srv/GetLogs.srv',
            'srv/HealthCheck.srv',
            'srv/TriggerTransition.srv'
        ]),
        ('share/vyra_module_interfaces/action', [
            'action/InitiateUpdate.action'
        ]),
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='H. Schernewski',
    maintainer_email='vyra.0a1@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    entry_points={
        'console_scripts': [
        ],
    },
)
