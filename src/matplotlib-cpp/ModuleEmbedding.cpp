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

bool ModuleEmbedding::import() {
  try {
    this->_pyModule = py::module::import(this->_moduleName.c_str());
    this->imported = true;
  } catch (py::error_already_set &e) {
#if ENABLE_DEBUG
    py::print(e);
#endif // ENABLE_DEBUG
    return false;
  }

  return true;
}

} // namespace pe
