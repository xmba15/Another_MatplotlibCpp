/**
 * @file    Basic.cpp
 *
 * @date    2019-08-02
 *
 * Copyright (c) organization
 *
 */

#include <matplotlib-cpp/MatplotlibCpp.hpp>

int main(int argc, char *argv[]) {
  using namespace pybind11::literals; // NOLINT(build/namespaces_literals)

  pe::vis::Matplotlib mpllib;
  if (!mpllib.imported()) {
    std::cout << "Failed to import matplotlib library\n";
  }

  int n = 5000;
  std::vector<double> x(n), y(n), z(n), w(n, 2);
  for (int i = 0; i < n; ++i) {
    x.emplace_back(i * i);
    y.emplace_back(sin(2 * M_PI * i / 360.0));
    z.emplace_back(log(i));
  }

  mpllib.figure(50, 50);
  py::dict kwargs = py::dict("label"_a = "sine line");
  mpllib.plot(x, y, kwargs);
  mpllib.title("Sample plot");
  mpllib.legend();

  mpllib.show();
  mpllib.savefig("temp");

  return 0;
}
