#include <cmath>

#include "dithering.hpp"
#include "util.hpp"

cv::Mat _bayer(cv::Mat src, int kernelsize) {
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);

	cv::Mat m;
	if(isInteger(std::log2(kernelsize))) {
		m = MakeThresholdMap2(kernelsize,true);
	}
	else {
		;
	}

	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* drow = dst.ptr<double>(i);
		double* mrow = m.ptr<double>(i % kernelsize);
		for (int j = 0; j < src.cols; j++)
		{
			if (row[j] > mrow[j % kernelsize]) {
				drow[j] = 255;
			}
			else {
				drow[j] = 0;
			}
		}
	}
	return dst;
}

cv::Mat MakeThresholdMap2(int kernelsize, bool isstart) {
	cv::Mat dst;
	if (kernelsize == 2) {
		dst = cv::Mat(2, 2, CV_64FC1);
		dst.at<double>(0, 0) = 0;
		dst.at<double>(0, 1) = 2;
		dst.at<double>(1, 0) = 3;
		dst.at<double>(1, 1) = 1;
	}
	else {
		cv::Mat temp;
		cv::Mat halfx4 = MakeThresholdMap2(kernelsize / 2, false) * 4;
		cv::vconcat(halfx4, halfx4 + 3, dst);
		cv::vconcat(halfx4 + 2, halfx4 + 1, temp);
		cv::hconcat(dst, temp, dst);
	}

	if (isstart) {
		dst += 1;
		dst /= (kernelsize * kernelsize);
		dst *= 256;
	}
	return dst;
}