#include <iostream>
#include "threshold.hpp"

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