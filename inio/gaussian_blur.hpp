#pragma once

#include <opencv2/opencv.hpp>

cv::Mat gblur(cv::Mat src, ushort blocksize,double sigma);