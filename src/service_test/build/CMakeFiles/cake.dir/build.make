# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/light/dev_ws/src/service_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/light/dev_ws/src/service_test/build

# Include any dependencies generated for this target.
include CMakeFiles/cake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cake.dir/flags.make

CMakeFiles/cake.dir/src/main.cpp.o: CMakeFiles/cake.dir/flags.make
CMakeFiles/cake.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/cake.dir/src/main.cpp.o: CMakeFiles/cake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/light/dev_ws/src/service_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cake.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cake.dir/src/main.cpp.o -MF CMakeFiles/cake.dir/src/main.cpp.o.d -o CMakeFiles/cake.dir/src/main.cpp.o -c /home/light/dev_ws/src/service_test/src/main.cpp

CMakeFiles/cake.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cake.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/light/dev_ws/src/service_test/src/main.cpp > CMakeFiles/cake.dir/src/main.cpp.i

CMakeFiles/cake.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cake.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/light/dev_ws/src/service_test/src/main.cpp -o CMakeFiles/cake.dir/src/main.cpp.s

# Object files for target cake
cake_OBJECTS = \
"CMakeFiles/cake.dir/src/main.cpp.o"

# External object files for target cake
cake_EXTERNAL_OBJECTS =

cake: CMakeFiles/cake.dir/src/main.cpp.o
cake: CMakeFiles/cake.dir/build.make
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_generator_py.so
cake: /opt/ros/humble/lib/libcomponent_manager.so
cake: /opt/ros/humble/lib/librclcpp_lifecycle.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/libstd_msgs__rosidl_generator_c.so
cake: /opt/ros/humble/lib/libclass_loader.so
cake: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.1.0
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_generator_py.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/libcomposition_interfaces__rosidl_generator_c.so
cake: /opt/ros/humble/lib/librclcpp.so
cake: /opt/ros/humble/lib/liblibstatistics_collector.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_generator_py.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/librosgraph_msgs__rosidl_generator_c.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_generator_py.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/libstatistics_msgs__rosidl_generator_c.so
cake: /opt/ros/humble/lib/librcl_lifecycle.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_generator_py.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/liblifecycle_msgs__rosidl_generator_c.so
cake: /opt/ros/humble/lib/librcl.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/librosidl_typesupport_fastrtps_c.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/librosidl_typesupport_fastrtps_cpp.so
cake: /opt/ros/humble/lib/libfastcdr.so.1.0.24
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/librosidl_typesupport_introspection_cpp.so
cake: /opt/ros/humble/lib/librosidl_typesupport_introspection_c.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/librosidl_typesupport_cpp.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_generator_py.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/librcl_interfaces__rosidl_generator_c.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_generator_py.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
cake: /opt/ros/humble/lib/libbuiltin_interfaces__rosidl_generator_c.so
cake: /opt/ros/humble/lib/librosidl_typesupport_c.so
cake: /usr/lib/x86_64-linux-gnu/libpython3.10.so
cake: /opt/ros/humble/lib/librcl_yaml_param_parser.so
cake: /opt/ros/humble/lib/libyaml.so
cake: /opt/ros/humble/lib/librmw_implementation.so
cake: /opt/ros/humble/lib/libament_index_cpp.so
cake: /opt/ros/humble/lib/librmw.so
cake: /opt/ros/humble/lib/librcl_logging_spdlog.so
cake: /opt/ros/humble/lib/librcpputils.so
cake: /opt/ros/humble/lib/librcl_logging_interface.so
cake: /opt/ros/humble/lib/libtracetools.so
cake: /opt/ros/humble/lib/librosidl_runtime_c.so
cake: /opt/ros/humble/lib/librcutils.so
cake: CMakeFiles/cake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/light/dev_ws/src/service_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cake.dir/build: cake
.PHONY : CMakeFiles/cake.dir/build

CMakeFiles/cake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cake.dir/clean

CMakeFiles/cake.dir/depend:
	cd /home/light/dev_ws/src/service_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/light/dev_ws/src/service_test /home/light/dev_ws/src/service_test /home/light/dev_ws/src/service_test/build /home/light/dev_ws/src/service_test/build /home/light/dev_ws/src/service_test/build/CMakeFiles/cake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cake.dir/depend

