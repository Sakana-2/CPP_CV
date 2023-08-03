#pragma once

#include <opencv2/opencv.hpp>

void HoughLines(cv::Mat src, double rho, double theta, int threshold);