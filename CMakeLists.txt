#usefull ressources: https://github.com/ggutierrez/gecodert
#set(MAKE_C_COMPILER "/usr/bin/gcc")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(CSP CXX)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
cmake_minimum_required(VERSION 2.8)

# Add path for some modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake-support"
  )
message(STATUS "compiler : ${CMAKE_CXX_COMPILER}")
##########################################################################
# Google or-tools
##########################################################################
find_package(OrTools REQUIRED)# generate ORTOOLS_INCLUDE_DIR and ORTOOLS_LIBRARY
include_directories(${ORTOOLS_INCLUDE_DIR})
message(STATUS "or-tools path : ${ORTOOLS_INCLUDE_DIR}")
##########################################################################
# This project products
##########################################################################
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
  source/csp.cc
  )

#add_library(csp ${SOURCES})
#target_link_libraries(csp OrTools)

add_executable(example ${SOURCES})
target_link_libraries(example OrTools)
##########################################################################
# Examples
##########################################################################

#add_executable(example test/main.cpp)
#target_link_libraries(example csp)

