/**
 * @file    Modern.cpp
 *
 * @date    2019-08-03
 *
 * Copyright (c) organization
 *
 */

#include <cmath>
#include <functional>
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

    int n = 5000;
    std::vector<double> x, y;
    x.reserve(n);
    y.reserve(n);

    for (int i = 0; i < n; ++i) {
        double t = 2 * M_PI * i / n;
        x.emplace_back(16 * sin(t) * sin(t) * sin(t));
        y.emplace_back(13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
    }

    mpllib.plot(x, y,
                {
                    {"color", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("r")},
                    {"linestyle", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("-")},
                });

    std::function<double(double)> xFunc = [](double x) { return (12.5 + std::abs(std::sin(x))); };
    mpllib.plot(x, xFunc,
                {
                    {"color", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("k")},
                    {"linestyle", pe::vis::Matplotlib::createAnyBaseMapData<std::string>("-")},
                });

    mpllib.savefig("Modern.png");
    mpllib.show();

    return 0;
}
