#include <iostream>

#include "main.hpp"
#include "grayscale.hpp"
#include "equalize_hist.hpp"
#include "threshold.hpp"

Inio::Inio(std::string path) {
	output_path = path;
	history.push_back(cv::imread(path));
}

void Inio::equalize_hist() {
	history.push_back(eh(history.back()));
}

void Inio::grayscale(double b, double g, double r) {
	history.push_back(gs(history.back(), b, g, r));
}

void Inio::threshold(uchar thresh) {
	history.push_back(th(history.back(), thresh));
}

void Inio::show() {
	cv::imshow(output_path, history.back());//あとで、整形して代入するようにする //historyの現在位置の画像を表示できるようにする
	cv::waitKey(0);
}

void Inio::save() {
	cv::imwrite(output_path, history.back());//historyの現在位置の(略)
}

void Inio::save(std::string another_path) {
	output_path = another_path;
	save();
}

int main()
{
	Inio asano("../assets/lenna.jpg");
	asano.grayscale();
	asano.threshold(125);
	asano.show();
	return 0;
}