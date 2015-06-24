include(FindPackageHandleStandardArgs)

message(STATUS "Finding Kiwi...")

find_path(KIWI_INCLUDE_DIR NAMES kiwi.h PATHS ${CMAKE_CURRENT_SOURCE_DIR} PATH_SUFFIXES "lib/kiwi/kiwi/")

message(STATUS "kiwi path : ${KIWI_INCLUDE_DIR}")

add_library(kiwi INTERFACE)
target_include_directories(kiwi INTERFACE ${KIWI_INCLUDE_DIR})

find_package_handle_standard_args(Kiwi REQUIRED_VARS KIWI_INCLUDE_DIR)
