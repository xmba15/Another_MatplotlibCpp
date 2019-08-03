/**
 * @file    Animation.cpp
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

    int n = 1000;
    std::vector<double> x, y, z;
    x.reserve(n);
    y.reserve(n);
    z.reserve(n);

    for (size_t i = 0; i < n; i++) {
        x.emplace_back(i * i);
        y.emplace_back(std::sin(2 * M_PI * i / 360.0));
        z.emplace_back(std::log(i));

        if (i % 10 == 0) {
            mpllib.clf();

            mpllib.plot(x, y,
                        {
                            {"label", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("log(x)")},
                        });

            mpllib.xlim(0, n * n);

            mpllib.title("Sample figure");

            mpllib.legend();

            mpllib.pause(0.01);
        }
    }

    return 0;
}
