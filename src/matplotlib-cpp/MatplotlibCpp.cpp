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

#include <pybind11/stl.h>

#include "ModuleEmbedding.hpp"
#include <matplotlib-cpp/MatplotlibCpp.hpp>

namespace pe
{
namespace vis
{
using namespace pybind11::literals;  // NOLINT(build/namespaces_literals)

class PYBIND11_EXPORT Matplotlib::MatplotlibImpl
{
 public:
    //! objectMap -> (python object name, corresponding python object)
    using ObjectMap = std::map<std::string, pybind11::object>;

    MatplotlibImpl();
    ~MatplotlibImpl();

    /**
     *  @brief constant getter of imported flag
     */
    const bool& imported() const;

    //@{
    /** wrapped methods from "matplotlib.pyplot" module. mainly used for 2d
     * visualization
     */
    pybind11::object figure(const double width = 25, const double height = 25,
                            const pybind11::dict& kwargs = pybind11::dict());

    pybind11::object title(const std::string& titleStr, const pybind11::dict& kwargs = pybind11::dict());
    pybind11::object xlabel(const std::string& xlabelStr, const pybind11::dict& kwargs = pybind11::dict());
    pybind11::object ylabel(const std::string& ylabelStr, const pybind11::dict& kwargs = pybind11::dict());
    pybind11::object show(const pybind11::dict& kwargs = pybind11::dict());
    pybind11::object savefig(const std::string& figName, const pybind11::dict& kwargs = pybind11::dict());

    template <typename DATA_TYPE>
    pybind11::object plot(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                          const pybind11::dict& kwargs = pybind11::dict("color"_a = "green", "marker"_a = "o",
                                                                        "linestyle"_a = "dashed"));

    pybind11::object subplot(const size_t nrows, const size_t ncols, const size_t index,
                             const pybind11::dict& kwargs = pybind11::dict());
    pybind11::object suptitle(const std::string& suptitleStr, const pybind11::dict& kwargs = pybind11::dict());

    template <typename DATA_TYPE>
    pybind11::object hist(const std::vector<DATA_TYPE>& x, const size_t bins,
                          const pybind11::dict& kwargs = pybind11::dict());

    template <typename DATA_TYPE>
    pybind11::object scatter(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                             const pybind11::dict& kwargs = pybind11::dict("color"_a = "pink", "marker"_a = "o",
                                                                           "alpha"_a = 0.5));

    pybind11::object legend(const std::string& location = "best", const pybind11::dict& kwargs = pybind11::dict());
    //@}

    //@{
    /** wrapped methods from "mpl_toolkits.mplot3d" module. mainly used for 3d
     * visualization
     */
    void initializeAxes(const double width, const double height, const pybind11::dict& kwargs = pybind11::dict());
    void set_xlabelAxes(const std::string& xlabel, const pybind11::dict& kwargs = pybind11::dict());
    void set_ylabelAxes(const std::string& ylabel, const pybind11::dict& kwargs = pybind11::dict());

    template <typename DATA_TYPE>
    void scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                     const pybind11::dict& kwargs = pybind11::dict("marker"_a = "o"));

    template <typename DATA_TYPE>
    void scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const std::vector<DATA_TYPE>& z,
                     const pybind11::dict& kwargs = pybind11::dict("marker"_a = "o"));

    template <typename DATA_TYPE>
    void scatter3DAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                       const pybind11::dict& kwargs = pybind11::dict("marker"_a = "o"));

    template <typename DATA_TYPE>
    void plotAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const std::vector<DATA_TYPE>& z,
                  const pybind11::dict& kwargs = pybind11::dict("color"_a = "green", "marker"_a = "o"));
    //@}

    pybind11::dict transformAnyBaseToDict(const AnyBaseMap& anyBM) const;

 private:
    /**
     *  @brief initialize python object corresponding to the name held in object map.
     */
    void updateObjectMap();

 private:
    //! Embedder of "matplotlib" module.
    ModuleEmbedding _mpl;

    //! Embedder of "matplotlib.pyplot" module.
    ModuleEmbedding _plt;

    //! Embedder of "mpl_toolkits.mplot3d" module.
    ModuleEmbedding _mplot3d;

    //! boolean flag to check if matplotlib's targeted modules have been imported successfully.
    bool _imported = false;

    //! map to contain python objects of the targeted methods in matplotlib library and the names of the objects.
    ObjectMap _objectMap;

    //! names of the targeted object in "matplotlib.pyplot" module.
    const std::vector<std::string> _pltObjectNames = {"figure",  "plot",    "title",    "xlabel", "ylabel",  "show",
                                                      "savefig", "subplot", "suptitle", "hist",   "scatter", "legend"};

    //! names of the targeted object in "mpl_toolkits.mplot3d" module.
    const std::vector<std::string> _mplot3dObjectNames = {"Axes3D"};
};

Matplotlib::MatplotlibImpl::MatplotlibImpl()
    : _mpl(ModuleEmbedding("matplotlib")), _plt(ModuleEmbedding("matplotlib.pyplot")),
      _mplot3d(ModuleEmbedding("mpl_toolkits.mplot3d"))
{
    this->_imported = this->_mpl.importModule();
    this->_imported = this->_plt.importModule();
    this->_imported = this->_mplot3d.importModule();

    this->updateObjectMap();
}

Matplotlib::MatplotlibImpl::~MatplotlibImpl() = default;

const bool& Matplotlib::MatplotlibImpl::imported() const
{
    return this->_imported;
}

void Matplotlib::MatplotlibImpl::updateObjectMap()
{
    if (!this->_imported) {
        return;
    }

    for (const std::string& objectName : this->_pltObjectNames) {
        this->_objectMap.emplace(objectName, this->_plt.pyModule().attr(objectName.c_str()));
    }

    for (const std::string& objectName : this->_mplot3dObjectNames) {
        this->_objectMap.emplace(objectName, this->_mplot3d.pyModule().attr(objectName.c_str()));
    }
}

pybind11::dict Matplotlib::MatplotlibImpl::transformAnyBaseToDict(const AnyBaseMap& anyBM) const
{
    pybind11::dict result;
    for (const auto& anyB : anyBM) {
        std::pair<std::string, std::shared_ptr<AnyBase>> anyBData = anyB.second;
        if (anyBData.first == "") {
            continue;
        }

        if (anyBData.first == "bool") {
            result[pybind11::cast(anyB.first)] = dynamic_cast<Any<bool>&>(*anyBData.second).data;
        } else if (anyBData.first == "int") {
            result[pybind11::cast(anyB.first)] = dynamic_cast<Any<int>&>(*anyBData.second).data;
        } else if (anyBData.first == "float") {
            result[pybind11::cast(anyB.first)] = dynamic_cast<Any<float>&>(*anyBData.second).data;
        } else if (anyBData.first == "double") {
            result[pybind11::cast(anyB.first)] = dynamic_cast<Any<double>&>(*anyBData.second).data;
        } else {
            result[pybind11::cast(anyB.first)] = dynamic_cast<Any<std::string>&>(*anyBData.second).data;
        }
    }

    return result;
}

pybind11::object Matplotlib::MatplotlibImpl::figure(const double width, const double height,
                                                    const pybind11::dict& kwargs)
{
    return this->_objectMap["figure"]("figsize"_a = pybind11::make_tuple(15, 5), **kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::title(const std::string& titleStr, const pybind11::dict& kwargs)
{
    return this->_objectMap["title"](titleStr, **kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::xlabel(const std::string& xlabelStr, const pybind11::dict& kwargs)
{
    return this->_objectMap["xlabel"](xlabelStr, **kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::ylabel(const std::string& ylabelStr, const pybind11::dict& kwargs)
{
    return this->_objectMap["ylabel"](ylabelStr, **kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::show(const pybind11::dict& kwargs)
{
    return this->_objectMap["show"](**kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::savefig(const std::string& figName, const pybind11::dict& kwargs)
{
    return this->_objectMap["savefig"](figName, **kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::subplot(const size_t nrows, const size_t ncols, const size_t index,
                                                     const pybind11::dict& kwargs)
{
    return this->_objectMap["subplot"](nrows, ncols, index, **kwargs);
}

pybind11::object Matplotlib::MatplotlibImpl::suptitle(const std::string& suptitleStr, const pybind11::dict& kwargs)
{
    return this->_objectMap["suptitle"](suptitleStr);
}

pybind11::object Matplotlib::MatplotlibImpl::legend(const std::string& location, const pybind11::dict& kwargs)
{
    return this->_objectMap["legend"]("loc"_a = location, **kwargs);
}

void Matplotlib::MatplotlibImpl::initializeAxes(const double width, const double height, const pybind11::dict& kwargs)
{
    pybind11::object fig = this->figure(width, height, kwargs);
    this->_objectMap["Axes3D"] = this->_objectMap["Axes3D"](fig, **kwargs);
}

void Matplotlib::MatplotlibImpl::set_xlabelAxes(const std::string& xlabel, const pybind11::dict& kwargs)
{
    this->_objectMap["Axes3D"].attr("set_xlabel")(xlabel, **kwargs);
}

void Matplotlib::MatplotlibImpl::set_ylabelAxes(const std::string& ylabel, const pybind11::dict& kwargs)
{
    this->_objectMap["Axes3D"].attr("set_ylabel")(ylabel, **kwargs);
}

template <typename DATA_TYPE>
pybind11::object Matplotlib::MatplotlibImpl::plot(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                                                  const pybind11::dict& kwargs)
{
    return this->_objectMap["plot"](pybind11::cast(x), pybind11::cast(y), **kwargs);
}

template <typename DATA_TYPE>
pybind11::object Matplotlib::MatplotlibImpl::hist(const std::vector<DATA_TYPE>& x, const size_t bins,
                                                  const pybind11::dict& kwargs)
{
    return this->_objectMap["hist"](pybind11::cast(x), bins, **kwargs);
}

template <typename DATA_TYPE>
pybind11::object Matplotlib::MatplotlibImpl::scatter(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                                                     const pybind11::dict& kwargs)
{
    return this->_objectMap["scatter"](pybind11::cast(x), pybind11::cast(y), **kwargs);
}

template <typename DATA_TYPE>
void Matplotlib::MatplotlibImpl::scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                                             const pybind11::dict& kwargs)
{
    this->_objectMap["Axes3D"].attr("scatter")(pybind11::cast(x), pybind11::cast(y), **kwargs);
}

template <typename DATA_TYPE>
void Matplotlib::MatplotlibImpl::scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                                             const std::vector<DATA_TYPE>& z, const pybind11::dict& kwargs)
{
    this->_objectMap["Axes3D"].attr("scatter")(pybind11::cast(x), pybind11::cast(y), pybind11::cast(z), **kwargs);
}

template <typename DATA_TYPE>
void Matplotlib::MatplotlibImpl::scatter3DAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                                               const pybind11::dict& kwargs)
{
    this->_objectMap["Axes3D"].attr("scatter3D")(pybind11::cast(x), pybind11::cast(y), **kwargs);
}

template <typename DATA_TYPE>
void Matplotlib::MatplotlibImpl::plotAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                                          const std::vector<DATA_TYPE>& z, const pybind11::dict& kwargs)
{
    this->_objectMap["Axes3D"].attr("plot")(pybind11::cast(x), pybind11::cast(y), pybind11::cast(z), **kwargs);
}

//-------------------------------------------------------------------------------------------------------------//

const std::unordered_map<std::type_index, std::string> Matplotlib::TYPE_NAMES = {
    {std::type_index(typeid(bool)), "bool"},
    {std::type_index(typeid(int)), "int"},
    {std::type_index(typeid(float)), "float"},
    {std::type_index(typeid(double)), "double"},
    {std::type_index(typeid(std::string)), "string"}};

Matplotlib::Matplotlib() : piml(std::unique_ptr<MatplotlibImpl>(new MatplotlibImpl))
{
}

Matplotlib::~Matplotlib() = default;

const bool& Matplotlib::imported() const
{
    return this->piml->imported();
}

void Matplotlib::figure(const double width, const double height, const AnyBaseMap& anyBM)
{
    this->piml->figure(width, height, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::title(const std::string& titleStr, const AnyBaseMap& anyBM)
{
    this->piml->title(titleStr, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::xlabel(const std::string& xlabelStr, const AnyBaseMap& anyBM)
{
    this->piml->xlabel(xlabelStr, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::ylabel(const std::string& ylabelStr, const AnyBaseMap& anyBM)
{
    this->piml->ylabel(ylabelStr, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::show(const AnyBaseMap& anyBM)
{
    this->piml->show(this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::savefig(const std::string& figName, const AnyBaseMap& anyBM)
{
    this->piml->savefig(figName, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::subplot(const size_t nrows, const size_t ncols, const size_t index, const AnyBaseMap& anyBM)
{
    this->piml->subplot(nrows, ncols, index, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::suptitle(const std::string& suptitleStr, const AnyBaseMap& anyBM)
{
    this->piml->suptitle(suptitleStr, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::legend(const std::string& location, const AnyBaseMap& anyBM)
{
    this->piml->legend(location, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::initializeAxes(const double width, const double height, const AnyBaseMap& anyBM)
{
    this->piml->initializeAxes(width, height, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::set_xlabelAxes(const std::string& xlabel, const AnyBaseMap& anyBM)
{
    this->piml->set_xlabelAxes(xlabel, this->piml->transformAnyBaseToDict(anyBM));
}

void Matplotlib::set_ylabelAxes(const std::string& ylabel, const AnyBaseMap& anyBM)
{
    this->piml->set_ylabelAxes(ylabel, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::plot(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM)

{
    this->piml->plot(x, y, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::hist(const std::vector<DATA_TYPE>& x, const size_t bins, const AnyBaseMap& anyBM)
{
    this->piml->hist(x, bins, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::scatter(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM)

{
    this->piml->scatter(x, y, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM)
{
    this->piml->scatterAxes(x, y, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                             const std::vector<DATA_TYPE>& z, const AnyBaseMap& anyBM)
{
    this->piml->scatterAxes(x, y, z, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::scatter3DAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                               const AnyBaseMap& anyBM)
{
    this->piml->scatter3DAxes(x, y, this->piml->transformAnyBaseToDict(anyBM));
}

template <typename DATA_TYPE>
void Matplotlib::plotAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                          const std::vector<DATA_TYPE>& z, const AnyBaseMap& anyBM)
{
    this->piml->plotAxes(x, y, z, this->piml->transformAnyBaseToDict(anyBM));
}

#define QUICK_CAST(DATA_TYPE)                                                                                          \
    template void Matplotlib::plot<DATA_TYPE>(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,        \
                                              const AnyBaseMap& anyBM);                                                \
    template void Matplotlib::hist<DATA_TYPE>(const std::vector<DATA_TYPE>& x, const size_t bins,                      \
                                              const AnyBaseMap& anyBM);                                                \
    template void Matplotlib::scatter<DATA_TYPE>(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,     \
                                                 const AnyBaseMap& anyBM);                                             \
    template void Matplotlib::scatterAxes<DATA_TYPE>(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, \
                                                     const AnyBaseMap& anyBM);                                         \
    template void Matplotlib::scatterAxes<DATA_TYPE>(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, \
                                                     const std::vector<DATA_TYPE>& z, const AnyBaseMap& anyBM);        \
    template void Matplotlib::scatter3DAxes<DATA_TYPE>(const std::vector<DATA_TYPE>& x,                                \
                                                       const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM);      \
    template void Matplotlib::plotAxes<DATA_TYPE>(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,    \
                                                  const std::vector<DATA_TYPE>& z, const AnyBaseMap& anyBM);

QUICK_CAST(double);
QUICK_CAST(float);
QUICK_CAST(int);

}  // namespace vis
}  // namespace pe
