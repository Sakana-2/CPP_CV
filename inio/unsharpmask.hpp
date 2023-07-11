#pragma once

#include <opencv2/opencv.hpp>

cv::Mat um_laplacian(cv::Mat src, int laplacian_mode, double k,int c);

cv::Mat um_mean(cv::Mat src, ushort blocksize, double k, int c);