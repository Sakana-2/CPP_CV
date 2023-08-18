#pragma once

#ifdef NDEBUG
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#endif

#include <cmath>
#include <opencv2/opencv.hpp>

#include "global.hpp"

inline double gaussian(double s, double rr) {
	return std::exp(-rr / (2 * s * s)) / (2 * PI * s * s);
}

cv::Mat mat_nearbyint(cv::Mat src);

cv::Mat mat_clump(cv::Mat src);

#ifdef NDEBUG
pybind11::dict mat2dict(cv::Mat src);

cv::Mat dict2mat(pybind11::dict src);
#endif // NDEBUG