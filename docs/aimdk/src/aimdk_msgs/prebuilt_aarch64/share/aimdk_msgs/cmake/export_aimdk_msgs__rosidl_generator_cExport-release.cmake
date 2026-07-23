#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aimdk_msgs::aimdk_msgs__rosidl_generator_c" for configuration "Release"
set_property(TARGET aimdk_msgs::aimdk_msgs__rosidl_generator_c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(aimdk_msgs::aimdk_msgs__rosidl_generator_c PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libaimdk_msgs__rosidl_generator_c.so"
  IMPORTED_SONAME_RELEASE "libaimdk_msgs__rosidl_generator_c.so"
  )

list(APPEND _cmake_import_check_targets aimdk_msgs::aimdk_msgs__rosidl_generator_c )
list(APPEND _cmake_import_check_files_for_aimdk_msgs::aimdk_msgs__rosidl_generator_c "${_IMPORT_PREFIX}/lib/libaimdk_msgs__rosidl_generator_c.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
