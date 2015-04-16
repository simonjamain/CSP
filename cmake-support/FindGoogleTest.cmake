message(STATUS "Finding google test...")


ADD_SUBDIRECTORY (lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

if (gtest AND gtest_main)
    set(GoogleTest_FOUND TRUE)
else()
    set(GoogleTest_FOUND FALSE)
endif()
