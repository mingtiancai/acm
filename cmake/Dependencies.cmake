# Dependencies.cmake - Third-party libraries configuration

function(setup_gtest)
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
endfunction()
