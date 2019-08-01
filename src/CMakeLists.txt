set(LIBRARY_NAME "matplotlib-cpp")
file(GLOB SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/matplotlib-cpp/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/matplotlib-cpp/*.hpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/pybind11)

function(__build_library)
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
endfunction(__build_library)
