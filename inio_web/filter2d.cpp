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
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);
	int half = (kernel.rows - 1) / 2;


	for (int i = 0; i < dst.rows; ++i)
	{
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			//畳み込み処 (カーネルの左上のインデックスが
			//元の画像をfor文で回した時のインデックスと一致)
			double sum = 0;
			for (int l = i; l < i + (2 * half) + 1; ++l) { 
				double* i_row = img.ptr<double>(l);
				double* k_row = kernel.ptr<double>(l-i);
				for (int m = j; m < j + (2 * half) + 1; ++m) {
					sum += i_row[m] * k_row[m - j];
				}
			}
			o_row[j] = sum; //丸めは最後に
		}
	}
	return dst;
} 