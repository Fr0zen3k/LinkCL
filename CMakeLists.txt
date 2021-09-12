cmake_minimum_required(VERSION 3.20.0)

project(LinkCL VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/LinkCL/src")

set(LinkCL_FILES
    "${LinkCL_SOURCE_FILES}"
    "${LinkCL_HEADER_FILES}"
    CACHE INTERNAL "" FORCE)

add_library(LinkCL STATIC "${LinkCL_FILES}")

set_target_properties(LinkCL PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(LinkCL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/LinkCL/src")
