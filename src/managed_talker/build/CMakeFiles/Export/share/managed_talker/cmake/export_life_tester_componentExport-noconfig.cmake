#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "managed_talker::life_tester" for configuration ""
set_property(TARGET managed_talker::life_tester APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(managed_talker::life_tester PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblife_tester.so"
  IMPORTED_SONAME_NOCONFIG "liblife_tester.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS managed_talker::life_tester )
list(APPEND _IMPORT_CHECK_FILES_FOR_managed_talker::life_tester "${_IMPORT_PREFIX}/lib/liblife_tester.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
