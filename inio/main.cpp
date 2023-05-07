#include <iostream>

#include "main.hpp"
#include "ganma_correction.hpp"
#include "grayscale.hpp"
#include "equalize_hist.hpp"
#include "threshold.hpp"

Inio::Inio(std::string path) {
	output_path = path;
	history.push_back(cv::imread(path));
}

void Inio::adaptive_threshold(ushort blocksize, uchar c) {
	if (history.back().type() == CV_8UC3) {
		history.push_back(ad_th_mean(gs(history.back()), blocksize, c));
	}
	else {
		history.push_back(ad_th_mean(history.back(), blocksize, c));
	}
	
}

void Inio::equalize_hist() {
	history.push_back(eh(history.back()));
}

void Inio::ganma_correction(float ganma) {
	history.push_back(gc(history.back(), ganma));
}

void Inio::grayscale(double b, double g, double r) {
	history.push_back(gs(history.back(), b, g, r));
}

void Inio::save() {
	cv::imwrite(output_path, history.back());//historyの現在位置の(略)
}

void Inio::save(std::string another_path) {
	output_path = another_path;
	save();
}

void Inio::show() {
	cv::namedWindow(output_path, cv::WINDOW_NORMAL);
	cv::imshow(output_path, history.back());//あとで、タイトルを整形して代入するようにする historyの現在位置の画像を表示できるようにする。デフォルトのガンマ値を変えられるようにする
	cv::waitKey(0);
}

void Inio::threshold(uchar thresh) {
	history.push_back(th(history.back(), thresh));
}

int main()
{
	Inio asano("../assets/st_view.jpg");
	asano.adaptive_threshold(3, 1);
	asano.save();
	return 0;
}