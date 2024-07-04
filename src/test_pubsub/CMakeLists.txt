cmake_minimum_required(VERSION 3.8)
project(test_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
add_library(tester_component SHARED src/main.cpp)
ament_target_dependencies(tester_component rclcpp std_msgs rclcpp_components)

rclcpp_components_register_node(
  tester_component
  PLUGIN "test_pubsub::NodeMsgNo"
  EXECUTABLE node_msg_no 
)

ament_export_targets(export_tester_component)


install(TARGETS tester_component
  EXPORT export_tester_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
