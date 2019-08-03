/**
 * @file    ModuleEmbedding.cpp
 *
 * @author  btran
 *
 * @date    2019-08-01
 *
 * Copyright (c) organization
 *
 */

#include <matplotlib-cpp/ModuleEmbedding.hpp>
#include <pybind11/eval.h>

#ifndef WITH_DEBUG
#define ENABLE_DEBUG 1
#endif // WITH_DEBUG

namespace pe {
ModuleEmbedding::ModuleEmbedding(const std::string &moduleName)
    : _moduleName(moduleName) {
  // initialize python interpreter;
  PythonInterpreter::getInstance();
}

const std::string &ModuleEmbedding::moduleName() const {
  return this->_moduleName;
}

const py::module &ModuleEmbedding::pyModule() const { return this->_pyModule; }

bool ModuleEmbedding::importModule() {
  try {
    this->_pyModule = py::module::import(this->_moduleName.c_str());
  } catch (py::error_already_set &e) {
    py::print(e.what());
    return false;
  }
  this->_imported = true;

  return true;
}

} // namespace pe
