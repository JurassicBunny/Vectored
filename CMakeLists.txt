cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)


add_library(vectored library.cpp)
target_link_libraries(vectored Eigen3::Eigen)