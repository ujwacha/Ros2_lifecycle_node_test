import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    "generate launch descriptions for the composable node"

    container = ComposableNodeContainer(
        name='tester_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='test_pubsub',
                plugin='test_pubsub::NodeMsgNo',
                name='tester',
                # ..
                extra_arguments=[{'use_intra_process_comms': True}],
            ),
        ],
        output='both',
    )

    return launch.LaunchDescription([container])

    
