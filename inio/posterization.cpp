#include "LUT.hpp"


cv::Mat pz(cv::Mat src, uchar level) {
	double height = 255.0 / (level - 1), width = 255.0 / level;
	uchar lut[256] = { 0 };
	uchar pre, next;
	for (uchar i = 0; i < level; i++) {
		pre = width * i;
		next = width * (i + 1);
		for (uchar j = pre; j < next; j++)
		{
			lut[j] = height * i;
		}
	}
	lut[255] = 255;
	return LUT(src, lut);
}