#include "grayscale.hpp"

//ポインタをループ変数にしたらもっと早いかも

cv::Mat gs(cv::Mat src, double b,double g, double r)
{
	cv::Mat dst(src.rows, src.cols, CV_64FC1,cv::Scalar::all(0));
	for (int i = 0; i < src.rows; ++i)
	{
		cv::Vec3d* row = src.ptr<cv::Vec3d>(i);
		double* dst_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			dst_row[j] = std::nearbyint((row[j][0] * b) + (row[j][1] * g) + (row[j][2] * r));
		}
	}
	return dst;
}