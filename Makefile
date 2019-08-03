examples_pyenv:
	mkdir build_examples && cd build_examples && cmake -DBUILD_EXAMPLES=ON -DUSE_PYENV=ON ../ && cmake build .
