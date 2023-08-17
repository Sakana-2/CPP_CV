#include <cmath>

#include "util.hpp"

cv::Mat mat_nearbyint(cv::Mat src) {
	cv::Mat dst = cv::Mat::zeros (src.rows, src.cols, CV_64FC1);
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			o_row[j] = std::nearbyint(row[j]);
		}
	}
	return dst;
}

cv::Mat mat_clump(cv::Mat src) {
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);
	for (int i = 0; i < dst.rows; ++i)
	{
		double* s_row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			if (s_row[j] < 0) {
				o_row[j] = 0;
			}
			else if (s_row[j] > 255) {
				o_row[j] = 255;
			}
			else {
				o_row[j] = s_row[j];
			}
		}
	}
	return dst;
}

MyImage mat2myimage(cv::Mat src) {
	return { std::vector<double>(src.begin<double>(), src.end<double>()),src.rows,src.cols,src.channels() == 1};
}

cv::Mat myimage2mat(MyImage src) {
	cv::Mat dst(src.rows, src.cols, src.ismono ? CV_64FC1 : CV_64FC3);
	for (int i = 0; i < src.rows; i++)
	{
		if (src.ismono) {
			double* row = dst.ptr<double>(i);
			for (int j = 0; j < src.cols; j++)
			{
				row[j] = src.data[i * src.cols + j];
			}
		}
		else {
			cv::Vec3d* row = dst.ptr<cv::Vec3d>(i);
			for (int j = 0; j < src.cols; j+=3)
			{
				row[j] = { src.data[i * src.cols + j],src.data[i * src.cols + j + 1],src.data[i * src.cols + j + 2] };
			}
		}
	}
	return dst;
}