#include <iostream>
#include <cmath>
#include "box_filter.hpp"
#include "grayscale.hpp"
#include "threshold.hpp"

cv::Mat th(cv::Mat src, uchar thresh)
{
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));
	cv::Mat src2;
	if (src.type() == CV_64FC3) {
		src2 = gs(src);
	}
	else {
		src2 = src.clone();
	}
	
	for (int i = 0; i < src2.rows; ++i)
	{
		double* row = src2.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src2.cols; ++j)
		{
			o_row[j] = (row[j] > thresh) ? 255 : 0;
		}
	}
	return dst;
}

cv::Mat ad_th_mean(cv::Mat src, ushort blocksize, uchar c) {
	cv::Mat src2;
	if (src.type() == CV_64FC3) {
		src2 = gs(src);
	}
	else {
		src2 = src.clone();
	}

	cv::Mat mean = box_filter(src2, blocksize);
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));

	for (int i = 0; i < src2.rows; ++i)
	{
		double* m_row = mean.ptr<double>(i);
		double* row = src2.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			double th = m_row[j] - c;
			o_row[j] = (row[j] > std::nearbyint(th)) ? 255 : 0;
		}
	}
	return dst;
}