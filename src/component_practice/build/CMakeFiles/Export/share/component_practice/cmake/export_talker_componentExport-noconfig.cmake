#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "component_practice::talker_component" for configuration ""
set_property(TARGET component_practice::talker_component APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(component_practice::talker_component PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libtalker_component.so"
  IMPORTED_SONAME_NOCONFIG "libtalker_component.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS component_practice::talker_component )
list(APPEND _IMPORT_CHECK_FILES_FOR_component_practice::talker_component "${_IMPORT_PREFIX}/lib/libtalker_component.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
