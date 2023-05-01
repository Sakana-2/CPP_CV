#include <opencv2/opencv.hpp>

#include "../grayscale/grayscale.hpp"
#include "equalize_hist.hpp"

int main() {
	cv::imwrite("./equalize_hist.png",equalize_hist(grayscale(cv::imread("../assets/lenna.jpg"))));
	return 0;
}