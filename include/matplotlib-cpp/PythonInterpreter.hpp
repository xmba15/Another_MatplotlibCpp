/**
 * @file    PythonInterpreter.hpp
 *
 * @brief   brief
 *
 * @author  btran
 *
 * @date    2019-08-01
 *
 * Copyright (c) organization
 *
 */

#ifndef PYTHONINTERPRETER_HPP_
#define PYTHONINTERPRETER_HPP_

#include <pybind11/embed.h>
#include <string>

/**
 *  @brief python embedding space
 */
namespace pe {
/**
 *  @brief Caller of Python Interpreter
 *
 *  Python's GIL implementation (eg: Cython) allows only a single thread to be
 * executed; hence this caller utilizes singleton pattern for calling python
 * interpreter.
 */
class PythonInterpreter {
public:
  /**
   *  @brief getter for static single instance of PythonInterpreter
   *
   */
  static PythonInterpreter &getInstance();

private:
  PythonInterpreter();
  ~PythonInterpreter();
};

} // namespace pe

#endif /* PYTHONINTERPRETER_HPP_ */
