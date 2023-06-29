#pragma once

#include <opencv2/opencv.hpp>

enum LAPLACIAN_MODES {
	LAPLACIAN_4,
	LAPLACIAN_8
};

cv::Mat _prewitt(cv::Mat src);

cv::Mat _sobel(cv::Mat src);

cv::Mat _laplacian(cv::Mat src, int mode);