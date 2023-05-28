#include "./unsharpmask.hpp"
#include "filter2d.hpp";

cv::Mat um(cv::Mat src, ushort blocksize, double k) {
	double half = (blocksize - 1) / 2;
	double bb = blocksize * blocksize;
	cv::Mat kernel(blocksize, blocksize, CV_64FC1, cv::Scalar::all(0));
	for (int i = 0; i < blocksize; ++i) {
		double* row = kernel.ptr<double>(i);
		for (int j = 0; j < blocksize; ++j) {
			if ((i == half) && (j == half)) { //ど真ん中だったら
				row[j] = 1 + ((bb - 1) * k / bb);
			}
			else { //外側だったら
				row[j] = -k / bb;
			}
		}
	}
	return filter2d(src, kernel);
}