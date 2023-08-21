#include "invert.hpp"

cv::Mat invrt(cv::Mat src) {
	cv::Mat Max(src.rows, src.cols, CV_64FC1, cv::Scalar::all(255));
	return Max - src;
}