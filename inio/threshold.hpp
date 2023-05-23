#pragma once

#include <opencv2/opencv.hpp>

cv::Mat th(cv::Mat src, uchar thresh);

cv::Mat ad_th_mean(cv::Mat src, ushort blocksize, uchar c);