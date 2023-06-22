#pragma once

#include <opencv2/opencv.hpp>

double gaussian(double s, double rr);

cv::Mat mat_nearbyint(cv::Mat src);

cv::Mat mat_clump(cv::Mat src);