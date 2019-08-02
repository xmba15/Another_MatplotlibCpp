/**
 * @file    MatplotlibCpp.cpp
 *
 * @author  btran
 *
 * @date    2019-08-01
 *
 * Copyright (c) organization
 *
 */

#include <matplotlib-cpp/MatplotlibCpp.hpp>

namespace pe {
namespace vis {
Matplotlib::Matplotlib()
    : _mpl(ModuleEmbedding("matplotlib")),
      _plt(ModuleEmbedding("matplotlib.pyplot")),
      _mplot3d(ModuleEmbedding("mpl_toolkits.mplot3d")) {
  this->_imported = this->_mpl.import();
  this->_imported = this->_plt.import();
  this->_imported = this->_mplot3d.import();

  this->updateObjectMap();
}

const bool &Matplotlib::imported() const { return this->_imported; }

const Matplotlib::ObjectMap &Matplotlib::objectMap() const {
  return this->_objectMap;
}

const ModuleEmbedding &Matplotlib::mpl() const { return this->_mpl; }

const ModuleEmbedding &Matplotlib::plt() const { return this->_plt; }

const ModuleEmbedding &Matplotlib::mplot3d() const { return this->_mplot3d; }

void Matplotlib::updateObjectMap() {
  if (!this->_imported) {
    return;
  }

  for (const std::string &objectName : this->_pltObjectNames) {
    this->_objectMap.emplace(objectName,
                             this->_plt.pyModule().attr(objectName.c_str()));
  }

  for (const std::string &objectName : this->_mplot3dObjectNames) {
    this->_objectMap.emplace(
        objectName, this->_mplot3d.pyModule().attr(objectName.c_str()));
  }
}

py::object Matplotlib::figure(const double width, const double height,
                              const py::dict &kwargs) {
  return this->_objectMap["figure"]("figsize"_a = py::make_tuple(15, 5),
                                    **kwargs);
}

py::object Matplotlib::title(const std::string &titleStr,
                             const py::dict &kwargs) {
  return this->_objectMap["title"](titleStr, **kwargs);
}

py::object Matplotlib::xlabel(const std::string &xlabelStr,
                              const py::dict &kwargs) {
  return this->_objectMap["xlabel"](xlabelStr, **kwargs);
}

py::object Matplotlib::ylabel(const std::string &ylabelStr,
                              const py::dict &kwargs) {

  return this->_objectMap["ylabel"](ylabelStr, **kwargs);
}

py::object Matplotlib::show(const py::dict &kwargs) {
  return this->_objectMap["show"](**kwargs);
}

py::object Matplotlib::savefig(const std::string &figName,
                               const py::dict &kwargs) {
  return this->_objectMap["savefig"](figName, **kwargs);
}

py::object Matplotlib::subplot(const size_t nrows, const size_t ncols,
                               const size_t index, const py::dict &kwargs) {
  return this->_objectMap["subplot"](nrows, ncols, index, **kwargs);
}

py::object Matplotlib::suptitle(const std::string &suptitleStr,
                                const py::dict &kwargs) {
  return this->_objectMap["suptitle"](suptitleStr);
}

py::object Matplotlib::legend(const std::string &location,
                              const py::dict &kwargs) {
  return this->_objectMap["legend"]("loc"_a = location, **kwargs);
}

py::object Matplotlib::axes(const py::object &figure, const py::dict &kwargs) {
  return this->_objectMap["Axes3D"](figure, **kwargs);
}

void Matplotlib::set_xlabel(py::object *axes, const std::string &xlabel,
                            const py::dict &kwargs) {
  axes->attr("set_xlabel")(xlabel, **kwargs);
}

void Matplotlib::set_ylabel(py::object *axes, const std::string &ylabel,
                            const py::dict &kwargs) {
  axes->attr("set_ylabel")(ylabel, **kwargs);
}

} // namespace vis
} // namespace pe
