#include "grayscale.hpp"

//ポインタをループ変数にしたらもっと早いかも

cv::Mat gs(cv::Mat src, double b,double g, double r)
{
	cv::Mat dst(src.rows, src.cols, CV_8UC1,cv::Scalar::all(0));
	for (int i = 0; i < src.rows; ++i)
	{
		cv::Vec3b* row = src.ptr<cv::Vec3b>(i);
		uchar* dst_row = dst.ptr<uchar>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			dst_row[j] = static_cast<uchar>(std::nearbyint((row[j][0] * b) + (row[j][1] * g) + (row[j][2] * r)));
		}
	}
	return dst;
}