#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "math" for configuration "Release"
set_property(TARGET math APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(math PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/math.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS math )
list(APPEND _IMPORT_CHECK_FILES_FOR_math "${_IMPORT_PREFIX}/lib/math.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
