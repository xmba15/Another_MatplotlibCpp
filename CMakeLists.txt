cmake_minimum_required(VERSION 3.8)

project(libmatplotlib_cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_TARGET_LIB_NAME "matplotlib_cpp")

add_subdirectory(src)

include(build_options)
