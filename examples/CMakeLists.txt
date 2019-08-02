list(APPEND EXAMPLES
  "Basic"
)

function(__build_example example_name)
  add_executable(
    ${example_name}
    ${CMAKE_CURRENT_LIST_DIR}/${example_name}.cpp
  )

  target_link_libraries(
    ${example_name}
    PUBLIC
       matplotlib-cpp
  )
endfunction(__build_example example_name)

foreach(EXAMPLE ${EXAMPLES})
  __build_example(${EXAMPLE})
endforeach(EXAMPLE)
