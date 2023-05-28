#include <cmath>

#include "filter2d.hpp"
#include "border_prettier.hpp"

cv::Mat filter2d(cv::Mat src, cv::Mat kernel) {

	if (kernel.rows != kernel.cols) {
		std::cout << "Sorry, not support rectangular kernel." << std::endl;
		std::exit(0);
	}
	if ((kernel.rows % 2 == 0) || (kernel.cols % 2 == 0)) {
		std::cout << "Kernel sizes must be odd." << std::endl;
		std::exit(0);
	}

	cv::Mat img = border_replicate(src,kernel.rows);
	int half = (kernel.rows - 1) / 2;


	for (int i = 0; i < src.rows; ++i)
	{
		double* o_row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			//畳み込み処 (カーネルの左上のインデックスが
			//元の画像をfor文で回した時のインデックスと一致)
			double sum = 0;
			for (int l = i; l < i + (2 * half) + 1; ++l) { 
				double* i_row = img.ptr<double>(i);
				double* k_row = kernel.ptr<double>(l-i);
				for (int m = j; m < j + (2 * half) + 1; ++m) {
					sum += i_row[m] * k_row[m - j];
				}
			}
			if (sum < 0) {
				sum = 0;
			}
			else if (sum > 255) {
				sum = 255;
			}
			o_row[j] = std::nearbyint(sum);
		}
	}
	
	return src;

}