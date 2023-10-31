#include "edge_detection.hpp"
#include "filter2d.hpp"
#include "global.hpp"
#include "unsharpmask.hpp"
#include "util.hpp"

cv::Mat um_laplacian(cv::Mat src, int laplacian_mode, double k, int c) {
	cv::Mat kernel = cv::Mat::zeros(3, 3, CV_64FC1), dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);
	cv::Mat sorry = cv::Mat::ones(5, 5, CV_64FC1);
	sorry.at<double>(2, 2) = 10;
	sorry.at<double>(1, 3) = 16;
	switch (laplacian_mode)
	{
	case LAPLACIAN_4:
		kernel.at<double>(0, 0) = 0;
		kernel.at<double>(1, 0) = -k;
		kernel.at<double>(2, 0) = 0;
		kernel.at<double>(0, 1) = -k;
		kernel.at<double>(1, 1) = 1+4*k;
		kernel.at<double>(2, 1) = -k;
		kernel.at<double>(0, 2) = 0;
		kernel.at<double>(1, 2) = -k;
		kernel.at<double>(2, 2) = 0;
		break;
	case LAPLACIAN_8:
		kernel.at<double>(0, 0) = -k;
		kernel.at<double>(1, 0) = -k;
		kernel.at<double>(2, 0) = -k;
		kernel.at<double>(0, 1) = -k;
		kernel.at<double>(1, 1) = 1+8*k;
		kernel.at<double>(2, 1) = -k;
		kernel.at<double>(0, 2) = -k;
		kernel.at<double>(1, 2) = -k;
		kernel.at<double>(2, 2) = -k;
		break;
	default:
		break;
	}
	return mat_clump(filter2d(src, kernel)) + c;
}

cv::Mat um_mean(cv::Mat src, ushort blocksize, double k, int c) {
	double half = (blocksize - 1) / 2;
	double bb = blocksize * blocksize;
	cv::Mat kernel = cv::Mat::zeros(blocksize, blocksize, CV_64FC1);
	for (int i = 0; i < blocksize; ++i) {
		double* row = kernel.ptr<double>(i);
		for (int j = 0; j < blocksize; ++j) {
			if ((i == half) && (j == half)) { //‚Ç^‚ñ’†‚¾‚Á‚½‚ç
				row[j] = 1 + ((bb - 1) * k / bb);
			}
			else { //ŠO‘¤‚¾‚Á‚½‚ç
				row[j] = -k / bb;
			}
		}
	}
	return mat_clump(filter2d(src, kernel)) + c;
}