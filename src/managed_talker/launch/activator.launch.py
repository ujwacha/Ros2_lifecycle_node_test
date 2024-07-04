from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    return LaunchDescription([
        Node(
            package='managed_talker',
            executable='all_activator_exec',
            parameters=[
                {"lifecycles_list": ["talker", "listener"]}
#                {"lifecycles_list": ["talker", "listener" ]}
            ],
            output='screen',
            emulate_tty=True
        )
    ])
