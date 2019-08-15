cmake_minimum_required(VERSION 3.8)

project(libmatplotlib_cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(googletest)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
)

set(PROJECT_TARGET_LIB_NAME "matplotlib_cpp")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/pybind11)
add_subdirectory(src)

include(build_options)
