#include "util.hpp"
#include <cmath>

double gaussian(double s,double rr) {
	const double pi = 3.141592653589793;
	return std::exp(-rr / (2 * s * s)) / (2 * pi * s * s);
}

cv::Mat mat_nearbyint(cv::Mat src) {
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));
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