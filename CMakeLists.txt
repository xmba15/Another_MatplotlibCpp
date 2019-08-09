cmake_minimum_required(VERSION 3.8)

project(libmatplotlib-cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(googletest)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
)

set(PROJECT_TARGET_LIB_NAME "matplotlib-cpp")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/pybind11)
add_subdirectory(src)

include(build_options)

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR "lib")
endif()

install(TARGETS ${PROJECT_TARGET_LIB_NAME}
  EXPORT ${PROJECT_TARGET_LIB_NAME}-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT  ${PROJECT_TARGET_LIB_NAME}-targets
  DESTINATION share/cmake/${PROJECT_NAME}
  EXPORT_LINK_INTERFACE_LIBRARIES
)

set(CONFIG_FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
configure_file(cmake/MatplotlibCppConfig.cmake.in "${CONFIG_FILE}" @ONLY)

install(FILES "${CONFIG_FILE}"
  DESTINATION share/cmake/${PROJECT_NAME}
)

install(DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/include/matplotlib-cpp
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)
