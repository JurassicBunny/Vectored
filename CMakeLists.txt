# cmake minimum version
cmake_minimum_required(VERSION 3.20)

# project name
set(PROJECT_NAME vectored)

# set project
project(${PROJECT_NAME})

# set C++ standard and require true
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# find the Eigen3 package
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# add Libvectored static library
add_library(${PROJECT_NAME} STATIC vectored.cpp)

# link Eigen3 libraries to the target
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)