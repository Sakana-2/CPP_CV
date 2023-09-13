#include "box_filter.hpp"
#include "filter2d.hpp"

cv::Mat bf(cv::Mat src, ushort blocksize) {
	cv::Mat kernel(blocksize, blocksize, CV_64FC1, cv::Scalar::all(1 / ((double)blocksize * blocksize)));
	return filter2d(src, kernel);
}