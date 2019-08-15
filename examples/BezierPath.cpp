/**
 * @file    BezierPath.cpp
 *
 * @date    2019-08-04
 *
 * Copyright (c) organization
 *
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include <matplotlib_cpp/MatplotlibCpp.hpp>

enum MPL_PATH { STOP = 0, MOVETO = 1, LINETO = 2, CURVE3 = 3, CURVE4 = 4, CLOSEPOLY = 5 };

int main(int argc, char* argv[])
{
    pe::vis::Matplotlib mpllib;

    if (!mpllib.imported()) {
        std::cout << "Failed to import matplotlib library\n";
        exit(EXIT_FAILURE);
    }

    mpllib.axes(8, 4);
    std::vector<std::array<double, 2>> vertices = {{0., 0.}, {0.2, 1.}, {1., 0.8}, {0.8, 0.}};
    std::vector<int> codes = {MOVETO, CURVE4, CURVE4, CURVE4};

    mpllib.add_patch(vertices, codes,
                     {
                         {"facecolor", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("none")},
                         {"lw", pe::vis::Matplotlib::createAnyBaseMapData<int>(2)},
                     });

    std::vector<double> xs, ys;
    xs.reserve(vertices.size());
    ys.reserve(vertices.size());

    std::transform(vertices.cbegin(), vertices.cend(), std::back_inserter(xs),
                   [](const std::array<double, 2>& p) { return p[0]; });

    std::transform(vertices.cbegin(), vertices.cend(), std::back_inserter(ys),
                   [](const std::array<double, 2>& p) { return p[1]; });

    mpllib.plotAxes(xs, ys,
                    {
                        {"marker", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("x")},
                        {"linestyle", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("--")},
                        {"color", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("black")},
                        {"lw", pe::vis::Matplotlib::createAnyBaseMapData<int>(2)},
                        {"ms", pe::vis::Matplotlib::createAnyBaseMapData<int>(10)},
                    });

    mpllib.textAxes(-0.05, -0.05, "P0");
    mpllib.textAxes(0.15, 1.05, "P");
    mpllib.textAxes(1.05, 0.85, "P2");
    mpllib.textAxes(0.85, -0.05, "P3");

    mpllib.set_xlimAxes(-0.1, 1.1);
    mpllib.set_ylimAxes(-0.1, 1.1);

    mpllib.savefig("BezierPath");
    mpllib.show();

    return 0;
}
