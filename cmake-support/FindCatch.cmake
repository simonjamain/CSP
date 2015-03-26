message(STATUS "Finding Catch...")

# After using this module, the following variables will be available:
#   CATCH_INCLUDE_DIR : path to the gecode headers.

# Look for the main header files of gecode.
file(TO_CMAKE_PATH "$ENV{PATH}" envpath)
#message("env path cmake : ${envpath}")

find_path(CATCH_INCLUDE_DIR NAMES catch.hpp PATHS envpath PATH_SUFFIXES "catch/include")
message(STATUS "catch path : ${CATCH_INCLUDE_DIR}")
include_directories(${CATCH_INCLUDE_DIR})

if (CATCH_INCLUDE_DIR)
    set(Catch_FOUND TRUE)
else()
	set(Catch_FOUND FALSE)
endif()

#http://www.cmake.org/Wiki/CMake_Useful_Variables
#-DCMAKE_PREFIX_PATH=/Users/doctorant/Desktop/lib
