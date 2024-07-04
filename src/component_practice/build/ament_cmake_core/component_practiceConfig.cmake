# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_component_practice_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED component_practice_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(component_practice_FOUND FALSE)
  elseif(NOT component_practice_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(component_practice_FOUND FALSE)
  endif()
  return()
endif()
set(_component_practice_CONFIG_INCLUDED TRUE)

# output package information
if(NOT component_practice_FIND_QUIETLY)
  message(STATUS "Found component_practice: 0.0.0 (${component_practice_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'component_practice' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${component_practice_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(component_practice_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_targets-extras.cmake")
foreach(_extra ${_extras})
  include("${component_practice_DIR}/${_extra}")
endforeach()
