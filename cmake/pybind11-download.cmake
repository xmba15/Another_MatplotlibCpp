cmake_minimum_required(VERSION 3.8)

project(pybind11-download NONE)

include(ExternalProject)
ExternalProject_Add(
  pybind11
  SOURCE_DIR "@PYBIND11_DOWNLOAD_ROOT@/pybind11-src"
  BINARY_DIR "@PYBIND11_DOWNLOAD_ROOT@/pybind11-build"
  GIT_REPOSITORY
    https://github.com/pybind/pybind11.git
  GIT_TAG
    v2.3
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
