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

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace pe
{
/**
 *  @brief visualization-related namespace
 */
namespace vis
{
// using namespace pybind11::literals;  // NOLINT(build/namespaces_literals)

/**
 *  @brief Holder of modules embedded inside matplotlib library
 *
 */
class Matplotlib
{
 public:
    using AnyBaseMap = std::map<int, int>;

    Matplotlib();
    ~Matplotlib();

    /**
     *  @brief constant getter of imported flag
     */
    const bool& imported() const;

    //@{
    /** wrapped methods from "matplotlib.pyplot" module. mainly used for 2d
     * visualization
     */
    void figure(const double width = 25, const double height = 25, const AnyBaseMap& anyBM = {});

    void title(const std::string& titleStr, const AnyBaseMap& anyBM = {});
    void xlabel(const std::string& xlabelStr, const AnyBaseMap& anyBM = {});
    void ylabel(const std::string& ylabelStr, const AnyBaseMap& anyBM = {});
    void show(const AnyBaseMap& anyBM = {});
    void savefig(const std::string& figName, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void plot(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM = {});

    void subplot(const size_t nrows, const size_t ncols, const size_t index, const AnyBaseMap& anyBM = {});
    void suptitle(const std::string& suptitleStr, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void hist(const std::vector<DATA_TYPE>& x, const size_t bins, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void scatter(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM = {});

    void legend(const std::string& location = "best", const AnyBaseMap& anyBM = {});
    //@}

    //@{
    /** wrapped methods from "mpl_toolkits.mplot3d" module. mainly used for 3d
     * visualization
     */
    void initializeAxes(const double width, const double height, const AnyBaseMap& anyBM = {});
    void set_xlabelAxes(const std::string& xlabel, const AnyBaseMap& anyBM = {});
    void set_ylabelAxes(const std::string& ylabel, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void scatterAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const std::vector<DATA_TYPE>& z,
                     const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void scatter3DAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const AnyBaseMap& anyBM = {});

    template <typename DATA_TYPE>
    void plotAxes(const std::vector<DATA_TYPE>& x, const std::vector<DATA_TYPE>& y, const std::vector<DATA_TYPE>& z,
                  const AnyBaseMap& anyBM = {});
    //@}

 private:
    class MatplotlibImpl;
    std::unique_ptr<MatplotlibImpl> piml;
};

}  // namespace vis
}  // namespace pe

#endif /* MATPLOTLIBCPP_HPP_ */
