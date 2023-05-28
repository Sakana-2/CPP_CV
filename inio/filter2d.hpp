#pragma once

#include <opencv2/opencv.hpp>

#include "util.hpp"

cv::Mat filter2d(cv::Mat src, cv::Mat kernel);