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

#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AnyBase.hpp"

namespace pe
{
/**
 *  @brief visualization-related namespace
 */
namespace vis
{
/**
 *  @brief Holder of modules embedded inside matplotlib library
 *
 */
class Matplotlib
{
 public:
    using AnyBaseMap = std::map<std::string, std::pair<std::string, std::shared_ptr<AnyBase>>>;
    static const std::unordered_map<std::type_index, std::string> TYPE_NAMES;

    Matplotlib();
    ~Matplotlib();

    /**
     *  @brief constant getter of imported flag
     */
    const bool& imported() const;

    //@{
    /** wrapped methods from "matplotlib.pyplot" module. mainly used for 2d visualization
     */
    void figure(const double width = 25, const double height = 25, const AnyBaseMap& anyBM = {});

    void title(const std::string& titleStr, const AnyBaseMap& anyBM = {});
    void xlabel(const std::string& xlabelStr, const AnyBaseMap& anyBM = {});
    void xlim(const double left, const double right, const AnyBaseMap& anyBM = {});
    void ylim(const double bottom, const double top, const AnyBaseMap& anyBM = {});
    void ylabel(const std::string& ylabelStr, const AnyBaseMap& anyBM = {});
    void axis(const std::string& axisType = "scaled", const AnyBaseMap& anyBM = {});
    void show(const AnyBaseMap& anyBM = {});
    void savefig(const std::string& figName, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void plot(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
              const AnyBaseMap& anyBM = {{"color", createAnyBaseMapData<std::string>("pink")}});

    template <typename DATA_TYPE>
    void plot(const std::vector<DATA_TYPE>& x, const std::function<DATA_TYPE(DATA_TYPE)>& xFunc,
              const AnyBaseMap& anyBM = {{"color", createAnyBaseMapData<std::string>("pink")}});

    void subplot(const size_t nrows, const size_t ncols, const size_t index, const AnyBaseMap& anyBM = {});
    void suptitle(const std::string& suptitleStr, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void hist(const std::vector<DATA_TYPE>& x, const size_t bins, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void scatter(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                 const AnyBaseMap& anyBM = {{"color", createAnyBaseMapData<std::string>("pink")},
                                            {"marker", createAnyBaseMapData<std::string>("o")},
                                            {"alpha", createAnyBaseMapData<double>(0.5)}});

    void legend(const std::string& location = "best", const AnyBaseMap& anyBM = {});
    void clf();
    void pause(const double interval);
    void grid(const AnyBaseMap& anyBM = {});
    //@}

    //@{
    /** wrapped methods from "mpl_toolkits.mplot3d" module. mainly used for 3d  visualization
     */
    void initializeAxes3D(const double width = 25, const double height = 25, const AnyBaseMap& anyBM = {});
    void set_xlabelAxes3D(const std::string& xlabel, const AnyBaseMap& anyBM = {});
    void set_ylabelAxes3D(const std::string& ylabel, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void scatterAxes3D(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                       const AnyBaseMap& anyBM = {{"marker", createAnyBaseMapData<std::string>("o")}});

    template <typename DATA_TYPE>
    void scatterAxes3D(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                       const std::vector<DATA_TYPE>& z,
                       const AnyBaseMap& anyBM = {{"marker", createAnyBaseMapData<std::string>("o")}});

    template <typename DATA_TYPE>
    void scatter3DAxes3D(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y,
                         const AnyBaseMap& anyBM = {{"marker", createAnyBaseMapData<std::string>("o")}});

    template <typename DATA_TYPE>
    void plotAxes3D(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const std::vector<DATA_TYPE>& z,
                    const AnyBaseMap& anyBM = {{"marker", createAnyBaseMapData<std::string>("o")},
                                               {"color", createAnyBaseMapData<std::string>("green")}});

    template <typename DATA_TYPE>
    void plot_surface(const std::vector<std::vector<DATA_TYPE>>& x, const std::vector<std::vector<DATA_TYPE>>& y,
                      const std::vector<std::vector<DATA_TYPE>>& z, const AnyBaseMap& anyBM = {});
    //@}

    //@{
    /** wrapped methods from "matplotlib.axes" module.
     */
    void axes(const double width = 50, const double height = 50, const AnyBaseMap& anyBM = {});
    void set_xlimAxes(const double left, const double right, const AnyBaseMap& anyBM = {});
    void set_ylimAxes(const double bottom, const double top, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void add_patch(const std::vector<std::array<DATA_TYPE, 2>>& vertices, const std::vector<int>& codes,
                   const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void plotAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void textAxes(const DATA_TYPE x, const DATA_TYPE y, const std::string& s, const AnyBaseMap& anyBM = {});
    //@}

    template <typename PARAM_DATA_TYPE>
    static std::pair<std::string, std::shared_ptr<AnyBase>> createAnyBaseMapData(PARAM_DATA_TYPE data);

 private:
    class MatplotlibImpl;
    std::unique_ptr<MatplotlibImpl> piml;
};

template <typename PARAM_DATA_TYPE>
std::pair<std::string, std::shared_ptr<AnyBase>> Matplotlib::createAnyBaseMapData(PARAM_DATA_TYPE data)
{
    auto it = TYPE_NAMES.find(std::type_index(typeid(data)));
    std::string type_name = (it != TYPE_NAMES.end()) ? it->second : "";

    return std::make_pair(type_name, std::make_shared<Any<PARAM_DATA_TYPE>>(data));
}

}  // namespace vis
}  // namespace pe
