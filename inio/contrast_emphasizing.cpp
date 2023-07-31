#include <cmath>

#include "contrast_emphasizing.hpp"
#include "LUT.hpp"

cv::Mat ce(cv::Mat src, uchar i_min, uchar i_max, uchar o_min, uchar o_max) {
	uchar lut[256] = { 0 };
	const double t = (double)(o_max - o_min) / (i_max - i_min);
	for (int i = 0; i < 256; i++)
	{
		if (i < i_min) {
			lut[i] = o_min;
		}
		else if ((i_min <= i) && (i <= i_max)) {
			lut[i] = std::nearbyint(t * (i - (double)i_min) + o_min);
		}
		else {
			lut[i] = o_max;
		}
	}
	return LUT(src, lut);
}