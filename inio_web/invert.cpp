#include "invert.hpp"

cv::Mat invert(cv::Mat src) {
	cv::Mat Max(src.rows, src.cols, CV_64FC1, cv::Scalar::all(255));
	return Max - src;
}