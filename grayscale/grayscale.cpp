#include "grayscale.hpp"
#include <iostream>

cv::Mat grayscale(cv::Mat src, double b,double g, double r)
{
	cv::Mat dst(src.cols, src.rows, CV_8UC1,cv::Scalar::all(0));
	for (int i = 0; i < src.rows; ++i)
	{
		cv::Vec3b* row = src.ptr<cv::Vec3b>(i);
		uchar* dst_row = dst.ptr<uchar>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			dst_row[j] = static_cast<uchar>(std::round((row[j][0] * b) + (row[j][1] * g) + (row[j][2] * r)));
		}
	}
	return dst;
}