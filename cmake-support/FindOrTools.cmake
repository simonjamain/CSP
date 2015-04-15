message(STATUS "Finding Or-tools...")

# After using this module, the following variables will be available:
#   ORTOOLS_LIBRARY : The gecode libraries that were found.
#   ORTOOLS_LIBRARY_PATH : The gecode libraries that were found.
#   ORTOOLS_INCLUDE_DIR : path to the gecode headers.
#   ORTOOLS_INCLUDE_DIR_DEPS : path to the gecode headers.

# Look for the main header files of gecode.
file(TO_CMAKE_PATH "$ENV{PATH}" envpath)
#message("env path cmake : ${envpath}")

find_library (ORTOOLS_LIBRARY NAMES ortools PATHS ${CMAKE_CURRENT_SOURCE_DIR} PATH_SUFFIXES "lib/or-tools/lib/")

if(NOT ORTOOLS_LIBRARY)
  	message(WARNING "Or-tools library not found!")
else()
	message(STATUS "Or-tools library found.")
endif()


find_path(ORTOOLS_INCLUDE_DIR NAMES constraint_solver PATHS ${CMAKE_CURRENT_SOURCE_DIR} PATH_SUFFIXES "lib/or-tools/include/")
message(STATUS "or-tools path : ${ORTOOLS_INCLUDE_DIR}")
include_directories(${ORTOOLS_INCLUDE_DIR})
set(OR_TOOLS_TOP ${ORTOOLS_INCLUDE_DIR})# used by or-tools

if (ORTOOLS_INCLUDE_DIR AND ORTOOLS_LIBRARY)
    set(OrTools_FOUND TRUE)
else()
    set(OrTools_FOUND FALSE)
endif()
