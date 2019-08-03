set(LIBRARY_NAME ${PROJECT_TARGET_LIB_NAME})

file(GLOB SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/matplotlib_cpp/MatplotlibCpp.cpp
)

# use python version other than system python
if(USE_PYENV)
  include(FindPythonPyenv)
endif(USE_PYENV)

include(pybind11)
__fetch_pybind11(
  ${PROJECT_SOURCE_DIR}/cmake
  ${PROJECT_BINARY_DIR}/pybind11_for_${PROJECT_TARGET_LIB_NAME}
)

add_library(${LIBRARY_NAME}
  SHARED
     ${SOURCE_FILES}
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


target_compile_features(${LIBRARY_NAME}
  PRIVATE
     cxx_std_11
)

target_compile_options(${LIBRARY_NAME}
  PRIVATE
     $<$<CONFIG:Debug>:-O0 -g -Wall -Werror>
     $<$<CONFIG:Release>:-O3>
)

target_link_libraries(${LIBRARY_NAME}
  PRIVATE
     pybind11::embed
)

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
configure_file(${PROJECT_SOURCE_DIR}/cmake/MatplotlibCppConfig.cmake.in "${CONFIG_FILE}" @ONLY)

install(FILES "${CONFIG_FILE}"
  DESTINATION share/cmake/${PROJECT_NAME}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/matplotlib_cpp
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)
