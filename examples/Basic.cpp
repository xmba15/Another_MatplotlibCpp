/**
 * @file    Basic.cpp
 *
 * @date    2019-08-02
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
    // import modules of matplotlib library
    pe::vis::Matplotlib mpllib;

    // check if the modules are imported successully or not
    if (!mpllib.imported()) {
        std::cout << "Failed to import matplotlib library\n";
        exit(EXIT_FAILURE);
    }

    int n = 5000;
    std::vector<double> x, y, z, w(n, 2);
    x.reserve(n);
    y.reserve(n);
    z.reserve(n);

    for (int i = 0; i < n; ++i) {
        x.emplace_back(i * i);
        y.emplace_back(std::sin(2 * M_PI * i / 360.0));
        z.emplace_back(std::log(i));
    }

    // create a figure of desired size
    mpllib.figure(1200, 780);

    // plot with default parameters
    mpllib.plot(x, y);

    // plot with user-input parameters
    mpllib.plot(x, w,
                {
                    {"color", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("r")},
                    {"linestyle", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("--")},
                });

    // plot with user-input parameters
    mpllib.plot(x, z,
                {
                    {"label", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("log(x)")},
                    {"lw", pe::vis::Matplotlib::createAnyBaseMapData<int>(2)},
                });

    // limit for x axis
    mpllib.xlim(0, 1000 * 1000);

    // add grid
    mpllib.grid();

    // add title
    mpllib.title("Sample plot");

    // add legend with default location (best)
    mpllib.legend();

    // save figure
    mpllib.savefig("Basic.png");

    // show figure
    mpllib.show();

    return 0;
}
