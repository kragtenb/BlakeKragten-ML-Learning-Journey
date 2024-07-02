# ~/ros2_ws/src/robot_arm/launch/robot_arm_launch.py

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='robot_arm',
            executable='camera_node.py',
            name='camera_node',
            output='screen'
        ),
        Node(
            package='robot_arm',
            executable='distance_node.py',
            name='distance_node',
            output='screen'
        ),
        Node(
            package='robot_arm',
            executable='wifi_image_sender_node.py',
            name='wifi_image_sender_node',
            output='screen'
        ),
        Node(
            package='robot_arm',
            executable='bluetooth_node',
            name='bluetooth_node',
            output='screen'
        ),
        Node(
            package='robot_arm',
            executable='servo_node',
            name='servo_node',
            output='screen'
        ),
    ])
