/**
 * @file    Surface.cpp
 *
 * @date    2019-08-03
 *
 * Copyright (c) organization
 *
 */

#include <cmath>
#include <iostream>
#include <vector>

#include <matplotlib_cpp/MatplotlibCpp.hpp>

int main(int argc, char* argv[])
{
    pe::vis::Matplotlib mpllib;

    if (!mpllib.imported()) {
        std::cout << "Failed to import matplotlib library\n";
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<double>> x, y, z;
    for (double i = -5; i <= 5; i += 0.25) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = -5; j <= 5; j += 0.25) {
            x_row.emplace_back(i);
            y_row.emplace_back(j);
            z_row.emplace_back(std::sin(std::hypot(i, j)));
        }
        x.emplace_back(x_row);
        y.emplace_back(y_row);
        z.emplace_back(z_row);
    }

    mpllib.initializeAxes3D();
    mpllib.plot_surface(x, y, z,
                        {{"cmap", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("plasma")},
                         {"linewidth", pe::vis::Matplotlib::createAnyBaseMapData<double>(0)}});

    mpllib.savefig("Surface.png");
    mpllib.show();

    return 0;
}
