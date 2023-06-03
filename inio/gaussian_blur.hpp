#pragma once

#include <opencv2/opencv.hpp>

cv::Mat gaussian_blur(cv::Mat src, ushort blocksize,double sigma);