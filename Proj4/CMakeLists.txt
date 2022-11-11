cmake_minimum_required(VERSION 3.14)
project(Proj4)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)
include_directories(src)

add_executable(
  test_SlidingWindowSR
  test_SlidingWindowSR.cpp
  src/SlidingWindowSR.cpp
  include/SlidingWindowSR.h

)
target_link_libraries(
  test_SlidingWindowSR
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_SlidingWindowSR)