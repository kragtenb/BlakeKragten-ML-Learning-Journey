# ~/ros2_ws/src/robot_arm/setup.py

from setuptools import setup
from glob import glob
import os

package_name = 'robot_arm'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Blake Kragten',
    maintainer_email='kragtenb@gmail.com',
    description='Robot arm project.',
    license='Your license',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'camera_node = robot_arm.camera_node:main',
            'distance_node = robot_arm.distance_node:main',
            'wifi_image_sender = robot_arm.wifi_image_sender_node:main',
            'bluetooth_node = robot_arm.bluetooth_node:main',
            'servo_node = robot_arm.servo_node:main',
        ],
    },
)
