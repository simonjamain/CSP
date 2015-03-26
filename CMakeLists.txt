#usefull ressources: https://github.com/ggutierrez/gecodert
#set(MAKE_C_COMPILER "/usr/bin/gcc")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(PROJECT_NAME CSP)

project(${PROJECT_NAME})
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
##########################################################################
# This project products
##########################################################################
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE HDRS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp")
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

set(SOURCES
	  ${SRCS}
	  ${HDRS}
  )

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ORTOOLS_LIBRARY})
##########################################################################
# Examples
##########################################################################

add_executable(example "${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp")
target_link_libraries(example ${PROJECT_NAME} ${ORTOOLS_LIBRARY})

