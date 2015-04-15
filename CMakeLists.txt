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
find_package(OrTools REQUIRED)# generate ORTOOLS_INCLUDE_DIR and ORTOOLS_LIBRARY
#find_package(Catch REQUIRED)# generate CATCH_INCLUDE_DIR
##########################################################################
# This project products
##########################################################################
file(GLOB_RECURSE HDRS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp")
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

set(SOURCES
	  ${SRCS}
	  ${HDRS}
  )

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ORTOOLS_LIBRARY})
##########################################################################
# Tests
##########################################################################
#file(GLOB_RECURSE TESTS_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp")
#file(GLOB_RECURSE TESTS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

#set(TESTS
#          ${TESTS_HDRS}
#          ${TESTS_SRCS}
#  )

#add_executable(runTests "${TESTS}")
#target_link_libraries(runTests ${PROJECT_NAME})
##########################################################################
# Examples
##########################################################################
file(GLOB_RECURSE EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")


foreach( exampleFile ${EXAMPLES} )

    get_filename_component(exampleName ${exampleFile} NAME_WE)

    #message(STATUS "exampleName : ${exampleName}")

    add_executable( ${exampleName} ${exampleFile} )
    # Link
    target_link_libraries( ${exampleName} ${PROJECT_NAME} )
endforeach()

##########################################################################
# Debug
##########################################################################

option(CSP_LOG_VALUES "Log dates found by solver"
       OFF)

if(${CSP_LOG_VALUES})
  add_definitions(-DCSP_LOG_VALUES)
  message(STATUS "Debogage des valeures des dates actif.")
endif()
