#include <cmath>

#include "gaussian_blur.hpp"
#include "util.hpp"
#include "filter2d.hpp"

cv::Mat gaussian_blur(cv::Mat src, ushort blocksize, double sigma) {
	double half = (blocksize - 1) / 2;
	cv::Mat kernel(blocksize, blocksize, CV_64FC1, cv::Scalar::all(0));
	double sum = 0;
	for (int i = 0; i < blocksize; i++)
	{
		double* row = kernel.ptr<double>(i);
		for (int j = 0; j < blocksize; j++)
		{
			double value = gaussian(sigma, std::pow(i - half, 2) + std::pow(j - half, 2));
			row[j] = value;
			sum += value;
		}
	}
	return filter2d(src, kernel / sum);
}