#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "test_pubsub::tester_component" for configuration ""
set_property(TARGET test_pubsub::tester_component APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(test_pubsub::tester_component PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libtester_component.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS test_pubsub::tester_component )
list(APPEND _IMPORT_CHECK_FILES_FOR_test_pubsub::tester_component "${_IMPORT_PREFIX}/lib/libtester_component.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
