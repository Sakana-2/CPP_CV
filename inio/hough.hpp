#pragma once

#include <opencv2/opencv.hpp>

void hl(cv::Mat src, double rho, double theta, int threshold);

//void CreateTrigTable(std::vector<double>& tabSin, std::vector<double>& tabCos, double theta, int numangle, double rho);