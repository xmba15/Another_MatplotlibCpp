/**
 * @file    ModuleEmbedding.hpp
 *
 * @author  btran
 *
 * @date    2019-08-01
 *
 * Copyright (c) organization
 *
 */

#pragma once

#include <pybind11/eval.h>
#include <string>

#include "PythonInterpreter.hpp"

namespace pe
{
/**
 *  @brief Class to embed a single python module
 *
 *  PYBIND11_EXPORT is the magic macro to help avoid visibility-related
 * troubles.
 *  [Reference](https://pybind11.readthedocs.io/en/stable/advanced/misc.html)
 *
 */
class PYBIND11_EXPORT ModuleEmbedding
{
 public:
    /**
     *  @brief constructor to initialize the targeted python module
     *
     *  The single python interpreter will be initialized here of not being
     * started yet.
     */
    explicit ModuleEmbedding(const std::string& moduleName);

    /**
     *  @brief constant getter of the module name
     *
     */
    const std::string& moduleName() const;

    /**
     *  @brief constant getter of the python object corresponding to the module
     */
    const pybind11::module& pyModule() const;

    /**
     *  @brief constant getter of imported flag
     *
     */
    const bool& imported() const;

    /**
     *  @brief Import python module
     *
     *  This procedure equals "import [module_name]" in python.
     *
     *  @return true if imported successfully; false other wise
     */
    bool importModule();

 private:
    //! name of the python module
    std::string _moduleName;

    //! python object corresponding to the module
    pybind11::module _pyModule;

    //! boolean flag to check if the module has been imported successully or not.
    bool _imported = false;
};

ModuleEmbedding::ModuleEmbedding(const std::string& moduleName) : _moduleName(moduleName)
{
    // initialize python interpreter;
    PythonInterpreter::getInstance();
}

const std::string& ModuleEmbedding::moduleName() const
{
    return this->_moduleName;
}

const pybind11::module& ModuleEmbedding::pyModule() const
{
    return this->_pyModule;
}

bool ModuleEmbedding::importModule()
{
    try {
        this->_pyModule = pybind11::module::import(this->_moduleName.c_str());
        this->_imported = true;
    } catch (pybind11::error_already_set& e) {
        pybind11::print(e.what());
    }

    return this->_imported;
}

}  // namespace pe
