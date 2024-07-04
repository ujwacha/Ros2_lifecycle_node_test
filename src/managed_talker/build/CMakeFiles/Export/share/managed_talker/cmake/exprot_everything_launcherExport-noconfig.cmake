#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "managed_talker::everything_launcher" for configuration ""
set_property(TARGET managed_talker::everything_launcher APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(managed_talker::everything_launcher PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libeverything_launcher.so"
  IMPORTED_SONAME_NOCONFIG "libeverything_launcher.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS managed_talker::everything_launcher )
list(APPEND _IMPORT_CHECK_FILES_FOR_managed_talker::everything_launcher "${_IMPORT_PREFIX}/lib/libeverything_launcher.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
