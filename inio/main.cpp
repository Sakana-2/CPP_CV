#include <iostream>

#include "main.hpp"
#include "border_prettier.hpp"
#include "ganma_correction.hpp"
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

void Inio::ganma_correction(float ganma) {
	history.push_back(gc(src, ganma));
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
	cv::imshow(output_path, history.back());//あとで、タイトルを整形して代入するようにする historyの現在位置の画像を表示できるようにする。デフォルトのガンマ値を変えられるようにする
	cv::waitKey(0);
}

void Inio::threshold(uchar thresh) {
	history.push_back(th(history.back(), thresh));
}

int main()
{
	//Inio asano("../assets/lenna.jpg");
	cv::imwrite("./saint.png", boder_replicate<cv::Vec3b>(cv::imread("../assets/tes.png", -1), 5));
	return 0;
}