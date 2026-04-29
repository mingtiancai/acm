cmake_minimum_required(VERSION 3.14)
project(acm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library containing the business logic
add_library(hello_lib src/hello.cpp)
target_include_directories(hello_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Main executable
add_executable(hello_world src/main.cpp)
target_link_libraries(hello_world PRIVATE hello_lib)

option(ACM_ENABLE_TESTS "Build unit tests" OFF)
option(ACM_FETCH_GTEST "Allow CMake to download GoogleTest when testing is enabled" OFF)

if(ACM_ENABLE_TESTS)
  enable_testing()
  find_package(GTest CONFIG QUIET)

  if(NOT GTest_FOUND AND ACM_FETCH_GTEST)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/heads/main.zip
      DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # Windows specific setting: ensure gtest links to the correct runtime library
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Organize GoogleTest targets in IDEs when they exist.
    set_target_properties(gtest gtest_main PROPERTIES FOLDER "ThirdParty/GoogleTest")
    if(TARGET googletest-populate)
      set_target_properties(googletest-populate PROPERTIES FOLDER "ThirdParty/GoogleTest")
    endif()
  endif()

  add_executable(hello_test tests/hello_test.cpp)
  target_link_libraries(hello_test PRIVATE hello_lib)

  if(GTest_FOUND OR TARGET GTest::gtest_main)
    target_link_libraries(hello_test PRIVATE GTest::gtest_main)
    target_compile_definitions(hello_test PRIVATE ACM_USE_GTEST=1)
    include(GoogleTest)
    gtest_discover_tests(hello_test)
  else()
    add_test(NAME hello_test COMMAND hello_test)
    message(STATUS "Tests are enabled without GoogleTest. The hello_test executable will run as a plain CTest test.")
  endif()
endif()
