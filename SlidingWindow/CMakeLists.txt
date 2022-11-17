cmake_minimum_required(VERSION 3.23)
project(SlidingWindow)

set(CMAKE_CXX_STANDARD 14)
add_executable(
        SlidingWindow_test
        src/SlidingWindow.cpp
        include/SlidingWindow.h
        SlidingWindow_test.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(
        SlidingWindow_test
        GTest::gtest_main
)