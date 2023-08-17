#pragma once

#include <vector>

const double PI = 3.141592653589793;

enum LAPLACIAN_MODES {
	LAPLACIAN_4,
	LAPLACIAN_8
};

struct MyImage {
	std::vector<double> data;
	int rows;
	int cols;
	bool ismono;
};