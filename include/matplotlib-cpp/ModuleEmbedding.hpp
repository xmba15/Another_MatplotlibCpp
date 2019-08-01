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

#ifndef MODULEEMBEDDING_HPP_
#define MODULEEMBEDDING_HPP_

#include <string>

#include "matplotlib-cpp/PythonInterpreter.hpp"

namespace py = pybind11;
namespace pe {
/**
 *  @brief Class to embed a single python module
 *
 *  PYBIND11_EXPORT is the magic macro to help avoid visibility-related
 * troubles.
 *  [Reference](https://pybind11.readthedocs.io/en/stable/advanced/misc.html)
 *
 */
class PYBIND11_EXPORT ModuleEmbedding {
public:
  /**
   *  @brief constructor to initialize the targeted python module
   *
   *  The single python interpreter will be initialized here of not being
   * started yet.
   */
  explicit ModuleEmbedding(const std::string &moduleName);

  /**
   *  @brief constant getter of the module name
   *
   */
  const std::string &moduleName() const;

  /**
   *  @brief constant getter of the python object corresponding to the module
   */
  const py::module &pyModule() const;

  /**
   *  @brief Import python module
   *
   *  This procedure equals "import [module_name]" in python.
   *
   *  @return true if imported successfully; false other wise
   */
  bool import();

  //! boolean flag to check if the module has been imported successully or not.
  bool imported = false;

private:
  //! name of the python module
  std::string _moduleName;

  //! python object corresponding to the module
  py::module _pyModule;
};
} // namespace pe

#endif /* MODULEEMBEDDING_HPP_ */
