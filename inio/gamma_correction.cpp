#include <cmath>
#include "gamma_correction.hpp"

cv::Mat gc(cv::Mat src, double ganma) {
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			row[j] = std::nearbyint(255 * std::pow(row[j] / 255.0, 1.0 / ganma));
		}
	}
	return src;
}