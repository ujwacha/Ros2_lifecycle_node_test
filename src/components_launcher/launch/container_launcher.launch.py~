import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    "generate launch descriptions for the composable node"

    container = ComposableNodeContainer(
        name='tester_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container_mt',
        composable_node_descriptions=[
            ComposableNode(
                package='component_practice',
                plugin='component_practice::PraPub',
                name='talker',
                # ..
                extra_arguments=[{'use_intra_process_comms': True}],
            ),

            ComposableNode(
                package='listener_com',
                plugin='listener_com::MinimalSubscriber',
                name='listener',
                # ..
                extra_arguments=[{'use_intra_process_comms': True}],
            ),

            ComposableNode(
                package='managed_talker',
                plugin='managed_talker::Life_Talker',
                name='lifetalker',
                # ..
                extra_arguments=[{'use_intra_process_comms': True}],
            ),

            # ComposableNode(
            #     package='managed_talker',
            #     plugin='managed_talker::LifeActivator',
            #     name='lifeactivator',
            #     parameters=[
            #         {"lifecycles_list": ["talker", "listener", "lifetalker"]}
            #         #                {"lifecycles_list": ["talker", "listener" ]}
            #     ],
            #     # ..
            #     extra_arguments=[{'use_intra_process_comms': True}],
            # ),



        ],
        output='both',
    )

    return launch.LaunchDescription([container])

    
