#include <iostream>
#include "threshold.hpp"
#include "border_prettier.hpp"

cv::Mat th(cv::Mat src, uchar thresh)
{
	for (int i = 0; i < src.rows; ++i)
	{
		uchar* row = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			row[j] = (row[j] > thresh) ? 255 : 0;
		}
	}
	return src;
}

cv::Mat ad_th_mean(cv::Mat src, ushort blocksize, uchar c) {
	cv::Mat img = boder_replicate<uchar>(src, blocksize);
	ushort half = (blocksize - 1) / 2;

	auto range_average = [img, blocksize, half](int y, int x) -> double
	{
		int sum = 0;
		for (int i = y - half; i < y + half + 1; ++i) {
			const uchar* row = img.ptr<uchar>(i);
			for (int j = x - half; j < x + half + 1; ++j) {
				sum += row[j];
			}
		}
		return sum / static_cast<double>(blocksize * blocksize);
	};

	for (int i = 0; i < src.rows; ++i)
	{
		uchar* i_row = img.ptr<uchar>(i + half);
		uchar* o_row = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			double th = range_average(i + half, j + half) - c;
			uchar thresh = th < 0 ? 0 : static_cast<uchar>(std::nearbyint(th));
			o_row[j] = o_row[j] > th ? 255 : 0;
		}
	}
	return src;
}