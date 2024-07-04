cmake_minimum_required(VERSION 3.8)
project(service_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(composition REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

# make an executable
add_executable(cake
  src/main.cpp)


# link dependencies
ament_target_dependencies(cake
  rclcpp
  std_msgs
  rclcpp_components
  lifecycle_msgs
  rclcpp_lifecycle)


# for colcon build, to find where to install packages
install(TARGETS
  cake
  DESTINATION lib/${PROJECT_NAME})

# make sure launch file is seen after we source ros
install(DIRECTORY
	launch
	DESTINATION share/${PROJECT_NAME})


ament_package()
