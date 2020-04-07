cmake_minimum_required(VERSION 3.15)
project(raytracing)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(STB_DIR "${CMAKE_SOURCE_DIR}/../stb")
include_directories("${STB_DIR}")
link_directories("${STB_DIR}")

add_executable(raytracing vec3.cpp vec3.hpp main.cpp ray.cpp ray.hpp hitable.hpp sphere.cpp sphere.hpp hitableList.cpp hitableList.hpp camera.cpp camera.hpp)