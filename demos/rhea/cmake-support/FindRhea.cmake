include(FindPackageHandleStandardArgs)

message(STATUS "Finding Rhea...")

find_path(RHEA_INCLUDE_DIR NAMES rhea PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/rhea/" NO_DEFAULT_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library (RHEA_LIBRARY NAMES rhea PATHS ${CMAKE_CURRENT_SOURCE_DIR} PATH_SUFFIXES "lib/rhea/build/rhea/")

if(NOT (RHEA_INCLUDE_DIR AND RHEA_LIBRARY))

	message(STATUS "rhea not found, trying to install...")
	execute_process(COMMAND "${CMAKE_MODULE_PATH}/installRhea.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_QUIET)

	find_path(RHEA_INCLUDE_DIR NAMES simplex_solver.hpp PATHS ${CMAKE_CURRENT_SOURCE_DIR} PATH_SUFFIXES "lib/rhea/rhea/")
	find_library (RHEA_LIBRARY NAMES rhea PATHS ${CMAKE_CURRENT_SOURCE_DIR} PATH_SUFFIXES "lib/rhea/build/rhea/")

	if(NOT (RHEA_INCLUDE_DIR AND RHEA_LIBRARY))
		message(WARNING "installation failed!")
	endif()

endif()


if(NOT (RHEA_INCLUDE_DIR AND RHEA_LIBRARY))
	message(WARNING "rhea not found!")
else()
	message(STATUS "rhea found, include path : ${RHEA_INCLUDE_DIR}")
	message(STATUS "rhea found, bin path : ${RHEA_LIBRARY}")
endif()


add_library(rhea INTERFACE)
target_link_libraries(rhea INTERFACE ${RHEA_LIBRARY})
target_include_directories(rhea INTERFACE ${RHEA_INCLUDE_DIR})

find_package_handle_standard_args(Rhea REQUIRED_VARS RHEA_INCLUDE_DIR RHEA_LIBRARY)
