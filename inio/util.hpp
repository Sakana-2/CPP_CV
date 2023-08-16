#pragma once

#include <cmath>
#include <opencv2/opencv.hpp>

#include "global.hpp"

inline double gaussian(double s, double rr) {
	return std::exp(-rr / (2 * s * s)) / (2 * PI * s * s);
}

cv::Mat mat_nearbyint(cv::Mat src);

cv::Mat mat_clump(cv::Mat src);