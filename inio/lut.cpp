#include "LUT.hpp"

cv::Mat LUT(cv::Mat src, uchar lut[256]) {
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			//std::cout << (int)row[j] << " " << (int)lut[(int)row[j]] << std::endl;
			o_row[j] = lut[(int)row[j]];
		}
	}
	return dst;
}