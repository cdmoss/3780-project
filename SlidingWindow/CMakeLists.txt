cmake_minimum_required(VERSION 3.23)
project(SlidingWindow)

set(CMAKE_CXX_STANDARD 14)
add_executable(
        SlidingWindow_test
        src/SlidingWindow.cpp
        include/SlidingWindow.h
        test/SlidingWindow_test.cpp
)

add_executable(
        Receiver_test
        test/Receiver_test.cpp
        include/Receiver.h
        src/Receiver.cpp
        src/SlidingWindow.cpp
        include/SlidingWindow.h
)

add_executable(
        Sender_test
        test/Sender_test.cpp
        include/Sender.h
        src/Sender.cpp
        src/SlidingWindow.cpp
        include/SlidingWindow.h
        include/Receiver.h
        src/Receiver.cpp
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

target_link_libraries(
        Receiver_test
        GTest::gtest_main
)

target_link_libraries(
        Sender_test
        GTest::gtest_main
)