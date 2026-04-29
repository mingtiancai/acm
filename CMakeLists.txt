cmake_minimum_required(VERSION 3.14)
project(acm)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library containing the business logic
add_library(algo_lib src/ants.cpp)
target_include_directories(algo_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Main executable
add_executable(hello_world src/main.cpp)
target_link_libraries(hello_world PRIVATE algo_lib)

option(ACM_ENABLE_TESTS "Build unit tests" ON)
option(ACM_FETCH_GTEST "Allow CMake to download GoogleTest when testing is enabled" ON)

if(ACM_ENABLE_TESTS)
  enable_testing()
  include(Dependencies)
  setup_gtest()

  if(NOT GTest_FOUND AND NOT TARGET GTest::gtest_main)
    message(FATAL_ERROR
      "GoogleTest is required when ACM_ENABLE_TESTS is ON. "
      "Enable ACM_FETCH_GTEST or install GTest first.")
  endif()

  add_executable(ants_test tests/ants_test.cpp)
  target_link_libraries(ants_test PRIVATE algo_lib GTest::gtest_main)
  include(GoogleTest)
  gtest_discover_tests(ants_test)
endif()
