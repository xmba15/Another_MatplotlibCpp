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
PythonInterpreter::PythonInterpreter() { Py_Initialize(); }

PythonInterpreter::~PythonInterpreter() { Py_Finalize(); }

PythonInterpreter &PythonInterpreter::getInstance() {
  static PythonInterpreter instance;
  return instance;
}

}  // namespace pe
