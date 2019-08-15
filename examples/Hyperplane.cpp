/**
 * @file    Hyperplane.cpp
 *
 * @author  btran
 *
 * @date    2019-08-07
 *
 * Copyright (c) organization
 *
 */

#include <cmath>
#include <iostream>
#include <vector>

#include <matplotlib_cpp/MatplotlibCpp.hpp>

std::vector<double> linspace(const double min, const double max, const size_t numPoint = 20);

template <typename DATA_TYPE>
std::array<std::vector<std::vector<DATA_TYPE>>, 2> meshgrid(const std::vector<DATA_TYPE>& xs,
                                                            const std::vector<DATA_TYPE>& ys);

int main(int argc, char* argv[])
{
    // import modules of matplotlib library
    pe::vis::Matplotlib mpllib;

    // check if the modules are imported successully or not
    if (!mpllib.imported()) {
        std::cout << "Failed to import matplotlib library\n";
        exit(EXIT_FAILURE);
    }

    // plot R(3) hyperplane (2x + 3y + 2.5z - 2 = 0)
    // normal p = (2,3,2.5)

    const double min = 0.0;
    const double max = 10.0;
    const size_t num = 50;

    std::vector<double> xs = linspace(-10.0, 10.0, 50);
    std::vector<double> ys = linspace(-10.0, 10.0, 50);

    const std::array<double, 3> normal = {2, 3, 2.5};

    auto gridXY = meshgrid(xs, ys);

    std::vector<std::vector<double>> Z;
    Z.reserve(gridXY[0].size());

    for (size_t ih = 0; ih < gridXY[0].size(); ++ih) {
        std::vector<double> curV;
        curV.reserve(gridXY[0][0].size());

        for (size_t iw = 0; iw < gridXY[0][0].size(); ++iw) {
            curV.emplace_back((2 - 2 * gridXY[0][ih][iw] - 3 * gridXY[1][ih][iw]) / 2.5);
        }

        Z.emplace_back(curV);
    }

    // half space 2x + 3y + 2.5z - 2 >= 0
    // point(1,2,z_axis)
    // choose z_axis = (2 - (2 * x_axis + 3 * y_axis) / 2.5) + epsilon

    const double x = 1;
    const double y = 2;
    const double epsilon = 7.9;
    const double z = (2 - (2 * x + 3 * y)) / 2.5 + epsilon;

    mpllib.initializeAxes3D();
    mpllib.plot_surface(gridXY[0], gridXY[1], Z,
                        {{"cmap", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("plasma")},
                         {"linewidth", pe::vis::Matplotlib::createAnyBaseMapData<double>(0)}});
    mpllib.scatterAxes3D<double>({x}, {y}, {z});

    mpllib.savefig("Hyperplane.png");
    mpllib.show();

    return EXIT_SUCCESS;
}

std::vector<double> linspace(const double min, const double max, const size_t num)
{
    std::vector<double> result;
    result.reserve(num);
    result.emplace_back(min);

    if (num < 2) {
        throw std::runtime_error("num should be bigger than 2");
    }

    double delta = (max - min) / (num - 1);
    double curV = min;
    for (size_t i = 0; i < num - 2; ++i) {
        curV += delta;
        result.emplace_back(curV);
    }

    result.emplace_back(max);
    return result;
}

template <typename DATA_TYPE>
std::array<std::vector<std::vector<DATA_TYPE>>, 2> meshgrid(const std::vector<DATA_TYPE>& xs,
                                                            const std::vector<DATA_TYPE>& ys)
{
    std::vector<std::vector<DATA_TYPE>> X, Y;
    X.reserve(ys.size());
    Y.reserve(ys.size());

    for (size_t i = 0; i < ys.size(); ++i) {
        X.emplace_back(xs);

        std::vector<DATA_TYPE> curV(xs.size());
        std::fill(curV.begin(), curV.end(), ys[i]);
        Y.emplace_back(curV);
    }

    return {X, Y};
}
