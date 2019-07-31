# C++ Wrapper for Python Matplotlib Lib #
I was looking for a light-weighted C++ library for visualization to integrate into my programs when I realized that there are no officialy *small* ones existing. One attempt that I noticed was a C++ wrapper for the famous visualization python library: Matplotlib (the original one can be found [HERE](https://github.com/lava/matplotlib-cpp); and the modified program with CMake build can be found [HERE](https://github.com/xmba15/matplotlib-cpp)). However, looking at the source codes to find a way to expand the library, I found out that the current approach directly utilizing Python/C API; makes it quite difficult for an expansion. That is the start of this library, written with pybind11 in hope of providing a more convenient way to connect with Matplotlib library.

## Dependencies ##
 - OS: Ubuntu (tested on 16.04, 19.04)
 - C++11 and above
 - python2/3
 - [pybind11](https://github.com/pybind/pybind11.git) : C++ library for seamless conversion between C++ and python
 - [matplotlib](https://matplotlib.org/)
