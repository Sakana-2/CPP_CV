#pragma once

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "global.hpp"

class Inio
{
	std::string output_path;
	std::vector<cv::Mat> history; //É|ÉCÉìÉ^ÇÃï€ë∂ÇÃï˚Ç™ëÅÇ¢Ç©Ç‡ÇµÇÍÇ»Ç¢
public:
	void adaptive_threshold_mean(ushort blocksize, uchar c);
	void contrast_emphasizing(uchar i_min, uchar i_max, uchar o_min, uchar o_max);
	void equalize_hist();
	void gamma_correction(double ganma = 2.2);
	void gaussisn_blur(ushort blocksize, double sigma);
	cv::Mat get();
	void grayscale(double b = 0.0722, double g = 0.7152, double r = 0.2126);
	void houghLines(double rho, double theta, int threshold);
	void invert();
	void laplacian(int mode);
	void multiply(Inio term);
	void posterize(uchar level);
	void prewitt();
	void save();
	void save(std::string another_path);

	void load(std::string path);
	void load(cv::Mat raw);
	void show();
	void sobel();
	void threshold(uchar thresh);
	void unsharpmask_lap(int laplacian_mode, double k, int c);
	void unsharpmask_mean(ushort blocksize, double k, int c);
};