function(__fetch_pybind11 download_module_path download_root)
  set(PYBIND11_DOWNLOAD_ROOT ${download_root})
  configure_file(
    ${download_module_path}/pybind11-download.cmake
    ${download_root}/CMakeLists.txt
    @ONLY
  )
  unset(PYBIND11_DOWNLOAD_ROOT)

  execute_process(
    COMMAND
      "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY
      ${download_root}
  )
  execute_process(
    COMMAND
      "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY
      ${download_root}
  )

  add_subdirectory(
    ${download_root}/pybind11-src
    ${download_root}/pybind11-build
  )
endfunction()
