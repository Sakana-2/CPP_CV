#include <cmath>

#include "global.hpp"
#include "util.hpp"

cv::Mat mat_nearbyint(cv::Mat src) {
	cv::Mat dst = cv::Mat::zeros (src.rows, src.cols, CV_64FC1);
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			o_row[j] = std::nearbyint(row[j]);
		}
	}
	return dst;
}

cv::Mat mat_clump(cv::Mat src) {
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);
	
	for (int i = 0; i < dst.rows; ++i)
	{
		double* s_row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			if (s_row[j] < 0) {
				o_row[j] = 0;
			}
			else if (s_row[j] > 255) {
				o_row[j] = 255;
			}
			else {
				o_row[j] = s_row[j];
			}
		}
	}
	return dst;
}