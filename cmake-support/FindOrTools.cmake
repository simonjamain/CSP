message(STATUS "Finding Or-tools...")

# After using this module, the following variables will be available:
#   ORTOOLS_LIBRARY : The gecode libraries that were found.
#   ORTOOLS_INCLUDE_DIR : path to the gecode headers.

# Look for the main header files of gecode.
file(TO_CMAKE_PATH "$ENV{PATH}" envpath)
#message("env path cmake : ${envpath}")

find_library (ORTOOLS_LIBRARY NAMES ortools PATHS envpath PATH_SUFFIXES "or-tools/lib/")
#find_library (ORTOOLS_LIBRARY NAMES ortools PATHS envpath)

if(NOT ORTOOLS_LIBRARY)
  	message(WARNING "Or-tools library not found!")
else()
	message(STATUS "Or-tools library found.")
endif()




find_path(ORTOOLS_INCLUDE_DIR NAMES constraint_solver PATHS envpath PATH_SUFFIXES "or-tools/src/")
#message(STATUS "Or-tools include DIR : ${ORTOOLS_INCLUDE_DIR}")