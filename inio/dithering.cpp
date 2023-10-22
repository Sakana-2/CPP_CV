#include "dithering.hpp"

cv::Mat _bayer(cv::Mat src, int kernelsize) {
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);

	double _m2[2][2] = { {0,2},{3,1} };
	cv::Mat m2(2, 2, CV_64FC1,_m2);
	m2 += 1;
	m2 /= 4;
	m2 *= 256;

	double _m4[4][4] = { {0,8,2,10},{12,4,14,6},{3,11,1,9},{15,7,13,5} };
	cv::Mat m4(4, 4, CV_64FC1, _m4);
	m4 += 1;
	m4 /= 16;
	m4 *= 256;

	double _m8[8][8] = { {0,48,12,60,3,51,15,63},{32,16,44,28,35,19,47,31},{8,56,4,52,11,59,7,55},{40,24,36,20,43,27,39,23},{2,50,14,62,1,49,13,61},{34,18,46,30,33,17,45,29},{10,58,6,54,9,57,5,53},{42,26,38,22,41,25,37,21} };
	cv::Mat m8(8, 8, CV_64FC1, _m8);
	m8 += 1;
	m8 /= 64;
	m8 *= 256;

	cv::Mat m;
	if (kernelsize == 2) {
		m = m2.clone();
	}else if(kernelsize == 4){
		m = m4.clone();
	}
	else if (kernelsize == 8) {
		m = m8.clone();
	}
	else {
		; //å„Ç≈çÏê¨
	}

	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* drow = dst.ptr<double>(i);
		double* mrow = m.ptr<double>(i % kernelsize);
		for (int j = 0; j < src.cols; j++)
		{
			if (row[j] > mrow[j % kernelsize]) {
				drow[j] = 255;
			}
			else {
				drow[j] = 0;
			}
		}
	}
	return dst;
}