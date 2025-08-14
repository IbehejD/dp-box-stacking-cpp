# Copyright (c) 2025 David Ibehej
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add tests
file(GLOB TEST_SOURCES "../src/dp/*.cpp")
add_executable(${PROJECT_NAME}_tests test.cpp ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}_tests PUBLIC ../include ../src)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
