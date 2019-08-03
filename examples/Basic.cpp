/**
 * @file    Basic.cpp
 *
 * @date    2019-08-02
 *
 * Copyright (c) organization
 *
 */

#include <cmath>
#include <vector>
#include <iostream>

#include <matplotlib-cpp/MatplotlibCpp.hpp>

int main(int argc, char* argv[])
{
    pe::vis::Matplotlib mpllib;

    if (!mpllib.imported()) {
        std::cout << "Failed to import matplotlib library\n";
        exit(EXIT_FAILURE);
    }

    int n = 5000;
    std::vector<double> x(n), y(n), z(n), w(n, 2);
    for (int i = 0; i < n; ++i) {
        x.emplace_back(i * i);
        y.emplace_back(sin(2 * M_PI * i / 360.0));
        z.emplace_back(log(i));
    }

    mpllib.figure(50, 50);

    mpllib.plot(x, y);
    mpllib.title("Sample plot");
    mpllib.legend();

    mpllib.show();
    mpllib.savefig("temp.png");

    return 0;
}
