#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

class Inio
{
	std::string output_path;
	std::vector<cv::Mat> history; //ƒ|ƒCƒ“ƒ^‚Ì•Û‘¶‚Ì•û‚ª‘‚¢‚©‚à‚µ‚ê‚È‚¢
public:
	Inio(std::string path);
	void adaptive_threshold(ushort blocksize, uchar c);
	void equalize_hist();
	void gamma_correction(double ganma = 2.2);
	cv::Mat get();
	void grayscale(double b = 0.0722, double g = 0.7152, double r = 0.2126);
	void multiply(Inio term);
	void save();
	void save(std::string another_path);
	void show();
	void threshold(uchar thresh);
	void unsharpmask(ushort blocksize, int k);
};