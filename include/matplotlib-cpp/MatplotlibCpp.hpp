/**
 * @file    MatplotlibCpp.hpp
 *
 * @author  btran
 *
 * @date    2019-08-01
 *
 * Copyright (c) organization
 *
 */

#ifndef MATPLOTLIBCPP_HPP_
#define MATPLOTLIBCPP_HPP_

#include <pybind11/stl.h>

#include <map>
#include <string>
#include <vector>

#include "matplotlib-cpp/ModuleEmbedding.hpp"

namespace pe {
/**
 *  @brief visualization-related namespace
 */
namespace vis {
using namespace pybind11::literals; // NOLINT(build/namespaces_literals)

/**
 *  @brief Holder of modules embedded inside matplotlib library
 *
 */
class PYBIND11_EXPORT Matplotlib {
public:
  //! objectMap -> (python object name, corresponding python object)
  using ObjectMap = std::map<std::string, py::object>;

public:
  /**
   *  @brief Constructor to import matplotlib's modules
   */
  Matplotlib();

  /**
   *  @brief constant getter of imported flag
   */
  const bool &imported() const;

  /**
   *  @brief constant getter of the objectMap flag
   */
  const ObjectMap &objectMap() const;

  /**
   *  @brief constant getter of embedder of "matplotlib" module
   *
   *  This embedder can be used to call necessary python methods that have not
   * been wrapped in this class.
   */
  const ModuleEmbedding &mpl() const;

  /**
   *  @brief constant getter of embedder of "matplotlib.pyplot" module
   *
   *  This embedder can be used to call necessary python methods that have not
   * been wrapped in this class.
   */
  const ModuleEmbedding &plt() const;

  /**
   *  @brief constant getter of embedder of "mpl_toolkits.mplot3d" module
   *
   *  This embedder can be used to call necessary python methods that have not
   * been wrapped in this class.
   */
  const ModuleEmbedding &mplot3d() const;

  //@{
  /** wrapped methods from "matplotlib.pyplot" module. mainly used for 2d
   * visualization
   */
  py::object figure(const double width = 15, const double height = 5);
  py::object title(const std::string &titleStr);
  py::object xlabel(const std::string &xlabelStr);
  py::object ylabel(const std::string &ylabelStr);
  py::object show();
  py::object savefig(const std::string &figName);

  template <typename DATA_TYPE>
  py::object
  plot(const std::vector<DATA_TYPE> &x, const std::vector<DATA_TYPE> &y,
       const std::string &color = "green", const std::string &marker = "o",
       const std::string &linestyle = "dashed");

  py::object subplot(const size_t nrows, const size_t ncols,
                     const size_t index);
  py::object suptitle(const std::string &suptitleStr);

  template <typename DATA_TYPE>
  py::object hist(const std::vector<DATA_TYPE> &x, const size_t bins);

  template <typename DATA_TYPE>
  py::object scatter(const std::vector<DATA_TYPE> &x,
                     const std::vector<DATA_TYPE> &y,
                     const std::string &color = "pink",
                     const std::string &marker = "o", const double alpha = 0.5);

  py::object legend(const std::string &location = "best");
  //@}

  //@{
  /** wrapped methods from "mpl_toolkits.mplot3d" module. mainly used for 3d
   * visualization
   */
  py::object axes(const py::object &figure);
  void set_xlabel(py::object *axes, const std::string &xlabel);
  void set_ylabel(py::object *axes, const std::string &ylabel);

  template <typename DATA_TYPE>
  void scatter(py::object *axes, const std::vector<DATA_TYPE> &x,
               const std::vector<DATA_TYPE> &y,
               const std::string &marker = "o");

  template <typename DATA_TYPE>
  void scatter(py::object *axes, const std::vector<DATA_TYPE> &x,
               const std::vector<DATA_TYPE> &y, const std::vector<DATA_TYPE> &z,
               const std::string &marker = "o");

  template <typename DATA_TYPE>
  void scatter3D(py::object *axes, const std::vector<DATA_TYPE> &x,
                 const std::vector<DATA_TYPE> &y,
                 const std::string &marker = "o");

  template <typename DATA_TYPE>
  void plot(py::object *axes, const std::vector<DATA_TYPE> &x,
            const std::vector<DATA_TYPE> &y, const std::vector<DATA_TYPE> &z,
            const std::string &color = "green",
            const std::string &marker = "o");
  //@}

private:
  /**
   *  @brief initialize python object corresponding to the name held in object
   * map
   */
  void updateObjectMap();

private:
  //! Embedder of "matplotlib" module
  ModuleEmbedding _mpl;

  //! Embedder of "matplotlib.pyplot" module
  ModuleEmbedding _plt;

  //! Embedder of "mpl_toolkits.mplot3d" module
  ModuleEmbedding _mplot3d;

  //! boolean flag to check if matplotlib's targeted modules have been imported
  //! successfully.
  bool _imported = false;

  //! map to contain python objects of the targeted methods in matplotlib
  //! library and the names of the objects
  ObjectMap _objectMap;

  //! names of the targeted object in "matplotlib.pyplot" module
  const std::vector<std::string> _pltObjectNames = {
      "figure",  "plot",    "title",    "xlabel", "ylabel",  "show",
      "savefig", "subplot", "suptitle", "hist",   "scatter", "legend"};

  //! names of the targeted object in "mpl_toolkits.mplot3d" module
  const std::vector<std::string> _mplot3dObjectNames = {"Axes3D"};
};

template <typename DATA_TYPE>
py::object Matplotlib::plot(const std::vector<DATA_TYPE> &x,
                            const std::vector<DATA_TYPE> &y,
                            const std::string &color, const std::string &marker,
                            const std::string &linestyle) {
  return this->_objectMap["plot"](py::cast(x), py::cast(y), "color"_a = color,
                                  "marker"_a = marker,
                                  "linestyle"_a = linestyle);
}

template <typename DATA_TYPE>
py::object Matplotlib::hist(const std::vector<DATA_TYPE> &x,
                            const size_t bins) {
  return this->_objectMap["hist"](py::cast(x), bins);
}

template <typename DATA_TYPE>
py::object Matplotlib::scatter(const std::vector<DATA_TYPE> &x,
                               const std::vector<DATA_TYPE> &y,
                               const std::string &color,
                               const std::string &marker, const double alpha) {
  return this->_objectMap["scatter"](py::cast(x), py::cast(y), "c"_a = color,
                                     "marker"_a = marker, "alpha"_a = alpha);
}

template <typename DATA_TYPE>
void Matplotlib::scatter(py::object *axes, const std::vector<DATA_TYPE> &x,
                         const std::vector<DATA_TYPE> &y,
                         const std::string &marker) {
  axes->attr("scatter")(py::cast(x), py::cast(y), "marker"_a = marker);
}

template <typename DATA_TYPE>
void Matplotlib::scatter(py::object *axes, const std::vector<DATA_TYPE> &x,
                         const std::vector<DATA_TYPE> &y,
                         const std::vector<DATA_TYPE> &z,
                         const std::string &marker) {
  axes->attr("scatter")(py::cast(x), py::cast(y), py::cast(z),
                        "marker"_a = marker);
}

template <typename DATA_TYPE>
void Matplotlib::scatter3D(py::object *axes, const std::vector<DATA_TYPE> &x,
                           const std::vector<DATA_TYPE> &y,
                           const std::string &marker) {
  axes->attr("scatter3D")(py::cast(x), py::cast(y));
}

template <typename DATA_TYPE>
void Matplotlib::plot(py::object *axes, const std::vector<DATA_TYPE> &x,
                      const std::vector<DATA_TYPE> &y,
                      const std::vector<DATA_TYPE> &z, const std::string &color,
                      const std::string &marker) {
  axes->attr("plot")(py::cast(x), py::cast(y), py::cast(z), "color"_a = color,
                     "marker"_a = marker);
}

} // namespace vis
} // namespace pe

#endif /* MATPLOTLIBCPP_HPP_ */
