#include <cmath>

#include "gamma_correction.hpp"
#include "lut.hpp"

cv::Mat gc(cv::Mat src, double ganma) {
	uchar lut[256] = { 0 };
	for (int i = 0; i < 256; ++i)
	{
		lut[i] = std::nearbyint(255 * std::pow(i / 255.0, 1.0 / ganma));
	}
	return LUT(src, lut);
}