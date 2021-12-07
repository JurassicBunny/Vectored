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
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# find the Eigen3 package
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# add library
add_library(${PROJECT_NAME} src/vectored.cpp)
# link Eigen3 libraries to the target
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)

# install targets
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES src/vectored.h
        DESTINATION include/Vectored)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE Vectored::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Vectored)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Vectored.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/VectoredConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Vectored)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/VectoredConfig.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Vectored)
