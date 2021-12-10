# cmake minimum version
cmake_minimum_required(VERSION 3.20)

# set release build optimization flag
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# project name
set(PROJECT_NAME Vectored)


# set project
project(${PROJECT_NAME})

# set C++ standard and require true
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find the Eigen3 package
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# add library
add_library(${PROJECT_NAME} INTERFACE)
# include dirs
target_include_directories(
        ${PROJECT_NAME}
        INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/Vectored>
                  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# link Eigen3 libraries to the target
target_link_libraries(
        ${PROJECT_NAME}
        INTERFACE Eigen3::Eigen )

# export the c++ 20 standard when using this library
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

# cmake helper functions
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# install targets
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/Vectored.cmake.in"
        "${PROJECT_BINARY_DIR}/VectoredConfig.cmake"
        INSTALL_DESTINATION ${PROJECT_SOURCE_DIR}/cmake/)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cmake/${PROJECT_NAME})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/Vectored
        DESTINATION include)