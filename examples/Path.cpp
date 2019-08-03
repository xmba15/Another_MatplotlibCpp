/**
 * @file    Path.cpp
 *
 * @date    2019-08-04
 *
 * Copyright (c) organization
 *
 */

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

    mpllib.axes(5, 5);
    std::vector<std::array<double, 2>> vertices = {{0., 0.}, {0., 1.}, {1., 1.}, {1., 0.}, {0., 0.}};
    std::vector<int> codes = {MOVETO, LINETO, LINETO, LINETO, CLOSEPOLY};
    mpllib.set_xlimAxes(-2, 2);
    mpllib.set_ylimAxes(-2, 2);

    mpllib.add_patch(vertices, codes,
                     {
                         {"facecolor", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("orange")},
                         {"lw", pe::vis::Matplotlib::createAnyBaseMapData<int>(2)},
                     });

    mpllib.savefig("Path.png");
    mpllib.show();

    return 0;
}
