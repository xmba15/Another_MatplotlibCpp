/**
 * @file    PythonInterpreter.cpp
 *
 * @author  btran
 *
 * @date    2019-08-01
 *
 * Copyright (c) organization
 *
 */

#include <matplotlib-cpp/PythonInterpreter.hpp>

namespace pe {
PythonInterpreter::PythonInterpreter() { pybind11::initialize_interpreter(); }

PythonInterpreter::~PythonInterpreter() { pybind11::finalize_interpreter(); }

PythonInterpreter &PythonInterpreter::getInstance() {
  static PythonInterpreter instance;
  return instance;
}

} // namespace pe
