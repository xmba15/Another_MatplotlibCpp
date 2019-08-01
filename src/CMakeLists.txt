set(LIBRARY_NAME "matplotlib-cpp")

file(GLOB SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/matplotlib-cpp/PythonInterpreter.cpp
  ${CMAKE_CURRENT_LIST_DIR}/matplotlib-cpp/ModuleEmbedding.cpp
  ${CMAKE_CURRENT_LIST_DIR}/matplotlib-cpp/MatplotlibCpp.cpp
)

add_library(${LIBRARY_NAME}
  SHARED
     ${SOURCE_FILES}
)

target_link_libraries(${LIBRARY_NAME}
  PUBLIC
     pybind11::embed
)

target_include_directories(${LIBRARY_NAME}
  PUBLIC
     ${PROJECT_SOURCE_DIR}/include
)
