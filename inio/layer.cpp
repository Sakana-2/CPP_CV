#include "layer.hpp"

cv::Mat mp(cv::Mat term1, cv::Mat term2) {
	if ((term1.rows != term2.rows) || (term1.cols != term2.cols)) { //•”•ª“I‚ÉæZ‚à‚Å‚«‚é‚æ‚¤‚É‚·‚é
		std::cout << "Multiplying different size image is not available." << std::endl;
		return term1;
	}
	return ((term2 / 255).mul(term1 / 255)) * 255;
}

cv::Mat _add(cv::Mat term1, cv::Mat term2) {
	cv::Mat dst = term1 + term2;
	for (int i = 0; i < dst.rows; ++i)
	{
		double* row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			row[j] = row[j] > 255 ? 255 : row[j];
		}
	}
	return dst;
}