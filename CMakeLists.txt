cmake_minimum_required(VERSION 3.2)
project(Plane)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++" )
set( CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc" )

add_executable(${PROJECT_NAME} plane.cpp)

