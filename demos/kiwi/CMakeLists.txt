#usefull ressources: https://github.com/ggutierrez/gecodert
#set(MAKE_C_COMPILER "/usr/bin/gcc")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

##########################################################################
# CMAKE POLICIES
##########################################################################
cmake_policy(SET CMP0037 NEW)

##########################################################################

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
# Modules
##########################################################################
find_package(Kiwi REQUIRED)
##########################################################################
# This project products
##########################################################################
#file(GLOB_RECURSE HDRS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
#file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#
#set(SOURCES
#    ${SRCS}
#	  ${HDRS}
#  )
#
#add_library(${PROJECT_NAME} ${SOURCES})
#
##########################################################################
# Examples
##########################################################################
file(GLOB_RECURSE EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")

foreach( exampleFile ${EXAMPLES} )

    get_filename_component(exampleName ${exampleFile} NAME_WE)

    #message(STATUS "exampleName : ${exampleName}")

    add_executable( ${exampleName} ${exampleFile} )
    # Link

    target_link_libraries( ${exampleName} kiwi )
endforeach()
