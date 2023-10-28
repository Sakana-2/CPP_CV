#include <opencv2/opencv.hpp>

cv::Mat _bayer(cv::Mat src, int kernelsize);

cv::Mat MakeThresholdMap2(int kernelsize, bool isstart);