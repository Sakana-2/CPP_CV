#include <iostream>

#include "equalize_hist.hpp"

cv::Mat eh(cv::Mat src) {
	unsigned int hist[256] = {}, cumsum[256] = {};
	//ヒストグラム
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			hist[static_cast<int>(row[j])] += 1;
		}
	}
	/*
	累積和を求める
	0の時だけ分離したのはC++だと-1をインデックスにできないから
	*/
	cumsum[0] = hist[0];
	for (int i=1; i<256;++i)
	{
		cumsum[i] = cumsum[i - 1] + hist[i];
	}
	double size = cumsum[255];
	//累積和を直線状に整形
	for (int i = 0; i < 256; ++i) {
		cumsum[i] = std::nearbyint(cumsum[i] * 255 / size);
	}

	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);
	//値を置換していく
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			o_row[j] = cumsum[static_cast<int>(row[j])];
		}
	}
	return dst;
}