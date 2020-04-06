cmake_minimum_required(VERSION 3.15)
project(raytracing)

set(CMAKE_CXX_STANDARD 20)

set(STB_DIR "${CMAKE_SOURCE_DIR}/../stb")
include_directories("${STB_DIR}")
link_directories("${STB_DIR}")

add_executable(raytracing main.cpp)