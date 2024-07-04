from launch_ros.actions import Node

from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, EmitEvent, ExecuteProcess,
                            LogInfo, RegisterEventHandler, TimerAction)
from launch.conditions import IfCondition
from launch.event_handlers import (OnExecutionComplete, OnProcessExit,
                                OnProcessIO, OnProcessStart, OnShutdown)
from launch.events import Shutdown
from launch.substitutions import (EnvironmentVariable, FindExecutable,
                                LaunchConfiguration, LocalSubstitution,
                                PythonExpression)


def generate_launch_description():
    turtlesim_node = Node(
        package='turtlesim',
        executable='turtlesim_node',
        name='sim'
    )

    teleop_key = Node(
        package='turtlesim',
        executable='turtle_teleop_key',
        name='keyboard'
    )

    notify = ExecuteProcess(
        cmd=[[
            FindExecutable(name='echo'),
            ' hi > $HOME/this',
        ]],

        shell=True
    )


    mainnode = Node(
        package='rqt_graph'
        executable='rqt_graph'

    )


    desc = LaunchDescription([
        turtlesim_node,

        RegisterEventHandler(
            OnProcessStart(
                target_action=turtlesim_node,

                on_start=[
                    notify,
                    mainnode
                ]
            )
        )
    ])

    return desc
        
