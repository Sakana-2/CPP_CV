#pragma once

#include <opencv2/opencv.hpp>

struct line {
	double theta;
	double rho;
};

void hl(cv::Mat src, std::vector<line>& lines, double rho, double theta, int threshold);

//void CreateTrigTable(std::vector<double>& tabSin, std::vector<double>& tabCos, double theta, int numangle, double rho);