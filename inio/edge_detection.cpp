#include <cmath>

#include "edge_detection.hpp"
#include "layer.hpp"
#include "filter2d.hpp"

cv::Mat _prewitt(cv::Mat src) {
	cv::Mat kernel_x(3, 3, CV_64FC1, cv::Scalar::all(0)), kernel_y(3, 3, CV_64FC1, cv::Scalar::all(0));
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));
	
	kernel_x.at<double>(0, 0) = -1;
	kernel_x.at<double>(1, 0) = -1;
	kernel_x.at<double>(2, 0) = -1;
	kernel_x.at<double>(0, 2) = 1;
	kernel_x.at<double>(1, 2) = 1;
	kernel_x.at<double>(2, 2) = 1;

	kernel_y.at<double>(0, 0) = -1;
	kernel_y.at<double>(0, 1) = -1;
	kernel_y.at<double>(0, 2) = -1;
	kernel_y.at<double>(2, 0) = 1;
	kernel_y.at<double>(2, 1) = 1;
	kernel_y.at<double>(2, 2) = 1;

	cv::Mat prewitt_x = filter2d(src, kernel_x);
	cv::Mat prewitt_y = filter2d(src, kernel_y);
	for (int i = 0; i < dst.rows; ++i)
	{
		double* prewitt_x_row = prewitt_x.ptr<double>(i);
		double* prewitt_y_row = prewitt_y.ptr<double>(i);
		double* dst_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			dst_row[j] = std::sqrt(std::pow(prewitt_x_row[j], 2.0) + std::pow(prewitt_y_row[j],2.0));
		}
	}
	return dst;
}

cv::Mat _sobel(cv::Mat src) {
	cv::Mat kernel_x(3, 3, CV_64FC1, cv::Scalar::all(0)), kernel_y(3, 3, CV_64FC1, cv::Scalar::all(0));
	cv::Mat dst(src.rows, src.cols, CV_64FC1, cv::Scalar::all(0));

	kernel_x.at<double>(0, 0) = -1;
	kernel_x.at<double>(1, 0) = -2;
	kernel_x.at<double>(2, 0) = -1;
	kernel_x.at<double>(0, 2) = 1;
	kernel_x.at<double>(1, 2) = 2;
	kernel_x.at<double>(2, 2) = 1;

	kernel_y.at<double>(0, 0) = -1;
	kernel_y.at<double>(0, 1) = -2;
	kernel_y.at<double>(0, 2) = -1;
	kernel_y.at<double>(2, 0) = 1;
	kernel_y.at<double>(2, 1) = 2;
	kernel_y.at<double>(2, 2) = 1;

	cv::Mat sobel_x = filter2d(src, kernel_x);
	cv::Mat sobel_y = filter2d(src, kernel_y);
	for (int i = 0; i < dst.rows; ++i)
	{
		double* sobel_x_row = sobel_x.ptr<double>(i);
		double* sobel_y_row = sobel_y.ptr<double>(i);
		double* dst_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			dst_row[j] = std::sqrt(std::pow(sobel_x_row[j], 2.0) + std::pow(sobel_y_row[j], 2.0));
		}
	}
	return dst;
}

cv::Mat _laplacian(cv::Mat src, int mode) {
	cv::Mat kernel(3, 3, CV_64FC1, cv::Scalar::all(0));

	switch (mode)
	{
	case LAPLACIAN_4:
		kernel.at<double>(0, 0) = 0;
		kernel.at<double>(1, 0) = 1;
		kernel.at<double>(2, 0) = 0;
		kernel.at<double>(0, 1) = 1;
		kernel.at<double>(1, 1) = -4;
		kernel.at<double>(2, 1) = 1;
		kernel.at<double>(0, 2) = 0;
		kernel.at<double>(1, 2) = 1;
		kernel.at<double>(2, 2) = 0;
		break;
	case LAPLACIAN_8:
		kernel.at<double>(0, 0) = 1;
		kernel.at<double>(1, 0) = 1;
		kernel.at<double>(2, 0) = 1;
		kernel.at<double>(0, 1) = 1;
		kernel.at<double>(1, 1) = -8;
		kernel.at<double>(2, 1) = 1;
		kernel.at<double>(0, 2) = 1;
		kernel.at<double>(1, 2) = 1;
		kernel.at<double>(2, 2) = 1;
		break;
	default:
		break;
	}
	
	return filter2d(src,kernel);
}