#include <iostream>

#include "border_prettier.hpp"
#include "grayscale.hpp"
#include "threshold.hpp"

cv::Mat th(cv::Mat src, uchar thresh)
{
	if (src.type() == CV_64FC3) {
		src = gs(src);
	}
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			row[j] = (row[j] > thresh) ? 255 : 0;
		}
	}
	return src;
}

cv::Mat ad_th_mean(cv::Mat src, ushort blocksize, uchar c) {
	if (src.type() == CV_64FC3) {
		src = gs(src);
	}
	cv::Mat img = boder_replicate<double>(src, blocksize);
	ushort half = (blocksize - 1) / 2;

	auto range_average = [img, blocksize, half](int y, int x) {
		ushort sum = 0;
		for (int i = y - half; i < y + half + 1; ++i) {
			const double* row = img.ptr<double>(i);
			for (int j = x - half; j < x + half + 1; ++j) {
				sum += row[j];
			}
		}
		return sum / static_cast<double>(blocksize * blocksize);
	};

	for (int i = 0; i < src.rows; ++i)
	{
		double* i_row = img.ptr<double>(i + half);
		double* o_row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			//std::cout << i << " " << j << std::endl;
			double th = range_average(i + half, j + half) - c;
			uchar thresh = th < 0 ? 0 : th;
			o_row[j] = o_row[j] > std::nearbyint(th) ? 255 : 0;
		}
	}
	return src;
}