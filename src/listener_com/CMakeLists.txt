cmake_minimum_required(VERSION 3.8)
project(listener_com)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(composition REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(lifecycle_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_library(listener_component SHARED src/main.cpp)
target_compile_definitions(listener_component PRIVATE "COMPOSITION_BUILDING_DLL")

ament_target_dependencies(listener_component rclcpp std_msgs rclcpp_components rclcpp_lifecycle lifecycle_msgs)

rclcpp_components_register_node(
  listener_component
  PLUGIN "listener_com::MinimalSubscriber"
  EXECUTABLE listener 
  )

ament_export_targets(export_talker_component)

install(TARGETS
  listener_component
  EXPORT export_talker_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )



install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})


ament_package()
