function(overload_message messages)
  message(STATUS "-----------------------------")
  message(STATUS "${messages}")
  message(STATUS "-----------------------------")
endfunction()

execute_process(
  COMMAND which python
  OUTPUT_VARIABLE PYTHON_EXECUTABLE OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND python -c "from __future__ import print_function; from distutils.sysconfig import get_python_inc; print(get_python_inc())"
  OUTPUT_VARIABLE PYTHON_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
)

execute_process(
  COMMAND python -c "from __future__ import print_function; import os, numpy.distutils; print(os.pathsep.join(numpy.distutils.misc_util.get_numpy_include_dirs()))"
  OUTPUT_VARIABLE PYTHON_NUMPY_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
)

execute_process(
  COMMAND python -c "from __future__ import print_function; import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR') + '/' + sysconfig.get_config_var('LDLIBRARY'))"
  OUTPUT_VARIABLE PYTHON_LIBRARY OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
)

execute_process(
  COMMAND python -c "from __future__ import print_function; import platform; print(platform.python_version())"
  OUTPUT_VARIABLE PYTHONLIBS_VERSION_STRING OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
)

overload_message("python executable: ${PYTHON_EXECUTABLE}")
overload_message("python include dirs ${PYTHON_INCLUDE_DIR}")
overload_message("python numpy include dirs: ${PYTHON_NUMPY_INCLUDE_DIR}")
overload_message("python libraries: ${PYTHON_LIBRARY}")
