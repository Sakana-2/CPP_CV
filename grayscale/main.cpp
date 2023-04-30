#include "grayscale.hpp"
#include <iostream>
int main() {
	//std::cout << std::round(127.5) << std::endl;
	cv::imwrite("./MAJIDESEIKOUSIRO.png", grayscale(cv::imread("../assets/lenna.jpg")));
	return 0;
}