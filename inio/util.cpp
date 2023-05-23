#include "util.hpp"
#include <cmath>

double gaussian(double s,double rr) {
	const double pi = 3.141592653589793;
	return std::exp(-rr / (2 * s * s)) / (2 * pi * s * s);
}