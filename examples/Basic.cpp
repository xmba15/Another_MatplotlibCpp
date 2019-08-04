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

#include <matplotlib-cpp/MatplotlibCpp.hpp>

int main(int argc, char* argv[])
{
    pe::vis::Matplotlib mpllib;

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

    mpllib.figure(1200, 780);

    mpllib.plot(x, y);
    mpllib.plot(x, w,
                {
                    {"color", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("r")},
                    {"linestyle", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("--")},
                });

    mpllib.plot(x, z,
                {
                    {"label", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("log(x)")},
                });

    mpllib.xlim(0, 1000 * 1000);
    mpllib.grid();
    mpllib.title("Sample plot");
    mpllib.legend();

    mpllib.savefig("Basic.png");
    mpllib.show();

    return 0;
}
