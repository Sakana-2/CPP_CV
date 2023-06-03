#include <cmath>
#include "gamma_correction.hpp"

cv::Mat gc(cv::Mat src, double ganma) {
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			o_row[j] = std::nearbyint(255 * std::pow(row[j] / 255.0, 1.0 / ganma));
		}
	}
	return dst;
}