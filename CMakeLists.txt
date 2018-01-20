cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Magma-Engine)

enable_language(C CXX)
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

# Engine version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

add_subdirectory(external/glew)
add_subdirectory(external/glfw)
add_subdirectory(src/)
