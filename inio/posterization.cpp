#include "LUT.hpp"
#include <cmath>

cv::Mat pz(cv::Mat src, uchar level) {
	double height = 255.0 / (level - 1), width = 255.0 / level;
	uchar lut[256] = { 0 };
	lut[255] = 255;
	uchar pre, next;
	for (uchar i = 0; i < level; i++) {
		pre = std::ceil(width * i);
		next = std::ceil(width * (i + 1));
		for (uchar j = pre; j < next; j++)
		{
			lut[j] = std::ceil(height * i);
		}
	}
	return LUT(src, lut);
}