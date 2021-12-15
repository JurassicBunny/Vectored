find_package(GTest QUIET)

# NOTE: the upper case GTEST! CK
if(NOT GTEST_FOUND)
  # Download and unpack googletest at configure time
  # but only if needed! CK
  configure_file(${CMAKE_SOURCE_DIR}/cmake/GoogleTest-CMakeLists.txt.in
    ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()

  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
    ${CMAKE_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL)
endif()
# Now simply link against gtest or gtest_main as needed. Eg
add_executable(vectored_test ./testing.cpp)
target_link_libraries(vectored_test gtest_main Eigen3::Eigen)
add_test(NAME vectored_test
    COMMAND vectored_test)
